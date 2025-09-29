#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "vectorOperation.h"
#include "AlinePlot.h"
#include "fstream"
using namespace sf;
using namespace std;




int main(){

    //prepares s 
    vector<double> S{};
    

    //prepares g
    vector<double> G{};
    

    //prepares Idenity matrix
    vector<double> ICreator{};
    vector<vector<double>> I{};

    ifstream matrixFile("matrix.txt"); // declare ifstream object and open the file
   
    
    // check for an error
    if ( matrixFile.fail() ) {
        cerr << "Error opening input file";
        return -1;
    }
    char value;
    int location = 0;
    
    bool found = false;
    //finds 1
    while(matrixFile >> value){
        if(value == '1'){
            found = true;
            break;
        }
        else if(value == '0' ){
            location++;
        }
    }
    // returns error if out of index
    if(!found || location > 15){
        cerr<< "Value not in matrix";
        return -1;
    }
    //closes file
    matrixFile.close();
    //reports location
    cout << "Value at: " << location <<endl;
    //creates the I S and G matrix
    for(int i = 0; i<16; i++){
        S.push_back(1.0/4); 
        G.push_back(0); 
        ICreator.clear();
        for(int s = 0; s<16; s++){
            if(i == s){
                ICreator.push_back(1);
            }
            else{
                ICreator.push_back(0);
            }
            
        }
        I.push_back(ICreator);
    }
    // inserts 1 at location in vector
    G.at(location) = 1;
    //prepares operater UG
    vector<vector<double>> UG{};
    //prepares operater US
    vector<vector<double>> US{};
    UG = subtract(I, mutiplyByConstant(tensorProduct(G,G),2));
    US =  subtract(I, mutiplyByConstant(tensorProduct(S,S),2));
    //creates PSI
    vector<double> psi{};
    //intialzes PSI
    psi = S;
    vector<double> sPsi{};
    //creates sPsi
    vector<double> gPsi{};   
    //creates gPsi
    // fills with intial probabilties
    sPsi.push_back(pow(abs(scalerProduct(psi,S)),2));
    gPsi.push_back(pow(abs(scalerProduct(psi,G)),2));
    //preforms 6 iteratoins
    int iterations = 6;
    vector<double> iterationsL = {0};
    for(int i = 0; i < iterations; i++){
        iterationsL.push_back(i+1);
        // preforms ug>|psi>
        psi = matrixVectorMultiplication(psi,UG);
        // preforms us>|psi>
        psi = matrixVectorMultiplication(psi,US);
        //saves new probabilities
        sPsi.push_back(pow(abs(scalerProduct(psi,S)),2));
        gPsi.push_back(pow(abs(scalerProduct(psi,G)),2));
    }
    //prepares windows
    RenderWindow window( VideoMode(680, 420), "SFML Test" );
    //prepares  SProbabilitys graph
    ALinePlot SProbabilitys(iterationsL, sPsi, sf::Color(196, 24, 47));
     //prepares  gProbabilitys graph
    ALinePlot GProbabilitys(iterationsL, gPsi, sf::Color::Blue);
    //intializes x and y axis
    RectangleShape xAxis;
    RectangleShape yAxis;
    xAxis.setSize(sf::Vector2f(600, 5));
    xAxis.setPosition(sf::Vector2f(20+40, 300));
    yAxis.setSize(sf::Vector2f(5, 290));
    yAxis.setPosition(sf::Vector2f(20+40, 10));
    xAxis.setFillColor(sf::Color::Black);
    yAxis.setFillColor(sf::Color::Black);

    //intilizes texts for points s
    vector<sf::Text> textS{};
    //intilizes texts for points g
    vector<sf::Text> textG{};
    //intilizes texts for legend and other values
    vector<sf::Text> textExtra{};

    //gets the position for points in sfml for s
    vector<double> xPosS = SProbabilitys.getNewX();
    vector<double> yPosS = SProbabilitys.getNewY();

    //gets the position for points in sfml for g    
    vector<double> xPosG = GProbabilitys.getNewX();
    vector<double> yPosG = GProbabilitys.getNewY();

    //loads font
    sf::Font font;
    
    if (!font.loadFromFile("arial.ttf"))
    {
        throw std::out_of_range("text not loaded");
    }
    else {

        // sets font
        sf::Text text1, text2;
        text1.setFont(font);
        text2.setFont(font);
        
        //holder variables
        float yHolder;
        string yHolder1;
        for(unsigned int i =0; i < xPosG.size(); i++){
            // insert x axis tick values
            text1.setString(to_string(i));
            text1.setCharacterSize(20);
            text1.setFillColor(sf::Color::Black); 
            text1.setPosition(sf::Vector2f(xPosG.at(i)-3, 325));
            textExtra.push_back(text1);
        }
        
        for(unsigned int i =0; i < gPsi.size(); i++){
            //insert points for g
            yHolder = int(gPsi.at(i)*100000)/100000.0;
            yHolder1 = to_string(yHolder);
            
            text2.setString(yHolder1);
            text2.setCharacterSize(15);
            text2.setFillColor(sf::Color::Blue); 
            text2.setPosition(sf::Vector2f(xPosG.at(i)+10, yPosG.at(i)-10));
            textG.push_back(text2);
        }
        for(unsigned int i =0; i < sPsi.size(); i++){
            //inserts point for s
            yHolder = int(sPsi.at(i)*100000)/100000.0;
            yHolder1 = to_string(yHolder);
            
            text2.setString(yHolder1);
            text2.setCharacterSize(15);
            text2.setFillColor(sf::Color(196, 24, 47)); 
            text2.setPosition(sf::Vector2f(xPosS.at(i)+10, yPosS.at(i)-10));
            textS.push_back(text2);
        }
        //labels for legend
        text1.setString("Amplitude G");
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Black); 
        text1.setPosition(sf::Vector2f(510, 145+25));
        textExtra.push_back(text1);

        text1.setString("Amplitude S");
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Black); 
        text1.setPosition(sf::Vector2f(510, 145));
        textExtra.push_back(text1);
        //xaxis lable
        text1.setString("Iteration");
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Black); 
        text1.setPosition(sf::Vector2f(320, 370));
        textExtra.push_back(text1);
        // yaxis labels
        text1.setString("Probabilty (0 to 1)");
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Black); 
        text1.setPosition(sf::Vector2f(20, 250));
        text1.rotate(90+180);
        textExtra.push_back(text1);


    }
    //legend colors
    sf::CircleShape legend1;
    sf::CircleShape legend2;
   
        
    legend1.setRadius(6);
    legend1.setOrigin(6,6);
    legend1.setPosition(500, 150+25);
    legend1.setFillColor(sf::Color::Blue);

    legend2.setRadius(6);
    legend2.setOrigin(6,6);
    legend2.setPosition(500, 150);
    legend2.setFillColor(sf::Color(196, 24, 47));

    



    sf::Event event;
    bool hideG = false;
    bool hideS = false;


    while(window.isOpen()) {
        sf::sleep(sf::milliseconds(100));
        window.clear(Color(199, 188, 187));
        window.draw(xAxis);
        window.draw(yAxis);
         
        while( window.pollEvent(event) ) {
            // if event type corresponds to pressing window X or q or esecape

            if(event.type == Event::Closed) {
                // tell the window to close
                window.close();
            }
            // check addition event types to handle additional events
        
            
            if(event.type == Event::KeyPressed){
                // close key events
                if (event.key.scancode == sf::Keyboard::Scan::Q || event.key.scancode == sf::Keyboard::Scan::Escape)
                {
                    window.close();
                }
                if (event.key.scancode == sf::Keyboard::Scan::G )
                {
                    if(!hideG)
                        hideG = true;
                    else
                        hideG = false;
                }
                if (event.key.scancode == sf::Keyboard::Scan::S )
                {   
                    if(!hideS)
                        hideS = true;
                    else
                        hideS = false;
                }

            }
        }
        //cheaks to hide s
        if(!hideS){
            //displays s
            for(unsigned int i = 0; i< textS.size(); i++){
                window.draw(textS.at(i));
            }
            SProbabilitys.draw(window);
        
        }
        //cheaks to hide g
        if (!hideG){
            //displays g
            for(unsigned int i = 0; i< textG.size(); i++){
                window.draw(textG.at(i));
            }
            GProbabilitys.draw(window);
        }
        for(unsigned int i = 0; i< textExtra.size(); i++){
            //displays lables
                window.draw(textExtra.at(i));
            }
        //draws legends
        window.draw(legend1);
        window.draw(legend2);

        window.display();
    }
 
    return 0;
}