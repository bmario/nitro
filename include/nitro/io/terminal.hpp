/*
 * Copyright (c) 2015-2021, Technische Universitšt Dresden, Germany
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to
 *    endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace nitro
{
namespace io
{
    namespace terminal
    {

        inline std::ostream& format_padded(std::ostream& s, const std::string& in, int left_pad = 0,
                                           int max_width = 80)
        {
            int space = 0;
            auto initial_indent = s.tellp();

            if (initial_indent <= left_pad)
            {
                s << std::setw(left_pad - initial_indent);
                space = max_width - left_pad;
            }

            for (auto word : nitro::lang::split(in, " "))
            {
                nitro::lang::replace_all(word, "\t", " ");

                if (word.size() + 1 > static_cast<std::size_t>(max_width - left_pad) ||
                    static_cast<int>(word.size() + 1) <= space)
                {
                    s << ' ' << word;
                }
                else
                {
                    s << std::endl << std::setw(left_pad) << ' ' << word;
                    space = max_width - left_pad;
                }

                space -= static_cast<int>(word.size()) + 1;
            }

            s << std::setw(0);

            return s;
        }
    } // namespace terminal
} // namespace io
} // namespace nitro
