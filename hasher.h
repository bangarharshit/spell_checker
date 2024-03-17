//
// Created by Harshit Bangar on 17/03/24.
//

#ifndef SPELL_CHECKER_HASHER_H
#define SPELL_CHECKER_HASHER_H


template <typename T, typename V>
class Hasher {
public:
    virtual V hash(const T& item) const = 0;
};


#endif //SPELL_CHECKER_HASHER_H
