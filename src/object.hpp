#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../scop.hpp"

struct Vector2 {
  float x, y;
};

struct Vector3 {
  float x, y, z;
};

struct Material {
  float Ns;
  Vector3 Ka;
  Vector3 Kd;
  Vector3 Ks;
  float Ni;
  float d;
  int illum;
};

struct Triangle {
  int mode;
  float medium;
  Vector3 *points[4];
  Vector2 initialPoints[4];
  Vector2 UV[4];
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
  Vector3 _lightData;
  Vector3 _lightColor;
  Vector3 _viewPos;
  // window managment stuff
  int _width;
  int _height;
  float _proportion;
  GLFWwindow *_window;
  // Camera Managment and Position
  float _focalLen;
  double _lastX;
  double _lastY;
  bool _isMoved;
  bool _isDragging;
  // Render Object
  int _vertecies;
  int _edges;
  int _faces;
  // Color and Material Mangment
  int _currentMaterial;
  float _colorMode;
  int _renderTexture;
  // Texture
  GLuint _texture2D;
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

  Material SetupDefaultMaterial();
  void addMoreDefaults();
  // Main loop
  void RunLoop();
  // Draw Figures
  void DrawTriangle(Triangle &triangle);
  void DrawRectangle(Triangle &rectangle);
  void Draw();
  void CalculateMedium();

  // Just cool function
  void Shader(Vector3 *point, int modifier);
  static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods);
  static void scrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset);
  static void handleMouseMove(GLFWwindow *window, double xpos, double ypos);
  static void handleRotation(Object *objInstance, double xpos, double ypos);
  static void handleMoving(Object *objInstance, double xpos, double ypos);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  static void centerObject(GLFWwindow *window);
  static void colorMode(Object *objInstance);
  static void changeColor(float *color, int colorMode);
  void SetupTexture(std::string path);
  void setupPoints();
  void DrawPoints();
  void DrawEdges();
  void DrawTriangleLine(Triangle &triangle);
  void DrawRectangleLine(Triangle &rectangle);
  void SelectTexture(Triangle &triangle, int i, int mode);

public:
  Object();
  Object(std::string &object, std::string &mtl);
  ~Object();
  void RenderObject();
};

#endif