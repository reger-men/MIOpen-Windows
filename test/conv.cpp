/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/
#include "test.hpp"
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <miopen/convolution.hpp>
#include <miopen/miopen.h>
#include <miopen/tensor.hpp>
#include <utility>

// #include "network_data.hpp"
#include "driver.hpp"
#include "get_handle.hpp"
#include "tensor_holder.hpp"
#include "verify.hpp"
#include <miopen/stringutils.hpp>

struct tensor_elem_gen_float
{
    double max_value = 1e-2;

    template <class... Ts>
    double operator()(Ts... Xs) const
    {
        return max_value * tensor_elem_gen_integer{17}(Xs...) / 17 * (double(std::rand())) /
               RAND_MAX;
    }
};

struct tensor_elem_gen_one
{
    template <class... Ts>
    double operator()(Ts...) const
    {
        return 1;
    }
};

template <class T>
tensor<T> get_output_tensor(const miopen::ConvolutionDescriptor& filter,
                            const tensor<T>& input,
                            const tensor<T>& weights)
{
    return tensor<T>{filter.GetForwardOutputTensor(input.desc, weights.desc)};
}

template <class T>
struct conv_base
{
    tensor<T> input;
    tensor<T> weights;
    tensor<T> out;
    miopen::ConvolutionDescriptor filter;
    int bias{};
    int search{};

    void fail(float = 0) const
    {
        std::cout << "Input tensor: " << input.desc.ToString() << std::endl;
        std::cout << "Weights tensor: " << weights.desc.ToString() << std::endl;
        std::cout << "Output tensor: " << out.desc.ToString() << std::endl;
        std::cout << "Filter: " << filter << std::endl;
    }
};

template <class T>
struct verify_forward_conv : conv_base<T>
{
    using conv_base<T>::out;
    using conv_base<T>::input;
    using conv_base<T>::weights;
    using conv_base<T>::filter;
    using conv_base<T>::bias;
    using conv_base<T>::search;

    verify_forward_conv(const tensor<T>& pinput,
                        const tensor<T>& pweights,
                        const miopen::ConvolutionDescriptor& pfilter,
                        int pbias   = 0,
                        int psearch = 0)
    {
        input   = pinput;
        weights = pweights;
        filter  = pfilter;
        bias    = pbias;
        search  = psearch;
    }

    tensor<T> cpu() const
    {
        auto rout = get_output_tensor(filter, input, weights);

        if(filter.mode == miopenTranspose)
        {
            std::fill(rout.begin(), rout.end(), 0);

            int out_h, out_w;
            std::tie(std::ignore, std::ignore, out_h, out_w) =
                miopen::tien<4>(rout.desc.GetLengths());

            int wei_c, wei_h, wei_w;
            std::tie(std::ignore, wei_c, wei_h, wei_w) = miopen::tien<4>(weights.desc.GetLengths());

            int in_n, in_c, in_h, in_w;
            std::tie(in_n, in_c, in_h, in_w) = miopen::tien<4>(input.desc.GetLengths());

            par_ford(in_n, wei_c)([&](int o, int k) {
                ford(in_c, in_h, in_w, wei_h, wei_w)([&](int w, int i, int j, int x, int y) {
                    const int start_x = i * filter.u - filter.pad_h;
                    const int start_y = j * filter.v - filter.pad_w;
                    const int out_x   = start_x + x * filter.dilation_h;
                    const int out_y   = start_y + y * filter.dilation_w;
                    if(out_x >= 0 && out_x < out_h && out_y >= 0 && out_y < out_w)
                    {
                        rout(o, k, out_x, out_y) += input(o, w, i, j) * weights(w, k, x, y);
                    }
                });
            });
        }
        else if(filter.mode == miopenGroupConv || filter.mode == miopenDepthwise)
        {
            int in_h, in_w;
            std::tie(std::ignore, std::ignore, in_h, in_w) =
                miopen::tien<4>(input.desc.GetLengths());

            int wei_n, wei_c, wei_h, wei_w;
            std::tie(wei_n, wei_c, wei_h, wei_w) = miopen::tien<4>(weights.desc.GetLengths());

            rout.par_for_each([&](int o, int w, int i, int j) {
                const int start_x  = i * filter.u - filter.pad_h;
                const int start_y  = j * filter.v - filter.pad_w;
                const int group_id = w / (wei_n / filter.group_count);

                double acc = bias;
                ford(wei_c, wei_h, wei_w)([&](int k, int x, int y) {
                    const int in_x  = start_x + x;
                    const int in_y  = start_y + y;
                    const int in_ch = group_id * wei_c + k;
                    if(in_x >= 0 && in_x < in_h && in_y >= 0 && in_y < in_w)
                    {
                        acc += input(o, in_ch, in_x, in_y) * weights(w, k, x, y);
                    }
                });
                rout(o, w, i, j) = acc;
            });
        }
        else
        {
            int in_h, in_w;
            std::tie(std::ignore, std::ignore, in_h, in_w) =
                miopen::tien<4>(input.desc.GetLengths());

            int wei_c, wei_h, wei_w;
            std::tie(std::ignore, wei_c, wei_h, wei_w) = miopen::tien<4>(weights.desc.GetLengths());

            rout.par_for_each([&](int o, int w, int i, int j) {
                const int start_x = i * filter.u - filter.pad_h;
                const int start_y = j * filter.v - filter.pad_w;

                double acc = bias;
                ford(wei_c, wei_h, wei_w)([&](int k, int x, int y) {
                    const int in_x = start_x + x * filter.dilation_h;
                    const int in_y = start_y + y * filter.dilation_w;
                    if(in_x >= 0 && in_x < in_h && in_y >= 0 && in_y < in_w)
                    {
                        acc += input(o, k, in_x, in_y) * weights(w, k, x, y);
                    }
                });
                rout(o, w, i, j) = acc;
            });
        }

        return rout;
    }

