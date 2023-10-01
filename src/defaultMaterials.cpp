#include "object.hpp"

Material Object::SetupDefaultMaterial() {
  Material mat;
  mat.Ka.x = 0.0f;
  mat.Ka.z = 0.0f;
  mat.Ka.y = 0.0f;
  mat.Ks.x = 0.0f;
  mat.Ks.z = 0.0f;
  mat.Ks.y = 0.0f;
  mat.Kd.x = 0.0f;
  mat.Kd.z = 0.0f;
  mat.Kd.y = 0.0f;
  mat.d = 1.0f;
  mat.illum = 2.0f;
  mat.Ns = 100;
  mat.Ni = 0;
  return mat;
}

void Object::addMoreDefaults() {
  Material mat;
  mat.Ka.x = 1.0f;
  mat.Ka.z = 0.0f;
  mat.Ka.y = 0.0f;
  mat.Ks.x = 0.5f;
  mat.Ks.z = 0.5f;
  mat.Ks.y = 0.5f;
  mat.Kd.x = 0.5f;
  mat.Kd.z = 0.5f;
  mat.Kd.y = 0.5f;
  mat.d = 1.0f;
  mat.illum = 2.0f;
  mat.Ns = 100;
  mat.Ni = 0;
  _material.push_back(mat);
  mat.Ka.x = 0.0f;
  mat.Ka.y = 1.0f;
  mat.Ns = 10;
  _material.push_back(mat);
  mat.Ka.y = 0.0f;
  mat.Ka.z = 1.0f;
  mat.Ns = 50;
  _material.push_back(mat);
  mat.Ka.z = 0.0f;
  mat.d = 0.5f;
  mat.Ns = 50;
  _material.push_back(mat);
  mat.Ka.x = 0.6f;
  mat.Ka.z = 0.3f;
  mat.Ka.y = 0.5f;
  mat.Ks.x = 0.5f;
  mat.Ks.z = 0.5f;
  mat.Ks.y = 0.5f;
  mat.Kd.x = 1.0f;
  mat.Kd.z = 1.0f;
  mat.Kd.y = 1.0f;
  mat.d = 1.0f;
  mat.illum = 2.0f;
  mat.Ns = 100;
  mat.Ni = 90;
  _material.push_back(mat);
}