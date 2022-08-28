#include "raylib.h"

struct Ball {
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw() {
		DrawCircle((int)x,(int)y, radius, WHITE);
	}
};

struct Paddle {
	float x, y;
	float speed;
	float width;
	float height;

	Rectangle GetRect() {
		return Rectangle{ x - width / 2,y - height / 2, width, height};
	}

	void Draw() {
		DrawRectangleRec(GetRect(), WHITE);
	}
};
int main() {
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 200;
	ball.speedY = 200;

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2 - 50;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2 - 50;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;
	
	const char* winnerText = nullptr;

	while (!WindowShouldClose()) {
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();
		
		// ball bouncing of the edges of the screen
		if (ball.y < 0) {
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight()) {
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		// ai
		if (ball.y < leftPaddle.y) {
			if (leftPaddle.y-(leftPaddle.height / 2) > 0) {
				leftPaddle.y -= leftPaddle.speed * GetFrameTime();
			}
		}
		if (ball.y > leftPaddle.y) {
			if (leftPaddle.y+(leftPaddle.height/2) < GetScreenHeight()) {
				leftPaddle.y += leftPaddle.speed * GetFrameTime();
			}
		}

		// player movement
		if (IsKeyDown(KEY_UP)) {
			if (rightPaddle.y-(rightPaddle.height / 2) > 0) {
				rightPaddle.y -= rightPaddle.speed * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_DOWN)) {
			if (rightPaddle.y+(rightPaddle.height / 2) < GetScreenHeight()) {
				rightPaddle.y += rightPaddle.speed * GetFrameTime();
			}
		}

		// collions
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect())) {
			if (ball.speedX < 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect())) {
			if (ball.speedX > 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}

		// win state
		if (ball.x < 0) {
			winnerText = "Right player wins!";
		}
		if (ball.x > GetScreenWidth()) {
			winnerText = "Left player wins!";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE)) {
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			winnerText = nullptr;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		ball.Draw();
		leftPaddle.Draw();
		rightPaddle.Draw();

		if (winnerText) {
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth()/ 2 - (textWidth/2), GetScreenHeight() / 2 - 30, 60, YELLOW);
			
			DrawText("click SPACE to restart", GetScreenWidth() / 2 - (MeasureText("click SPACE to restart", 30)/2), GetScreenHeight() / 2 + 100, 30, WHITE);
		}

		DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}