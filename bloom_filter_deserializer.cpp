//
// Created by Harshit Bangar on 17/03/24.
//

#include "bloom_filter_deserializer.h"
#include "fstream"
#include "iostream"
#include "bloom_filter.h"
#include "vector"
#include "std_hasher.h"
#include "optional"

// Function to read a specified number of bytes from the file
std::vector<char> readBytes(std::ifstream& file, size_t numBytes) {
    std::vector<char> buffer(numBytes);
    file.read(buffer.data(), numBytes);
    return buffer;
}

// Function to read a big endian integer value from the file
template<typename T>
T readBigEndian(std::ifstream& file, size_t numBytes) {
    auto bytes = readBytes(file, numBytes);
    T value = 0;
    for (size_t i = 0; i < numBytes; ++i) {
        value |= static_cast<T>(static_cast<uint8_t>(bytes[i])) << ((numBytes - i - 1) * 8);
    }
    return value;
}


std::optional<BloomFilter> BloomFilterDeserializer::deserialize(const std::string &path) const {
    // Read identifier
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return std::nullopt;
    }
    auto identifier = readBytes(file, 4);
    if (std::string(identifier.data(), identifier.size()) != "CCBF") {
        std::cerr << "Error: Invalid file format." << std::endl;
        return std::nullopt;
    }

    // Read version
    uint16_t version = readBigEndian<uint16_t>(file, 2);

    // Read numHashFunctions
    uint16_t numHashFunctions = readBigEndian<uint16_t>(file, 2);

    // Read numBits
    uint32_t numBits = readBigEndian<uint32_t>(file, 4);

    // Read bit array
    std::vector<bool> bitArray;
    char byte;
    while (file.get(byte)) {
        for (int i = 0; i < 8; ++i) {
            bitArray.push_back((byte >> i) & 1);
        }
    }
    // Close file
    file.close();

    StdHasher<std::string, size_t> hasher;

    BloomFilter bf = BloomFilter(std::move(bitArray), numHashFunctions, numBits, hasher);
    return bf;
}


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <inputPath>\n";
        return 1;
    }

    std::string inputPath = argv[1];
    BloomFilterDeserializer deserializer;
    std::optional<BloomFilter> bloomFilter = deserializer.deserialize(inputPath);
    if(bloomFilter != std::nullopt) {
        bloomFilter.value().containsSentence("hi hello word concurrency coding challenges imadethis up");
    }
    return 0;
}