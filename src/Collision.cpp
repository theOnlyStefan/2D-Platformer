#include "Collision.h"

bool collision::checkCollision(collision& c)
{
	//care offset
	x += offX, y += offY;

	bool horizontalOverlap = pow((c.x + c.a - (x + a)), 2) < pow((a + c.a), 2);
	bool verticalOverlap = pow((c.y + c.b - (y + b)), 2) < pow((b + c.b), 2);

	x -= offX, y -= offY;

	if (horizontalOverlap && verticalOverlap) {
		return true;
	}
	else {
		return false;
	}
}

void collision::resolveCollision1d(collision& h2, bool xAxis)
{
	//move center from 0,0 to real center
	x += a + offX, y += b + offY;
	h2.x += h2.a + h2.offX; h2.y += h2.b + h2.offY;

	if (xAxis) {
		x = resolve1d(x, h2.x, a, h2.a);
		//drawPush((int)h2.x, (int)h2.y, (int)h2.a, (int)h2.b, true, x < h2.x);
		//Drawing pushing direction
		touchingWall = true;

		//float leftK = h2.x - x - a - h2.a;
		//float rightK = x - h2.x - a - h2.a;
	}
	else {
		y = resolve1d(y, h2.y, b, h2.b);
		//drawPush((int)h2.x, (int)h2.y, (int)h2.a, (int)h2.b, false, y < h2.y);

		if (y > h2.y) touchingCeiling = true;
		if (y < h2.y) grounded = true;
	}
	//adjust x and y back
	x -= (a + offX), y -= (b + offY);
	h2.x -= (h2.a + h2.offX), h2.y -= (h2.b + h2.offY);
}

void collision::drawPush(int x2, int y2, int a2, int b2, bool xAxis, bool firstIsLowerValue)
{
	int squareSize = 3;

	if (xAxis) {
		DrawLine(x2, y2, x2 + a2 / 2, y2, RED);
		int loc = firstIsLowerValue ? x2 - squareSize : x2 + a2 / 2 + squareSize;
		DrawCircle(loc, y2, (float)squareSize, PURPLE);
	}
	else {
		DrawLine(x2, y2, x2, y2 + b2 / 2, YELLOW);
		int loc = firstIsLowerValue ? y2 - squareSize : y2 + b2 / 2 + squareSize;
		DrawCircle(x2, loc, (float)squareSize, GREEN);
	}
}


