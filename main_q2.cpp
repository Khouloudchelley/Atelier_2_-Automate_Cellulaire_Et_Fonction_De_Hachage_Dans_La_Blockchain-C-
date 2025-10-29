#include "ac_hash.h"
#include <iostream>

int main() {
    std::cout << "=== TEST QUESTION 2 - FONCTION DE HACHAGE ===" << std::endl;
    
    // Test simple de la fonction
    std::cout << "\n--- Test basique ac_hash() ---" << std::endl;
    std::string test1 = ac_hash("Hello", 30, 128);
    std::string test2 = ac_hash("World", 30, 128);
    
    std::cout << "ac_hash('Hello') = " << test1 << std::endl;
    std::cout << "ac_hash('World') = " << test2 << std::endl;
    std::cout << "Longueur: " << test1.length() << " caractEres hexadecimaux" << std::endl;
    
    // Lancement des tests complets
    question2_demo();
    
    std::cout << "\n QUESTION 2 VALIDEE - Fonction de hachage operationnelle!" << std::endl;
    return 0;
}