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
void koch_snowflake(const vec2& a, const vec2& b, int depth);
void init();
void display();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int VBO;
unsigned int VAO;


const int depth = 5;
const int size = 3 * 1024;
int counter = 0;
float y_offset = 0.5f;
float epsilon = 0.025f;

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

void koch_snowflake(const vec2& a, const vec2& b, int depth)
{

    if (depth == 0)
    {
        points[counter++] = b;
        return;
    }
    vec2 v0 = a + ((b - a)/ 3.0f);
    vec2 v2 = a + (2.f / 3 * (b - a));
    vec2 d = v2 - v0;
    float c = 0.5;
    float s = 0.8660254;
    vec2 drot = vec2(c * d.x -  s * d.y, s * d.x + c * d.y);
    vec2 v1 = (v0 + drot);

    koch_snowflake(a, v0, depth - 1);
    koch_snowflake(v0, v1, depth - 1);
    koch_snowflake(v1, v2, depth - 1);
    koch_snowflake(v2, b, depth - 1);
}


void init() {


    //provide data for triangle
    vec2 triangle[3] = { vec2(-0.5, 0.5), vec2(0.5,0.5), vec2(0, -0.5) };
    points[counter] = triangle[0];
    counter++;
    koch_snowflake(triangle[0], triangle[1], depth);
    koch_snowflake(triangle[1], triangle[2], depth);
    koch_snowflake(triangle[2], triangle[0], depth);

    for (int i = 0; i < size; ++i)
    {
        std::cout << points[i].x <<",y: " << points[i].y << std::endl;
    }

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