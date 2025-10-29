#ifndef AC_HASH_H
#define AC_HASH_H

#include <string>
#include <vector>
#include <cstdint>

// 2.1 Fonction de hachage principale
std::string ac_hash(const std::string& input, uint32_t rule, size_t steps);

// 2.2 Conversion
std::vector<int> string_to_bits(const std::string& input);
std::string bits_to_hex(const std::vector<int>& bits);
std::vector<int> compress_to_256_bits(const std::vector<int>& bits);

// 2.4 Tests
void question2_demo();
void test_hash_collisions();
void test_different_rules();

#endif