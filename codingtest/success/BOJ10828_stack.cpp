/*
- stack 구현
*/ 

// #include <stack>
#include <iostream>
#include <string>
using namespace std;

int32_t N; 

class STACK 
{
public:
    void push(int32_t tmpint) {
        _arr[_top] = tmpint;
        _top += 1;
    }    
    int32_t pop() {
        if (!empty())
        {
            _top -= 1;
            return _arr[_top];
        }
        else 
            return -1;
    }
    int32_t size() {return _top;}
    int32_t empty() {return (_top==0) ? 1 : 0; }
    int32_t top() {
        if (!empty())
            return _arr[_top-1];
        else 
            return -1;
    }

public:
    int32_t _arr[10000];
    int32_t _top { 0 };
};

int main(int argc, const char** argv)
{
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    
    STACK stck; 

    
    int32_t tmpint; 
    // int8_t command[6];
    string command;

    cin >> N ;
    // scanf("%d",&N);
    for (int32_t ii = 0; ii < N; ++ii)    
    {
        // scanf("%s",&command);
        cin >> command;
        if (command == "push")
        {   
            cin >> tmpint;
            stck.push(tmpint);
        }
        else if (command == "pop")
        {
            cout << stck.pop() << endl;
        }
        else if (command == "size")
        {
            cout << stck.size() << endl;
        }
        else if (command == "empty")
        {
            cout << stck.empty() << endl;
        }
        else if (command == "top")
        {
            cout << stck.top() << endl;
        }
    }
}