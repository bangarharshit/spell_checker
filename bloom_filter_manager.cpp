//
// Created by Harshit Bangar on 17/03/24.
//

#include <fstream>
#include "bloom_filter_manager.h"
#include "iostream"
#include "string"
#include "bloom_filter.h"
#include "std_hasher.h"

const int version = 1;

BloomFilterManager::BloomFilterManager(BloomFilter&& filter) : filter(std::move(filter)) {}

void BloomFilterManager::saveToFile(const std::string& path) const {
    std::ofstream file(path, std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return;
    }
    const char* identifier = "CCBF";
    file.write(identifier, 4);
    writeBigEndian(file, version, 2);
    writeBigEndian(file, filter.numHashFunctions, 2);
    writeBigEndian(file, filter.numBits, 4);
    // Convert the bit array into bytes and write them to the file
    char byte = 0;
    int bitCount = 0;
    for (bool bit : filter.bitArray) {
        // Set the corresponding bit in the byte
        byte |= (bit ? 1 : 0) << bitCount;
        bitCount++;

        // If we've accumulated 8 bits, write the byte to the file
        if (bitCount == 8) {
            file.put(byte);
            byte = 0;
            bitCount = 0;
        }
    }

    // If there are any remaining bits, write the last byte padded with zeros
    if (bitCount > 0) {
        file.put(byte);
    }
    if (file.fail()) {
        std::cerr << "Failed to write data to file." << std::endl;
        return;
    }
    // Close file
    file.close();
}

