#include "object.hpp"

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

void Object::DrawPoints() {
  glPointSize(5.0f);
  for (auto it = _pointCordData.begin(); it != _pointCordData.end(); it++) {
    glBegin(GL_POINTS);
    Shader(&(*it), _currentMaterial);
    glVertex3f(it->x / _focalLen / _proportion, it->y / _focalLen,
               it->z / _focalLen);
    glEnd();
  }
}

void Object::DrawEdges() {
  for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
    Triangle tri = *it;
    if (tri.mode == 1)
      DrawTriangleLine(*it);
    else if (tri.mode == 0)
      DrawRectangleLine(*it);
  }
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
    if (_faces % 2 == 0)
      Draw();
    if (_vertecies % 2 == 1)
      DrawPoints();
    if (_edges % 2 == 1)
      DrawEdges();
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
  _faces = 0;
  _vertecies = 0;
  _edges = 0;
  _renderTexture = 0;
}

void Object::RenderObject() {
  ProcessData();
  glfwInit();
  MakeLight();
  InitGLFW();
  glfwMakeContextCurrent(_window);
  SetupTexture("textures/riga.jpg");
  centerObject(_window);
  setupPoints();
  RunLoop();
  glfwTerminate();
}