    tensor<T> gpu() const
    {
        auto&& handle = get_handle();
        auto rout     = get_output_tensor(filter, input, weights);

        auto in_dev  = handle.Write(input.data);
        auto wei_dev = handle.Write(weights.data);
        auto out_dev = handle.Write(rout.data);

        size_t workspace_size =
            filter.ForwardGetWorkSpaceSize(handle, weights.desc, input.desc, rout.desc);

        std::vector<char> workspace(workspace_size);
        auto workspace_dev = workspace_size != 0 ? handle.Write(workspace) : nullptr;

        int ret_algo_count;
        miopenConvAlgoPerf_t perf;

        float alpha = 1, beta = 0;

        filter.FindConvFwdAlgorithm(handle,
                                    input.desc,
                                    in_dev.get(),
                                    weights.desc,
                                    wei_dev.get(),
                                    rout.desc,
                                    out_dev.get(),
                                    1,
                                    &ret_algo_count,
                                    &perf,
                                    workspace_dev.get(),
                                    workspace_size,
                                    search);

        filter.ConvolutionForward(handle,
                                  &alpha,
                                  input.desc,
                                  in_dev.get(),
                                  weights.desc,
                                  wei_dev.get(),
                                  perf.fwd_algo,
                                  &beta,
                                  rout.desc,
                                  out_dev.get(),
                                  workspace_dev.get(),
                                  workspace_size);

        rout.data = handle.Read<T>(out_dev, rout.data.size());

        return rout;
    }

    void fail(float = 0) const
    {
        std::cout << "Forward convolution: " << std::endl;
        this->conv_base<T>::fail();
    }
};

template <class T>
struct verify_backward_conv : conv_base<T>
{
    using conv_base<T>::input;
    using conv_base<T>::weights;
    using conv_base<T>::out;
    using conv_base<T>::filter;
    using conv_base<T>::bias;
    using conv_base<T>::search;

    verify_backward_conv(const tensor<T>& pinput,
                         const tensor<T>& pweights,
                         const tensor<T>& pout,
                         const miopen::ConvolutionDescriptor& pfilter,
                         int pbias   = 0,
                         int psearch = 0)
    {
        input   = pinput;
        weights = pweights;
        out     = pout;
        filter  = pfilter;
        bias    = pbias;
        search  = psearch;
    }

