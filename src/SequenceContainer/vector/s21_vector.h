#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H

#include <cmath>
#include <iostream>

namespace s21 {
template<typename V, class Allocator = std::allocator<V>>
class vector {
 public:

  //  ------------------------------Member type------------------------------
  using value_type = V;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = V *;
  using const_iterator = const V *;
  using size_type = size_t;
  using allocator_type = Allocator;
  using pointer = value_type *;

  //  ------------------------------Functions------------------------------

  //  Дефолтный конструктор
  vector() : arr_(nullptr), size_(0), capacity_(0) {}

  //  Параметризованный конструктор
  vector(size_type n) : arr_(nullptr), size_(n), capacity_(n) {
    arr_ = new value_type[size_];
    for (size_t i = 0; i < size_; i++) {
      arr_[i] = value_type();
    }
  }

  //  Конструктор списка инициализаторов
  vector(std::initializer_list<value_type> const &items) : vector(items.size()) {
    std::copy(items.begin(), items.end(), arr_);
  }

  //  Конструктор копирования
  vector(const vector &v) : vector(v.capacity_) {
    for (size_type i = 0; i < v.size_; ++i) {
      arr_[i] = v.arr_[i];
    }
    size_ = v.size_;
    capacity_ = v.capacity_;
  }

  //  Конструктор перемещения
  vector(vector &&v) noexcept: arr_(v.arr_), size_(v.size_), capacity_(v.capacity_) {
    v.arr_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

  //  Деструктор
  ~vector() {
    delete[] arr_;
    arr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  //  Перегрузка оператора для перемещения объекта
  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] arr_;
      arr_ = v.arr_;
      capacity_ = v.capacity_;
      size_ = v.size_;
      v.arr_ = nullptr;
      v.capacity_ = 0;
      v.size_ = 0;
    }
    return *this;
  }

  //  ------------------------------Element access------------------------------

  //  Возвращает ссылку на элемент в указанном месте pos с проверкой границ
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Out of range");
    }
    return arr_[pos];
  }
  //  Возвращает ссылку на элемент в указанном месте
  reference operator[](size_type pos) { return arr_[pos]; }

  //  Возвращает ссылку на первый элемент в контейнере
  reference front() { return arr_[0]; }

  //  Возвращает ссылку на последний элемент в контейнере
  reference back() { return arr_[size_ - 1]; }

  //  Возвращает указатель на базовый массив
  pointer data() noexcept { return arr_; }

  //  ------------------------------Iterators------------------------------

  iterator begin() noexcept { return arr_; }
  const_iterator begin() const noexcept { return arr_; }
  iterator end() noexcept { return arr_ + size_; }
  const_iterator end() const noexcept { return arr_ + size_; }

  //  ------------------------------Capacity------------------------------

  //  Проверяет, нет ли в контейнере элементов
  bool empty() const noexcept { return size_ == 0; }

  //  Возвращает количество элементов в контейнере
  size_type size() const noexcept { return size_; }

  //  Возвращает максимальное количество элементов, которые может содержать контейнер
  size_type max_size() const noexcept { return allocator_.max_size(); }

  //  Увеличиваем емкость вектора до значения, которое больше или равно size
  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error("Out of memory");
    }
    if (size > capacity_) {
      V *buff = allocator_.allocate(size);
      for (size_type i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
      delete[] arr_;
      arr_ = buff;
      capacity_ = size;
    }
  }

  //  Возвращает количество элементов, для которых в данный момент выделено место в контейнере
  size_type capacity() const noexcept { return capacity_; }

  //  Запрашивает удаление неиспользуемой емкости
  void shrink_to_fit() { if (size_ != capacity_) reserve(size_); }

  //  ------------------------------Modifiers------------------------------

  //  Удаляет все элементы из контейнера
  void clear() noexcept {
    for (size_type i = 0; i < size_; ++i) {
      allocator_.destroy(arr_ + i);
    }
    size_ = 0;
  }

  //  Вставляет элементы в указанное место в контейнере
  iterator insert(iterator pos, const_reference value) {
    auto dif = pos - begin();
    size_++;
    for (int i = size_ - 1; i > pos - begin(); i--) {
      arr_[i] = arr_[i - 1];
    }
    arr_[pos - begin()] = value;
    if (size_ - 1 == capacity_) {
      reserve(size_ == 0 ? 1 : capacity_ * 2);
    }
    return begin() + dif;
  }

  //  Удаляет указанные элементы из контейнера.
  void erase(iterator pos) {
    for (size_type i = pos - begin(); i < size_ - 1; i++) {
      arr_[i] = arr_[i + 1];
    }
    size_--;
  }

  //  Добавляет заданное значение элемента в конец контейнера
  void push_back(const_reference value) {
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }
    arr_[size_] = value;
    size_ += 1;
  }

  //  Удаляет последний элемент контейнера
  void pop_back() { allocator_.destroy(arr_ + --size_); }

  //  Меняет содержимое и вместимость контейнера с другими
  void swap(vector<value_type> &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(allocator_, other.allocator_);
  }

 private:
  pointer arr_;
  size_type size_;
  size_type capacity_;
  allocator_type allocator_;
};
}

#endif //CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H