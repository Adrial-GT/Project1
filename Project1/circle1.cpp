#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include<iostream>
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PI = 3.14159265359f;
float progress = 0.0f;

const char* vertexShaderSource = R"(
    #version 330 core
    uniform mat4 u_projectionMatrix;
    in vec2 a_position;

    void main() {
        gl_Position = u_projectionMatrix * vec4(a_position, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    uniform float u_progress;

    void drawCircle(float cx, float cy, float radius, int segments) {
        float angleStep = 2.0 * 3.14159265359 / segments;

        for (int i = 0; i <= segments; i++) {
            float angle = angleStep * i;
            float x = cx + radius * cos(angle);
            float y = cy + radius * sin(angle);
            float progressRadius = radius * u_progress;
            if (sqrt(x * x + y * y) <= progressRadius) {
                gl_FragColor = vec4(0.0, 0.8, 0.2, 1.0);
            } else {
                gl_FragColor = vec4(0.2, 0.2, 0.2, 1.0);
            }
        }
    }

    void main() {
        drawCircle(0.0, 0.0, 0.4, 100);
    }
)";

GLuint createShader(GLenum shaderType, const char* shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = (char*)malloc(length);
        glGetShaderInfoLog(shader, length, &length, infoLog);
        fprintf(stderr, "Failed to compile shader:\n%s\n", infoLog);
        free(infoLog);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Circular Progress Bar", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwTerminate();
        return -1;
    }

    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Bind attribute location for a_position
    glBindAttribLocation(shaderProgram, 0, "a_position");

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint progressUniform = glGetUniformLocation(shaderProgram, "u_progress");

    // Set up vertex data
    GLuint vao, vbo;
    float vertices[] = {
        0.0f, 0.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Update progress value here (0.0 to 1.0)
        progress += 0.001f;
        if (progress > 1.0f)
            progress = 0.0f;

        glUniform1f(progressUniform, progress);

        // Set up the projection matrix here
        float aspectRatio = (float)WINDOW_WIDTH / WINDOW_HEIGHT;
        float left = -aspectRatio;
        float right = aspectRatio;
        float bottom = -1.0f;
        float top = 1.0f;
        float nearVal = -1.0f;
        float farVal = 1.0f;

        glm::mat4 projectionMatrix = glm::ortho(left, right, bottom, top, nearVal, farVal);
        GLuint projectionMatrixUniform = glGetUniformLocation(shaderProgram, "u_projectionMatrix");
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_POINTS, 0, 1);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return 0;
}

