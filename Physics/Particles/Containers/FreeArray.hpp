#ifndef FREEARRAY_H
#define FREEARRAY_H

#include <glm/glm.hpp>

template<typename T>
class FreeArray{
	int size;
	T *data;
	int *freeList;
public:
	FreeArray(int size);
	int add(T element);
	T get(int index);
	void remove(int index);

};

int main(){
	FreeArray<int> a(10);
}

#endif