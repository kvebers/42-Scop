#include "object.hpp"

void Object::centerObject(GLFWwindow *window) {
  Object *objInstance = static_cast<Object *>(glfwGetWindowUserPointer(window));
  int cnt = 0;
  float offsetX = 0;
  float offsetY = 0;
  float offsetZ = 0;
  for (auto it = objInstance->_pointCordData.begin();
       it != objInstance->_pointCordData.end(); it++) {
    offsetX += it->x;
    offsetY += it->y;
    offsetZ += it->z;
    cnt++;
  }
  if (cnt == 0)
    return;
  offsetX /= cnt;
  offsetY /= cnt;
  offsetZ /= cnt;
  for (auto it = objInstance->_pointCordData.begin();
       it != objInstance->_pointCordData.end(); it++) {
    it->x -= offsetX;
    it->y -= offsetY;
    it->z -= offsetZ;
  }
}

void Object::colorMode(Object *objInstance) {
  if (objInstance->_colorMode > 0)
    objInstance->_colorMode = -1;
  else
    objInstance->_colorMode = 1;
}

void Object::changeColor(float *color, int colorMode) {
  *color += colorMode * 0.1;
  if (*color > 1.0f) {
    *color = 1.0f;
  } else if (*color < 0.0f) {
    *color = 0.0f;
  }
}

void Object::keyCallback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  (void)scancode;
  (void)mods;
  Object *objInstance = static_cast<Object *>(glfwGetWindowUserPointer(window));
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    switch (key) {
    case GLFW_KEY_1:
      objInstance->_currentMaterial = 0;
      objInstance->_renderTexture = 0;
      break;
    case GLFW_KEY_2:
      objInstance->_currentMaterial = 1;
      objInstance->_renderTexture = 0;
      break;
    case GLFW_KEY_3:
      objInstance->_currentMaterial = 2;
      objInstance->_renderTexture = 0;
      break;
    case GLFW_KEY_4:
      objInstance->_currentMaterial = 3;
      objInstance->_renderTexture = 0;
      break;
    case GLFW_KEY_5:
      objInstance->_currentMaterial = 4;
      objInstance->_renderTexture = 0;
      break;
    case GLFW_KEY_6:
      objInstance->_renderTexture = 1;
      break;
    case GLFW_KEY_7:
      objInstance->_renderTexture = 2;
      break;
    case GLFW_KEY_8:
      objInstance->_renderTexture = 3;
      break;
    case GLFW_KEY_9:
      objInstance->_faces++;
      break;
    case GLFW_KEY_0:
      objInstance->_vertecies++;
      break;
    case GLFW_KEY_MINUS:
      objInstance->_edges++;
      break;
    case GLFW_KEY_Q:
      changeColor(&objInstance->_material[objInstance->_currentMaterial].Ka.x,
                  objInstance->_colorMode);
      break;
    case GLFW_KEY_W:
      changeColor(&objInstance->_material[objInstance->_currentMaterial].Ka.y,
                  objInstance->_colorMode);
      break;
    case GLFW_KEY_E:
      changeColor(&objInstance->_material[objInstance->_currentMaterial].Ka.z,
                  objInstance->_colorMode);
      break;
    case GLFW_KEY_R:
      changeColor(&objInstance->_material[objInstance->_currentMaterial].d,
                  objInstance->_colorMode);
      break;
    case GLFW_KEY_T:
      colorMode(objInstance);
      break;
    case GLFW_KEY_SPACE:
      centerObject(window);
      break;
    }
  }
}
