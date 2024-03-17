//
// Created by Harshit Bangar on 17/03/24.
//

#ifndef SPELL_CHECKER_BLOOM_FILTER_DESERIALIZER_H
#define SPELL_CHECKER_BLOOM_FILTER_DESERIALIZER_H

#include "string"
#include "bloom_filter.h"
#include "optional"
class BloomFilterDeserializer {
public:
    std::optional<BloomFilter> deserialize(const std::string &path) const;
};
#endif //SPELL_CHECKER_BLOOM_FILTER_DESERIALIZER_H