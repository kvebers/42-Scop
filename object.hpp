#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "scop.hpp"

struct Material {
  float Ns;
  float Ka[3];
  float Kd[3];
  float Ks[3];
  float Ni;
  float d;
  int illum;
};

class Object {
private:
  std::string _obj;
  std::string _mtl;
  std::vector<std::string> _objData;
  std::vector<std::string> _mtlData;
  std::vector<std::string> _pointData;
  std::vector<std::string> _triangleData;
  Material _material;
  GLFWwindow *_window;

  void ReadObj();
  void ProcessData();
  void SplitObject();
  void MakeMaterial();

public:
  Object();
  Object(std::string &object, std::string &mtl);
  ~Object();
  void RenderObject();
};

#endif