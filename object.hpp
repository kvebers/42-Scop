#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "scop.hpp"

class Object {
private:
    std::string _name;
public:
  Object();
  Object(std::string &object);
  ~Object();

public:
};

#endif