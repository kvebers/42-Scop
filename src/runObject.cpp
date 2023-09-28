#include "object.hpp"

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

void Object::CalculateMedium() {
  for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
    Triangle tri = *it;
    tri.medium = tri.points[0]->z;
    if (tri.medium > tri.points[1]->z)
      tri.medium = tri.points[1]->z;
    if (tri.medium > tri.points[2]->z)
      tri.medium = tri.points[2]->z;
    if (tri.mode == 0)
      if (tri.medium > tri.points[3]->z)
        tri.medium = tri.points[3]->z;
    it->medium = tri.medium;
  }
  std::sort(
      _drawData.begin(), _drawData.end(),
      [](const Triangle &a, const Triangle &b) { return a.medium < b.medium; });
}

void Object::Draw() {
  glfwGetWindowSize(_window, &_width, &_height);
  _proportion = static_cast<float>(_width) / static_cast<float>(_height);
  CalculateMedium();
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
    if (_material[0].d < 1) {
      glDepthMask(GL_FALSE);
      glEnable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
    } else
      glDepthMask(GL_TRUE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Draw();
    glfwSwapBuffers(_window);
    glfwPollEvents();
  }
}

void Object::MakeLight() {
  _focalLen = 5.0f;
  _lightData.x = 1.0f;
  _lightData.y = 1.0f;
  _lightData.z = 1.0f;
  _lightColor.x = 1.0f;
  _lightColor.y = 1.0f;
  _lightColor.z = 1.0f;
  _viewPos.x = 0.0f;
  _viewPos.y = 0.0f;
  _viewPos.z = 0.0f;
}

void Object::RenderObject() {
  ProcessData();
  glfwInit();
  MakeLight();
  InitGLFW();
  glfwMakeContextCurrent(_window);
  RunLoop();
  glfwTerminate();
}