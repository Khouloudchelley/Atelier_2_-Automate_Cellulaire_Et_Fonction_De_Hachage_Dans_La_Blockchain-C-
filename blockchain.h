#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string>
#include <vector>
#include <ctime>

struct Block {
    int index;
    std::string previous_hash;
    std::string data;
    std::string hash;
    uint32_t nonce;
    time_t timestamp;
    
    Block(int idx, const std::string& prev_hash, const std::string& d);
    std::string to_string() const;
    std::string serialize() const;
};

class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;
    
public:
    Blockchain();
    void add_block(const std::string& data, const std::string& hash_mode, uint32_t rule = 30);
    bool is_valid() const;
    void print_chain() const;
    
    // 3.1 Mode de hachage
    std::string calculate_hash(const Block& block, const std::string& hash_mode, uint32_t rule = 30);
    void mine_block(Block& block, const std::string& hash_mode, uint32_t rule = 30);
    
    // Getters
    size_t size() const { return chain.size(); }
    const Block& get_block(int index) const { return chain[index]; }
};

void question3_demo();

#endif