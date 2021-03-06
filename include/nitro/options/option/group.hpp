/*
 * Copyright (c) 2015-2020, Technische Universität Dresden, Germany
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

#include <nitro/options/fwd.hpp>

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace nitro
{
namespace options
{
    class group
    {
    public:
        group(const options::parser& parser, const std::string& name,
              const std::string& description = std::string(""));

        group(group&&) = default;

        group(const group&) = delete;
        group& operator=(const group&) = delete;

        auto option(const std::string& name, const std::string& description = std::string(""))
            -> options::option&;
        auto multi_option(const std::string& name, const std::string& description = std::string(""))
            -> options::multi_option&;
        auto toggle(const std::string& name, const std::string& description = std::string(""))
            -> options::toggle&;

        const std::map<std::string, options::option>& get_options() const;
        const std::map<std::string, options::multi_option>& get_multi_options() const;
        const std::map<std::string, options::toggle>& get_toggles() const;

        const std::string& name() const;
        const std::string& description() const;

        bool empty() const;

        void usage(std::ostream& s) const;

    private:
        const parser& parser_;
        std::string name_;
        std::string description_;

        std::map<std::string, options::option> options_;
        std::map<std::string, options::multi_option> multi_options_;
        std::map<std::string, options::toggle> toggles_;
        std::vector<options::base*> order_;
    };
} // namespace options
} // namespace nitro
