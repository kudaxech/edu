#include"TXLib.h"
#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

void DrawBall(double x, double y, double r = 0, int red = 0, int green = 0, int blue = 0) {


	for (double k = r; k > 0; --k) {

		txSetFillColor(RGB(red * sqrt((1 - pow(k / r, 2))), green * sqrt((1 - pow(k / r, 2))), blue * sqrt((1 - pow(k / r, 2)))));
		txSetColor(RGB(red * sqrt((1 - pow(k / r, 2))), green * sqrt((1 - pow(k / r, 2))), blue * sqrt((1 - pow(k / r, 2)))));
		txCircle(x, y, k);

	}

}
void MoveBall(vector <double>& first_ball, vector <double>& second_ball, double dt, double r1, double r2,vector <double>& params_of_desk) {

	double x1 = first_ball[0];
	double y1 = first_ball[1];
	double Vx1 = first_ball[2];
	double Vy1 = first_ball[3];

	double x2 = second_ball[0];
	double y2 = second_ball[1];
	double Vx2 = second_ball[2];
	double Vy2 = second_ball[3];


	if (y2 > 600 - r2 && Vy2 > 0 || y2 < r2 && Vy2 < 0 ) {

		if (y2 > 600 - r2 && Vy2 > 0) {

			cout << "Ќубас" << endl;

		}

		(Vy2) = (-1) * (Vy2);

	}
	if (x2 > 800 - r2 && Vx2 > 0 || x2 < r2 && Vx2 < 0) {

		(Vx2) = (-1) * (Vx2);

	}

	if (y1 > 600 - r1 && Vy1 > 0  || y1 < r1 && Vy1 < 0) {

		if (y1 > 600 - r1 && Vy1 > 0) {

			cout << "Ќубас" << endl;

		}

		(Vy1) = (-1) * (Vy1);

	}
	if (x1 > 800 - r1 && Vx1 > 0 || x1 < r1 && Vx1 < 0) {

		(Vx1) = (-1) * (Vx1);

	}


	if (x1 > params_of_desk[0] - r1 && x1 < params_of_desk[1] + r1 && y1 > params_of_desk[2] - r1 && Vy1 > 0) {

		Vy1 *= (-1);
	}
	if (x2 > params_of_desk[0] - r2 && x2 < params_of_desk[1] + r2 && y2 > params_of_desk[2] - r2 && Vy2 > 0) {

		Vy2 *= (-1);
	}

	
	if (sqrt(pow(x1-x2, 2) + pow(y1-y2, 2)) < r1+r2) {

		double k = (y2 - y1) / (x2 - x1);

		double sin = k / (sqrt(pow(k, 2) + 1));
		double cos = 1 / (sqrt(pow(k, 2) + 1));

		// зададим через матрицу перехода свз€ть координат в разных —ќ

		double V_trans_before_bitting_1_ball = cos * Vx1 + sin * Vy1;
		double V_normal_before_bitting_1_ball = (-1) * sin * Vx1 + cos * Vy1;

		double V_trans_before_bitting_2_ball = cos * Vx2 + sin * Vy2;
		double V_normal_before_bitting_2_ball = (-1) * sin * Vx2 + cos * Vy2;

		// выразил скорости в новой —  , теперь помен€ем тангенциальные составл€ющие

		double tmp = V_trans_before_bitting_2_ball;

		V_trans_before_bitting_2_ball = V_trans_before_bitting_1_ball;
		V_trans_before_bitting_1_ball = tmp;

		// теперь вернем эти координаты в старую систему координат 

		double V_x_1_ball_after_bitting = cos * V_trans_before_bitting_1_ball - sin * V_normal_before_bitting_1_ball;
		double V_y_1_ball_after_bitting = sin * V_trans_before_bitting_1_ball + cos * V_normal_before_bitting_1_ball;

		double V_x_2_ball_after_bitting = cos * V_trans_before_bitting_2_ball - sin * V_normal_before_bitting_2_ball;
		double V_y_2_ball_after_bitting = sin * V_trans_before_bitting_2_ball + cos * V_normal_before_bitting_2_ball;

		// теперь помен€ем значени€ соответствующих переменных

		Vx1 = V_x_1_ball_after_bitting;
		Vy1 = V_y_1_ball_after_bitting;

		Vx2 = V_x_2_ball_after_bitting;
		Vy2 = V_y_2_ball_after_bitting;




	}



	(x1) += (Vx1) * dt;
	(y1) += (Vy1) * dt;

	(x2) += (Vx2) * dt;
	(y2) += (Vy2) * dt;

	first_ball[0] = x1;             
	first_ball[1] = y1;	
	first_ball[2] = Vx1;								
	first_ball[3] = Vy1;								

	second_ball[0] = x2;								
	second_ball[1] = y2;								
	second_ball[2] = Vx2;								
	second_ball[3] = Vy2;								

}

void ControlBall(vector<double>& first_ball) {

	if (GetAsyncKeyState(VK_UP)) {

		(first_ball[3]) *= 1.01;

	}
	if (GetAsyncKeyState(VK_DOWN)) {

		(first_ball[3]) /= 1.01;

	}
	if (GetAsyncKeyState(VK_LEFT)) {

		(first_ball[2]) /= 1.01;

	}
	if (GetAsyncKeyState(VK_RIGHT)) {

		(first_ball[2]) *= 1.01;

	}

}
void ControlDesk(double* middle_X_position_of_desk ) {

	if (GetAsyncKeyState('A')) {

		*middle_X_position_of_desk -= 5;

	}
	if (GetAsyncKeyState('D')) {

		*middle_X_position_of_desk += 5;

	}
}

int main() {

	setlocale(LC_ALL, "Russian");

	txCreateWindow(800, 600);

	const double dt = 0.1;

	double x1 = 400, y1 = 300, Vx1 = 20, Vy1 = 20;
	double x2 = 200, y2 = 200, Vx2 = 20, Vy2 = 20;

	vector <double> first_ball = { x1,y1,Vx1,Vy1 };
	vector <double> second_ball = { x2,y2,Vx2,Vy2 };

	double Y1_position = 550;
	double Y2_position = 600;
	double middle_X_position_of_desk = 400;

	int r1 = 0;
	int r2 = 0;

	cin >> r1 >> r2;

	for (;;) {

		txClear();

		vector<double> params_of_desk = { middle_X_position_of_desk - 100, middle_X_position_of_desk + 100,Y1_position ,Y2_position, };
		MoveBall(first_ball, second_ball, dt, r1, r2,params_of_desk);

		ControlBall(first_ball);
		ControlDesk(&middle_X_position_of_desk);

		DrawBall(first_ball[0], first_ball[1], r1, 150, 40, 60);
		DrawBall(second_ball[0], second_ball[1], r2, 150, 40, 60);

		txRectangle(middle_X_position_of_desk-100,Y1_position,middle_X_position_of_desk+100,Y2_position);

		txSetFillColor(RGB(0, 0, 0));

		txBegin();
		txSleep(0.02);

	}

	return 0;
}

