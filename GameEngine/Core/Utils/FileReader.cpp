//
//  FileReader.cpp
//  GameEngine
//
//  Created by Felippe Durán on 18/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "FileReader.h"
#include <iostream>
#include <fstream>

using namespace std;

string FileReader::read() {
    string content;
    ifstream file;
    file.open(filename);
    
    string line;
    while (getline(file, line)) {
        content.append(line);
    }
    file.close();
    return content;
};
