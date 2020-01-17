#pragma once
template <typename T>
class SmartPointer
{
public:
		T *mObj;
	public:
		SmartPointer(T *obj){ }
		T& operator*(int x);
		T* operator->();
		~SmartPointer();
};

template<typename T>
inline T & SmartPointer<T>::operator*(int x)
{
	return *mObj;
}

template<typename T>
inline T * SmartPointer<T>::operator->()
{
	return mObj;
}

template<typename T>
inline SmartPointer<T>::~SmartPointer()
{
	delete mObj;
}
