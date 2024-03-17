//
// Created by Harshit Bangar on 17/03/24.
//
#include <gtest/gtest.h>
#include "bloom_filter.h"
#include "std_hasher.h"

constexpr StdHasher<std::string, size_t> hasher;

TEST(BloomFilterTest, Contains) {
    BloomFilter bf(100, 0.01, hasher);
    bf.insert("test");
    ASSERT_TRUE(bf.containsWord("test"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}