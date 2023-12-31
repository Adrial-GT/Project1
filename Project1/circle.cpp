#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>
#include<iostream>
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PI = 3.14159265359f;
float progress = 0.0f;

void drawCircle(float cx, float cy, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawProgressBar() {
    float cx = 0.0f;
    float cy = 0.0f;
    float radius = 0.4f;
    int segments = 100;

    float progressAngle = 2.0f * PI * progress;

    glColor3f(0.2f, 0.2f, 0.2f); // Background color
    drawCircle(cx, cy, radius, segments);

    glColor3f(0.0f, 0.8f, 0.2f); // Progress color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments * progress; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD����ʧ�ܣ�" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Update progress value here (0.0 to 1.0)
        progress += 0.001f;
        if (progress > 1.0f)
            progress = 0.0f;

        drawProgressBar();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
