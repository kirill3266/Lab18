#ifndef LFU_HPP
#define LFU_HPP

#include <cstddef>
#include <iostream>
#include <map>
#include <unordered_map>

template<typename Key>
class LFUCache  {
    std::multimap<std::size_t, Key> frequency_storage;
    std::unordered_map<Key,typename std::multimap<std::size_t, Key>::iterator> lfu_storage;
public:

    LFUCache() = default;

    ~LFUCache() = default;

    void Insert(const Key &key)  {
        constexpr std::size_t INIT_VAL = 1;
        // all new value initialized with the frequency 1
        lfu_storage[key] =
                frequency_storage.emplace_hint(frequency_storage.cbegin(), INIT_VAL, key);
    }

    void Touch(const Key &key)  {
        // get the previous frequency value of a key
        auto elem_for_update = lfu_storage[key];
        auto updated_elem = std::make_pair(elem_for_update->first + 1, elem_for_update->second);
        // update the previous value
        frequency_storage.erase(elem_for_update);
        lfu_storage[key] =
                frequency_storage.emplace_hint(frequency_storage.cend(), std::move(updated_elem));
    }

    void Erase(const Key &key) noexcept  {
        frequency_storage.erase(lfu_storage[key]);
        lfu_storage.erase(key);
    }

    const Key &ReplCandidate() const noexcept  {
        // at the beginning of the frequency_storage we have the
        // least frequency used value
        return frequency_storage.cbegin()->second;
    }

};

#endif // LFU_HPP