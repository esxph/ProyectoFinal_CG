// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"

// Properties
const GLuint WIDTH = 1280, HEIGHT = 720;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );
void openDrawer();
void getChairBack();

 // SE DECLARAN LAS DOS ANIMACIONES COMPLEJAS
void moveCar();
void moveBear();


// Camera
Camera camera( glm::vec3( 0.0f, 5.0f, 23.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
int counter = 0;

float drawer_x = 0.0;

float chair_y = 0.0;


float car_x = 0.0;
float car_y = 0.0;
float car_z = 0.0;
float rotCar = 0.0;
float rotBear = 0.0;
float bear_y = 0.0;

float plant_x = 0.0;


bool cir1 = true;
bool cir2 = false;
bool cir3 = false;
bool cir4 = false;
bool cir5 = false;
bool cir6 = false;

bool bearCir = false;
bool cirB1 = true;
bool cirB2 = false;

bool carCircuit = false;
bool door = true;

glm::vec3 iniPosCar(-6.7, -0.7f, 2.295f);

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
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto", nullptr, nullptr );
    
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
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
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
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    
    // Load models

    Model ourModel  ((char *)"Models/HouseModel/HouseModel.obj");
    Model ourModel2 ((char*) "Models/Couch/Couch.obj");
    Model ourModel3((char*) "Models/TvStand/tvStand.obj");
    Model ourModel4((char*)"Models/Bed/Bed.obj");
    Model ourModel5((char*)"Models/Basket/Basket.obj");
    Model deskRoom((char*) "Models/Desk/desk.obj");
    Model drawerDesk((char*)"Models/Desk/cajon.obj"); // Cajon
    Model chairRoom((char*)"Models/Chair/chair.obj");
    Model carModel((char*)"Models/Car2/car.obj");
    Model bearModel((char*)"Models/Bear/bear.obj");

    Model drawerModel((char*)"Models/Drawer/drawer.obj");
    Model lampModel((char*)"Models/Lamp/lamp.obj");
    Model closetModel((char*)"Models/Closet/closet.obj");
    Model tableModel((char*)"Models/Table/table.obj");
    Model couch2Model((char*)"Models/Couch/Couch2ndfloor.obj");
    Model couch3Model((char*)"Models/Couch/Couch2ndfloor2.obj");
    Model plantModel((char*)"Models/Plant/plant.obj"); 
    Model doorModel((char*)"Models/Door/door.obj");
    Model kitchenModel((char*)"Models/Kitchen/kitchen.obj");
    Model tableKit((char*)"Models/TableKit/tablekit.obj");
    Model teapot((char*)"Models/Teapot/teapot.obj");


    // Draw in wireframe
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
   
    // Game loop
    while( !glfwWindowShouldClose( window ) )
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime( );
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Check and call events
        glfwPollEvents( );
        DoMovement( );
        moveCar();
        moveBear();
        
        // Clear the colorbuffer
        glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        shader.Use( );
        
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "view" ), 1, GL_FALSE, glm::value_ptr( view ) );
        
        
        // Draw the loaded model
        glm::mat4 model(1);
        glm::mat4 backup;
      

        // HOUSE MODEL LOADING AND DRAWING 
		glUniformMatrix4fv( glGetUniformLocation( shader.Program, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );
        ourModel.Draw(shader);
      
        backup = model;

        if (door) {
            // DOOR MODEL LOADING AND DRAWING 
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            doorModel.Draw(shader);
        }

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ourModel2.Draw(shader);



        // BASKET LOADING
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ourModel3.Draw(shader);


        // BED LOADING AND DRAWING
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ourModel4.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // DESK LOADING
        ourModel5.Draw(shader);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        deskRoom.Draw(shader);


        //DRAWER LOADING 
        model = glm::translate(model, glm::vec3(0.0f+ drawer_x, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        drawerDesk.Draw(shader);
        model = backup;

        // CHAIR LOADING AND DRAWING
        model = glm::translate(model, glm::vec3(0.0f+ chair_y, 0.0f , 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        chairRoom.Draw(shader);
        model = backup;

        model = glm::mat4(1);
        model = glm::translate(model, iniPosCar+ glm::vec3(car_x, car_y, car_z));
        model = glm::rotate(model, rotCar, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        carModel.Draw(shader);

        model = backup;

        // BEAR LOADING 
        model = glm::translate(model, glm::vec3(0.0f,0.0f + bear_y, 0.0f));
        model = glm::rotate(model, rotBear, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bearModel.Draw(shader);
        model = backup;

        // DRAWER LOADING
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        drawerModel.Draw(shader);

        // LAMP LOADING
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lampModel.Draw(shader);

        // CLOSET LOADING 
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        closetModel.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tableModel.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        couch2Model.Draw(shader);

        model = backup;

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        couch3Model.Draw(shader);

        model = glm::translate(model, glm::vec3(3.478f, -8.179f, 4.460f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        plantModel.Draw(shader);
        
        model = backup;

        model = glm::translate(model, glm::vec3(5.178, -8.179f, 4.460f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        plantModel.Draw(shader);

        model = backup;


        model = glm::translate(model, glm::vec3(-3.186f, -4.893f, 4.52f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        plantModel.Draw(shader);

        model = backup;
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        kitchenModel.Draw(shader);
        model = backup;

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tableKit.Draw(shader);

        model = backup;

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        teapot.Draw(shader);

        


        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
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

    if (keys[GLFW_KEY_Y])
    {
        openDrawer(); // FUNCION PARA ABRIR EL CAJÓN DEL ESCRITORIO.
    }


    if (keys[GLFW_KEY_T])
    {
       
        getChairBack(); // FUNCIÓN PARA DESLIZAR LA SILLA HACIA ATRAS
    }

    if (keys[GLFW_KEY_J]) { // ANIMACION CAIDA DEL OSO

        (bearCir == false)? bearCir = true: bearCir=false, rotBear=0.0f,bear_y=0, cirB1=true; // SE ACTIVA LA ANIMACION DEL OSO
       
    }

    if (keys[GLFW_KEY_K]) { // ANIMACIÓN PARA ABRIR LA PUERTA
        (door == true) ? door = false : door = true;
    }

    if (keys[GLFW_KEY_L]) {
        
        (carCircuit == false) ? carCircuit = true,cir1=true  : carCircuit = false; // INICIAR LA ANIMACION DEL COCHE
       
    }

    if (keys[GLFW_KEY_P]) {

        plant_x = plant_x + 0.1;
        cout << plant_x;

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

void openDrawer(){
    (drawer_x == 0) ? drawer_x = -0.6 : drawer_x = 0;
}

void getChairBack(){
    (chair_y == 0) ? chair_y = -0.6 : chair_y = 0;
}

void moveCar() {

    if (carCircuit) {
   
        if (cir1) {
            (car_z < 10.3) ? car_z = car_z + 0.1 : cir1 = false;
            (cir1 == false) ? cir2 = true, rotCar=45.5 : cir1 = true;
        }
         
        if (cir2) {
            (car_x < 17.8) ? car_x = car_x + 0.1 : cir2 = false;
            (cir2 == false) ? cir3 = true, rotCar = 47.1 : cir2 = true;
        }

        if (cir3) {
            (car_z > -10.5) ? car_z = car_z - 0.1 : cir3 = false;
            (cir3 == false) ? cir4 = true, rotCar = 48.6 : cir3 = true;
        }

        if (cir4) {
            (car_x > -4.5) ? car_x = car_x - 0.1 : cir4 = false;
            (cir4 == false) ? cir5 = true, rotCar = 0 : cir4 = true;
        }

        if (cir5) {
            (car_z < 7.5) ? car_z = car_z + 0.1 : cir5 = false;
            (cir5 == false) ? cir6 = true, rotCar = 45.5 : cir5 = true;
        }
        if (cir6) {
            (car_x > 0.1) ? car_x = car_x + 0.1 : cir6 = false;
            carCircuit = false;
        }

    }
}


void moveBear() { 

    if (bearCir) {

        if (cirB1) {
            (rotBear < 0.4) ? rotBear = rotBear + 0.05 : cirB1 = false, cirB2=true;
        }

        if (cirB2) {
            (bear_y > -2.1) ? bear_y = bear_y - 0.1 : cirB2 = false;
        }
    }
}