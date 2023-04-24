#ifndef _TETRIS_HPP_
#define _TETRIS_HPP_

#include <utility>
#include <queue>

#include "util.hpp"

using namespace std;

class Tetris {
public:
    queue<int> nextPos(DiredCube cube, Region region);

    #if SHOW
        void renderRegion(Region region);
        void emulateDown(Region region, vector<Position> positions);
    #endif
};

#endif