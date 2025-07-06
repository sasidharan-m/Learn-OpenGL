//
//  main.cpp
//  CameraExcercise1
//
//  Created by  Sasidharan Mahalingam on 05/07/25.
//

#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "shader_loader.h"
#include <unistd.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

bool firstMouse = true; // Global boolean for mouse controlled movement initialization
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// define variables that store the camera position, direction and up vector
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

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

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// input function that gets called every time the scroll wheel is used
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

// input function that gets triggered every time a input key is pressed
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    float cameraSpeed = 2.5f * deltaTime;
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * glm::normalize(glm::cross(worldUp, cameraRight));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * glm::normalize(glm::cross(worldUp, cameraRight));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraRight * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += cameraRight * cameraSpeed;
}

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
    std::string currentpath = "/Documents/OpenGL/OpenGL-Programs/Part-1 Getting Started/Practice Programs/7.5 CameraExcercise1/";
    // Setting the paths of vertex and fragment shaders
    std::string vsPath = homepath + currentpath + "textures.vs";
    std::string fsPath = homepath + currentpath + "textures.fs";
    // build and compile the shader program
    Shader ourShader(vsPath.c_str(), fsPath.c_str());
    
    // set the vertices, color and texture
   float vertices[] = {
        // positions          // texture coords

        // Back face
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // Bottom-left
        0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  // Bottom-right
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  // Top-right
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  // Top-left

        // Front face
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,

        // Right face
        0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,   0.0f, 1.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   0.0f, 1.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,   0.0f, 1.0f
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

    // define the translations for the different cubes
    glm::vec3 cube_positions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };
        
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // load and create a texture
    unsigned int texture1, texture2;
    // Set up first texture
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // flip the loaded image
    stbi_set_flip_vertically_on_load(true);
    // Set the right img path
    std::string texturePath1 = homepath + "/Documents/OpenGL/OpenGL-Programs/" + "resources/container.jpg";
    unsigned char *data = stbi_load(texturePath1.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture1" << std::endl;
    }
    stbi_image_free(data);
    // Set up second texture
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    // Set the right img path
    std::string texturePath2 = homepath + "/Documents/OpenGL/OpenGL-Programs/" + "resources/awesomeface.png";
    data = stbi_load(texturePath2.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture2" << std::endl;
    }
    stbi_image_free(data);
    // active the shader before setting the uniform variables
    ourShader.use();
    // activating the shader before setting the uniforms
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.getProgramID(), "texture1"), 0);
    // or set it via the texture class
    ourShader.setInt("texture2", 1);
    
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        // create transformations
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        

        // render container
        ourShader.use();

        // set the view and projection matrices
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        for(unsigned int i = 0; i < 10; ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube_positions[i]);
            
            float angle = 20.0f * i;
            
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            
            unsigned int modelLoc = glGetUniformLocation(ourShader.getProgramID(), "model");
            unsigned int viewLoc = glGetUniformLocation(ourShader.getProgramID(), "view");
            unsigned int projectionLoc = glGetUniformLocation(ourShader.getProgramID(), "projection");

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        
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
