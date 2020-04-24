std::vector<float> findCrossingLineSegments(std::vector < std::vector <float> > absol_hit_coord_1 , std::vector < std::vector <float> > new_absol_hit_coord_2 , std::vector < std::vector <float> > old_absol_hit_coord_2 )
{
    int quantity_of_points_1 = absol_hit_coord_1.size();
    int quantity_of_points_2 = new_absol_hit_coord_2.size();
    Vector3f collision;

    for( int i = 0 ; i < quantity_of_points_1 ; ++i)
    {
        for( int j = 0 ; j < quantity_of_points_2 ; ++j)
        {
            if( i == quantity_of_points_1 - 1 )
            {
                Vector3f
                first_point_hitbox = {absol_hit_coord_1[i][0] ,absol_hit_coord_1[i][1] ,0 } ,
                second_point_hitbox = {absol_hit_coord_1[0][0] ,absol_hit_coord_1[0][1] ,0 } , 

                old_point_hitbox = {old_absol_hit_coord_2[j][0],old_absol_hit_coord_2[j][1],0},
                new_point_hitbox = {new_absol_hit_coord_2[j][0],new_absol_hit_coord_2[j][1],0};

                std::vector<float> angle = {0,0};
                


                if(areCrossing(first_point_hitbox,second_point_hitbox,old_point_hitbox,new_point_hitbox,angle))
                {   
                    std::cout << "this is "<< j << " point from moving hitbox"<< std::endl;
                    return angle;
                }

            }
            else
            {   
                Vector3f
                first_point_hitbox = {absol_hit_coord_1[i][0] ,absol_hit_coord_1[i][1] ,0 } ,
                second_point_hitbox = {absol_hit_coord_1[i+1][0] ,absol_hit_coord_1[i+1][1] ,0 } , 

                old_point_hitbox = {old_absol_hit_coord_2[j][0],old_absol_hit_coord_2[j][1],0},
                new_point_hitbox = {new_absol_hit_coord_2[j][0],new_absol_hit_coord_2[j][1],0};

                std::vector<float> angle = {0,0};

                if(areCrossing(first_point_hitbox,second_point_hitbox,old_point_hitbox,new_point_hitbox,angle))
                {   
                    std::cout << "this is "<< j << " point from moving hitbox"<< std::endl;
                    return angle;
                }
                
            }
            
        }

    }

    return {0,0};

}

std::vector<float> findCollisionByCheckPoints(std::vector < std::vector <float> > new_absol_hit_coord_moving, std::vector < std::vector <float> > old_absol_hit_coord_moving , std::vector < std::vector <float> > new_absol_hit_coord_2 , std::vector < std::vector <float> > old_absol_hit_coord_2 )
{   
    int size_of_moving = new_absol_hit_coord_moving.size();
    int other_size = new_absol_hit_coord_2.size();

    for(int i = 0 ; i < size_of_moving ; ++i)
    {
        if( i == size_of_moving - 1 )
        {
            std::vector<std::vector<float>> points_clockwise;
            points_clockwise.push_back({old_absol_hit_coord_moving[i]});
            points_clockwise.push_back({old_absol_hit_coord_moving[0]});
            points_clockwise.push_back({new_absol_hit_coord_moving[0]});
            points_clockwise.push_back({new_absol_hit_coord_moving[i]});

            for( int j = 0 ; j < other_size ; ++j)
            {
                std::vector<float> old_point = old_absol_hit_coord_2[j];
                std::vector<float> new_point = new_absol_hit_coord_2[j];
                if( checkPointInPolygon(old_point,points_clockwise) or checkPointInPolygon(new_point,points_clockwise))
                {//// сюда зайдет в том случае если есть пересечение 100%
                    float 
                    sin = 0,
                    cos = 0;
                    
                    

                    if ( old_absol_hit_coord_moving[i][0] == old_absol_hit_coord_moving[0][0])
                    {
                        if (old_absol_hit_coord_moving[i][1] < old_absol_hit_coord_moving[0][1])
                        {
                            sin = 1;
                            cos = 0;
                        }
                        else 
                        {
                            sin = -1;
                            cos = 0;
                        }
                    }
                    else {
                        float k = (old_absol_hit_coord_moving[0][1] - old_absol_hit_coord_moving[i][1]) / (old_absol_hit_coord_moving[0][0] - old_absol_hit_coord_moving[i][0]);
                        std::cout <<" k = "<<k<<std::endl;
                        sin = k / (sqrt(pow(k, 2) + 1));
                        cos = 1 / (sqrt(pow(k, 2) + 1));
                    }

                    
                    return {cos,-sin};
                 
                }

                
            }

        }
        else
        {
            std::vector<std::vector<float>> points_clockwise;
            points_clockwise.push_back({old_absol_hit_coord_moving[i]});
            points_clockwise.push_back({old_absol_hit_coord_moving[i+1]});
            points_clockwise.push_back({new_absol_hit_coord_moving[i+1]});
            points_clockwise.push_back({new_absol_hit_coord_moving[i]});

            for( int j = 0 ; j < other_size ; ++j)
            {
                std::vector<float> old_point = old_absol_hit_coord_2[j];
                std::vector<float> new_point = new_absol_hit_coord_2[j];
                if( checkPointInPolygon(old_point,points_clockwise) or checkPointInPolygon(new_point,points_clockwise))
                {//// сюда зайдет в том случае если есть пересечение 100%
                    float 
                    sin = 0,
                    cos = 0;

                    
                    

                    if ( old_absol_hit_coord_moving[i][0] == old_absol_hit_coord_moving[i+1][0])
                    {
                        if (old_absol_hit_coord_moving[i][1] < old_absol_hit_coord_moving[i+1][1])
                        {
                            sin = 1;
                            cos = 0;
                        }
                        else 
                        {
                            sin = -1;
                            cos = 0;
                        }
                    }
                    else {
                        float k = (old_absol_hit_coord_moving[i+1][1] - old_absol_hit_coord_moving[i][1]) / (old_absol_hit_coord_moving[i+1][0] - old_absol_hit_coord_moving[i][0]);
                        
                        sin = k / (sqrt(pow(k, 2) + 1));
                        cos = 1 / (sqrt(pow(k, 2) + 1));
                    }
                    
                    return {cos,-sin};
                     
                }



            }

        }

    }


    return{0,0};

}
