#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Turtle.hpp"
#include <iostream>
#include <vector>

typedef glm::vec2 vec2;
#define BUFFER_OFFSET(bytes) ((GLvoid*) (bytes)
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void draw_box(float width, float origin);
void init();
void display();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int VBO;
unsigned int VAO;


const int size = 8;

vec2 points[size];


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Turtle Shell", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    init();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// processes all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void draw_box( float width, float origin) {
    width = width / 100.f;

    float pos_length_size = origin + width;
    float neg_length_size = origin - width;

    vec2 box[4] = {
        vec2(origin,origin),
        vec2(pos_length_size, origin),
        vec2(pos_length_size, neg_length_size),
        vec2(origin, neg_length_size)
    };

    for (int i = 0; i < 4; ++i) {
        points[i] = box[i];
    }
}

void init() {

    draw_box(10.f,0.f);
    //TO DO: It seems I have to seperate the draw calls.
    draw_box(10.f,0.1f);

    Shader ourShader(RESOURCES_PATH "vertex.vc", RESOURCES_PATH "fragment.fc");
    ourShader.use();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Initialize the vertex position attribute from the vertex shader

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0,
        BUFFER_OFFSET(0)));
    glEnableVertexAttribArray(0);
}

void display() {
    glClearColor(0.f,0.f,0.f,1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_LINE_LOOP, 0, size);
}