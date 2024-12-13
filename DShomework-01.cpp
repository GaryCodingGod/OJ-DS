// Write a program that consists of three classes, A, B, and C, such that B is a subclass of A and C is a subclass of B.
// Each class should define a member variable named ”x” (that is,  each has itsown variable named x).  
//Describe a way for a member function in C to access and set A’s version of x toa given value, without changing B or C’s version.
#include <iostream>

using namespace std;

class A {
    public:
        int x;
        A() {}
        A(int a): x(a) {}
        ~A() {}
};

class B: public A {  
    public:
        int x;
        B() {}
        B(int b): x(b) {}
        ~B() {}
};

class C: public B {
    public:
        int x;
        C() {}
        C(int c): x(c) {}

        // 修改 A 類別的成員函數
        void set_A_x(int val) {
            A::x = val;
        }
        ~C() {}
};

int main() {

    return 0;
}
