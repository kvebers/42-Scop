#include "object.hpp"

void Object::DrawRectangle(Triangle &rectangle) {
  glBegin(GL_QUADS);
  Shader(rectangle.points[0], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[0]->x + 1) / 2,
                 (rectangle.points[0]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[0].x, rectangle.initialPoints[0].y);
  glVertex3f(rectangle.points[0]->x / _focalLen / _proportion,
             rectangle.points[0]->y / _focalLen,
             rectangle.points[0]->z / _focalLen);
  Shader(rectangle.points[1], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[1]->x + 1) / 2,
                 (rectangle.points[1]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[1].x, rectangle.initialPoints[1].y);
  glVertex3f(rectangle.points[1]->x / _focalLen / _proportion,
             rectangle.points[1]->y / _focalLen,
             rectangle.points[1]->z / _focalLen);
  Shader(rectangle.points[2], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[2]->x + 1) / 2,
                 (rectangle.points[2]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[2].x, rectangle.initialPoints[2].y);
  glVertex3f(rectangle.points[2]->x / _focalLen / _proportion,
             rectangle.points[2]->y / _focalLen,
             rectangle.points[2]->z / _focalLen);
  Shader(rectangle.points[3], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[3]->x + 1) / 2,
                 (rectangle.points[3]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[3].x, rectangle.initialPoints[3].y);
  glVertex3f(rectangle.points[3]->x / _focalLen / _proportion,
             rectangle.points[3]->y / _focalLen,
             rectangle.points[3]->z / _focalLen);
  glEnd();
}

void Object::DrawTriangle(Triangle &triangle) {
  glBegin(GL_TRIANGLES);
  Shader(triangle.points[0], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[0]->x + 1) / 2,
                 (triangle.points[0]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[0].x, triangle.initialPoints[0].y);
  glVertex3f(triangle.points[0]->x / _focalLen / _proportion,
             triangle.points[0]->y / _focalLen,
             triangle.points[0]->z / _focalLen);
  Shader(triangle.points[1], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[1]->x + 1) / 2,
                 (triangle.points[1]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[1].x, triangle.initialPoints[1].y);
  glVertex3f(triangle.points[1]->x / _focalLen / _proportion,
             triangle.points[1]->y / _focalLen,
             triangle.points[1]->z / _focalLen);
  Shader(triangle.points[2], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.5f, 0.5f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[2]->x + 1) / 2,
                 (triangle.points[2]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[2].x, triangle.initialPoints[2].y);
  glVertex3f(triangle.points[2]->x / _focalLen / _proportion,
             triangle.points[2]->y / _focalLen,
             triangle.points[2]->z / _focalLen);
  glEnd();
}

