#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <vector>
#include <stdexcept>
#include <functional>
#include <utility>
#include <iterator>

#define INIT_CAPACITY 16
#define INIT_SIZE 0
#define MAX_LOAD_FACTOR 0.75
#define MIN_LOAD_FACTOR 0.25
#define MIN_CAPACITY 1

/*
* @brief Template parameters:
* - KeyT   : type of keys
* - ValueT : type of values
*/
template <class KeyT, class ValueT>

/*
* @class HashMap
* @brief A generic implementation of a hash map data structure
* @var buckets Pointer to a dynamically allocated array of buckets
* @var table_size Number of (key, value) pairs in the hash map
* @var table_capacity Number of buckets (always a power of 2)
*/
class HashMap {
public:
    // constructors and destructor

    /*
    * @brief Constructs an empty HashMap with INIT_CAPACITY buckets (default constructor)
    */
    HashMap();

    /*
    * @brief Constructs a HashMap from a key vector and a matching values vector
    * @param keys Vector of keys
    * @param values Vector of values
    */
    HashMap(std::vector<KeyT> keys, std::vector<ValueT> values);
    
    /*
    * @brief Constructs a HashMap from another HashMap (copy constructor)
    * @param hashmap HashMap to Construct another HashMap from
    */
    HashMap(const HashMap<KeyT, ValueT>& hashmap);

    /*
    * @brief Clears contents and deleted allocated buckets array (destructor)
    */
    virtual ~HashMap();

    //    methods

    /*
    * @brief Returns the size of the HashMap
    * @return Number of pairs stored in the HashMap
    */
    int size() const;

    /*
    * @brief Returns the capacity of the HashMap
    * @return Number of buckets in the HashMap
    */
    int capacity() const;

    /*
    * @brief Returns whether the HashMap is empty 
    * @return true if the HashMap contains no elements, false otherwise
    */
    bool empty() const;

    /*
    * @brief Inserts a (key, value) pair into the HashMap
    * @param key Key to insert
    * @param value Value to insert
    * @return true if insertion was successful, false otherwise
    */
    bool insert(const KeyT& key, const ValueT& value);

    /*
    * @brief Returns whether a given key is stored in the HashMap
    * @param key Key to look for
    * @return true is key exists in the HashMap, false otherwise
    */
    bool contains_key(const KeyT& key) const;

    /*
    * @brief Accesses the value of a given key
    * @param key Key look up the value of
    * @return Reference to the values mapped to a given key
    * @throws std::runtime_error if key does not exist in HashMap
    *
    */
    ValueT& at(const KeyT& key);

    /*
    * @brief Const at()
    */
    const ValueT& at(const KeyT& key) const;

    /*
    * @brief Erases a pair with a given key from the HashMap
    * @param key Key in the pair that should be erased
    * @return true if erasure was successful, false otherwise
    */
    bool virtual erase(const KeyT& key);

    /*
    * @brief Load factor getter
    * @return double representing the HashMap's current load factor
    */
    double get_load_factor() const;

    /*
    * @brief Bucket size getter
    * @param key Key that should be stored in the bucket to find the size of
    * @return int representing the number of pairs currently stored
    * in bucket that contains a pair with a given key
    * @throws std::runtime_error if the key does not exist in the HashMap
    */
    int bucket_size(const KeyT& key) const;

    /*
    * @brief Bucket index getter
    * @param key Key that should be stored in the bucket to find the index of
    * @return int representing the index of a bucket that contains a pair 
    * with a given key
    * @throws std::runtime_error if the key does not exist in the HashMap
    */
    int bucket_index(const KeyT& key) const;

    /*
    * @brief Removes all the pairs from the hashmap, keeping the current capacity
    */
    void clear();

//    operators

    /*
    * @brief Copies a given HashMap and assigns the data to this HashMap
    * @param hashmap HashMap to copy and assign
    * @return Reference to this HashMap
    */
    HashMap& operator= (const HashMap<KeyT, ValueT>& hashmap);

    /*
    * @brief const operator[] - delegates to at()
    */
    const ValueT& operator[](const KeyT& key) const;

    /*
    * @brief Inserts a default ValueT if key does not exist in hashmap 
    * and returns its value
    * @param key Key to find (or insert) and return the value of
    * @return Reference to the value mapped to the given key
    */
    ValueT& operator[](const KeyT& key);

