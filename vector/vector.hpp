#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <ostream>
#include <stdexcept>

template<typename T>
class vector{
    T* data;
    size_t size, capacity;

    void clean_up();

    public:
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
};

#endif
        
        