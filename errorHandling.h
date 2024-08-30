#include <iostream>
using namespace std;

class customError
{
private:
    string message;

public:
    customError(string message)
    {
        this->message = message;
    }
    void what()
    {
        textRed(message);
        ScreenWaitMilliSec(1500);
    }
};
