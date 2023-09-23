#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "scop.hpp"

class Object {
private:
  std::string _obj;
  std::string _mtl;
  std::vector<std::string> _objData;
  std::vector<std::string> _mtlData;
  std::vector<std::string> _pointData;
  std::vector<std::string> _triangleData;
  GLFWwindow *_window;
  void ReadObj();
  void ProcessData();
  void SplitObject();

public:
  Object();
  Object(std::string &object, std::string &mtl);
  ~Object();
  void RenderObject();
};

#endif