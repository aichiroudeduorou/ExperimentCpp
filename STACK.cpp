#include"STACK.h"
#include<iostream>
using namespace std;
STACK::STACK(int m) : QUEUE{ m }, q{ m }{   ////初始化栈：最多存放2m-2个元素
	/*cout << __FUNCTION__ << endl;*/
}
STACK::STACK(const STACK& s) : QUEUE{ s }, q{ s.q } {         		//用栈s深拷贝初始化栈
	/*cout << __FUNCTION__ << endl;*/
}
STACK::STACK(STACK&& s)noexcept :QUEUE{ (QUEUE&&)s }, q{ (QUEUE&&)s.q } {     		//用栈s移动拷贝初始化栈
	/*cout << __FUNCTION__ << endl;*/
}
int STACK::size() const noexcept {		  		//返回栈的容量即2m
	/*cout << __FUNCTION__ << endl;*/
	return (QUEUE::size() + q.size());
}
STACK::operator int() const noexcept {	   		//返回栈的实际元素个数
	/*cout << __FUNCTION__ << endl;*/
	return (QUEUE::operator int() + q.operator int());
}
STACK& STACK::operator<<(int e) { 	     		//将e入栈，并返回当前栈
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
STACK& STACK::operator>>(int& e) {    		//出栈到e，并返回当前栈
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

STACK& STACK::operator=(const STACK& s) {	//深拷贝赋值并返回被赋值栈
	/*cout << __FUNCTION__ << endl;*/
	QUEUE::operator=(s);
	q.operator=(s.q);
	return (*this);
}
STACK& STACK::operator=(STACK&& s)noexcept {   //移动赋值并返回被赋值栈
	/*cout << __FUNCTION__ << endl;*/
	QUEUE::operator=((QUEUE&&)s);
	q.operator=((QUEUE&&)s.q);
	return (*this);
}
char* STACK::print(char* b)const noexcept {	//从栈底到栈顶打印栈元素
	/*cout << __FUNCTION__ << endl;*/
	QUEUE::print(b);
	q.print(b);
	//cout << "STACK:" << b << endl;
	return b;
}

STACK::~STACK()noexcept {	              	//销毁栈
	/*cout << __FUNCTION__ << endl;*/
	q.~QUEUE();
	QUEUE::~QUEUE();
}

