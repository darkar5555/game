//
//  Car.h
//  GLWF
//
//  Created by Rodrigo Castro Ramos on 2/1/19.
//  Copyright © 2019 Rodrigo Castro Ramos. All rights reserved.
//

#ifndef Car_h
#define Car_h

#include <vector>

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"
#include "Knife.h"
#include "Shield.h"

using namespace std;

enum Car_Movement
{
    IZQ,
    JUM,
    DER,
    PROTECT,
    DEPROTECT,
    ATTACK
};


class Car {
    
public:
    glm::vec3 playerPosition;
    GLfloat movementSpeed;
    GLfloat movementJump;
    glm::vec3 lefth;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 jump;
    glm::vec3 front;
    bool jumpPresed;
    string path;
    bool attack;
    Knife knife;
    Shield shield;
    bool defense;
    GLint lifes;

    Car(){
        playerPosition = glm::vec3 (0.0f, 0.0f, 0.0f);
        lefth = glm::vec3 (-1.0f, 0.0f, 0.0f);
        right = glm::vec3 ( 1.0f, 0.0f, 0.0f );
        jump = glm::vec3 ( 0.0f, 0.05f, 0.0f );
        movementSpeed = 6.0f;
        movementJump = 4.0f;
        jumpPresed = false;
        front = glm::vec3 ( 0.0f, 0.0f, -1.0f );
        attack = false;
        lifes = 3;
//        knife(playerPosition);
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
    
    void movement(GLint modelLoc, GLint viewLoc, GLint projLoc, Shader shader, Model ourModel, glm::mat4 view, glm::mat4 projection, glm::mat4 model){
        shader.Use();
        modelLoc = glGetUniformLocation( shader.Program, "model" );
        viewLoc = glGetUniformLocation( shader.Program, "view" );
        projLoc = glGetUniformLocation( shader.Program, "projection" );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        
        
        model=glm::mat4(1.0f);
        model=glm::translate(model,playerPosition);
        model=glm::scale(model, glm::vec3(0.005f,0.005f,0.005f));
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        ourModel.Draw( shader );
    }
    
    void DropKnife(glm::vec3 temp, GLint modelLoc, GLint viewLoc, GLint projLoc, Shader shader, Model ourModel, glm::mat4 view, glm::mat4 projection, glm::mat4 model, GLfloat deltaTime){
        knife.movementAttac(temp, modelLoc, viewLoc, projLoc, shader, ourModel, view, projection, model, deltaTime);
    }

    void DropShield(GLint modelLoc, GLint viewLoc, GLint projLoc, Shader shader, Model ourModel, glm::mat4 view, glm::mat4 projection, glm::mat4 model, GLfloat deltaTime){
        if (defense == true) {
            glm::vec3 temp = glm::vec3 (playerPosition.x, playerPosition.y-0.7f, playerPosition.z-0.5f);
            this->shield.movementDefense(temp ,modelLoc, viewLoc, projLoc, shader, ourModel, view, projection, model, deltaTime);
        }
    }

    
    void ProcessKeyboard( Car_Movement direction, GLfloat deltaTime )
    {
        GLfloat velocity = this->movementSpeed * deltaTime;
        
        if ( direction == DER )
        {
            this->playerPosition += this->right * velocity;
//            cout<<"aprete a la derecha";
        }
        
        if ( direction == IZQ )
        {
            this->playerPosition += this->lefth * velocity;
        }
        
        if ( direction == JUM && playerPosition.y == 0.0f )
        {
            //            jumpPresed = true;
            movementJump = 4.0f;
            jumpPresed = true;
            jump = glm::vec3 (0.0f,1.0f,0.0f);
        }
        //        cout<<this->playerPosition.y<< " ";
        
        if ( direction == PROTECT )
        {
//            cout<< jumpPresed;
//            attack = true;
            defense = true;
        }
        if ( direction == DEPROTECT ){
            defense = false;
        }
        if ( direction == ATTACK ) {
            attack = true;
        }
    }
    
    void jumper( GLfloat deltaTime ){
        GLfloat velocityJump = this->movementJump * deltaTime;
        if ( jumpPresed == true ) {
            if ( this->playerPosition.y <= 3.0f && jumpPresed == true ){
                this->playerPosition += this->jump * velocityJump;
                if (this->playerPosition.y > 2.6f ){
                    jumpPresed = false;
                    cout<<"jump presses igual a falseo"<< endl;
                    cout<<jumpPresed;
                }
            }
            
        }
        if ( jumpPresed == false ) {
            if ( this->playerPosition.y != 0.0f && jumpPresed == false ){
                this->playerPosition -=  this->jump * velocityJump;
                if ( this->playerPosition.y <= 0.0f){
                    jumpPresed = true;
                    this->playerPosition.y = 0.0f;
                    jump = glm::vec3 (0.0f,0.0f,0.0f);
                }
            }
        }
    }
    
    void edges(){
         if (playerPosition.x > 3.0f) {
            right = glm::vec3 (0.0, 0.0f, 0.0f);
            lefth = glm::vec3 (-1.0, 0.0f, 0.0f);

        }
        if (playerPosition.x < -3.0f) {
            lefth = glm::vec3 (0.0, 0.0f, 0.0f);
            right = glm::vec3 (1.0, 0.0f, 0.0f);
        }
        if (playerPosition.x > -2.9f && playerPosition.x < 2.9f) {
            right = glm::vec3 (1.0, 0.0f, 0.0f);
            lefth = glm::vec3 (-1.0, 0.0f, 0.0f);
        }
    }
    
    glm::vec3 GetPosition( )
    {
        return this->playerPosition;
    }
    
    glm::vec3 GetFront( )
    {
        return this->front;
    }

    
};

#endif /* Car_h */
