#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include <stdlib.h>
#include <stdio.h>

static const char* fragment_shader_text =
"uniform vec2 R;"
"void main()\n"
"{\n"
"    vec2 uv = gl_FragCoord.xy / R * 2. - 1.;"
"    gl_FragColor = vec4(uv, 0.0, 1.0);\n"
"}\n";
 
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
 
int main(void)
{
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
 
    GLFWwindow* const window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
 
    glfwSetKeyCallback(window, key_callback);
 
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);
 
    // NOTE: OpenGL error checks have been omitted for brevity
 
    const GLuint program = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragment_shader_text);
    const GLint res_location = glGetUniformLocation(program, "R");
 
    glUseProgram(program);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
 
        glfwGetFramebufferSize(window, &width, &height);
 
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
 
        glUniform2f(res_location, (GLfloat)width, (GLfloat)height);
        glRectf(-1,-1,1,1);
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    return 0;
}