#include "object.hpp"
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

void Object::ReadObj() {
  std::ifstream obj(_obj);
  std::string line;
  while (std::getline(obj, line)) {
    _objData.push_back(line);
  }
  obj.close();
  std::ifstream mtl(_obj);
  while (std::getline(mtl, line)) {
    _mtlData.push_back(line);
  }
  mtl.close();
}

void Object::ProcessData() {
  for (std::vector<std::string>::iterator it = _objData.begin();
       it != _objData.end(); it++) {
    if ((*it)[0] != 'v' || (*it)[0] != 'f') {
      it->erase();
    } else
      break;
  }
}

void Object::RenderObject() {
  ReadObj();
  ProcessData();
  
}