void Object::DrawRectangleLine(Triangle &rectangle) {
  glLineWidth(4.0f);
  glBegin(GL_LINES);
  Shader(rectangle.points[0], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[0]->x + 1) / 2,
                 (rectangle.points[0]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[0].x, rectangle.initialPoints[0].y);
  glVertex3f(rectangle.points[0]->x / _focalLen / _proportion,
             rectangle.points[0]->y / _focalLen,
             rectangle.points[0]->z / _focalLen);
  Shader(rectangle.points[1], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[1]->x + 1) / 2,
                 (rectangle.points[1]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[1].x, rectangle.initialPoints[1].y);
  glVertex3f(rectangle.points[1]->x / _focalLen / _proportion,
             rectangle.points[1]->y / _focalLen,
             rectangle.points[1]->z / _focalLen);
  Shader(rectangle.points[1], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[1]->x + 1) / 2,
                 (rectangle.points[1]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[1].x, rectangle.initialPoints[1].y);
  glVertex3f(rectangle.points[1]->x / _focalLen / _proportion,
             rectangle.points[1]->y / _focalLen,
             rectangle.points[1]->z / _focalLen);

  Shader(rectangle.points[2], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[2]->x + 1) / 2,
                 (rectangle.points[2]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[2].x, rectangle.initialPoints[2].y);
  glVertex3f(rectangle.points[2]->x / _focalLen / _proportion,
             rectangle.points[2]->y / _focalLen,
             rectangle.points[2]->z / _focalLen);
  Shader(rectangle.points[2], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(1.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[2]->x + 1) / 2,
                 (rectangle.points[2]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[2].x, rectangle.initialPoints[2].y);
  glVertex3f(rectangle.points[2]->x / _focalLen / _proportion,
             rectangle.points[2]->y / _focalLen,
             rectangle.points[2]->z / _focalLen);

  Shader(rectangle.points[3], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[3]->x + 1) / 2,
                 (rectangle.points[3]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[3].x, rectangle.initialPoints[3].y);
  glVertex3f(rectangle.points[3]->x / _focalLen / _proportion,
             rectangle.points[3]->y / _focalLen,
             rectangle.points[3]->z / _focalLen);
  Shader(rectangle.points[3], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[3]->x + 1) / 2,
                 (rectangle.points[3]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[3].x, rectangle.initialPoints[3].y);
  glVertex3f(rectangle.points[3]->x / _focalLen / _proportion,
             rectangle.points[3]->y / _focalLen,
             rectangle.points[3]->z / _focalLen);

  Shader(rectangle.points[0], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((rectangle.points[0]->x + 1) / 2,
                 (rectangle.points[0]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(rectangle.initialPoints[0].x, rectangle.initialPoints[0].y);
  glVertex3f(rectangle.points[0]->x / _focalLen / _proportion,
             rectangle.points[0]->y / _focalLen,
             rectangle.points[0]->z / _focalLen);

  glEnd();
}

void Object::DrawTriangleLine(Triangle &triangle) {
  glLineWidth(4.0f);
  glBegin(GL_LINES);
  Shader(triangle.points[0], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[0]->x + 1) / 2,
                 (triangle.points[0]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[0].x, triangle.initialPoints[0].y);
  glVertex3f(triangle.points[0]->x / _focalLen / _proportion,
             triangle.points[0]->y / _focalLen,
             triangle.points[0]->z / _focalLen);

  Shader(triangle.points[1], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[1]->x + 1) / 2,
                 (triangle.points[1]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[1].x, triangle.initialPoints[1].y);
  glVertex3f(triangle.points[1]->x / _focalLen / _proportion,
             triangle.points[1]->y / _focalLen,
             triangle.points[1]->z / _focalLen);
  Shader(triangle.points[1], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 1.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[1]->x + 1) / 2,
                 (triangle.points[1]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[1].x, triangle.initialPoints[1].y);
  glVertex3f(triangle.points[1]->x / _focalLen / _proportion,
             triangle.points[1]->y / _focalLen,
             triangle.points[1]->z / _focalLen);

  Shader(triangle.points[2], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.5f, 0.5f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[2]->x + 1) / 2,
                 (triangle.points[2]->y + 1) / 2);
  else if (_renderTexture == 3)
    glVertex3f(triangle.points[2]->x / _focalLen / _proportion,
               triangle.points[2]->y / _focalLen,
               triangle.points[2]->z / _focalLen);
  Shader(triangle.points[2], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.5f, 0.5f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[2]->x + 1) / 2,
                 (triangle.points[2]->y + 1) / 2);
  else if (_renderTexture == 3)
    glVertex3f(triangle.points[2]->x / _focalLen / _proportion,
               triangle.points[2]->y / _focalLen,
               triangle.points[2]->z / _focalLen);

  Shader(triangle.points[0], _currentMaterial);
  if (_renderTexture == 1)
    glTexCoord2f(0.0f, 0.0f);
  else if (_renderTexture == 2)
    glTexCoord2f((triangle.points[0]->x + 1) / 2,
                 (triangle.points[0]->y + 1) / 2);
  else if (_renderTexture == 3)
    glTexCoord2f(triangle.initialPoints[0].x, triangle.initialPoints[0].y);
  glVertex3f(triangle.points[0]->x / _focalLen / _proportion,
             triangle.points[0]->y / _focalLen,
             triangle.points[0]->z / _focalLen);

  glEnd();
}