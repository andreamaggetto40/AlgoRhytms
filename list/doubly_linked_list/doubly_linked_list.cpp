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

        head = std::move(dll.head);
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

template<typename T>
doubly_linked_list<T>& doubly_linked_list<T>::push_front(const T& el){
    std::lock_guard<std::mutex> lock(dll_mutex);

    std::unique_ptr<node> to_add = std::make_unique<node>();

    to_add->info = el;
    to_add->prev = nullptr;

    if(!head){
        head = std::move(to_add);
        tail = head.get();
    }
    else{
        to_add->next = std::move(head);
        head = std::move(to_add);
        to_add->next->prev = head.get();
    }

    return *this;
};

template<typename T>
size_t doubly_linked_list<T>::get_size() const{
    return size.load();
};

template<typename T>
class doubly_linked_list<T>::iterator{  
    private:
        node* current;
    public:
        explicit iterator(node* init) : current(init){};

        T& operator*(){return current->info;}
        T* operator->(){return &current->info;}
        iterator& operator++(){
            current = current->next.get();
            return *this;
        }
        iterator& operator++(int){
            iterator tmp(*this);
            current = current->next.get();
            return tmp;
        }
        bool operator==(const iterator& it){return current == it.current;}
        bool operator!=(const iterator& it){return current != it.current;}
};

template<typename T>
typename doubly_linked_list<T>::iterator doubly_linked_list<T>::begin(){    
    return iterator(head.get());
};

template<typename T>
typename doubly_linked_list<T>::iterator doubly_linked_list<T>::end(){
    return iterator(nullptr);
};

template<typename T>
class doubly_linked_list<T>::const_iterator{
    private:
        const node* current;
    public:
        explicit const_iterator(const node* init) : current(init){};

        const T& operator*() const {return current->info;}
        const T* operator->() const{return &current->info;}
        const_iterator& operator++(){
            current = current->next.get();
            return *this;
        }
        const_iterator operator++(int){
            const_iterator tmp(*this);
            current = current->next.get();
            return tmp;
        }
        bool operator==(const const_iterator& it) const{
            return current == it.current;
        }
        bool operator!=(const const_iterator& it) const{
            return current != it.current;
        }
};

template<typename T>
typename doubly_linked_list<T>::const_iterator doubly_linked_list<T>::begin() const{
    return const_iterator(head.get());
};

template<typename T>
typename doubly_linked_list<T>::const_iterator doubly_linked_list<T>::end() const{
    return const_iterator(nullptr);
};

template<typename T>
class doubly_linked_list<T>::reverse_iterator{
    private:
        node* current;
    public:
        reverse_iterator(node* init) : current(init){};

        T& operator*(){return current->info;}
        T* operator->(){return &current->info;}
        reverse_iterator& operator++(){
            current = current->prev;
            return *this;
        }
        reverse_iterator operator++(int){
            reverse_iterator tmp(*this);
            current = current->prev;
            return tmp;
        }
        bool operator==(const reverse_iterator& it){return current == it.current;}
        bool operator!=(const reverse_iterator& it){return current != it.current;}
};

template<typename T>
typename doubly_linked_list<T>::reverse_iterator doubly_linked_list<T>::rbegin(){
    return reverse_iterator(tail);
};

template<typename T>
typename doubly_linked_list<T>::reverse_iterator doubly_linked_list<T>::rend(){
    return reverse_iterator(nullptr);
};

template<typename T>
class doubly_linked_list<T>::const_reverse_iterator{
    private:
        const node* current;
    public:
        const_reverse_iterator(const node* init) : current(init){};

        const T& operator*() const {return current->info;}
        const T* operator->() const{return &current->info;}
        const_reverse_iterator& operator++(){
            current = current->prev;
            return *this;
        }
        const_reverse_iterator operator++(int){
            const_reverse_iterator tmp(*this);
            current = current->prev;
            return tmp;
        }
        bool operator==(const const_reverse_iterator& it){return current == it.current;}
        bool operator!=(const const_reverse_iterator& it){return current != it.current;}
};

template<typename T>
typename doubly_linked_list<T>::const_reverse_iterator doubly_linked_list<T>::crbegin() const{
    return const_reverse_iterator(tail);
};

template<typename T>
typename doubly_linked_list<T>::const_reverse_iterator doubly_linked_list<T>::crend() const{
    return const_reverse_iterator(nullptr);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const doubly_linked_list<T>& l){ 
    os << "[";
    for(auto it = l.begin(); it != l.end(); ++it) {
        os << *it;
        if (std::next(it) != l.end()) {  // Se non è l'ultimo elemento
            os << ", ";
        }
    }
    os << "]";
    return os;
};