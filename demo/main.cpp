#include <iostream>
#include <vector>
#include <string>

#include "HashMap.hpp"
#include "Dictionary.hpp"

/*
* @brief Simple demonstration of HashMap and Dictionary 
*/
int main() {
    // ==================== HashMap demo ====================
    std::cout << "=== HashMap demo ===\n";

    HashMap<int, std::string> hashmap;
    std::cout << std::boolalpha;

    auto dump = [](const auto& m, const char* name) {
        std::cout << name
            << " size= " << m.size()
            << " capacity= " << m.capacity()
            << " load factor= " << m.get_load_factor()
            << "\n";
        };

    dump(hashmap, "empty hashmap");

    // insert + lookup
    for (int i = 0; i < 16; i++) {
        hashmap.insert(i, "a");
    }
    std::cout << "hashmap[100] default-inserts(empty string): \"" << hashmap[100] << "\"\n";

    dump(hashmap, "after inserting 0..15 and 100");
    std::cout << "contains 1? " << hashmap.contains_key(1) << "\n";
    std::cout << "at(1) = " << hashmap.at(1) << "\n";

    // lookup failure
    try { hashmap.at(-1); }
    catch (const std::exception& e) {
        std::cout << "[expected] at(-1) threw: " << e.what() << "\n";
    }

    // erase + resize
    for (int i = 0; i < 9; i++) {
        hashmap.erase(i);
    }

    dump(hashmap, "after erasing 0..8");

    // copy + equality
    HashMap<int, std::string> copy(hashmap);
    std::cout << "hashmap == copy? " << (hashmap == copy) << "\n";
    copy[9] = "b"; 
    std::cout << "hashmap == copy after change? " << (hashmap == copy) << "\n";

    // iteration 
    std::cout << "iterating (first few):\n";
    int shown = 0;
    for (const auto& [key, value] : hashmap) {
        std::cout << key << " -> " << value << "\n";
        if (shown++ == 3) break;
    }

    // ==================== Dictionaty demo ====================
    std::cout << "=== Dictionary demo ===\n";

    Dictionary dict;
    dict["apple"] = "fruit";
    std::cout << "dict['apple'] = " << dict.at("apple") << "\n";
    try { dict.erase("missing"); }
    catch (const InvalidKey& e) {
        std::cout << "[expected] dict.erase('missing') threw: " << e.what() << "\n";
    }
}