#include <iostream>
#include <cmath>
#include "SDL/SDL_mixer.h"
#include <unistd.h>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "SOIL2/SOIL2.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <math.h>

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Box.h"
#include "Light.h"
#include "Coins.h"
#include "Player.h"
//#include "Mesh.h"
#include "Model.h"
#include "Car.h"
#include "Manzana.h"
#include "Fence.h"
#include "Persona.h"
#include "Tronco.h"
#include "Wood.h"
#include "Knife.h"
#include "Rock.h"
#include "Proyectil.h"
#include "Shield.h"


// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

Mix_Chunk *sound = NULL;
Mix_Chunk *sound2=NULL;
Mix_Chunk *sound_wood=NULL;
Mix_Chunk *sound_eat=NULL;
Mix_Chunk *sound_knife=NULL;
int channel;
int channel2;
// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );
void MovePlayer( );
void MoveCar( );

bool pausando = false;
bool despausando = true;


// Player lifes and score
GLfloat score = 0.0f;
GLfloat lifes = 3.0f;

// Camera
Camera  camera( glm::vec3( 0.0f, 1.5f, 5.0f ) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

bool pausegame = false;
// Player
Player player;

// Aqui se esta creando el carro
Car car;
Manzana manzana;
Fence fence;
Persona persona;
Tronco tronco;
Wood wood;
Knife knife;
Shield shield;

vector<Wood> woods;
vector<Manzana> manzanas;
vector<Fence> fences;
vector<Persona> personas;
vector<Tronco> troncos;
vector<Rock> rocks;
vector<Proyectil> proyectiles;
vector<Knife> knifes;


// Light attributes
glm::vec3 lightPos( 1.2f, 1.0f, 2.0f );

// Deltatime
GLfloat deltaTime = 0.0f;    // Time between current frame and last frame
GLfloat lastFrame = 0.0f;      // Time of last frame


glm::vec3 positionRandom(){
    return glm::vec3(  rand()%7-3,  0.0f,  -(rand()%300) - 100.0f );
}
glm::vec3 positionRandomUp(){
    return glm::vec3(  rand()%7-3,  2.0f,  -(rand()%300) -100.0f );
}


// Funcion de collision
float collision(glm::vec3 a, glm::vec3 b){
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
}


// The MAIN function, from here we start the application and run the game loop
int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow( WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    
    // Build and compile our shader program
    Shader lightingShader( "resources/shaders/lighting.vs", "resources/shaders/lighting.frag" );
    Shader lampShader( "resources/shaders/lamp.vs", "resources/shaders/lamp.frag" );
    
    
    
    // El for para crear varios woods, personas, faces, troncos, manzanas
    for (int i = 0; i<10; i++) {
        glm::vec3 temp = positionRandom();
        Wood a(temp);
        woods.push_back(a);
    }
    for (int i = 0; i<10; i++) {
        glm::vec3 temp = positionRandom();
        Tronco a(temp);
        troncos.push_back(a);
    }
    for (int i = 0; i<10; i++) {
        glm::vec3 temp = positionRandom();
        Persona a(temp);
        personas.push_back(a);
    }
    for (int i = 0; i<10; i++) {
        glm::vec3 temp = positionRandom();
        Fence a(temp);
        fences.push_back(a);
    }
    for (int i = 0; i<20; i++) {
        glm::vec3 temp = positionRandom();
        Manzana a(temp);
        manzanas.push_back(a);
    }
    for (int i = 0; i<15; i++) {
        glm::vec3 temp = positionRandom();
        Rock a(temp);
        rocks.push_back(a);
    }
    for (int i = 0; i<15; i++) {
        glm::vec3 temp = positionRandomUp();
        Proyectil a(temp);
        proyectiles.push_back(a);
    }
    for (int i = 0; i<5; i++) {
        Knife a;
        knifes.push_back(a);
    }



    GLfloat finishvertices[]=
            {
                //posicion                                  //color                                 //texcoords                         //normal
                -0.5f, 0.5f, 0.f ,          0.f, 0.f, 1.f,                 0.f, 1.f,                //
                -0.5f, -0.5f, 0.f ,         0.f, 0.f, 1.f,             0.f, 0.f,               //
                0.5f, -0.5f, 0.f   ,        0.f, 0.f, 1.f,                1.f, 0.f,                //
            
                //glm::vec3(-0.5f, 0.5f, 0.f),                glm::vec3(1.f, 0.f, 0.f),               glm::vec2(0.f, 1.f),
                //glm::vec3(0.5f, -0.5f, 0.f),                glm::vec3(0.f, 0.f, 1.f),               glm::vec2(1.f, 0.f),
                0.5f, 0.5f, 0.f,             0.f, 0.f, 1.f,                  1.f, 1.f               // 0.f, 0.f, 1.f
            };


    
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] =
    {
        // Positions            // Normals              // Texture Coords
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
        
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
        
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
        
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
    };
    
    
    // Positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(  0.7f,  0.2f,  2.0f      ),
        glm::vec3(  2.3f, -3.3f, -4.0f      ),
        glm::vec3(  -4.0f,  2.0f, -12.0f    ),
        glm::vec3(  0.0f,  0.0f, -3.0f      )
    };
    
    

    // First, set the container's VAO (and VBO)
    GLuint VBO, boxVAO;
    glGenVertexArrays( 1, &boxVAO );
    glGenBuffers( 1, &VBO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    
    glBindVertexArray( boxVAO );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )0 );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )( 6 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 2 );
    glBindVertexArray( 0 );
    
    


    
    // Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
    GLuint lightVAO;
    glGenVertexArrays( 1, &lightVAO );
    glBindVertexArray( lightVAO );
    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    // Set the vertex attributes (only position data for the lamp))
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )0 ); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
    glEnableVertexAttribArray( 0 );
    glBindVertexArray( 0 );
    
    // Load textures
    GLuint diffuseMap, specularMap, emissionMap, diffuseMapCoin, specularMapCoin, diffuseSpace, specularSpace;
    glGenTextures( 1, &diffuseMap );
    glGenTextures( 1, &specularMap );
    glGenTextures( 1, &emissionMap );
    glGenTextures( 1, &diffuseMapCoin);
    glGenTextures( 1, &specularMapCoin);
    glGenTextures( 1, &diffuseSpace);
    glGenTextures( 1, &specularSpace);

    
    int imageWidth, imageHeight;
    unsigned char *image;
    
    // Variables de Textura
    GLuint cubeTexture = TextureLoading::LoadTexture("resources/images/container2.png");
    Box cubos;
    Coin coins;
    GLuint coinTexture = TextureLoading::LoadTexture("resources/images/moneda.jpg");

    
