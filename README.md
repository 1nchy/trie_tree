# TRIE TREE

## 摘要

为了实现各类项目中常用的字符串解析与字符串补全/建议功能，这里我们利用哈希表实现一个简易的字典树结构。

## 概述

### 需求分析与设计

字符串解析时，常常遵循**最长匹配**原则。
例如在计算器应用中，我们要读入一个表达式 `sinh(pi/2)`，我们可能已经定义了两种有关的三角函数与反三角函数：`sin`、`sinh`。
在这个例子中，我们依据最长匹配原则，应该选择 `sinh` 作为我们的解析结果。

关于字符串补全与建议功能，字典树容易求出单词的公共前缀，进而进行补全，利用树的分枝，容易求出单词建议。

为了兼顾时间与空间复杂度，我们使用哈希表实现了字典树。

### 构造函数

`trie_tree` 除了默认构造函数以外，还提供了一个列表初始化的方法。其效果相当于对列表中的字符串逐一调用 `add` 接口，该构造函数主要是方便开发者构造一个 `const` 的字典树。

~~~cpp
/**
 * asp::trie_tree _t;
 * _t.add("one");
 * _t.add("two");
 * _t.add("three");
*/
asp::trie_tree _t {"one", "two", "three"};
~~~

### 成员函数

~~~cpp
asp::trie_tree _t1 {"sin", "sinh"};
std::string _s = "sinh(pi/2)";
const auto _len = _t1.longest_match(_s.cbegin(), _s.cend()); // _len = 4
asp::trie_tree _t2 {"HOME", "HOSTTYPE"};
std::string _env = "H";
_env.append(_t2.next(_env)); // _env = "HO"
const auto _suggestion = _t2.tab(_env); // _suggestion = ["ME", "STTYPE"]
~~~

## 实现

### 节点实现

~~~cpp
struct trie_tree_node {
    const char _c;
    bool _end_of_word = false;
    std::unordered_map<char, trie_tree_node*> _children;
};
~~~

树节点使用哈希表保存子节点集合。

### 字典树实现

字典树几乎所有函数都依赖于节点定位功能，即根据给定字符串，找到最接近的节点（拥有公共前缀）。
