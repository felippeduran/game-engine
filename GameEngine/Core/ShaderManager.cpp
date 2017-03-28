//
//  ShaderManager.cpp
//  OpenGLTutoria1
//
//  Created by Felippe Durán on 1/23/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "ShaderManager.h"

using namespace std;

//destructor delete programs
ShaderManager::~ShaderManager() {
    map<string, GLuint>::iterator i;
    for (i = programs.begin();i != programs.end(); ++i)
    {
        GLuint pr = i->second;
        glDeleteProgram(pr);
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

void ShaderManager::createProgram(const string& shaderName, const string& vertexShaderFilename, const string& fragmentShaderFilename) {
    
    GLuint vertex_shader = createShader(GL_VERTEX_SHADER, readShader(vertexShaderFilename), vertexShaderFilename);
    GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, readShader(fragmentShaderFilename), fragmentShaderFilename);
    
    int link_result = 0;
    //create the program handle, attatch the shaders and link it
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_result);
    //check for link errors
    if (link_result == GL_FALSE) {
        int info_log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
        vector<char> program_log(info_log_length);
        glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
        cout << "Shader Loader : LINK ERROR" << endl << &program_log[0] << endl;
        return;
    }
    
    programs[shaderName] = program;
}

const GLuint ShaderManager::getShader(const string& shaderName) {
    return programs.at(shaderName);
    
}
