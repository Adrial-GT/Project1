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
    uniform float progress; // ����ֵ����ΧΪ0��1
    uniform vec2 resolution; // ��Ļ�ֱ���

    out vec4 FragColor;

    void main() {
        // ��Ƭ������ת��Ϊ��Բ��(0.0, 0.0)Ϊԭ�������
        vec2 position = (gl_FragCoord.xy - resolution) / resolution.y;

        // ����Ƭ����Բ�ĵĽǶ�
        float angle = atan(position.y, position.x);

        // ���Ƕ�ת����0��2��֮��
        if (angle < 0.0) {
            angle += 2.0 * 3.1415926;
        }

        // �������ֵ��Ӧ�ĽǶ�
        float progressAngle = progress * 2.0 * 3.1415926;

        // ����СԲ�ʹ�Բ�İ뾶���������Ǽ�����Ļ�߶ȵ�һ��Ϊ��Բ�İ뾶
        float smallRadius = resolution.y / 4.0;
        float bigRadius = resolution.y / 2.0;

        // ���ݽǶȺͽ���ֵ����Ƭ�ε���ɫ
        if (angle >= progressAngle && length(position) >= smallRadius && length(position) <= bigRadius) {
            // ���Ȳ��ֵ���ɫ������ʹ����ɫ
            FragColor = vec4(0.0, 1.0, 0.0, 1.0);
        } else if (length(position) >= smallRadius && length(position) <= bigRadius) {
            // �ǽ��Ȳ��ֵ���ɫ������ʹ�û�ɫ
            FragColor = vec4(0.5, 0.5, 0.5, 1.0);
        } else {
            // ��������Բ������Ϊ͸��
            FragColor = vec4(0.0, 0.0, 0.0, 0.0);
        }
    }
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "�޷���ʼ��GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Circle Progress Bar", nullptr, nullptr);
    if (!window) {
        std::cerr << "�޷���������" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "�޷���ʼ��GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // ������ɫ������
    unsigned int vertexShader, fragmentShader, shaderProgram;

    // ������ɫ��
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Ƭ����ɫ��
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // ��ɫ������
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ���û���Բ�ν������Ķ�������
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

    // ��ȡuniform������λ��
    int progressLocation = glGetUniformLocation(shaderProgram, "progress");
    int resolutionLocation = glGetUniformLocation(shaderProgram, "resolution");

    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime(); // ��ǰʱ��
        float deltaTime = currentTime; // ������ʱ��

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ���½���ֵ������ÿ2������0.1����ʾ����Ч��
        float progress = fmod(deltaTime / 2.0f, 1.0f);

        // ����uniform������ֵ
        glUniform1f(progressLocation, progress);
        glUniform2f(resolutionLocation, WINDOW_WIDTH, WINDOW_HEIGHT);

        // ����ȫ���ı���
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

