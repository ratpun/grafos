#ifndef INTLIST_HPP
#define INTLIST_HPP

class IntList {
private:
  int *data;
  int capacity;
  int count;
  void resize(int newCapacity);

public:
  IntList();
  ~IntList();
  void add(int value);
  int size() const;
  int get(int index) const;
};

#endif
