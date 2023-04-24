#include <iostream>
#include <unistd.h>
#include <cmath>
#include <math.h>

#include "tetris.hpp"

using namespace std;
/* implement this function */
/*
而整個 queue 代表你在此回合的所有行為，
此刻你移動，就會將 Left or Right 存進 queue 中；
此刻你移動，就會將 Clockwise or CounterClockwise 存進 queue 中；
舉例來說：
[None, Clockwise, Left, Left]，
代表： 不做事 -> 順時鐘轉 -> 左移 -> 左移

cube有Cube cube; Direction dir; int x; 三個參數，
region 為二維陣列[][]
*/

queue<int> Tetris::nextPos(DiredCube cube, Region region)
{
    queue<int> q;
    srand(time(NULL));
    for (int i = 0; i < 50; i++)
    {
        int y = rand() % 4;
        if(y == 0)
            q.push(Left);
        else if(y == 1)
            q.push(Right);
        else if(y == 2)
            q.push(Clockwise);
        else
            q.push(CounterClockwise);
    }

    #if DEBUG
    for (int i = 0; i < 50; i++) {
        q.push(rand() % 5);
    }
    #endif

    return q;
}

#if SHOW
/**
 * Don't change those codes below
 * It's just for show tetris
 **/
void Tetris::renderRegion(Region region)
{
    for (size_t i = 0; i < (region.size() / 2) + 6; i++)
        cout << '_';
    
    cout << '\n';
    for (size_t i = 0; i < region.size(); i++) {
        cout << '|';
        for (size_t j = 0; j < region[i].size(); j++) {
            if (region[i][j] == 0) {
                cout << ' ';
            } else {
                cout << '@';
            }
        }
        cout << "|\n";
    }

    for (size_t i = 0; i < (region.size() / 2) + 6; i++)
        cout << '_';
    
    cout << '\n';
}

void Tetris::emulateDown(Region region, vector<Position> positions)
{
	for (int i = 0; i < positions.size(); i++) {
		region[ positions[i].second ][ positions[i].first ] = 1;
	}
    
	clear();
	renderRegion(region);
	usleep(SPEED);
}
#endif