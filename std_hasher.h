//
// Created by Harshit Bangar on 17/03/24.
//

#include "hasher.h"
#include "functional"

template<typename T, typename V>
class StdHasher : public Hasher<T, V> {
    std::hash<T> hashFunction;
public:
    V hash(const T& item) const override {
        return hashFunction(item);
    }
};