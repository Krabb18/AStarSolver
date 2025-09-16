#ifndef ASTARSOLVER_H
#define ASTARSOLVER_H

#include "raylib.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <math.h>

using namespace std;

struct sNode
{
    bool isObstacle = false;
    int localGoal;
    int globalGoal;
    int x = 0;
    int y = 0;
    bool visited = false;
    
    vector<sNode*> vecNeighbors;
    sNode* parent;
};

class AStarSolver
{
    private:
    int w = 0;
    int h = 0;

    public:
        sNode* nodes;
        sNode* nodeStart;
        sNode* nodeEnd;

        //Drawing functions
        void DrawGrid();

        void InitGrid(int width, int height);
        bool SolveAStar();
        void Delete();
};

#endif
