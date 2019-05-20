//
//  MaterialSerializer.h
//  GameEngine
//
//  Created by Felippe Durán on 14/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef MaterialSerializer_h
#define MaterialSerializer_h

struct Material;

class MaterialSerializer {
public:
    MaterialSerializer(Material &material) : material(material) {};
    
    std::string serialize();
    
private:
    Material &material;
};

#endif /* MaterialSerializer_h */
