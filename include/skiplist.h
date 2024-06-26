class Skiplist {
private:
    struct Node {
        std::vector<std::pair<Node*, Node*>> column;
        int key;
        int count;
    };

    // sentinel columns
    Node left;
    Node right;

    // find first item that is greater or equal to num
    Node * find(int num) {
        int l = right.column.size() - 1;
        Node * n = &left;
        while (n->key < num) {
            while (l && n->column[l].second->key > num)
                l--;
            n = n->column[l].second;
        }
        return n;
    }

    void erase_column(Node * n) {
        for (int i = 0 ; i != n->column.size() ; ++i) {
            auto * ln = n->column[i].first;
            auto * rn = n->column[i].second;
            ln->column[i].second = rn;
            rn->column[i].first = ln;
        }
        delete n;
    }
public:

    Skiplist() {
        left.key = INT_MIN;
        left.count = 0;
        left.column.push_back(std::make_pair<Node*, Node*>(nullptr, &right));
        right.key = INT_MAX;
        right.count = 0;
        right.column.push_back(std::make_pair<Node*, Node*>(&left, nullptr));
    }

    bool search(int target) {
        auto n = find(target);
        return (n->key == target && n->count);
    }

    void add(int num) {
        auto n = find(num);
        if (n->key == num) {
            n->count ++;
            return;
        }
        // create new node with frequency of 1
        auto nn = new Node(std::vector<std::pair<Node*,Node*>>(1,std::make_pair(n->column[0].first, n)),
                            num, 1);

        // attach new node to predecessor and successor    
        n->column[0].first->column[0].second = nn;
        n->column[0].first = nn;

        // grow column randomly
        while (rand() < RAND_MAX / 2) {
            if (nn->column.size() ==  left.column.size()) {
                left.column.push_back(left.column.back());
                left.column.back().second = nn;
                right.column.push_back(right.column.back());
                right.column.back().first = nn;
            
                nn->column.push_back(std::make_pair(&left, &right));
            } else {
                assert (nn->column.size() <  left.column.size());
                Node * nl = nn->column.back().first;
                Node * nr = nn->column.back().second;
                // find first taller column on the left
                while (nl->column.size() <= nn->column.size()) {
                    assert(nl->column.size() == nn->column.size());
                    nl = nl->column.back().first;
                }
                // find first taller column on the right
                while (nr->column.size() <= nn->column.size()) {
                    assert(nr->column.size() == nn->column.size());
                    nr = nr->column.back().second;
                }
                nr->column[nn->column.size()].first = nn;
                nl->column[nn->column.size()].second = nn;

                nn->column.push_back(std::make_pair(nl, nr));
            }
        }
    }

    bool erase(int num) {
        auto n = find(num);
        if (n->key == num && n->count) {
            n->count --;
            // consider real deletion
            if (!n->count)
                erase_column(n);
            return true;
        } else {
            return false;
        }
    }
};
