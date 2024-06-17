// segment tree
template <typename CounterT, typename BinaryOp = std::plus<CounterT>,
	  CounterT IdentityElement = 0>
class SegTree {

public:
    SegTree(size_t stsz = 0) {
	static_assert(BinaryOp()(1, IdentityElement) == 1);
	static_assert(BinaryOp()(0, IdentityElement) == 0);
	static_assert(BinaryOp()(INT_MIN, IdentityElement) == INT_MIN);
	static_assert(BinaryOp()(INT_MAX, IdentityElement) == INT_MAX);
	prepare_st(stsz);
    }

    void set_size(size_t stsz) {
	prepare_st(stsz);
    }

    void set(size_t idx, CounterT val) {
	assert(idx <= t[0].size());
	t[0][idx] = val;
	assert(op(val, IdentityElement) == val);
	// change for all the levels
	int level = 0;
	while (level < t.size() - 1) {
	    level++;
	    idx /= 2;
	    t[level][idx] =
		op(t[level - 1][2 * idx], t[level - 1][2 * idx + 1]);
	}
    }

    CounterT query(size_t b, size_t e) {
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

    void prepare_st(int l) {
	while (l) {
	    t.emplace_back(l + 1, IdentityElement);
	    if (l > 1)
		l = (l + 1) / 2;
	    else
		break;
	};
    }


    // try to answer sum range based on level and index of a node per given
    // level
    CounterT query_sum(int b, int e, int level, int n) {
	assert(n >= 0);
	assert(level < t.size());
	assert(level >= 0);
	assert(b <= e);
	// left and right edge of node denoted by n at level;
	size_t left_bound = n * (1 << level);
	size_t right_bound = left_bound + (1 << level) - 1;
	if (right_bound < b || left_bound > e) {
	    return 0; // disjoint ranges
	} else if (right_bound <= e && left_bound >= b) {
	    assert(n < t[level].size());
	    return t[level][n];
	} else {
	    return op(query_sum(b, e, level - 1, n * 2),
		      query_sum(b, e, level - 1, n * 2 + 1));
	}
    }
};
