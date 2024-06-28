#ifndef _ICY_DETAILS_TRIE_TREE_HPP_
#define _ICY_DETAILS_TRIE_TREE_HPP_

#include <unordered_map>

namespace icy {
namespace __details__ {

struct trie_tree_node {
    typedef trie_tree_node self;
    trie_tree_node(char _c, bool _eow = false);
    ~trie_tree_node();
    bool contains(char _c) const;
    void add(char _c);
    bool del(char _c);
    const char _c;
    // bool _end_of_word = false;
    size_t _word_frequency = 0;
    std::unordered_map<char, self*> _children;
};

}
}

#endif // _ICY_DETAILS_TRIE_TREE_HPP_