    tensor<T> cpu() const
    {
        auto rinput = input;
        std::fill(rinput.begin(), rinput.end(), 0);

        if(filter.mode == miopenTranspose)
        {
            int out_h, out_w;
            std::tie(std::ignore, std::ignore, out_h, out_w) =
                miopen::tien<4>(out.desc.GetLengths());

            int wei_c, wei_h, wei_w;
            std::tie(std::ignore, wei_c, wei_h, wei_w) = miopen::tien<4>(weights.desc.GetLengths());

            rinput.par_for_each([&](int o, int w, int i, int j) {
                const int start_x = i * filter.u - filter.pad_h;
                const int start_y = j * filter.v - filter.pad_w;

                double acc = 0.0;
                ford(wei_c, wei_h, wei_w)([&](int k, int x, int y) {
                    const int in_x = start_x + x * filter.dilation_h;
                    const int in_y = start_y + y * filter.dilation_w;
                    if(in_x >= 0 && in_x < out_h && in_y >= 0 && in_y < out_w)
                    {
                        acc += out(o, k, in_x, in_y) * weights(w, k, x, y);
                    }
                });
                rinput(o, w, i, j) = acc;
            });
        }
        else if(filter.mode == miopenGroupConv || filter.mode == miopenDepthwise)
        {
            int in_c, in_h, in_w;
            std::tie(std::ignore, in_c, in_h, in_w) = miopen::tien<4>(rinput.desc.GetLengths());

            int wei_c, wei_h, wei_w;
            std::tie(std::ignore, wei_c, wei_h, wei_w) = miopen::tien<4>(weights.desc.GetLengths());

            int out_n, out_c, out_h, out_w;
            std::tie(out_n, out_c, out_h, out_w) = miopen::tien<4>(out.desc.GetLengths());

            par_ford(out_n, in_c)([&](int o, int k) {
                const int group_id = k / wei_c;
                ford(out_c / filter.group_count, out_h, out_w, wei_h, wei_w)(
                    [&](int w, int i, int j, int x, int y) {
                        const int start_x = i * filter.u - filter.pad_h;
                        const int start_y = j * filter.v - filter.pad_w;
                        const int in_x    = start_x + x;
                        const int in_y    = start_y + y;
                        const int out_ch  = group_id * (out_c / filter.group_count) + w;
                        const int wei_ch  = k % wei_c;
                        if(in_x >= 0 && in_x < in_h && in_y >= 0 && in_y < in_w)
                        {
                            rinput(o, k, in_x, in_y) +=
                                out(o, out_ch, i, j) * weights(out_ch, wei_ch, x, y);
                        }
                    });
            });
        }
        else
        {
            int in_h, in_w;
            std::tie(std::ignore, std::ignore, in_h, in_w) =
                miopen::tien<4>(rinput.desc.GetLengths());

            int wei_c, wei_h, wei_w;
            std::tie(std::ignore, wei_c, wei_h, wei_w) = miopen::tien<4>(weights.desc.GetLengths());

            int out_n, out_c, out_h, out_w;
            std::tie(out_n, out_c, out_h, out_w) = miopen::tien<4>(out.desc.GetLengths());

            par_ford(out_n, wei_c)([&](int o, int k) {
                ford(out_c, out_h, out_w, wei_h, wei_w)([&](int w, int i, int j, int x, int y) {
                    const int start_x = i * filter.u - filter.pad_h;
                    const int start_y = j * filter.v - filter.pad_w;
                    const int in_x    = start_x + x * filter.dilation_h;
                    const int in_y    = start_y + y * filter.dilation_w;
                    if(in_x >= 0 && in_x < in_h && in_y >= 0 && in_y < in_w)
                    {
                        rinput(o, k, in_x, in_y) += out(o, w, i, j) * weights(w, k, x, y);
                    }
                });
            });
        }
        return rinput;
    }

