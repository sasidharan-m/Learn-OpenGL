//
//  main.cpp
//  Colors
//
//  Created by  Sasidharan Mahalingam on 07/07/25.
//

#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "shader_loader.h"
#include "camera.h"
#include <unistd.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

bool firstMouse = true; // Global boolean for mouse controlled movement initialization

float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


// framebuffer size function to resize the viewport everytime the use resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// input function that gets called every time the mouse in moved
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

// input function that gets called every time the scroll wheel is used
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(static_cast<float>(yoffset));
}

// input function that gets triggered every time a input key is pressed
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::forward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::backward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::left, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::right, deltaTime);
}


// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main(int argc, const char * argv[]) {
    // set up GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // create a GFLW Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // set up viewport size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //set the mouse movement and scroll wheel callback functions
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // set up GLAD to manage OpenGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Getting homepath
    std::string homepath = getenv("HOME");
    // Setting current path
    std::string currentpath = "/Documents/OpenGL/OpenGL-Programs/Part-2 Lighting/Example Programs/2.2 BasicLightingSpecular/";
    // Setting the paths of vertex and fragment shaders
    std::string vsPath = homepath + currentpath + "basiclightingspecular.vs";
    std::string fsPath = homepath + currentpath + "basiclightingspecular.fs";
    std::string lightvsPath = homepath + currentpath + "light_basiclightingspecular.vs";
    std::string lightfsPath = homepath + currentpath + "light_basiclightingspecular.fs";
    // build and compile the shader program
    Shader ourShader(vsPath.c_str(), fsPath.c_str());
    Shader lightingOurShader(lightvsPath.c_str(), lightfsPath.c_str());
    
    // set the vertices, color and texture
   float vertices[] = {
        // positions.          //normals

        // Back face.
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        // Front face
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,

        // Right face
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

        // Top face
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };
    
    unsigned int indices[] = {
        // Back face
        0, 1, 2,
        2, 3, 0,

        // Front face
        4, 5, 6,
        6, 7, 4,

        // Left face
        8, 9,10,
        10,11, 8,

        // Right face
        12,13,14,
        14,15,12,

        // Bottom face
        16,17,18,
        18,19,16,

        // Top face
        20,21,22,
        22,23,20
    };
  
    unsigned int VBO, VAO, lightingVAO, EBO;
    
    // first configure the cube's VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //second configure the lighting cube's VAO
    glGenVertexArrays(1, &lightingVAO);

    glBindVertexArray(lightingVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // start render loop
    while(!glfwWindowShouldClose(window))
    {
        // per frame time calculation
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // process any inputs
        processInput(window);
        
        // clear color buffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // set the view and projection matrices
        view = camera.getViewMatrix();
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        

        // render color cube
        ourShader.use();
        ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("lightPos", lightPos);
        ourShader.setVec3("viewPos", camera.getPosition());
        
        unsigned int modelLoc = glGetUniformLocation(ourShader.getProgramID(), "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.getProgramID(), "view");
        unsigned int projectionLoc = glGetUniformLocation(ourShader.getProgramID(), "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // render lighting cube

        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        lightingOurShader.use();
        modelLoc = glGetUniformLocation(lightingOurShader.getProgramID(), "model");
        viewLoc = glGetUniformLocation(lightingOurShader.getProgramID(), "view");
        projectionLoc = glGetUniformLocation(lightingOurShader.getProgramID(), "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(lightingVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        // poll events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    // deallocate all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    
    // terminate GLFW's resources
    glfwTerminate();
    
    return 0;
}
