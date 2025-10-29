#include "ac_hash.h"
#include "ac_core.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// 2.2 Conversion du texte en bits
vector<int> string_to_bits(const string& input) {
    vector<int> bits;
    bits.reserve(input.length() * 8);
    
    for (unsigned char c : input) {
        for (int i = 7; i >= 0; --i) {
            bits.push_back((c >> i) & 1);
        }
    }
    return bits;
}

// Conversion des bits en hexadecimal
string bits_to_hex(const vector<int>& bits) {
    stringstream ss;
    ss << hex << uppercase;
    
    for (size_t i = 0; i < bits.size(); i += 4) {
        int nibble = 0;
        for (int j = 0; j < 4 && (i + j) < bits.size(); ++j) {
            nibble = (nibble << 1) | bits[i + j];
        }
        ss << nibble;
    }
    return ss.str();
}

// Compression vers 256 bits
vector<int> compress_to_256_bits(const vector<int>& bits) {
    vector<int> result(256, 0);
    
    if (bits.size() <= 256) {
        // Copie directe
        for (size_t i = 0; i < bits.size(); ++i) {
            result[i] = bits[i];
        }
    } else {
        // Compression par XOR
        for (size_t i = 0; i < bits.size(); ++i) {
            result[i % 256] ^= bits[i];
        }
    }
    
    return result;
}

// 2.1 Fonction de hachage principale
string ac_hash(const string& input, uint32_t rule, size_t steps) {
    // Conversion de l'entree en bits
    vector<int> state = string_to_bits(input);
    
    // Padding à 256 bits minimum
    if (state.size() < 256) {
        state.resize(256, 0);
    }
    
    // Creation et evolution de l'automate
    CellularAutomaton ca;
    ca.init_state(state);
    ca.evolve_steps(rule, steps);
    
    // Compression vers 256 bits exactement
    vector<int> final_state = compress_to_256_bits(ca.get_state());
    
    // Conversion en hexadecimal
    return bits_to_hex(final_state);
}

// 2.4 Test de collisions (VERSION CORRIGeE)
void test_hash_collisions() {
    cout << "\n--- Test 2.4 - Collisions de hash ---" << endl;
    
    // Utilisation de pairs au lieu de structured binding
    vector<pair<string, string>> test_cases;
    test_cases.push_back(make_pair("Hello", "hello"));
    test_cases.push_back(make_pair("Hello", "Hello!"));
    test_cases.push_back(make_pair("abc", "abd"));
    test_cases.push_back(make_pair("", " "));
    
    bool all_different = true;
    
    for (const auto& test_case : test_cases) {
        string input1 = test_case.first;
        string input2 = test_case.second;
        
        string hash1 = ac_hash(input1, 30, 128);
        string hash2 = ac_hash(input2, 30, 128);
        
        cout << "'" << input1 << "' -> " << hash1.substr(0, 16) << "..." << endl;
        cout << "'" << input2 << "' -> " << hash2.substr(0, 16) << "..." << endl;
        
        if (hash1 == hash2) {
            cout << "COLLISION DeTECTeE!" << endl;
            all_different = false;
        } else {
            cout << " Hashs differents" << endl;
            
            // Calcul du pourcentage de difference
            int diff_count = 0;
            size_t min_len = min(hash1.length(), hash2.length());
            for (size_t i = 0; i < min_len; i++) {
                if (hash1[i] != hash2[i]) diff_count++;
            }
            double diff_percent = (diff_count * 100.0) / min_len;
            cout << "   Difference: " << diff_count << "/" << min_len << " caracteres (" 
                 << fixed << setprecision(1) << diff_percent << "%)" << endl;
        }
        cout << endl;
    }
    
    if (all_different) {
        cout << " SUCCES: Aucune collision detectee!" << endl;
    }
}

// Test avec differentes regles
void test_different_rules() {
    cout << "\n--- Test avec differentes regles ---" << endl;
    
    string input = "Blockchain Master IASD";
    
    cout << "Input: '" << input << "'" << endl;
    cout << endl;
    
    cout << "Rule 30:  " << ac_hash(input, 30, 128) << endl;
    cout << "Rule 90:  " << ac_hash(input, 90, 128) << endl;
    cout << "Rule 110: " << ac_hash(input, 110, 128) << endl;
    
    // Verification que les regles produisent des resultats differents
    string h30 = ac_hash(input, 30, 128);
    string h90 = ac_hash(input, 90, 128);
    string h110 = ac_hash(input, 110, 128);
    
    if (h30 != h90 && h30 != h110 && h90 != h110) {
        cout << " SUCCeS: Chaque regle produit un hash unique" << endl;
    } else {
        cout << "ATTENTION: Certaines regles produisent le même hash" << endl;
    }
}

// Test de la conversion texte->bits
void test_conversion() {
    cout << "\n--- Test conversion texte->bits ---" << endl;
    
    string test_str = "AB";
    vector<int> bits = string_to_bits(test_str);
    
    cout << "Texte: '" << test_str << "'" << endl;
    cout << "Bits: ";
    for (size_t i = 0; i < bits.size(); i++) {
        cout << bits[i];
        if ((i + 1) % 8 == 0) cout << " ";
    }
    cout << endl;
    
    // Verification
    cout << "A (65): 01000001" << endl;
    cout << "B (66): 01000010" << endl;
}

// Demonstration complete Question 2
void question2_demo() {
    cout << "\n" << string(60, '=') << endl;
    cout << "QUESTION 2 - FONCTION DE HACHAGE AC_HASH" << endl;
    cout << string(60, '=') << endl;
    
    cout << "2.1 Fonction ac_hash() implementee" << endl;
    cout << "2.2 Conversion texte->bits: 8 bits par caractere" << endl;
    cout << "2.3 Processus 256 bits: padding + compression XOR" << endl;
    cout << "2.4 Tests de collisions en cours..." << endl;
    
    test_conversion();
    test_hash_collisions();
    test_different_rules();
    
    // Test de proprietes de base
    cout << "\n--- Tests de proprietes ---" << endl;
    cout << "Chaine vide: " << ac_hash("", 30, 128) << endl;
    cout << "Un caractere: " << ac_hash("A", 30, 128) << endl;
    
    string long_input(1000, 'X');
    string long_hash = ac_hash(long_input, 30, 128);
    cout << "Longue chaine (1000 'X'): " << long_hash.substr(0, 32) << "..." << endl;
    cout << "Longueur du hash: " << long_hash.length() << " caracteres hexadecimaux" << endl;
}