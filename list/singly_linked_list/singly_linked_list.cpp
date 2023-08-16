#include "singly_linked_list.hpp"


/**
 * @brief Constructor that initializes a node with a given value.
 * @param value The value to be stored in the node.
 * @complexity O(1)
 */
template<typename T>
singly_linked_list<T>::node::node(const T& value) : info(value), next(nullptr){};

/**
 * @brief Default constructor that initializes an empty list.
 * @complexity O(1)
 */
template<typename T>
singly_linked_list<T>::singly_linked_list() : head(nullptr), tail(nullptr), size(0){};


/**
 * @brief Copy constructor.
 * @param l The list to copy from.
 * @complexity O(n), where n is the size of list l.
 */
template<typename T>
singly_linked_list<T>::singly_linked_list(const singly_linked_list<T>& l){
    node* it = l.head;

    while(it){
        push_back(it->info);
        it = it->next;
    }
};


/**
 * @brief Move constructor.
 * @param l The list to move from.
 * @complexity O(1)
 */
template<typename T>
singly_linked_list<T>::singly_linked_list(singly_linked_list<T>&& l) : head(l.head), tail(l.tail), size(l.size){
    l.head = l.tail = nullptr;
    l.size = 0;
};


/**
 * @brief Destructor that clears the list.
 * @complexity O(n), where n is the size of the list.
 */
template<typename T>
singly_linked_list<T>::~singly_linked_list(){
    clear();
};

/**
 * @brief Copy assignment operator.
 * @param l The list to copy from.
 * @return Reference to the current list.
 * @complexity O(n + m), where n is the size of the current list and m is the size of list l.
 */
template<typename T>
singly_linked_list<T>& singly_linked_list<T>::operator=(const singly_linked_list<T>& l) noexcept{
    if(this != &l){
        clear();

        node* to_add = l.head;

        while(to_add){
            push_back(to_add->info);
            to_add = to_add->next;
        }
    }
    return *this;
};

/**
 * @brief Move assignment operator.
 * @param l The list to move from.
 * @return Reference to the current list.
 * @complexity O(n), where n is the size of the current list.
 */
template<typename T>
singly_linked_list<T>& singly_linked_list<T>::operator=(singly_linked_list<T>&& l) noexcept{
    if(this != &l){
        clear();

        head = l.head;
        tail = l.tail;
        size = l.size;

        l.head = l.tail = nullptr;
    }
    return *this;
};

/**
 * @brief Appends a value at the end of the list and returns a reference to the modified list.
 * 
 * This method appends the specified value to the end of the list. If the list is empty, the new
 * element becomes both the head and the tail of the list. Otherwise, the new element is added
 * after the current tail.
 * 
 * @param value The value to append.
 * @return A reference to the modified list using a Fluent API style.
 * 
 * @complexity O(1)
 */
template<typename T>
singly_linked_list<T> singly_linked_list<T>::push_back(const T& value){      
    std::lock_guard<std::mutex> lock(l_mutex);

    node* to_add = new node(value);

    if(!head) head = tail = to_add;
    else{
        tail->next = to_add;
        tail = tail->next;
    }
    ++size;

    return *this;
};

/**
 * @brief Adds a value at the beginning of the list and returns a reference to the modified list.
 * 
 * This method adds the specified value at the beginning of the list. If the list is empty, the new
 * element becomes both the head and the tail of the list. Otherwise, the new element is added
 * before the current head.
 * 
 * @param value The value to add.
 * @return A reference to the modified list using a Fluent API style.
 * 
 * @complexity O(1)
 */
template<typename T>
void singly_linked_list<T>::pop_back(){
    std::lock_guard<std::mutex> lock(l_mutex);

    if(!head) return;
    if(head == tail){
        delete tail;
        head = tail = nullptr;
    }
    else{
        node* it = head;
        
        while(it->next != tail) it = it->next;
        
        delete tail;
        tail = it;
        tail->next = nullptr;
    }
    --size;
};  

