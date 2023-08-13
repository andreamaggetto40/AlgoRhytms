#include "vector.hpp"

/*
    @file vector.cpp
    @brief The current cpp source file contains the actual implementation of the vector class methods    
*/

/**
 * @brief Default constructor for the vector class.
 * Initializes an empty vector with a default capacity of 10.
 */
template<typename T>
vector<T>::vector() : size(0), capacity(10), data(new T[capacity]){};

/**
 * @brief Constructor for the vector class that initializes with a given element and size.
 * 
 * @param init The initial value for all elements.
 * @param init_size The size of the vector to be created.
 */
template<typename T>
vector<T>::vector(const T& init, size_t init_size) : size(init_size), capacity(init_size * 2), data(new T[init_size * 2]){
    for(size_t i = 0; i < init_size; ++i) data[i] = init;
};

/**
 * @brief Copy constructor.
 *
 * Creates a new vector by copying the contents of another vector.
 *
 * @param v The vector to be copied.
 */
template<typename T>
vector<T>::vector(const vector<T>& v) : size(v.size), capacity(v.capacity), data(new T[capacity]){
    for(size_t i = 0; i < v.size; ++i) data[i] = v.data[i];
};

/**
 * @brief Move constructor.
 *
 * Creates a new vector by taking ownership of the contents of another vector. The source vector
 * will be left in a valid but unspecified state.
 *
 * @param v The vector to be moved.
 */
template<typename T>
vector<T>::vector(vector<T>&& v) : size(v.size), capacity(v.capacity), data(v.data){
    v.data = nullptr;
    v.size = v.capacity = 0;
};

/**
 * @brief Destructor.
 *
 * Deallocates the memory used by the vector and sets its size and capacity to zero.
 */
template<typename T>
vector<T>::~vector(){
    clean_up();
};

/**
 * @brief Returns the current size of the vector.
 *
 * @return The number of elements in the vector.
 * 
 *  @note The time complexity is O(1)
 */
template<typename T>
size_t vector<T>::get_size() const{
    return size;
};

/**
 * @brief Adds an element to the end of the vector.
 *
 * If the vector is at its capacity, it will be resized to accommodate the new element.
 *
 * @param el The element to be added.
 * 
 * @note the time complexity is O(1) amortized
 */
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

/**
 * @brief Copy assignment operator.
 *
 * Copies the contents of another vector into this vector.
 *
 * @param v The vector to be copied.
 * @return Reference to the modified vector.
 * 
 * @note the time complexity of the function is O(n)
 */
template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& v){
    if(this != &v){
        clean_up();

        data = new T[v.capacity];
        copy_from(v);
        size = v.size;
        capacity = v.capacity;
    }
    return *this;
};

/**
 * @brief Move assignment operator.
 *
 * Moves the contents of another vector into this vector, leaving the source vector in a valid but unspecified state.
 *
 * @param v The vector to be moved.
 * @return Reference to the modified vector.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& v) noexcept{
    if(this != &v){
        clean_up();

        data = v.data;
        size = v.size;
        capacity = v.capacity;

        v.data = nullptr;
        v.size = v.capacity = 0;
    }
    return *this;
};

/**
 * @brief Accesses the element at the specified index with bounds checking.
 *
 * @param index The index of the element to be accessed.
 * @return Reference to the element.
 * @throws std::out_of_range If the index is out of range.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
T& vector<T>::at(const size_t index) const{
    if(index >= size) throw std::out_of_range("Out of range");
    return data[index];
};

/**
 * @brief Checks if the vector is empty.
 *
 * @return True if the vector is empty, otherwise false.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
bool vector<T>::empty() const{
    return size == 0;
};

/**
 * @brief Accesses the last element of the vector.
 *
 * @return Reference to the last element.
 * @throws std::out_of_range If the vector is empty.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
T& vector<T>::back() const{
    if(size == 0) throw std::out_of_range("Out of range!");
    return data[size - 1];
};

/**
 * @brief Accesses the first element of the vector.
 *
 * @return Reference to the first element.
 * @throws std::out_of_range If the vector is empty.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
T& vector<T>::front() const{
    if(size == 0) throw std::out_of_range("Out of range!");
    return data[0];
}

/**
 * @brief Equality comparison operator.
 *
 * Checks if two vectors are equal by comparing their elements.
 *
 * @param v The vector to be compared.
 * @return True if the vectors are equal, otherwise false.
 * 
 * @note the time complexity is O(n)
 */
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

