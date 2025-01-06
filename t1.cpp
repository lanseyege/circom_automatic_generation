#include <iostream>
#include <cstring>

using namespace std;



int func1(char **equations, int n) {
    
}

int main() {
    cout << "input the amount of equations: " << endl;
    int n, i = 0, len = 100; 
    char a;
    cin >> n; 
    cout << "input equations: " << endl;
    cin.get(a);
    char equations[n][len] ;
    while ( i < n) {
        cin.getline(equations[i], len, '\n') ;
        i ++;
    }
    for (i = 0; i < n; i ++) {
        cout << i << " : " << equations[i] << endl;
        cout << strlen(equations[i]) << endl;
    }
}