//    GLuint probando = Box::LoadBox();

    
    // Diffuse map
    image = SOIL_load_image( "resources/images/container2.png", &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB );
    glBindTexture( GL_TEXTURE_2D, diffuseMap );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( image );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST );
    
    // Specular map
    image = SOIL_load_image( "resources/images/container_specular.png", &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB );
    glBindTexture( GL_TEXTURE_2D, specularMap );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( image );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST );
    glBindTexture( GL_TEXTURE_2D, 0 );
    
    
    
    // ===================
    // Texture de el spacio
    // ===================
    GLuint texture;
    
    int width, height;

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    // Set our texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    // Set texture filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // Load, create texture and generate mipmaps
    unsigned char *imageSpace = SOIL_load_image( "resources/images/ambiente.jpg", &width, &height, 0, SOIL_LOAD_RGBA );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageSpace );
    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( imageSpace );
    glBindTexture( GL_TEXTURE_2D, 0 );

    //game over
    GLuint texturegame;

    int width2,height2;

    glGenTextures( 1, &texturegame );
    glBindTexture( GL_TEXTURE_2D, texturegame );
    // Set our texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    // Set texture filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // Load, create texture and generate mipmaps
    unsigned char *imageGame = SOIL_load_image( "resources/images/image.jpg", &width2, &height2, 0, SOIL_LOAD_RGBA );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageGame);
    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( imageGame );
    glBindTexture( GL_TEXTURE_2D, 0 );
    
    //menu opciones
    GLuint textureop;

    int width3,height3;

    glGenTextures( 1, &textureop );
    glBindTexture( GL_TEXTURE_2D, textureop );
    // Set our texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    // Set texture filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // Load, create texture and generate mipmaps
    unsigned char *imageOp = SOIL_load_image( "resources/images/image2.jpg", &width3, &height3, 0, SOIL_LOAD_RGBA );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width3, height3, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageOp);
    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( imageOp );
    glBindTexture( GL_TEXTURE_2D, 0 );


    
    // Set texture units
    lightingShader.Use( );
    glUniform1i( glGetUniformLocation( lightingShader.Program, "material.diffuse" ), 0 );
    glUniform1i( glGetUniformLocation( lightingShader.Program, "material.specular" ), 1 );
    

    Shader shader("resources/shaders/modelLoading.vs","resources/shaders/modelLoading.frag");
    Model ourModel("resources/model/Small car.obj");
    Model manzanaModel("resources/model/manzana/apple textured obj.obj");
    Model fenceModel("resources/model/fence/fence wood.obj");
    Model personaModel("resources/model/persona/dummy_obj.obj");
    Model troncoModel("resources/model/tronco1/low_obj_500.obj");
    Model woodModel("resources/model/tronco2/low_obj_7000.obj");
    Model knifeModel("resources/model/knife/Knife_1.obj");
    Model rockModel("resources/model/cubo_piedra/objAztec.obj");
    Model proyectilModel("resources/model/proyectil/Mk 82 Snakeye.obj");
    Model shieldModel("resources/model/escudo/Zelda+Sword.obj");

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( GLfloat )SCREEN_WIDTH / ( GLfloat )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    

    //MUisca del juego
    
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
            printf("Unable to initialize audio: %s\n", Mix_GetError());
                exit(1);
    }
    sound = Mix_LoadWAV("resources/music/Dystopic-Mayhem.wav");
    sound2 = Mix_LoadWAV("resources/music/jump.wav");
    sound_eat = Mix_LoadWAV("resources/music/eat.wav");
    sound_wood = Mix_LoadWAV("resources/music/wood.wav");
    sound_knife = Mix_LoadWAV("resources/music/throw-knife.wav");
    if(sound == NULL) {
            printf("Unable to load WAV file: %s\n", Mix_GetError());
    }
    channel = Mix_PlayChannel(-1, sound, -1);



    



    // Game loop
    while ( !glfwWindowShouldClose( window ) )
    {
        // Calculate deltatime of current frame
        GLfloat currentFrame = glfwGetTime( );
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents( );
        DoMovement( );
        
        MovePlayer();
        MoveCar();
        
        // Clear the colorbuffer
        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        //model loading
      


        
        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.Use( );
        GLint viewPosLoc = glGetUniformLocation( lightingShader.Program, "viewPos" );
        glUniform3f( viewPosLoc, camera.GetPosition( ).x, camera.GetPosition( ).y, camera.GetPosition( ).z);
        // Set material properties
        glUniform1f( glGetUniformLocation( lightingShader.Program, "material.shininess" ), 32.0f );
        // == ==========================
        // Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
        // the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
        // by defining light types as classes and set their values in there, or by using a more efficient uniform approach
        // by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
        // == ==========================
        // Directional light
        glUniform3f( glGetUniformLocation( lightingShader.Program, "dirLight.direction" ), -0.2f, -1.0f, -0.3f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "dirLight.ambient" ), 0.05f, 0.05f, 0.05f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "dirLight.diffuse" ), 0.4f, 0.4f, 0.4f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "dirLight.specular" ), 0.5f, 0.5f, 0.5f );
        
        // Point light 1
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[0].position" ), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[0].ambient" ), 0.05f, 0.05f, 0.05f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[0].diffuse" ), 0.8f, 0.8f, 0.8f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[0].specular" ), 1.0f, 1.0f, 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[0].constant" ), 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[0].linear" ), 0.09f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[0].quadratic" ), 0.032f );
        
        //point ligth ambiente
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[0].position" ), 0.0f, 0.0f, -80.0f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[0].ambient" ), 25.05f, 25.05f, 25.05f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[0].diffuse" ), 0.8f, 0.8f, 0.8f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[0].specular" ), 1.0f, 1.0f, 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[0].constant" ), 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[0].linear" ), 0.09f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[0].quadratic" ), 0.032f );
        
        // Point light 2
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[1].position" ), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[1].ambient" ), 0.05f, 0.05f, 0.05f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[1].diffuse" ), 0.8f, 0.8f, 0.8f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[1].specular" ), 1.0f, 1.0f, 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[1].constant" ), 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[1].linear" ), 0.09f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[1].quadratic" ), 0.032f );
        
        // Point light 3
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[2].position" ), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[2].ambient" ), 0.05f, 0.05f, 0.05f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[2].diffuse" ), 0.8f, 0.8f, 0.8f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[2].specular" ), 1.0f, 1.0f, 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[2].constant" ), 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[2].linear" ), 0.09f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[2].quadratic" ), 0.032f );
        
        // Point light 4
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[3].position" ), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[3].ambient" ), 0.05f, 0.05f, 0.05f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[3].diffuse" ), 0.8f, 0.8f, 0.8f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "pointLights[3].specular" ), 1.0f, 1.0f, 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[3].constant" ), 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[3].linear" ), 0.09f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "pointLights[3].quadratic" ), 0.032f );
        
        
        // Spotlight player
        glUniform3f( glGetUniformLocation( lightingShader.Program, "spotLight.position" ), car.GetPosition( ).x, car.GetPosition( ).y, car.GetPosition( ).z );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "spotLight.direction" ), car.GetFront( ).x, car.GetFront( ).y, car.GetFront( ).z );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "spotLight.ambient" ), 0.0f, 0.0f, 0.0f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "spotLight.diffuse" ), 1.0f, 1.0f, 1.0f );
        glUniform3f( glGetUniformLocation( lightingShader.Program, "spotLight.specular" ), 1.0f, 1.0f, 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "spotLight.constant" ), 1.0f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "spotLight.linear" ), 0.09f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "spotLight.quadratic" ), 0.032f );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "spotLight.cutOff" ), glm::cos( glm::radians( 12.5f ) ) );
        glUniform1f( glGetUniformLocation( lightingShader.Program, "spotLight.outerCutOff" ), glm::cos( glm::radians( 15.0f ) ) );
        
        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix( );

        glm::mat4 model(1.0f);
        
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation( lightingShader.Program, "model" );
        GLint viewLoc = glGetUniformLocation( lightingShader.Program, "view" );
        GLint projLoc = glGetUniformLocation( lightingShader.Program, "projection" );
        // Pass the matrices to the shader
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        
        // Bind diffuse map
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, diffuseMap );
        // Bind specular map
        glActiveTexture( GL_TEXTURE1 );
        glBindTexture( GL_TEXTURE_2D, specularMap );
        
        
        glBindVertexArray( boxVAO );
        for ( GLuint i = 0; i < cubos.cubePositions.size(); i++ )
        {
            model = glm::mat4( 1.0f );
            model = glm::translate( model, cubos.cubePositions[i] );
            //            model = glm::translate( model, coins.coinsPositions[i]);
            GLfloat dist = collision(car.playerPosition, cubos.cubePositions[i]);
            if (dist<1.5f){
                // cout<<"hubo una collision";
                cubos.exploited[i] = true;
                cubos.updatePosition();
                cubos.exploited[i] = false;
            }
            //            GLfloat angle = 20.0f * i;
            model = glm::rotate( model, 0.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
            if (pausando == true) {
                cubos.noMove();
            }
            if (pausando == false) {
                cubos.dePause();
            }
            cubos.movement(deltaTime*0.07);
            glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
            
            glDrawArrays( GL_TRIANGLES, 0, 36 );
        }
        glBindVertexArray( 0 );
        
        
        
        
        // dibujando es espacio
        // Bind diffuse map
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        
        // Bind diffuse map
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texture );
        // Bind specular map
        glBindVertexArray( boxVAO );
        model = glm::mat4( 1.0f );
        model = glm::translate( model, glm::vec3 (0.0f, 0.0f, 0.0f) );
        model = glm::rotate( model, 0.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
        model = glm::scale( model, glm::vec3( 100.0f ) ); // Make it a smaller cube
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        glDrawArrays( GL_TRIANGLES, 0, 36 );
        glBindVertexArray( 0 );

        
        //game over
        // Bind diffuse map
        if ( car.lifes <= 0 )
        {
            glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
            glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
            glActiveTexture( GL_TEXTURE0 );
            glBindTexture( GL_TEXTURE_2D, texturegame );
            // Bind specular map
            glBindVertexArray( boxVAO );
            model = glm::mat4( 1.0f );
            model = glm::translate( model, glm::vec3 (0.0f, 2.0f, 0.0f) );
            model = glm::rotate( model, 0.0f, glm::vec3( 0.5f, 4.0f, .0f ) );
            model = glm::scale( model, glm::vec3( 5.0f,2.f,2.f )); // Make it a smaller cube
            glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
            glDrawArrays( GL_TRIANGLES, 0, 8 );
            glBindVertexArray( 0 );
            pausegame = true;
            if (car.lifes < -30) {
                glfwSetWindowShouldClose(window, GL_TRUE);

            }
        }
        
        if(pausegame == true)
        {
            
            float timegame= glfwGetTime();

            
            glfwSetTime(timegame);
            
        
        }

        //opciones
        if(pausando == true)
        {
            glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, textureop );
        // Bind specular map
        glBindVertexArray( boxVAO );
        model = glm::mat4( 1.0f );
        model = glm::translate( model, glm::vec3 (0.0f, 2.0f, 1.5f) );
        model = glm::rotate( model, 0.0f, glm::vec3( 0.5f, 4.0f, .0f ) );
        model = glm::scale( model, glm::vec3( 7.0f,4.f,2.f )); // Make it a smaller cube
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        glDrawArrays( GL_TRIANGLES, 0, 8 );
        glBindVertexArray( 0 );
        }
        
        

        // Also draw the lamp object, again binding the appropriate shader
        lampShader.Use( );
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation( lampShader.Program, "model" );
        viewLoc = glGetUniformLocation( lampShader.Program, "view" );
        projLoc = glGetUniformLocation( lampShader.Program, "projection" );
        // Set matrices
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        model = glm::mat4( 1.0f );
        model = glm::translate( model, lightPos );
        model = glm::scale( model, glm::vec3( 0.2f ) ); // Make it a smaller cube
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        // Draw the light object (using light's vertex attributes)
        glBindVertexArray( lightVAO );
        glDrawArrays( GL_TRIANGLES, 0, 36 );
        glBindVertexArray( 0 );
        

        // We now draw as many light bulbs as we have point lights.
        glBindVertexArray( lightVAO );
        for ( GLuint i = 0; i < 4; i++ )
        {
            model = glm::mat4( 1.0f );
            model = glm::translate( model, pointLightPositions[i] );
            model = glm::scale( model, glm::vec3( 0.2f ) ); // Make it a smaller cube
            glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
            glDrawArrays( GL_TRIANGLES, 0, 36 );
        }
        glBindVertexArray( 0 );

       
        // Pass the matrices to the shader
        shader.Use();

        modelLoc = glGetUniformLocation( shader.Program, "model" );
        viewLoc = glGetUniformLocation( shader.Program, "view" );
        projLoc = glGetUniformLocation( shader.Program, "projection" );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );

    
        model=glm::mat4(1.0f);
        model=glm::translate(model,glm::vec3(0.0f,-1.75f,0.0f));
        model=glm::scale(model, glm::vec3(0.01f,0.01f,0.01f));
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        ourModel.Draw( shader );

        
        // Aqui crearemos todos los modelos
        // Aqui creamos el carro con la clase car
        car.movement(modelLoc, viewLoc, projLoc, shader, ourModel, view, projection, model);
        car.jumper(deltaTime);
        if (car.attack == true){
            if (pausando == true) {
                knife.noMove();
            }
            if (pausando == false) {
                knife.dePause();
            }
            knife.movement( modelLoc, viewLoc, projLoc, shader, knifeModel, view, projection, model, deltaTime);
        }
        
        if (car.defense == true) {
            car.DropShield(modelLoc, viewLoc, projLoc, shader, shieldModel ,view, projection, model, deltaTime);
        }
        car.edges();

        
        
        for (int i = 0; i < woods.size(); i++) {
            GLfloat dist = collision(car.playerPosition, woods[i].woodPosition);
            if (dist<2.5f && car.defense == true){
                woods[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                woods[i].woodPosition = newPosition;
                woods[i].destroyed = false;
                car.defense = false;
            }
            if (dist<2.0f && car.defense == false) {
                car.lifes = car.lifes -1;
                woods[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                woods[i].woodPosition = newPosition;
                woods[i].destroyed = false;
                cout<<"Me queda vidas" << car.lifes <<endl;
            }
            GLfloat dist2 = collision(knife.knifePosition, woods[i].woodPosition);
            if ( dist2<2.0f ){
                woods[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                woods[i].woodPosition = newPosition;
                woods[i].destroyed = false;
                car.attack = false;
                knife.knifePosition =glm::vec3 (0.0, -14.f, 0.0f);
            }
            if (pausando == true) {
                woods[i].noMove();
            }
            if (pausando == false) {
                woods[i].dePause();
            }
            woods[i].movement(modelLoc, viewLoc, projLoc, shader, woodModel ,view, projection, model, deltaTime);
        }
        for (int i = 0; i < fences.size(); i++) {
            GLfloat dist = collision(car.playerPosition, fences[i].fencePosition);
            if (dist<2.5f && car.defense == true){
                fences[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                fences[i].fencePosition = newPosition;
                fences[i].destroyed = false;
                car.defense = false;
            }
            if (dist<1.5f && car.defense == false) {
                car.lifes = car.lifes -1;
                fences[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                fences[i].fencePosition = newPosition;
                fences[i].destroyed = false;
                cout<<"Me queda vidas" << car.lifes <<endl;
            }

            GLfloat dist2 = collision(knife.knifePosition, fences[i].fencePosition);
            if ( dist2<1.5f ){
                // cout<<"hubo una collision";
                fences[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                fences[i].fencePosition = newPosition;
                fences[i].destroyed = false;
                car.attack = false;
                knife.knifePosition =glm::vec3 (0.0, -14.f, 0.0f);

                //                cout<<"Colision con una manzana"<<endl;
            }
            if (pausando == true) {
                fences[i].noMove();
            }
            if (pausando == false) {
                fences[i].dePause();
            }
            fences[i].movement(modelLoc, viewLoc, projLoc, shader, fenceModel ,view, projection, model, deltaTime);
        }
        for (int i = 0; i < personas.size(); i++) {
            GLfloat dist = collision(car.playerPosition, personas[i].personaPosition);
            if (dist<2.5f && car.defense == true){
                // cout<<"hubo una collision";
                personas[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                personas[i].personaPosition = newPosition;
                personas[i].destroyed = false;
                car.defense = false;
                //                cout<<"Colision con una manzana"<<endl;
            }
            if (dist<1.5f && car.defense == false) {
                car.lifes = car.lifes -1;
                personas[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                personas[i].personaPosition = newPosition;
                personas[i].destroyed = false;
                cout<<"Me queda vidas"<< car.lifes <<endl;
            }
            GLfloat dist2 = collision(knife.knifePosition, personas[i].personaPosition);
            if ( dist2<1.5f ){
                // cout<<"hubo una collision";
                personas[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                personas[i].personaPosition = newPosition;
                personas[i].destroyed = false;
                car.attack = false;
                knife.knifePosition =glm::vec3 (0.0, -14.f, 0.0f);
                //                cout<<"Colision con una manzana"<<endl;
            }
            if (pausando == true) {
                personas[i].noMove();
            }
            if (pausando == false) {
                personas[i].dePause();
            }
            personas[i].movement(modelLoc, viewLoc, projLoc, shader, personaModel ,view, projection, model, deltaTime);
        }
        for (int i = 0; i < manzanas.size(); i++) {
            GLfloat dist = collision(car.playerPosition, manzanas[i].manzanaPosition);
            if (dist<1.5f){
                // cout<<"hubo una collision";
                manzanas[i].destroyed = true;
                channel = Mix_PlayChannel(1, sound_eat, 0);
                glm::vec3 newPosition = positionRandom();
                manzanas[i].manzanaPosition = newPosition;
                manzanas[i].destroyed = false;
//                cout<<"Colision con una manzana"<<endl;
            }
            if (pausando == true) {
                manzanas[i].noMove();
            }
            if (pausando == false) {
                manzanas[i].dePause();
            }
            manzanas[i].movement(modelLoc, viewLoc, projLoc, shader, manzanaModel ,view, projection, model, deltaTime);
        }
        for (int i = 0; i < rocks.size(); i++) {
            GLfloat dist = collision(car.playerPosition, rocks[i].rockPosition);
            if (dist<2.5f && car.defense == true){
                // cout<<"hubo una collision";
                rocks[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                rocks[i].rockPosition = newPosition;
                rocks[i].destroyed = false;
                car.defense = false;
                //                cout<<"Colision con una manzana"<<endl;
            }
            if (dist<1.5f && car.defense == false) {
                car.lifes = car.lifes -1;
                rocks[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                rocks[i].rockPosition = newPosition;
                rocks[i].destroyed = false;

                cout<<"Me queda vidas"<< car.lifes <<endl;
            }
            GLfloat dist2 = collision(knife.knifePosition, rocks[i].rockPosition);
            if ( dist2<1.5f ){
                // cout<<"hubo una collision";
                rocks[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                rocks[i].rockPosition = newPosition;
                rocks[i].destroyed = false;
                car.attack = false;
                knife.knifePosition =glm::vec3 (0.0, -14.f, 0.0f);
                //                cout<<"Colision con una manzana"<<endl;
            }

            if (pausando == true) {
                rocks[i].noMove();
            }
            if (pausando == false) {
                rocks[i].dePause();
            }
            rocks[i].movement(modelLoc, viewLoc, projLoc, shader, rockModel ,view, projection, model, deltaTime);
        }
        for (int i = 0; i < proyectiles.size(); i++) {
            GLfloat dist = collision(car.playerPosition, proyectiles[i].proyectilPosition);
            if (dist<2.5f && car.defense == true){
                // cout<<"hubo una collision";
                proyectiles[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                proyectiles[i].proyectilPosition = newPosition;
                proyectiles[i].destroyed = false;
                car.defense = false;
                //                cout<<"Colision con una manzana"<<endl;
            }
            if (dist<1.5f && car.defense == false) {
                car.lifes = car.lifes -1;
                proyectiles[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                proyectiles[i].proyectilPosition = newPosition;
                proyectiles[i].destroyed = false;
                cout<<"me queda vidas"<< car.lifes <<endl;
            }
            GLfloat dist2 = collision(knife.knifePosition, proyectiles[i].proyectilPosition);
            if ( dist2<1.5f ){
                // cout<<"hubo una collision";
                proyectiles[i].destroyed = true;
                glm::vec3 newPosition = positionRandom();
                proyectiles[i].proyectilPosition = newPosition;
                proyectiles[i].destroyed = false;
                car.attack = false;
                knife.knifePosition =glm::vec3 (0.0, -14.f, 0.0f);
                //                cout<<"Colision con una manzana"<<endl;
            }
            if (pausando == true) {
                proyectiles[i].noMove();
            }
            if (pausando == false) {
                proyectiles[i].dePause();
            }
            proyectiles[i].movement(modelLoc, viewLoc, projLoc, shader, proyectilModel ,view, projection, model, deltaTime);
        }

        
        

        
        
//        knife.movement(modelLoc, viewLoc, projLoc, shader, knifeModel, view, projection, model, deltaTime);




        
        

        
        
//        cout<< score<<endl;
        
        // Swap the screen buffers
        glfwSwapBuffers( window );
    }
    
    glDeleteVertexArrays( 1, &boxVAO );
    glDeleteVertexArrays( 1, &lightVAO );
    glDeleteBuffers( 1, &VBO );
    
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
}

void MovePlayer(){
    // Player controls
    
    if ( keys[GLFW_KEY_H]) {
        player.ProcessKeyboard( IZQUIERDA, deltaTime );
    }
    if ( keys[GLFW_KEY_K] ) {
        player.ProcessKeyboard( DERECHA, deltaTime );
    }
    if ( keys[GLFW_KEY_J] ) {
        player.ProcessKeyboard( PROTECCION, deltaTime );
    }
}

void MoveCar(){
    if ( keys[GLFW_KEY_RIGHT] ){
        car.ProcessKeyboard(DER, deltaTime);
    }
    if ( keys[GLFW_KEY_LEFT] ) {
        car.ProcessKeyboard(IZQ, deltaTime);
    }
    if ( keys[GLFW_KEY_UP] ) {
        
        channel = Mix_PlayChannel(-1, sound2, 0);
        car.ProcessKeyboard( JUM, deltaTime );
    }
    if ( keys[GLFW_KEY_DOWN] ) {
        car.ProcessKeyboard( PROTECT, deltaTime );
        car.defense = true;
    }
    /*if ( keys[GLFW_KEY_V] ) {
        car.ProcessKeyboard(DEPROTECT, deltaTime);
    }*/
    if ( keys[GLFW_KEY_SPACE] ) {
        car.attack = true;
        //        knife.dropped = true;
        channel = Mix_PlayChannel(-1, sound_knife, 0);
        knife.knifePosition = car.playerPosition;
    }
    if ( keys[GLFW_KEY_V] ) {
        pausando = true;
    }
    if ( keys[GLFW_KEY_B] ) {
        pausando = false;
    }
    

}



// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}
