#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "QUEUE.h"
using namespace std;

extern const char* TestQUEUE(int& s);

int main() {
    int s;
    const char* e = TestQUEUE(s);
    cout << s << endl;
    cout << e << endl;
    getchar();
    return 0;
}





