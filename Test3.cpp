#include "TXLib.h"
#include <cmath>
#include <iostream>

struct Ball  {

	double  x = 0,
			y = 0,
			r = 0,
			Vx = 0,
			Vy = 0,
			red = 0,
			green = 0,
			blue = 0;

};
struct Board {

	double Y1_position = 550;
	double Y2_position = 600;
	double middle_X_position = 400;

};

void Collision_of_Balls(Ball& ball1, Ball& ball2) {

	double k = (ball2.y - ball1.y) / (ball2.x - ball1.x);

	double sin = k / (sqrt(pow(k, 2) + 1));
	double cos = 1 / (sqrt(pow(k, 2) + 1));

	// зададим через матрицу перехода свз€ть координат в разных —ќ

	double V_trans_before_hitting_1_ball = cos * ball1.Vx + sin * ball1.Vy;
	double V_normal_before_hitting_1_ball = (-1) * sin * ball1.Vx + cos * ball1.Vy;

	double V_trans_before_hitting_2_ball = cos * ball2.Vx + sin * ball2.Vy;
	double V_normal_before_hitting_2_ball = (-1) * sin * ball2.Vx + cos * ball2.Vy;

	// выразил скорости в новой —  , теперь помен€ем тангенциальные составл€ющие

	double tmp = V_trans_before_hitting_2_ball;

	V_trans_before_hitting_2_ball = V_trans_before_hitting_1_ball;
	V_trans_before_hitting_1_ball = tmp;

	// теперь вернем эти координаты в старую систему координат 

	double V_x_1_ball_after_hitting = cos * V_trans_before_hitting_1_ball - sin * V_normal_before_hitting_1_ball;
	double V_y_1_ball_after_hitting = sin * V_trans_before_hitting_1_ball + cos * V_normal_before_hitting_1_ball;

	double V_x_2_ball_after_hitting = cos * V_trans_before_hitting_2_ball - sin * V_normal_before_hitting_2_ball;
	double V_y_2_ball_after_hitting = sin * V_trans_before_hitting_2_ball + cos * V_normal_before_hitting_2_ball;

	// теперь помен€ем значени€ соответствующих переменных

	ball1.Vx = V_x_1_ball_after_hitting;
	ball1.Vy = V_y_1_ball_after_hitting;

	ball2.Vx = V_x_2_ball_after_hitting;
	ball2.Vy = V_y_2_ball_after_hitting;

}

void DrawBall(const Ball& ball) {
	
	for (double k = ball.r; k > 0; --k) {

		auto rgb = RGB(ball.red * sqrt((1 - pow(k / ball.r, 2))), ball.green *sqrt((1 - pow(k / ball.r, 2))), ball.blue * sqrt((1 - pow(k / ball.r, 2))));

		txSetFillColor(rgb);
		txSetColor(rgb);
		txCircle(ball.x, ball.y, k);

	}
}
void MoveBall (Ball& ball1,Ball& ball2,const Board& board,double dt) {

	if (ball2.y > 600 - ball2.r && ball2.Vy > 0 || ball2.y < ball2.r && ball2.Vy < 0 ) {

		if (ball2.y > 600 - ball2.r && ball2.Vy > 0) {

			cout << "Ќубас" << std::endl;

		}

		ball2.Vy = (-1) * ball2.Vy;

	}
	if (ball2.x> 800 - ball2.r && ball2.Vx > 0 || ball2.x < ball2.r && ball2.Vx < 0) {

		ball2.Vx = (-1) * ball2.Vx;

	}

	if (ball1.y > 600 - ball1.r && ball1.Vy > 0  || ball1.y < ball1.r && ball1.Vy < 0) {

		if (ball1.y > 600 - ball1.r && ball1.Vy > 0) {

			cout << "Ќубас" << std::endl;

		}

		ball1.Vy = (-1) * ball1.Vy;

	}
	if (ball1.x > 800 - ball1.r && ball1.Vx > 0 || ball1.x < ball1.r && ball1.Vx < 0) {

		ball1.Vx = (-1) * ball1.Vx;

	}

	if (ball1.x > board.middle_X_position - 100 - ball1.r && ball1.x <  board.middle_X_position + 100 + ball1.r && ball1.y > board.Y1_position - ball1.r && ball1.Vy > 0) {

		ball1.Vy *= (-1);
	}
	if (ball2.x > board.middle_X_position - 100 - ball2.r && ball2.x <  board.middle_X_position + 100 + ball2.r && ball2.y > board.Y1_position - ball2.r && ball2.Vy > 0) {

		ball2.Vy *= (-1);
	}

	if (sqrt(pow(ball1.x- ball2.x, 2) + pow(ball1.y- ball2.y, 2)) < ball1.r+ ball2.r) {

		Collision_of_Balls(ball1,ball2);

	}

	ball1.x += ball1.Vx * dt;
	ball1.y += ball1.Vy * dt;

	ball2.x += ball2.Vx * dt;
	ball2.y += ball2.Vy * dt;
}

void ControlBall(Ball& ball) {

	if (GetAsyncKeyState(VK_UP)) {

		ball.Vy *= 1.01;

	}
	if (GetAsyncKeyState(VK_DOWN)) {

		ball.Vy /= 1.01;

	}
	if (GetAsyncKeyState(VK_LEFT)) {

		ball.Vx /= 1.01;

	}
	if (GetAsyncKeyState(VK_RIGHT)) {

		ball.Vx *= 1.01;

	}
}
void ControlDesk(Board& board) {

	if (GetAsyncKeyState('A')) {

		board.middle_X_position -= 5;

	}
	if (GetAsyncKeyState('D')) {

		board.middle_X_position += 5;

	}
}

int main() {

	setlocale(LC_ALL, "Russian");

	txCreateWindow(800, 600);

	const double dt = 0.1;

	double  r1 = 0,
		    r2 = 0;

	cout << "¬ведите радиусы первого и второго шаров: ";
	std::cin >> r1 >> r2;

	Ball ball1 = { 400,200, r1,20,20,250 ,0,0};
	Ball ball2= {200, 200, r2, 20, 20, 250,0,0};
	Board board;

	for (;;) {

		txClear();

		MoveBall(ball1 ,ball2 ,board,dt);

		ControlBall(ball1);
		ControlDesk(board);

		txBegin();

		DrawBall(ball1);
		DrawBall(ball2);

		txRectangle(board.middle_X_position -100,board.Y1_position,board.middle_X_position +100,board.Y2_position);

		txSetFillColor(RGB(0, 0, 0));

		txEnd();
		txSleep(0.02);
	}
	return 0;
}