    /*
    * @brief Checks if a given HashMap is equal to this HashMap (contain the same (key, value) pairs)
    * @param hashmap Hashmap to check equality with 
    * @return true if HashMaps are equal, false otherwise
    */
    bool operator==(const HashMap<KeyT, ValueT>& hashmap) const;

    /*
    * @brief Checks if a given HashMap is not equal to this HashMap
    * @param hashmap Hashmao to check inequality with
    * @return true if HashMaps are unequal, false otherwise
    */
    bool operator!=(const HashMap<KeyT, ValueT>& hashmap) const;

    /*
    * @class ConstIterator
    * @brief A forward-only const iterator over (key, value) pairs 
    * stored in the HashMap
    * @var _hashmap HashMap to iterate over
    * @var _bucket_index Index of the current bucket
    * @var _pair_index index of the current pair
    * @note Iteration sequence: bucket 0..capacity - 1. in each bucket pair 0..size - 1
    */
    class ConstIterator {
        friend class HashMap<KeyT, ValueT>;

    public:

        // typedefs
        typedef std::pair<KeyT, ValueT> value_type;
        typedef const value_type &reference;
        typedef const value_type *pointer;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;

        /*
        * @brief Pre-increment: advances to the next pair in the current bucket, 
        * or the first element in the next non-empty bucket, 
        * if already at end(), doesn't advance 
        * @return ConstIterator that holds the current pair (before advancing)
        */
        ConstIterator &operator++ () {
            if (_bucket_index >= _hashmap.table_capacity) return *this;
            ++_pair_index;
            while (_bucket_index < _hashmap.table_capacity) {
                if (_pair_index < _hashmap.buckets[_bucket_index].size()) return *this;
                ++_bucket_index;
                _pair_index = 0;
                if (_bucket_index < _hashmap.table_capacity && !_hashmap.buckets[_bucket_index].empty()) return *this;
            }
            _pair_index = 0;
            return *this;
        }

        /*
        * @brief Post-increment: Advances to the next pair in the current bucket, 
        * or the first element in the next non-empty bucket, 
        * if already at end(), doesn't advance 
        * @return ConstIterator that holds the current pair (after advancing)
        */
        ConstIterator operator++ (int) {
            ConstIterator it (*this);
            this->operator++();
            return it;
        }

        /*
        * @brief Checks if a given ConstIterator is eqaul to this ConstIterator -
        * same HashMap and same position
        * @param rhs ConstIterator to check equality with
        * @return true if the iterators are equal, false otherwise
        */
        bool operator== (const ConstIterator& rhs) const {
            return (&_hashmap == &rhs._hashmap) &&
            (_bucket_index == rhs._bucket_index) &&
            (_pair_index == rhs._pair_index);
        }

        /*
        * @brief Checks if a given ConstIterator is not eqaul to this ConstIterator
        * @param rhs ConstIterator to check inequality with
        * @return true if the iterators are unequal, false otherwise
        */
        bool operator != (const ConstIterator &rhs) const {
            return !operator== (rhs);
        }
        
        /*
        * @brief Dereference operator
        * @return Const reference to the current pair
        * throws std::out_of_range when trying to dereference end()
        */
        reference operator* () const {
            if (_bucket_index >= _hashmap.table_capacity) {
                throw std::out_of_range("HashMap iterator: dereference of end()");
            }
            if (_pair_index >= _hashmap.buckets[_bucket_index].size()) {
                throw std::out_of_range("HashMap iterator: invalid pair index");
            }
            return _hashmap.buckets[_bucket_index][_pair_index];
        }

        /*
        * @brief Pointer operator
        * @return Pointer to current (key, value) pair 
        */
        pointer operator-> () const {
            return &(**this);
        };

    private:
        const HashMap<KeyT, ValueT>& _hashmap;
        size_t _bucket_index;
        size_t _pair_index;

        /*
        * @brief Costructs a ConstIterator from a given HashMap at a given position
        * @param hashmap HashMap to iterate over
        * @param bucket_index Current bucket index
        * @param pair_index Current pair index
        */
        ConstIterator(const HashMap<KeyT, ValueT>& hashmap,
            size_t bucket_index, size_t pair_index) :
            _hashmap(hashmap), _bucket_index(bucket_index),
            _pair_index(pair_index) {
        }

    };

    using const_iterator = ConstIterator;
    
