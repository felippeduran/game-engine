//
//  Program.h
//  GameEngine
//
//  Created by Felippe Durán on 15/05/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef Program_h
#define Program_h

#include <OpenGL/gltypes.h>

class Program {
public:
    Program(GLuint vertShader, GLuint fragShader);
    ~Program();
    
    void use();
    
    GLint getAttribute(const GLchar* attribName) const;
    GLint getUniform(const GLchar* uniformName) const;
    
private:
    GLuint _program;
    GLuint _vertShader;
    GLuint _fragShader;
};

#endif /* Program_h */
