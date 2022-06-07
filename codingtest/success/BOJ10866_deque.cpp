/*
- deque 구현
*/ 

#include <iostream>
#include <string>
using namespace std;

int32_t N; 

class DEQUE 
{
public:
    void push_front(int32_t tmpint) {
        _arr[_front] = tmpint;
        _front -= 1;
    }    
    void push_back(int32_t tmpint) {
        _arr[_back] = tmpint;
        _back += 1;
    }    
    int32_t pop_front() {
        if (!empty())
        {
            _front += 1;
            return _arr[_front];
        }
        else 
            return -1;
    } 
    int32_t pop_back() {
        if (!empty())
        {
            _back -= 1;
            return _arr[_back];
        }
        else 
            return -1;
    }
    int32_t size() {return _back - _front - 1;}
    int32_t empty() {return (size()==0) ? 1 : 0; }
    int32_t front() {
        if (!empty())
            return _arr[_front+1];
        else 
            return -1;
    }
    int32_t back() {
        if (!empty())
            return _arr[_back-1];
        else 
            return -1;
    }

public:
    int32_t _arr[20001];
    int32_t _front { 10000 };
    int32_t _back { 10001 };
};

int main(int argc, const char** argv)
{
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    
    DEQUE dq; 
    int32_t tmpint; 
    string command;

    cin >> N ;
    for (int32_t ii = 0; ii < N; ++ii)    
    {
        cin >> command;
        if (command == "push_front")
        {   
            cin >> tmpint;
            dq.push_front(tmpint);
        }
        else if (command == "push_back")
        {   
            cin >> tmpint;
            dq.push_back(tmpint);
        }
        else if (command == "pop_front")
        {   
            cout << dq.pop_front() << endl;
        }
        else if (command == "pop_back")
        {   
            cout << dq.pop_back() << endl;
        }
        else if (command == "size")
        {   
            cout << dq.size() << endl;
        }
        else if (command == "empty")
        {   
            cout << dq.empty() << endl;
        }
        else if (command == "front")
        {   
            cout << dq.front() << endl;
        }
        else if (command == "back")
        {   
            cout << dq.back() << endl;
        }
    }
}