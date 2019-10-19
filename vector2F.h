struct vector2F{

    vector2F(){

        x = 0;
        y = 0;

    }
    vector2F(float x , float y){

        this->x = x;
        this->y = y;

    }
    vector2F operator+(vector2F vec){

        return{x+vec.x,y+vec.y};

    }
    vector2F operator*(float const1){

        x*= const1;
        y*= const1;

    }
    vector2F operator/(float const1){

        x/= const1;
        y/= const1;
        
    }
    void operator=(vector2F vec){
        
        this->x=vec.x;
        this->y=vec.y;

    }
    vector2F to_proect_this_vector_on(vector2F vec){
        
        float cos = (x*vec.x+y*vec.y)/(sqrt(x*x+y*y)*sqrt(vec.x*vec.x+vec.y*vec.y));
        float norm_of_first_vector = sqrt(x*x+y*y);
        float norm_of_second_vector = sqrt(vec.x*vec.x+vec.y*vec.y);

        return{norm_of_first_vector*cos*vec.x/norm_of_second_vector,norm_of_first_vector*cos*vec.y/norm_of_second_vector};
    }




    float x = 0,
          y = 0;

};
