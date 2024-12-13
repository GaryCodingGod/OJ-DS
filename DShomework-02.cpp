//The roots of the quadratic equationax2+bx+c= 0, a= 0 are given by the following formula: (一元二次方程的求根公式)
//n this formula, the termb2−4acis called thediscriminant.  If b^2−4ac = 0, the equation has a single(repeated) root.
//If b^2−4ac >0, the equation has two real roots.  If b^2−4ac <0, the equation has twocomplex roots.  
//Design and implement the class quadraticEqso that an object of this class can store thecoefficients of a quadratic equation. 
//Overload the operators + and – to add and subtract, respectively,the corresponding coefficients of two quadratic equations.  
//Overload the relational operators == and !=to determine if two quadratic equations are the same. 
// Add appropriate constructors to initialize objects.Overload the stream extraction and insertion operator for easy input and output. 
// Also, include functionmembers to determine and output the type and the roots of the equation.  Write a program to test yourclass.
#include <iostream>
#include <cmath>
using namespace std;

class quadraticEq {
    private:
        int a;
        int b;
        int c;
        double type;
        string rootType;
    public:
        quadraticEq() {}
        quadraticEq(int x, int y, int z): a(x), b(y), c(z) {}

        friend istream& operator>>(istream &in, quadraticEq &eq);
        friend ostream& operator<<(ostream &cout, quadraticEq &eq);
        
        void judgeRootType() {
            type = (b * b) - (4 * a * c);

            if (type == 0) rootType = "Single repeated root";
            else if (type > 0) rootType = "Two real roots";
            else rootType = "Two complex roots";

            cout << "The root type: " << rootType << endl;
        }

        void countRoot() {
            if (type >= 0) {
                // 計算根
                double sqrtType = sqrt(type);
                double pos = (-b + sqrtType) / (2 * a);
                double neg = (-b - sqrtType) / (2 * a);

                if (type == 0) {
                    cout << "Root: " << pos << endl;
                } else {
                    cout << "Root 1: " << pos << ", Root 2: " << neg << endl;
                }
            } else {
                // 計算複數根
                double realPart = -b / (2.0 * a);
                double imagPart = sqrt(-type) / (2.0 * a);
                cout << "Complex roots: " << realPart << " + " << imagPart << "i and "
                     << realPart << " - " << imagPart << "i" << endl;
            }
        }
        
        quadraticEq operator+(quadraticEq &eq) {
            quadraticEq temp;
            temp.a = this->a + eq.a;
            temp.b = this->b + eq.b;
            temp.c = this->c + eq.c;
            
            return temp;
        }
        quadraticEq operator-(quadraticEq &eq) {
            quadraticEq temp;
            temp.a = this->a - eq.a;
            temp.b = this->b - eq.b;
            temp.c = this->c - eq.c;
            
            return temp;
        }

        bool operator==(quadraticEq &eq) {
            bool result = this->a == eq.a && this->b == eq.b && this->c == eq.c;
            return result;
        }

        bool operator!=(quadraticEq &eq) {
            
            return !(*this == eq);
        }

        ~quadraticEq() {}
};

istream& operator>>(istream &in, quadraticEq &eq) {
    in >> eq.a >> eq.b >> eq.c;
    return in;
}

ostream& operator<<(ostream &cout, quadraticEq &eq) {
    if (eq.a == 1 || eq.a == -1) cout << ((eq.a == 1) ? "x^2" : "-x^2");
    else cout << eq.a << "x^2";

    if (eq.b > 0 && eq.b != 1) cout << " + " << eq.b << "x";
    else if (eq.b == 1) cout << " + x";
    else cout << " - " << abs(eq.b) << "x";

    if (eq.c > 0) cout << " + " << eq.c << " = 0" << endl;
    else cout << " - " << abs(eq.c) <<  " = 0" << endl;

    return cout;
}


int main() {
    

    return 0;
}