#include"QUEUE.h"
QUEUE::QUEUE(int m) :max{ m }, head{ 0 }, tail{ 0 }, elems{} {		//��ʼ�����У��������m��Ԫ��
    //cout << "fun1" << endl;
    *(int**)&elems = new int[max];
}
QUEUE::QUEUE(const QUEUE& q) : max{ q.max }, head{ q.head }, tail{ q.tail }, elems{} {			//��q�����ʼ������
    //cout << "fun2" << endl;
    int* temp = new int[max];
    for (int i = head; i != tail; i = (i + 1) % max) {
        temp[i] = q.elems[i];
    }
    *(int**)&elems = temp;
}
QUEUE::QUEUE(QUEUE&& q)noexcept :max{ q.max }, head{ q.head }, tail{ q.tail }, elems{q.elems} {		//��q�ƶ���ʼ������
    //cout << "fun3" << endl;
    *(int*)&q.max = 0;
    q.head = q.tail = 0;
    *(int**)&q.elems = nullptr;
}
QUEUE::operator int() const noexcept {	//���ض��е�ʵ��Ԫ�ظ���
    //cout << "fun4" << endl;
    int num = tail - head;
    if (num < 0)
        num += max;
    return num;
}
int QUEUE::size() const noexcept {		//���ض�����������Ԫ�ظ���max
    //cout << "fun5" << endl;
    return max;
};
QUEUE& QUEUE::operator<<(int e) {  	//��e�����β���������ص�ǰ����
    //cout << "fun6" << endl;
    if ((tail + 1) % max == head) {
        throw "QUEUE is full!";
    }
    ((int*)(elems))[tail] = e;
    tail = (tail + 1) % max;
    return *this;
}
QUEUE& QUEUE::operator>>(int& e) { 	//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
    //cout << "fun7" << endl;
    if (head == tail) {
        throw "QUEUE is empty!";
    }
    e = (elems)[head];
    head = (head + 1) % max;
    return *this;
}
QUEUE& QUEUE::operator=(const QUEUE& q) {            //�����ֵ�����ر���ֵ����
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
QUEUE& QUEUE::operator=(QUEUE&& q)noexcept {               //�ƶ���ֵ�����ر���ֵ����
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
char* QUEUE::print(char* s) const noexcept {                 //��ӡ������s������s
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
QUEUE::~QUEUE() {	 					//���ٵ�ǰ����
    //cout << "fun11" << endl;
    if (max != 0) {
        *(int*)&(max) = 0;
        head = tail = 0;
        delete[] elems;
        *(int**)&(elems) = nullptr;
    }
}