/**
 * @brief Adds a value at the beginning of the list.
 * @param value The value to add.
 * @complexity O(1)
 */
template<typename T>
singly_linked_list<T> singly_linked_list<T>::push_front(const T& value){
    std::lock_guard<std::mutex> lock(l_mutex);

    node* to_add = new node(value);

    if(!head) head = tail = to_add;
    else{
        to_add->next = head;
        head = to_add;
    }
    ++size;

    return *this;
};

/**
 * @brief Removes the first element from the list.
 * @complexity O(1)
 */
template<typename T>
void singly_linked_list<T>::pop_front(){
    std::lock_guard<std::mutex> lock(l_mutex);

    if(!head) return;
    
    if(head == tail){
        delete head;
        head = tail = nullptr;
    }
    else{
        node* to_add = head;
        head = head->next;
        delete to_add;
    }

    --size;
};

/**
 * @brief Searches for a value in the list.
 * @param value The value to search for.
 * @return Reference to the found value.
 * @throw std::runtime_error If the value is not found.
 * @complexity O(n), where n is the size of the list.
 */
template<typename T>
const T& singly_linked_list<T>::search(const T& value) const{ 
    std::lock_guard<std::mutex> lock(l_mutex);

    node* it = head;
    
    while(it){
        if(it->info == value) return it->info;
        it = it->next;
    }

    throw std::runtime_error("Value not found!");
};

/**
 * @brief Returns the current size of the list.
 * @return The size of the list.
 * @complexity O(1)
 */
template<typename T>
size_t singly_linked_list<T>::get_size() const{
    return size;
};

/**
 * @class iterator
 * @brief Iterator for singly_linked_list.
 */
template<typename T>
class singly_linked_list<T>::iterator{
    private:
        node* current;
    
    public:
        using value_type = T;
        using iterator_category = std::forward_iterator_tag;
        using pointer = T*;
        using reference = T&;

        iterator() : current(nullptr){};
        iterator(const node* current_n) : current(current_n){};
        
        pointer operator->() const{
            return current->info;
        }

        reference operator*() const{
            return &current->info;
        }

        iterator& operator++(){
            if(current) current = current->next;
            return *this;
        }

        iterator operator++(int){
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
};

/**
 * @brief Constant iterator for the singly_linked_list class.
 * 
 * This iterator is designed to safely iterate over a singly_linked_list without allowing
 * modifications to the elements it references. This ensures that the list's
 * integrity remains intact during iterations.
 * 
 * @tparam T The type of elements in the singly_linked_list.
 */
template<typename T>
class singly_linked_list<T>::const_iterator{
    private:
        node* current;
    public:
        using value_type = const T;
        using iterator_category = std::forward_iterator_tag;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() : current(nullptr){};
        const_iterator(const node* current_n) : current(current_n){};
        
        pointer operator->() const{
            return current->info;
        }

        reference operator*() const{
            return &current->info;
        }

        const_iterator& operator++(){
            if(current) current = current->next;
            return *this;
        }

        const_iterator operator++(int){
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
};

/**
 * @brief Returns an iterator pointing to the beginning of the list.
 * @return Iterator to the beginning.
 * @complexity O(1)
 */
template<typename T>
typename singly_linked_list<T>::iterator singly_linked_list<T>::begin(){
    return iterator(head);
};

/**
 * @brief Returns an iterator pointing to the end of the list.
 * @return Iterator to the end.
 * @complexity O(1)
 */
template<typename T>
typename singly_linked_list<T>::iterator singly_linked_list<T>::end(){
    return iterator(nullptr);
};

/**
 * @brief Clears all elements from the list.
 * @complexity O(n), where n is the size of the list.
 */
template<typename T>
void singly_linked_list<T>::clear(){
    std::lock_guard<std::mutex> lock(l_mutex);
    node* current;

    while(head){
        current = head;
        head = head->next;
        delete current;
    }

    size = 0;
};


