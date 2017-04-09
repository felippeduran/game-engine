//
//  slot_map.h
//  GameEngine
//
//  Created by Felippe Durán on 3/14/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef slot_map_h
#define slot_map_h

#include <vector>

template<class T> class slot_map_iterator;
template<class T> class const_slot_map_iterator;

template<class T>
class slot_map {
public:
    slot_map() = default;
    slot_map(const slot_map& slotMap) : objects(slotMap.objects), count(count) {};
    ~slot_map() {
        for (auto objectsArray : objects) {
            delete []objectsArray;
        }
    }
    
    long long createObject() {
        if (freeList.empty()) {
            T* chunk = new T[chunk_size];
            for (int i = (int)chunk_size - 1; i >= 0; --i) {
                chunk[i].id = objects.size() * chunk_size + i;
                freeList.push_back((int)objects.size() * (int)chunk_size + i);
            }
            objects.push_back(chunk);
            indirection.resize(indirection.size() + chunk_size);
        }
        
        int free = freeList.back();
        freeList.pop_back();
        indirection[free] = count;
        long long id = objects[count / chunk_size][count % chunk_size].id;
        count += 1;
        return id;
    };
    
    T* getObject(long long id) const {
        int index = indirection[id & 0xFFFFFFFF];
        T*obj = objects[index / chunk_size] + index % chunk_size;
        return obj->id != id ? nullptr : obj;
    };
    
    void destroyObject(long long id) {
        T* obj = getObject(id);
        if (obj) {
            obj->id = (obj->id & 0xFFFFFFFF) | (((obj->id >> 32) + 1) << 32);
            freeList.push_back(id & 0xFFFFFFFF);

            int index = indirection[id & 0xFFFFFFFF];
            int lastUsedIndex = count - 1;
            T lastObj = objects[lastUsedIndex / chunk_size][lastUsedIndex % chunk_size];
            
            objects[lastUsedIndex / chunk_size][lastUsedIndex % chunk_size] = *obj;
            objects[index / chunk_size][index % chunk_size] = lastObj;
            
            indirection[lastObj.id & 0xFFFFFFFF] = index;
            
            count -= 1;
        }
    };
    
    size_t size() const {return count; };
    
    typedef slot_map_iterator<T> iterator;
    typedef const_slot_map_iterator<T> const_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef T value_type;
    typedef T * pointer;
    typedef T & reference;
    
    iterator begin() { return iterator(*this, 0); }
    iterator end() { return iterator(*this, count); }
    const_iterator begin() const { return const_iterator(*this, 0); }
    const_iterator end() const { return const_iterator(*this, count); }
    
    T& operator[](const size_t idx) { return objects[idx / chunk_size][idx % chunk_size]; }
    
private:
    std::vector<T *> objects;
    std::vector<int> indirection;
    std::vector<int> freeList;
    const size_t chunk_size = 256;
    int count;
    
    friend class const_slot_map_iterator<T>;
    friend class slot_map_iterator<T>;
};


template<class T>
class const_slot_map_iterator {
public:
    using const_iterator = typename slot_map<T>::const_iterator;
    using difference_type = typename slot_map<T>::difference_type;
    using size_type = typename slot_map<T>::size_type;
    using value_type = typename slot_map<T>::value_type;
    using pointer = typename slot_map<T>::pointer;
    using reference = typename slot_map<T>::reference;
    using iterator_category = std::random_access_iterator_tag;
    
    const_slot_map_iterator(slot_map<T>& slotMap, int offset) : slotMap(&slotMap), offset(offset) {};
    
    bool operator==(const const_iterator& other) { return offset == other.offset; }
    bool operator!=(const const_iterator& other) { return not operator==(other); }
    bool operator<(const const_iterator& other) const { return offset < other.offset; }
    bool operator>(const const_iterator& other) const { return offset > other.offset; }
    bool operator<=(const const_iterator& other) const { return offset <= other.offset; }
    bool operator>=(const const_iterator& other) const { return offset >= other.offset; }
    
    const T & operator*() { return slotMap->objects[offset / slotMap->chunk_size][offset % slotMap->chunk_size]; }
    const_iterator & operator++() { ++offset; return *this; }
    
    const_iterator operator++ ( int ) {
        const_slot_map_iterator<T> result = *this;
        ++offset;
        return result;
    }
    
    const_iterator & operator--() { --offset; return *this; }
    
    const_iterator operator-- ( int ) {
        const_slot_map_iterator<T> result = *this;
        --offset;
        return result;
    }
    
    const_iterator& operator+=(difference_type i) {
        offset += i;
        return *this;
    }
    
    const_iterator& operator-=(difference_type i) {
        return operator+=(-i);
    }
    
    const_iterator operator+(difference_type i) const {
        auto result = *this;
        result += i;
        return result;
    }
    
    const_iterator operator-(difference_type i) const {
        auto result = *this;
        result -= i;
        return result;
    }
    
    difference_type operator-(const const_iterator& other) const {
        return offset - other.offset;
    }
    
    const_iterator& operator=(const_iterator other) {
        std::swap(offset, other.offset);
        std::swap(slotMap, other.slotMap);
        return *this;
    }

    
protected:
    slot_map<T> *slotMap;
    int offset;
};


template<class T>
class slot_map_iterator : public const_slot_map_iterator<T> {
public:
    using base_iterator = const_slot_map_iterator<T>;
    using iterator = typename slot_map<T>::iterator;
    using difference_type = typename base_iterator::difference_type;
    using size_type = typename base_iterator::size_type;
    using value_type = typename base_iterator::value_type;
    using pointer = typename base_iterator::pointer;
    using reference = typename base_iterator::reference;
    
    slot_map_iterator(slot_map<T>& slotMap, int offset) : const_slot_map_iterator<T>(slotMap, offset) {};
    
    T & operator*() { return this->slotMap->objects[this->offset / this->slotMap->chunk_size][this->offset % this->slotMap->chunk_size]; }

    iterator & operator++() { ++this->offset; return *this; }
    
    iterator operator++ ( int ) {
        slot_map_iterator<T> result = *this;
        ++const_slot_map_iterator<T>::operator++();
        return result;
    }
    
    iterator & operator--() { --this->offset; return *this; }
    
    iterator operator-- ( int ) {
        slot_map_iterator<T> result = *this;
        --this->offset;
        return result;
    }
    
    iterator& operator+=(difference_type i) {
        base_iterator::operator+=(i);
        return *this;
    }
    
    iterator& operator-=(difference_type i) {
        return operator+=(-i);
    }
    
    iterator operator+(difference_type i) const {
        auto result = *this;
        result += i;
        return result;
    }
    
    iterator operator-(difference_type i) const {
        auto result = *this;
        result -= i;
        return result;
    }
    
    difference_type operator-(const iterator& other) const {
        return base_iterator::operator-(other);
    }
    
    iterator& operator=(iterator other) {
        base_iterator::operator=(other);
        return *this;
    }
};

#endif /* slot_map_h */
