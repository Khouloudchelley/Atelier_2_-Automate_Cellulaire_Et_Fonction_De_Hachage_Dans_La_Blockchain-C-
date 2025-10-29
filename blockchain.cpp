#include "blockchain.h"
#include "ac_hash.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>

using namespace std;

Block::Block(int idx, const std::string& prev_hash, const std::string& d)
    : index(idx), previous_hash(prev_hash), data(d), nonce(0), timestamp(time(nullptr)) {}

string Block::to_string() const {
    stringstream ss;
    ss << "Block " << index << " [Prev: " << previous_hash.substr(0, 8) << "...";
    ss << " | Hash: " << hash.substr(0, 8) << "... | Nonce: " << nonce;
    ss << " | Data: " << (data.length() > 20 ? data.substr(0, 17) + "..." : data) << "]";
    return ss.str();
}

string Block::serialize() const {
    stringstream ss;
    ss << index << previous_hash << data << nonce << timestamp;
    return ss.str();
}

Blockchain::Blockchain() : difficulty(1) {  // DIFFICULTE REDUITE À 1
    // Genesis block
    Block genesis(0, "0", "Genesis Block");
    genesis.hash = ac_hash(genesis.serialize(), 30, 128);
    chain.push_back(genesis);
}

string Blockchain::calculate_hash(const Block& block, const std::string& hash_mode, uint32_t rule) {
    string data = block.serialize();
    
    if (hash_mode == "AC_HASH") {
        return ac_hash(data, rule, 128);
    } else {
        // Simulation SHA256
        return "sha2_" + ac_hash(data, 30, 64).substr(0, 59);
    }
}

void Blockchain::mine_block(Block& block, const std::string& hash_mode, uint32_t rule) {
    string target(difficulty, '0');
    
    cout << "Minage du bloc " << block.index << " avec " << hash_mode;
    if (hash_mode == "AC_HASH") {
        cout << " (Rule " << rule << ")";
    }
    cout << "..." << endl;
    
    auto start_time = chrono::high_resolution_clock::now();
    int iterations = 0;
    const int MAX_ITERATIONS = 10000;  // Timeout reduit
    
    while (iterations < MAX_ITERATIONS) {
        block.hash = calculate_hash(block, hash_mode, rule);
        iterations++;
        
        if (block.hash.substr(0, difficulty) == target) {
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
            
            cout << "Bloc mine! Nonce: " << block.nonce << endl;
            cout << "  Hash: " << block.hash << endl;
            cout << "  Iterations: " << iterations << endl;
            cout << "  Temps: " << duration.count() << " ms" << endl;
            return;
        }
        block.nonce++;
    }
    
    // Si timeout
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << " Timeout apres " << iterations << " iterations (" << duration.count() << " ms)" << endl;
    cout << "Dernier hash: " << block.hash.substr(0, 32) << "..." << endl;
}

void Blockchain::add_block(const std::string& data, const std::string& hash_mode, uint32_t rule) {
    Block new_block(chain.size(), chain.back().hash, data);
    mine_block(new_block, hash_mode, rule);
    chain.push_back(new_block);
}

bool Blockchain::is_valid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        if (chain[i].previous_hash != chain[i-1].hash) {
            return false;
        }
    }
    return true;
}

void Blockchain::print_chain() const {
    cout << "\n=== BLOCKCHAIN ===" << endl;
    cout << "Taille: " << chain.size() << " blocs" << endl;
    cout << "Difficulte: " << difficulty << " zeros requis" << endl;
    cout << string(50, '-') << endl;
    
    for (const auto& block : chain) {
        cout << block.to_string() << endl;
    }
    
    cout << string(50, '-') << endl;
    cout << "Validite: " << (is_valid() ? " VALIDE" : " INVALIDE") << endl;
}

void question3_demo() {
    cout << "\n" << string(60, '=') << endl;
    cout << "QUESTION 3 - INTEGRATION DANS LA BLOCKCHAIN" << endl;
    cout << string(60, '=') << endl;
    
    Blockchain bc;
    
    cout << "\n 3.1 - Minage avec AC_HASH (Rule 30)" << endl;
    bc.add_block("Transaction Alice → Bob: 50 BTC", "AC_HASH", 30);
    
    cout << "\n 3.1 - Minage avec AC_HASH (Rule 110)" << endl;
    bc.add_block("Transaction Bob → Charlie: 25 BTC", "AC_HASH", 110);
    
    cout << "\n 3.1 - Minage avec SHA256 (simule)" << endl;
    bc.add_block("Transaction Charlie → David: 10 BTC", "SHA256");
    
    cout << "\n 3.3 - Validation de la blockchain" << endl;
    bc.print_chain();
}