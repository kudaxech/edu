#include <SFML/Graphics.hpp>
#include <fstream>

int TXT_COUTER = 0;
int WORD_COUTER = 0;
const int NUMBER_OF_LINE_TRANSFERS = 27;

void RefreshWindow (sf::RenderWindow& window,sf::Text& text , const char* txt ,char* words,const int size_of_txt ){
    int counter = 0;
    int size_of_words = 0;
        for(int i = 0;;){
            if((int)words[i]!=16 && words[i]!='\0'){
                size_of_words++;
                i++;
            }else{
                break;
            }
        }
    for(int i = 0 ; i < size_of_words ; ++i ){

        if(words[i]=='\n'){
            ++counter;
        }
    }
    if(counter < NUMBER_OF_LINE_TRANSFERS){

        words[WORD_COUTER]=txt[TXT_COUTER];
        TXT_COUTER++;WORD_COUTER++;
        words[WORD_COUTER]=txt[TXT_COUTER];
        TXT_COUTER++;WORD_COUTER++;
        words[WORD_COUTER]=txt[TXT_COUTER];
        TXT_COUTER++;WORD_COUTER++;
        words[WORD_COUTER]='\0';


        text.setString(words);
        window.clear();
        window.draw(text);
        window.display();

    }else{
        
        int number_of_symbols_in_the_first_string = 0;
        for(int i = 0 ;;){
            if(words[i]!='\n'){
                number_of_symbols_in_the_first_string++;
                i++;
            }else{
                number_of_symbols_in_the_first_string++;
                break;
            }
        }
        
        for(int i = 0;i<size_of_words-number_of_symbols_in_the_first_string;++i){
        
            words[i]=words[i+number_of_symbols_in_the_first_string];

        }

        WORD_COUTER = size_of_words-number_of_symbols_in_the_first_string;
        words[WORD_COUTER]=txt[TXT_COUTER];
        TXT_COUTER++;WORD_COUTER++;
        words[WORD_COUTER]=txt[TXT_COUTER];
        TXT_COUTER++;WORD_COUTER++;
        words[WORD_COUTER]=txt[TXT_COUTER];
        TXT_COUTER++;WORD_COUTER++;
        words[WORD_COUTER]='\0';


        text.setString(words);
        window.clear();
        window.draw(text);
        window.display();
    }
}

int main(){

    sf::RenderWindow window(sf::VideoMode(1500,1000),".");
    window.setKeyRepeatEnabled(false);

    std::fstream f;

    f.open("abc.txt");
    f.seekg(0,std::ios::end);
    int len = f.tellg();
    char* txt = new char[len];
    char* words = new char[len];
    f.seekg(0,std::ios::beg);
    f.read(txt,len);
    f.close();
    

    sf::Font font;
    if ( !font.loadFromFile( "Arial.ttf" ) ){
    
        return 0 ;
    }


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setColor(sf::Color::Green);

    while(window.isOpen()){
   
        sf::Event event;
        while(window.waitEvent(event)){

            if(event.type == sf::Event::Closed){
                window.close();
                break;
            }
            if(event.type == sf::Event::KeyPressed){

                RefreshWindow(window,text,txt,words,len);
                
            }   
        }
    }

 delete []txt;
 delete []words;
 return 0;
}
