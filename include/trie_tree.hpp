#ifndef _ICY_TRIE_TREE_HPP_
#define _ICY_TRIE_TREE_HPP_

#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>

namespace icy {

class trie_tree;

class trie_tree {
private:
    struct node {
    public:
        node(char, bool);
        ~node();
        auto add(char) -> void;
        auto del(char) -> bool;
        auto clear() -> void;
        auto value() const -> char;
        auto frequency() const -> size_t;
        auto increase_frequency() -> void;
        auto decrease_frequency() -> void;
        auto set_frequency(size_t) -> void;
        const auto& children() const { return _children; }
    private:
        std::unordered_map<char, node*> _children;
        const char _c;
        size_t _frequency = 0;
    };
    using node_type = trie_tree::node;
public:
public:
    trie_tree() : _root(0, false) {}
    trie_tree(std::initializer_list<const char* const>);
    trie_tree(const trie_tree&);
    trie_tree& operator=(const trie_tree&);
    ~trie_tree() = default;
    /**
     * @brief insert string, increase count, ignore empty string
     * @return string count
    */
    auto insert(const std::string& _s) -> size_t;
    /**
     * @brief decrease count, ignore empty string
     * @return string count
    */
    auto reduce(const std::string& _s) -> size_t;
    /**
     * @brief erase string
     * @return whether the string exists
    */
    auto erase(const std::string& _s) -> bool;
    /**
     * @return string count
    */
    auto count(const std::string& _s) const -> size_t;
    /**
     * @brief erase all string
    */
    auto clear() -> void;
    /**
     * @return whether any string starts with `_s`
    */
    auto starts_with(const std::string& _s) const -> bool;
    /**
     * @return whether trie tree contains `_s`
    */
    auto contains(const std::string& _s) const -> bool;
    /**
     * @return the completion for all strings, of which start with `_s`
    */
    auto completion(const std::string& _s) const -> std::vector<std::string>;
    /**
     * @return the prefix for all strings, of which start with `_s`
    */
    auto prefix(const std::string& _s) const -> std::string;
    /**
     * @brief longest match of `_s` in trie tree
     * @return the length of the matching part
    */
    auto match(const std::string& _s) const -> size_t;
    /**
     * @brief longest match of `[_begin, _end)` in trie tree
     * @return the length of the matching part
    */
    auto match(std::string::const_iterator _begin, std::string::const_iterator _end) const -> size_t;
    /**
     * @brief longest match of `[_begin, _end)` in trie tree
     * @return the length of the matching part
    */
    auto match(const char* _begin, const char* _end) const -> size_t;
private:
    // _M_locate the node, to which the path from the %_root is the %_s
    auto _M_locate(const std::string& _s) -> node_type*;
    // _M_locate the node, to which the path from the %_root is the %_s
    auto _M_locate(const std::string& _s) const -> const node_type*;
    // return the path of %_s when tree contains %_s
    auto _M_trace(const std::string& _s) -> std::vector<node_type*>;
    void _M_assign(const trie_tree& _t);
    void _M_clone_sub_tree(node_type* const _p, const node_type* const _t);
private:
    node_type _root;
    size_t _word_cnt = 0;
    size_t _max_depth = 0;
};

}

#endif // _ICY_TRIE_TREE_HPP_