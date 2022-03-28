#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    size_ = 0;
    capacity_ = capacity;
    data_= new int[capacity];
    for (int i = 0; i < capacity; i++) {
      data_[i] = 0;
    }

  }

  DynamicArray::~DynamicArray() {
    size_ = 0;
    capacity_ = 0;
    delete data_;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {
    if (capacity_<=size_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }
    data_[size_] = value;
    size_++;
  }

  bool DynamicArray::Insert(int index, int value) {
    if (index < 0 || index > size_){
      return false;
    }
    if (size_==capacity_) {
      Resize(capacity_+kCapacityGrowthCoefficient);
    }
    int* newData = new int[capacity_];
    std::copy(&data_[0],&data_[index],newData);
    newData[index] = value;
    for (int i =index+1; i<capacity_;i++){
      newData[i]=data_[i-1];

    }
    size_++;
    data_=newData;
    return true;

  }

  bool DynamicArray::Set(int index, int new_value) {
    if (index >= size_ || index<0){
      return false;
    }
    data_[index] = new_value;
    return true;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    if(index < 0 || index>=size_){
      return std::nullopt;
    }
    int* newData= new int[capacity_];
    std::copy(&data_[0],&data_[index],newData);
    int num = data_[index];
    for ( int i=index; i<size_;i++){
      newData[i]=data_[i+1];
    }
    size_--;
    data_=newData;
    return num;


  }

  void DynamicArray::Clear() {
    size_=0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (index<0 || index>=size_){
      return std::nullopt;
    }
    return data_[index];
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for(int i = 0; i<size_;i++) {
      if (data_[i] == value) {
        return i;
      }
    }
      return std::nullopt;
    }



  bool DynamicArray::Contains(int value) const {
    for ( int i = 0; i<size_; i++) {
      if (data_[i] == value) {
        return true;
      }
    }
        return false;
      }



  bool DynamicArray::IsEmpty() const {
    if (size_ == 0 ){
      return true;
    } else{
      return false;
    }
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if( new_capacity> capacity_) {
      int* newData=new int[new_capacity];
      std::copy(&data_[0],&data_[size_],newData);
      delete[] data_;
      data_= newData;
      capacity_=new_capacity;
      return true;
    } else{
      return false;
    }
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment