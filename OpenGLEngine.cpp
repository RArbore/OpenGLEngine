#include "OpenGLEngine.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

Camera camera(0.5f, 0.1f); // cameraSpeed, sensitivity

std::vector<float> vertices;
glm::vec3 lightPos;

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 0.5f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.goForwards();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.goBackwards();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.goLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.goRight();
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.goUp();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.goDown();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    camera.mouse_callback(window, xpos, ypos);
}

const unsigned int SCR_WIDTH = 1440;
const unsigned int SCR_HEIGHT = 900;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int OpenGLEngine::runRenderer()
{
    /* Cube vertices
    float cubeR = 0.0f;
    float cubeG = 0.0f;
    float cubeB = 0.0f;

    vertices = {
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,  -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  -1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, -1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  cubeR, cubeG, cubeB,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  cubeR, cubeG, cubeB,  0.0f, 1.0f, 0.0f,
    };
    */

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

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);  

    Shader ourShader("vertex.glsl", "fragment.glsl");

    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);  

    // info to map vertices to vertex shader inputs (position, color, normal)
    VAOInfo vaoInfo(3);
    vaoInfo.addAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    vaoInfo.addAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoInfo.addAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

    Model model(vertices, vaoInfo, ourShader);

    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float fps = 1.0f / deltaTime;

        std::cout << fps << std::endl;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();
        ourShader.setVec3("lightColor", lightColor);
        ourShader.setVec3("lightPos", lightPos);
        ourShader.setVec3("viewPos", camera.getCameraPosVector()); 

        camera.updateDirection();

        glm::mat4 view = camera.generateViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 15000.0f);

        glm::mat4 modelMatrix = glm::mat4(1.0f);

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        ourShader.setMat4("projection", projection);
        
        model.draw(GL_TRIANGLES, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    model.cleanUp();

    glfwTerminate();

    return 0;
}