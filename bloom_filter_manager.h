//
// Created by Harshit Bangar on 17/03/24.
//

#ifndef SPELL_CHECKER_BLOOM_FILTER_MANAGER_H
#define SPELL_CHECKER_BLOOM_FILTER_MANAGER_H

#include <fstream>
#include "string"
#include "bloom_filter.h"

class BloomFilterManager {
private:
    BloomFilter filter;
    // Function to write an integer value in big endian format
    template<typename T>
    void writeBigEndian(std::ofstream& file, T value, size_t numBytes) const {
        // Convert value to big endian
        for (size_t i = numBytes; i > 0; --i) {
            char byte = (value >> ((i - 1) * 8)) & 0xFF;
            file.put(byte);
        }
    }
public:
    BloomFilterManager(BloomFilter&& filter);
    void saveToFile(const std::string& path) const;
};


#endif //SPELL_CHECKER_BLOOM_FILTER_MANAGER_H
