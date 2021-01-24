#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
#include<iostream>

using namespace std;

template <typename T>
class MAT {
	T* const e;							//ָ���������;���Ԫ�ص�ָ��
	const int r, c;							//�������r����c��С
public:
	MAT(int r, int c);						//������
	MAT(const MAT& a);				//�������
	MAT(MAT&& a)noexcept;			//�ƶ�����
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
	virtual MAT operator+(const MAT& a)const;	//����ӷ������ܼ����쳣
	virtual MAT operator-(const MAT& a)const;	//������������ܼ����쳣
	virtual MAT operator*(const MAT& a)const;	//����˷������ܳ����쳣
	virtual MAT operator~()const;					//����ת��
	virtual MAT& operator=(const MAT& a);		//�����ֵ����
	virtual MAT& operator=(MAT&& a)noexcept;	//�ƶ���ֵ����
	virtual MAT& operator+=(const MAT& a);		//��+=������
	virtual MAT& operator-=(const MAT& a);		//��-=������
	virtual MAT& operator*=(const MAT& a);		//��*=������
//print�����s������s�����ÿո���������ûس�����
	virtual char* print(char* s)const noexcept;
};
template <typename T> MAT<T>::MAT(int r, int c) :e{ new T[r * c] }, r{ r }, c{ c } {
	cout << __FUNCTION__ << endl;
}
template <typename T> MAT<T>::MAT(const MAT<T>& a) : e{ new T[a.r * a.c] }, r{ a.r }, c{ a.c } {				//�������
	cout << __FUNCTION__ << endl;
	for (int i = 0; i < (a.r * a.c); i++) {
		e[i] = a.e[i];
	}
}
template <typename T> MAT<T>::MAT(MAT<T>&& a)noexcept :e{ a.e }, r{ a.r }, c{ a.c } {			//�ƶ�����
	cout << __FUNCTION__ << endl;
	*(T**)&a.e = nullptr;
	*(int*)&a.r = 0;
	*(int*)&a.c = 0;
}
template <typename T> MAT<T>::~MAT()noexcept {
	cout << __FUNCTION__ << endl;
	if (e!=nullptr) {
		delete[]e;
		*(T**)&e = nullptr;
		*(int*)&r = 0;
		*(int*)&c = 0;
	}
}
template <typename T> T* const MAT<T>::operator[ ](int r) {//ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
	cout << __FUNCTION__ << endl;
	if (r >= this->r) {
		throw"Cross the border!";
	}
	if (r < 0) {
		throw"Cross the border!";
	}
	return &e[r * c];
}
template <typename T> MAT<T> MAT<T>::operator+(const MAT<T>& a)const {	//����ӷ������ܼ����쳣
	cout << __FUNCTION__ << endl;
	MAT sum(r, c);
	if (e == nullptr || a.e == nullptr || r != a.r || c != a.c) {
		throw"Can not add!";
	}
	for (int i = 0; i < r * c; i++) {
		sum.e[i] = e[i] + a.e[i];
	}
	return sum;
}
template <typename T> MAT<T> MAT<T>::operator-(const MAT<T>& a)const {	//������������ܼ����쳣
	cout << __FUNCTION__ << endl;
	MAT sub(r, c);
	if (e == nullptr || a.e == nullptr || r != a.r || c != a.c) {
		throw"Can not sub!";
	}
	for (int i = 0; i < r * c; i++) {
		sub.e[i] = e[i] - a.e[i];
	}
	return sub;
}
template <typename T> MAT<T> MAT<T>::operator*(const MAT<T>& a)const {	//����˷������ܳ����쳣
	cout << __FUNCTION__ << endl;
	MAT mul(r, c);
	if (e == nullptr || a.e == nullptr || c != a.r) {
		throw"Can not multiply!";
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < a.c; j++) {
			mul.e[i * a.c + j] = 0;
			for (int k = 0; k < c; k++) {
				mul.e[i * a.c + j] += (e[i * c + k] * a.e[k * a.c + j]);
			}
		}

	}
	return mul;
}
template <typename T> MAT<T> MAT<T>::operator~()const {					//����ת��
	cout << __FUNCTION__ << endl;
	MAT trans(c, r);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			trans.e[j * r + i] = e[i * c + j];
		}
	}
	return trans;
}
template <typename T> MAT<T>& MAT<T>::operator=(const MAT<T>& a) {		//�����ֵ����
	cout << __FUNCTION__ << endl;
	if (&a == this)
		return (*this);
	*(T**)&e = new T[a.r * a.c];
	*(int*)&r = a.r;
	*(int*)&c = a.c;
	for (int i = 0; i < r * c; i++) {
		e[i] = a.e[i];
	}
	return (*this);
}
template <typename T> MAT<T>& MAT<T>::operator=(MAT<T>&& a)noexcept {	//�ƶ���ֵ����
	cout << __FUNCTION__ << endl;
	if (&a == this)
		return *this;
	*(T**)&e = a.e;
	*(int*)&r = a.r;
	*(int*)&c = a.c;
	*(T**)&a.e = nullptr;
	*(int*)&a.r = 0;
	*(int*)&a.c = 0;
	return (*this);
}
template <typename T> MAT<T>& MAT<T>::operator+=(const MAT<T>& a) {		//��+=������
	cout << __FUNCTION__ << endl;
	if (e == nullptr || a.e == nullptr || r != a.r || c != a.c) {
		throw"Can not add!";
	}
	for (int i = 0; i < r * c; i++) {
		e[i] = e[i] + a.e[i];
	}
	return (*this);
}
template <typename T> MAT<T>& MAT<T>::operator-=(const MAT<T>& a) {		//��-=������
	cout << __FUNCTION__ << endl;
	if (e == nullptr || a.e == nullptr || r != a.r || c != a.c) {
		throw"Can not sub!";
	}
	for (int i = 0; i < r * c; i++) {
		e[i] = e[i] - a.e[i];
	}
	return (*this);
}
//template <typename T> MAT<T>& MAT<T>::operator*=(const MAT<T>& a) {		//��*=������
//	cout << __FUNCTION__ << endl;
//	MAT<T> mul(r, a.c);
//	if (e == nullptr || a.e == nullptr || c != a.r) {
//		throw"Can not multiply!";
//	}
//	for (int i = 0; i < r; i++) {
//		for (int j = 0; j < a.c; j++) {
//			mul.e[i * a.c + j] = 0;
//			for (int k = 0; k < c; k++) {
//				mul.e[i * a.c + j] += (e[i * c + k] * a.e[k * a.c + j]);
//			}
//		}
//	}
//	if (e != nullptr)
//		delete[]e;
//	*(T**)&e = new T[mul.r * mul.c];
//	*(int*)&r = mul.r;
//	*(int*)&c = mul.c;
//	for (int i = 0; i < r * c; i++) {
//		e[i] = mul.e[i];
//	}
//	//delete[]mul.e;
//	/*T** z = (T**)&e;
//	*z = mul.e;
//	z = (T**)&mul.e;
//	*z = nullptr;
//	*(int*)&r = mul.r;
//	*(int*)&c = mul.c;*/
//	return (*this);
//}
template <typename T> MAT<T> & MAT<T>::operator*=(const MAT<T> & a) {		//��*=������
	cout << __FUNCTION__ << endl;
	T* tmp = new T[r * a.c];
	if (e == nullptr || a.e == nullptr || c != a.r) {
		throw"Can not multiply!";
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < a.c; j++) {
			tmp[i * a.c + j] = 0;
			for (int k = 0; k < c; k++) {
				tmp[i * a.c + j] += (e[i * c + k] * a.e[k * a.c + j]);
			}
		}
	}
	if (e != nullptr)
		delete[]e;
	*(T**)&e = tmp;
	*(int*)&c = a.c;
	return (*this);
}
template <typename T> char* MAT<T>::print(char* s)const noexcept { //print�����s������s�����ÿո���������ûس�����
	cout << __FUNCTION__ << endl;
	char* temp = s;
	s[0] = '\0';
	if (e == nullptr)
		return s;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			temp = s + strlen(s);
			if (j == c - 1) {
				sprintf(temp, "%6ld\n", e[i * c + j]);
			}
			else {
				sprintf(temp, "%6ld ", e[i * c + j]);
			}
		}
	}
	return s;
}
