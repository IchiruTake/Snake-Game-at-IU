#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <windows.h>
/* Tutorial: https://www.sfml-dev.org/tutorials/2.5/ */
using namespace sf;

int N = 60 ,M = 45; 		         //The Array Matrix that contain Height = 60 blocks --- Width = 45 blocks
int size = 16; 			     	     //Square Pixel Width x Height (images included in nearby folder) --- Constant data 
int w = size*N;				        //Width (w) shows the number of pixel available (= size x N)
int h = size*M;				        //Height (h) shows the number of pixel available (= size x M)      
int Number_of_obstacle = 4;         //The number of obstacle is initialize at 4 
int Load = 0;                      //Load is initialize at 0
float timer = 0, delay = 0.2;

int dir, score = 0; 					        //dir = Direction - Left = 1; Right = 2; Up = 3; Down = 0, intitialize score = 0 
int Snake_Length = 4; 		                   //Snake_Length = Length of the Snake 

struct snake {int x, y;}  Snake[100];          //Make object named Snake with two data shows position (x, y) and set it as array

struct Fruit {int x, y;}  Food;		          //Make object named Food with two data shows position (x, y)

struct obstacle {int x, y;}  Obstacle[100];  //Make object named obstacle with two data shows position (x, y) and set it as array

struct achievements {char name; int score;} Gamers[1000];   //Make object named achievements with 2 data shows name and score and set it as array 

void Tick()
{
    //Snake Movement Algorithm for the whole body -- Starting from its tails
	for (int i=Snake_Length; i > 0 ; --i)
    {
		Snake[i].x=Snake[i-1].x; 
		Snake[i].y=Snake[i-1].y;
	}
	
	// Snake Movement Algorithm for the head movement
    if (dir==0) Snake[0].y+=1;      
    if (dir==1) Snake[0].x-=1;        
    if (dir==2) Snake[0].x+=1;         
    if (dir==3) Snake[0].y-=1;   
	
	// If Snake eats Food
    if ((Snake[0].x==Food.x) && (Snake[0].y==Food.y)) 
    {
		Snake_Length = Snake_Length + 1; 	//Increment the Snake's Length by 1
		score = score + 5;
		Food.x = rand() % N; 			 	//Set up new position for food at x-axis
		Food.y = (rand() % M) + 2;				//Set up new position for food at y-axis
	}
	
	// If Snake overpass the wall -- Give him available at the other size (for Easy mode)
    if (Snake[0].x>N-1) Snake[0].x=0;  if (Snake[0].x<0) Snake[0].x=N-1;
    if (Snake[0].y>M-1) Snake[0].y=2;  if (Snake[0].y<2) Snake[0].y=M-1;
    
    //Making obstacle 
    //for (i = 0; i < Number_of_obstacle; i++) {Obstacle[i].x = rand() %N; Obstacle[i].y = (rand() %M) +2;}
    
    //Snake dies when
    //for (i = 0; i < Number_of_obstacle; i++)
//{
		//if (Snake[0].x == Obstacle[i].x && Snake[0].y == Obstacle[i].y) {window.clear; "you are dead",  Gamers[Load].score = score; Load = Load + 1; delay = 10000;		}
//}
//for (i = 0; i < Snake_Length; i++)
//	{
	//	if (Snake[0].x == Snake_Length[i].x && Snake[0].y == Snake_Length[i].y) {window.clear; "you are dead", Gamers[Load].score = score; Load = Load + 1; delay = 10000;		}
//	}
 
   
}

