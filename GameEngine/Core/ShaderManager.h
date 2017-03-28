//
//  ShaderManager.h
//  OpenGLTutoria1
//
//  Created by Felippe Durán on 1/23/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef ShaderManager_h
#define ShaderManager_h

#include <OpenGL/gl3.h>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class ShaderManager {
    
public:
    ShaderManager() {};
    ~ShaderManager();
    
    //modify char* to std::string
    void createProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename);
    GLuint createProgram(std::string vertex_shader_code, std::string fragment_shader_code);
    
    const GLuint getShader(const std::string&);
    
private:
    //modify char* to std::string
    std::string readShader(const std::string& filename);
    //modify char* to std::string
    GLuint createShader(GLenum shaderType, const std::string& source, const std::string& shaderName);
    
    std::map<std::string, GLuint> programs;
};

#endif /* ShaderManager_h */
