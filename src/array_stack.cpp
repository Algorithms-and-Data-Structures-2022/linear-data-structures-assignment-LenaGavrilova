#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость стека
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    size_=0;
    capacity_=capacity;
    data_=new int[capacity_];
    for (int i = 0; i<capacity_;i++){
      data_[i]=0;
    }
  }

  ArrayStack::~ArrayStack() {
    size_=0;
    capacity_=0;
    delete data_;
    data_= nullptr;
  }

  void ArrayStack::Push(int value) {
    if(capacity_<=size_){
      Resize(capacity_+kCapacityGrowthCoefficient);
    }
    data_[size_]=value;
    size_++;
  }

  bool ArrayStack::Pop() {
    if (size_==0){
      return false;
    }
    data_[size_-1]=0;
    size_--;
    return true;
  }

  void ArrayStack::Clear() {
    size_=0;
  }

  std::optional<int> ArrayStack::Peek() const {
    if (size_ ==0) {
      return std::nullopt;
    }
    return data_[size_-1];
  }

  bool ArrayStack::IsEmpty() const {
    if (size_==0){
      return true;
    } else {

      return false;
    }
  }

  int ArrayStack::size() const {
    return size_;
  }

  int ArrayStack::capacity() const {
    return capacity_;
  }

  bool ArrayStack::Resize(int new_capacity) {
    if(capacity_< new_capacity){
      int* newData= new int[new_capacity];
      std::copy(&data_[0],&data_[size_],newData);
      delete[] data_;
      capacity_=new_capacity;
      data_ = newData;
      return true;
    } else {
      return false;
    }
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  ArrayStack::ArrayStack(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> ArrayStack::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment