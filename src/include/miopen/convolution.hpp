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
#ifndef GUARD_MIOPEN_CONVOLUTION_HPP_
#define GUARD_MIOPEN_CONVOLUTION_HPP_

#include <functional>
#include <miopen/common.hpp>
#include <miopen/conv_algo_name.hpp>
#include <miopen/handle.hpp>
#include <miopen/miopen.h>
#include <miopen/perf_field.hpp>
#include <miopen/tensor.hpp>
#include <miopen/solver.hpp>

namespace miopen {

using WinogradKernelParams = std::tuple<int /*N*/,
                                        int /*C*/,
                                        int /*H*/,
                                        int /*W*/,
                                        int /*K*/,
                                        int /*n_groups*/,
                                        int /*out_H*/,
                                        int /*out_W*/,
                                        int /*R*/,
                                        int /*S*/,
                                        int /*pad_H*/,
                                        int /*pad_W*/,
                                        bool /*isRxS*/>;

using ExtraKernelArgs = std::tuple<int /*N*/,
                                   int /*C*/,
                                   int /*H*/,
                                   int /*W*/,
                                   int /*K*/,
                                   int /*n_groups*/,
                                   int /*out_H*/,
                                   int /*out_W*/>;

struct ConvolutionDescriptor : miopenConvolutionDescriptor
{

    ConvolutionDescriptor(int p_pad_h      = 0,
                          int p_pad_w      = 0,
                          int p_u          = 1,
                          int p_v          = 1,
                          int p_dilation_h = 1,
                          int p_dilation_w = 1);
    ConvolutionDescriptor(miopenConvolutionMode_t c_mode,
                          miopenPaddingMode_t p_mode,
                          int p_pad_h      = 0,
                          int p_pad_w      = 0,
                          int p_u          = 1,
                          int p_v          = 1,
                          int p_dilation_h = 1,
                          int p_dilation_w = 1);

    std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>
    GetForwardOutputDim(const TensorDescriptor& inputTensorDesc,
                        const TensorDescriptor& filterDesc) const;
    TensorDescriptor GetForwardOutputTensor(const TensorDescriptor& inputTensorDesc,
                                            const TensorDescriptor& filterDesc) const;

    std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>
    GetBackwardsWeightsDim(const TensorDescriptor& inputTensorDesc,
                           const TensorDescriptor& outputTensorDesc) const;
    TensorDescriptor GetBackwardWeightsTensor(const TensorDescriptor& inputTensorDesc,
                                              const TensorDescriptor& outputTensorDesc) const;

    std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>
    GetBackwardOutputDim(const TensorDescriptor& outputTensorDesc,
                         const TensorDescriptor& filterDesc) const;
    TensorDescriptor GetBackwardOutputTensor(const TensorDescriptor& outputTensorDesc,
                                             const TensorDescriptor& filterDesc) const;

    size_t ForwardGetWorkSpaceSizeGEMM(Handle& handle,
                                       const TensorDescriptor& wDesc,
                                       const TensorDescriptor& yDesc) const;

    size_t ForwardGetWorkSpaceSizeGEMMTranspose(const TensorDescriptor& xDesc,
                                                const TensorDescriptor& yDesc) const;

    size_t ForwardGetWorkSpaceSizeGEMMStridedBatched(Handle& handle,
                                                     const TensorDescriptor& xDesc,
                                                     const TensorDescriptor& wDesc,
                                                     const TensorDescriptor& yDesc) const;

    size_t
    ForwardBackwardDataGetWorkSpaceSizeDirect(Handle& handle,
                                              const TensorDescriptor& xDesc,
                                              const TensorDescriptor& yDesc,
                                              const TensorDescriptor& wDesc,
                                              int direction) const; // 1: Forward, 0: BackwardData

    size_t ForwardGetWorkSpaceSizeFFT(const TensorDescriptor& wDesc,
                                      const TensorDescriptor& xDesc,
                                      const TensorDescriptor& yDesc) const;

