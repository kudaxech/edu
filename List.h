#include <iostream>

class Node {

    public:

        int value ;
        Node* next;


        Node(){

            value = 0;
            next = nullptr;

        }

};

class List{
    public:

        List(){

            head = nullptr;
        }
        ~List(){

            clear();

        }
        
        int len(){

            int counter_of_objects = 0;

            Node* current = head;

            while(current){

                counter_of_objects ++ ;
                current = current -> next;

            }

            return counter_of_objects;
        }

        Node* getObjectByIndex(int index){

            int counter_of_objects = 0;
            
            Node* current = head;

            while(counter_of_objects < index){

                counter_of_objects ++ ;
                current = current -> next;

            }

            return current;
        }

        void pushFront(int value_input){

            Node* first = new Node;

            first -> value = value_input;

            first -> next = this -> head;
            this -> head = first;

        }

        void pushBack(int value_input){

            int index_of_last_oblect = len() - 1;

            Node* new_last_object = new Node;

            Node* old_last_object = getObjectByIndex(index_of_last_oblect);

            new_last_object -> next = nullptr;
            new_last_object -> value = value_input;

            old_last_object -> next = new_last_object;
            
        }

        void deleteByIndex(int index){
            
            Node* deleting_object = getObjectByIndex(index);
            Node* before_deleting_object = getObjectByIndex(index-1);

            before_deleting_object -> next = deleting_object -> next;

            delete[] deleting_object;
        }

        bool find(int value){

            bool is_value_found = false;
            int counter_of_objects = 0;
            int len_of_list = len();

            while(counter_of_objects < len_of_list){

                Node* pointer = getObjectByIndex(counter_of_objects);

                if(pointer -> value == value){
                    is_value_found = true;
                    break;
                }

                counter_of_objects++;
            }

            return is_value_found;
        }

        void print(){

            int counter_of_objects = 0;
            int len_of_list = len();

            while(counter_of_objects < len_of_list){

                Node* pointer = getObjectByIndex(counter_of_objects);

                std::cout << pointer -> value << std::endl;

                counter_of_objects++;

            }
        }

        void clear(){

            int len_of_list = len();
            int counter_of_objects = len_of_list - 1;

            while( counter_of_objects > 0 ){
                
                deleteByIndex(counter_of_objects);
                counter_of_objects--;
            }

            delete[] head;

            head = nullptr;

        }

        void insertByIndex( int index ){

            if( index == 0 ){
                pushFront(0);
            }
            else if( index == len()-1 ){
                pushBack(0);
            }
            else{
                Node* old_object = getObjectByIndex(index);
                Node* before_old_object = getObjectByIndex(index-1);

                Node* new_object = new Node;

                new_object -> next = before_old_object -> next;
                before_old_object -> next = new_object;
            }
        }

        int& operator[](int index){
                        
            Node* current = getObjectByIndex(index);

            return current -> value ;
        }

        void operator=(List& copied){

            int len_of_lists = len();
            int counter_of_lists = len_of_lists - 1;

            while( counter_of_lists >= 0 ){
                
                Node* pointer_of_this_list = getObjectByIndex(counter_of_lists);
                pointer_of_this_list -> value = copied[counter_of_lists];

            }
        }

    private:

        Node* head;

};
