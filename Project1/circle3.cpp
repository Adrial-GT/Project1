#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// Shader sources
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 Color;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    Color = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec3 Color;
uniform float innerRadius;
uniform float outerRadius;
uniform float progress;

void main()
{
    vec2 center = vec2(0.0, 0.0);
    float length = length(gl_FragCoord.xy - center.xy);
    
    float outerCircle = smoothstep(outerRadius, outerRadius + 0.02, length);
    float innerCircle = smoothstep(innerRadius, innerRadius + 0.02, length);
    float circle = outerCircle - innerCircle;
    
    // Calculate progress bar position
    float barStart = innerRadius;
    float barEnd = mix(innerRadius, outerRadius, progress);
    float progressBar = smoothstep(barStart, barEnd, length);
    
    // Check if the current pixel is within the circular progress bar
    float barMask = step(outerRadius, length) * (1.0 - step(innerRadius, length));
    
    // Calculate final color based on progress
    vec3 finalColor = mix(vec3(0.2, 0.2, 0.2), Color, progressBar);
    
    // Apply the color
    FragColor = vec4(finalColor, 1.0) * circle * barMask;
}
)";

float* generateCircleVertices(float radius, int numSegments) {
    const float PI = 3.14159265359f;
    float* vertices = new float[(numSegments + 2) * 6]; // 2 extra vertices for center and starting point
    int centerIndex = 0;
    int startingIndex = 6;
    float angleStep = 2.0f * PI / numSegments;

    // Center vertex
    vertices[centerIndex] = 0.0f;
    vertices[centerIndex + 1] = 0.0f;
    vertices[centerIndex + 2] = 0.0f;
    vertices[centerIndex + 3] = 0.2f;
    vertices[centerIndex + 4] = 0.2f;
    vertices[centerIndex + 5] = 0.2f;

    // Starting point vertex
    vertices[startingIndex] = radius;
    vertices[startingIndex + 1] = 0.0f;
    vertices[startingIndex + 2] = 0.0f;
    vertices[startingIndex + 3] = 1.0f;
    vertices[startingIndex + 4] = 0.0f;
    vertices[startingIndex + 5] = 0.0f;

    for (int i = 1; i <= numSegments; ++i) {
        float angle = angleStep * i;
        int vertexIndex = startingIndex + i * 6;
        vertices[vertexIndex] = radius * cos(angle);
        vertices[vertexIndex + 1] = radius * sin(angle);
        vertices[vertexIndex + 2] = 0.0f;
        vertices[vertexIndex + 3] = 1.0f;
        vertices[vertexIndex + 4] = 0.0f;
        vertices[vertexIndex + 5] = 0.0f;
    }

    return vertices;
}

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Circular Progress Bar", NULL, NULL);
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
    const int numSegments = 100;
    float* vertices = generateCircleVertices(0.6f, numSegments);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (numSegments + 2) * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input handling
        glfwPollEvents();

        // Calculate the progress of the circular progress bar (ranging from 0 to 1)
        float progress = (sin(glfwGetTime()) + 1.0f) / 2.0f;

        // Clear the screen with a solid color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Set the color and progress uniform variables in the fragment shader
        int innerRadiusLoc = glGetUniformLocation(shaderProgram, "innerRadius");
        glUniform1f(innerRadiusLoc, 0.4f); // Inner circle radius

        int outerRadiusLoc = glGetUniformLocation(shaderProgram, "outerRadius");
        glUniform1f(outerRadiusLoc, 0.6f); // Outer circle radius

        int progressLoc = glGetUniformLocation(shaderProgram, "progress");
        glUniform1f(progressLoc, progress);

        // Draw the circular progress bar
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 2);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
    }

    // Cleanup and exit
    delete[] vertices;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
