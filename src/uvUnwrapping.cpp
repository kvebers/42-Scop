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
      edge.lenX = edge.end.x - edge.start.x +
                  sin(edge.angle) * (edge.end.z - edge.start.z);
      edge.lenY = edge.end.y -
                  edge.start.y * cos(edge.angle) * (edge.end.z - edge.start.z);
      ;
      // +
      //             cos(edge.angle) * (edge.end.z - edge.start.z);
      if (std::find(edges.begin(), edges.end(), edge) == edges.end()) {
        edges.push_back(edge);
      }
    }
  }

  std::vector<Edge> sortedEdges;
  std::set<int> usedVertices;
  std::vector<Edge> remainingEdges = edges;

  while (!remainingEdges.empty()) {
    auto it = std::find_if(remainingEdges.begin(), remainingEdges.end(),
                           [&usedVertices](const Edge &e) {
                             return usedVertices.count(e.startPoint) ||
                                    usedVertices.count(e.endPoint);
                           });
    if (it == remainingEdges.end()) {
      it = std::min_element(remainingEdges.begin(), remainingEdges.end(),
                            [](const Edge &a, const Edge &b) {
                              return std::min(a.startPoint, a.endPoint) <
                                     std::min(b.startPoint, b.endPoint);
                            });
    }
    sortedEdges.push_back(*it);
    usedVertices.insert(it->startPoint);
    usedVertices.insert(it->endPoint);
    remainingEdges.erase(it);
  }
  std::map<int, Vector2> translated;
  for (auto it = sortedEdges.begin(); it != sortedEdges.end(); it++) {

    auto found = translated.find(it->startPoint);
    Vector2 val;
    if (found != translated.end()) {
      val = found->second;
      val.x += it->lenX;
      val.y += it->lenY;
      translated[it->endPoint] = val;
      continue;
    }
    auto found1 = translated.find(it->startPoint);
    if (found1 != translated.end()) {
      val = found1->second;
      val.x += it->lenX;
      val.y += it->lenY;
      translated[it->startPoint] = val;
      continue;
    }
    val.x = 0;
    val.y = 0;
    translated[it->startPoint] = val;
    val.x += it->lenX;
    val.y += it->lenY;
    translated[it->endPoint] = val;
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