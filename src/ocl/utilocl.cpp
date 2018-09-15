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
#include <cmath>
#include <miopen/kernel_cache.hpp>
#include <miopen/util.hpp>

#define WG_SIZE 256
#define MAX_ACTIVE_THREADS (64 * 4 * 64)
#define MAX_LOCAL_MEM 65536
//#define MIOPEN_TRANS_DEBUG

namespace miopen {

float Im2ColGPU(Handle& handle,
                const int data_size,
                ConstData_t im,
                const int im_offset,
                const int c,
                const int h,
                const int w,
                const int wei_h,
                const int wei_w,
                const int out_h,
                const int out_w,
                const int pad_h,
                const int pad_w,
                const int stride_h,
                const int stride_w,
                const int dilation_h,
                const int dilation_w,
                Data_t col)
{
    std::string program_name = "MIOpenUtilKernels.cl";
    std::string kernel_name  = "Im2Col";

    std::string network_config = std::to_string(c) + std::to_string(h) + std::to_string(w) +
                                 std::to_string(wei_h) + std::to_string(wei_w) +
                                 std::to_string(pad_h) + std::to_string(pad_w) +
                                 std::to_string(stride_h) + std::to_string(stride_w) +
                                 std::to_string(dilation_h) + std::to_string(dilation_w);

    auto&& kernels = handle.GetKernels("miopenIm2Col", network_config);

    if(!kernels.empty())
    {
        int data_size_off = data_size - im_offset;
        auto kernel       = kernels.front();
        kernel(data_size_off,
               im,
               im_offset,
               h,
               w,
               wei_h,
               wei_w,
               out_h,
               out_w,
               pad_h,
               pad_w,
               stride_h,
               stride_w,
               dilation_h,
               dilation_w,
               col);
    }
    else
    {
        std::string params;
        int num_ch_per_wg;
        if((out_h <= 8 && out_w <= 8) && (stride_h == 1 && stride_w == 1) && (c % 4 == 0))
            num_ch_per_wg = 4;
        else
            num_ch_per_wg = 1;

        int tile_sz_x  = 32;
        int tile_sz_y  = 8;
        int num_blks_x = std::ceil(static_cast<float>(out_w) / tile_sz_x);
        int num_blks   = num_blks_x * std::ceil(static_cast<float>(out_h) / tile_sz_y);
        int local_mem_sz;
        if(num_ch_per_wg == 1)
            local_mem_sz = ((tile_sz_x - 1) * stride_w + (wei_w - 1) * dilation_w + 1) *
                           ((tile_sz_y - 1) * stride_h + (wei_h - 1) * dilation_h + 1);
        else
            local_mem_sz = std::max(
                num_ch_per_wg *
                    ((std::ceil(static_cast<float>(tile_sz_x) / num_ch_per_wg) - 1) * stride_w +
                     (wei_w - 1) * dilation_w + 1) *
                    ((tile_sz_y - 1) * stride_h + (wei_h - 1) * dilation_h + 1),
                num_ch_per_wg * ((tile_sz_x - 1) * stride_w + (wei_w - 1) * dilation_w + 1) *
                    ((std::ceil(static_cast<float>(tile_sz_y) / num_ch_per_wg) - 1) * stride_h +
                     (wei_h - 1) * dilation_h + 1));

        // adjust mapping for large kernel
        int type_size    = 4; // Need to adjust for fp16
        int extreme_case = num_ch_per_wg * ((wei_w - 1) * dilation_w + 1) *
                           ((wei_h - 1) * dilation_h + 1) * type_size;
        if(extreme_case > MAX_LOCAL_MEM)
        {
            params += " -DEXTREME_LARGE";
            params += " -DNUM_CH_TOTAL=" + std::to_string(c);
        }
        else
        {
            while(local_mem_sz * type_size > MAX_LOCAL_MEM)
            {
                tile_sz_x  = tile_sz_x == 1 ? 1 : (tile_sz_y == 1 ? (tile_sz_x / 2) : tile_sz_x);
                tile_sz_y  = tile_sz_y == 1 ? 1 : (tile_sz_y / 2);
                num_blks_x = std::ceil(static_cast<float>(out_w) / tile_sz_x);
                num_blks   = num_blks_x * std::ceil(static_cast<float>(out_h) / tile_sz_y);
                if(num_ch_per_wg == 1)
                    local_mem_sz = ((tile_sz_x - 1) * stride_w + (wei_w - 1) * dilation_w + 1) *
                                   ((tile_sz_y - 1) * stride_h + (wei_h - 1) * dilation_h + 1);
                else
                    local_mem_sz = std::max(
                        num_ch_per_wg *
                            ((std::ceil(static_cast<float>(tile_sz_x) / num_ch_per_wg) - 1) *
                                 stride_w +
                             (wei_w - 1) * dilation_w + 1) *
                            ((tile_sz_y - 1) * stride_h + (wei_h - 1) * dilation_h + 1),
                        num_ch_per_wg *
                            ((tile_sz_x - 1) * stride_w + (wei_w - 1) * dilation_w + 1) *
                            ((std::ceil(static_cast<float>(tile_sz_y) / num_ch_per_wg) - 1) *
                                 stride_h +
                             (wei_h - 1) * dilation_h + 1));
            }
        }

        int data_size_off = data_size - im_offset;

        params += " -DNUM_CH_PER_WG=" + std::to_string(num_ch_per_wg);
        params += " -DNUM_IM_BLKS_X=" + std::to_string(num_blks_x);
        params += " -DNUM_IM_BLKS=" + std::to_string(num_blks);
        params += " -DLOCAL_MEM_SIZE=" + std::to_string(local_mem_sz);
        params += " -DSTRIDE_GT_1=" + std::to_string(static_cast<int>(stride_h * stride_w > 1));
        params += " -DTILE_SZ_X=" + std::to_string(tile_sz_x);
        params += " -DTILE_SZ_Y=" + std::to_string(tile_sz_y);
        params += " -DUSE_IM_OFF_GUARD=1 -DMIOPEN_USE_FP16=0 -DMIOPEN_USE_FP32=1";

        const std::vector<size_t> vld{256, 1, 1};
        size_t global_threads = 256 * std::max(1, (c / num_ch_per_wg)) * num_blks;
        const std::vector<size_t> vgd{global_threads, 1, 1};

        handle.AddKernel(
            "miopenIm2Col", network_config, program_name, kernel_name, vld, vgd, params)(
            data_size_off,
            im,
            im_offset,
            h,
            w,
            wei_h,
            wei_w,
            out_h,
            out_w,
            pad_h,
            pad_w,
            stride_h,
            stride_w,
            dilation_h,
            dilation_w,
            col);
    }

    return handle.GetKernelTime();
}

float Col2ImGPU(Handle& handle,
                ConstData_t col,
                const int col_h,
                const int col_w,
                const int wei_h,
                const int wei_w,
                const int pad_h,
                const int pad_w,
                const int stride_h,
                const int stride_w,
                const int dilation_h,
                const int dilation_w,
                const int c,
                const int h,
                const int w,
                Data_t im,
                int im_offset)
{
    std::string program_name = "MIOpenUtilKernels2.cl";
    std::string kernel_name  = "Col2Im";

    std::string network_config =
        std::to_string(col_h) + std::to_string(col_w) + std::to_string(wei_h) +
        std::to_string(wei_w) + std::to_string(pad_h) + std::to_string(pad_w) +
        std::to_string(stride_h) + std::to_string(stride_w) + std::to_string(dilation_h) +
        std::to_string(dilation_w) + std::to_string(c) + std::to_string(h) + std::to_string(w);

    auto&& kernels = handle.GetKernels("miopenCol2Im", network_config);

    if(!kernels.empty())
    {
        auto kernel = kernels.front();
        kernel(col,
               col_h,
               col_w,
               wei_h,
               wei_w,
               pad_h,
               pad_w,
               stride_h,
               stride_w,
               dilation_h,
               dilation_w,
               h,
               w,
               im,
               im_offset);
    }
    else
    {
        std::string params = "-DMIOPEN_USE_FP16=0 -DMIOPEN_USE_FP32=1";
        const std::vector<size_t> vld{256, 1, 1};
        size_t global_threads = c * h * w;
        const std::vector<size_t> vgd{global_threads, 1, 1};

        handle.AddKernel(
            "miopenCol2Im", network_config, program_name, kernel_name, vld, vgd, params)(col,
                                                                                         col_h,
                                                                                         col_w,
                                                                                         wei_h,
                                                                                         wei_w,
                                                                                         pad_h,
                                                                                         pad_w,
                                                                                         stride_h,
                                                                                         stride_w,
                                                                                         dilation_h,
                                                                                         dilation_w,
                                                                                         h,
                                                                                         w,
                                                                                         im,
                                                                                         im_offset);
    }
    return handle.GetKernelTime();
}

float transpose_NCHW2CNHW(Handle& handle,
                          int n,
                          int c,
                          int h_in,
                          int w_in,
                          int h_out,
                          int w_out,
                          ConstData_t in,
                          Data_t out,
                          int in_offset,
                          int out_offset,
                          int h_stride,
                          int w_stride)
{

    std::string program_name = "MIOpenUtilKernels4.cl";

    if(h_stride == 1 && w_stride == 1)
    {
        assert(h_in == h_out && w_in == w_out);

        std::string kernel_name = "transpose_NCHW2CNHW_opt";

        std::string network_config = std::to_string(n) + std::to_string(c) + std::to_string(h_in) +
                                     std::to_string(w_in) + std::to_string(in_offset) +
                                     std::to_string(out_offset);

        auto&& kernels = handle.GetKernels(kernel_name, network_config);

        if(!kernels.empty())
        {
            auto kernel = kernels.front();
            kernel(in, out);
        }
        else
        {
            int RD_BLCK      = ((h_in * w_in) % 4 == 0) ? 4 : ((h_in * w_in) % 2 == 0) ? 2 : 1;
            int HW_RD        = (h_in * w_in) / RD_BLCK;
            size_t MAP_RD    = HW_RD * c;
            size_t lcl_size0 = WG_SIZE; //((MAP_RD + 63)/64 < 4) ? ((MAP_RD + 63)/64)*64 : 256;

            std::string READ_TYPE = (RD_BLCK == 1) ? "float" : "float" + std::to_string(RD_BLCK);

            std::string params;
            params += " -DNC_TRANS_NCHW_OPT";
            params += " -DIN_OFF=" + std::to_string(in_offset);
            params += " -DOUT_OFF=" + std::to_string(out_offset);
            params += " -DH=" + std::to_string(h_in);
            params += " -DW=" + std::to_string(w_in);
            params += " -DN=" + std::to_string(n);
            params += " -DC=" + std::to_string(c);
            params += " -DRD_BLCK=" + std::to_string(RD_BLCK);
            params += " -DHW_RD=" + std::to_string(HW_RD);
            params += " -DMAP_RD=" + std::to_string(MAP_RD);
            params += " -DREAD_TYPE=" + READ_TYPE;

            const std::vector<size_t> vld{lcl_size0, 1, 1};
            std::vector<size_t> vgd{MAP_RD, 1, 1};

            if(MAP_RD < MAX_ACTIVE_THREADS)
            {
                vgd = {MAP_RD, static_cast<size_t>(n), 1};
                params += " -D_2D_WG";
            }

            handle.AddKernel(
                kernel_name, network_config, program_name, kernel_name, vld, vgd, params)(in, out);
        }
    }
    else
    {
        assert(h_in > h_out && w_in > w_out);

        std::string kernel_name = "transpose_NCHW2CNHW";

        std::string network_config =
            std::to_string(n) + std::to_string(c) + std::to_string(h_in) + std::to_string(h_out) +
            std::to_string(w_in) + std::to_string(w_out) + std::to_string(h_stride) +
            std::to_string(w_stride) + std::to_string(in_offset) + std::to_string(out_offset);

        auto&& kernels = handle.GetKernels(kernel_name, network_config);

        if(!kernels.empty())
        {
            auto kernel = kernels.front();
            kernel(in, out);
        }
        else
        {
            std::string params;
            params += " -DNC_TRANS_NCHW";
            params += " -DN=" + std::to_string(n);
            params += " -DC=" + std::to_string(c);
            params += " -DHW_IN=" + std::to_string(h_in * w_in);
            params += " -DHW_OUT=" + std::to_string(h_out * w_out);
            params += " -DW_IN=" + std::to_string(w_in);
            params += " -DW_OUT=" + std::to_string(w_out);
            params += " -DH_STRIDE=" + std::to_string(h_stride);
            params += " -DW_STRIDE=" + std::to_string(w_stride);
            params += " -DIN_OFF=" + std::to_string(in_offset);
            params += " -DOUT_OFF=" + std::to_string(out_offset);

            size_t ld0 = WG_SIZE;
            size_t gd0 = c * h_out * w_out;
            const std::vector<size_t> vld{ld0, 1, 1};
            std::vector<size_t> vgd{gd0, 1, 1};

            if(gd0 < MAX_ACTIVE_THREADS)
            {
                vgd = {gd0, static_cast<size_t>(n), 1};
                params += " -D_2D_WG";
            }

            handle.AddKernel(
                kernel_name, network_config, program_name, kernel_name, vld, vgd, params)(in, out);
        }
    }

#ifdef MIOPEN_TRANS_DEBUG
    float nMB = (float)n * c * (h_out * w_out + h_in * w_in) * sizeof(float) * 1e-6;
    fprintf(stderr,
            "NCHW->CNHW MB: %f time: %f GB/s: %f\n",
            nMB,
            handle.GetKernelTime(),
            2 * nMB / handle.GetKernelTime());
#endif

    return handle.GetKernelTime();
}

float transpose_CNHW2NCHW(Handle& handle,
                          int n,
                          int c,
                          int h_out,
                          int w_out,
                          int h_in,
                          int w_in,
                          ConstData_t in,
                          Data_t out,
                          int in_offset,
                          int out_offset,
                          int h_stride,
                          int w_stride)
{

    std::string program_name = "MIOpenUtilKernels4.cl";

    if(h_stride == 1 && w_stride == 1)
    {
        assert(h_out == h_in && w_out == w_in);

        std::string kernel_name = "transpose_CNHW2NCHW_opt";

        std::string network_config = std::to_string(n) + std::to_string(c) + std::to_string(h_out) +
                                     std::to_string(w_out) + std::to_string(in_offset) +
                                     std::to_string(out_offset);

        auto&& kernels = handle.GetKernels(kernel_name, network_config);

        if(!kernels.empty())
        {
            auto kernel = kernels.front();
            kernel(in, out);
        }
        else
        {
            int RD_BLCK      = ((h_out * w_out) % 4 == 0) ? 4 : ((h_out * w_out) % 2 == 0) ? 2 : 1;
            int HW_RD        = (h_out * w_out) / RD_BLCK;
            size_t MAP_RD    = HW_RD * c;
            size_t lcl_size0 = WG_SIZE; //((MAP_RD + 63)/64 < 4) ? ((MAP_RD + 63)/64)*64 : 256;

            std::string READ_TYPE = (RD_BLCK == 1) ? "float" : "float" + std::to_string(RD_BLCK);

            std::string params;
            params += " -DNC_TRANS_CNHW_OPT";
            params += " -DIN_OFF=" + std::to_string(in_offset);
            params += " -DOUT_OFF=" + std::to_string(out_offset);
            params += " -DH=" + std::to_string(h_out);
            params += " -DW=" + std::to_string(w_out);
            params += " -DN=" + std::to_string(n);
            params += " -DC=" + std::to_string(c);
            params += " -DRD_BLCK=" + std::to_string(RD_BLCK);
            params += " -DHW_RD=" + std::to_string(HW_RD);
            params += " -DMAP_RD=" + std::to_string(MAP_RD);
            params += " -DREAD_TYPE=" + READ_TYPE;

            const std::vector<size_t> vld{lcl_size0, 1, 1};
            std::vector<size_t> vgd{MAP_RD, 1, 1};

            if(MAP_RD < MAX_ACTIVE_THREADS)
            {
                vgd = {MAP_RD, static_cast<size_t>(n), 1};
                params += " -D_2D_WG";
            }

            handle.AddKernel(
                kernel_name, network_config, program_name, kernel_name, vld, vgd, params)(in, out);
        }
    }
    else
    {
        assert(h_in > h_out && w_in > w_out);

        std::string kernel_name = "transpose_CNHW2NCHW";

        std::string network_config =
            std::to_string(n) + std::to_string(c) + std::to_string(h_in) + std::to_string(h_out) +
            std::to_string(w_in) + std::to_string(w_out) + std::to_string(h_stride) +
            std::to_string(w_stride) + std::to_string(in_offset) + std::to_string(out_offset);

        auto&& kernels = handle.GetKernels(kernel_name, network_config);

        if(!kernels.empty())
        {
            auto kernel = kernels.front();
            kernel(in, out);
        }
        else
        {
            std::string params;
            params += " -DNC_TRANS_CNHW";
            params += " -DN=" + std::to_string(n);
            params += " -DC=" + std::to_string(c);
            params += " -DHW_IN=" + std::to_string(h_in * w_in);
            params += " -DHW_OUT=" + std::to_string(h_out * w_out);
            params += " -DW_IN=" + std::to_string(w_in);
            params += " -DW_OUT=" + std::to_string(w_out);
            params += " -DH_STRIDE=" + std::to_string(h_stride);
            params += " -DW_STRIDE=" + std::to_string(w_stride);
            params += " -DIN_OFF=" + std::to_string(in_offset);
            params += " -DOUT_OFF=" + std::to_string(out_offset);

            size_t ld0 = WG_SIZE;
            size_t gd0 = c * h_out * w_out;
            const std::vector<size_t> vld{ld0, 1, 1};
            std::vector<size_t> vgd{gd0, 1, 1};

            if(gd0 < MAX_ACTIVE_THREADS)
            {
                vgd = {gd0, static_cast<size_t>(n), 1};
                params += " -D_2D_WG";
            }

            handle.AddKernel(
                kernel_name, network_config, program_name, kernel_name, vld, vgd, params)(in, out);
        }
    }

#ifdef MIOPEN_TRANS_DEBUG
    float nMB = (float)n * c * (h_out * w_out + h_in * w_in) * sizeof(float) * 1e-6;
    fprintf(stderr,
            "CNHW->NCHW MB: %f time: %f GB/s: %f\n",
            nMB,
            handle.GetKernelTime(),
            nMB / handle.GetKernelTime());
#endif

    return handle.GetKernelTime();
}

} // namespace miopen
