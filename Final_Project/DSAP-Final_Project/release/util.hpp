#ifndef _TYPES_HPP_
#define _TYPES_HPP_

#include <vector>
#include <queue>
#include <utility>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#define SCORE_UNIT 10
#define HEIGHT 40
#define WIDTH 25
#define SPEED 10000

#ifndef SHOW
    /* 如果要看降落畫面就設 1，否則 0 */
    #define SHOW 1
#endif

/* 如果要產生固定的方塊就設 1，否則 0 */
#define DEBUG 1

/* For rotation and translation */
#define None 0
#define Clockwise 1
#define CounterClockwise 2
#define Left 3
#define Right 4

enum Cube {
    Icube,
    Jcube,
    Lcube,
    Qcube,
    Scube,
    Tcube,
    Zcube,
    CUBE_NUM
};

enum Direction {
    East,
    North,
    West,
    South,
    DIRECTION_NUM
};

typedef struct _DiredCube {
    Cube cube;
    Direction dir;
    int x;
} DiredCube;

using Region = std::vector< std::vector<int> >;
using Position = std::pair<int, int>;
using Cubes = std::queue<DiredCube>;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
inline void clear()
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(hOut, coord);
}
#else
inline void clear()
{
    system("clear");
}
#endif /* OS version check */

#endif
