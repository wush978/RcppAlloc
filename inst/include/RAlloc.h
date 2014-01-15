#ifndef __RALLOC_H__
#define __RALLOC_H__

#include <cstdlib>
#define STRICT_R_HEADERS
#include <Rcpp.h>
#include <new>
#include <limits>

namespace RALLOC {

template <class T> 
struct allocator {
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    // convert an allocator<T> to allocator<U>
    template <class U>
    struct rebind { typedef allocator<U> other; };
    
    inline explicit allocator() throw() {}
    inline ~allocator() throw() {}
    inline explicit allocator(const allocator&) throw() {}
    template <class U>
    inline explicit allocator(const allocator<U>&) throw(){}

    // address
    pointer address(reference x) const { return &x; }
    const_pointer address(const_reference x) const { return &x; }

    // memory allocation
    pointer allocate(size_type s, void const * = 0) {
        if (0 == s)
            return NULL;
        pointer temp = R_Calloc(s, T); 
        if (temp == NULL)
            throw std::bad_alloc();
        return temp;
    }

    void deallocate(pointer p, size_type) {
        R_Free(p);
    }

    size_type max_size() const throw() { 
        return std::numeric_limits<size_t>::max() / sizeof(T); 
    }

    void construct(pointer p, const T& val) {
        new((void *)p) T(val);
    }

    void destroy(pointer p) {
        p->~T();
    }
};
}

#endif //__RALLOC_H__