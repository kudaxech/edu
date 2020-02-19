#include <vector>
#include <iostream>
#include <cmath>



std::vector<int> GiveSortedVector (const std::vector<int>& input_vector1){

    std::vector<int> input_vector =  input_vector1;  
    int position_of_positive_value = 0;
    int size_of_input_array = input_vector.size();

    for(int i = 0 ; i < size_of_input_array ; ++i){
        if(input_vector[i] >= 0){
            position_of_positive_value = i;
            break;
        }
    }

    std::vector<int> output_vector;

    int left_pointer = position_of_positive_value,
        right_pointer = position_of_positive_value;

    left_pointer--;
    right_pointer++;
    bool first_positive_number_is_used = false;


    for(int i = 1 ; i <= size_of_input_array ; ++i){

        if( left_pointer >= 0 and right_pointer < size_of_input_array ){
  
            if( pow(input_vector[left_pointer],2) > pow(input_vector[right_pointer],2) ){
                output_vector.push_back( pow(input_vector[right_pointer],2) );
                right_pointer++;

            }
            else {
                
                if(pow(input_vector[left_pointer],2) < pow(input_vector[position_of_positive_value] , 2) ){
                    
                    output_vector.push_back( pow(input_vector[left_pointer],2) );
                    left_pointer--;
                    

                }else{
                    if( !first_positive_number_is_used ){
                        
                        output_vector.push_back(input_vector[position_of_positive_value]);
                        first_positive_number_is_used = true;


                    }else{
                        output_vector.push_back( pow(input_vector[left_pointer],2)  );
                        left_pointer--;
                        
                    }

                } 
            }    

        }else if( left_pointer < 0 and right_pointer < size_of_input_array ){
            
            output_vector.push_back( pow(input_vector[right_pointer], 2 ) );
            right_pointer++;
        
        }else if( right_pointer >= size_of_input_array and left_pointer >= 0 ){
           
            output_vector.push_back( pow(input_vector[left_pointer],2 ) );
            left_pointer--;
        
        }
        
        
    }
    
    return output_vector;
}

int main(){

    std::vector<int> input_vector = {-10 , -7 , -4 , -1 , 1 , 2 , 6};
    
    std::vector<int> output_vector = GiveSortedVector(input_vector);

    for(auto i : output_vector){

        std::cout << i << ' ';
    }

    return 0;
}
