#include "object.hpp"
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

Object::Object() {
  std::cout << "The Object has been constructed" << std::endl;
}

Object::~Object() { std::cout << "The Object has been destroyed" << std::endl; }

Object::Object(std::string &object, std::string &mtl)
    : _obj(object), _mtl(mtl) {
  std::cout << "Object has been constructed" << std::endl;
}
