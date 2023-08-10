#include <iostream>

template<typename T>
class vector{
    T* data;
    size_t size, capacity;

    void v_delete();

    public:
        vector();
        vector(const T& init, size_t init_size);
        vector(const vector<T>& v);
        vector(vector<T>&& v);
        ~vector();  

        vector<T>& operator=(const vector<T>& v);
        vector<T>& operator=(vector<T>&& v);

        size_t get_size() const;
        void push_back(const T& el);
};
        
        