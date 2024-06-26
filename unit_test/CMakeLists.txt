include_directories(../include/pitch)

add_executable(skiplist_test skiplist_test.cpp)
target_compile_options(skiplist_test PRIVATE -g )
target_link_libraries(skiplist_test GTest::gtest_main)
gtest_discover_tests(skiplist_test)
