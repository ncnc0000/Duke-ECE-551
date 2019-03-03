#include "node.h"

#include <assert.h>
void buildMapHelper(const Node * nodes, BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (nodes->sym != NO_SYM) {
    assert(nodes->left == NULL && nodes->right == NULL);
    theMap[nodes->sym] = b;
  }
  else {
    assert(nodes->left != NULL && nodes->right != NULL);
    buildMapHelper(nodes->left, b.plusZero(), theMap);
    buildMapHelper(nodes->right, b.plusOne(), theMap);
  }
}

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  buildMapHelper(this, b, theMap);
}
