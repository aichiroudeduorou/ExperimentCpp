#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

using namespace std;

struct Queue {
    int* const  elems;	   	//elems申请内存用于存放队列的元素
    const  int  max;	  	//elems申请的最大元素个数max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
};
void initQueue(Queue* const p, int m);	//初始化p指队列：最多申请m个元素
void initQueue(Queue* const p, const Queue& s); //用s深拷贝初始化p指队列
void initQueue(Queue* const p, Queue&& s); //用s移动初始化p指队列
int  number(const Queue* const p);	//返回p指队列的实际元素个数
int  size(const Queue* const p);			//返回p指队列申请的最大元素个数max
Queue* const enter(Queue* const p, int e);  //将e入队列尾部，并返回p
Queue* const leave(Queue* const p, int& e); //从队首出元素到e，并返回p
Queue* const assign(Queue* const p, const Queue& q); //深拷贝赋q给队列并返回p
Queue* const assign(Queue* const p, Queue&& q); //移动赋q给队列并返回p
char* print(const Queue* const p, char* s);//打印p指队列至s并返回s
void destroyQueue(Queue* const p);	 //销毁p指向的队列

extern const char* TestQueue(int& s);


int main()
{
    int s;
    const char *e = TestQueue(s);
    cout << e << endl;
    cout << s << endl;
    getchar();
    return 0;
}

void initQueue(Queue* const p, int m) {            //初始化p指队列：最多申请m个元素
    //cout << "func1" << endl;
    if (p->max != 0) {
        *(int*)&(p->max) = 0;
        p->head = p->tail = 0;
        free(p->elems);
        *(int**)&(p->elems) = NULL;
    }
    *(int*)&(p->max) = m;
    *(int**)&(p->elems) = (int*)malloc(m * sizeof(int));
    p->head = p->tail = 0;
}
void initQueue(Queue* const p, const Queue& s) {            ////用s深拷贝初始化p指队列
    //cout << "func2" << endl;
    if (p->elems == s.elems) return;
    if (p->max != 0) {
        *(int*)&(p->max) = 0;
        p->head = p->tail = 0;
        free(p->elems);
        *(int**)&(p->elems) = NULL;
    }
    const struct Queue* q = &s;
    if (s.elems != NULL) {
        int max = s.max;
        *(int*)&(p->max) = max;
        p->head = q->head;
        p->tail = q->tail;
		int* temp = (int*)malloc(max * sizeof(int));
        for (int i = s.head; i != s.tail; i=(i+1)%max) {
            temp[i] = s.elems[i];
        }
        *(int**)&(p->elems) = temp;
    }
}
void initQueue(Queue* const p, Queue&& s) {           //用s移动初始化p指队列
    //cout << "func3" << endl;
    if (p->elems == s.elems) return;
    if (p->max != 0) {
        *(int*)&(p->max) = 0;
        p->head = p->tail = 0;
        free(p->elems);
        *(int**)&(p->elems) = NULL;
    }
    if (s.elems != NULL) {
        const struct Queue* q = &s;
        int max = q->max;
        *(int*)&(p->max) = max;
        *(int**)&(p->elems) = q->elems;
        p->head = q->head;
        p->tail = q->tail;
        *(int**)&(q->elems) = NULL;
        *(int*)&(q->max) = 0;
        s.head = s.tail = 0;
    }
}
int  number(const Queue* const p) {	//返回p指队列的实际元素个数
    //cout << "func4" << endl;
    if (p->max == 0)
        return 0;
    int num = p->tail - p->head;
    if (num < 0) num += p->max;
    return num;
}
int  size(const Queue* const p) {			//返回p指队列申请的最大元素个数max
    //cout << "func5" << endl;
    return p->max;
}
Queue* const enter(Queue* const p, int e) {             //将e入队列尾部，并返回p
    //cout << "func6" << endl;
    int max = p->max;
    if ((p->tail + 1) % max == p->head) {
        throw "Queue is full!";
    }
    ((int*)(p->elems))[p->tail] = e;
	p->tail = (p->tail + 1) % p->max;
    return p;
}
Queue* const leave(Queue* const p, int& e) {            //从队首出元素到e，并返回p
    //cout << "func7" << endl;
    if (p->head == p->tail) {
        throw "Queue is empty!";
    }
    e = (p->elems)[p->head];
    p->head = (p->head + 1) % p->max;
    return p;
}
Queue* const assign(Queue* const p, const Queue& q) {               //深拷贝赋q给队列并返回p
    //cout << "func8" << endl;
    if (p->elems == q.elems) return p;
    if (p->max != 0) {
        *(int*)&(p->max) = 0;
        p->head = p->tail = 0;
        free(p->elems);
        *(int**)&(p->elems) = NULL;
    }
    int max = q.max;
    *(int*)&(p->max) = max;
    p->head = q.head;
    p->tail = q.tail;
	int* temp = (int*)malloc(max * sizeof(int));
    for (int i = q.head; i != q.tail; i=(i+1)%max) {
        temp[i] = q.elems[i];
    }
    *(int**)&(p->elems) = temp;
    return p;
}
Queue* const assign(Queue* const p, Queue&& q) {               //移动赋q给队列并返回p
    //cout << "func9" << endl;
    if (p->elems == q.elems) return p;
    if (p->max != 0) {
        *(int*)&(p->max) = 0;
        p->head = p->tail = 0;
        free(p->elems);
        *(int**)&(p->elems) = NULL;
    }
    int max = q.max;
    *(int*)&(p->max) = max;
    *(int**)&(p->elems) = q.elems;
    p->head = q.head;
    p->tail = q.tail;
    *(int**)&(q.elems) = NULL;
    *(int*)&(q.max) = 0;
    q.head = q.tail = 0;
    return p;
}
char* print(const Queue* const p, char* s) {                 //打印p指队列至s并返回s
    //cout << "func10" << endl;
    if (p->max == 0) return s;
    int max = p->max;
    for (int i = p->head; i != p->tail; i = (i + 1) % max) {
        char* str = s + strlen(s);
        sprintf(str, "%d,", p->elems[i]);
    }
    return s;
}

void destroyQueue(Queue* const p) {	                      //销毁p指向的队列
    //cout << "func11" << endl;
    *(int*)&(p->max) = 0;
    p->head = p->tail = 0;
    free(p->elems);
    *(int**)&(p->elems) = NULL;
}