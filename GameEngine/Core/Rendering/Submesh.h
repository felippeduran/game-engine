//
//  Submesh.h
//  GameEngine
//
//  Created by Felippe Durán on 19/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef Submesh_h
#define Submesh_h

struct Submesh {
    int materialId;
    int offsetIBO;
    int size;
    
    Submesh(int materialId, int offsetIBO, int size) : materialId(materialId), offsetIBO(offsetIBO), size(size) {};
};

#endif /* Submesh_h */