/**
 * @brief Inequality comparison operator.
 *
 * Checks if two vectors are not equal by comparing their elements.
 *
 * @param v The vector to be compared.
 * @return True if the vectors are not equal, otherwise false.
 * 
 * @note the time complexity is O(n)
 */
template<typename T>
bool vector<T>::operator!=(const vector<T>& v) const{
    return !(*this == v);
};

/**
 * @brief Clears the contents of the vector.
 *
 * Deallocates memory used by the vector and sets its capacity to 10.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
void vector<T>::clear(){
    clean_up();

    capacity = 10;

    data = new T[capacity];
};

/**
 * @brief Iterator class for the vector.
 *
 * This class provides a way to iterate over the elements of the vector.
 */
template<typename T>
class vector<T>::iterator{
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using point_diff = ptrdiff_t;

        iterator(pointer ptr) : current(ptr){};

        bool operator==(iterator& other){
            return current == other.current;
        }
        bool operator!=(iterator& other){
            return !(current == other.current;)
        }
        iterator& operator++(){
            ++current;
            return *this;
        }
        iterator operator++(int){
            iterator temp = *this;
            ++current;
            return temp;
        }
        reference operator*() const{
            return *current;
        }
        pointer operator->() const{
            return current;
        }
    private:
        pointer current;
};

/**
 * @brief Constant Iterator class for the vector.
 *
 * This class provides a way to iterate over the elements of the vector while preventing modification of the elements.
 */
template<typename T>
class vector<T>::const_iterator{
    public:
        using iterator_type = std::forward_iterator_tag;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;
        using point_diff = ptrdiff_t;

        const_iterator(pointer ptr) : current(ptr){};

        bool operator==(const const_iterator& other) const{
            return current == other.current;
        }
        bool operator!=(const const_iterator& other) const{
            return !(current == other.current);
        }

        const_iterator& operator++(){
            ++current;
            return *this;
        }
        const_iterator operator++(int){
            const_iterator temp = *this;
            ++current;
            return temp;
        }
        reference operator*() const{
            return *current;
        }
        pointer operator->() const{
            return current;
        }

    private:
        pointer current;
};

/**
 * @brief Creates an iterator pointing to the beginning of the vector.
 *
 * @return An iterator pointing to the first element.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
typename vector<T>::iterator vector<T>::begin(){    
    return iterator(data);
};

/**
 * @brief Creates an iterator pointing to the end of the vector.
 *
 * @return An iterator pointing to the element after the last one.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
typename vector<T>::iterator vector<T>::end(){
    return iterator(data + size);
}

/**
 * @brief Creates a constant iterator pointing to the beginning of the vector.
 *
 * @return A constant iterator pointing to the first element.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
typename vector<T>::const_iterator vector<T>::begin() const{
    return iterator(data);
}

/**
 * @brief Creates a constant iterator pointing to the end of the vector.
 *
 * @return A constant iterator pointing to the element after the last one.
 * 
 * @note the time complexity is O(1)
 */
template<typename T>
typename vector<T>::const_iterator vector<T>::end() const{
    return iterator(data + size);
}

template<typename T>
void vector<T>::clean_up(){
    delete[] data;
    data = nullptr;
    size = capacity = 0;
};

template<typename T>
void vector<T>::copy_from(const vector<T>& v){
    for(size_t i = 0; i < v.size; ++i) data[i] = v.data[i];
};









    

