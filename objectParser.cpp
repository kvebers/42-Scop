#include "object.hpp"
#include <exception>
#include <iostream>
#include <ostream>
#include <sys/errno.h>
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

void Object::MakeMaterial() {
  for (auto it = _mtlData.begin(); it != _mtlData.end(); it++) {
    std::string prefix;
    std::istringstream iss(*it);
    iss >> prefix;
    std::cout << prefix << std::endl;
    try {
      if (prefix == "Ns")
        _material.Ns = std::stof(it->substr(3));
      else if (prefix == "Ka") {
        std::string ka1, ka2, ka3;
        iss >> ka1 >> ka2 >> ka3;
        _material.Ka[0] = std::stof(ka1);
        _material.Ka[1] = std::stof(ka2);
        _material.Ka[2] = std::stof(ka3);
      } else if (prefix == "Kd") {
        std::string kd1, kd2, kd3;
        iss >> kd1 >> kd2 >> kd3;
        _material.Kd[0] = std::stof(kd1);
        _material.Kd[1] = std::stof(kd2);
        _material.Kd[2] = std::stof(kd3);
      } else if (prefix == "Ks") {
        std::string ks1, ks2, ks3;
        iss >> ks1 >> ks2 >> ks3;
        _material.Ks[0] = std::stof(ks1);
        _material.Ks[1] = std::stof(ks2);
        _material.Ks[2] = std::stof(ks3);
      } else if (prefix == "Ni") {
        std::string ni;
        iss >> ni;
        _material.Ni = std::stof(ni);
      } else if (prefix == "d") {
        std::string d;
        iss >> d;
        _material.d = std::stof(d);
      } else if (prefix == "illum") {
        std::string illum;
        iss >> illum;
        _material.illum = std::stof(illum);
      }
    } catch (const std::exception &error) {
      std::cerr << "Error: " << error.what() << std::endl;
      exit(127);
    }
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

void Object::MakeLight() {
  _lightData.x = 100;
  _lightData.y = 100;
}

void Object::TransferTo2DTriangle() {}

void Object::SetupTriangles {
  try {
    for (auto it = _pointData.begin(); it != _pointData.end(); it++) {
      std::string prefix, x, y, z;
      std::istringstream iss(*it);
      iss >> prefix >> x >> y >> z;
      std::vector<Vector3> temp;
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

void Object::ProcessData() {
  ReadObj();
  RemoveBlend();
  MakeMaterial();
  MakeLight();
  SplitObject();
  SetupTriangles();
}