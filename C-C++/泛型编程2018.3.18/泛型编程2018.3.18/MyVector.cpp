#include<iostream>
using namespace std;
#include"MyVector.h"

template <typename T>
ostream& operator<<(ostream& out, const MyVector<T> &obj)
{
	for (int i = 0; i <obj.m_len; i++)
	{
		out << obj.m_space[i] << " ";
	}
	cout << endl;
	return out;
}



template<typename T> 
MyVector<T>::MyVector(int size )
{
	m_space = new T[size];
	m_len = size;
}




template<typename T>
MyVector<T>::MyVector(const MyVector &obj)
{
	m_len = obj.m_len;
	m_space = new T[m_len];

	for (int i = 0; i < m_len; i++)
	{
		m_space[i] = obj.m_space[i];
	}

}



template<typename T>
MyVector<T>::~MyVector()
{
	if (m_space!=NULL)
	{
		delete[] m_space;
		m_space = NULL;
		m_len = 0;
	}

}




template<typename T>
T & MyVector<T>:: operator[](int index)
{
	return m_space[index];
}




template<typename T>
MyVector<T> & MyVector<T>::operator=(const MyVector<T> &obj)
{
	if (m_space!=NULL)
	{
		delete[] m_space;
		m_space = NULL;
		m_len = 0;
	}
	m_len = obj.m_len;
	m_space = new T[m_len];

	for (int i = 0; i < m_len; i++)
	{
		m_space[i] = obj.m_space[i];
	}

	return *this
}