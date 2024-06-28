#include "details/trie_tree_node.hpp"

namespace icy {
namespace __details__ {

trie_tree_node::trie_tree_node(char _c, bool _end_of_word)
 : _c(_c), _word_frequency(_end_of_word ? 1 : 0) {}
trie_tree_node::~trie_tree_node() {
    for (auto& _i : _children) {
        delete _i.second;
    }
    _children.clear();
}
auto trie_tree_node::contains(char _c) const -> bool {
    return _children.contains(_c);
}
auto trie_tree_node::add(char _c) -> void {
    _children.emplace(_c, new self(_c));
}
auto trie_tree_node::del(char _c) -> bool {
    if (!contains(_c)) return false;
    delete _children.at(_c);
    _children.erase(_c);
    return true;
}

}
}