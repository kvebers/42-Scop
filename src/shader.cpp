#include "object.hpp"

Vector3 Magnitude(Vector3 point) {
  Vector3 magnitude;
  float magHelper =
      sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
  if (magHelper == 0) {
    magnitude.x = 0;
    magnitude.y = 0;
    magnitude.z = 0;
  } else {
    magnitude.x = point.x / magHelper;
    magnitude.y = point.y / magHelper;
    magnitude.z = point.z / magHelper;
  }
  return magnitude;
}

Vector3 Multiply(Vector3 first, Vector3 other) {
  Vector3 result;
  result.x = first.x * other.x;
  result.y = first.y * other.y;
  result.z = first.z * other.z;
  return result;
}

Vector3 Max(Vector3 first, Vector3 other) {
  Vector3 valToRet;
  valToRet.x = std::max(first.x, other.x);
  valToRet.y = std::max(first.y, other.y);
  valToRet.z = std::max(first.z, other.z);
  return valToRet;
}

Vector3 Sub(Vector3 first, Vector3 other) {
  Vector3 valToReturn;
  valToReturn.x = first.x - other.x;
  valToReturn.y = first.y - other.y;
  valToReturn.z = first.z - other.z;
  return valToReturn;
}

Vector3 Pow(Vector3 first, float other) {
  Vector3 valToReturn;
  valToReturn.x = (first.x == 0 && other <= 0) ? 0 : pow(first.x, other);
  valToReturn.y = (first.y == 0 && other <= 0) ? 0 : pow(first.y, other);
  valToReturn.z = (first.z == 0 && other <= 0) ? 0 : pow(first.z, other);
  return valToReturn;
}

Vector3 Add(Vector3 first, Vector3 other) {
  Vector3 valToReturn;
  valToReturn.x = first.x + other.x;
  valToReturn.y = first.y + other.y;
  valToReturn.z = first.z + other.z;
  return valToReturn;
}

Vector3 Normalize(Vector3 first) {
  Vector3 valToReturn;
  float division =
      sqrt(first.x * first.x + first.y * first.y + first.z * first.z);
  if (division == 0) {
    valToReturn.x = 0;
    valToReturn.y = 0;
    valToReturn.z = 0;
  } else {
    valToReturn.x = first.x / division;
    valToReturn.y = first.y / division;
    valToReturn.z = first.z / division;
  }
  return valToReturn;
}

Vector3 Dot(Vector3 first, Vector3 other) {
  Vector3 valToReturn;
  float value = first.x * other.x + first.y * other.y + first.z * other.z;
  valToReturn.x = value;
  valToReturn.y = value;
  valToReturn.z = value;
  return valToReturn;
}

Vector3 Reflect(const Vector3 &incoming, const Vector3 &normal) {
  Vector3 twos;
  twos.x = 2;
  twos.y = 2;
  twos.z = 2;
  Vector3 dotProd = Dot(incoming, normal);
  return Sub(incoming, Multiply(normal, Multiply(twos, dotProd)));
}

void Object::Shader(Vector3 *point) {
  Vector3 def;
  def.x = 0;
  def.y = 0;
  def.z = 0;
  Vector3 normal;
  normal.x = 0;
  normal.y = 1;
  normal.z = 0;
  Vector3 lightDir = Normalize(Sub(_lightData, *point));
  Vector3 viewDir = Normalize(Sub(_viewPos, *point));
  Vector3 ambient = Multiply(_material[0].Ka, _lightColor);

  // Diffuse term
  Vector3 diffIntensity = Max(Dot(normal, lightDir), def);
  Vector3 diffuse =
      Multiply(Multiply(_material[0].Kd, _lightColor), diffIntensity);
  Vector3 reflectDir = Reflect(Sub(def, lightDir), normal);
  Vector3 specIntensity =
      Pow(Max(Dot(viewDir, reflectDir), def), _material[0].Ns);
  Vector3 specular =
      Multiply(Multiply(_material[0].Ks, _lightColor), specIntensity);

  // Combine terms
  Vector3 result = Add(ambient, Add(diffuse, specular));
  std::cout << result.x << " " << result.y << " " << result.z << std::endl;
  glColor4f(result.x, result.y, result.z, _material[0].d);
}