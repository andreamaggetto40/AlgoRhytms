#include "singly_linked_list.hpp"

template<typename T>
singly_linked_list<T>::node::node(const T& value) : info(value), next(nullptr){};

template<typename T>
singly_linked_list<T>::singly_linked_list() : head(nullptr), tail(nullptr), size(0){};

template<typename T>
singly_linked_list<T>::singly_linked_list(const singly_linked_list<T>& l){
    node* it = l.head;

    while(it){
        push_back(it->info);
        it = it->next;
    }
};

template<typename T>
singly_linked_list<T>::singly_linked_list(singly_linked_list<T>&& l) : head(l.head), tail(l.tail), size(l.size){
    l.head = l.tail = nullptr;
    l.size = 0;
};

template<typename T>
singly_linked_list<T>::~singly_linked_list(){
    clear();
};

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

template<typename T>
void singly_linked_list<T>::push_back(const T& value){      
    std::lock_guard<std::mutex> lock(l_mutex);

    node* to_add = new node(value);

    if(!head) head = tail = to_add;
    else{
        tail->next = to_add;
        tail = tail->next;
    }
    ++size;
};

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

template<typename T>
void singly_linked_list<T>::push_front(const T& value){
    std::lock_guard<std::mutex> lock(l_mutex);

    node* to_add = new node(value);

    if(!head) head = tail = to_add;
    else{
        to_add->next = head;
        head = to_add;
    }
    ++size;
};

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

template<typename T>
size_t singly_linked_list<T>::get_size() const{
    return size;
};

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

template<typename T>
typename singly_linked_list<T>::iterator singly_linked_list<T>::begin(){
    return iterator(head);
};

template<typename T>
typename singly_linked_list<T>::iterator singly_linked_list<T>::end(){
    return iterator(nullptr);
};


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


