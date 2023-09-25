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
    Material material;
    std::string prefix;
    std::istringstream iss(*it);
    iss >> prefix;
    std::cout << prefix << std::endl;
    try {
      if (prefix == "Ns")
        material.Ns = std::stof(it->substr(3));
      else if (prefix == "Ka") {
        std::string ka1, ka2, ka3;
        iss >> ka1 >> ka2 >> ka3;
        material.Ka[0] = std::stof(ka1);
        material.Ka[1] = std::stof(ka2);
        material.Ka[2] = std::stof(ka3);
      } else if (prefix == "Kd") {
        std::string kd1, kd2, kd3;
        iss >> kd1 >> kd2 >> kd3;
        material.Kd[0] = std::stof(kd1);
        material.Kd[1] = std::stof(kd2);
        material.Kd[2] = std::stof(kd3);
      } else if (prefix == "Ks") {
        std::string ks1, ks2, ks3;
        iss >> ks1 >> ks2 >> ks3;
        material.Ks[0] = std::stof(ks1);
        material.Ks[1] = std::stof(ks2);
        material.Ks[2] = std::stof(ks3);
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
      _material.push_back(material);
    } catch (const std::exception &error) {
      std::cerr << "Error invalid material: " << error.what() << std::endl;
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
      temp.points[0] = _pointCordData[std::stoi(first) - 1];
      temp.points[1] = _pointCordData[std::stoi(sec) - 1];
      temp.points[2] = _pointCordData[std::stoi(third) - 1];
      if (!(iss >> forth)) {
        temp.points[3].x = -1;
        temp.points[3].y = -1;
        temp.points[3].z = -1;
        temp.mode = 1;
        forth.clear();
      } else {
        temp.mode = 0;
        temp.points[3] = _pointCordData[std::stoi(forth) - 1];
      }
      _drawData.push_back(temp);
    }
  } catch (const std::exception error) {
    std::cerr << "Error Vertecie not found: " << error.what();
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
}