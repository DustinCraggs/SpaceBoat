#include "FreeArray.hpp"

template<typename T>
FreeArray<T>::FreeArray(int size){
	this->size = size;
	data = new T[size];
	freeList = new int[size];
	for( int i=0; i<size; i++ ){
		freeList[i] = i;
	}
}

template<typename T>
int FreeArray<T>::add(T element){
	
}