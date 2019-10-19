#include "TXLib.h"
#include <cmath>
#include <iostream>
#include <vector>

class Ballsss;

void Collision_of_Balls(const double x1, const double y1, const double x2, const double y2, double& Vx1, double& Vy1, double& Vx2, double& Vy2) {

	double k = (y2 - y1) / (x2 - x1);

	double sin = k / (sqrt(pow(k, 2) + 1));
	double cos = 1 / (sqrt(pow(k, 2) + 1));

	// зададим через матрицу перехода свз€ть координат в разных —ќ

	double V_trans_before_hitting_1_ball = cos * Vx1 + sin * Vy1;
	double V_normal_before_hitting_1_ball = (-1) * sin * Vx1 + cos * Vy1;

	double V_trans_before_hitting_2_ball = cos * Vx2 + sin * Vy2;
	double V_normal_before_hitting_2_ball = (-1) * sin * Vx2 + cos * Vy2;

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

	Vx1 = V_x_1_ball_after_hitting;
	Vy1 = V_y_1_ball_after_hitting;

	Vx2 = V_x_2_ball_after_hitting;
	Vy2 = V_y_2_ball_after_hitting;


}

void DrawBall(double x, double y, double r = 0, int red = 0, int green = 0, int blue = 0) {
	
	for (double k = r; k > 0; --k) {

		auto rgb = RGB(red * sqrt((1 - pow(k / r, 2))), green * sqrt((1 - pow(k / r, 2))), blue * sqrt((1 - pow(k / r, 2))));

		txSetFillColor(rgb);
		txSetColor(rgb);
		txCircle(x, y, k);

	}
}
void MoveBall(double& x1,double& x2,double& y1, double& y2 , double& Vx1,double& Vy1,double& Vx2 , double& Vy2, double dt, double r1, double r2,double& Y1_position_of_board,double& middle_X_position_of_board) {

	if (y2 > 600 - r2 && Vy2 > 0 || y2 < r2 && Vy2 < 0 ) {

		if (y2 > 600 - r2 && Vy2 > 0) {

			cout << "Ќубас" << std::endl;

		}

		(Vy2) = (-1) * (Vy2);

	}
	if (x2 > 800 - r2 && Vx2 > 0 || x2 < r2 && Vx2 < 0) {

		(Vx2) = (-1) * (Vx2);

	}

	if (y1 > 600 - r1 && Vy1 > 0  || y1 < r1 && Vy1 < 0) {

		if (y1 > 600 - r1 && Vy1 > 0) {

			cout << "Ќубас" << std::endl;

		}

		(Vy1) = (-1) * (Vy1);

	}

	if (x1 > 800 - r1 && Vx1 > 0 || x1 < r1 && Vx1 < 0) {

		(Vx1) = (-1) * (Vx1);

	}

	if (x1 > middle_X_position_of_board - 100 - r1 && x1 <  middle_X_position_of_board + 100 + r1 && y1 > Y1_position_of_board - r1 && Vy1 > 0) {

		Vy1 *= (-1);
	}
	if (x2 > middle_X_position_of_board - 100 - r2 && x2 <  middle_X_position_of_board + 100 + r2 && y2 > Y1_position_of_board - r2 && Vy2 > 0) {

		Vy2 *= (-1);
	}

	if (sqrt(pow(x1-x2, 2) + pow(y1-y2, 2)) < r1+r2) {

		Collision_of_Balls( x1, y1, x2, y2, Vx1,Vy1, Vx2, Vy2);

	}


	(x1) += (Vx1) * dt;
	(y1) += (Vy1) * dt;

	(x2) += (Vx2) * dt;
	(y2) += (Vy2) * dt;

}

void ControlBall(double& Vx1 , double& Vy1) {

	if (GetAsyncKeyState(VK_UP)) {

		Vy1 *= 1.01;

	}
	if (GetAsyncKeyState(VK_DOWN)) {

		Vy1 /= 1.01;

	}
	if (GetAsyncKeyState(VK_LEFT)) {

		Vx1 /= 1.01;

	}
	if (GetAsyncKeyState(VK_RIGHT)) {

		Vx1 *= 1.01;

	}
}
void ControlDesk(double* middle_X_position_of_board) {

	if (GetAsyncKeyState('A')) {

		*middle_X_position_of_board -= 5;

	}
	if (GetAsyncKeyState('D')) {

		*middle_X_position_of_board += 5;

	}
}

int main() {

	setlocale(LC_ALL, "Russian");

	txCreateWindow(800, 600);

	const double dt = 0.1;

	double x1 = 400, y1 = 300, Vx1 = 20, Vy1 = 20;
	double x2 = 200, y2 = 200, Vx2 = 20, Vy2 = 20;
	
	double Y1_position_of_board = 550;
	double Y2_position_of_board = 600;
	double middle_X_position_of_board = 400;

	int r1 = 0;
	int r2 = 0;
	cout << "¬ведите радиусы первого и второго шаров: ";
	std::cin >> r1 >> r2;

	for (;;) {

		txClear();

		MoveBall(x1, x2, y1, y2, Vx1, Vy1, Vx2, Vy2, dt, r1, r2, Y1_position_of_board,middle_X_position_of_board);

		ControlBall(Vx1,Vy1);
		ControlDesk(&middle_X_position_of_board);

		txBegin();

		DrawBall(x1,y1, r1, 150, 40, 60);
		DrawBall(x2,y2, r2, 150, 40, 60);

		txRectangle(middle_X_position_of_board -100,Y1_position_of_board,middle_X_position_of_board +100,Y2_position_of_board);

		txSetFillColor(RGB(0, 0, 0));

		txEnd();
		txSleep(0.02);
	}
	return 0;
}

