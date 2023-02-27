#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos,1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Actividad de Portafolio No.1: Tangram de Perrito", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float Tamgram[] =
    {
         0.02f,0.37f,0.0f,    0.968, 0.737, 0.690, // Punto No.0
         0.13f,0.44f,0.0f,    0.968, 0.737, 0.690, // Punto No.1
         -0.14f,0.60f,0.0f,   0.968, 0.737, 0.690, // Punto No.2

         0.02f,0.37f,0.0f,    0.690, 0.968, 0.941, // Punto No.3
         -0.15f,0.36f,0.0f,   0.690, 0.968, 0.941, // Punto No.4
         -0.14f,0.60f,0.0f,   0.690, 0.968, 0.941, // Punto No.5

         -0.33f,0.68f,0.0f,   0.862, 0.968, 0.690, // Punto No.6
         -0.18f,0.62f,0.0f,   0.862, 0.968, 0.690, // Punto No.7
         -0.20f,0.58f,0.0f,   0.862, 0.968, 0.690, // Punto No.8

         -0.37f,0.51f,0.0f,   0.886, 0.690, 0.968, // Punto No.9
         -0.26f,0.60f,0.0f,   0.886, 0.690, 0.968, // Punto No.10
         -0.22f,0.53f,0.0f,   0.886, 0.690, 0.968, // Punto No.11

         -0.32f,0.24f,0.0f,   0.968, 0.850, 0.690, // Punto No.12
         -0.30f,0.08f,0.0f,   0.968, 0.850, 0.690, // Punto No.13
         -0.2f,0.1f,0.0f,     0.968, 0.850, 0.690, // Punto No.14

         0.02f,0.37f,0.0f,    1, 0.682, 0.819, // Punto No.15
         -0.18f,0.02f,0.0f,   1, 0.682, 0.819, // Punto No.16
         0.02f,-0.0f,0.0f,    1, 0.682, 0.819, // Punto No.17

         0.02f,0.37f,0.0f,    0.682, 0.901, 1, // Punto No.18
         0.18f,0.02f,0.0f,    0.682, 0.901, 1, // Punto No.19
         0.02f,-0.0f,0.0f,    0.682, 0.901, 1, // Punto No.20

    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2, //Triangulo No.1
        3, 4, 5, //Triangulo No.2
        6, 7, 8, //Triangulo No.3
        9, 10, 11, //Triangulo No.4
        12, 13, 14, //Triangulo No.5
        15, 16, 17, //Triangulo No.6
        18, 19, 20, //Triangulo No.7
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Tamgram), Tamgram, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Column Major
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //Column Major
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //Column Major
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram);
        glLineWidth(20.0);
        glPointSize(20.0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 30);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
