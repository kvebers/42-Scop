#include "object.hpp"

int findSmallestValue(int val1, int val2, int val3, int val4) {
  int smol = val1;
  if (val2 < smol)
    smol = val2;
  if (val3 < smol)
    smol = val3;
  if (val4 != -1 && val4 < smol)
    smol = val4;
  return smol;
}

void Object::unwrap() {
  // Indexing Triangle Texturing Order
  for (auto it = _drawData.begin(); it != _drawData.end(); it++) {
    it->smallestLocation = findSmallestValue(
        it->locations[0], it->locations[1], it->locations[2], it->locations[3]);
  }
  // SORTING by Triangle Order
  std::sort(_drawData.begin(), _drawData.end(),
            [](const Triangle &first, const Triangle &sec) {
              return first.smallestLocation < sec.smallestLocation;
            });
}