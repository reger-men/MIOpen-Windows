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

#include <miopen/db_path.hpp>
#include <miopen/env.hpp>
#include <miopen/stringutils.hpp>

#include <cstdlib>

MIOPEN_DECLARE_ENV_VAR(MIOPEN_DB_PATH)
MIOPEN_DECLARE_ENV_VAR(MIOPEN_USER_DB_PATH)
MIOPEN_DECLARE_ENV_VAR(MIOPEN_FIND_DB_PATH)

namespace miopen {

std::string GetDbPath()
{
    auto p = GetStringEnv(MIOPEN_DB_PATH{});
    if(p == nullptr)
        return "/opt/rocm/x86_64-w64-mingw32/miopen/miopen/db";
    else
        return p;
}

namespace {
std::string PrepareUserDbPath()
{
    auto p = GetStringEnv(MIOPEN_USER_DB_PATH{});
    if(p == nullptr)
        p = "~/.config/miopen/";

    const char* home_dir = GetStringEnv(HOME{});
    if(home_dir == nullptr)
    {
        // todo:
        // need to figure out what is the correct thing to do here
        // in tensoflow unit tests run via bazel, $HOME is not set, so this can happen
        // setting home_dir to the /tmp for now
        home_dir = "/tmp";
    }

    return ReplaceString(p, "~", home_dir);
}

std::string PrepareFindDbPath()
{
    auto p = GetStringEnv(MIOPEN_FIND_DB_PATH{});
    if(p == nullptr)
        p = "~/.config/miopen/";

    return ReplaceString(p, "~", GetStringEnv(HOME{}));
}
} // namespace

const std::string& GetUserDbPath()
{
    static const auto instance = PrepareUserDbPath();
    return instance;
}

const std::string& GetFindDbPath()
{
    static const auto instance = PrepareFindDbPath();
    return instance;
}

} // namespace miopen
