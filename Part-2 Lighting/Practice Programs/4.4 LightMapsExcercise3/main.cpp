//
//  main.cpp
//  Materials
//
//  Created by  Sasidharan Mahalingam on 01/08/25.
//

#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "shader_loader.h"
#include "camera.h"
#include <unistd.h>
#include <source_location>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char* path);

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

// utility function to load the given image as texture
unsigned int loadTexture(const char* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
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

    // Setting current path
    std::filesystem::path source_file(std::source_location::current().file_name());
    std::string currentpath = source_file.parent_path();
    std::string projectpath = source_file.parent_path().parent_path().parent_path().parent_path();

    // Setting the paths of vertex and fragment shaders
    std::string vsPath = currentpath + "/specularmap.vs";
    std::string fsPath = currentpath + "/specularmap.fs";
    std::string lightvsPath = currentpath + "/light_cube.vs";
    std::string lightfsPath = currentpath + "/light_cube.fs";
    // build and compile the shader program
    Shader ourShader(vsPath.c_str(), fsPath.c_str());
    Shader lightingOurShader(lightvsPath.c_str(), lightfsPath.c_str());
    
    // set the vertices, color and texture
   float vertices[] = {
        // positions.          // normals        // texture co-ords

        // Back face.
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,      0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     0.0f, 0.0f, -1.0f,      1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     0.0f, 0.0f, -1.0f,      1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,      0.0f, 1.0f,

        // Front face
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 1.0f,       1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,       1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,       0.0f, 1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f, 0.0f, 0.0f,      0.0f, 1.0f,

        // Right face
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,       0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,       1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,       0.0f, 1.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,      0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,      1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,      1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,      0.0f, 1.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,       0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,       0.0f, 1.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture co-ord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //second configure the lighting cube's VAO
    glGenVertexArrays(1, &lightingVAO);

    glBindVertexArray(lightingVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // load diffuse map as texture
    std::string diffuseMapPath = projectpath + "/resources/container2.png";
    unsigned int diffuseMap = loadTexture(diffuseMapPath.c_str());

    // load specular map as texture
    std::string specularMapPath = projectpath + "/resources/container2_specular_colored.png";
    unsigned int specularMap = loadTexture(specularMapPath.c_str());
    
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
        ourShader.setInt("material.diffuse", 0);
        ourShader.setInt("material.specular", 1);

        ourShader.setVec3("light.position", lightPos);
        ourShader.setVec3("viewPos", camera.getPosition());

        // set the light properties
        ourShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        ourShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        //set the material properties
        ourShader.setFloat("material.shininess", 32.0f);
        
        unsigned int modelLoc = glGetUniformLocation(ourShader.getProgramID(), "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.getProgramID(), "view");
        unsigned int projectionLoc = glGetUniformLocation(ourShader.getProgramID(), "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);

        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

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
