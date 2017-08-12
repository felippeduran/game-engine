//
//  ShaderManager.cpp
//  OpenGLTutoria1
//
//  Created by Felippe Durán on 1/23/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "ShaderManager.h"
#include "Program.h"

using namespace std;

ShaderManager::~ShaderManager() {
    for (auto& programPair : programs) {
        delete programPair.second;
    }
    programs.clear();
}

string ShaderManager::readShader(const string& filename) {    
    string shaderCode;
    ifstream file(filename, ios::in);
    
    if(!file.good()) {
        cout<<"Can't read file "<<filename<<endl;
        terminate();
    }
    
    file.seekg(0, ios::end);
    shaderCode.resize((unsigned int)file.tellg());
    file.seekg(0, ios::beg);
    file.read(&shaderCode[0], shaderCode.size());
    file.close();
    return shaderCode;
}

GLuint ShaderManager::createShader(GLenum shaderType, const string& source, const string& shaderName) {
    int compile_result = 0;
    
    GLuint shader = glCreateShader(shaderType);
    const char *shader_code_ptr = source.c_str();
    const int shader_code_size = (int)source.size();
    
    glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
    
    //check for errors
    if (compile_result == GL_FALSE) {
        int info_log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        vector<char> shader_log(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
        cout << "ERROR compiling shader: " << shaderName << endl << &shader_log[0] << endl;
        return 0;
    }
    return shader;
}

void ShaderManager::createProgram(const string& programName, const string& vertexShaderFilename, const string& fragmentShaderFilename) {
    GLuint vertex_shader = createShader(GL_VERTEX_SHADER, readShader(vertexShaderFilename), vertexShaderFilename);
    GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, readShader(fragmentShaderFilename), fragmentShaderFilename);
    
    programs[programName] = new Program(vertex_shader, fragment_shader);
}

Program *ShaderManager::getProgram(const string& programName) {
    return programs.at(programName);
    
}
