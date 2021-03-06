//
//  Shield.h
//  GLWF
//
//  Created by Rodrigo Castro Ramos on 2/1/19.
//  Copyright © 2019 Rodrigo Castro Ramos. All rights reserved.
//

#ifndef Shield_h
#define Shield_h

#include <vector>

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"

using namespace std;

class Shield {
    
public:
    glm::vec3 shieldPosition;
    GLfloat movementSpeed;
   
    glm::vec3 front;
    string path;
    GLfloat angle;
    Shield(){
        shieldPosition = glm::vec3 (-2.0f, 0.0f, -65.0f);
        movementSpeed = 6.0f;
        front = glm::vec3 ( 0.0f, 0.0f, 1.0f );
        angle = 0.0f;
    }
    Shield(glm::vec3 position){
        shieldPosition = position;
        movementSpeed = 6.0f;
        front = glm::vec3 ( 0.0f, 0.0f, 1.0f );
        angle = 0.0f;
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
        model=glm::translate(model,shieldPosition);
        model=glm::scale(model, glm::vec3(1.f,1.f,1.f));
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        ourModel.Draw( shader );
        shieldPosition += front * velocity;
    }
    
    void movementDefense(glm::vec3 position,GLint modelLoc, GLint viewLoc, GLint projLoc, Shader shader, Model ourModel, glm::mat4 view, glm::mat4 projection, glm::mat4 model, GLfloat deltaTime){
        
        GLfloat velocity = velocidad * deltaTime;
        shader.Use();
        modelLoc = glGetUniformLocation( shader.Program, "model" );
        viewLoc = glGetUniformLocation( shader.Program, "view" );
        projLoc = glGetUniformLocation( shader.Program, "projection" );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        
        
        model=glm::mat4(1.0f);
        model=glm::translate(model,position);
        model=glm::scale(model, glm::vec3(0.07f,0.07f,0.07f));
//        model=glm::rotate(model,angle, glm::vec3( 0.0f, 0.5f, 0.5f ));
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        ourModel.Draw( shader );
        position += front * velocity;
//        angle = angle+ 1.0f * velocity;
    }

    
    
    glm::vec3 GetPosition( )
    {
        return this->shieldPosition;
    }
    
    glm::vec3 GetFront( )
    {
        return this->front;
    }
    
    
};


#endif /* Shield_h */
