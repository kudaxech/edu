#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "vector2F.h"
#include "Ball.h"


class DrawableObject {
    public:

    virtual void Draw(){

    }
   
};
class GraphicManager{
    public:

        ~GraphicManager(){
            for(int i = 0;i< number_of_objects;++i){
                delete objects[i];
            }

            delete[] objects;
        }
        

        void DrawAll(){

            for(int i = 0 ;i<number_of_objects;++i){
                
                (*(objects[i])).Draw();
                
            }
        }
        void Register(DrawableObject* object,int number_of_input_object){
            objects[number_of_input_object-1] = object;
            
        }
        void SetNumberOfObjectsAndDoArray(int number_of_objects_input){
            number_of_objects = number_of_objects_input;
            objects = new DrawableObject*[number_of_objects];
        }
        
    private:
        int number_of_objects ;
        DrawableObject **objects ;
};
class AllBalls:public DrawableObject {
    public:
        ~AllBalls(){

            delete[] balls;
            delete[] window;
        }

        void Draw(){

            (*window).clear();
            for(int i = 0; i < quantity_of_balls;++i){

				(balls[i]).DrawBall(*window);

			}
            (*window).display();

        }
        void SetBallsAndQuantity(Ball* balls_input,int quantity_of_balls_input){
            balls = balls_input;
			quantity_of_balls = quantity_of_balls_input;
        }


        sf::RenderWindow* window;
    private:
		int quantity_of_balls = 0;
        Ball* balls;
};
void DrawAll(class GraphicManager&  manager ){

    manager.DrawAll();

}
void Collide_of_All_Balls(Ball* balls,int number_of_balls) {

	for (int i = 0; i < number_of_balls; ++i) {

		for (int j = 0; j < number_of_balls; ++j) {
			if (i != j) {
				balls[i].To_Collide_With_This_Ball(balls[j]);
			}
		}
	}
}
void MoveAllBalls(Ball* balls,int number_of_balls) {

	for (int i = 0; i < number_of_balls; ++i) {
		balls[i].MoveBall();
	}
}
void ToFillArray(Ball* balls,int number_of_balls){

	for (int i = 0; i < number_of_balls; ++i) {

		balls[i].r = 10;
		balls[i].x = rand()%800;
		balls[i].y = rand()%600;
		balls[i].Vx = rand()%20;
		balls[i].Vy = rand()%20;
	}
}

int main() {

    sf::RenderWindow window(sf::VideoMode(900, 600), "!!!!!!!!!!!!!!");
    window.setFramerateLimit(80);

	const double dt = 0.1;
	int number_of_balls = 0;

	std::cout<<"Enter number of the balls: ";
	std::cin>>number_of_balls;

	Ball* balls = new Ball[number_of_balls];

	AllBalls Balls;
	Balls.window = &window;
	Balls.SetBallsAndQuantity(balls,number_of_balls);

	GraphicManager manager;
	manager.SetNumberOfObjectsAndDoArray(1);
	manager.Register(&Balls,1);

	ToFillArray(balls,number_of_balls);

	while (window.isOpen()){

        MoveAllBalls(balls,number_of_balls);
        Collide_of_All_Balls(balls,number_of_balls);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


		DrawAll(manager);
		
	}
	delete[] balls;
	return 0;
}
