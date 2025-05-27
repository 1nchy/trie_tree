#include "main.hpp"

#include "trie_tree.hpp"

int main() {
    icy::trie_tree _tt({
        "three", "third", "four", "fourth"
    });
    EXPECT_EQ(_tt.insert("third"), 2);
    EXPECT_EQ(_tt.insert("three"), 2);
    EXPECT_EQ(_tt.count("third"), 2);
    EXPECT_EQ(_tt.count("four"), 1);
    EXPECT_EQ(_tt.prefix("f"), "our");
    EXPECT_EQ(_tt.completion("th").size(), 2);
    EXPECT_TRUE(_tt.erase("third"));
    return 0;
}