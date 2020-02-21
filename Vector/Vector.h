#pragma once									
#include <iostream>									

template<typename T>
class Vector
{
public:
	Vector();                               // default constructor 								
	Vector(const size_t size);				// constructor				
	Vector(const Vector<T>& a);				// copy constructor				
	Vector(Vector<T>&& a);				    // move constructor 				
	~Vector();								// destructor


	Vector<T>& operator=(const Vector<T>& rhs);	// assignment operator							
	Vector<T>& operator=(Vector<T>&& rhs);      // move assignment operator								
	T& operator[](T i);

	size_t size() const;
	size_t capacity() const;

	void resize(const size_t size);
	void reserve(const size_t cap);
	void push_back(T a);
	void pop_back();

	friend std::ostream& operator<<(std::ostream& output, const Vector<T>& rhs)
	{
		for (size_t i = 0; i < rhs._size; ++i) {
			output << rhs._elem[i] << ' ';
		}
		return output;
	}

private:
	T* _elem;
	size_t _capacity;
	size_t _size;
};


template<typename T>
Vector<T>::Vector()                // default constructor									
	: _elem(new T[1]), _size(0), _capacity(1)
{
	//_elem[0] = T();           // size is 0, therefore no need to initialize the value.								
}

template<typename T>
Vector<T>::Vector(const size_t size)         // constructor									
{
	if (size == 0) {                         // same as default constructor								
		_elem = new T[1];
		_size = 0;
		_capacity = 1;
	}
	else {
		_size = size;
		_capacity = size;
		_elem = new T[_size];
		for (size_t i = 0; i < _size; ++i)
			_elem[i] = T();                   // value-initialization						
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T>& a)          // copy constructor (deep copy) 									
	: _size(a._size), _capacity(a._capacity)   // initializing list is more cost-efficient								
{
	_elem = new T[a._capacity];
	for (size_t i = 0; i < a._size; ++i) {
		_elem[i] = a._elem[i];
	}
}

template<typename T>
Vector<T>::Vector(Vector<T>&& a)          // move constructor (shallow copy) 									
	: _size(a._size),
	_capacity(a._capacity),
	_elem(a._elem)
{
	a._elem = nullptr;
}

template<typename T>
Vector<T>::~Vector()             // destructor									
{
	delete[] _elem;
	std::cout << "destructor executed" << std::endl;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)    // assignment operator (deep copy)									
{
	if (this == &rhs) {
		return *this;
	}

	delete[] _elem;
	_elem = new T[rhs._capacity];   // "_elem" redirected to new memory of correct size.								
	_size = rhs._size;
	_capacity = rhs._capacity;
	for (size_t i = 0; i < rhs._size; ++i) {
		_elem[i] = rhs._elem[i];
	}
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs)    // move assignment operator (shallow copy)									
// shouldn't use "const Vector<T>&& rhs", as const Vector<T>&& rhs == const Vector<T> & rhs									
{
	if (this == &rhs) {
		return *this;
	}

	delete[] _elem;
	_elem = rhs._elem;
	_size = rhs._size;
	_capacity = rhs._capacity;
	rhs._elem = nullptr;
	return *this;
}


template<typename T>
T& Vector<T>::operator[](T i)       // operator[] overloading									
{
	if (i < _size) {
		return _elem[i];
	}
	else {
		return std::out_of_range("out_of_range");
	}
}

template<typename T>
size_t Vector<T>::size() const           // const means object itself should be constant. Calling this function shouldn't change the object.									
{
	return _size;
}

template<typename T>
size_t Vector<T>::capacity() const
{
	return _capacity;
}

template<typename T>
void Vector<T>::resize(const size_t size)
{
	if (size > _size&& size <= _capacity) {
		for (size_t i = _size; i < size; ++i) {
			_elem[i] = T();              // value-initialize the newly-expanded memory to correspond to _size 						
		}
	}
	else
	{
		T* _elem_new = new T[size];                // new array created on heap 							
		for (size_t i = 0; i < _size; ++i) {
			_elem_new[i] = std::move(_elem[i]);    // use "move assignment operator" to perform shallow copy, which is cost-effective when the "T class" contains pointer that points to huge amount of data.						
		}
		for (size_t i = _size; i < size; ++i) {
			_elem_new[i] = T();
		}
		delete[] _elem;
		_elem = _elem_new;
		_elem_new = nullptr;
		_capacity = size;      // may consider to expand the capacity beyond size, but not mandatory.							
	}
	_size = size;        // under all conditions, _size needs to match size 								
}

template<typename T>
void Vector<T>::reserve(const size_t capacity)
{
	if (capacity > _capacity) {
		T* _elem_new = new T[capacity];
		for (size_t i = 0; i < _size; ++i) {
			_elem_new[i] = std::move(_elem[i]);     // call move assignment operator for shallow copy						
		}
		//for (size_t i = _size; i < cap; ++i) {    // no need to initialize memory beyond _size							
		//	_elem_new[i] = T();						
		delete[] _elem;
		_elem = _elem_new;
		_elem_new = nullptr;
		_capacity = capacity;
	}
}

template<typename T>
void Vector<T>::push_back(T a)
{
	if (_capacity < _size + 1)
	{
		reserve(2 * _size);
	}
	_elem[_size] = a;
	++_size;
}

template<typename T>
void Vector<T>::pop_back()
{
	//_elem[_size - 1] = T();   // no need value-initialize beyond _size.								
	--_size;
}

