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
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );
void goForward();
void goBackwards();


// Camera
Camera camera( glm::vec3( -10.0f, 10.0f, 23.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
int counter = 0;

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
    Model drawerDesk((char*)"Models/Desk/cajon.obj");
    Model chairRoom((char*)"Models/Chair/chair.obj");
    Model carModel((char*)"Models/Car/car.obj");
    Model bearModel((char*)"Models/Bear/bear.obj");

    Model drawerModel((char*)"Models/Drawer/drawer.obj");
    Model lampModel((char*)"Models/Lamp/lamp.obj");
    Model closetModel((char*)"Models/Closet/closet.obj");
    Model tableModel((char*)"Models/Table/table.obj");
    Model couch2Model((char*)"Models/Couch/Couch2ndfloor.obj");
    Model couch3Model((char*)"Models/Couch/Couch2ndfloor2.obj");
    Model plantModel((char*)"Models/Plant/plant.obj"); 

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
       
        //model = glm::translate( model, glm::vec3( 0.0f, 0.0f, 0.0f ) ); // Translate it down a bit so it's at the center of the scene
       // model = glm::scale( model, glm::vec3( 1.2f, 1.2f, 1.2f ) );	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv( glGetUniformLocation( shader.Program, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );
        ourModel.Draw(shader);
      
        backup = model;

        // model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
        // model = glm::scale(model, glm::vec3(2.2f, 2.2f, 2.2f));	// It's a bit too big for our scene, so scale it down
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        // Swap the buffers

        ourModel2.Draw(shader);



        //model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f)); // Translate it down a bit so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));	// It's a bit too big for our scene, so scale it down
        //model = glm::rotate(model, -30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //// Swap the buffers
       

        ourModel3.Draw(shader);


        //model = glm::translate(model, glm::vec3(-5.0f, 0.5f, +3.0f)); // Translate it down a bit so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));	// It's a bit too big for our scene, so scale it down
        //model = glm::rotate(model, -30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //// Swap the buffers


        ourModel4.Draw(shader);

        //model = glm::translate(model, glm::vec3(-9.0f, 0.5f, +3.0f)); // Translate it down a bit so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));	// It's a bit too big for our scene, so scale it down
       // model = glm::rotate(model, -30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //// Swap the buffers


        ourModel5.Draw(shader);


        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        deskRoom.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        drawerDesk.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        chairRoom.Draw(shader);

        model = glm::translate(model, glm::vec3(7.7f, -0.763f, -3.005f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        carModel.Draw(shader);

        model = backup;

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bearModel.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        drawerModel.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lampModel.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        closetModel.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tableModel.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        couch2Model.Draw(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        couch3Model.Draw(shader);

        model = glm::translate(model, glm::vec3(3.478f, -8.179f, 4.460f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        plantModel.Draw(shader);
        
        model = backup;


        model = glm::translate(model, glm::vec3(-3.186f, -4.893f, 4.52f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        plantModel.Draw(shader);

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
      //  goForward(); // FUNCION QUE CAMBIA ADELANTE EL PEZ
    }


    if (keys[GLFW_KEY_T])
    {
      //  goBackwards(); // FUNCION QUE REGRESA AL PEZ ANTERIOR
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

void goForward(){

    (counter == 4) ? counter=0 : counter++;
   
}

void goBackwards(){

    (counter == 0) ? counter = 4 : counter--;

}
