#include <iostream>
// #define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecciones y transformaciones basicas", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define las dimensiones del viewport
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

    // enable alpha support
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Build and compile our shader program
    Shader ourShader("Shader/P2/core.vs", "Shader/P2/core.frag");

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
       -0.5f * 500, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Front
        0.5f * 500, -0.5f * 500, 0.5f * 500,  1.0f, 0.0f, 0.0f,
        0.5f * 500,  0.5f * 500, 0.5f * 500,  1.0f, 0.0f, 0.0f,
        0.5f * 500,  0.5f * 500, 0.5f * 500,  1.0f, 0.0f, 0.0f,
       -0.5f * 500,  0.5f * 500, 0.5f * 500, 1.0f, 0.0f, 0.0f,
       -0.5f * 500, -0.5f * 500, 0.5f * 500, 1.0f, 0.0f, 0.0f,

       -0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f, 0.0f, // Back
        0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f, 0.0f,
        0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f, 0.0f,
        0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f, 0.0f,
       -0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f, 0.0f,
       -0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f, 0.0f,

        0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f, 1.0f, // Right
        0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f, 1.0f,
        0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 0.0f, 1.0f,
        0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 0.0f, 1.0f,
        0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f, 1.0f,
        0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f, 1.0f,

       -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f, 0.0f, // Left
       -0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f, 0.0f,
       -0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f, 0.0f,
       -0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f, 0.0f,
       -0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 1.0f, 0.0f,
       -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f, 0.0f,

       -0.5f * 500, -0.5f * 500, -0.5f * 500, 0.0f, 1.0f, 1.0f, // Bottom
        0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f, 1.0f,
        0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 1.0f, 1.0f,
        0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 1.0f, 1.0f,
       -0.5f * 500, -0.5f * 500,  0.5f * 500, 0.0f, 1.0f, 1.0f,
       -0.5f * 500, -0.5f * 500, -0.5f * 500, 0.0f, 1.0f, 1.0f,

       -0.5f * 500,  0.5f * 500, -0.5f * 500, 1.0f, 0.2f, 0.5f, // Top
        0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 0.2f, 0.5f,
        0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.2f, 0.5f,
        0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.2f, 0.5f,
       -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.2f, 0.5f,
       -0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 0.2f, 0.5f,
    };
  
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::mat4(1);
    projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();

        glm::mat4 view = glm::mat4(1);
        glm::mat4 model = glm::mat4(1);

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);

        // --- CUBO 1: Superior Izquierdo (Rotado en X y Y) ---
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(250.0f, 450.0f, 0.0f)); // Posición
        model = glm::rotate(model, 0.8f, glm::vec3(1.0f, 1.0f, 0.0f)); // Rotación combinada
        model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));     // Escala uniforme
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- CUBO 2: Superior Derecho (Rotado levemente en Y) ---
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(550.0f, 450.0f, 0.0f));
        model = glm::rotate(model, 1.2f, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación en Y
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));        // Escala uniforme
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- CUBO 3: Inferior Izquierdo 
        
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(250.0f, 150.0f, 0.0f));
        model = glm::rotate(model, 0.4f, glm::vec3(1.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));        // 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- CUBO 4: Inferior Derecho 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(550.0f, 150.0f, 0.0f));
        model = glm::rotate(model, 0.2f, glm::vec3(0.0f, 1.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));      //
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return EXIT_SUCCESS;
}