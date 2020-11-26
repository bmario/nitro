/*
 * Copyright (c) 2015-2019, Technische Universität Dresden, Germany
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

#ifndef INCLUDE_NITRO_BROKEN_OPTIONS_PARSER_HPP
#define INCLUDE_NITRO_BROKEN_OPTIONS_PARSER_HPP

#include <nitro/broken_options/argument.hpp>
#include <nitro/broken_options/exception.hpp>
#include <nitro/broken_options/option/group.hpp>
#include <nitro/broken_options/option/multi_option.hpp>
#include <nitro/broken_options/option/option.hpp>
#include <nitro/broken_options/option/toggle.hpp>
#include <nitro/broken_options/options.hpp>

#include <nitro/except/raise.hpp>

#include <deque>
#include <iostream>
#include <map>
#include <string>

namespace nitro
{
namespace broken_options
{

    class parser
    {
    public:
        parser(const std::string& app_name = std::string("main"),
               const std::string& about = std::string(""))
        : app_name_(app_name), about_(about),
          groups_({ nitro::broken_options::group(all_argument_names_, 0, "arguments") }),
          default_group_(groups_.front())
        {
        }

        auto parse(int argc, const char* const argv[]) -> options;

    public:
        nitro::broken_options::group& group(const std::string& name,
                                            const std::string& description = std::string(""));
        nitro::broken_options::group&
        default_group(const std::string& name = std::string(""),
                      const std::string& description = std::string(""));

        auto option(const std::string& name, const std::string& description = std::string(""))
            -> broken_options::option&;
        auto multi_option(const std::string& name, const std::string& description = std::string(""))
            -> broken_options::multi_option&;
        auto toggle(const std::string& name, const std::string& description = std::string(""))
            -> broken_options::toggle&;

        void accept_positionals(std::size_t amount = std::numeric_limits<std::size_t>::max());
        void positional_name(const std::string& name);

    public:
        std::ostream& usage(std::ostream& s = std::cout, bool print_default_group = true);

    private:
        void check_consistency();

        std::map<std::string, nitro::broken_options::option&> get_all_options();
        std::map<std::string, nitro::broken_options::multi_option&> get_all_multi_options();
        std::map<std::string, nitro::broken_options::toggle&> get_all_toggles();

        template <typename Iter>
        bool parse_options(Iter& it, Iter end);

        template <typename Iter>
        bool parse_multi_options(Iter& it, Iter end);

        template <typename Iter>
        bool parse_toggles(Iter& it, Iter end);

        void prepare();
        void validate();

        template <typename F>
        void for_each_option(F f);

    private:
        std::string app_name_;
        std::string about_;

        std::set<std::string> all_argument_names_;
        std::deque<nitro::broken_options::group> groups_;

        nitro::broken_options::group& default_group_;

        std::size_t allowed_positionals_ = 0;
        std::string positional_name_ = "args";
    };
} // namespace broken_options
} // namespace nitro

#include <nitro/broken_options/parser.ipp>

#endif // INCLUDE_NITRO_BROKEN_OPTIONS_PARSER_HPP
