#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector <int> vec;
    cout << vec.empty() << endl;
    vec.push_back(1);
    vec.push_back(2);
    cout << vec.back() << endl;
    cout << vec.empty() << endl;
}
