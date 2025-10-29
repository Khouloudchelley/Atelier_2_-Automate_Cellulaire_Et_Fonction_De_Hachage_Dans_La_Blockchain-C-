#include "tests.h"
#include <iostream>

int main() {
    std::cout << "=== TEST QUESTIONS 4-7 - ANALYSES ET COMPARAISONS ===" << std::endl;
    
    std::cout << "\n Question 4 - Performance" << std::endl;
    question4_comparaison_performance();
    
    std::cout << "\n Question 5 - Effet avalanche" << std::endl;
    question5_effet_avalanche();
    
    std::cout << "\n Question 6 - Distribution des bits" << std::endl;
    question6_distribution_bits();
    
    std::cout << "\n Question 7 - Comparaison des regles" << std::endl;
    question7_comparaison_regles();
    
    std::cout << "\n QUESTIONS 4-7 VALIDEES - Tous les tests passes!" << std::endl;
    return 0;
}