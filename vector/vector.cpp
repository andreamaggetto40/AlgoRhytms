#include "vector.hpp"

template<typename T>
vector<T>::vector() : size(0), capacity(10), data(new T[capacity]){};

template<typename T>
vector<T>::vector(const T& init, size_t init_size) : size(init_size), capacity(size * 2), data(new T[capacity]){
    for(size_t i = 0; i < init_size; ++i) data[i] = init;
};

template<typename T>
vector<T>::vector(const vector<T>& v) : size(v.size), capacity(v.capacity), data(new T[capacity]){
    for(size_t i = 0; i < v.size; ++i) data[i] = v.data[i];
};

template<typename T>
vector<T>::vector(vector<T>&& v) : size(v.size), capacity(v.capacity), data(v.data){
    v.data = nullptr;
    v.size = v.capacity = 0;
};

template<typename T>
vector<T>::~vector(){
    v_delete();
};

template<typename T>
size_t vector<T>::get_size() const{
    return size;
};

template<typename T>
void vector<T>::push_back(const T& el){
    if(size >= capacity){
        capacity *= 2;

        T* data_restore = nullptr;
        try{
            data_restore = new T[capacity];
        }
        catch(const std::bad_alloc& ex){
            throw std::runtime_error("Fail to locate dynamic memory");
        }
        
        for(size_t i = 0; i < size; ++i) data_restore[i] = std::move(data[i]);
        delete data;
        data = data_restore;
    }
    data[size] = el;
    ++size;
};

template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& v){
    if(this != &v){
        T* new_data = nullptr;

        try{
            new_data = new T[v.capacity];
            for(size_t i = 0; i < v.size; ++i) new_data[i] = v.data[i];
        }
        catch(const std::bad_alloc ex){
            delete[] new_data;
            throw;
        }
        v_delete();
        data = new_data;
        size = v.size;
        capacity = v.capacity;
    }
    return *this;
};

template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& v) noexcept{
    if(this != &v){
        v_delete();

        data = v.data;
        size = v.size;
        capacity = v.capacity;

        v.data = nullptr;
        size = capacity = 0;
    }
    return *this;
};

template<typename T>
void vector<T>::v_delete(){
    if(data){
        for(size_t i = 0; i < size; ++i) data[i].~T();
        size = capacity = 0;
    }
};










    

