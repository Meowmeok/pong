#include <iostream>
#include <raylib.h>
#define screenHeight 300
#define screenWidth 500
#define sideBarHeight 70
#define sideBarWidth 5
#define speedOfSizeBar 2.5
#define speedOfBallHeightWhenStart -0.8
#define speedOfBallWidthWhenStart 2

float speedOfBallWidth = speedOfBallWidthWhenStart;
float speedOfBallHeight = speedOfBallHeightWhenStart;

struct Rec
{
	Vector2 position;
	Vector2 size;
};

struct Cir
{
	Vector2 position;
	float radius;	
};

bool checkLose(Cir &ball);
void keepSideBar(Rec &rec);
void changePositionOfSideBar1(Rec &sideBar);
void changePositionOfSideBar2(Rec &sideBar);
void initCir(Cir &cir, Vector2 position, float radius);
void initRec(Rec &rec, Vector2 position, Vector2 size);
void changePositionOfBall(Cir &ball, Rec sideBar1, Rec sideBar2, bool &firstMove);

int main()
{
	Cir ball;
	Rec sideBar1;
	Rec sideBar2;
	bool firstMove = true;
	initCir(ball, {screenWidth/2, screenHeight/2}, 7);
	initRec(sideBar1, {0, (screenHeight - sideBarHeight) / 2}, {sideBarWidth, sideBarHeight});
	initRec(sideBar2, {screenWidth-sideBarWidth, (screenHeight - sideBarHeight) / 2}, {sideBarWidth, sideBarHeight});
	InitWindow(screenWidth, screenHeight, "Pong");
	SetTargetFPS(100);
	while(WindowShouldClose() == false)
	{
		changePositionOfSideBar1(sideBar1);
		keepSideBar(sideBar1);
		changePositionOfSideBar2(sideBar2);
		keepSideBar(sideBar2);
		changePositionOfBall(ball, sideBar1, sideBar2, firstMove);
		if(checkLose(ball))
		{
			while(WindowShouldClose() == false)
			{
				BeginDrawing();
				ClearBackground(BLACK);
				DrawText("GAME IS END.", 80, 120, 50, WHITE);
				EndDrawing();
			}
			break;
		}
		BeginDrawing();
		ClearBackground(BLACK);
		//draw line
		DrawRectangle(screenWidth/2, 0, 1, screenHeight, WHITE);
		//draw circle
		DrawCircleLines(screenWidth/2, screenHeight/2, 30, WHITE);
		//draw ball	
		DrawCircleV(ball.position, ball.radius, WHITE);
		DrawRectangleV(sideBar1.position, sideBar1.size, WHITE);
		DrawRectangleV(sideBar2.position, sideBar2.size, WHITE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

void initRec(Rec &rec, Vector2 position, Vector2 size)
{
	rec.position = position;
	rec.size = size;
}

void initCir(Cir &cir, Vector2 position, float radius)
{
	cir.position = position;
	cir.radius = radius;
}

void changePositionOfBall(Cir &ball, Rec sideBar1, Rec sideBar2, bool &firstMove)
{
	Rectangle rec1{sideBar1.position.x, sideBar1.position.y, sideBar1.size.x, sideBar1.size.y};
	Rectangle rec2{sideBar2.position.x, sideBar2.position.y, sideBar2.size.x, sideBar2.size.y};
	if(firstMove == true && !CheckCollisionCircleRec(ball.position, ball.radius, rec1) && !CheckCollisionCircleRec(ball.position, ball.radius, rec2))
	{
		ball.position.x += speedOfBallWidthWhenStart;
		ball.position.y += speedOfBallHeightWhenStart;
	}
	else
	{
		if(speedOfBallHeight == 0)
		{
			speedOfBallHeight += 0.8;
		}
		else if(ball.position.y <= ball.radius)
		{
			speedOfBallHeight = (-1)*speedOfBallHeight;
			ball.position.x += speedOfBallWidth;
			ball.position.y += speedOfBallHeight;
		}
		else if(ball.position.y >= screenHeight-ball.radius)
		{
			speedOfBallHeight = (-1)*speedOfBallHeight;
			ball.position.x += speedOfBallWidth;
			ball.position.y += speedOfBallHeight;
		}
		else
		{
			if(CheckCollisionCircleRec(ball.position, ball.radius, rec1))
			{
				firstMove = false;
				speedOfBallWidth = (-1)*speedOfBallWidth;
				ball.position.x += speedOfBallWidth + 1;
				ball.position.y += speedOfBallHeight;
			}
			else if(CheckCollisionCircleRec(ball.position, ball.radius, rec2))
			{
				firstMove = false;
				speedOfBallWidth = (-1)*speedOfBallWidth;
				ball.position.x += speedOfBallWidth + 1;
				ball.position.y += speedOfBallHeight;
			}
			else
			{
				ball.position.x += speedOfBallWidth;
				ball.position.y += speedOfBallHeight;
			}
		}
	}
}

bool checkLose(Cir &ball)
{
	if(ball.position.x <= ball.radius)
		return true;
	else if(ball.position.x >= screenWidth-ball.radius)
		return true;
	return false;
}

void changePositionOfSideBar1(Rec &sideBar)
{
	if(IsKeyDown(87) || IsKeyDown(119))
	{
		sideBar.position.y -= speedOfSizeBar;
	}
	else if(IsKeyDown(83) || IsKeyDown(115))
	{
		sideBar.position.y += speedOfSizeBar;
	}
}

void changePositionOfSideBar2(Rec &sideBar)
{
	if(IsKeyDown(KEY_UP))
	{
		sideBar.position.y -= speedOfSizeBar;
	}
	else if(IsKeyDown(KEY_DOWN))
	{
		sideBar.position.y += speedOfSizeBar;
	}	
}

void keepSideBar(Rec &rec)
{
	if(rec.position.y <= 0)
	{
		rec.position.y = 0;
	}
	else if((rec.position.y + rec.size.y) >= screenHeight)
	{
		rec.position.y = screenHeight - rec.size.y;
	}
}