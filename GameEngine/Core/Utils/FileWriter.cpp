//
//  FileWriter.cpp
//  GameEngine
//
//  Created by Felippe Durán on 18/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "FileWriter.h"
#include <iostream>
#include <fstream>

using namespace std;

void FileWriter::write(string &content) {
    ofstream file;
    file.open(filename);
    file << content;
    file.close();
};