    /*
    * @brief const begin()
    */
    const_iterator cbegin () const {
        int i = 0;
        while (i < table_capacity && buckets[i].empty()) {
            i++;
        }
        if (i == table_capacity) {
            return cend();
        }
        return ConstIterator(*this, i, 0);
    }

    /*
    * @brief const end()
    */
    const_iterator cend () const {
        return ConstIterator(*this, table_capacity, 0);
    }

    /*
    * @brief Returns iterator to first pair (skip empty buckets)
    * @return ConstIterator after being set to first pair
    */
    const_iterator begin () const {
        return cbegin();
    }
    /*
    * @brief Returns iterator to end position (one past the last pair)
    * @return ConstIterator after being set to end position
    */
    const_iterator end () const {
        return cend();
    }

private:
    std::vector<std::pair<KeyT, ValueT>>* buckets;
    int table_size;
    int table_capacity;

};

// ==================== Implementation ====================

template <class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap() {
    table_size = INIT_SIZE;
    table_capacity = INIT_CAPACITY;
    buckets = new std::vector<std::pair<KeyT, ValueT>> [INIT_CAPACITY];
}


template <class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(std::vector<KeyT> keys,
                               std::vector<ValueT> values) {
    // validate value vector and key vector size match
    if (keys.size() != values.size()) {
        throw std::runtime_error("vector sizes don't match!");
    } else {
        // insert all (key, value) pairs
        table_size = INIT_SIZE;
        table_capacity = INIT_CAPACITY;
        buckets = new std::vector<std::pair<KeyT, ValueT>> [INIT_CAPACITY];
        for (size_t i = 0; i < keys.size(); i++) {
            bool res = insert(keys[i], values[i]);
            if (!res) {
                (*this)[keys[i]] = values[i];
            }
        }
    }
}


template <class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap<KeyT, ValueT>& hashmap) {
    table_capacity = hashmap.capacity();
    table_size = hashmap.size();
    buckets = new std::vector<std::pair<KeyT, ValueT>> [table_capacity];
    for (int i = 0; i < table_capacity; i++) {
        for (size_t j = 0; j < hashmap.buckets[i].size(); j++) {
           buckets[i].push_back(hashmap.buckets[i][j]);
        }
    }
}


template <class KeyT, class ValueT>
HashMap<KeyT, ValueT>::~HashMap() {
    clear();
    delete [] buckets;
}


template <class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::size() const {
    return table_size;
}


template <class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::capacity() const {
    return table_capacity;
}


template <class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::empty() const {
    return (table_size == 0);
}


template <class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::insert(const KeyT& key, const ValueT& value) {
    // validate key does not exist in HashMap
    if (contains_key(key)) {
        return false;
    }
    else {
        // insert (key, value) pair
        std::hash<KeyT> hash_key;
        std::size_t bucket_index = hash_key(key) & (table_capacity - 1);
        auto pair = std::pair<KeyT, ValueT> (key, value);
        buckets[bucket_index].push_back(pair);
        table_size++;
        // resize HashMap and rehash pairs 
        while (get_load_factor() > MAX_LOAD_FACTOR) {
            auto temp = new std::vector<std::pair<KeyT,
            ValueT>>[table_capacity * 2];
            for (int i = 0; i < table_capacity; i++) {
                for (size_t j = 0; j < buckets[i].size(); j++) {
                    std::size_t bucket_index = hash_key(buckets[i][j].first)
                            & ((table_capacity * 2) - 1);
                    temp[bucket_index].push_back(buckets[i][j]);
                }
            }
            delete [] buckets;
            buckets = temp;
            table_capacity *= 2;
        }
        return true;
    }
}


template <class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::contains_key(const KeyT& key) const {
    std::hash<KeyT> hash_key;
    std::size_t bucket_index = hash_key(key) & (table_capacity - 1);
    for (size_t j = 0; j < buckets[bucket_index].size(); j++) {
        if (buckets[bucket_index][j].first == key) {
            return true;
        }
    }
    return false;
}


template <class KeyT, class ValueT>
ValueT& HashMap<KeyT, ValueT>::at(const KeyT& key) {
    std::hash<KeyT> hash_key;
    int bucket = hash_key(key) & (table_capacity - 1);
    for (size_t i = 0; i < buckets[bucket].size(); i++) {
        if (buckets[bucket][i].first == key) return buckets[bucket][i].second;
    }
    throw std::runtime_error("no such key exists!");
}


