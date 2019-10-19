struct Ball {

bool Is_Collide_With_This_Ball(const Ball& ball) {

	if ( sqrt(pow(this->x - ball.x, 2) + pow(this->y - ball.y, 2)) <= this->r + ball.r) {
		float V_relative_1_to_2_X = this->Vx - ball.Vx;
		float V_relative_1_to_2_Y = this->Vy - ball.Vy;

		if (((ball.x - this->x) * V_relative_1_to_2_X > 0) && ((ball.y - this->y) * V_relative_1_to_2_Y > 0)) {

			return true;
		}
		else if ((ball.x - this->x) * V_relative_1_to_2_X > 0) {
	
			return true;
			
		}
		else if ((ball.y - this->y) * V_relative_1_to_2_Y > 0) {
			
			return true;
			
		}
	}

	return false;
}
void To_Collide_With_This_Ball(Ball& ball) {

	double sin = -1;
	double cos = 0;

	if (Is_Collide_With_This_Ball(ball)) {
		if (this->x == ball.x) {
			if (this->y < ball.y) {
				sin = 1;
				cos = 0;
			}
			else {
				sin = -1;
				cos = 0;
			}
		}
		else {
			double k = (ball.y - this->y) / (ball.x - this->x);
			sin = k / (sqrt(pow(k, 2) + 1));
			cos = 1 / (sqrt(pow(k, 2) + 1));
		}

		// зададим через матрицу перехода свзять координат в разных СО

		double V_trans_before_hitting_1_ball = cos * this->Vx + sin * this->Vy;
		double V_normal_before_hitting_1_ball = (-1) * sin * this->Vx + cos * this->Vy;

		double V_trans_before_hitting_2_ball = cos * ball.Vx + sin * ball.Vy;
		double V_normal_before_hitting_2_ball = (-1) * sin * ball.Vx + cos * ball.Vy;

		// выразил скорости в новой СК , теперь поменяем тангенциальные составляющие

		double tmp = V_trans_before_hitting_2_ball;

		V_trans_before_hitting_2_ball = V_trans_before_hitting_1_ball;
		V_trans_before_hitting_1_ball = tmp;

		// теперь вернем эти координаты в старую систему координат 

		double V_x_1_ball_after_hitting = cos * V_trans_before_hitting_1_ball - sin * V_normal_before_hitting_1_ball;
		double V_y_1_ball_after_hitting = sin * V_trans_before_hitting_1_ball + cos * V_normal_before_hitting_1_ball;

		double V_x_2_ball_after_hitting = cos * V_trans_before_hitting_2_ball - sin * V_normal_before_hitting_2_ball;
		double V_y_2_ball_after_hitting = sin * V_trans_before_hitting_2_ball + cos * V_normal_before_hitting_2_ball;

		// теперь поменяем значения соответствующих переменных

		this->Vx = V_x_1_ball_after_hitting;
		this->Vy = V_y_1_ball_after_hitting;

		ball.Vx = V_x_2_ball_after_hitting;
		ball.Vy = V_y_2_ball_after_hitting;
	}
}
void DrawBall(sf::RenderWindow& window ) {

	for(double i = r;i>0;--i){
        sf::CircleShape shape(i);
        shape.setPosition(this->x-i,this->y-i);
		shape.setFillColor(sf::Color(this->red * sqrt((1 - pow(i / this->r, 2))), this->green* sqrt((1 - pow(i / this->r, 2))),this->blue* sqrt((1 - pow(i / this->r, 2)))));
    	window.draw(shape);
		
	}
}
void MoveBall() {

	if (this->y > 600 - this->r && this->Vy > 0 || this->y < this->r && this->Vy < 0) {

		this->Vy = (-1) * this->Vy;

	}
	if (this->x > 800 - this->r && this->Vx > 0 || this->x < this->r && this->Vx < 0) {

		this->Vx = (-1) * this->Vx;

	}

	this->x += this->Vx * dt;
	this->y += this->Vy * dt;
}

	const double dt = 0.1;
	double  x = 6,
			y = 6,
			r = 5,
			Vx = 10,
			Vy = 10,
			red = 144,
			green = 0,
			blue = 0;
};