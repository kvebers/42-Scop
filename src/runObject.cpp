#include "object.hpp"

void Object::Shader(Vector3 *point) {
  Vector3 magnitude;
  float magHelper =
      sqrt(point->x * point->x + point->y + point->y + point->z * point->z);
  if (magHelper == 0) {
    magnitude.x = 0;
    magnitude.y = 0;
    magnitude.z = 0;
  } else {
    magnitude.x = point->x / magHelper;
    magnitude.y = point->y / magHelper;
    magnitude.z = point->z / magHelper;
  }

  glColor3f(magnitude.x, magnitude.y, magnitude.z);
}

void Object::DrawRectangle(Triangle &rectangle) {
  glBegin(GL_QUADS);
  Shader(rectangle.points[0]);
  glVertex3f(rectangle.points[0]->x / _focalLen / _proportion,
             rectangle.points[0]->y / _focalLen,
             rectangle.points[0]->z / _focalLen);
  Shader(rectangle.points[1]);
  glVertex3f(rectangle.points[1]->x / _focalLen / _proportion,
             rectangle.points[1]->y / _focalLen,
             rectangle.points[1]->z / _focalLen);
  Shader(rectangle.points[2]);
  glVertex3f(rectangle.points[2]->x / _focalLen / _proportion,
             rectangle.points[2]->y / _focalLen,
             rectangle.points[2]->z / _focalLen);
  Shader(rectangle.points[3]);
  glVertex3f(rectangle.points[3]->x / _focalLen / _proportion,
             rectangle.points[3]->y / _focalLen,
             rectangle.points[3]->z / _focalLen);
  glEnd();
}

void Object::DrawTriangle(Triangle &triangle) {
  glBegin(GL_TRIANGLES);
  Shader(triangle.points[0]);
  glVertex3f(triangle.points[0]->x / _focalLen / _proportion,
             triangle.points[0]->y / _focalLen,
             triangle.points[0]->z / _focalLen);
  Shader(triangle.points[1]);
  glVertex3f(triangle.points[1]->x / _focalLen / _proportion,
             triangle.points[1]->y / _focalLen,
             triangle.points[1]->z / _focalLen);
  Shader(triangle.points[2]);
  glVertex3f(triangle.points[2]->x / _focalLen / _proportion,
             triangle.points[2]->y / _focalLen,
             triangle.points[2]->z / _focalLen);
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
  glfwSetWindowUserPointer(_window, this);
  glfwSetMouseButtonCallback(_window, mouseButtonCallback);
  glfwSetCursorPosCallback(_window, handleMouseMove);
  glfwSetScrollCallback(_window, Object::scrollCallback);
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
    glfwSetScrollCallback(_window, Object::scrollCallback);
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