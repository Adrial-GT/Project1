#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

// 顶点着色器代码
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        gl_Position = projection * view * vec4(aPos, 1.0);
    }
)";

// 片段着色器代码
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

int main() {
    // 初始化GLFW
    if (!glfwInit()) {
        std::cout << "GLFW初始化失败！" << std::endl;
        return -1;
    }

    // 配置GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3D箱子", nullptr, nullptr);
    if (!window) {
        std::cout << "窗口创建失败！" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 设置当前上下文
    glfwMakeContextCurrent(window);

    // 加载GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD加载失败！" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 编译顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 检查顶点着色器是否编译成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "顶点着色器编译失败：" << infoLog << std::endl;
    }

    // 编译片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // 检查片段着色器是否编译成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "片段着色器编译失败：" << infoLog << std::endl;
    }

    // 创建着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 检查着色器程序是否链接成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "着色器程序链接失败：" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 设置立方体的顶点数据
    float vertices[] = {
        // 前面
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        // 后面
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    // 设置立方体的索引数据
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 3, 7,
        7, 4, 0,
        1, 2, 6,
        6, 5, 1,
        3, 2, 6,
        6, 7, 3,
        0, 1, 5,
        5, 4, 0,
    };

    // 创建顶点缓冲对象和索引缓冲对象
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 绑定顶点数组对象和缓冲对象
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 解绑VAO和缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 设置摄像机参数
    glm::vec3 cameraPos(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // 计算摄像机的观察矩阵
    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    // 设置透视投影矩阵
    float fov = 45.0f;
    float aspectRatio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
    float nearClip = 0.1f;
    float farClip = 100.0f;
    glm::mat4 projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);

    // 获取view和projection的uniform变量的位置
    int viewLocation = glGetUniformLocation(shaderProgram, "view");
    int projectionLocation = glGetUniformLocation(shaderProgram, "projection");

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 检查是否需要关闭窗口
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // 更新摄像机观察矩阵和透视投影矩阵的值
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        // 绘制立方体
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // 交换缓冲区和获取事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清除分配的资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // 终止GLFW
    glfwTerminate();
    return 0;
}
