#include <iostream>
#include <fstream>
#include <vector>

std::vector< std::vector<char> > ReadFromFile(char name_of_file[] ){

    int col = 0,
        str = 0;
    
    std::ifstream islands ;
    islands.open(name_of_file);
    islands >> str >> col;
    std::vector < std::vector <char> > field_of_islands(str, std::vector <char> (col) );
    
    for(int i = 0 ; i < str ; ++i ){
        for(int k = 0 ; k < col ; ++k){
            
            islands >> field_of_islands[i][k];
        }
    }
    islands.close();
    return field_of_islands;
}
void FindNeighbours(std::vector< std::vector<char> >& field_of_islands , int str_position , int col_position){
    int str = field_of_islands.size(),
        col = field_of_islands[0].size();


    if(field_of_islands[str_position][col_position] == '1'){

        field_of_islands[str_position][col_position] = '0';

        if( (str_position > 0 and col_position > 0 ) and (str_position < str - 1 and col_position < col - 1 )  ){
            
            FindNeighbours(field_of_islands ,str_position - 1 ,col_position);
            FindNeighbours(field_of_islands ,str_position + 1 ,col_position);
            FindNeighbours(field_of_islands ,str_position ,col_position - 1 );
            FindNeighbours(field_of_islands ,str_position ,col_position + 1);

        }else if( str_position == 0 and col_position == 0 ){

            FindNeighbours(field_of_islands ,str_position + 1 ,col_position);
            FindNeighbours(field_of_islands ,str_position  ,col_position + 1 );

        }else if( str_position == 0 and col_position == col - 1 ){

            FindNeighbours(field_of_islands , str_position + 1 ,col_position );
            FindNeighbours(field_of_islands , str_position , col_position - 1 );

        }else if( str_position == str - 1 and col_position == 0 ){

            FindNeighbours(field_of_islands ,str_position - 1 ,col_position );
            FindNeighbours(field_of_islands ,str_position  ,col_position + 1 );

        }else if( str_position == str - 1 and col_position == col - 1 ){

            FindNeighbours(field_of_islands ,str_position - 1 ,col_position );
            FindNeighbours(field_of_islands ,str_position  ,col_position - 1 );

        }else if( str_position == 0 ){

            FindNeighbours(field_of_islands ,str_position + 1 ,col_position );
            FindNeighbours(field_of_islands ,str_position  ,col_position - 1 );
            FindNeighbours(field_of_islands ,str_position ,col_position + 1 );   

        }else if( str_position == str - 1 ){
            
            FindNeighbours(field_of_islands ,str_position  ,col_position - 1 );
            FindNeighbours(field_of_islands ,str_position ,col_position + 1 );
            FindNeighbours(field_of_islands ,str_position - 1 ,col_position  );

        }else if( col_position == 0 ){
            
            FindNeighbours(field_of_islands ,str_position - 1 ,col_position );
            FindNeighbours(field_of_islands ,str_position + 1 ,col_position );
            FindNeighbours(field_of_islands ,str_position  ,col_position + 1 );

        }else if( col_position == col - 1 ){
            
            FindNeighbours(field_of_islands ,str_position - 1 ,col_position );
            FindNeighbours(field_of_islands ,str_position + 1 ,col_position );
            FindNeighbours(field_of_islands ,str_position  ,col_position - 1 );

        }
    } 
}
void FindFirstGround(std::vector< std::vector<char> >& field_of_islands){

    int str = field_of_islands.size(),
        col = field_of_islands[0].size();

    
    int str_position = 0,
        col_position = 0;

    for(int i = 0 ; i < str ; ++i){
        for(int k = 0 ; k < col ; ++k){
            if(field_of_islands[i][k] == '1'){
                str_position = i;
                col_position = k;
                break;
            }
        }
    }
    
    FindNeighbours(field_of_islands,str_position,col_position);

}
bool FieldIsEmpty(const std::vector< std::vector<char> >& field_of_islands){

    int str = field_of_islands.size(),
        col = field_of_islands[0].size();

     for(int i = 0 ; i < str ; ++i){
        for(int k = 0 ; k < col ; ++k){
            if( field_of_islands[i][k] == '1'){
                return false;
            }
        }
    }

    return true;
}

int main(){

    std::vector< std::vector<char> > field_of_islands = ReadFromFile("array_of_islands.txt");
    
    int quantity_of_islands = 0;
    while( !FieldIsEmpty( field_of_islands )){
        FindFirstGround(field_of_islands);
        quantity_of_islands++;
        
    }
    
    std::cout << quantity_of_islands << std::endl;

    return 0;
}
