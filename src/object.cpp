#include "object.hpp"

Object::Object() {
  std::cout << "The Object has been constructed" << std::endl;
}

Object::~Object() { std::cout << "The Object has been destroyed" << std::endl; }

Object::Object(std::string &object, std::string &mtl, std::string &texture)
    : _obj(object), _mtl(mtl), _texture(texture) {
  std::cout << "Object has been constructed" << std::endl;
}
