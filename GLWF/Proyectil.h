//
//  Proyectil.h
//  GLWF
//
//  Created by Rodrigo Castro Ramos on 2/1/19.
//  Copyright © 2019 Rodrigo Castro Ramos. All rights reserved.
//

#ifndef Proyectil_h
#define Proyectil_h


#include <vector>

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"

using namespace std;

class Proyectil {
    
public:
    glm::vec3 proyectilPosition;
    GLfloat movementSpeed;
    glm::vec3 lefth;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 front;
    string path;
    
    Proyectil(){
        proyectilPosition = glm::vec3 (-2.0f, 0.0f, -65.0f);
        lefth = glm::vec3 (-1.0f, 0.0f, 0.0f);
        right = glm::vec3 ( 1.0f, 0.0f, 0.0f );
        movementSpeed = 6.0f;
        front = glm::vec3 ( 0.0f, 0.0f, -1.0f );
    }
    Proyectil(glm::vec3 position){
        proyectilPosition = position;
        lefth = glm::vec3 (-1.0f, 0.0f, 0.0f);
        right = glm::vec3 ( 1.0f, 0.0f, 0.0f );
        movementSpeed = 6.0f;
        front = glm::vec3 ( 0.0f, 0.0f, -1.0f );
    }
    
    void DrawCar(GLint modelLoc, GLint viewLoc, GLint projLoc, Shader shader, Model ourModel, glm::mat4 view, glm::mat4 projection, glm::mat4 model){
        shader.Use();
        modelLoc = glGetUniformLocation( shader.Program, "model" );
        viewLoc = glGetUniformLocation( shader.Program, "view" );
        projLoc = glGetUniformLocation( shader.Program, "projection" );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        
        
        model=glm::mat4(1.0f);
        model=glm::translate(model,glm::vec3(2.0f,1.75f,3.0f));
        model=glm::scale(model, glm::vec3(0.1f,0.1f,0.1f));
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        ourModel.Draw( shader );
    }
    
    void movement(GLint modelLoc, GLint viewLoc, GLint projLoc, Shader shader, Model ourModel, glm::mat4 view, glm::mat4 projection, glm::mat4 model, GLfloat deltaTime){
        
        GLfloat velocity = velocidad * deltaTime;
        shader.Use();
        modelLoc = glGetUniformLocation( shader.Program, "model" );
        viewLoc = glGetUniformLocation( shader.Program, "view" );
        projLoc = glGetUniformLocation( shader.Program, "projection" );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        
        
        model=glm::mat4(1.0f);
        model=glm::translate(model,proyectilPosition);
        model=glm::scale(model, glm::vec3(1.f,1.f,1.f));
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        ourModel.Draw( shader );
        proyectilPosition += glm::vec3 ( 0.0f, 0.0f, 1.0f) * velocity;
    }
    
    
    glm::vec3 GetPosition( )
    {
        return this->proyectilPosition;
    }
    
    glm::vec3 GetFront( )
    {
        return this->front;
    }
    
    
};


#endif /* Proyectil_h */
