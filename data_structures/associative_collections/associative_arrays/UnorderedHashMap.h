#ifndef UNORDERED_HASH_MAP_H
#define UNORDERED_HASH_MAP_H

#include <memory>
#include <functional>

#include "dsaaTypedefs.h"

namespace dsaa
{
    template <typename Key,                                            // UnorderedHashMap::key_type
              typename T,                                              // UnorderedHashMap::mapped_type
              typename Hash = std::hash<Key>,                          // UnorderedHashMap::hasher
              typename Predicate = std::equal_to<Key>,                 // UnorderedHashMap::key_equal
              typename Alloc = std::allocator<std::pair<const Key, T>> // UnorderedHashMap::allocator_type
              >
    class UnorderedHashMap
    {
    };
}

#endif //!UNORDERED_HASH_MAP_H