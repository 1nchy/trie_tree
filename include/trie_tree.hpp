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
    /**
     * @brief 添加字符串，若字符串已存在，则计数加一
    */
    auto add(const std::string& _s) -> void;
    /**
     * @brief 字符串计数减一
     * @return true，若该字符串不存在则返回 false
    */
    auto minus(const std::string& _s) -> bool;
    /**
     * @brief 删除字符串
     * @return true，若该字符串不存在则返回 false
    */
    auto del(const std::string& _s) -> bool;
    /**
     * @return 字符串计数
    */
    auto count(const std::string& _s) const -> size_t;
    /**
     * @brief 删除所有字符串
    */
    auto clear() -> void;
    /**
     * @return 字典树是否包含为 %_s 的路径（不一定包含 %_s）
    */
    auto query(const std::string& _s) const -> bool;
    /**
     * @return 字典树是否包含为 %_s
    */
    auto contains(const std::string& _s) const -> bool;
    /**
     * @brief 查找所有以 %_s 为前缀的单词（空字符串是所有单词的前缀）
     * @return 所有单词的补全
    */
    auto tab(const std::string& _s) const -> std::vector<std::string>;
    /**
     * @brief 查找所有以 %_s 为前缀的单词（空字符串是所有单词的前缀）
     * @return 所有单词补全的公共前缀
    */
    auto next(const std::string& _s) const -> std::string;
    /**
     * @brief 寻找字符串在字典树中的最长匹配
     * @return 返回匹配部分的长度
    */
    auto longest_match(const std::string& _s) const -> size_t;
    /**
     * @brief 寻找字符串在字典树中的最长匹配
     * @param _begin 字符串起始迭代器
     * @param _end 字符串终止迭代器
     * @return 返回匹配部分的长度
    */
    auto longest_match(std::string::const_iterator _begin, std::string::const_iterator _end) const -> size_t;
private:
    // locate the node, to which the path from the %_root is the %_s
    auto locate(const std::string& _s) -> node_type*;
    // locate the node, to which the path from the %_root is the %_s
    auto locate(const std::string& _s) const -> const node_type*;
    // return the path of %_s when tree contains %_s
    auto trace(const std::string& _s) -> std::vector<node_type*>;
private:
    node_type _root;
    size_t _word_cnt = 0;
    size_t _max_depth = 0;
};
};

#endif // _ASP_TRIE_TREE_HPP_