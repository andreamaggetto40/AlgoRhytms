#include "doubly_linked_list.hpp"

template<typename T>
doubly_linked_list<T>::doubly_linked_list() = default;

template<typename T>
doubly_linked_list<T>::doubly_linked_list(const T& init, size_t init_size) : size(0){
    for(size; size < init_size; ++size){
        std::unique_ptr<node> to_add = std::make_unique<node>();
        to_add->info = init;
        to_add->prev = tail;
        to_add->next = nullptr;

        if(!head){
            head = std::move(to_add);
            tail = head.get();
        }
        else{
            tail->next = std::move(to_add);
            tail = tail->next.get();
        }
    }
};

template<typename T>
doubly_linked_list<T>::doubly_linked_list(doubly_linked_list<T>&& dll){
    head = std::move(dll.head);
    tail = dll.tail;
    size = dll.size;    

    dll.tail = nullptr;
    dll.size = 0;
};

template<typename T>
doubly_linked_list<T>::doubly_linked_list(const doubly_linked_list<T>& dll){            
    node* it = dll.head.get();

    while(it != nullptr){
        push_back(it->info);
        it = it->next.get();
    }
};

template<typename T>
doubly_linked_list<T>& doubly_linked_list<T>::operator=(const doubly_linked_list<T>& dll){
    if(this != &dll){
        head.reset();
        tail = nullptr;
        size = 0;

        node* it = dll.head.get();
        while(it != nullptr){
            push_back(it->info);
            it = it->next.get();
        }
    }
    return *this;
};

template<typename T>
doubly_linked_list<T>& doubly_linked_list<T>::operator=(doubly_linked_list<T>&& dll){
    if(this != &dll){
        head.reset();
        tail = nullptr;
        size = 0;

        head = std::move(dll.head);s
        tail = dll.tail;
        size = dll.size;

        dll.head = nullptr;
        dll.tail = nullptr;
        dll.size = 0;
    }
    return *this;
};

template<typename T>
bool doubly_linked_list<T>::operator==(const doubly_linked_list<T>& dll) const{
    if(size != dll.size) return false;

    node* it = head.get();
    node* it_dll = dll.head.get();

    while(it != nullptr){
        if(it->info != it_dll->info) return false;
        it = it->next.get();
        it_dll = it_dll->next.get();
    }

    return true;
};  

template<typename T>
bool doubly_linked_list<T>::operator!=(const doubly_linked_list<T>& dll) const{
    return !(*this == dll);
};

template<typename T>
doubly_linked_list<T>& push_back(const T& el){       
    std::lock_guard<std::mutex> lock(dll_mutex);

    std::unique_ptr<node> to_add = std::make_unique<node>();
    to_add->info = el;
    to_add->prev = tail;
    to_add->next = nullptr;

    if(!head){
        head = std::move(to_add);
        tail = head.get();
    }
    else{
        tail->next = std::move(to_add);
        tail = tail->next.get();
    }
    ++size;

    return *this;
};