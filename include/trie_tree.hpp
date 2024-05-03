#ifndef _ASP_TRIE_TREE_HPP_
#define _ASP_TRIE_TREE_HPP_

#include <string>
#include <vector>
#include <unordered_map>

#include "details/trie_tree_node.hpp"

namespace asp {
class trie_tree;

class trie_tree {
    typedef __details__::trie_tree_node node_type;
public:
    trie_tree() : _root(0) {}
    trie_tree(std::initializer_list<const char* const>);
    trie_tree(const trie_tree&) = delete;
    trie_tree& operator=(const trie_tree&) = delete;
    ~trie_tree() = default;
    void add(const std::string& _s);
    bool del(const std::string& _s);
    void clear();
    /**
     * @brief whether the tree contains %_s, return false if %_s.empty()
    */
    bool query(const std::string& _s) const;
    /**
     * @brief list all completions prefixed with %_s, return all words if %_s.empty()
    */
    std::vector<std::string> tab(const std::string& _s) const;
    /**
     * @brief common prefix of all completions prefixed with %_s, all words prefixed with ""
    */
    std::string next(const std::string& _s) const;
    /**
     * @brief longest string match
    */
    size_t longest_match(std::string::const_iterator _begin, std::string::const_iterator _end) const;
private:
    node_type* locate(const std::string& _s);
    const node_type* locate(const std::string& _s) const;
    std::vector<node_type*> trace(const std::string& _s);
private:
    node_type _root;
    size_t _word_cnt = 0;
    size_t _max_depth = 0;
};
};

#endif // _ASP_TRIE_TREE_HPP_