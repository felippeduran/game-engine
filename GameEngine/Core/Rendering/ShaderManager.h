//
//  ShaderManager.h
//  OpenGLTutoria1
//
//  Created by Felippe Durán on 1/23/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef ShaderManager_h
#define ShaderManager_h

#include <GL/glew.h>
#include <map>

namespace tdogl {
    class Program;
};

class ShaderManager {
public:
    ShaderManager() {};
    ~ShaderManager();
    
    void createProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename);
    GLuint createProgram(std::string vertex_shader_code, std::string fragment_shader_code);
    
    tdogl::Program *getProgram(const std::string& programName);
    
private:
    
    std::map<std::string, tdogl::Program *> programs;
};

#endif /* ShaderManager_h */
