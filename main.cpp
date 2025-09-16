#include "raylib.h"
#include "AStarSolver.h"

AStarSolver aStarSolver;

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 850;

    InitWindow(screenWidth, screenHeight, "AStarSandbox");

    SetTargetFPS(60);   
    aStarSolver.InitGrid(16, 16);
    bool a = aStarSolver.SolveAStar();     
    cout << "Solved: " << a << endl;      

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            aStarSolver.DrawGrid();

        EndDrawing();
    }
    aStarSolver.Delete();

    CloseWindow(); 

    return 0;
}