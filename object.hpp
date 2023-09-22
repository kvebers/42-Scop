#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "scop.hpp"
#include <string>
#include <vector>

class Object {
private:
  std::string _obj;
  std::string _mtl;
  std::vector<std::string> _objData;
  std::vector<std::string> _mtlData;

public:
  Object();
  Object(std::string &object, std::string &mtl);
  ~Object();
  void RenderObject();
  void ReadObj();
};

#endif