int main()
{  
    srand(time(0)); //Seed the random 

    RenderWindow window(VideoMode(w, h), "Snake Game!"); // Make usable file

    Texture t1, t2, t3; 								//Set texture t1 and t2. 
    t1.loadFromFile("images/white.png");			//t1 = Images by loading with file 'white.png'
    t2.loadFromFile("images/red.png");				//t2 = Images by loading with file 'red.png'
    t3.loadFromFile("images/green.png");            //t3 = Images by loading with file 'green.png'

    Sprite sprite1(t1);								//Denote by sprite1(t1) 			
    Sprite sprite2(t2);								//Denote by sprite2(t2)
    Sprite sprite3(t3);                             //Denote by sprite3(t3)

    Clock clock;                                   //Change name 'Clock' = clock
	float timer = 0, delay = 0.1;	               //Count time by timer and set delay. Delay (s) will determined the speed of Snake. Small 'delay' variable causes the Snake moving faster, vice versa
	float temp = delay;
    int Real_Time_Count = 0;
    Food.x = 10; Food.y = 10;                      //Initial position for the food (applicable once only)
										
    
    while (window.isOpen())                        //Running the file and keep open
    
    
    {
        float time = clock.getElapsedTime().asSeconds();            //Take the Elapsed Time value (s) and assign to 'time' variable
        clock.restart();
        timer = timer + time;                                       // Increment the 'timer' by time 

        Event e; 	                                                //Set the Event and name as e
        while (window.pollEvent(e)) //Doing event consequently
        {
            if (e.type == Event::Closed)      window.close();       //Close the window
            if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::R)) {Snake[0].x = 0; Snake[0].y = 2; score = 0; dir = 0;}
			}
            
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;     //If pressing left, set dir = 1 and keeps 'dir' not keeps turning Left (keep the Snake move to the Left at the time press Left)
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2;    //If pressing Right, set dir = 2 and keeps 'dir' not keeps turning Right (keep the Snake move to the Left at the time press Right)
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;	  	 //If pressing Up, set dir = 3 and keeps 'dir' not keeps turning Up (keep the Snake move to the Left at the time press Up)
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0; 	 //If pressing Down, set dir = 0 and keeps 'dir' not keeps turning Down (keep the Snake move to the Left at the time press Down)

        if (Keyboard::isKeyPressed(Keyboard::P)) {delay = 10000;}
		if (Keyboard::isKeyPressed(Keyboard::C)) {delay = temp;}
		if (timer > delay) {timer = 0; Tick();}                                                          //When timer > delay, reconstruct the 'timer' variable to zero and do 'Tick' function where Snake can move
		if (timer > delay) {timer = 0; Real_Time_Count = Real_Time_Count + 1; Tick();}                  //When timer > delay, reconstruct the 'timer' variable to zero and do 'Tick' function where Snake can move
		if (Real_Time_Count >= 300) {delay = 9* delay / 10; temp = delay; Real_Time_Count = 0;	}       //Each 30s passed, the speed is increased
        

   	// ----- DRAWING THE WINDOW ----//
    window.clear();                                                            //Clean the window
    
	Text text ; 
	char scoreString[1000];
	itoa(score, scoreString, 10);                    //convert score from char to string 
	
    for (int i = 0; i < N; i++) 
      for (int j = 0; j < M; j++) 
        { sprite1.setPosition(i*size, j*size);  window.draw(sprite1); }                              //Drawing the Map for Snake's movement with image = white.png, denote at sprite1
    for (int i = 0; i < N; i++)
    	for(int j = 0; j < 2; j++)
    	{ sprite3.setPosition(i*size, j*size);  window.draw(sprite3); }                              //Drawing the space for score 
    for (int i=0; i<Number_of_obstacle;i++)
   	{sprite3.setPosition( Obstacle[i].x*size, Obstacle[i].y*size); window.draw(sprite3);}                //Drawing the obstacle
    for (int i=0;i<Snake_Length;i++)
        { sprite2.setPosition(Snake[i].x*size, Snake[i].y*size);  window.draw(sprite2); }            //Drawing the Snake with image = red.png, denote at sprite2
   
    sprite2.setPosition(Food.x*size, Food.y*size);  window.draw(sprite2);                             //Drawing the Snake with image = red.png, denote at sprite2
	
	//SFML:: Window:: FullScreen
	
    window.display(); // Show the screen
    }

    return 0;
}
