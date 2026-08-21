#include <iostream>
using namespace std;

const int MAX_AGE = 100;

int main() {
    int age;
    cout << "Enter your age: ";
    cin >> age;

    string name;
    cout << "Enter your name: ";
    cin >> name;

    cout << "Hello, " << name << "! You are " << age << " years old." << endl;
    return 0;
}