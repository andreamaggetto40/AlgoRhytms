#include <cstddef>
#include <new>

template<typename T>
class allocator{
    public: 
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_pointer = const T*;
        using const_reference = const T&;
        using size_type = size_t;

        template<typename U>
        struct rebind{
            using other = allocator<U>;
        };

        allocator() = default;
        ~allocator() = default;

        allocator(const allocator<T>& a) noexcept = default;
        allocator(allocator<T>&& a) noexcept = default;

        allocator& operator=(const allocator<T>& a) = default;
        allocator& operator=(allocator<T>&& a) = default;

        pointer address(reference r) const noexcept{
            return &x;
        }

        const_pointer address(const_reference r) const noexcept{
            return &x;
        }

        
        pointer allocate(size_type n, const_pointer hint = 0) {
            return static_cast<pointer>(::operator new(n * sizeof(T)));
        }

        // deallocate
        void deallocate(pointer p, size_type n) {
            ::operator delete(p);
        }

       
        bool operator==(const MyAllocator&) const noexcept {
            return true;
        }

        bool operator!=(const MyAllocator& other) const noexcept {
            return !(*this == other);
        }
};  
        