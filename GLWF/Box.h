//
//  Box.h
//  GLWF
//
//  Created by Rodrigo Castro Ramos on 1/21/19.
//  Copyright © 2019 Rodrigo Castro Ramos. All rights reserved.
//

#ifndef Box_h
#define Box_h

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "SOIL2/SOIL2.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

class Box {
    
public:
    vector<glm::vec3> cubePositions;
    vector<bool> exploited;
    Box(){
        cubePositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        cubePositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        cubePositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        cubePositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        cubePositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        cubePositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        exploited.push_back(false);
        exploited.push_back(false);
        exploited.push_back(false);
        exploited.push_back(false);
        exploited.push_back(false);
        exploited.push_back(false);
    }
    
    void movement(){
        for (int i = 0; i < cubePositions.size(); i++) {
            cubePositions[i].z += 0.0001 ;
            if (cubePositions[i].z >= 10) {
                cubePositions[i].x = rand()%10-1;
                cubePositions[i].z = -rand()%10;
            }
        }
    }
    
    void updatePosition(){
        for (int i = 0; i < cubePositions.size(); i++) {
            if (exploited[i] == true) {
                cubePositions[i] = glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 );
                cout<< "Colicionaron conmigo soy un cubo"<<endl;
            }
                
        }
    }
    
    static GLuint LoadBox(){
        GLuint cubeVAO, cubeVBO;
        GLfloat vertices[] = {
                // Positions          // Texture Coords
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
                
            };
        glGenVertexArrays( 1, &cubeVAO );
        glGenBuffers( 1, &cubeVBO );
        glBindVertexArray( cubeVAO );
        glBindBuffer( GL_ARRAY_BUFFER, cubeVBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), &vertices, GL_STATIC_DRAW );
        glEnableVertexAttribArray(0);
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * ) 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
        glBindVertexArray(0);
        return cubeVAO;
    }
    
};

#endif /* Box_h */
