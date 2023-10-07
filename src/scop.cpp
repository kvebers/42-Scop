#include "object.hpp"

int check_parsing(char *argv, std::string comp) {
  std::string parsed = std::string(argv);
  if (parsed.length() < 4) {
    std::cerr << "Not an " << comp << " file: " << parsed << std::endl;
    return 0;
  }
  if (parsed.substr(parsed.length() - 4) != comp) {
    std::cerr << "Not an " << comp << " file: " << parsed << std::endl;
    return 0;
  }
  std::ifstream file(parsed);
  if (!file.is_open()) {
    std::cerr << "Failed to open" << comp << " file: " << parsed << std::endl;
    return 0;
  }
  file.close();
  return 1;
}

int main(int argc, char **argv) {

  if (argc != 4) {
    std::cerr << "Not enought arguments " << std::endl;
    return 0;
  }
  if (check_parsing(argv[1], ".obj") == 0)
    return 0;
  if (check_parsing(argv[2], ".mtl") == 0)
    return (0);
  if (check_parsing(argv[3], ".jpg") == 0)
    return (0);
  std::string objString = std::string(argv[1]);
  std::string mtlString = std::string(argv[2]);
  std::string texture = std::string(argv[3]);
  Object Render(objString, mtlString, texture);
  Render.RenderObject();
}