    bool IsWinograd3x3Supported(Handle& handle,
                                bool direction,
                                const TensorDescriptor& wDesc,
                                const TensorDescriptor& xDesc) const;

    bool IsBwdWeightsDirectSupported(const TensorDescriptor& wDesc) const;

    bool IsDirectSupported(const TensorDescriptor& wDesc) const;

    size_t ForwardGetWorkSpaceSize(Handle& handle,
                                   const TensorDescriptor& wDesc,
                                   const TensorDescriptor& xDesc,
                                   const TensorDescriptor& yDesc) const;

    void FindConvFwdAlgorithm(Handle& handle,
                              const TensorDescriptor& xDesc,
                              ConstData_t x,
                              const TensorDescriptor& wDesc,
                              ConstData_t w,
                              const TensorDescriptor& yDesc,
                              ConstData_t y,
                              int requestAlgoCount,
                              int* returnedAlgoCount,
                              miopenConvAlgoPerf_t* perfResults,
                              Data_t workSpace,
                              size_t workSpaceSize,
                              bool exhaustiveSearch) const;

    int FindWinogradKernel(Handle& handle,
                           const TensorDescriptor& xDesc,
                           const TensorDescriptor& wDesc,
                           const TensorDescriptor& yDesc,
                           WinogradKernelParams& k_p,
                           KernelInvoke& kernel,
                           std::string& solver_id,
                           int direction,
                           std::string* kcache_key = nullptr) const;

    int FindFwdFFTKernel(Handle& handle,
                         const TensorDescriptor& xDesc,
                         const TensorDescriptor& wDesc,
                         const TensorDescriptor& yDesc,
                         size_t workSpaceSize,
                         std::vector<KernelInvoke>& kernels,
                         std::string& kcache_key) const;

    float ExecuteFwdFFTKernel(Handle& handle,
                              const TensorDescriptor& xDesc,
                              ConstData_t x,
                              const TensorDescriptor& wDesc,
                              ConstData_t w,
                              const TensorDescriptor& yDesc,
                              Data_t y,
                              Data_t workSpace,
                              size_t workSpaceSize,
                              bool timed = false) const;

    int FindBwdFFTKernel(Handle& handle,
                         const TensorDescriptor& dyDesc,
                         const TensorDescriptor& wDesc,
                         const TensorDescriptor& dxDesc,
                         size_t workSpaceSize,
                         std::vector<KernelInvoke>& kernels) const;

    float ExecuteBwdFFTKernel(Handle& handle,
                              const TensorDescriptor& dyDesc,
                              ConstData_t dy,
                              const TensorDescriptor& wDesc,
                              ConstData_t w,
                              const TensorDescriptor& dxDesc,
                              Data_t dx,
                              Data_t workSpace,
                              size_t workSpaceSize,
                              bool timed = false) const;

    std::vector<miopen::solver::ConvSolution>
    FindDataDirectSolutions(Handle& handle,
                            const TensorDescriptor& xDesc,
                            const TensorDescriptor& wDesc,
                            const TensorDescriptor& yDesc,
                            bool exhaustiveSearch,
                            bool isForward,
                            std::string& network_config,
                            ExtraKernelArgs& extraArgs) const;

    void ConvolutionForward(Handle& handle,
                            const void* alpha,
                            const TensorDescriptor& xDesc,
                            ConstData_t x,
                            const TensorDescriptor& wDesc,
                            ConstData_t w,
                            miopenConvFwdAlgorithm_t algo,
                            const void* beta,
                            const TensorDescriptor& yDesc,
                            Data_t y,
                            Data_t workSpace,
                            size_t workSpaceSize) const;

    size_t BackwardDataGetWorkSpaceSizeGEMM(Handle& handle,
                                            const TensorDescriptor& wDesc,
                                            const TensorDescriptor& dyDesc) const;

    size_t BackwardDataGetWorkSpaceSizeGEMMTranspose(const TensorDescriptor& dyDesc,
                                                     const TensorDescriptor& dxDesc) const;

