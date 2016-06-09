#ifndef BACKSWAPARRAY_H
#define BACKSWAPARRAY_H


#include <algorithm>

template<typename T>
class BackSwapArray{
public:
	BackSwapArray(unsigned int N);
	~BackSwapArray();

	// add/remove
	void add(T element);
	void remove(unsigned int i);

	// Retrieval
	T* data();
	T at(unsigned int i);
	T &operator[](unsigned int i);

	// Size and capacity
	unsigned int size();
	void reallocate(unsigned int N);
	unsigned int capacity();
private:
	T* m_data;
	unsigned int m_size;
	unsigned int m_capacity;
};

// int main(){
// 	int n = 10;
// 	BackSwapArray<float> bsa(n);
// 	for( int i=0; i<n; i++ ){
// 		bsa.add((i+1)*0.1f);
// 	}
// 	float acc = 0;
// 	bsa.remove(3);
// 	for( int i=0; i<bsa.size(); i++ ){
// 		// acc += bsa.get(i) * bsa.get(i+1) * 3.5;
// 		// acc += bsa[i] * bsa[i+1] * 3.5;
// 		std::cout << bsa[i] << std::endl;
// 	}
// }

template<typename T>
BackSwapArray<T>::BackSwapArray(unsigned int N){
	m_data = new T[N];
	m_size = 0;
	m_capacity = N;
}

template<typename T>
BackSwapArray<T>::~BackSwapArray(){
	delete m_data;
}

template<typename T>
void BackSwapArray<T>::add(T element){
	m_data[m_size++] = element;
}

template<typename T>
void BackSwapArray<T>::remove(unsigned int i){
	m_data[i] = m_data[--m_size];
}

// Returns pointer to data
template<typename T>
T *BackSwapArray<T>::data(){
	return m_data;
}

// Returns copy
template<typename T>
T BackSwapArray<T>::at(unsigned int i){
	return m_data[i];
}

// Returns by reference
template<typename T>
T& BackSwapArray<T>::operator[](unsigned int i){
	return m_data[i];
}

template<typename T>
unsigned int BackSwapArray<T>::size(){
	return m_size;
}

template<typename T>
void BackSwapArray<T>::reallocate(unsigned int N){
	// Copy data
	T* temp = new T[N];
	memcpy(temp, m_data, std::max(m_size, N) * sizeof(T));

	// Update members and free
	m_capacity = N;
	m_size = std::min(m_size, N);
	delete m_data;
	m_data = temp;
}

template<typename T>
unsigned int BackSwapArray<T>::capacity(){
	return m_capacity;
}


#endif
