// test.cpp
#include "iostream.h"
#include "string.h"

using namespace std;

int main(int argc, char* argv[])
{
    string* msg = new string("hello world");
    cout << *msg << endl;
    delete msg;
    return 0;
}
