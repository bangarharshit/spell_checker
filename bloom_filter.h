//
// Created by Harshit Bangar on 17/03/24.
//

#ifndef SPELL_CHECKER_BLOOM_FILTER_H
#define SPELL_CHECKER_BLOOM_FILTER_H
#include <vector>
#include <functional>
#include <cmath>
#include "hasher.h"

class BloomFilter {
private:
    std::vector<bool> bitArray;
    size_t numHashFunctions;
    size_t numBits;
    const Hasher<std::string, size_t>& hasher;
    friend class BloomFilterManager;
public:
    BloomFilter(size_t numItems, double falsePositiveProbability, const Hasher<std::string, size_t>& hasher);
    BloomFilter(std::vector<bool>&& bitArray, size_t numHashFunctions, size_t numBits, const Hasher<std::string, size_t>& hasher);
    BloomFilter(BloomFilter&& other) noexcept;
    void insert(const std::string& item);
    [[nodiscard]] bool containsWord(const std::string& item) const;
    void containsSentence(const std::string& sentences) const;
private:
    [[nodiscard]] std::vector<size_t> hash(const std::string& item) const;
};


#endif //SPELL_CHECKER_BLOOM_FILTER_H
