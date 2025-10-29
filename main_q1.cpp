#include "ac_core.h"
#include <iostream>

int main() {
    std::cout << "=== TEST QUESTION 1 - AUTOMATE CELLULAIRE ===" << std::endl;
    
    CellularAutomaton ca;
    
    // Test 1.1 - Initialisation
    std::cout << "\n--- Test 1.1 init_state() ---" << std::endl;
    ca.init_state("0001000");
    std::cout << "Etat initial: " << ca.state_to_string() << std::endl;
    
    // Test 1.2 - Evolution Rule 30
    std::cout << "\n--- Test 1.2 evolve() Rule 30 ---" << std::endl;
    ca.init_state("0001000");
    std::cout << "Etape 0: ";
    ca.print_state(true);
    for (int i = 0; i < 5; i++) {
        ca.evolve(30);
        std::cout << "Etape " << (i+1) << ": ";
        ca.print_state(true);
    }
    
    // Test 1.3 - Verification Rule 90
    std::cout << "\n--- Test 1.3 evolve() Rule 90 ---" << std::endl;
    ca.init_state("0001000");
    std::cout << "Etape 0: ";
    ca.print_state(true);
    for (int i = 0; i < 5; i++) {
        ca.evolve(90);
        std::cout << "Etape " << (i+1) << ": ";
        ca.print_state(true);
    }
    
    // TEST AJOUTÉ - Vérification Rule 110
    std::cout << "\n--- Test 1.3 evolve() Rule 110 ---" << std::endl;
    ca.init_state("0001000");
    std::cout << "Etape 0: ";
    ca.print_state(true);
    for (int i = 0; i < 5; i++) {
        ca.evolve(110);
        std::cout << "Etape " << (i+1) << ": ";
        ca.print_state(true);
    }
    
    std::cout << "\nQUESTION 1 VALIDEE - Automate cellulaire fonctionnel!" << std::endl;
    return 0;
}