//
//  Wood.h
//  GLWF
//
//  Created by Rodrigo Castro Ramos on 2/1/19.
//  Copyright © 2019 Rodrigo Castro Ramos. All rights reserved.
//

#ifndef Wood_h
#define Wood_h

#include <vector>

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"

using namespace std;

class Wood {
    
public:
    glm::vec3 woodPosition;
    GLfloat movementSpeed;
    glm::vec3 front;
    bool destroyed;
    
    Wood(){
        woodPosition = glm::vec3 (-2.0f, 0.0f, -65.0f);\
        movementSpeed = 6.0f;
        front = glm::vec3 ( 0.0f, 0.0f, 1.0f );
        destroyed = false;
    }
    Wood(glm::vec3 position){
        woodPosition = position;
        movementSpeed = 6.0f;
        front = glm::vec3 ( 0.0f, 0.0f, 1.0f );
        destroyed = false;
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
        model=glm::scale(model, glm::vec3(0.005f,0.005f,0.005f));
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
        model=glm::translate(model,woodPosition);
        model=glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        ourModel.Draw( shader );
        woodPosition += front * velocity;
    }
    
    void noMove(){
        front = glm::vec3 (0.0f, 0.0f, 0.0f);
    }
    void dePause(){
        front = glm::vec3 (0.0f, 0.0f, 1.0f);
    }
    
    glm::vec3 GetPosition( )
    {
        return this->woodPosition;
    }
    
    glm::vec3 GetFront( )
    {
        return this->front;
    }
    
    
};


#endif /* Wood_h */
