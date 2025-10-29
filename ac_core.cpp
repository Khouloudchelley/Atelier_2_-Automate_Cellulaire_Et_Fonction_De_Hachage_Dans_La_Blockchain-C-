#include "ac_core.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ============================================================================
// IMPLÉMENTATION DE LA CLASSE CellularAutomaton
// ============================================================================

array<int, 8> CellularAutomaton::decode_rule(uint32_t rule) {
    array<int, 8> map{};
    for (int i = 0; i < 8; ++i) {
        map[i] = (rule >> i) & 1u;
    }
    return map;
}

void CellularAutomaton::init_state(const vector<int>& bits) {
    state = bits;
}

void CellularAutomaton::init_state(const string& bitstring) {
    state.clear();
    for (char c : bitstring) {
        if (c == '0') state.push_back(0);
        else if (c == '1') state.push_back(1);
    }
}

void CellularAutomaton::evolve(uint32_t rule, const string& boundary) {
    if (state.empty()) return;
    
    array<int, 8> rmap = decode_rule(rule);
    vector<int> new_state(state.size(), 0);
    
    for (size_t i = 0; i < state.size(); ++i) {
        int left, self, right;
        
        // Calcul du voisin gauche
        if (i == 0) {
            left = (boundary == "wrap") ? state[state.size() - 1] : 0;
        } else {
            left = state[i - 1];
        }
        
        // Cellule courante
        self = state[i];
        
        // Calcul du voisin droit
        if (i + 1 == state.size()) {
            right = (boundary == "wrap") ? state[0] : 0;
        } else {
            right = state[i + 1];
        }
        
        // Code du voisinage (0-7)
        int code = (left << 2) | (self << 1) | right;
        
        // Application de la règle
        new_state[i] = rmap[code];
    }
    
    state = new_state;
}

void CellularAutomaton::evolve_steps(uint32_t rule, size_t steps, const string& boundary) {
    for (size_t i = 0; i < steps; ++i) {
        evolve(rule, boundary);
    }
}

vector<int> CellularAutomaton::get_state() const {
    return state;
}

string CellularAutomaton::state_to_string(bool pretty) const {
    string result;
    for (int b : state) {
        result += pretty ? (b ? '#' : ' ') : (b ? '1' : '0');
    }
    return result;
}

string CellularAutomaton::state_to_binary_string() const {
    string result;
    for (int b : state) {
        result += b ? '1' : '0';
    }
    return result;
}

void CellularAutomaton::print_state(bool pretty) const {
    cout << state_to_string(pretty) << endl;
}

// ============================================================================
// FONCTIONS DE DÉMONSTRATION QUESTION 1
// ============================================================================

void question1_demo() {
    cout << "\n" << string(60, '=') << endl;
    cout << "QUESTION 1 - AUTOMATE CELLULAIRE 1D" << endl;
    cout << string(60, '=') << endl;
    
    CellularAutomaton ca;
    
    cout << "\n--- Test Règle 30 (comportement chaotique) ---" << endl;
    cout << "État initial avec un seul '1' au centre:" << endl;
    
    ca.init_state("0000001000000");
    cout << "Étape 0: ";
    ca.print_state(true);
    
    for (int i = 0; i < 8; i++) {
        ca.evolve(30);
        cout << "Étape " << (i + 1) << ": ";
        ca.print_state(true);
    }
    
    cout << "\n--- Test Règle 90 (motif fractal) ---" << endl;
    ca.init_state("0000001000000");
    cout << "Étape 0: ";
    ca.print_state(true);
    
    for (int i = 0; i < 8; i++) {
        ca.evolve(90);
        cout << "Étape " << (i + 1) << ": ";
        ca.print_state(true);
    }
    
    cout << "\n--- Test Règle 110 (universelle) ---" << endl;
    ca.init_state("0000001000000");
    cout << "Étape 0: ";
    ca.print_state(true);
    
    for (int i = 0; i < 8; i++) {
        ca.evolve(110);
        cout << "Étape " << (i + 1) << ": ";
        ca.print_state(true);
    }
}

void verify_rule_transitions() {
    cout << "\n--- Vérification des règles de transition ---" << endl;
    
    // Fonction pour afficher une règle
    auto print_rule_details = [](uint32_t rule, const string& name) {
        cout << name << " (décimal: " << rule << ")" << endl;
        cout << "Binaire: ";
        for (int i = 7; i >= 0; --i) {
            cout << ((rule >> i) & 1);
        }
        cout << endl;
        
        cout << "Table de transition:" << endl;
        cout << "Voisinage | Sortie" << endl;
        cout << "----------|-------" << endl;
        
        array<int, 8> rmap;
        for (int i = 0; i < 8; ++i) {
            rmap[i] = (rule >> i) & 1u;
        }
        
        // Afficher dans l'ordre 111, 110, 101, ..., 000
        for (int i = 7; i >= 0; --i) {
            int left = (i >> 2) & 1;
            int center = (i >> 1) & 1;
            int right = i & 1;
            cout << "  " << left << center << right << "     |    " << rmap[i] << endl;
        }
        cout << endl;
    };
    
    print_rule_details(30, "Rule 30");
    print_rule_details(90, "Rule 90");
    print_rule_details(110, "Rule 110");
}

// ============================================================================
// FONCTIONS DE TEST SUPPLÉMENTAIRES
// ============================================================================

void test_conditions_limites() {
    cout << "\n--- Test des conditions aux limites ---" << endl;
    
    CellularAutomaton ca;
    
    cout << "Condition 'wrap' (périodique):" << endl;
    ca.init_state("100");
    cout << "Initial: " << ca.state_to_binary_string() << endl;
    ca.evolve(30, "wrap");
    cout << "Après 1 étape: " << ca.state_to_binary_string() << endl;
    
    cout << "Condition 'zero' (bords à 0):" << endl;
    ca.init_state("100");
    cout << "Initial: " << ca.state_to_binary_string() << endl;
    ca.evolve(30, "zero");
    cout << "Après 1 étape: " << ca.state_to_binary_string() << endl;
}

void test_pattern_specifique() {
    cout << "\n--- Test avec pattern spécifique ---" << endl;
    
    CellularAutomaton ca;
    
    // Pattern alterné
    cout << "Pattern alterné 010101:" << endl;
    ca.init_state("010101");
    cout << "Initial: " << ca.state_to_binary_string() << endl;
    
    for (int i = 0; i < 4; i++) {
        ca.evolve(90);
        cout << "Étape " << (i + 1) << ": " << ca.state_to_binary_string() << endl;
    }
    
    // Pattern tout à 1
    cout << "\nPattern tout à 1 (11111):" << endl;
    ca.init_state("11111");
    cout << "Initial: " << ca.state_to_binary_string() << endl;
    
    for (int i = 0; i < 4; i++) {
        ca.evolve(30);
        cout << "Étape " << (i + 1) << ": " << ca.state_to_binary_string() << endl;
    }
}

// Fonction pour exécuter tous les tests de la Question 1
void run_all_q1_tests() {
    cout << "TESTS COMPLETS QUESTION 1" << endl;
    cout << string(50, '=') << endl;
    
    question1_demo();
    verify_rule_transitions();
    test_conditions_limites();
    test_pattern_specifique();
    
    cout << "\n✅ TOUS LES TESTS QUESTION 1 SONT PASSÉS!" << endl;
}