    size_t BackwardGetWorkSpaceSizeFFT(const TensorDescriptor& wDesc,
                                       const TensorDescriptor& dyDesc,
                                       const TensorDescriptor& dxDesc) const;

    size_t BackwardDataGetWorkSpaceSize(Handle& handle,
                                        const TensorDescriptor& wDesc,
                                        const TensorDescriptor& dyDesc,
                                        const TensorDescriptor& dxDesc) const;

    void FindConvBwdDataAlgorithm(Handle& handle,
                                  const TensorDescriptor& dyDesc,
                                  ConstData_t dy,
                                  const TensorDescriptor& wDesc,
                                  ConstData_t w,
                                  const TensorDescriptor& dxDesc,
                                  ConstData_t dx,
                                  int requestAlgoCount,
                                  int* returnedAlgoCount,
                                  miopenConvAlgoPerf_t* perfResults,
                                  Data_t workSpace,
                                  size_t workSpaceSize,
                                  bool exhaustiveSearch) const;

    void ConvolutionBackwardData(Handle& handle,
                                 const void* alpha,
                                 const TensorDescriptor& dyDesc,
                                 ConstData_t dy,
                                 const TensorDescriptor& wDesc,
                                 ConstData_t w,
                                 miopenConvBwdDataAlgorithm_t algo,
                                 const void* beta,
                                 const TensorDescriptor& dxDesc,
                                 Data_t dx,
                                 Data_t workSpace,
                                 size_t workSpaceSize) const;

    size_t ConvolutionBackwardWeightsGetWorkSpaceSize(Handle& handle,
                                                      const TensorDescriptor& dyDesc,
                                                      const TensorDescriptor& xDesc,
                                                      const TensorDescriptor& dwDesc) const;

    size_t BackwardWeightsGetWorkSpaceSizeGEMM(Handle& handle,
                                               const TensorDescriptor& dyDesc,
                                               const TensorDescriptor& dwDesc) const;

    size_t BackwardWeightsGetWorkSpaceSizeDirect(Handle& handle,
                                                 const TensorDescriptor& dyDesc,
                                                 const TensorDescriptor& xDesc,
                                                 const TensorDescriptor& dwDesc) const;

    void FindConvBwdWeightsAlgorithm(Handle& handle,
                                     const TensorDescriptor& dyDesc,
                                     ConstData_t dy,
                                     const TensorDescriptor& xDesc,
                                     ConstData_t x,
                                     const TensorDescriptor& dwDesc,
                                     ConstData_t dw,
                                     int requestAlgoCount,
                                     int* returnedAlgoCount,
                                     miopenConvAlgoPerf_t* perfResults,
                                     Data_t workSpace,
                                     size_t workSpaceSize,
                                     bool exhaustiveSearch) const;

    void ConvolutionBackwardWeights(Handle& handle,
                                    const void* alpha,
                                    const TensorDescriptor& dyDesc,
                                    ConstData_t dy,
                                    const TensorDescriptor& xDesc,
                                    ConstData_t x,
                                    miopenConvBwdWeightsAlgorithm_t algo,
                                    const void* beta,
                                    const TensorDescriptor& dwDesc,
                                    Data_t dw,
                                    Data_t workSpace,
                                    size_t workSpaceSize) const;

    miopenConvolutionMode_t mode;
    miopenPaddingMode_t paddingMode;
    int pad_h;
    int pad_w;
    int u;
    int v;
    int dilation_h;
    int dilation_w;
    int group_count;
};

void ConvolutionBackwardBias(Handle& handle,
                             const void* alpha,
                             const TensorDescriptor& dyDesc,
                             ConstData_t dy,
                             const void* beta,
                             const TensorDescriptor& dbDesc,
                             Data_t db);

std::ostream& operator<<(std::ostream& stream, const ConvolutionDescriptor& c);

} // namespace miopen
MIOPEN_DEFINE_OBJECT(miopenConvolutionDescriptor, miopen::ConvolutionDescriptor);

#endif // GUARD_MIOPEN_CONVOLUTION_HPP_
