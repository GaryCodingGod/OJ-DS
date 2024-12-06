#include <iostream>
#include <vector>

using namespace std;

template <typename T>
T sum(const vector<T> &v) {
    typedef typename vector<T>::const_iterator constIter;
    T sum = 0;
    for (constIter it = v.begin(); it != v.end(); it++) {
        sum += *it;
    }
    return sum;
}

int main() {
    
    vector<int> intVec = {10, 20, 30, 40, 50};
    cout << "Sum of intVec: " << sum(intVec) << endl;

    vector<double> doubleVec = {1.05, 2.15, 3.25, 4.35, 5.45};
    cout << "Sum of doubleVec: " << sum(doubleVec) << endl;

    vector<int> emptyVec;
    cout << "Sum of emptyVec: " << sum(emptyVec) << endl;

    vector<int> negativeVec = {-10, -20, -30, -40, -50};
    cout << "Sum of negativeVec: " << sum(negativeVec) << endl;

    return 0;
}
