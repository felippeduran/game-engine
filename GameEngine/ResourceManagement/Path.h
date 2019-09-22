//
//  Path.h
//  GameEngine
//
//  Created by Felippe Durán on 02/09/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef Path_h
#define Path_h

#include <stdio.h>

class Path {
public:
    Path(std::string fullpath) : fullpath(fullpath) {};
    
    std::string basename();
    std::string dirname();
    
private:
    std::string fullpath;
};

#endif /* Path_h */
