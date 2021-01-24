#include"STACK.h"
#include<iostream>
using namespace std;
STACK::STACK(int m) : QUEUE{ m }, q{ m }{   ////��ʼ��ջ�������2m-2��Ԫ��
	/*cout << __FUNCTION__ << endl;*/
}
STACK::STACK(const STACK& s) : QUEUE{ s }, q{ s.q } {         		//��ջs�����ʼ��ջ
	/*cout << __FUNCTION__ << endl;*/
}
STACK::STACK(STACK&& s)noexcept :QUEUE{ (QUEUE&&)s }, q{ (QUEUE&&)s.q } {     		//��ջs�ƶ�������ʼ��ջ
	/*cout << __FUNCTION__ << endl;*/
}
int STACK::size() const noexcept {		  		//����ջ��������2m
	/*cout << __FUNCTION__ << endl;*/
	return (QUEUE::size() + q.size());
}
STACK::operator int() const noexcept {	   		//����ջ��ʵ��Ԫ�ظ���
	/*cout << __FUNCTION__ << endl;*/
	return (QUEUE::operator int() + q.operator int());
}
STACK& STACK::operator<<(int e) { 	     		//��e��ջ�������ص�ǰջ
	/*cout << __FUNCTION__ << endl;*/
	if (QUEUE::operator int() < QUEUE::size() - 1) {
		QUEUE::operator<<(e);
		return (*this);
	}
	if (q.operator int() == q.size() - 1) {
		throw "STACK is full!";
	}
	else {
		q.operator<<(e);
	}
	return (*this);
}
STACK& STACK::operator>>(int& e) {    		//��ջ��e�������ص�ǰջ
	/*cout << __FUNCTION__ << endl;*/
	int base = QUEUE::operator int();
	int more = q.operator int();
	if (base == 0) {
		throw "STACK is empty!";
	}
	int* elem=nullptr;
	if (more != 0) {  //QUEUE is full
		elem = new int[more];
		for (int i = 0; i < more-1; i++)
			q.operator>>(elem[i]);
		q.operator>>(e);
		for (int i = 0; i < more - 1; i++)
			q.operator<<(elem[i]);
		delete[] elem;
	}
	else {
		elem = new int[base];
		for (int i = 0; i < base-1; i++)
			QUEUE::operator>>(elem[i]);
		QUEUE::operator>>(e);
		for (int i = 0; i < base - 1; i++)
			QUEUE::operator<<(elem[i]);
		delete[] elem;
	}
	return (*this);
}

STACK& STACK::operator=(const STACK& s) {	//�����ֵ�����ر���ֵջ
	/*cout << __FUNCTION__ << endl;*/
	QUEUE::operator=(s);
	q.operator=(s.q);
	return (*this);
}
STACK& STACK::operator=(STACK&& s)noexcept {   //�ƶ���ֵ�����ر���ֵջ
	/*cout << __FUNCTION__ << endl;*/
	QUEUE::operator=((QUEUE&&)s);
	q.operator=((QUEUE&&)s.q);
	return (*this);
}
char* STACK::print(char* b)const noexcept {	//��ջ�׵�ջ����ӡջԪ��
	/*cout << __FUNCTION__ << endl;*/
	QUEUE::print(b);
	q.print(b);
	//cout << "STACK:" << b << endl;
	return b;
}

STACK::~STACK()noexcept {	              	//����ջ
	/*cout << __FUNCTION__ << endl;*/
	q.~QUEUE();
	QUEUE::~QUEUE();
}

