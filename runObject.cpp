#include "object.hpp"

void Object::RenderObject() {
  ReadObj();
  ProcessData();
  glfwInit();
  _window = glfwCreateWindow(1920, 1080, "SCOP", NULL, NULL);
  if (!_window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    perror("Error");
    return;
  }
  glfwMakeContextCurrent(_window);
  while (!glfwWindowShouldClose(_window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Here I can Input my own stuff
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glfwSwapBuffers(_window);
    glfwPollEvents();
  }
  glfwTerminate();
}