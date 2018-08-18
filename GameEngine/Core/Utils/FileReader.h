//
//  FileReader.h
//  GameEngine
//
//  Created by Felippe Durán on 18/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef FileReader_h
#define FileReader_h

class FileReader {
public:
    FileReader(std::string& filename) : filename(filename) {};
    
    std::string read();
    
private:
    std::string filename;
};

#endif /* FileReader_h */
