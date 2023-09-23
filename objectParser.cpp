#include "object.hpp"
#include <vector>

void Object::ReadObj() {
  std::ifstream obj(_obj);
  std::string line;
  while (std::getline(obj, line)) {
    _objData.push_back(line);
  }
  obj.close();
  std::ifstream mtl(_mtl);
  while (std::getline(mtl, line)) {
    _mtlData.push_back(line);
  }
  mtl.close();
}

void Object::SplitObject() {
  for (auto it = _objData.begin(); it != _objData.end(); it++) {
    if ((*it)[0] == 'v')
      _pointData.push_back(*it);
    if ((*it)[0] == 'f')
      _triangleData.push_back(*it);
  }
}

void Object::ProcessData() {
  for (auto it = _objData.begin(); it != _objData.end(); it++) {
    if ((*it).length() == 0 || ((*it)[0] != 'v' && (*it)[0] != 'f'))
      it->erase();
    else
      break;
  }

  for (auto it = _mtlData.begin(); it != _mtlData.end(); it++) {
    if ((*it).length() == 0 || (*it).find("newmtl") == std::string::npos)
      it->erase();
    else
      break;
  }
  SplitObject();
}