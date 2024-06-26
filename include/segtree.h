#include <functional>
#include <climits>
// Generic implementation of a segment tree.
//
//
// Example configurations:
// Default: calculate sum of items at indices
//    useful for: https://leetcode.com/problems/range-sum-query-mutable
// SegTree<int, std_max, INT_MIN> : Calculate maximum of values
//    useful for: https://leetcode.com/problems/block-placement-queries
// Note: Binary Op needs to be wrapped in a function object, i.e.
//     struct std_max {
//        const int operator()(int a, int b) const { return max(a, b); }
//    };
// Identity element needs to be provided with operation - an element such that
// op(X, IdentityElement) == X for any value of X;
//
#define SEGTREE_ASSERTS
template <typename CounterT, typename BinaryOp = std::plus<CounterT>,
          CounterT IdentityElement = 0>
class SegTree
{

public:
    SegTree(size_t stsz = 0)
    {
#ifdef SEGTREE_ASSERTS
        assert(op(1, IdentityElement) == 1);
        assert(op(0, IdentityElement) == 0);
        assert(op(INT_MIN, IdentityElement) == INT_MIN);
        assert(op(INT_MAX, IdentityElement) == INT_MAX);
#endif
        prepare_st(stsz);
    }

    // change size (note: tree is wiped. no recalculation is performed)
    void set_size(size_t stsz) { prepare_st(stsz); }

    // Update & recalculate the segment tree (O(lgn))
    void set(size_t idx, CounterT val)
    {
#ifdef SEGTREE_ASSERTS
        assert(idx < t[0].size());
        assert(op(val, IdentityElement) == val);
#endif
        t[0][idx] = val;
        // change for all the levels
        int level = 0;
        while (level < t.size() - 1)
        {
            idx /= 2;
            int didx = idx * 2;
            t[++level][idx] = op(t[level][didx], t[level][didx + 1]);
        }
    }

    // calculate sum (or any other op) for range b..e inclusive (e is not "after-end")
    CounterT query(size_t b, size_t e)
    {
        return query_sum(b, e, t.size() - 1, 0);
    }

private:
    BinaryOp op;
    // i.e.
    // 0100000010001000
    // 1 0 0 0 1 0 1 0
    // 1.  0.  1.  1
    // 1.      2
    // 3
    //
    vector<vector<CounterT>> t;

    void prepare_st(int l)
    {
        while (l)
        {
            t.emplace_back(l + 1, IdentityElement);
            if (l > 1)
                l = (l + 1) / 2;
            else
                break;
        };
    }

    // try to answer sum range based on level and index of a node per given
    // level
    CounterT query_sum(int b, int e, int level, int n)
    {
#ifdef SEGTREE_ASSERTS
        assert(n >= 0);
        assert(level < t.size());
        assert(level >= 0);
        assert(b <= e);
#endif
        // left and right edge of node denoted by n at level;
        size_t left_bound = n * (1 << level);
        size_t right_bound = left_bound + (1 << level) - 1;
        if (right_bound < b || left_bound > e)
        {
            return 0; // disjoint ranges
        }
        else if (right_bound <= e && left_bound >= b)
        {
            return t[level][n];
        }
        else
        {
            return op(query_sum(b, e, level - 1, n * 2),
                      query_sum(b, e, level - 1, n * 2 + 1));
        }
    }
};