    tensor<T> gpu() const
    {
        auto&& handle = get_handle();
        auto rinput   = input;
        std::fill(rinput.begin(), rinput.end(), 0);

        auto out_dev = handle.Write(out.data);
        auto wei_dev = handle.Write(weights.data);
        auto in_dev  = handle.Write(rinput.data);

        size_t workspace_size =
            filter.BackwardDataGetWorkSpaceSize(handle, weights.desc, out.desc, rinput.desc);

        std::vector<char> workspace(workspace_size);
        auto workspace_dev = workspace_size != 0 ? handle.Write(workspace) : nullptr;

        int ret_algo_count;
        miopenConvAlgoPerf_t perf;

        float alpha = 1, beta = 0;

        filter.FindConvBwdDataAlgorithm(handle,
                                        out.desc,
                                        out_dev.get(),
                                        weights.desc,
                                        wei_dev.get(),
                                        rinput.desc,
                                        in_dev.get(),
                                        1,
                                        &ret_algo_count,
                                        &perf,
                                        workspace_dev.get(),
                                        workspace_size,
                                        search);

        filter.ConvolutionBackwardData(handle,
                                       &alpha,
                                       out.desc,
                                       out_dev.get(),
                                       weights.desc,
                                       wei_dev.get(),
                                       perf.bwd_data_algo,
                                       &beta,
                                       rinput.desc,
                                       in_dev.get(),
                                       workspace_dev.get(),
                                       workspace_size);

        rinput.data = handle.Read<T>(in_dev, rinput.data.size());
        return rinput;
    }

    void fail(float) const
    {
        std::cout << "Backward convolution: " << std::endl;
        this->conv_base<T>::fail();
    }
};

template <class T>
struct verify_backward_weights_conv : conv_base<T>
{
    using conv_base<T>::input;
    using conv_base<T>::weights;
    using conv_base<T>::out;
    using conv_base<T>::filter;
    using conv_base<T>::bias;
    using conv_base<T>::search;

    verify_backward_weights_conv(const tensor<T>& pinput,
                                 const tensor<T>& pweights,
                                 const tensor<T>& pout,
                                 const miopen::ConvolutionDescriptor& pfilter,
                                 int pbias   = 0,
                                 int psearch = 0)
    {
        input   = pinput;
        weights = pweights;
        out     = pout;
        filter  = pfilter;
        bias    = pbias;
        search  = psearch;
    }

    tensor<T> cpu() const
    {
        auto rweights = weights;
        std::fill(rweights.begin(), rweights.end(), 0);

        int in_h, in_w;
        std::tie(std::ignore, std::ignore, in_h, in_w) = miopen::tien<4>(
            filter.mode == miopenTranspose ? out.desc.GetLengths() : input.desc.GetLengths());

        int wei_c, wei_h, wei_w;
        std::tie(std::ignore, wei_c, wei_h, wei_w) = miopen::tien<4>(rweights.desc.GetLengths());

        int out_n, out_c, out_h, out_w;
        std::tie(out_n, out_c, out_h, out_w) = miopen::tien<4>(
            filter.mode == miopenTranspose ? input.desc.GetLengths() : out.desc.GetLengths());

        int groups = 1;
        if(filter.mode == miopenGroupConv || filter.mode == miopenDepthwise)
            groups = filter.group_count;

        par_ford(out_c, wei_c, wei_h, wei_w)([&](int w, int k, int x, int y) {
            double acc         = 0.0;
            const int group_id = w / (out_c / groups);
            const int in_ch    = group_id * wei_c + k;
            ford(out_n, out_h, out_w)([&](int o, int i, int j) {
                const int start_x = i * filter.u - filter.pad_h;
                const int start_y = j * filter.v - filter.pad_w;
                const int in_x    = start_x + x * filter.dilation_h;
                const int in_y    = start_y + y * filter.dilation_w;
                if(in_x >= 0 && in_x < in_h && in_y >= 0 && in_y < in_w)
                {
                    acc += (filter.mode == miopenTranspose
                                ? out(o, k, in_x, in_y) * input(o, w, i, j)
                                : input(o, in_ch, in_x, in_y) * out(o, w, i, j));
                }
            });
            rweights(w, k, x, y) = acc;
        });
        return rweights;
    }

