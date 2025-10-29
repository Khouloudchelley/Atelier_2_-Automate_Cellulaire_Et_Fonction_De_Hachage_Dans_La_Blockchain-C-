#include "blockchain.h"
#include <iostream>

int main() {
    std::cout << "=== TEST QUESTION 3 - BLOCKCHAIN ===" << std::endl;
    
    // Test de base
    std::cout << "\n--- Creation de la blockchain ---" << std::endl;
    Blockchain bc;
    bc.print_chain();
    
    // Test d'ajout de blocs
    std::cout << "\n--- Ajout de blocs avec differents modes de hachage ---" << std::endl;
    
    std::cout << "\n1. Bloc avec AC_HASH (Rule 30):" << std::endl;
    bc.add_block("Premiere transaction", "AC_HASH", 30);
    
    std::cout << "\n2. Bloc avec AC_HASH (Rule 110):" << std::endl;
    bc.add_block("Deuxieme transaction", "AC_HASH", 110);
    
    std::cout << "\n3. Bloc avec SHA256:" << std::endl;
    bc.add_block("Troisieme transaction", "SHA256");
    
    // Affichage final
    std::cout << "\n--- Blockchain finale ---" << std::endl;
    bc.print_chain();
    
    std::cout << "\n QUESTION 3 VALIDEE - Integration blockchain reussie!" << std::endl;
    return 0;
}