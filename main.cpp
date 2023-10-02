#include "raylib.h"

int main() {
	InitWindow(800, 600, "Window");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		
		BeginDrawing();
			ClearBackground(BLACK);
			DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}