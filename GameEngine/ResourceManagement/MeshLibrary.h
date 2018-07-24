//
//  MeshLibrary.h
//  GameEngine
//
//  Created by Felippe Durán on 14/09/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef MeshLibrary_h
#define MeshLibrary_h

class MaterialLibrary;

class MeshLibrary {
public:
    MeshLibrary(MaterialLibrary *materialLibrary) : materialLibrary(materialLibrary) {};
    ~MeshLibrary();
    
    void loadMesh(const std::string& filename);
    
private:
    MaterialLibrary *materialLibrary;
};

#endif /* MeshLibrary_h */
