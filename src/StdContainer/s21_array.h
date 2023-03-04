#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_ARRAY_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_ARRAY_H

#include "iostream"
#include "limits"
#include <array>

namespace s21 {
template<typename A, size_t N>
class array {
 public:

  using value_type = A;
  using reference = A &;
  using const_reference = const A &;
  using iterator = A *;
  using const_iterator = const A *;
  using size_type = size_t;

  //  Дефолтный конструктор
  array() : size_(N) {}

  //  Конструктор списка инициализаторов
  array(std::initializer_list<value_type> const &items) {
    int init = 0;
    for (auto i = items.begin(); i != items.end(); i++, init++) {
      arr_[init] = *i;
    }
  }

  //  Конструктор копирования
  array(const array &a) {
    size_ = a.size_;
    for (size_type i = 0; i < size_; i++) arr_[i] = a.arr_[i];
  }

  //  Конструктор перемещения
  array(array &&a) noexcept {
    std::move(a.cbegin(), a.cend(), arr_);
  }

  //  Деструктор
  ~array() {}

  //  Перегрузка оператора для перемещения объекта
  void operator=(array &&a) { std::move(a.cbegin(), a.cend(), arr_); }

  //  Возвращает ссылку на элемент в указанном месте pos с проверкой границ
  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Out of range");
    return arr_[pos];
  }

  //  Возвращает ссылку на элемент в указанном месте
  reference operator[](size_type pos) { return at(pos); }

  //  Возвращает ссылку на первый элемент в контейнере
  reference front() { return arr_[0]; }

  //  Возвращает ссылку на последний элемент в контейнере
  reference back() { return arr_[size_ - 1]; }

  //  Возвращает указатель на базовый массив
  value_type *data() noexcept { return arr_; }

  iterator begin() noexcept { return arr_; }
  const_iterator cbegin() const noexcept { return arr_; }
  iterator end() noexcept { return arr_ + size_; }
  const_iterator cend() const noexcept { return arr_ + size_; }

  //  Проверяет, нет ли в контейнере элементов
  bool empty() const noexcept { return size_ == 0; }

  //  Возвращает количество элементов в контейнере
  size_type size() const noexcept { return size_; }

  //  Возвращает максимальное количество элементов, которые может содержать контейнер
  size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2; }

  //  Меняет содержимое и вместимость контейнера с другими
  void swap(array &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
  }

  void fill(const_reference value) {
    if ((size_ = 0)) throw std::out_of_range("array is empty");
    for (size_t i = 0; i < size_; ++i) arr_[i] = value;
  }

 private:
  value_type arr_[N];
  size_type size_;
};
}

#endif //CPP2_S21_CONTAINERS_0_SRC_S21_ARRAY_H