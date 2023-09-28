#include "object.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

void Object::MakeMaterial() {
  try {
    Material material = SetupDefaultMaterial();
    for (auto it = _mtlData.begin(); it != _mtlData.end(); it++) {
      std::string prefix;
      std::istringstream iss(*it);
      iss >> prefix;
      if (prefix == "Ns")
        material.Ns = std::stof(it->substr(3));
      else if (prefix == "Ka") {
        std::string ka1, ka2, ka3;
        iss >> ka1 >> ka2 >> ka3;
        material.Ka.x = std::stof(ka1);
        material.Ka.y = std::stof(ka2);
        material.Ka.z = std::stof(ka3);
      } else if (prefix == "Kd") {
        std::string kd1, kd2, kd3;
        iss >> kd1 >> kd2 >> kd3;
        material.Kd.x = std::stof(kd1);
        material.Kd.y = std::stof(kd2);
        material.Kd.z = std::stof(kd3);
      } else if (prefix == "Ks") {
        std::string ks1, ks2, ks3;
        iss >> ks1 >> ks2 >> ks3;
        material.Ks.x = std::stof(ks1);
        material.Ks.y = std::stof(ks2);
        material.Ks.z = std::stof(ks3);
      } else if (prefix == "Ni") {
        std::string ni;
        iss >> ni;
        material.Ni = std::stof(ni);
      } else if (prefix == "d") {
        std::string d;
        iss >> d;
        material.d = std::stof(d);
      } else if (prefix == "illum") {
        std::string illum;
        iss >> illum;
        material.illum = std::stof(illum);
      }
    }
    _material.push_back(material);
  } catch (const std::exception &error) {
    std::cerr << "Error invalid material: " << error.what() << std::endl;
    exit(127);
  }
}

void Object::RemoveBlend() {
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
}

void Object::SetupTriangles() {
  try {
    for (auto it = _pointData.begin(); it != _pointData.end(); it++) {
      std::string prefix, x, y, z;
      std::istringstream iss(*it);
      iss >> prefix >> x >> y >> z;
      Vector3 temp;
      temp.x = std::stof(x);
      temp.y = std::stof(y);
      temp.z = std::stof(z);
      _pointCordData.push_back(temp);
    }
  } catch (const std::exception error) {
    std::cerr << "Error triangle data: " << error.what() << std::endl;
    exit(127);
  }
}

void Object::SetupRender() {
  try {
    for (auto it = _triangleData.begin(); it != _triangleData.end(); it++) {
      std::string prefix, first, sec, third, forth;
      std::istringstream iss(*it);
      iss >> prefix >> first >> sec >> third;
      Triangle temp;
      temp.points[0] = &_pointCordData[std::stoi(first) - 1];
      temp.points[1] = &_pointCordData[std::stoi(sec) - 1];
      temp.points[2] = &_pointCordData[std::stoi(third) - 1];
      if (!(iss >> forth)) {
        temp.points[3] = nullptr;
        temp.mode = 1;
        forth.clear();
      } else {
        temp.mode = 0;
        temp.points[3] = &_pointCordData[std::stoi(forth) - 1];
      }
      _drawData.push_back(temp);
    }
  } catch (const std::exception error) {
    std::cerr << "Error Vertecie not found: " << error.what();
    exit(127);
  }
}

void Object::SetupTexture(std::string path) {
  int width;
  int height;
  int channels;
  GLint maxTextureSize;
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (data) {
    glGenTextures(1, &_texture2D);
    glBindTexture(GL_TEXTURE_2D, _texture2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    if (width > maxTextureSize || height > maxTextureSize) {
      std::cerr << "Texture to big" << std::endl;
      exit(127);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    stbi_image_free(data);
  } else {
    std::cerr << "Error Loading the image" << std::endl;
    exit(127);
  }
}

void Object::ProcessData() {
  ReadObj();
  RemoveBlend();
  MakeMaterial();
  MakeLight();
  SplitObject();
  SetupTriangles();
  SetupRender();
  addMoreDefaults();
}