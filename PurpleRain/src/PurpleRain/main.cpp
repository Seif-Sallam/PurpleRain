#include "raylib.h"
#include <string>

constexpr const Vector2 RAIN_DROP_SIZE = Vector2{5, 15};
constexpr const Color RAIN_DROP_COLOR = Color{128, 0, 128, 255};
constexpr const float GRAVITY = 0.01f;

struct RainDrop {
	// The Z component will be used even though we are in 2D
	Vector3 position;
	float speed; // in the Y direction
};

void InitRainDrop(RainDrop& rainDrop);
void UpdateRainDrop(RainDrop& rainDrop, float windSpeed, float deltaTime);
void DrawRainDrop(RainDrop& rainDrop);
float GetWindSpeed();

void DrawFPS(float dt);

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Purple Rain");

	RainDrop drops[1000] = {};
	for (auto& drop : drops)
		InitRainDrop(drop);

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	// Remove exit by Esc
	SetExitKey(KEY_NULL);

	float deltaTime = 1.0f;
	bool drawText = false;

	float windSpeed = 0.0f; // X Speed

	// Main game loop
	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime();

		if (IsKeyPressed(KEY_SPACE))
			drawText = !drawText;
		if (IsKeyPressed(KEY_D) || IsKeyDown(KEY_D))
			windSpeed += 0.01f;
		if (IsKeyPressed(KEY_A) || IsKeyDown(KEY_A))
			windSpeed -= 0.01f;

		for (auto& drop : drops)
			UpdateRainDrop(drop, windSpeed, deltaTime);

		BeginDrawing();
		{
			ClearBackground(BLACK);
			for (auto& drop : drops)
				DrawRainDrop(drop);
			if (drawText)
				DrawFPS(deltaTime);
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

float map(float value, float minV, float maxV, float otherMin, float otherMax)
{
	// Maps the value between other value range
	return ((value / (minV + maxV)) * otherMax) + otherMin;
}

void InitRainDrop(RainDrop& rainDrop)
{
	rainDrop.position.x = (float)GetRandomValue(3, GetRenderWidth() - 3);
	rainDrop.position.y = (float)GetRandomValue(-50, 10);

	static const int MAX_SPEED = 5;
	static const int MIN_SPEED = 0;
	static const int Z_MIN = 1;
	static const int Z_MAX = 11;

	rainDrop.position.z = (float)GetRandomValue(Z_MIN, Z_MAX);

	rainDrop.speed = map(rainDrop.position.z, Z_MIN, Z_MAX, MIN_SPEED, MAX_SPEED);
}

void UpdateRainDrop(RainDrop& rainDrop, float windSpeed, float deltaTime)
{
	rainDrop.speed += rainDrop.speed * GRAVITY;
	rainDrop.position.x += windSpeed;
	rainDrop.position.y += rainDrop.speed;

	// If we are out of bounds
	if (rainDrop.position.y >= GetRenderHeight())
	{
		// give it a random position
		InitRainDrop(rainDrop);
	}
}

void DrawRainDrop(RainDrop& drop)
{
	DrawRectangle((int)drop.position.x, (int)drop.position.y, (int)RAIN_DROP_SIZE.x, (int)RAIN_DROP_SIZE.y, RAIN_DROP_COLOR);
}

float GetWindSpeed()
{
	auto mousePosition = GetMousePosition();
	if(mousePosition.x < 0)
		mousePosition.x = 0;
	else if (mousePosition.x > GetRenderWidth())
		mousePosition.x = (float)GetRenderWidth();
	float middleOfScreen = GetRenderWidth() / 2.0f;

	auto delta = int(mousePosition.x - middleOfScreen) % 100; // Max speed in the X

	return (float) 5.0f * delta / 100;
}

void DrawFPS(float deltaTime)
{
	std::string latency = "Latency: " + std::to_string(deltaTime);
	std::string fps = "FPS: " + std::to_string(GetFPS());

	DrawText(latency.c_str(), 10, 0, 30, RAYWHITE);
	DrawText(fps.c_str(), 10, 40, 30, RAYWHITE);
}