#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE

template<typename T>
class LinkedList
{
  class nodes
  {
   public:
    T data;
    nodes * next;
    nodes * prev;
    //nodes() : next(NULL), prev(NULL) {}
    nodes(const T & d) : data(d), next(NULL), prev(NULL) {}
    //nodes(T & d, nodes * item) : data(d), next(item), prev(NULL) {}
  };

  class iterator
  {
    nodes * current;

   public:
    iterator() : current(NULL) {}
    iterator(nodes * c) : current(c) {}
    iterator & operator++() {
      current = current->next;
      return *this;
    }
    bool operator==(const iterator & rhs) const { return current == rhs.current; }
    T & operator*() { return current->data; }
  };
  int size;
  nodes * head;
  nodes * tail;

 public:
  iterator begin() { return iterator(head); }
  iterator end() { return iterator(tail); }
  LinkedList() : size(0), head(NULL), tail(NULL) {}

  LinkedList(const LinkedList & rhs) : size(0), head(NULL), tail(NULL) {
    if (rhs.size == 0) {
      head = NULL;
      tail = NULL;
      return;
    }
    nodes * temp = rhs.head;
    while (temp != NULL) {
      addBack(temp->data);
      temp = temp->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList temp(rhs);
    std::swap(head, temp.head);
    std::swap(tail, temp.tail);
    std::swap(size, temp.size);
    return *this;
  }

  void addFront(const T & item) {
    nodes * temp = head;
    head = new nodes(item);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next = temp;
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    nodes * temp = tail;
    tail = new nodes(item);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev = temp;
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    nodes * current = head;
    if (size == 0) {
      return false;
    }
    for (int i = 0; i < size; i++) {
      if (item == current->data) {
        if (current->next != NULL) {
          current->next->prev = current->prev;
        }
        else {
          tail = current->prev;
        }
        if (current->prev != NULL) {
          current->prev->next = current->next;
        }
        else {
          head = current->next;
        }
        size--;
        delete current;
        return true;
      }
      current = current->next;
    }
    return false;
  }

  int getSize() const { return size; }

  T & operator[](int index) {
    try {
      if (index < 0 || index > size - 1 || this->size == 0) {
        throw std::out_of_range("out of range");
      }
      nodes * current = head;
      for (int i = 0; i < index; i++) {
        current = current->next;
      }
      return current->data;
    }
    catch (const std::out_of_range & oor) {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
      exit(EXIT_FAILURE);
    }
  }

  const T & operator[](int index) const {
    try {
      if (index < 0 || index > size - 1 || this->size == 0) {
        throw std::out_of_range("out of range");
      }
      nodes * current = this->head;
      for (int i = 0; i < index; i++) {
        current = current->next;
      }
      return current->data;
    }

    catch (const std::out_of_range & oor) {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
      exit(EXIT_FAILURE);
    }
  }

  int find(const T & item) {
    if (head == NULL) {
      return -1;
    }
    nodes * current = head;
    int i = 0;
    while (current != NULL) {
      if (current->data == item) {
        return i;
      }
      current = current->next;
      i++;
    }
    return -1;
  }

  ~LinkedList() {
    while (head != NULL) {
      nodes * tmp = head->next;
      delete head;
      head = tmp;
    }
    tail = NULL;
    size = 0;
  }
  friend void testList(void);
};
#endif
