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
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    glfwGetCursorPos(objInstance->_window, &objInstance->_lastX,
                     &objInstance->_lastY);
    objInstance->_isDragging = true;
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    objInstance->_isDragging = false;
  }
}

void Object::handleMouseMove(GLFWwindow *window, double xpos, double ypos) {
  Object *objInstance = static_cast<Object *>(glfwGetWindowUserPointer(window));
  if (!objInstance->_isDragging) {
    return;
  }
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