#include "object.hpp"
#include <cmath>
#include <set>
#include <vector>

// Calculating the furthest distance from the X axis
float calculateDelta(std::vector<std::map<int, Vector2>> &translated) {
  if (translated.empty()) {
    return 1.0f;
  }
  float maxX = translated[0].begin()->second.x;
  float minX = translated[0].begin()->second.x;
  float maxY = translated[0].begin()->second.y;
  float minY = translated[0].begin()->second.y;
  for (auto itr = translated.begin(); itr != translated.end(); itr++) {
    for (auto it = itr->begin(); it != itr->end(); it++) {
      if (maxX < it->second.x)
        maxX = it->second.x;
      if (minX > it->second.x)
        minX = it->second.x;
      if (maxY < it->second.y)
        maxY = it->second.x;
      if (minY > it->second.y)
        minY = it->second.y;
    }
  }
  float delta = maxX - minX;
  if (delta < maxY - minY)
    delta =    - minY;
  return delta;
}
// Spliting QUADS and Triangles into Edges
std::vector<Edge> Object::CreateEdges() {
  std::vector<Edge> edges;
  for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
    int points = 0;
    if (it->mode == 1)
      points = 3;
    else
      points = 4;
    for (int i = 0; i < points; i++) {
      Edge edge;
      edge.start = *(it->points[i]);
      edge.end = *(it->points[(i + 1) % points]);
      edge.startPoint = it->locations[i];
      edge.endPoint = it->locations[(i + 1) % points];
      float dx = edge.end.x - edge.start.x;
      float dy = edge.end.y - edge.start.y;
      float dz = edge.end.z - edge.start.z;
      if (dx < 0)
        edge.lenX = -sqrt(dx * dx + dz * dz);
      else
        edge.lenX = sqrt(dx * dx + dz * dz);
      if (dy < 0)
        edge.lenY = sqrt(dy * dy);
      else
        edge.lenY = -sqrt(dy * dy);
      if (std::find(edges.begin(), edges.end(), edge) == edges.end()) {
        edges.push_back(edge);
      }
    }
  }
  return edges;
}

void Object::unwrap() {

  std::vector<Edge> sortedEdges = CreateEdges();
  std::vector<std::map<int, Vector2>> objects;
  // Spliting the objects
  while (!sortedEdges.empty()) {
    std::map<int, Vector2> translated;
    Vector2 vec;
    vec.x = 0;
    vec.y = 0;
    translated[sortedEdges.front().startPoint] = vec;
    vec.x += sortedEdges.front().lenX;
    vec.y += sortedEdges.front().lenY;
    translated[sortedEdges.front().endPoint] = vec;
    sortedEdges.erase(sortedEdges.begin());
    int len = sortedEdges.size();
    int tempLen = len + 1;
    // Itterating thill there are no more unconnected points
    while (tempLen != len) {
      tempLen = len;
      for (auto it = sortedEdges.begin(); it != sortedEdges.end();) {
        auto found = translated.find(it->startPoint);
        auto found1 = translated.find(it->endPoint);
        Vector2 val;
        if (found != translated.end()) {
          val = found->second;
          val.x += it->lenX;
          val.y += it->lenY;
          translated[it->endPoint] = val;
          it = sortedEdges.erase(it);
          continue;
        }
        if (found1 != translated.end()) {
          val = found1->second;
          val.x -= it->lenX;
          val.y -= it->lenY;
          translated[it->startPoint] = val;
          it = sortedEdges.erase(it);
          continue;
        }
        it++;
      }
      len = sortedEdges.size();
    }
    objects.push_back(translated);
  }

  float delta = calculateDelta(objects);
  // Iterating Trought Diffrent Objects
  for (auto translated = objects.begin(); translated != objects.end();
       translated++) {
    // NORMALIZING THE DATA
    for (auto it = translated->begin(); it != translated->end(); it++) {
      it->second.x = (it->second.x + delta) / (delta * 2);
      it->second.y = (it->second.y + delta) / (delta * 2);
    }
    // Attaching the Points to the Material
    for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
      int points = 0;
      if (it->mode == 1)
        points = 3;
      else
        points = 4;
      for (int i = 0; i < points; i++) {
        auto find = translated->find(it->locations[i]);
        if (find != translated->end())
          it->UV_Proper[i] = find->second;
      }
    }
  }
}