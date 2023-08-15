#include <iostream>
#include <mutex>
#include <atomic>

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

        iterator begin();
        iterator end();
};
        