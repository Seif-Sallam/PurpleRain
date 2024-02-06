#include "raylib.h"

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Purple Rain");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	// Remove exit by Esc
	SetExitKey(KEY_NULL);

	// Main game loop
	while (!WindowShouldClose())
	{

		BeginDrawing();
		{
			ClearBackground(Color{168, 168, 168, 255});
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}