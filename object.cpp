#include "object.hpp"

Object::Object() {
  std::cout << "The Object has been constructed" << std::endl;
}

Object::~Object() { std::cout << "The Object has been destroyed" << std::endl; }

Object::Object(std::string &object) : _name(object) {
  std::cout << "Object has been constructed" << std::endl;
}
