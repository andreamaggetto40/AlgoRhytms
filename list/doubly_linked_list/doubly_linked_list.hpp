#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <cstddef>
#include <mutex>
#include <atomic>
#include <memory>

template<typename T>
class doubly_linked_list{
    private:
        struct node{
            T info;
            node* prev;
            std::unique_ptr<node> next;
        };

        std::unique_ptr<node> head;
        node* tail;
        mutable std::mutex dll_mutex;
        std::atomic<size_t> size;

    public:
        doubly_linked_list();
        doubly_linked_list(const T& init, size_t init_size);
        doubly_linked_list(const doubly_linked_list<T>& dll);
        doubly_linked_list(doubly_linked_list<T>&& dll);

        doubly_linked_list<T>& operator=(const doubly_linked_list<T>& dll);
        doubly_linked_list<T>& operator=(doubly_linked_list<T>&& dll);

        bool operator==(const doubly_linked_list<T>& dll) const;
        bool operator!=(const doubly_linked_list<T>& dll) const;

        doubly_linked_list<T>& push_back(const T& el);
        doubly_linked_list<T>& push_front(const T& el);
        size_t get_size() const;

        class iterator;
        class const_iterator;
        class reverse_iterator;
        class const_reverse_iterator;

        iterator begin();
        iterator end();
        
        const_iterator begin() const;
        const_iterator end() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        const_reverse_iterator crbegin() const;
        const_reverse_iterator crend() const;
};

#endif