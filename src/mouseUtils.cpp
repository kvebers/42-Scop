#include "object.hpp"

void Object::scrollCallback(GLFWwindow *window, double xoffset,
                            double yoffset) {
  Object *objInstance = static_cast<Object *>(glfwGetWindowUserPointer(window));
  (void)xoffset;
  if (objInstance) {
    if (objInstance->_focalLen - yoffset > 2 &&
        objInstance->_focalLen - yoffset < 200)
      objInstance->_focalLen -= yoffset;
  }
}

void Object::mouseButtonCallback(GLFWwindow *window, int button, int action,
                                 int mods) {
  Object *objInstance = static_cast<Object *>(glfwGetWindowUserPointer(window));
  (void)mods;
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS) {
      glfwGetCursorPos(objInstance->_window, &objInstance->_lastX,
                       &objInstance->_lastY);
      objInstance->_isDragging = true;
    } else if (action == GLFW_RELEASE) {
      objInstance->_isDragging = false;
    }
  }
  if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    if (action == GLFW_PRESS) {
      glfwGetCursorPos(objInstance->_window, &objInstance->_lastX,
                       &objInstance->_lastY);
      objInstance->_isMoved = true;
    } else if (action == GLFW_RELEASE) {
      objInstance->_isMoved = false;
    }
  }
  if (objInstance->_isMoved == true && objInstance->_isDragging == true) {
    objInstance->_isMoved = false;
    objInstance->_isDragging = false;
  }
}

void Object::handleRotation(Object *objInstance, double xpos, double ypos) {
  double deltaX = xpos - objInstance->_lastX;
  double deltaY = ypos - objInstance->_lastY;
  objInstance->_lastX = xpos;
  objInstance->_lastY = ypos;
  deltaX /= 100;
  deltaY /= 100;
  for (auto it = objInstance->_pointCordData.begin();
       it != objInstance->_pointCordData.end(); it++) {
    Vector3 &points = *it;
    float oldY = points.y;
    float oldX = points.x;
    points.y = oldY * cos(deltaY) - points.z * sin(deltaY);
    points.z = oldY * sin(deltaY) + points.z * cos(deltaY);
    points.x = oldX * cos(deltaX) + points.z * sin(deltaX);
    points.z = -oldX * sin(deltaX) + points.z * cos(deltaX);
  }
}

void Object::handleMoving(Object *objInstance, double xpos, double ypos) {
  double deltaX = xpos - objInstance->_lastX;
  double deltaY = ypos - objInstance->_lastY;
  objInstance->_lastX = xpos;
  objInstance->_lastY = ypos;
  deltaX /= 100;
  deltaY /= 100;
  for (auto it = objInstance->_pointCordData.begin();
       it != objInstance->_pointCordData.end(); it++) {
    Vector3 &points = *it;
    points.x += deltaX;
    points.y -= deltaY;
  }
}

void Object::handleMouseMove(GLFWwindow *window, double xpos, double ypos) {
  Object *objInstance = static_cast<Object *>(glfwGetWindowUserPointer(window));
  if (objInstance->_isDragging == false && objInstance->_isMoved == false) {
    return;
  }
  if (objInstance->_isDragging == true)
    handleRotation(objInstance, xpos, ypos);
  if (objInstance->_isMoved == true)
    handleMoving(objInstance, xpos, ypos);
}