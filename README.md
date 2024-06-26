# data_structures
Test implementations of certain data structures I'm finding useful

Data structure implementations are in:
* `include`

Other directories are tests, as follows
* `unit_test` - unit tests for data structures specifically
* `leetcode_test` - certain solutions for LeetCode problems using data structures outlined (replicating behavior of LeetCode test runner)

To run and test:

```
export CXX=/opt/homebrew/opt/llvm/bin/clang++
cmake -B build
cmake --build build -j
ctest --test-dir build/
```