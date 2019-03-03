#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdlib>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  class nodes
  {
   public:
    K key;
    V value;
    nodes * left;
    nodes * right;
    nodes() : left(NULL), right(NULL) {}
    nodes(K key, V value) : key(key), value(value), left(NULL), right(NULL) {}
  };
  nodes * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) { copy(rhs.root); }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap temp(rhs);
      std::swap(temp.root, root);
    }
    return *this;
  }

  void copy(const nodes * curr) {
    if (curr != NULL) {
      add(curr->key, curr->value);
      copy(curr->left);
      copy(curr->right);
    }
  }

  void add(const K & key, const V & value) {
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
        p->value = value;
        return;
      }
    }
    nodes * newelement = new nodes(key, value);
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

  const V & lookup(const K & key) const throw(std::invalid_argument) {
    nodes * p = root;
    while (p != NULL) {
      if (key < p->key) {
        p = p->left;
      }
      else if (key > p->key) {
        p = p->right;
      }
      else {
        return p->value;
      }
    }
    throw std::invalid_argument("can't find it");
  }

  nodes * remove_helper(nodes * node, const K & key) {
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
        node->value = s->value;
        node->key = s->key;
        node->right = remove_helper(node->right, s->key);
      }
    }
    return node;
  }

  virtual void remove(const K & key) { root = remove_helper(root, key); }

  void destory(nodes * curr) {
    if (curr != NULL) {
      destory(curr->left);
      destory(curr->right);
      delete curr;
    }
  }

  ~BstMap() { destory(root); }
};
#endif
