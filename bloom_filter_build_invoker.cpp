//
// Created by Harshit Bangar on 17/03/24.
//
#include "bloom_filter_manager.h"
#include "std_hasher.h"
#include <fstream>
#include "bloom_filter_manager.h"
#include "iostream"
#include "string"
#include "bloom_filter.h"

static BloomFilter build(Hasher<std::string, size_t>& hasher, const std::string& dictionaryPath) {
    std::ifstream file(dictionaryPath);
    if(!file.is_open()) {
        std::cerr << "Error: Could not open file " << dictionaryPath << std::endl;
        // throw exception

    }

    std::string word;
    std::vector<std::string> words;
    while (file >> word) {
        words.push_back(word);
    }
    BloomFilter bf(words.size(), 0.01, hasher);
    for (const auto& word_locaL : words) {
        bf.insert(word_locaL);
    }
    return bf;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <dictionaryPath> <outputPath>\n";
        return 1;
    }

    std::string dictionaryPath = argv[1];
    std::string outputPath = argv[2];
    StdHasher<std::string, size_t> hasher;


    BloomFilter bf = build(hasher, dictionaryPath);
    BloomFilterManager bloomFilterManager(std::move(bf));
    bloomFilterManager.saveToFile(outputPath);
    return 0;
}
