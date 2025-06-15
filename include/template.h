
#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <vector>
#include <iostream>
using namespace std;

template<typename T>
void Swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
class SimpleContainer {
public:
    void Add(const T& item) { data.push_back(item); }
    size_t Size() const { return data.size(); }
    const T& Get(size_t i) const { return data.at(i); }
private:
    vector<T> data;
};

#endif