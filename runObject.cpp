#include "object.hpp"

void Object::DrawTriangle(Triangle &triangle) {
  glBegin(GL_TRIANGLES);
  glVertex2f(triangle.points[0].x, triangle.points[0].y);
  glVertex2f(triangle.points[1].x, triangle.points[1].y);
  glVertex2f(triangle.points[2].x, triangle.points[2].y);
  glEnd();
}

void Object::InitGLFW() {
  _window = glfwCreateWindow(2560, 1920, "SCOP", NULL, NULL);
  if (!_window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    perror("Error");
    return;
  }
}

void Object::Draw() {
  for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
    DrawTriangle(*it);
  }
}

void Object::RunLoop() {
  while (!glfwWindowShouldClose(_window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Draw();
    glfwSwapBuffers(_window);
    glfwPollEvents();
  }
}

void Object::RenderObject() {
  ProcessData();
  glfwInit();
  InitGLFW();
  glfwMakeContextCurrent(_window);
  RunLoop();
  glfwTerminate();
}