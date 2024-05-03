#ifndef _ASP_DETAILS_TRIE_TREE_HPP_
#define _ASP_DETAILS_TRIE_TREE_HPP_

#include <unordered_map>

namespace asp {
namespace __details__ {

struct trie_tree_node {
    typedef trie_tree_node self;
    trie_tree_node(char _c, bool _eow = false);
    ~trie_tree_node();
    bool contains(char _c) const;
    void add(char _c);
    bool del(char _c);
    const char _c;
    bool _end_of_word = false;
    std::unordered_map<char, self*> _children;
};

}
}

#endif // _ASP_DETAILS_TRIE_TREE_HPP_