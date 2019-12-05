#include <SFML/Graphics.hpp>

class DrawableObject {
    public:
    virtual ~DrawableObject(){}

    virtual void Draw(sf::RenderWindow* window){}

};
class GraphicManager{
    public:

        GraphicManager(){
            size_of_array = 5;
            objects = new DrawableObject*[size_of_array];
        }

        ~GraphicManager(){

            delete[] objects;
        }

        void DrawAll(sf::RenderWindow* window){
            for(int i = 0 ;i<amount_of_objects;++i)      
                objects[i] -> Draw(window);
        }

        void Register(DrawableObject* object){
            if(amount_of_objects == size_of_array){
                ExpandErray(objects);
                return Register(object);
            }
        
            objects[amount_of_objects]=object;
            amount_of_objects++;               
        }

        void UnRegister(DrawableObject* object){
            RefreshArray(objects,object);
        }
        
    private:
        int amount_of_objects = 0;
        int size_of_array = 0;
        DrawableObject **objects ;

        void ExpandErray(DrawableObject** objects){

            if(size_of_array != 0){
                DrawableObject ** new_array = new DrawableObject*[2*size_of_array];

                for(int i = 0 ; i <size_of_array;++i){
                    new_array[i] = objects[i];
                }

                size_of_array*=2;

                delete[] objects;
// C++ realloc cstdlib
                objects = new_array;
            }
            else{
                delete[] objects;
                size_of_array = 2;

                DrawableObject ** new_array = new DrawableObject*[size_of_array];
            }
        }
        void RefreshArray(DrawableObject** objects, DrawableObject* object){

            for(int i = 0; i < size_of_array; ++i){

                if(objects[i]==object){ // remove 
                    if(size_of_array == 1){

                        delete[] objects;
                        amount_of_objects--;
                        size_of_array = 2;

                        DrawableObject** new_array = new DrawableObject*[size_of_array];

                        objects = new_array;
                    }else{ 

                        for(int k = i ; k <= size_of_array-2;++k){//  прикол в том что не нужно будет проерять массив на равество
                                                                  // его размера единицы тк мы уже сделали размер не равным 1
                                                                  //
                            objects[k]=objects[k+1];
                        }

                        amount_of_objects--;
                        size_of_array--; // ne nado прикол в том что мы вообще говря работаем только с переменной amount_of_obj 
                                         // и поэтому если мы просто уменьшим ее на 1 то нам не нужно будет потом следить 
                                         //за тем что вообще лежит в массиве 

                        DrawableObject** new_array = new DrawableObject*[size_of_array]; // ne nado
                        for(int i = 0 ; i <size_of_array;++i){
                            new_array[i] = objects[i];
                        }
                        delete[] objects;

                        objects = new_array;

                    }
                }
            }   
        }
};
