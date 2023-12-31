#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Shader sources
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
uniform vec2 u_mouse;
out vec4 FragColor;
void main()
{
    vec3 color = vec3(u_mouse.x, 0.5, 0.5);
    FragColor = vec4(color, 1.0);
}
)";

// Mouse position
double mouseX = 0.0;

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Color Bar", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set the viewport size
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Register callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // Create and compile the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shaders as they're linked into the program and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers
    float vertices[] = {
        -1.0f, -0.1f, 0.0f, // Left-bottom vertex
         1.0f, -0.1f, 0.0f, // Right-bottom vertex
         1.0f,  0.1f, 0.0f, // Right-top vertex
        -1.0f,  0.1f, 0.0f  // Left-top vertex
    };

    unsigned int indices[] = {
        0, 1, 2, // First triangle
        0, 2, 3  // Second triangle
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input handling
        glfwPollEvents();

        // Clear the screen with a solid color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Set the mouse position as a uniform
        int mouseLocation = glGetUniformLocation(shaderProgram, "u_mouse");
        glUniform2f(mouseLocation, static_cast<float>(mouseX), 0.5f);

        // Draw the color bar
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
    }

    // Cleanup and exit
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

// Framebuffer resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Cursor position callback
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Normalize the mouse position to the range [-1, 1]
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    mouseX = static_cast<float>(xpos) / width * 2.0f - 1.0f;
}
