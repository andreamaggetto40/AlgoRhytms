#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <ostream>
#include <stdexcept>
#include <mutex>

/**
 * @file vector.hpp
 * @brief Custom templated, multithreaded, and thread-safe vector class definition.
 *
 * This vector class is a handcrafted implementation designed to emulate the behavior and functionalities of the STL vector in C++. It provides dynamic array capabilities and is designed to be versatile across multiple data types. The implementation ensures thread safety through mutexes and lock guards, allowing for concurrent access and modifications without data races or inconsistencies.
 *
 * @note For utilizing the functionalities of this vector class, it's imperative to include this file.
 * 
 * @author Andrea Maggetto
 */

template<typename T>
class vector{
    T* data;
    size_t size, capacity;
    mutable std::mutex mtx_;

    void clean_up();
    void copy_from(const vector<T>& v);

    public:
        class iterator;
        class const_iterator;

        vector();
        vector(const T& init, size_t init_size);
        vector(const vector<T>& v);
        vector(vector<T>&& v);
        ~vector();  

        vector<T>& operator=(const vector<T>& v);
        vector<T>& operator=(vector<T>&& v) noexcept;
        const T& operator[](const size_t index) const;
        T& operator[](const size_t index);
        
        bool operator==(const vector<T>& v) const;
        bool operator!=(const vector<T>& v) const;

        size_t get_size() const;
        void push_back(const T& el);
        T& at(const size_t index) const;
        bool empty() const;
        T& back() const;
        T& front() const;
        void clear();
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
};

#endif
        
        