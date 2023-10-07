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
      // float theta_xy = atan2(dy, dx);
      float theta_yz = atan2(dz, dy);
      float theta_zx = atan2(dx, dz);
      edge.lenX = dx + dz * sin(theta_zx);
      edge.lenY = dy + dz * cos(theta_yz);
      // edge.lenX = edge.end.x - edge.start.x +
      //             sin(edge.angle) * (edge.end.z - edge.start.z);
      // edge.lenY = edge.end.y -
      //             edge.start.y * cos(edge.angle) * (edge.end.z -
      //             edge.start.z);
      // +
      //             cos(edge.angle) * (edge.end.z - edge.start.z);
      if (std::find(edges.begin(), edges.end(), edge) == edges.end()) {
        edges.push_back(edge);
      }
    }
  }

  std::vector<Edge> sortedEdges = edges; // Copy the edges into sortedEdges

  std::sort(sortedEdges.begin(), sortedEdges.end(),
            [](const Edge &a, const Edge &b) {
              return std::min(a.startPoint, a.endPoint) <
                     std::min(b.startPoint, b.endPoint);
            });

  std::map<int, Vector2> translated;
  int len = sortedEdges.size();
  int tempLen = len + 1;
  while (tempLen != len) {
    tempLen = len;
    for (auto it = sortedEdges.begin(); it != sortedEdges.end();) {

      auto found = translated.find(it->startPoint);
      Vector2 val;
      if (found != translated.end()) {
        val = found->second;
        val.x += it->lenX;
        val.y += it->lenY;
        translated[it->endPoint] = val;
        it = sortedEdges.erase(it);
        continue;
      }
      auto found1 = translated.find(it->startPoint);
      if (found1 != translated.end()) {
        val = found1->second;
        val.x += it->lenX;
        val.y += it->lenY;
        translated[it->startPoint] = val;
        it = sortedEdges.erase(it);
        continue;
      }
      it++;
      val.x = 0;
      val.y = 0;
      translated[it->startPoint] = val;
      val.x += it->lenX;
      val.y += it->lenY;
      translated[it->endPoint] = val;
    }
    len = sortedEdges.size();
  }

  for (auto it = translated.begin(); it != translated.end(); it++) {
    it->second.x = (it->second.x + 1) / 2;
    it->second.y = (it->second.y + 1) / 2;
    std::cout << it->first << " " << it->second.x << " " << it->second.y
              << std::endl;
  }
  int cnt = 0;
  for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
    int points = 0;
    if (it->mode == 1)
      points = 3;
    else
      points = 4;
    for (int i = 0; i < points; i++) {
      auto find = translated.find(it->locations[i]);
      it->UV_Proper[i] = find->second;
      cnt++;
    }
  }
  std::cout << cnt << std::endl;
}