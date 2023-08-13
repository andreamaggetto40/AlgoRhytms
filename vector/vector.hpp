#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <ostream>
#include <stdexcept>

/*
    @file vector.hpp    
    @brief templated vector class definition. vector is a class which aims to showcase how a dynamic C++ like vector is implemented from scratch.

    @note in order to actually use the vector class, this file must be included.

    @author Andrea Maggetto
*/

template<typename T>
class vector{
    T* data;
    size_t size, capacity;

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
        
        