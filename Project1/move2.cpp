#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

// ������ɫ������
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

// Ƭ����ɫ������
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

int main() {
    // ��ʼ��GLFW
    if (!glfwInit()) {
        std::cout << "GLFW��ʼ��ʧ�ܣ�" << std::endl;
        return -1;
    }

    // ����GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ��������
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "�ƶ�������", nullptr, nullptr);
    if (!window) {
        std::cout << "���ڴ���ʧ�ܣ�" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ���õ�ǰ������
    glfwMakeContextCurrent(window);

    // ����GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD����ʧ�ܣ�" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ���붥����ɫ��
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // ��鶥����ɫ���Ƿ����ɹ�
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "������ɫ������ʧ�ܣ�" << infoLog << std::endl;
    }

    // ����Ƭ����ɫ��
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // ���Ƭ����ɫ���Ƿ����ɹ�
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Ƭ����ɫ������ʧ�ܣ�" << infoLog << std::endl;
    }

    // ������ɫ������
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // �����ɫ�������Ƿ����ӳɹ�
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "��ɫ����������ʧ�ܣ�" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ���������εĶ�������
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    // ���������ε���������
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // �������㻺�����������������
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // �󶨶����������ͻ������
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ���VAO�ͻ������
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window)) {
        // ����Ƿ���Ҫ�رմ���
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // ʹ��ʱ��������ƫ������ʵ���Զ��ƶ�Ч��
        float time = glfwGetTime();
        float speed = 0.5f;
        float offsetX = sin(time * speed);
        float offsetY = cos(time * speed);

        // ��Ⱦָ��
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // ���¶������ݣ�����ƫ�����ƶ�������
        float updatedVertices[] = {
            -0.5f + offsetX, -0.5f + offsetY, 0.0f,
             0.5f + offsetX, -0.5f + offsetY, 0.0f,
             0.5f + offsetX,  0.5f + offsetY, 0.0f,
            -0.5f + offsetX,  0.5f + offsetY, 0.0f,
        };
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(updatedVertices), updatedVertices, GL_STATIC_DRAW);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // �����������ͻ�ȡ�¼�
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ����������Դ
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // ��ֹGLFW
    glfwTerminate();
    return 0;
}
