#include "gtest/gtest.h"
#include "skiplist.h"
namespace {
class shm_helpers_test : public ::testing::Test {};




TEST_F(shm_helpers_test, move_data_through_ring_buffer) {
    auto sl = new Skiplist;
    sl->add(1);
    sl->add(2);
    sl->add(3);
    ASSERT_FALSE(sl->search(0));
    sl->add(4);
    ASSERT_TRUE(sl->search(1));
    ASSERT_FALSE(sl->erase(0)); // no '0' so can't remove
    ASSERT_TRUE(sl->erase(1)); // there is '1', so return true
    ASSERT_FALSE(sl->search(1));
}


}  // namespace