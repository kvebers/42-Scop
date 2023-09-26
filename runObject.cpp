#include "object.hpp"

void Object::RandomColor() {
  float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  glColor3f(r, g, b);
}

void Object::DrawRectangle(Triangle &rectangle) {
  RandomColor();
  glBegin(GL_QUADS);
  glVertex3f(rectangle.points[0].x / _focalLen / _proportion,
             rectangle.points[0].y / _focalLen,
             rectangle.points[0].z / _focalLen);
  glVertex3f(rectangle.points[1].x / _focalLen / _proportion,
             rectangle.points[1].y / _focalLen,
             rectangle.points[1].z / _focalLen);
  glVertex3f(rectangle.points[2].x / _focalLen / _proportion,
             rectangle.points[2].y / _focalLen,
             rectangle.points[2].z / _focalLen);
  glVertex3f(rectangle.points[3].x / _focalLen / _proportion,
             rectangle.points[3].y / _focalLen,
             rectangle.points[3].z / _focalLen);
  glEnd();
}

void Object::DrawTriangle(Triangle &triangle) {
  RandomColor();
  glBegin(GL_TRIANGLES);
  glVertex3f(triangle.points[0].x / _focalLen / _proportion,
             triangle.points[0].y / _focalLen,
             triangle.points[0].z / _focalLen);
  glVertex3f(triangle.points[1].x / _focalLen / _proportion,
             triangle.points[1].y / _focalLen,
             triangle.points[1].z / _focalLen);
  glVertex3f(triangle.points[2].x / _focalLen / _proportion,
             triangle.points[2].y / _focalLen,
             triangle.points[2].z / _focalLen);
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
  glfwGetWindowSize(_window, &_width, &_height);
  _proportion = static_cast<float>(_width) / static_cast<float>(_height);
  for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
    Triangle tri = *it;
    if (tri.mode == 1)
      DrawTriangle(*it);
    else if (tri.mode == 0)
      DrawRectangle(*it);
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

void Object::MakeLight() { _focalLen = 5.0f; }

void Object::RenderObject() {
  ProcessData();
  glfwInit();
  MakeLight();
  InitGLFW();
  glfwMakeContextCurrent(_window);
  RunLoop();
  glfwTerminate();
}