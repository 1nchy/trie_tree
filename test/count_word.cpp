#include "main.hpp"

#include "trie_tree.hpp"

int main() {
    icy::trie_tree _tt({
        "three", "third", "four", "fourth"
    });
    EXPECT_EQ(_tt.insert("third"), 2);
    EXPECT_EQ(_tt.insert("three"), 2);
    EXPECT_EQ(_tt.insert("three"), 3);
    EXPECT_EQ(_tt.reduce("three"), 2);
    EXPECT_EQ(_tt.reduce("five"), 0);
    EXPECT_EQ(_tt.count("third"), 2);
    EXPECT_EQ(_tt.count("four"), 1);
    EXPECT_EQ(_tt.prefix("f"), "our");
    EXPECT_EQ(_tt.completion("th").size(), 2);
    EXPECT_TRUE(_tt.erase("third"));
    EXPECT_TRUE(_tt.starts_with("th"));
    EXPECT_FALSE(_tt.starts_with("for"));
    EXPECT_EQ(_tt.match("forty"), 0);
    EXPECT_EQ(_tt.match("fourteen"), 4);
    return 0;
}