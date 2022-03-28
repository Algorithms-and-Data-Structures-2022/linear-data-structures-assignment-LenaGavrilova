#include "assignment/linked_list.hpp"

    namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* el = new Node(value);
    if(front_ != nullptr){
      back_->next=el;
      back_=el;
    } else {
      front_= el;
      back_=el;
    }
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if( index<0 || index >size_) {
      return false;
    }
    Node* el = new Node(value);
    if(IsEmpty()){
      front_=el;
      back_=el;
    } else if (index == 0){
      el->next= front_;
      front_=el;
    } else
        if(index==size_){
      back_->next=el;
      back_=el;
    } else {
      el->next = FindNode(index - 1)->next;
      FindNode(index - 1)->next = el;
    }
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if(index<0 || index>=size_) {
      return false;
    }
    FindNode(index)->value= new_value;
    return true;

  }

  std::optional<int> LinkedList::Remove(int index) {
    if(index<0  || index>=size_){
      return std::nullopt;
    }
    int num;
    if(index==0){
      num=(front_->value);
      front_=(front_->next);
    } else{
      num = FindNode(index)->value;
      FindNode(index-1)->next= FindNode(index)->next;
    }
    size_--;
    return num;

  }

  void LinkedList::Clear() {
    Node* label = front_;
    for ( int i =0; i<size_;i++){
      Node* cursor = label->next;
      delete label;
      label=cursor;
    }
    size_=0;
    front_= nullptr;
    back_= nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if(index<0 || index>=size_) {
      return std::nullopt;
    }
    Node* num = FindNode(index);
    return num->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* label = front_;
    for(int i = 0;i<size_;i++){
      if(label->value==value){
        return i;
      }
      label = label->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
      if(IndexOf(value)!=std::nullopt){
        return true;
      }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    if(size_==0){
      return true;
    }else {
      return false;
    }
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if(front_!= nullptr){
      return front_->value;
    } else {

      return std::nullopt;
    }
  }

  std::optional<int> LinkedList::back() const {
    if(back_!= nullptr){
      return back_->value;
    }else {
      return std::nullopt;
    }
  }

  Node* LinkedList::FindNode(int index) const {
    if(index<0 || index>=size_){
      return nullptr;
    }
    Node* el = front_;
    for(int i=0;i<index;i++){
      el=el->next;

    }
    return el;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr  ,size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment