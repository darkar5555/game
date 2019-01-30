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



const GLfloat velocidad      =  6.0f;


class Player {
    
    
public:
    glm::vec3 playerPosition;
    GLfloat movementSpeed;
    GLfloat movementJump;
    glm::vec3 lefth;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 jump;
    bool jumpPresed;

    
    Player(){
        playerPosition = glm::vec3 (0.0f, 0.0f, 0.0f);
        lefth = glm::vec3 (-1.0f, 0.0f, 0.0f);
        right = glm::vec3 ( 1.0f, 0.0f, 0.0f );
        jump = glm::vec3 ( 0.0f, 1.0f, 0.0f );
        movementSpeed = 6.0f;
        movementJump = 4.0f;
        jumpPresed = false;
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

        if ( direction == SALTO && jumpPresed == false )
        {
//            jumpPresed = true;
//            for (GLfloat i = playerPosition.y; i <= 7.0f ; i = i + .1f) {
//                this->playerPosition += this->jump * velocity;
//                cout<<"El salto falta mejorar"<<endl;
//                //            this->playerPosition.y -= 5.0f * velocity;
//            }
//            while( playerPosition.y < 3.0f ){
//                this->playerPosition += this->jump * velocityJump;
//                cout<<"El salto falta mejorar"<<endl;
////            }
//                while (jumpPresed == false && playerPosition.y >4.0f) {
//                    playerPosition = glm::vec3( 0.0f, 0.0f, 0.0f );
//                    jumpPresed = true;
//                }
            
            
            while( playerPosition.y < 4.0f ){
                cout<< playerPosition.y<<endl;
                this->playerPosition += this->jump * velocity;
                cout<<"El salto falta mejorar"<<endl;
            }

//            for (GLfloat i = 7.0f; i >= 0.0f  ; i = i-.1f) {
//                this->playerPosition -= this->jump * velocity;
//                cout<< i<< endl;
//                cout<<"El salto falta mejorar de bajada"<<endl;
//                //            this->playerPosition.y -= 5.0f * velocity;
//            }
//            this->playerPosition = glm::vec3 (0.0f, 0.0f, 0.0f);
        

            
        }

        if ( direction == PROTECCION )
        {
            cout<<"me tengo que proteger"<<endl;
        }
    }
    
};


#endif /* Player_h */
