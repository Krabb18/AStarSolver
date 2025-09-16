#include "AStarSolver.h"

void AStarSolver::InitGrid(int width, int height)
{
    w = width;
    h = height;

    nodes = new sNode[width * height];
    for(int x = 0; x<width; x++)
    {
        for(int y = 0; y<height; y++)
        {
            nodes[y * width + x].x = x;
			nodes[y * width + x].y = y;
            nodes[y * width + x].isObstacle = false;
            nodes[y * width + x].localGoal = INFINITY;
            nodes[y * width + x].globalGoal = INFINITY;
            nodes[y * width + x].parent = nullptr;
			nodes[y * width + x].visited = false;

            //Hier werden die neighbors initialisiert
            if(y > 0)
            {
                nodes[y*width + x].vecNeighbors.push_back(&nodes[(y - 1) * width + (x + 0)]);
            }
            
            if(y < height -1)
            {
                nodes[y*width + x].vecNeighbors.push_back(&nodes[(y + 1) * width + (x + 0)]);
            }

            if(x > 0)
            {
                nodes[y*width + x].vecNeighbors.push_back(&nodes[(y + 0) * width + (x -1)]);
            }

            if(x < width -1)
            {
                nodes[y*width + x].vecNeighbors.push_back(&nodes[(y + 0) * width + (x +1)]);
            }

            //Nur zum testen
            nodeStart = &nodes[(height / 2) * width + 1];
		    nodeEnd = &nodes[(height / 2) * width + width-2];
        }
    }
}


bool AStarSolver::SolveAStar()
{
    for(int x = 0; x<w; x++)
    {
        for(int y = 0; y<h; y++)
        {
            nodes[y * w + x].localGoal = INFINITY;
            nodes[y * w + x].globalGoal = INFINITY;
            nodes[y * w + x].parent = nullptr;
			nodes[y * w + x].visited = false;

            if(y == 8 && x == 8){nodes[y * w + x].isObstacle = true;}
        }
    }

    auto distance = [](sNode* a, sNode* b) // For convenience
		{
			return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
		};

		auto heuristic = [distance](sNode* a, sNode* b) // So we can experiment with heuristic
		{
			return distance(a, b);
		};

    sNode* currentNode = nodeStart;
    nodeStart->localGoal = 0.0f;
	nodeStart->globalGoal = heuristic(nodeStart, nodeEnd);

    list<sNode*> nodesToTest;
    nodesToTest.push_back(nodeStart);

    while(!nodesToTest.empty() && currentNode != nodeEnd)
    {
        nodesToTest.sort([](const sNode* lhs, const sNode* rhs){ return lhs->globalGoal < rhs->globalGoal; } );

        while (!nodesToTest.empty() && nodesToTest.front()->visited)
        {
            nodesToTest.pop_front();
        }
        
        if(nodesToTest.empty()) break;
        currentNode = nodesToTest.front();
		currentNode->visited = true; 

        for(auto &nei : currentNode->vecNeighbors)
        {
            if(!nei->visited && !nei->isObstacle){nodesToTest.push_back(nei);}
            if(currentNode->localGoal + distance(currentNode, nei) < nei->localGoal)
            {
                nei->parent = currentNode;
                nei->localGoal = currentNode->localGoal + distance(currentNode, nei);
                nei->globalGoal = nei->localGoal + heuristic(nei, nodeEnd);
            }

            
        }
    }

    return true;
}

void AStarSolver::Delete()
{
    delete nodes;
}

void AStarSolver::DrawGrid()
{
    SolveAStar();
    for(int x = 0; x<w; x++)
    {
        for(int y = 0; y<h; y++)
        {
            Color col = RED;
            if(nodes[y * w + x].isObstacle){col = GRAY;}

            if(CheckCollisionRecs((Rectangle){nodes[y * w + x].x * 25, nodes[y * w + x].y * 25, 25, 25}, (Rectangle){GetMouseX(), GetMouseY(), 5, 5}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                nodes[y * w + x].isObstacle = !nodes[y * w + x].isObstacle;
            }

            DrawRectangle(nodes[y * w + x].x * 25, nodes[y * w + x].y * 25, 20, 20, col);
        }
    }

    //Draw Path
    if(nodeEnd != nullptr)
    {
        sNode* p = nodeEnd;
        while (p->parent != nullptr)
        {
           DrawLine(p->x * 25 + 10, p->y * 25 + 10,
            p->parent->x * 25 + 10, p->parent->y * 25 + 10, YELLOW);

            p = p->parent;
            cout << "node end ist nichtmake nullpttr" << endl;
        }
        cout << "node end ist nichtmake nullpttr" << endl;
    }
    else
    {
        cout << "node end ist nullpttr" << endl;
    }
}
