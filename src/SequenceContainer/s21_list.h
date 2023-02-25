#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H

#include <cmath>
#include <iostream>

template <typename T>
class List {
 public:
  using value_type = T;
  using reference = T;
  using const_reference = T;
  using iterator = T;
  using const_iterator = T;
  using size_type = T;

 private:
  value_type value;
  List* next;
  List* prev;
  };

#endif //CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
