//
//  Light.h
//  GLWF
//
//  Created by Rodrigo Castro Ramos on 1/28/19.
//  Copyright © 2019 Rodrigo Castro Ramos. All rights reserved.
//

#ifndef Light_h
#define Light_h

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
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

class Light {
public:
    vector<glm::vec3> lightPositions;
    Light(){
        lightPositions.push_back(glm::vec3(  0.7f,  0.2f,  2.0f ));
        lightPositions.push_back(glm::vec3(  2.3f, -3.3f, -4.0f ));
        lightPositions.push_back(glm::vec3( -4.0f,  2.0f, -12.0f ));
        lightPositions.push_back(glm::vec3( 0.0f,  0.0f, -3.0f ));
    }
    
};


#endif /* Light_h */
