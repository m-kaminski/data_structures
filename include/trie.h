class Trie {
    struct trie_node {
        trie_node() {
            fill(children.begin(), children.end(), nullptr);
        }
        array<trie_node *, 27> children;
    };
    trie_node root; 
public:
    Trie() {
        
    }
    
    void insert(string word) {
        trie_node * n = &root;
        for (char c : word) {
            if (!n->children[c-'a']) {
                n->children[c-'a'] = new trie_node;
            }
            n = n->children[c-'a'];
        }
        n->children[26] = new trie_node;
    }
    
    bool search(string word) {

        trie_node * n = &root;
        for (char c : word) {
            if (!n->children[c-'a']) {
                return false;
            }
            n = n->children[c-'a'];
        }        
        return n->children[26] != nullptr;
    }
    
    bool startsWith(string prefix) {
        trie_node * n = &root;
        for (char c : prefix) {
            if (!n->children[c-'a']) {
                return false;
            }
            n = n->children[c-'a'];
        }        
        return true;        
    }
};
