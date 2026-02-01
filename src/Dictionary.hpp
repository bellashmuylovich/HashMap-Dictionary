#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <stdexcept>
#include <utility>

#include "HashMap.hpp"

/*
* @class InvalidKey
* @brief Exception thrown by Dictionary::erase when a key does not exist
*/
class InvalidKey : public std::invalid_argument {
public:

    /*
    * @brief Constructs an exception with a default message
    */
    InvalidKey() : std::invalid_argument("Invalid Key!") {}
    
    /*
    * @brief Constructs an exception with a custom message
    * @param message Message to show in exception
    */
    explicit InvalidKey(const std::string& message) : std::invalid_argument(message) {}
};

/*
* @class Dictionary
* @brief a custom HashMap that maps string keys to strings
*/
class Dictionary : public HashMap<std::string, std::string> {
public:

//    constructors

    /*
    * @brief Constructs an empty dictionary (default constructor)
    */
    Dictionary() = default;

    /*
    * @brief Constructs a Dictionary from a vector of string keys 
    * and a matching vector of string values
    * @param keys Vector od string keys
    * @param values Vecto of string values
    */
    Dictionary(std::vector<std::string> keys,
               std::vector<std::string> values);

    /*
    * @brief Constructs a Dictionary from another Dictionary (copy constructor)
    * @param dictionary Dictionary to construct another Dictionary from
    */
    Dictionary(const Dictionary& dictionary);

//    methods

    /*
    * @brief Erases a pair with a given key from the Dictionary
    * @param key Key in the pair that should be erased
    * @return true if erasure was successful, false otherwise
    * @throws InvalidKey if key does not exist in Dictionary
    */
    bool erase(const std::string& key) override;

    template <class Iterator>
    /*
    * @brief Bulk updates from iterator range of (key, value) pairs,
    * if pair does not exist - inserts it
    * @param begin Start of update range
    * @param end End of update range
    */
    void update(Iterator begin, Iterator end);
};

// ==================== Implementation ====================
inline Dictionary::Dictionary(std::vector<std::string> keys,
    std::vector<std::string> values)
    : HashMap<std::string, std::string>(std::move(keys), std::move(values)) {}

inline Dictionary::Dictionary(const Dictionary& dictionary) :
    HashMap<std::string, std::string>(dictionary){}

inline bool Dictionary::erase(const std::string& key) {
    // validate key exists in Dictionary
    if (!contains_key(key)) {
        throw InvalidKey();
    }
    // attempt erasure
    return HashMap<std::string, std::string>::erase(key);
}

template <class Iterator>
void Dictionary::update(Iterator begin, Iterator end) {
    for (auto i = begin; i != end; i++) {
        (*this)[i->first] = i->second;
    }
}

#endif //DICTIONARY_HPP