template <class KeyT, class ValueT>
const ValueT& HashMap<KeyT, ValueT>::at(const KeyT& key) const {
    std::hash<KeyT> hash_key;
    int bucket = hash_key(key) & (table_capacity - 1);
    for (size_t i = 0; i < buckets[bucket].size(); i++) {
        if (buckets[bucket][i].first == key) return buckets[bucket][i].second;
    }
    throw std::runtime_error("no such key exists!");
}


template <class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::erase(const KeyT& key) {
    // validate key exists in HashMap
    if (!contains_key(key)) {
        return false;
    }
    else {
        // erase (key, value) pair from HahsMap
        int bucket_idx = bucket_index(key);
        auto& bucket = buckets[bucket_idx];
        for (size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].first == key) {
                bucket.erase(bucket.begin() + i);
                table_size--;
                break;
            }
        }
        // resize HashMap and rehash pairs 
        while ((get_load_factor() < MIN_LOAD_FACTOR) &&
        (table_capacity > MIN_CAPACITY)) {
            auto temp = new std::vector<std::pair<KeyT,
            ValueT>>[table_capacity / 2];
            std::hash<KeyT> hash_key;
            for (int i = 0; i < table_capacity; i++) {
                for (size_t j = 0; j < buckets[i].size(); j++) {
                    std::size_t bucket_index = hash_key(buckets[i][j].first)
                            & ((table_capacity / 2) - 1);
                    temp[bucket_index].push_back(buckets[i][j]);
                }
            }
            delete [] buckets;
            buckets = temp;
            table_capacity /= 2;
        }
        return true;
    }
}


template <class KeyT, class ValueT>
double HashMap<KeyT, ValueT>::get_load_factor() const {
    double load_factor = (double)table_size / (double)table_capacity;
    return load_factor;
}


template <class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucket_size(const KeyT& key) const {
    if (contains_key(key)) {
        int bucket = bucket_index(key);
        return static_cast<int>(buckets[bucket].size());
    }
    else {
        throw std::runtime_error("no such key exists!");
    }
}


template <class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucket_index(const KeyT& key) const {
    if (contains_key(key)) {
        std::hash<KeyT> hash_key;
        size_t bucket_index = hash_key(key) & (static_cast<size_t>(table_capacity) - 1);
        return static_cast<int>(bucket_index);
    }
    else {
        throw std::runtime_error("no such key exists!");
    }
}


template <class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::clear() {
    for (int i = 0; i < table_capacity; i++) {
        buckets[i].clear();
    }
    table_size = 0;
}


template <class KeyT, class ValueT>
HashMap<KeyT, ValueT>& HashMap<KeyT, ValueT>::operator=(const HashMap<KeyT, ValueT>& hashmap) {
    if (this == &hashmap) return *this;
    HashMap tmp(hashmap);
    std::swap(buckets, tmp.buckets);
    std::swap(table_size, tmp.table_size);
    std::swap(table_capacity, tmp.table_capacity);
    return *this;
}


template <class KeyT, class ValueT>
const ValueT& HashMap<KeyT, ValueT>::operator[](const KeyT& key) const {
    return at(key);
}


template <class KeyT, class ValueT>
ValueT& HashMap<KeyT, ValueT>::operator[](const KeyT& key) {
    // if key is not in HashMap - add it
    if (!contains_key(key)) {
        insert(key, ValueT());
    }
    // find and return value mapped to given key
    int bucket = bucket_index(key);
    size_t index = 0;
    for (size_t i = 0; i < buckets[bucket].size(); i++) {
        if (buckets[bucket][i].first == key) {
            index = i;
        }
    }
    return buckets[bucket][index].second;
}


template <class KeyT, class ValueT>
bool HashMap<KeyT,ValueT>::operator==(const HashMap<KeyT, ValueT>& hashmap) const {
    // validate HashMaps sizes match
    if (table_size != hashmap.size()) return false;
    
    for (int i = 0; i < table_capacity; i++) {
        for (const auto& [key, value] : buckets[i]) {
            // validate HashMaps have the same keys
            if (!hashmap.contains_key(key)) return false;
            // validate HashMaps have the same values mapped to same keys
            if (hashmap.at(key) != value) return false;
        }
    }
    return true;
}


template <class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator!=(const HashMap<KeyT, ValueT>& hashmap) const {
    return !(*this == hashmap);
}

#endif //HASHMAP_HPP
