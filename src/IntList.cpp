#include "../include/IntList.hpp"
#include <cstdlib>

void IntList::resize(int newCapacity) {
  int *newData = new int[newCapacity];
  for (int i = 0; i < count; i++) {
    newData[i] = data[i];
  }
  delete[] data;
  data = newData;
  capacity = newCapacity;
}

IntList::IntList() : data(0), capacity(0), count(0) {
  capacity = 10;
  data = new int[capacity];
}

IntList::~IntList() { delete[] data; }

void IntList::add(int value) {
  if (count == capacity) {
    resize(capacity * 2);
  }
  data[count++] = value;
}

int IntList::size() const { return count; }

int IntList::get(int index) const {
  if (index < 0 || index >= count)
    return -1;
  return data[index];
}
