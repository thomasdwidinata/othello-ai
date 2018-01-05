
// unnamed-library , a `libThom` Derivative

#ifndef unnamedlibrary
#define unnamedlibrary
#endif

#pragma once

#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

// Defining Terminal Colour Modifiers
#define RESETCOLOUR   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

// Define system function based on where the compiler runs from
#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
    #include <conio.h>
    void system_pause()
    {
        system("pause");
    }
    void system_clear_screen()
    {
        system("cls");
    }
    #ifdef _WIN64
        //define something for Windows (64-bit only)
    #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
        #error "Unsupported: iOS Simulator. This library is not indended to run on this OS."
    #elif TARGET_OS_IPHONE
        #error "Unsupported: iOS. This library is not indended to run on this OS."
    #elif TARGET_OS_MAC
        void system_pause()
        {
            printf("Press any key to continue...");
            getchar();
        }
        void system_clear_screen()
        {
            system("clear");
        }
    #else
        #error "Unsupported: Unknown Apple Product. This library is not indended to run on this OS."
    #endif
#elif __linux__
    void system_pause()
    {
        printf("Press enter to continue...");
        std::cin.get();
    }
    void system_clear_screen()
    {
        system("clear");
    }
#elif __unix__ // all unices not caught above
    #error "Unsupported: UNIX. This library is not indended to run on this OS."
#elif defined(_POSIX_VERSION)
    #error "Unsupported: POSIX Compatible System. This library is not indended to run on this OS."
#else
    #error "Unsupported an unknown system. This library is not indended to run on this OS."
#endif


int scanNumber() // Input sanitiser to make sure that user inputs only numbers, and clears the input stream to avoid infinite loop, and returns the integer value
{
    int choice;
    std::cin >> choice;
    while(std::cin.fail())
    {
        std::cin.clear(); //This corrects the stream.
        std::cin.ignore(); //This skips the left over stream data.
        printf("Invalid response, please input numbers only : ");
        std::cin >> choice;
    }
    return choice;
}

bool kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return true;
    }

    return false;
}

void initRandomiser()
{
  srand(time(NULL));
}

int randomise(int min, int max)
{
  return (rand() % (max + 1 - min)) + min;
}
