#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    void main() {
        gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    uniform float progress; // 进度值，范围为0到1
    uniform vec2 resolution; // 屏幕分辨率

    out vec4 FragColor;

    void main() {
        // 计算片段在屏幕上的位置，将屏幕中心设为圆心
        vec2 center = resolution / 2.0;
        vec2 position = gl_FragCoord.xy - center;

        // 计算片段与圆心的距离
        float distance = length(position);

        // 计算圆的半径，这里我们假设屏幕高度的一半为圆的半径
        float radius = resolution.y / 2.0;

        // 根据距离和进度值决定片段的颜色
        if (distance <= radius) {
            float angle = atan(position.y, position.x); // 计算片段与圆心的角度
            float progressAngle = progress * 2.0 * 3.1415926; // 进度值转换为角度

            if (angle <= progressAngle) {
                // 进度部分的颜色，这里使用绿色
                FragColor = vec4(0.0, 1.0, 0.0, 1.0);
            } else {
                // 非进度部分的颜色，这里使用灰色
                FragColor = vec4(0.5, 0.5, 0.5, 1.0);
            }
        } else {
            // 超出圆的区域为透明
            FragColor = vec4(0.0, 0.0, 0.0, 0.0);
        }
    }
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "无法初始化GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Circle Progress Bar", nullptr, nullptr);
    if (!window) {
        std::cerr << "无法创建窗口" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "无法初始化GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // 编译着色器程序
    unsigned int vertexShader, fragmentShader, shaderProgram;

    // 顶点着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // 片段着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 着色器程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 设置绘制圆形进度条的顶点数据
    unsigned int VBO, VAO;
    const float vertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(shaderProgram);

    // 获取uniform变量的位置
    int progressLocation = glGetUniformLocation(shaderProgram, "progress");
    int resolutionLocation = glGetUniformLocation(shaderProgram, "resolution");

    // 渲染循环
    float startTime = glfwGetTime(); // 记录开始时间
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime(); // 当前时间
        float deltaTime = currentTime - startTime; // 经过的时间

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 更新进度值，假设每2秒增加0.1来表示动画效果
        float progress = fmod(deltaTime / 2.0f, 1.0f);

        // 更新uniform变量的值
        glUniform1f(progressLocation, progress);
        glUniform2f(resolutionLocation, WINDOW_WIDTH, WINDOW_HEIGHT);

        // 绘制全屏四边形
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