    tensor<T> gpu() const
    {
        auto&& handle = get_handle();
        auto rweights = weights;
        std::fill(rweights.begin(), rweights.end(), 0);

        auto out_dev = handle.Write(out.data);
        auto wei_dev = handle.Write(rweights.data);
        auto in_dev  = handle.Write(input.data);

        std::size_t workspace_size = filter.ConvolutionBackwardWeightsGetWorkSpaceSize(
            handle, out.desc, input.desc, rweights.desc);

        std::vector<char> workspace(workspace_size);
        auto workspace_dev = workspace_size != 0 ? handle.Write(workspace) : nullptr;

        int ret_algo_count;
        miopenConvAlgoPerf_t perf;

        float alpha = 1, beta = 0;
        filter.FindConvBwdWeightsAlgorithm(handle,
                                           out.desc,
                                           out_dev.get(),
                                           input.desc,
                                           in_dev.get(),
                                           rweights.desc,
                                           wei_dev.get(),
                                           1,
                                           &ret_algo_count,
                                           &perf,
                                           workspace_dev.get(),
                                           workspace_size,
                                           search);

        filter.ConvolutionBackwardWeights(handle,
                                          &alpha,
                                          out.desc,
                                          out_dev.get(),
                                          input.desc,
                                          in_dev.get(),
                                          perf.bwd_weights_algo,
                                          &beta,
                                          rweights.desc,
                                          wei_dev.get(),
                                          workspace_dev.get(),
                                          workspace_size);

        rweights.data = handle.Read<T>(wei_dev, rweights.data.size());
        return rweights;
    }

    void fail(float) const
    {
        std::cout << "Backward weights convolution: " << std::endl;
        this->conv_base<T>::fail();
    }
};

template <class T>
struct conv_driver : test_driver
{
    tensor<T> input;
    tensor<T> weights;
    miopen::ConvolutionDescriptor filter;
    std::string conv_mode;
    std::string pad_mode;
    bool enable_backward_weights = false;
    bool do_backward_data        = true;
    int search                   = 0;
    unsigned long max_value      = miopen_type<T>{} == miopenHalf ? 5 : 17;
    int groupCount{};

    std::unordered_map<std::string, miopenConvolutionMode_t> cmode_lookup = {
        {"CONV", miopenConvolution},
        {"TRANS", miopenTranspose},
        {"GROUP", miopenGroupConv},
        {"DW", miopenDepthwise},
        {"CONVOLUTION", miopenConvolution},
        {"TRANSPOSE", miopenTranspose},
        {"GROUPCONV", miopenGroupConv},
        {"DEPTHWISE", miopenDepthwise}};

    std::unordered_map<std::string, miopenPaddingMode_t> pmode_lookup = {
        {"SAME", miopenPaddingSame},
        {"VALID", miopenPaddingValid},
        {"DEFAULT", miopenPaddingDefault}};

    conv_driver()
    {
        add(input, "input", get_input_tensor(tensor_elem_gen_integer{max_value}));
        add(weights, "weights", get_weights_tensor(tensor_elem_gen_integer{max_value}));
        add(filter, "filter", generate_data(get_filters()));
        add(enable_backward_weights, "enable-backward-weights", flag());
        add(do_backward_data, "disable-backward-data", set_value(false));
        add(search, "search", set_value(1));
        add(conv_mode, "cmode", generate_data({"conv"}));
        add(pad_mode, "pmode", generate_data({"default", "same", "valid"}));
        add(groupCount, "group-count", generate_data({1}));
    }

    std::vector<miopen::ConvolutionDescriptor> get_filters()
    {
        return {miopen::ConvolutionDescriptor{0, 0, 1, 1},
                miopen::ConvolutionDescriptor{0, 0, 2, 2},
                miopen::ConvolutionDescriptor{1, 1, 1, 1},
                miopen::ConvolutionDescriptor{1, 1, 2, 2},
                miopen::ConvolutionDescriptor{2, 2, 1, 1},
                miopen::ConvolutionDescriptor{3, 3, 2, 2},
                miopen::ConvolutionDescriptor{0, 0, 1, 1, 2, 2},
                miopen::ConvolutionDescriptor{1, 1, 2, 2, 3, 3},
                miopen::ConvolutionDescriptor{3, 3, 2, 2, 4, 4}};
    }

