//
//  Player.h
//  GLWF
//
//  Created by Rodrigo Castro Ramos on 1/29/19.
//  Copyright © 2019 Rodrigo Castro Ramos. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <vector>

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Player_Movement
{
    IZQUIERDA,
    SALTO,
    DERECHA,
    PROTECCION
};





class Player {
    
    
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

    
    Player(){
        playerPosition = glm::vec3 (0.0f, 0.0f, 0.0f);
        lefth = glm::vec3 (-1.0f, 0.0f, 0.0f);
        right = glm::vec3 ( 1.0f, 0.0f, 0.0f );
        jump = glm::vec3 ( 0.0f, 0.05f, 0.0f );
        movementSpeed = 6.0f;
        movementJump = 4.0f;
        jumpPresed = false;
        front = glm::vec3 ( 0.0f, 0.0f, -1.0f );
    }
    
    void ProcessKeyboard( Player_Movement direction, GLfloat deltaTime )
    {
        GLfloat velocity = this->movementSpeed * deltaTime;
        GLfloat velocityJump = this->movementJump * deltaTime;

        if ( direction == DERECHA )
        {
            this->playerPosition += this->right * velocity;
        }

        if ( direction == IZQUIERDA )
        {
            this->playerPosition += this->lefth * velocity;
        }

        if ( direction == SALTO && playerPosition.y == 0.0f )
        {
//            jumpPresed = true;
            cout<< "entre al loop"<<endl;
            movementJump = 4.0f;
            jumpPresed = true;
            jump = glm::vec3 (0.0f,1.0f,0.0f);
        }
//        cout<<this->playerPosition.y<< " ";
        
    
        

        if ( direction == PROTECCION )
        {
            cout<<"me tengo que proteger"<<endl;
            cout<< jumpPresed;
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
    
    glm::vec3 GetPosition( )
    {
        return this->playerPosition;
    }
    
    glm::vec3 GetFront( )
    {
        return this->front;
    }

    
};


#endif /* Player_h */
