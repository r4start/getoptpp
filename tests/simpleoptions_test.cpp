/*
    Copyright (C) 2011  Hugo Arregui, FuDePAN

    This file is part of GetOpt_pp.

    GetOpt_pp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GetOpt_pp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <string>
#include <vector>
#include <iostream>
#include <mili/mili.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "getoptpp/getopt_pp.h"

using namespace GetOpt;
using namespace std;
using namespace mili;

TEST(GetOptPPTest, just_long_option)
{
    const char* argv[] = {"test", "--name", "Hugo"};
    GetOpt_pp ops(3, argv);
    string name;
    ops >> Option("name", name);
    ASSERT_EQ("Hugo", name);
}

TEST(GetOptPPTest, just_long_option_default)
{
    const char* argv[] = {"test"};
    GetOpt_pp ops(1, argv);
    string name;
    ops >> Option("name", name, "world");
    ASSERT_EQ("world", name);
}

TEST(GetOptPPTest, both_options_long)
{
    const char* argv[] = {"test", "--name", "Hugo"};
    GetOpt_pp ops(3, argv);
    string name;
    ops >> Option('n', "name", name);
    ASSERT_EQ("Hugo", name);
}

TEST(GetOptPPTest, both_options_short)
{
    const char* argv[] = {"test", "-n", "Hugo"};
    GetOpt_pp ops(3, argv);
    string name;
    ops >> Option('n', "name", name);
    ASSERT_EQ("Hugo", name);
}

TEST(GetOptPPTest, option_not_found)
{
    const char* argv[] = {"test"};
    GetOpt_pp ops(1, argv);
    ops.exceptions(ios::eofbit);
    string name;

    ASSERT_THROW(ops >> Option('n', "name", name), OptionNotFoundEx);
}

TEST(GetOptPPTest, no_manipulators)
{
    const char* argv[] = {"test", "-n", "Hugo"};
    GetOpt_pp ops(3, argv);
    string name;

    ASSERT_EQ("Hugo", ops.getopt<std::string>('n', "name"));
}

TEST(GetOptPPTest, no_manipulators_option_not_found)
{
    const char* argv[] = {"test"};
    GetOpt_pp ops(1, argv);
    ops.exceptions(ios::eofbit);

    ASSERT_THROW(ops.getopt<std::string>('n', "name"), OptionNotFoundEx);
}


TEST(GetOptPPTest, global_options)
{
    const char* argv[] = {"test", "arg1", "arg2"};

    GetOpt_pp ops(3, argv);

    std::vector<std::string> args;
    ops >> GlobalOption(args);

    ASSERT_EQ("test", ops.app_name());

    for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
    {
        const unsigned int index = it - args.begin() + 1;
        ASSERT_EQ(argv[index], *it);
    }

}
