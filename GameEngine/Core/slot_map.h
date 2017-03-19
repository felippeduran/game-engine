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

template<class T>
class slot_map {
public:
    long long createObject() {
        if (freeList.empty()) {
            T* chunk = new T[chunk_size];
            for (int i = (int)chunk_size - 1; i >= 0; --i) {
                chunk[i].id = objects.size() * chunk_size + i;
                freeList.push_back((int)objects.size() * (int)chunk_size + i);
            }
            objects.push_back(chunk);
        }
        
        int free = freeList.back();
        freeList.pop_back();
        return objects[free / chunk_size][free % chunk_size].id;
    };
    
    T* getObject(long long id) {
        T* obj = objects[(id & 0xFFFFFFFF) / chunk_size] + ((id & 0xFFFFFFFF) % chunk_size);
        return obj->id != id ? nullptr : obj;
    };
    
    void destroyObject(long long id) {
        T* obj = getObject(id);
        obj->id = (obj->id & 0xFFFFFFFF) | (((obj->id >> 32) + 1) << 32);
        freeList.push_back(id & 0xFFFFFFFF);
    };
    
private:
    std::vector<T *> objects;
    std::vector<int> freeList;
    const size_t chunk_size = 256;
};

#endif /* slot_map_h */
