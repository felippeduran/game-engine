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
            indirection.resize(indirection.size() + chunk_size);
        }
        
        int free = freeList.back();
        freeList.pop_back();
        indirection[free] = count;
        long long id = objects[count / chunk_size][count % chunk_size].id;
        count += 1;
        return id;
    };
    
    T* getObject(long long id) {
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
    
private:
    std::vector<T *> objects;
    std::vector<int> indirection;
    std::vector<int> freeList;
    const size_t chunk_size = 256;
    int count;
};

#endif /* slot_map_h */
