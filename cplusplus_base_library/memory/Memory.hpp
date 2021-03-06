﻿#ifndef _m_NEW_MEMORY_HPP_CPP_
#define _m_NEW_MEMORY_HPP_CPP_() 1

#include <memory>
#include <utility>
#include <cstddef>
#include <cstdint>
#include <cinttypes>
#include <type_traits>
#include "../private_cplusplus_base_library/cplusplus_base_library_global.hpp"

#ifndef _EXPORT_MALLOC_FREE_IMPORT
#define _EXPORT_MALLOC_FREE_IMPORT CPLUSPLUS_BASE_LIBRARYSHARED_EXPORT
#endif

#if !defined(MEMORY_CLASS_NEW_DELETE)

#if defined(__cplusplus)
#define MEMORY_CLASS_NEW_DELETE public: \
static void operator delete(void *arg) { memory::free(arg); } \
static void operator delete[](void *arg) { memory::free(arg); } \
static void * operator new(std::size_t n) { auto ans=memory::malloc(n); if (ans) { return ans; }throw std::bad_alloc{}; } \
static void * operator new[](std::size_t n) { auto ans=memory::malloc(n); if (ans) { return ans; }throw std::bad_alloc{}; }
#else
#define MEMORY_CLASS_NEW_DELETE
#endif

#endif

namespace memory {

_EXPORT_MALLOC_FREE_IMPORT void * malloc(std::size_t);
_EXPORT_MALLOC_FREE_IMPORT void free(void *);
_EXPORT_MALLOC_FREE_IMPORT void freePoolMemory();
inline void free(const void * arg) { memory::free(const_cast<void*>(arg)); }

}/*memory*/

namespace memory {

class _EXPORT_MALLOC_FREE_IMPORT __memory__construct_static {
    friend void constructStatic();
protected:
    static bool __is_construct_static() noexcept(true);
    static void __set_construct_static() noexcept(true);
    static bool __run_once(void(*)(void)) noexcept(true);
};

}/*memory*/

#endif

/*
*/

