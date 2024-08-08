#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "config.h"

unsigned int make_module(const std::string& filepath, unsigned int module_type);

unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {

    std::vector<unsigned int> modules;
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));


    unsigned int shader = glCreateProgram();
    for (unsigned int shaderModule : modules) {
        glAttachShader(shader, shaderModule);
    }  
    glLinkProgram(shader);

       int success;
    glGetShaderiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader Linking error:\n" << errorLog << std::endl;
    }

     for (unsigned int shaderModule : modules) {
        glDeleteShader(shaderModule);
    }

    return shader;


}

unsigned int make_module(const std::string& filepath, unsigned int module_type) {

    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line)) {
        bufferedLines << line << "\n";
    }
    std::string shaderSource = bufferedLines.str();
    const char* shaderSrc = shaderSource.c_str();
    bufferedLines.str("");
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;
    }
    return shaderModule;
}

int main() {

    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }
    
    window = glfwCreateWindow(800, 600, "window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Couldn't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }
    

    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    unsigned int shader = make_shader(
        "../shaders/vertex.txt",
        "../shaders/fragment.txt"
    );

    while (!glfwWindowShouldClose(window))  {
        glfwPollEvents();


        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);

        glfwSwapBuffers(window);

    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;

}




