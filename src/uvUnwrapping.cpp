#include "object.hpp"
#include <set>
#include <vector>

void Object::unwrap() {
  // Indexing Triangle Texturing Order

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
      edge.angle = atan2(edge.end.x - edge.start.x, edge.end.z - edge.start.z);
      float dx = edge.end.x - edge.start.x;
      float dy = edge.end.y - edge.start.y;
      float dz = edge.end.z - edge.start.z;
      if (dx < 0)
        edge.lenX = -sqrt(dx * dx + dz * dz);
      else
        edge.lenX = sqrt(dx * dx + dz * dz);
      if (dy < 0)
        edge.lenY = -sqrt(dy * dy);
      else
        edge.lenY = sqrt(dy * dy);
      if (std::find(edges.begin(), edges.end(), edge) == edges.end()) {
        edges.push_back(edge);
      }
    }
  }

  std::vector<Edge> sortedEdges = edges; // Copy the edges into sortedEdges

  // std::sort(sortedEdges.begin(), sortedEdges.end(),
  //           [](const Edge &a, const Edge &b) {
  //             return std::min(a.startPoint, a.endPoint) <
  //                    std::min(b.startPoint, b.endPoint);
  //           });

  std::map<int, Vector2> translated;
  if (!sortedEdges.empty()) {
    Vector2 vec;
    vec.x = 0;
    vec.y = 0;
    translated[sortedEdges.front().startPoint] = vec;
    vec.x += sortedEdges.front().lenX;
    vec.y += sortedEdges.front().lenX;
    translated[sortedEdges.front().endPoint] = vec;
    sortedEdges.erase(sortedEdges.begin());
  }
  int len = sortedEdges.size();
  int tempLen = len + 1;
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
        val.x += it->lenX;
        val.y += it->lenY;
        translated[it->startPoint] = val;
        it = sortedEdges.erase(it);
        std::cout << " I was here" << std::endl;
        continue;
      }
      it++;
    }
    len = sortedEdges.size();
  }

  for (auto it = translated.begin(); it != translated.end(); it++) {
    it->second.x = (it->second.x + 1) / 2;
    it->second.y = (it->second.y + 1) / 2;
  }
  for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
    int points = 0;
    if (it->mode == 1)
      points = 3;
    else
      points = 4;
    for (int i = 0; i < points; i++) {
      auto find = translated.find(it->locations[i]);
      it->UV_Proper[i] = find->second;
    }
  }
}