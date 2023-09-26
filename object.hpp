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
  Vector3 *points[4];
};

class Object {
private:
  // parsing data
  std::string _obj;
  std::string _mtl;
  std::vector<std::string> _objData;
  std::vector<std::string> _mtlData;
  std::vector<std::string> _pointData;
  std::vector<std::string> _triangleData;
  // Point cordinates
  std::vector<Vector3> _pointCordData;
  // Triangles and Quads to draw stuff
  std::vector<Triangle> _drawData;
  // Vector of materials
  std::vector<Material> _material;
  Vector2 _lightData;

  // window managment stuff
  int _width;
  int _height;
  float _proportion;
  GLFWwindow *_window;
  float _focalLen;
  double _lastX;
  double _lastY;
  bool _isDragging;
  // Parsing
  void ReadObj();
  void ProcessData();
  void SplitObject();
  void MakeMaterial();
  void RemoveBlend();
  void MakeLight();
  void SetupTriangles();
  void SetupRender();
  void InitGLFW();
  // Main loop
  void RunLoop();
  // Draw Figures
  void DrawTriangle(Triangle &triangle);
  void DrawRectangle(Triangle &rectangle);
  void Draw();
  // Just cool function
  void RandomColor();
  static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods);
  static void scrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset);
  static void handleMouseMove(GLFWwindow *window, double xpos, double ypos);

public:
  Object();
  Object(std::string &object, std::string &mtl);
  ~Object();
  void RenderObject();
};

#endif