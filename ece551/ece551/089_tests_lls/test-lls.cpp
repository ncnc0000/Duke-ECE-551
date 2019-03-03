#include <assert.h>

#include <cstdlib>

#include "il.h"

void testList(void) {
  IntList list;
  assert(list.head == NULL);
  assert(list.tail == NULL);
  assert(list.size == 0);
  assert(list.getSize() == 0);
  assert(list.find(0) == -1);
  list.remove(1);
  assert(list.head == NULL);
  assert(list.tail == NULL);
  assert(list.size == 0);
  assert(list.getSize() == 0);

  IntList test10;
  test10.addFront(100);
  test10.remove(100);
  assert(test10.head == NULL);
  assert(test10.tail == NULL);
  assert(test10.size == 0);
  assert(test10.getSize() == 0);

  IntList test;
  assert(test.head == NULL);
  assert(test.tail == NULL);
  assert(test.size == 0);
  assert(test.getSize() == 0);
  for (int i = 0; i < 10; i++) {
    assert(test.getSize() == i);
    test.addBack(i);
    assert(test.getSize() == i + 1);
    assert(test[i] == i);
    assert(test.find(i) == i);
  }
  assert(test.find(-1) == -1);

  //assert(test[10] == -1);

  IntList list3;
  list3 = list;
  assert(list3.head == NULL);
  assert(list3.tail == NULL);
  assert(list3.size == 0);
  assert(list3.getSize() == 0);
  assert(&list3 != &list);

  list.addFront(5);
  assert(list.head->data == 5);
  assert(list.getSize() == 1);
  assert(list.tail->data == 5);
  assert(list.head->next == NULL);
  assert(list.head->prev == NULL);
  assert(list.tail->next == NULL);
  assert(list.tail->prev == NULL);

  list.addFront(6);
  assert(list.head->data == 6);
  assert(list.getSize() == 2);
  assert(list.head->next->data == 5);
  assert(list.head->next->next == NULL);
  assert(list.head->prev == NULL);
  assert(list.head->next->prev->data == 6);
  assert(list.tail->data == 5);
  assert(list.tail->prev->data == 6);
  assert(list.tail->next == NULL);

  list.addBack(6);
  assert(list.head->data == 6);
  assert(list.getSize() == 3);
  assert(list.head->next->data == 5);
  assert(list.head->next->next->data == 6);
  assert(list.head->prev == NULL);
  assert(list.head->next->prev->data == 6);
  assert(list.head->next->next->next == NULL);
  assert(list.head->next->next->prev->data == 5);
  assert(list.tail->data == 6);
  assert(list.tail->next == NULL);
  assert(list.tail->prev->data == 5);

  assert(list.remove(6) == true);
  assert(list.head->data == 5);
  assert(list.head->prev == NULL);
  assert(list.head->next->data == 6);
  assert(list.head->next->next == NULL);
  assert(list.head->next->prev->data == 5);
  assert(list.tail->data == 6);
  assert(list.tail->next == NULL);
  assert(list.tail->prev->data == 5);
  assert(list.getSize() == 2);

  list.addBack(6);
  assert(list.getSize() == 3);
  assert(list.head->data == 5);
  assert(list.head->next->data == 6);
  assert(list.head->prev == NULL);
  assert(list.head->next->next->data == 6);
  assert(list.head->next->prev->data == 5);
  assert(list.head->next->next->next == NULL);
  assert(list.head->next->next->prev->data == 6);
  assert(list.tail->data == 6);
  assert(list.tail->next == NULL);
  assert(list.tail->prev->data == 6);

  IntList list2;
  list2 = list;
  assert(&list2 != &list);
  assert(list2[0] == list[0]);
  assert(list2[1] == list[1]);
  assert(list2[2] == list[2]);
  assert(list2.getSize() == 3);
  assert(list2.head->data == 5);
  assert(list2.head->next->data == 6);
  assert(list2.head->prev == NULL);
  assert(list2.head->next->next->data == 6);
  assert(list2.head->next->prev->data == 5);
  assert(list2.head->next->next->next == NULL);
  assert(list2.head->next->next->prev->data == 6);
  assert(list2.tail->data == 6);
  assert(list2.tail->next == NULL);
  assert(list2.tail->prev->data == 6);

  assert(list2.remove(9) == false);
  assert(list2.getSize() == 3);
  assert(list2.head->data == 5);
  assert(list2.head->next->data == 6);
  assert(list2.head->prev == NULL);
  assert(list2.head->next->next->data == 6);
  assert(list2.head->next->prev->data == 5);
  assert(list2.head->next->next->next == NULL);
  assert(list2.head->next->next->prev->data == 6);
  assert(list2.tail->data == 6);
  assert(list2.tail->next == NULL);
  assert(list2.tail->prev->data == 6);

  IntList list1(list);
  assert(&list1 != &list);
  assert(list1[0] == list[0]);
  assert(list1[1] == list[1]);
  assert(list1[2] == list[2]);
  assert(list1.getSize() == 3);
  assert(list1.head->data == 5);
  assert(list1.head->next->data == 6);
  assert(list1.head->prev == NULL);
  assert(list1.head->next->next->data == 6);
  assert(list1.head->next->prev->data == 5);
  assert(list1.head->next->next->next == NULL);
  assert(list1.head->next->next->prev->data == 6);
  assert(list1.tail->data == 6);
  assert(list1.tail->next == NULL);
  assert(list1.tail->prev->data == 6);

  const int a = 0;
  assert(list[a] == 5);
  assert(list[a + 1] == 6);
  assert(list[a + 2] == 6);

  assert(list.getSize() == 3);
  assert(list.head->data == 5);
  assert(list.head->next->data == 6);
  assert(list.head->prev == NULL);
  assert(list.head->next->next->data == 6);
  assert(list.head->next->prev->data == 5);
  assert(list.head->next->next->next == NULL);
  assert(list.head->next->next->prev->data == 6);
  assert(list.tail->data == 6);
  assert(list.tail->next == NULL);
  assert(list.tail->prev->data == 6);

  assert(list.find(5) == 0);
  assert(list.find(6) == 1);
  assert(list.find(7) == -1);

  assert(list.getSize() == 3);
  assert(list.head->data == 5);
  assert(list.head->next->data == 6);
  assert(list.head->prev == NULL);
  assert(list.head->next->next->data == 6);
  assert(list.head->next->prev->data == 5);
  assert(list.head->next->next->next == NULL);
  assert(list.head->next->next->prev->data == 6);
  assert(list.tail->data == 6);
  assert(list.tail->next == NULL);
  assert(list.tail->prev->data == 6);
  assert(list3.find(0));
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