    void run()
    {
        int input_c, input_h, input_w, wei_c, wei_k, wei_h, wei_w;
        std::tie(wei_k, wei_c, wei_h, wei_w) = miopen::tien<4>(weights.desc.GetLengths());
        std::tie(std::ignore, input_c, input_h, input_w) = miopen::tien<4>(input.desc.GetLengths());

        filter.mode        = cmode_lookup[miopen::ToUpper(conv_mode)];
        filter.paddingMode = pmode_lookup[miopen::ToUpper(pad_mode)];
        filter.group_count =
            filter.mode == miopenDepthwise ? input_c : std::max(static_cast<int>(groupCount), 1);
        if(filter.group_count > 1 &&
           !(filter.mode == miopenDepthwise || filter.mode == miopenTranspose))
            filter.mode = miopenGroupConv;

        /// lack of support of 2x2 filter and transposeConv for half type
        /// \todo enhance support of half type into conv/transConv
        if((input.desc.GetType() == miopenHalf) &&
           (((filter.mode == miopenConvolution) && !filter.IsDirectSupported(weights.desc)) ||
            (filter.dilation_h > 1 || filter.dilation_w > 1) ||
            (filter.mode == miopenTranspose || filter.mode == miopenGroupConv ||
             filter.mode == miopenDepthwise)))
        {
            // Unsupported config for conv with half type
            return;
        }

        if(((filter.mode == miopenTranspose) && (input_c == wei_k)) ||
           ((filter.mode == miopenConvolution) && (input_c == wei_c)) ||
           ((filter.mode == miopenGroupConv) && (input_c % wei_c == 0)) ||
           ((filter.mode == miopenDepthwise) && (wei_c == 1)))
        {
            if(filter.mode == miopenConvolution &&
               ((filter.dilation_h == 1 && filter.dilation_w == 1) || (wei_h == 1 && wei_w == 1)))
            {
                if(filter.paddingMode == miopenPaddingSame)
                {
                    if(filter.u == 0 || filter.v == 0)
                        return;
                    auto _pad_h =
                        (input_h % filter.u == 0)
                            ? (std::max(static_cast<int>(wei_h - filter.u), 0))
                            : (std::max(static_cast<int>(wei_h - (input_h % filter.u)), 0));
                    auto _pad_w =
                        (input_w % filter.v == 0)
                            ? (std::max(static_cast<int>(wei_w - filter.v), 0))
                            : (std::max(static_cast<int>(wei_w - (input_w % filter.v)), 0));

                    filter.pad_h = _pad_h / 2;
                    filter.pad_w = _pad_w / 2;

                    int out_h = std::ceil(static_cast<double>(input_h) / filter.u);
                    int out_w = std::ceil(static_cast<double>(input_w) / filter.v);

                    if(out_h <= 0 || out_w <= 0)
                        return;
                }
                else if(filter.paddingMode == miopenPaddingValid)
                {
                    if(filter.u == 0 || filter.v == 0)
                        return;
                    filter.pad_h = 0;
                    filter.pad_w = 0;

                    int out_h = std::ceil(static_cast<double>(input_h - wei_h + 1) / filter.u);
                    int out_w = std::ceil(static_cast<double>(input_w - wei_w + 1) / filter.v);

                    if(out_h <= 0 || out_w <= 0)
                        return;
                }
            }

            if(((filter.mode == miopenConvolution &&
                 input.desc.GetLengths().at(1) == weights.desc.GetLengths().at(1)) ||
                (filter.mode == miopenTranspose &&
                 input.desc.GetLengths().at(1) == weights.desc.GetLengths().at(0)) ||
                (filter.mode == miopenGroupConv &&
                 (input.desc.GetLengths().at(1) % weights.desc.GetLengths().at(1) == 0)) ||
                (filter.mode == miopenDepthwise && weights.desc.GetLengths().at(1) == 1)) &&
               wei_h > 2 * filter.pad_h && wei_w > 2 * filter.pad_w &&
               input_h >= (2 * filter.pad_h + wei_h) && input_w >= (2 * filter.pad_w + wei_w))
            {
                auto out_p = verify(verify_forward_conv<T>{input, weights, filter, 0, search});
                for(auto& x : out_p.first)
                    x = (long(x + 19) * 2) % max_value + (long(x + 19) * 2) % (max_value - 1) +
                        (long(x + 19) * 2) % (max_value + 1); // Clamp big numbers
                if(do_backward_data)
                    verify(verify_backward_conv<T>{input, weights, out_p.first, filter, 0, search});
                if(enable_backward_weights or (MIOPEN_USE_MIOPENGEMM and sizeof(T) > 2))
                {
                    verify(verify_backward_weights_conv<T>{
                        input, weights, out_p.first, filter, 0, search});
                }
            }
        }
    }
};

int main(int argc, const char* argv[]) { test_drive<conv_driver>(argc, argv); }
