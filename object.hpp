#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "scop.hpp"
#include <vector>

struct Material {
  float Ns;
  float Ka[3];
  float Kd[3];
  float Ks[3];
  float Ni;
  float d;
  int illum;
};

struct Vector2 {
  float x, y;
};

struct Vector3 {
  float x, y, z;
};

struct Triangle {
  int mode;
  Vector3 points[4];
};

class Object {
private:
  std::string _obj;
  std::string _mtl;
  std::vector<std::string> _objData;
  std::vector<std::string> _mtlData;
  std::vector<std::string> _pointData;
  std::vector<std::string> _triangleData;
  std::vector<Vector3> _pointCordData;
  std::vector<Triangle> _drawData;
  std::vector<Material> _material;
  Vector2 _lightData;
  GLFWwindow *_window;
  float _focalLen;

  void ReadObj();
  void ProcessData();
  void SplitObject();
  void MakeMaterial();
  void RemoveBlend();
  void MakeLight();
  void SetupTriangles();
  void SetupRender();

  void InitGLFW();
  void RunLoop();
  void DrawTriangle(Triangle &triangle);
  void DrawRectangle(Triangle &rectangle);
  void Draw();
  void RandomColor();

public:
  Object();
  Object(std::string &object, std::string &mtl);
  ~Object();
  void RenderObject();
};

#endif