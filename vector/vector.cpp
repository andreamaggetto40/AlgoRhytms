#include "vector.hpp"

template<typename T>
vector<T>::vector() : size(0), capacity(10), data(new T[capacity]){};

template<typename T>
vector<T>::vector(const T& init, size_t init_size) : size(init_size), capacity(init_size * 2), data(new T[init_size * 2]){
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
    if(size == capacity){
        size_t new_capacity = (capacity == 0) ? 0 : capacity * 2;
        
        T* data_restore = new T[new_capacity];

        for(size_t i = 0; i < size; ++i) data_restore[i] = std::move(data[i]);

        delete[] data;
        data = data_restore;
        capacity = new_capacity;
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
        v.size = v.capacity = 0;
    }
    return *this;
};

template<typename T>
T& vector<T>::at(const size_t index) const{
    if(index >= size) throw std::out_of_range("Out of range");
    return data[index];
};

template<typename T>
bool vector<T>::empty() const{
    return size == 0;
};

template<typename T>
T& vector<T>::back() const{
    if(size == 0) throw std::out_of_range("Out of range!");
    return data[size - 1];
};

template<typename T>
T& vector<T>::front() const{
    if(size == 0) throw std::out_of_range("Out of range!");
    return data[0];
}

template<typename T>
bool vector<T>::operator==(const vector<T>& v) const{
    if(this != &v){
        if(size != v.size) return false;
        for(size_t i = 0; i < size; ++i){
            if(data[i] != v.data[i]) return false;
        }
    }
    return true;
};

template<typename T>
bool vector<T>::operator!=(const vector<T>& v) const{
    return !(*this == v);
};

template<typename T>
void vector<T>::clear(){
    v_delete();
    capacity = 10;

    try{
        data = new T[capacity];
    }
    catch(const std::bad_alloc& ex){
        throw std::runtime_error("Failed to allocate dynamic memory");
    }
};

template<typename T>
void vector<T>::v_delete(){
    if(data){
        for(size_t i = 0; i < size; ++i) data[i].~T();
        delete[] data;
        size = capacity = 0;
    }
};

template<typename T>
void vector<T>::print() const{
    for(size_t i = 0; i < size; ++i) std::cout << data[i] << " ";
};

int main(int argc, char const *argv[])
{
    
}










    

