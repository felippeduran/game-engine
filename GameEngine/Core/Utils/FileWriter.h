//
//  FileWriter.h
//  GameEngine
//
//  Created by Felippe Durán on 18/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef FileWriter_h
#define FileWriter_h

class FileWriter {
public:
    FileWriter(std::string& filename) : filename(filename) {};
    
    void write(std::string& content);
    
private:
    std::string filename;
};

#endif /* FileWriter_h */
