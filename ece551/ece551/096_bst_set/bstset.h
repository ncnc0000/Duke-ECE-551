#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <iostream>

#include "cstdlib"
#include "set.h"

template<typename T>
class BstSet : public Set<T>
{
  class nodes
  {
   public:
    T key;
    nodes * left;
    nodes * right;
    nodes() {}
    nodes(const T & key) : key(key), left(NULL), right(NULL) {}
  };
  nodes * root;

 public:
  BstSet() : root(NULL) {}
  void add(const T & key) {
    nodes * p = root;
    nodes * temp = NULL;
    while (p != NULL) {
      temp = p;
      if (key < p->key) {
        p = p->left;
      }
      else if (key > p->key) {
        p = p->right;
      }
      else {
        return;
      }
    }
    nodes * newelement = new nodes(key);
    if (root != NULL) {
      if (temp->key < key) {
        temp->right = newelement;
      }
      else {
        temp->left = newelement;
      }
    }
    else {
      root = newelement;
    }
  }

  BstSet(const BstSet & rhs) : root(NULL) { copy(rhs.root); }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      BstSet temp(rhs);
      std::swap(temp.root, root);
    }
    return *this;
  }

  void copy(const nodes * node) {
    if (node != NULL) {
      add(node->key);
      copy(node->left);
      copy(node->right);
    }
  }

  bool contains(const T & key) const {
    nodes * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return true;
      }
      if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }

  nodes * remove_helper(nodes * node, const T & key) {
    if (node == NULL) {
      return node;
    }
    else if (key < node->key) {
      node->left = remove_helper(node->left, key);
    }
    else if (key > node->key) {
      node->right = remove_helper(node->right, key);
    }
    else {
      if ((node->right == NULL) && (node->left == NULL)) {
        delete node;
        node = NULL;
      }
      else if (node->left == NULL) {
        nodes * temp = node;
        node = node->right;
        delete temp;
      }
      else if (node->right == NULL) {
        nodes * temp = node;
        node = node->left;
        delete temp;
      }
      else {
        // select the left-most right child (right once, then all the way left)
        nodes * s = node->right;
        // use a iteration to find left most
        while (s->left != NULL) {
          s = s->left;
        }
        node->key = s->key;
        node->right = remove_helper(node->right, s->key);
      }
    }
    return node;
  }

  virtual void remove(const T & key) { root = remove_helper(root, key); }

  void destory(nodes * node) {
    if (node != NULL) {
      destory(node->left);
      destory(node->right);
      delete node;
    }
  }

  ~BstSet() { destory(root); }
};
#endif
