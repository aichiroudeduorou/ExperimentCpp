#include"STACK.h"
extern const char* TestSTACK(int& s);

int main() {
    int s;
    const char* e = TestSTACK(s);
    cout << s << endl;
    cout << e << endl;
    getchar();
    return 0;
}

//测试函数
/*int main() {
    STACK *q=new STACK(3);
    char* s=new char[1];
    *q<<1;
    *q<<2;
    *q<<3;
    *s = '\0';
    cout << "初始化栈为：" << q->print(s) << endl;
    try {
        (*q)<<(4);
    }
    catch (const char* msg) {
        cout << msg << endl;
    }
    *s = '\0';
    cout << "插入元素4后栈为：" << q->print(s) << endl;
    try {
        (*q)<<(5);
    }
    catch (const char* msg) {
        cout << msg << endl;
    }
    cout << "当前栈中已有元素为：" << (int)(*q) << " 个" << endl;
    int e;
    (*q)>> e;
    cout << "将栈顶元素出栈得 " << e << endl;
    *s = '\0';
    cout << "将栈顶元素出栈后栈为：" << q->print(s) << endl;
    cout << "当前栈容量为 " << q->size() << endl;
    STACK newq(*q);
    *s = '\0';
    cout << "深拷贝的新栈为：" << newq.print(s) << endl;
    q->~STACK();
    newq.~STACK();
    getchar();
    return 0;
}*/
