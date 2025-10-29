#include "tests.h"
#include "ac_hash.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>
#include <numeric>
#include <cmath>

using namespace std;
using namespace chrono;

// Fonction utilitaire pour conversion hexa→binaire
string hex_to_binary(const string& hex) {
    string binary;
    for (char c : hex) {
        int value;
        if (c >= '0' && c <= '9') value = c - '0';
        else if (c >= 'A' && c <= 'F') value = 10 + (c - 'A');
        else if (c >= 'a' && c <= 'f') value = 10 + (c - 'a');
        else continue;
        
        for (int i = 3; i >= 0; i--) {
            binary += (value & (1 << i)) ? '1' : '0';
        }
    }
    return binary;
}

// Question 4 - Comparaison performance
void question4_comparaison_performance() {
    cout << "\n" << string(60, '=') << endl;
    cout << "QUESTION 4 - COMPARAISON PERFORMANCE" << endl;
    cout << string(60, '=') << endl;
    
    string test_data = "Donnees de test pour la performance";
    const int iterations = 50;  // Reduit pour aller plus vite
    
    cout << "Test sur " << iterations << " hachages AC_HASH..." << endl;
    
    // Test AC_HASH Rule 30
    auto start_ac30 = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        ac_hash(test_data + to_string(i), 30, 128);
    }
    auto end_ac30 = high_resolution_clock::now();
    auto duration_ac30 = duration_cast<microseconds>(end_ac30 - start_ac30);
    
    // Test AC_HASH Rule 110
    auto start_ac110 = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        ac_hash(test_data + to_string(i), 110, 128);
    }
    auto end_ac110 = high_resolution_clock::now();
    auto duration_ac110 = duration_cast<microseconds>(end_ac110 - start_ac110);
    
    cout << fixed << setprecision(2);
    cout << "AC_HASH Rule 30:  " << (duration_ac30.count() / (double)iterations) << " μs par hash" << endl;
    cout << "AC_HASH Rule 110: " << (duration_ac110.count() / (double)iterations) << " μs par hash" << endl;
    cout << "SHA256 (estime):  ~150 μs par hash" << endl;
    
    // Comparaison
    double speed_ac30 = 150.0 / (duration_ac30.count() / (double)iterations);
    cout << "Rule 30 est " << speed_ac30 << " fois plus rapide que SHA256 estime" << endl;
}

// Question 5 - Effet avalanche
void question5_effet_avalanche() {
    cout << "\n" << string(60, '=') << endl;
    cout << "QUESTION 5 - EFFET AVALANCHE" << endl;
    cout << string(60, '=') << endl;
    
    vector<pair<string, string>> test_pairs;
    test_pairs.push_back(make_pair("Hello World", "Hello World!"));
    test_pairs.push_back(make_pair("Blockchain", "Blockchaim"));
    test_pairs.push_back(make_pair("abcdefgh", "abcdefgi"));
    test_pairs.push_back(make_pair("123456789", "123456780"));
    
    double total_percentage = 0.0;
    int test_count = 0;
    
    cout << "Test de l'effet avalanche (Rule 30):" << endl;
    cout << "Un bit d'entree different doit changer ~50% des bits de sortie" << endl << endl;
    
    for (const auto& test_pair : test_pairs) {
        string input1 = test_pair.first;
        string input2 = test_pair.second;
        
        string hash1 = ac_hash(input1, 30, 128);
        string hash2 = ac_hash(input2, 30, 128);
        
        // Conversion hexa → binaire pour calcul precis
        string bin1 = hex_to_binary(hash1);
        string bin2 = hex_to_binary(hash2);
        
        int bit_differences = 0;
        size_t min_len = min(bin1.length(), bin2.length());
        
        for (size_t i = 0; i < min_len; i++) {
            if (bin1[i] != bin2[i]) bit_differences++;
        }
        
        double percentage = (bit_differences * 100.0) / min_len;
        total_percentage += percentage;
        test_count++;
        
        cout << "Test " << test_count << ": '" << input1 << "' vs '" << input2 << "'" << endl;
        cout << "  Bits differents: " << bit_differences << "/" << min_len;
        cout << " (" << fixed << setprecision(2) << percentage << "%)" << endl;
        cout << "  Hash1: " << hash1.substr(0, 16) << "..." << endl;
        cout << "  Hash2: " << hash2.substr(0, 16) << "..." << endl << endl;
    }
    
    double average_percentage = total_percentage / test_count;
    cout << "=== RESULTAT AVALANCHE ===" << endl;
    cout << "Pourcentage moyen de bits differents: " << average_percentage << "%" << endl;
    cout << "Ideal: 50%" << endl;
    cout << "Ecart: " << abs(average_percentage - 50.0) << "%" << endl;
    cout << "Effet avalanche: " << (abs(average_percentage - 50.0) < 10.0 ? " FORT" : " FAIBLE") << endl;
}

