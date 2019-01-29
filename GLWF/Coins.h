//
//  Coins.h
//  GLWF
//
//  Created by Rodrigo Castro Ramos on 1/28/19.
//  Copyright © 2019 Rodrigo Castro Ramos. All rights reserved.
//

#ifndef Coins_h
#define Coins_h

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

class Coin {
    
public:
    vector<glm::vec3> coinsPositions;
    vector<bool> gotcha;

    Coin(){
        coinsPositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        coinsPositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        coinsPositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        coinsPositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        coinsPositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        coinsPositions.push_back(glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 ));
        gotcha.push_back(false);
        gotcha.push_back(false);
        gotcha.push_back(false);
        gotcha.push_back(false);
        gotcha.push_back(false);
        gotcha.push_back(false);
    }
    void movement(){
        for (int i = 0; i < coinsPositions.size(); i++) {
            coinsPositions[i].z += 0.001 ;
            if (coinsPositions[i].z >= 10) {
                coinsPositions[i].x = rand()%10-1;
                coinsPositions[i].z = -rand()%10;
            }
        }
    }
    
    void updateCoins(){
        for (int i = 0; i < coinsPositions.size(); i++) {
            if (gotcha[i] == true) {
                coinsPositions[i] = glm::vec3(  rand()%10-1,  0.0f,  -rand()%10 );
                cout<< "Colicionaron conmigo soy moneda"<<endl;
            }
        }
    }

    
};


#endif /* Coins_h */
