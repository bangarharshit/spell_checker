//
// Created by Harshit Bangar on 17/03/24.
//

#include <string>
#include "bloom_filter.h"
#include "hasher.h"
#include <sstream>
#include "iostream"

BloomFilter::BloomFilter(size_t numItems, double falsePositiveProbability, const Hasher<std::string, size_t>& hasher): hasher(hasher) {
    // Calculate number of bits and number of hash functions
    numBits = -1 * (numItems * log(falsePositiveProbability)) / (log(2) * log(2));
    numHashFunctions = (numBits / numItems) * log(2);
    // Initialize bit array with false values
    bitArray = std::vector<bool>(numBits, false);
}

BloomFilter::BloomFilter(std::vector<bool>&& bitArray, size_t numHashFunctions, size_t numBits, const Hasher<std::string, size_t>& hasher)
        : bitArray(std::move(bitArray)),
          numHashFunctions(numHashFunctions),
          numBits(numBits),
          hasher(hasher) {}


BloomFilter::BloomFilter(BloomFilter&& other) noexcept
        : bitArray(std::move(other.bitArray)),
          numHashFunctions(other.numHashFunctions),
          numBits(other.numBits),
          hasher(other.hasher) {
    // Clear the data members of the other object
    other.numHashFunctions = 0;
    other.numBits = 0;
}

void BloomFilter::insert(const std::string& item) {
    // Set bits at hash locations to true
    std::vector<size_t> hashes = hash(item);
    for (size_t hashIndex : hashes) {
        bitArray[hashIndex] = true;
    }
}

std::vector<std::string> splitIntoWords(const std::string& item) {
    std::istringstream iss(item);
    std::vector<std::string> words;
    std::string word;

    while (std::getline(iss, word, ' ')) {
        words.push_back(word);
    }

    return words;
}

bool BloomFilter::containsWord(const std::string &item) const {
    std::vector<size_t> hashes = hash(item);
    for (size_t hashIndex : hashes) {
        if (!bitArray[hashIndex]) {
            return false;
        }
    }
    return true;
}

void BloomFilter::containsSentence(const std::string& sentences) const {
    // Check if all bits at hash locations are true
    std::vector<std::string> words = splitIntoWords(sentences);
    std::cout << "These words are spelled incorrectly: \n";
    for (const auto& word : words) {
        if (!containsWord(word)) {
            std::cout << word << std::endl;
        }
    }
}



std::vector<size_t> BloomFilter::hash(const std::string& item) const {
    std::vector<size_t> hashes;
    std::hash<std::string> hashFunction;

    // Generate multiple hash values using different seed values
    for (size_t i = 0; i < numHashFunctions; ++i) {
        size_t hashValue = hashFunction(item + std::to_string(i));
        hashes.push_back(hashValue % numBits);
    }

    return hashes;
}