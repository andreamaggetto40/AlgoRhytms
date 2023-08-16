#include <iostream>
#include <mutex>
#include <atomic>

/**
 * @file singly_linked_list.hpp
 * @brief A thread-safe singly linked list implementation.
 * 
 * This list provides basic operations like push_back, pop_back, push_front, and pop_front.
 * It is designed to be thread-safe using mutexes.
 * 
 * @tparam T Type of the elements.
 * 
 * @author Andrea Maggetto
 */

template<typename T>
class singly_linked_list{
    private:
        struct node{
            T info;
            node* next;
            node(const T& value);
        };

        node* head;
        node* tail;
        std::atomic<size_t> size;
        mutable std::mutex l_mutex;

        void clear();

    public:
        singly_linked_list();
        singly_linked_list(const singly_linked_list<T>& l);
        singly_linked_list(singly_linked_list<T>&& l);
        ~singly_linked_list();

        singly_linked_list& operator=(const singly_linked_list<T>& l) noexcept;
        singly_linked_list& operator=(singly_linked_list<T>&& l) noexcept;

        void push_back(const T& value);
        void pop_back();
        void push_front(const T& value);
        void pop_front();

        const T& search(const T& value) const;
        size_t get_size() const;

        class iterator;
        class const_iterator;

        iterator begin();
        iterator end();
};
        