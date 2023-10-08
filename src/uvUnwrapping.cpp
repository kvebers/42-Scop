#include "object.hpp"
#include <set>
#include <vector>

float calculateDelta(std::map<int, Vector2> &translated) {
  float maxX = translated.begin()->second.x;
  float minX = translated.begin()->second.x;
  float maxY = translated.begin()->second.y;
  float minY = translated.begin()->second.y;
  for (auto it = translated.begin(); it != translated.end(); it++) {
    if (maxX < it->second.x)
      maxX = it->second.x;
    if (minX > it->second.x)
      minX = it->second.x;
    if (maxY < it->second.y)
      maxX = it->second.x;
    if (minY > it->second.y)
      minY = it->second.y;
  }
  float delta = maxX - minX;
  if (delta < maxY - minY)
    delta = maxY - minY;
  return delta;
}

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
  while (!sortedEdges.empty()) {
    std::map<int, Vector2> translated;
    Vector2 vec;
    vec.x = 0;
    vec.y = 0;
    translated[sortedEdges.front().startPoint] = vec;
    vec.x = 0;
    vec.y = 0;
    translated[sortedEdges.front().endPoint] = vec;
    sortedEdges.erase(sortedEdges.begin());
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
          val.x = 0;
          val.y = 0;
          translated[it->endPoint] = val;
          it = sortedEdges.erase(it);
          continue;
        }
        if (found1 != translated.end()) {
          val = found1->second;
          val.x = 0;
          val.y = 0;
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
  for (auto translated = objects.begin(); translated != objects.end();
       translated++) {
    float delta = calculateDelta(*translated);
    for (auto it = translated->begin(); it != translated->end(); it++) {
      it->second.x = (it->second.x + delta) / (delta * 2);
      it->second.y = (it->second.y + delta) / (delta * 2);
    }
    for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
      int points = 0;
      if (it->mode == 1)
        points = 3;
      else
        points = 4;
      for (int i = 0; i < points; i++) {
        auto find = translated->find(it->locations[i]);
        it->UV_Proper[i] = find->second;
      }
    }
  }
}