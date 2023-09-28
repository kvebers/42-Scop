#include "object.hpp"

void Object::DrawRectangle(Triangle &rectangle) {
  glBegin(GL_QUADS);
  Shader(rectangle.points[0]);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 0.0f);
  glVertex3f(rectangle.points[0]->x / _focalLen / _proportion,
             rectangle.points[0]->y / _focalLen,
             rectangle.points[0]->z / _focalLen);
  Shader(rectangle.points[1]);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 0.0f);
  glVertex3f(rectangle.points[1]->x / _focalLen / _proportion,
             rectangle.points[1]->y / _focalLen,
             rectangle.points[1]->z / _focalLen);
  Shader(rectangle.points[2]);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 1.0f);
  glVertex3f(rectangle.points[2]->x / _focalLen / _proportion,
             rectangle.points[2]->y / _focalLen,
             rectangle.points[2]->z / _focalLen);
  Shader(rectangle.points[3]);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
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
  glVertex3f(triangle.points[0]->x / _focalLen / _proportion,
             triangle.points[0]->y / _focalLen,
             triangle.points[0]->z / _focalLen);
  Shader(triangle.points[1]);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
  glVertex3f(triangle.points[1]->x / _focalLen / _proportion,
             triangle.points[1]->y / _focalLen,
             triangle.points[1]->z / _focalLen);
  Shader(triangle.points[2]);
  if (_renderTexture == 1)
    glTexCoord2f(0.5f, 0.5f);
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
    perror("Error");
    return;
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
    } else
      glDepthMask(GL_TRUE);
    if (_renderTexture == 1) {
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, _texture2D);
    } else {
      glDisable(GL_TEXTURE_2D);
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
  std::string path = "textures/riga.jpg";
  SetupTexture(path);
  centerObject(_window);
  RunLoop();
  glfwTerminate();
}