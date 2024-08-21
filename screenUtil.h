/*
NOTE: THE FEATURES OF PRINTING THE ASCII ART FROM STRING AND PRINTING THE STRING IN A BOX
      WONT WORK FINE IF THE STRING BECOMES OUT OF BOUNDS, THAT IS, IF THE CONSOLE WINDOW
      WIDTH IS TOO SMALL TO DISPLAY IT, TRY REDUCING THE LENGTH OF THE STRING IF ENCOUNTER
      SUCH A PROBLEM
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <unordered_map>
using namespace std;

// ANSI Escape Codes:
// reset
#define RESET "\033[0m"
// text colors
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
// background colors
#define BLACK_BG "\033[40m"
#define RED_BG "\033[41m"
#define GREEN_BG "\033[42m"
#define YELLOW_BG "\033[43m"
#define BLUE_BG "\033[44m"
#define MAGENTA_BG "\033[45m"
#define CYAN_BG "\033[46m"
#define WHITE_BG "\033[47m"
// text styles
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define REVERSE "\033[7m"
#define HIDDEN "\033[8m"
// to clear screen
#define CLEAR_SCR "\033[2J\033[1;1H"

// storing predefined ascii characters
unordered_map<char, vector<string>> asciimap = {
    {'A', {"    ___ ", "   /   |", "  / /| |", " / ___ |", "/_/  |_|"}},
    {'B', {"    ____ ", "   / __ )", "  / __  |", " / /_/ / ", "/_____/  "}},
    {'C', {"   ______", "  / ____/", " / /     ", "/ /___   ", "\\____/   "}},
    {'D', {"    ____ ", "   / __ \\", "  / / / /", " / /_/ / ", "/_____/  "}},
    {'E', {"    ______", "   / ____/", "  / __/   ", " / /___   ", "/_____/   "}},
    {'F', {"    ______","   / ____/","  / /_    "," / __/    ","/_/       ",}},
    {'G', {"   ______", "  / ____/", " / / __  ", "/ /_/ /  ", "\\____/   "}},
    {'H', {"    __  __", "   / / / /", "  / /_/ / ", " / __  /  ", "/_/ /_/   "}},
    {'I', {"    ____", "   /  _/", "   / /  ", " _/ /   ", "/___/   "}},
    {'J', {"      _  ", "     | | ", "     | | ", " ____| | ", "|______| "}},
    {'K', {"    __ __", "   / //_/", "  / ,<   ", " / /| |  ", "/_/ |_|  "}},
    {'L', {"    __ ", "   / / ", "  / /  ", " / /___", "/_____/"}},
    {'M', {"    __  ___", "   /  |/  /", "  / /|_/ / ", " / /  / /  ", "/_/  /_/   "}},
    {'N', {"    _   __", "   / | / /", "  /  |/ / ", " / /|  /  ", "/_/ |_/   "}},
    {'O', {"   ____ ", "  / __ \\", " / / / /", "/ /_/ / ", "\\____/  "}},
    {'P', {"    ____ ", "   / __ \\", "  / /_/ /", " / ____/ ", "/_/      "}},
    {'Q', {"   ____ ", "  / __ \\", " / / / /", "/ /_/ / ", "\\___\\_\\ "}},
    {'R', {"    ____ ", "   / __ \\", "  / /_/ /", " / _, _/ ", "/_/ |_|  "}},
    {'S', {"   _____", "  / ___/", "  \\__ \\ ", " ___/ / ", "/____/  "}},
    {'T', {"  ______", " /_  __/", "  / /   ", " / /    ", "/_/     "}},
    {'U', {"   __  __", "  / / / /", " / / / / ", "/ /_/ /  ", "\\____/   "}},
    {'V', {" _    __", "| |  / /", "| | / / ", "| |/ /  ", "|___/   "}},
    {'W', {" _       __", "| |     / /", "| | /| / / ", "| |/ |/ /  ", "|__/|__/   "}},
    {'X', {"   _  __", "  | |/ /", "  |   / ", " /   |  ", "/_/|_|  "}},
    {'Y', {"__  __", "\\ \\/ /", " \\  / ", " / /  ", "/_/   "}},
    {'Z', {" _____", "/__  /", "  / / ", " / /__", "/____/"}},
};

// CLEARING SCREEN
void ScreenClear()
{
    std::cout << CLEAR_SCR;
}

// WAITING IN CONSOLE
void ScreenWaitSec(int x)
{
    this_thread::sleep_for(chrono::seconds(x));
}
void ScreenWaitMilliSec(int x)
{
    this_thread::sleep_for(chrono::milliseconds(x));
}

// FONT STYLES
void textBold(string s, bool newline = true)
{
    cout << BOLD << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textDim(string s, bool newline = true)
{
    cout << DIM << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textItalic(string s, bool newline = true)
{
    cout << ITALIC << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textUnderline(string s, bool newline = true)
{
    cout << UNDERLINE << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textBlink(string s, bool newline = true)
{
    cout << BLINK << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textReverse(string s, bool newline = true)
{
    cout << REVERSE << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textHidden(string s, bool newline = true)
{
    cout << HIDDEN << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

// TEXT COLORS
void textBlack(string s, bool newline = true)
{
    cout << BLACK << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textRed(string s, bool newline = true)
{
    cout << RED << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textGreen(string s, bool newline = true)
{
    cout << GREEN << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textYellow(string s, bool newline = true)
{
    cout << YELLOW << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textBlue(string s, bool newline = true)
{
    cout << BLUE << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textMagenta(string s, bool newline = true)
{
    cout << MAGENTA << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textCyan(string s, bool newline = true)
{
    cout << CYAN << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textWhite(string s, bool newline = true)
{
    cout << WHITE << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

// BG COLORS
void textBgBlack(string s, bool newline = true)
{
    cout << BLACK_BG << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textBgRed(string s, bool newline = true)
{
    cout << RED_BG << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textBgGreen(string s, bool newline = true)
{
    cout << GREEN_BG << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textBgYellow(string s, bool newline = true)
{
    cout << YELLOW_BG << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textBgBlue(string s, bool newline = true)
{
    cout << BLUE_BG << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textBgMagenta(string s, bool newline = true)
{
    cout << MAGENTA_BG << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textBgCyan(string s, bool newline = true)
{
    cout << CYAN_BG << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

void textBgWhite(string s, bool newline = true)
{
    cout << WHITE_BG << s << RESET;
    if (newline)
    {
        cout << endl;
    }
}

// ANIMATING TEXT
void textAnimate(string text, int delay)
{
    for (char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << endl;
}

// DRAWING ASCII ART FROM TEXT
void textAscii(string s)
{
    vector<string> line = {"", "", "", "", ""};

    for (char i : s)
    {
        vector<string> v = asciimap[i];
        for (int k = 0; k < 5; k++)
        {
            line[k] += v[k];
        }
    }

    for (int i = 0; i < 5; i++)
    {
        cout << line[i] << endl;
    }
}

// PRINTING TEXT IN A BOX
// spacing refers to how many tabs of space to leave from left of screen
void textInBox(string s, int spacing = 0)
{
    int length = 2;
    for (auto i : s)
    {
        length++;
    }

    for (int i = 0; i < spacing; i++)
    {
        cout << "\t";
    }
    cout << "\u2554";
    for (int i = 0; i < length; i++)
    {
        cout << "\u2550";
    }
    cout << "\u2557" << endl;

    for (int i = 0; i < spacing; i++)
    {
        cout << "\t";
    }
    cout << "\u2551 " << s << " \u2551" << endl;

    for (int i = 0; i < spacing; i++)
    {
        cout << "\t";
    }
    cout << "\u255A";
    for (int i = 0; i < length; i++)
    {
        cout << "\u2550";
    }
    cout << "\u255D" << endl;
}