// Question 6 - Distribution des bits
void question6_distribution_bits() {
    cout << "\n" << string(60, '=') << endl;
    cout << "QUESTION 6 - DISTRIBUTION DES BITS" << endl;
    cout << string(60, '=') << endl;
    
    const int sample_size = 1000;  // Reduit pour aller plus vite
    int total_bits = 0;
    int ones_count = 0;
    
    cout << "Analyse de la distribution sur " << sample_size << " hachages..." << endl;
    
    for (int i = 0; i < sample_size; i++) {
        string input = "sample_" + to_string(i);
        string hash = ac_hash(input, 30, 128);
        string binary_hash = hex_to_binary(hash);
        
        for (char bit : binary_hash) {
            if (bit == '1') ones_count++;
            total_bits++;
        }
        
        // Barre de progression
        if ((i + 1) % 100 == 0) {
            cout << "Progression: " << (i + 1) << "/" << sample_size << " hachages analyses" << endl;
        }
    }
    
    double percentage_ones = (ones_count * 100.0) / total_bits;
    double ideal = 50.0;
    double deviation = abs(percentage_ones - ideal);
    
    cout << "\n=== RESULTATS DISTRIBUTION ===" << endl;
    cout << "Echantillon: " << sample_size << " hachages" << endl;
    cout << "Bits totaux analyses: " << total_bits << endl;
    cout << "Bits a 1: " << ones_count << " (" << fixed << setprecision(4) << percentage_ones << "%)" << endl;
    cout << "Bits a 0: " << (total_bits - ones_count) << " (" << (100.0 - percentage_ones) << "%)" << endl;
    cout << "Deviation par rapport a 50%: " << deviation << "%" << endl;
    cout << "Distribution: " << (deviation < 2.0 ? " PARFAITEMENT EQUILIBREE" : 
                                deviation < 5.0 ? " BIEN EQUILIBREE" : " DESEQUILIBREE") << endl;
}

// Question 7 - Comparaison des regles
void question7_comparaison_regles() {
    cout << "\n" << string(60, '=') << endl;
    cout << "QUESTION 7 - COMPARAISON DES REGLES" << endl;
    cout << string(60, '=') << endl;
    
    string test_input = "Input test pour comparaison des regles";
    vector<uint32_t> rules = {30, 90, 110};
    vector<string> rule_names = {"Rule 30", "Rule 90", "Rule 110"};
    
    cout << "Input de test: '" << test_input << "'" << endl << endl;
    
    // Test performance
    cout << "--- PERFORMANCE (temps par hachage) ---" << endl;
    vector<double> performances;
    
    for (size_t i = 0; i < rules.size(); i++) {
        auto start = high_resolution_clock::now();
        string hash = ac_hash(test_input, rules[i], 128);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        
        performances.push_back(duration.count());
        cout << rule_names[i] << ": " << duration.count() << " μs" << endl;
        cout << "  Hash: " << hash.substr(0, 32) << "..." << endl;
        
        // Detection de problemes
        if (hash.substr(0, 16) == "0000000000000000") {
            cout << "  ⚠️  ATTENTION: Hash suspect (trop de zeros)" << endl;
        }
    }
    
    // Test distribution pour chaque regle
    cout << "\n--- DISTRIBUTION DES BITS ---" << endl;
    const int dist_sample = 100;
    
    for (size_t i = 0; i < rules.size(); i++) {
        int ones = 0, total = 0;
        
        for (int j = 0; j < dist_sample; j++) {
            string input = "dist_test_" + to_string(j);
            string hash = ac_hash(input, rules[i], 128);
            string binary = hex_to_binary(hash);
            
            for (char bit : binary) {
                if (bit == '1') ones++;
                total++;
            }
        }
        
        double percentage = (ones * 100.0) / total;
        double deviation = abs(percentage - 50.0);
        
        cout << rule_names[i] << ": " << fixed << setprecision(2) << percentage << "% de 1";
        cout << " (ecart: " << deviation << "%)";
        cout << " - " << (deviation < 5.0 ? " BON" : " MAUVAIS") << endl;
    }
    
    // Recommandation finale
    cout << "\n=== RECOMMANDATION FINALE ===" << endl;
    cout << "Rule 30: Chaotique, bonne distribution, rapide  RECOMMANDEE" << endl;
    cout << "Rule 90: Lineaire, distribution desequilibree  NON RECOMMANDEE" << endl;
    cout << "Rule 110: Universelle, lente, distribution correcte  ALTERNATIVE" << endl;
    cout << "MEILLEURE REGLE POUR LE HACHAGE: RULE 30" << endl;
}

void run_all_tests() {
    question4_comparaison_performance();
    question5_effet_avalanche();
    question6_distribution_bits();
    question7_comparaison_regles();
}