#include "object.hpp"

void Object::DrawRectangle(Triangle &rectangle) {
  glBegin(GL_QUADS);
  Shader(rectangle.points[0]);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[0]->x + 1) / 2,
                 (rectangle.points[0]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[0].x, rectangle.initialPoints[0].y);
  glVertex3f(rectangle.points[0]->x / _focalLen / _proportion,
             rectangle.points[0]->y / _focalLen,
             rectangle.points[0]->z / _focalLen);
  Shader(rectangle.points[1]);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[1]->x + 1) / 2,
                 (rectangle.points[1]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[1].x, rectangle.initialPoints[1].y);
  glVertex3f(rectangle.points[1]->x / _focalLen / _proportion,
             rectangle.points[1]->y / _focalLen,
             rectangle.points[1]->z / _focalLen);
  Shader(rectangle.points[2]);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[2]->x + 1) / 2,
                 (rectangle.points[2]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[2].x, rectangle.initialPoints[2].y);
  glVertex3f(rectangle.points[2]->x / _focalLen / _proportion,
             rectangle.points[2]->y / _focalLen,
             rectangle.points[2]->z / _focalLen);
  Shader(rectangle.points[3]);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[3]->x + 1) / 2,
                 (rectangle.points[3]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[3].x, rectangle.initialPoints[3].y);
  glVertex3f(rectangle.points[3]->x / _focalLen / _proportion,
             rectangle.points[3]->y / _focalLen,
             rectangle.points[3]->z / _focalLen);
  glEnd();
}

void Object::DrawTriangle(Triangle &triangle) {
  glBegin(GL_TRIANGLES);
  Shader(triangle.points[0]);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[0]->x + 1) / 2,
                 (triangle.points[0]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[0].x, triangle.initialPoints[0].y);
  glVertex3f(triangle.points[0]->x / _focalLen / _proportion,
             triangle.points[0]->y / _focalLen,
             triangle.points[0]->z / _focalLen);
  Shader(triangle.points[1]);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[1]->x + 1) / 2,
                 (triangle.points[1]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[1].x, triangle.initialPoints[1].y);
  glVertex3f(triangle.points[1]->x / _focalLen / _proportion,
             triangle.points[1]->y / _focalLen,
             triangle.points[1]->z / _focalLen);
  Shader(triangle.points[2]);
  if (_renderTexture == 1)
    glTexCoord2f(0.5f, 0.5f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[2]->x + 1) / 2,
                 (triangle.points[2]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[2].x, triangle.initialPoints[2].y);
  glVertex3f(triangle.points[2]->x / _focalLen / _proportion,
             triangle.points[2]->y / _focalLen,
             triangle.points[2]->z / _focalLen);
  glEnd();
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

void Object::InitGLFW() {
  _window = glfwCreateWindow(2560, 1920, "SCOP", NULL, NULL);
  if (!_window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(127);
  }
  glfwSetWindowUserPointer(_window, this);
  glfwSetMouseButtonCallback(_window, mouseButtonCallback);
  glfwSetCursorPosCallback(_window, handleMouseMove);
  glfwSetScrollCallback(_window, scrollCallback);
  glfwSetKeyCallback(_window, keyCallback);
}

void Object::CalculateMedium() {
  for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
    Triangle tri = *it;
    tri.medium = (tri.points[0]->z + tri.points[1]->z + tri.points[2]->z) / 3;
    it->medium = tri.medium;
  }
  std::sort(
      _drawData.begin(), _drawData.end(),
      [](const Triangle &a, const Triangle &b) { return a.medium < b.medium; });
}

void Object::RunLoop() {
  while (!glfwWindowShouldClose(_window)) {
    glfwSetScrollCallback(_window, Object::scrollCallback);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (_material[_currentMaterial].d < 1) {
      glDepthMask(GL_FALSE);
      glEnable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
    } else {
      glDepthMask(GL_TRUE);
      glDisable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);
    }
    if (_renderTexture > 0) {
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, _texture2D);
    } else {
      glDisable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, 0);
      glUseProgram(0);
    }
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
  _currentMaterial = 0;
  _colorMode = 1;
  _renderTexture = 0;
}

void Object::RenderObject() {
  ProcessData();
  glfwInit();
  MakeLight();
  InitGLFW();
  glfwMakeContextCurrent(_window);
  SetupTexture("textures/ok.jpg");
  centerObject(_window);
  setupPoints();
  RunLoop();
  glfwTerminate();
}