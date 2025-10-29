#ifndef AC_CORE_H
#define AC_CORE_H

#include <vector>
#include <string>
#include <array>
#include <cstdint>

class CellularAutomaton {
private:
    std::vector<int> state;
    std::array<int, 8> decode_rule(uint32_t rule);

public:
    // 1.1 Initialisation
    void init_state(const std::vector<int>& bits);
    void init_state(const std::string& bitstring);
    
    // 1.2 Évolution
    void evolve(uint32_t rule, const std::string& boundary = "wrap");
    void evolve_steps(uint32_t rule, size_t steps, const std::string& boundary = "wrap");
    
    // Getters
    std::vector<int> get_state() const;
    std::string state_to_string(bool pretty = false) const;
    std::string state_to_binary_string() const;
    void print_state(bool pretty = false) const;
    size_t size() const { return state.size(); }
};

// Fonctions de démonstration Q1
void question1_demo();
void verify_rule_transitions();
void test_conditions_limites();
void test_pattern_specifique();
void run_all_q1_tests();

#endif