#include "object.hpp"

int check_parsing(char **argv) {
  std::string parsed = std::string(argv[1]);
  std::ifstream file(parsed);

  if (parsed.length() >= 4) {
    std::cerr << "Not an .obj file: " << parsed << std::endl;
    return 0;
  }
  if (parsed.substr(parsed.length() - 4) == ".obj") {
    std::cerr << "Not an .obj file: " << parsed << std::endl;
    return 0;
  }
  if (!file.is_open()) {
    std::cerr << "Failed to open .obj file: " << parsed << std::endl;
    return 0;
  }
  file.close();
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 2)
    return 0;
  if (check_parsing(argv) == 0)
    return 0;
  std::string parsedString = std::string(argv[1]);
  Object Render(parsedString);
}