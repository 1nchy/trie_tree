#include "trie_tree.hpp"

#include <cassert>

#include <functional>

namespace asp {
auto trie_tree::locate(const std::string& _s)
-> node_type* {
    node_type* _p = &_root;
    for (const auto _c : _s) {
        if (_p->contains(_c)) {
            _p = _p->_children.at(_c);
        }
        else {
            return &_root;
        }
    }
    return _p;
}
auto trie_tree::locate(const std::string& _s) const
-> const node_type* {
    const node_type* _p = &_root;
    for (const auto _c : _s) {
        if (_p->contains(_c)) {
            _p = _p->_children.at(_c);
        }
        else {
            return &_root;
        }
    }
    return _p;
}
auto trie_tree::trace(const std::string& _s)
-> std::vector<node_type*> {
    std::vector<node_type*> _path;
    if (_s.empty()) return _path;
    _path.reserve(_max_depth);
    node_type* _p = &_root;
    for (const auto _c : _s) {
        if (_p->contains(_c)) {
            _p = _p->_children.at(_c);
            _path.emplace_back(_p);
        }
        else {
            return {};
        }
    }
    return _path;
}
auto trie_tree::_M_assign(const trie_tree& _t)
-> void {
    _M_clone_sub_tree(&_root, &_t._root);
}
auto trie_tree::_M_clone_sub_tree(node_type* const _p, const node_type* const _t)
-> void {
    assert(_p->_c == _t->_c);
    _p->_word_frequency = _t->_word_frequency;
    for (const auto [_c, _cp] : _t->_children) {
        _p->add(_c);
        _M_clone_sub_tree(_p->_children[_c], _t->_children.at(_c));
    }
}


trie_tree::trie_tree(std::initializer_list<const char* const> _il)
: _root(0) {
    for (const auto& _s : _il) {
        add(std::string(_s));
    }
}
trie_tree::trie_tree(const trie_tree& _t)
: _root(0) {
    _M_assign(_t);
    _max_depth = _t._max_depth;
    _word_cnt = _t._word_cnt;
}
trie_tree& trie_tree::operator=(const trie_tree& _t) {
    if (&_t == this) return *this;
    _M_assign(_t);
    _max_depth = _t._max_depth;
    _word_cnt = _t._word_cnt;
    return *this;
}


auto trie_tree::add(const std::string& _s)
-> void {
    if (_s.empty()) return;
    node_type* _p = &_root;
    size_t _depth = 0;
    for (const auto _c : _s) {
        if (_p->contains(_c)) {
            _p = _p->_children.at(_c);
        }
        else {
            _p->add(_c);
            ++_depth;
            _p = _p->_children.at(_c);
        }
    }
    if (_p->_word_frequency == 0) {
        ++_word_cnt;
    }
    ++_p->_word_frequency;
    _max_depth = std::max(_max_depth, _depth);
}
auto trie_tree::minus(const std::string& _s)
-> bool {
    if (_s.empty()) return false;
    std::vector<node_type*> _path = trace(_s);
    if (_path.empty()) return false;
    node_type* _p = _path.back();
    assert(_p->_word_frequency != 0);
    --_p->_word_frequency;
    if (_p->_word_frequency != 0) return true;
    char _to_del_key = 0;
    for (auto _i = _path.rbegin(); _i != _path.rend(); ++_i) {
        _p = *_i;
        _p->del(_to_del_key);
        if (_p->_children.size() >= 1) break;
        _to_del_key = _p->_c;
    }
    --_word_cnt;
    return true;
}
auto trie_tree::del(const std::string& _s)
-> bool {
    if (_s.empty()) return false;
    std::vector<node_type*> _path = trace(_s);
    if (_path.empty()) return false;
    node_type* _p = _path.back();
    assert(_p->_word_frequency != 0); _p->_word_frequency = 0;
    char _to_del_key = 0;
    for (auto _i = _path.rbegin(); _i != _path.rend(); ++_i) {
        _p = *_i;
        _p->del(_to_del_key);
        if (_p->_children.size() >= 1) break;
        _to_del_key = _p->_c;
    }
    --_word_cnt;
    return true;
}
auto trie_tree::count(const std::string& _s) const
-> size_t {
    const node_type* _p = locate(_s);
    return _p->_word_frequency;
}
auto trie_tree::clear()
-> void {
    for (auto& _i : _root._children) {
        delete _i.second;
    }
    _root._children.clear();
}
auto trie_tree::query(const std::string& _s) const
-> bool {
    if (_s.empty()) return false;
    const node_type* _p = locate(_s);
    return _p != &_root;
}
auto trie_tree::contains(const std::string& _s) const
-> bool {
    return count(_s) != 0;
}
auto trie_tree::tab(const std::string& _s) const
-> std::vector<std::string> {
    const node_type* _p = locate(_s);
    if (!_s.empty() && _p == &_root) return {};
    std::vector<std::string> _completion;
    std::string _path; _path.reserve(_max_depth);
    std::function<void(const node_type* _p)> dfs
    = [&](const node_type* _p) {
        if (_p->_word_frequency != 0) {
            // if (!_path.empty())
            _completion.emplace_back(_path);
        }
        for (const auto& _i : _p->_children) {
            _path.push_back(_i.first);
            const node_type* _k = _i.second;
            dfs(_k);
            _path.pop_back();
        }
    };
    dfs(_p);
    return _completion;
}
auto trie_tree::next(const std::string& _s) const
-> std::string {
    // const node_type* _p = locate(_s);
    const node_type* _p = &_root;
    for (const auto _c : _s) {
        if (_p->contains(_c)) {
            _p = _p->_children.at(_c);
        }
        else {
            _p = &_root; break;
        }
    }
    if (!_s.empty() && _p == &_root) return {};
    std::string _completion;
    while (_p->_children.size() == 1 && _p->_word_frequency == 0) {
        _p = _p->_children.cbegin()->second;
        _completion.push_back(_p->_c);
    }
    return _completion;
}
auto trie_tree::longest_match(const std::string& _s) const
-> size_t {
    const node_type* _p = &_root;
    size_t _max_match = 0;
    for (size_t _i = 0; _i != _s.size();) {
        if (_p->contains(_s[_i])) {
            _p = _p->_children.at(_s[_i]); ++_i;
            if (_p->_word_frequency != 0) {
                _max_match = _i;
            }
        }
        else {
            break;
        }
    }
    return _max_match;
}
auto trie_tree::longest_match(std::string::const_iterator _begin, std::string::const_iterator _end) const
-> size_t {
    std::string::const_iterator _i = _begin;
    const node_type* _p = &_root;
    size_t _max_match = 0;
    while (_i != _end) {
        if (_p->contains(*_i)) {
            _p = _p->_children.at(*_i); ++_i;
            if (_p->_word_frequency != 0) {
                _max_match = _i - _begin;
            }
        }
        else {
            break;
        }
    }
    return _max_match;
}
};