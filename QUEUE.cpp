#include"QUEUE.h"
QUEUE::QUEUE(int m) :max{ m }, head{ 0 }, tail{ 0 }, elems{} {		//初始化队列：最多申请m个元素
    //cout << "fun1" << endl;
    *(int**)&elems = new int[max];
}
QUEUE::QUEUE(const QUEUE& q) : max{ q.max }, head{ q.head }, tail{ q.tail }, elems{} {			//用q深拷贝初始化队列
    //cout << "fun2" << endl;
    int* temp = new int[max];
    for (int i = head; i != tail; i = (i + 1) % max) {
        temp[i] = q.elems[i];
    }
    *(int**)&elems = temp;
}
QUEUE::QUEUE(QUEUE&& q)noexcept :max{ q.max }, head{ q.head }, tail{ q.tail }, elems{q.elems} {		//用q移动初始化队列
    //cout << "fun3" << endl;
    *(int*)&q.max = 0;
    q.head = q.tail = 0;
    *(int**)&q.elems = nullptr;
}
QUEUE::operator int() const noexcept {	//返回队列的实际元素个数
    //cout << "fun4" << endl;
    int num = tail - head;
    if (num < 0)
        num += max;
    return num;
}
int QUEUE::size() const noexcept {		//返回队列申请的最大元素个数max
    //cout << "fun5" << endl;
    return max;
};
QUEUE& QUEUE::operator<<(int e) {  	//将e入队列尾部，并返回当前队列
    //cout << "fun6" << endl;
    if ((tail + 1) % max == head) {
        throw "QUEUE is full!";
    }
    ((int*)(elems))[tail] = e;
    tail = (tail + 1) % max;
    return *this;
}
QUEUE& QUEUE::operator>>(int& e) { 	//从队首出元素到e，并返回当前队列
    //cout << "fun7" << endl;
    if (head == tail) {
        throw "QUEUE is empty!";
    }
    e = (elems)[head];
    head = (head + 1) % max;
    return *this;
}
QUEUE& QUEUE::operator=(const QUEUE& q) {            //深拷贝赋值并返回被赋值队列
    //cout << "fun8" << endl;
    if (elems == q.elems) return *this;
    if (elems != nullptr) {
        *(int**)&(elems) = nullptr;
    }
    *(int*)&(max) = q.max;
    head = q.head;
    tail = q.tail;
    int* temp = new int[max];
    for (int i = q.head; i != q.tail; i = (i + 1) % max) {
        temp[i] = q.elems[i];
    }
    *(int**)&(elems) = temp;
    return *this;
}
QUEUE& QUEUE::operator=(QUEUE&& q)noexcept {               //移动赋值并返回被赋值队列
    //cout << "fun9" << endl;
    if (elems == q.elems) return *this;
    if (elems != nullptr) {
        *(int**)&(elems) = nullptr;
    }
    *(int*)&(max) = q.max;
    *(int**)&(elems) = q.elems;
    head = q.head;
    tail = q.tail;
    *(int**)&(q.elems) = nullptr;
    *(int*)&(q.max) = 0;
    q.head = q.tail = 0;
    return *this;
}
char* QUEUE::print(char* s) const noexcept {                 //打印队列至s并返回s
    //cout << "fun10" << endl;
    //cout << s << endl;
    *s = '\0';
    if (max == 0) return s;
    int i;
    for (i = head; i != tail; i = (i + 1) % max) {

        char* str = s + strlen(s);
        sprintf(str, "%d,", elems[i]);
    }
    //cout << s << endl;
    return s;
}
QUEUE::~QUEUE() {	 					//销毁当前队列
    //cout << "fun11" << endl;
    if (max != 0) {
        *(int*)&(max) = 0;
        head = tail = 0;
        delete[] elems;
        *(int**)&(elems) = nullptr;
    }
}