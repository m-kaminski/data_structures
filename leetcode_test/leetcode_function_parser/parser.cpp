#include <fstream>
#include <iostream>
#include <any>
#include <cassert>
#include <sstream>
#include <functional>

#include "parser.h"

/*
Example invocation:
./build/leetcode_test/leetcode_function_parser/parser \
./leetcode_test/handling-sum-queries-after-update/test_data/1/calls.txt \
./leetcode_test/handling-sum-queries-after-update/test_data/1/args.txt \
./leetcode_test/handling-sum-queries-after-update/test_data/1/res.txt

./build/leetcode_test/leetcode_function_parser/parser ./leetcode_test/handling-sum-queries-after-update/test_data/1/calls.txt ./leetcode_test/handling-sum-queries-after-update/test_data/1/args.txt ./leetcode_test/handling-sum-queries-after-update/test_data/1/res.txt

./build/leetcode_test/leetcode_function_parser/parser ./leetcode_test/handling-sum-queries-after-update/test_data/8/calls.txt ./leetcode_test/handling-sum-queries-after-update/test_data/8/args.txt ./leetcode_test/handling-sum-queries-after-update/test_data/8/res.txt

*/



std::vector<std::string> read_calls(const std::string &path)
{
    std::vector<std::any> table = lc_util::read_any_vector(path);
    std::vector<std::string> result;
    std::transform(table.begin(), table.end(), back_inserter(result), [](auto &v)
                   { return any_cast<std::string>(v); });
    return result;
}
int main(int argc, const char **argv)
{
    if (argc < 4)
    {
        std::cerr << "3 arguments needed: set of functions, set of arguments and set of expected outcomes" << std::endl;
        return -1;
    }
    
    auto calls = read_calls(argv[1]);

    for (auto &c : calls)
    {
        std::cout << c << std::endl;
    }
    

    auto args = lc_util::read_any_vector(argv[2]);
    std::cout << "V2" << std::endl;
    lc_util::print_any_vector(args, std::cout);
    std::cout << "\nV1" << std::endl;
    lc_util::print_any_vector(lc_util::read_any_vector(argv[1]), std::cout);
    std::cout << std::endl;

    return 0;
}
