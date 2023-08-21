#include "doubly_linked_list.hpp"

template<typename T>
doubly_linked_list<T>::doubly_linked_list() = default;

template<typename T>
doubly_linked_list<T>::doubly_linked_list(const T& init, size_t init_size) : size(0){
    for(size_t i = 0; i < init_size; ++i) push_back(init);
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