#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float yaw = 270.0f;
float pitch = 0.0f;
bool firstMouse = true;

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
}

float lastX = 400, lastY = 300;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw   += xoffset;
    pitch += yoffset;  
    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
}

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);  

    Shader ourShader("vertex.glsl", "fragment.glsl");
    Shader lightCubeShader("vertex.glsl", "light.glsl");

    float cubeR = 0.2f;
    float cubeG = 0.2f;
    float cubeB = 0.2f;

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,
        -0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,

        -0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,
         0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,
        -0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,
        -0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,

        -0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,
        -0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,
        -0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,
        -0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,

         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,
         0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,

        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,
         0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,
        -0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,

        -0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,
        -0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,
        -0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,
    };

    std::vector<glm::vec3> cubePositions;
    for (float x = 0; x < 5; x++) {
        for (float y = 0; y < 5; y++) {
            cubePositions.push_back(glm::vec3(x*1.1, y*1.1, 0.0f));
        }
    }

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 lightColor(0.9f, 0.4f, 0.6f);

    glEnable(GL_DEPTH_TEST);  

    unsigned int VBO, VAO, lightVAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();
        ourShader.setVec3("lightColor", lightColor);

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw));
        direction.z = sin(glm::radians(yaw));
        direction.y = 0.0f;
        cameraFront = glm::normalize(direction);
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction = glm::normalize(direction);
        view = glm::lookAt(cameraPos, cameraPos + direction, cameraUp);
        projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        for (unsigned int i = 0; i < cubePositions.size(); i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = model = glm::translate(model, cubePositions[i]);

            unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            ourShader.setMat4("projection", projection);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); 

        lightCubeShader.use();
        lightCubeShader.setVec3("lightColor", lightColor);

        unsigned int modelLoc = glGetUniformLocation(lightCubeShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(lightCubeShader.ID, "view");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        lightCubeShader.setMat4("projection", projection);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}