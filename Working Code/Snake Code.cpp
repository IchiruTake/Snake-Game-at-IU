#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctime>
#include <iostream>

/* Tutorial: https://www.sfml-dev.org/tutorials/2.5/ */
using namespace sf; using namespace std;
//Snake's Map
int Space = 4;
int N = 75, M = 45; 		         		//The Snake's Map that contain Height = 60 blocks --- Width = 45 blocks
int size = 16; 			     	     		//Square Pixel: Width x Height (images included in nearby folder) --- Constant data 
int Width = size * N;				        //Width (w) shows the number of pixel available (= size x N)
int Height = size * (M + Space);				//Height (h) shows the number of pixel available (= size x M)      

//Obstacle
int ObstacleNumber = 10; int ObstacleCount = 1;        		
float ObstacleDuration, ObstacleRealTime; 

//Player
int PlayerNumber = 0; int scoreTemporary;       //Number of player who played game (initial)
float delay; int Structable = 0;

//Snake
int dir = 0; int score = 0; 					        //dir = Direction - Left = 1; Right = 2; Up = 3; Down = 0, intitialize score = 0 
int Snake_Length = 1; 		                   	//Snake_Length = Length of the Snake 

//Structing class
struct snake {int x, y;}  Snake[100], Snake_2[100];          				//Make object named Snake 			with two data shows position (x, y) and set it as array
struct Fruit {int x, y;}  Food; int FoodChoice;				//Make object named Food 			with two data shows position (x, y)
struct obstacle {int x, y;}  Obstacle[100];  				//Make object named obstacle 		with two data shows position (x, y) and set it as array
struct achievements {char name[100] ; int score;} Player[1000], Player_2[1000]; int n;   //Make object named achievements	with two data shows name and score and set it as array 

//Compulsory
Window window0, window, window1; Font font; 
String playerInput; Text playerText;
Texture t12; int RestartStatus = 0;
float RealTime;

//Music
Music music;
float MusicDuration, EndingMusicTime;
int MusicChoice, MusicStatus;

//Function
void GUI();
void SingleEasy(); void SingleHard();
void DoubleEasy(); void DoubleHard();

// Snake #2
int dir_2 = 0; int Snake_Length_2 = 1; int score_2 = 0;

void EasyMode ()
{
	//Snake Movement Algorithm for the whole body -- Starting from its tails
	for (int i = Snake_Length; i > 0 ; --i)
    {
		Snake[i].x = Snake[i-1].x; 
		Snake[i].y = Snake[i-1].y;
	}
	// Snake Movement Algorithm for the head movement
    if (dir == 0) Snake[0].y += 1;      if (dir == 1) Snake[0].x -= 1;        
	if (dir == 2) Snake[0].x += 1;      if (dir == 3) Snake[0].y -= 1;   
	// If Snake eats Food
	if ((Snake[0].x == Food.x) && (Snake[0].y == Food.y)) 
    {
		if (FoodChoice == 1) {score = score + 2;}  		//Apple
		if (FoodChoice == 2) {score = score + 5;}		//Melon
		if (FoodChoice == 3) {score = score + 10;} 		//Strawberry
		
		Snake_Length = Snake_Length + 1; 		//Increment the Snake's Length by 1
		Food.x = rand() % N; 			 		//Set up new position for food at x-axis
		Food.y = rand() % M + Space;			//Set up new position for food at y-axis
		// Setting the next food
		FoodChoice = rand() % 3 + 1;
		if (FoodChoice == 1) {t12.loadFromFile("Images/Fruit/Apple.png"); 		Sprite sprite12(t12);}  	//Apple
		if (FoodChoice == 2) {t12.loadFromFile("Images/Fruit/Melon.png"); 		Sprite sprite12(t12);}		//Melon
		if (FoodChoice == 3) {t12.loadFromFile("Images/Fruit/Strawberry.png"); 	Sprite sprite12(t12);} 		//Strawberry
	}
	//If Snake Passed Wall -- Give him available at the other size (for Easy Mode)
    if (Snake[0].x > N - 1) 			Snake[0].x = 0;  
	if (Snake[0].x < 0) 				Snake[0].x = N - 1;
    if (Snake[0].y > M - 1 + Space) 	Snake[0].y = Space;  
	if (Snake[0].y < Space) 			Snake[0].y = M - 1 + Space;	
}
void HardMode()
{
	//Snake Movement Algorithm for the whole body -- Starting from its tails
	for (int i = Snake_Length; i > 0 ; --i)
    {
		Snake[i].x = Snake[i-1].x; 
		Snake[i].y = Snake[i-1].y;
	}
	// Snake Movement Algorithm for the head movement
    if (dir == 0) Snake[0].y += 1;      if (dir == 1) Snake[0].x -= 1;        
	if (dir == 2) Snake[0].x += 1;      if (dir == 3) Snake[0].y -= 1;   
	// If Snake eats Food
	if ((Snake[0].x == Food.x) && (Snake[0].y == Food.y)) 
    {
		if (FoodChoice == 1) {score = score + 2;}  		//Apple
		if (FoodChoice == 2) {score = score + 5;}		//Melon
		if (FoodChoice == 3) {score = score + 10;} 		//Strawberry
		
		Snake_Length = Snake_Length + 1; 		//Increment the Snake's Length by 1
		Food.x = rand() % N; 			 		//Set up new position for food at x-axis
		Food.y = rand() % M + Space;				//Set up new position for food at y-axis
		// Setting the next food
		FoodChoice = rand() % 3 + 1;
		if (FoodChoice == 1) {t12.loadFromFile("Images/Fruit/Apple.png"); 		Sprite sprite12(t12);}  	//Apple
		if (FoodChoice == 2) {t12.loadFromFile("Images/Fruit/Melon.png"); 		Sprite sprite12(t12);}		//Melon
		if (FoodChoice == 3) {t12.loadFromFile("Images/Fruit/Strawberry.png"); 	Sprite sprite12(t12);} 		//Strawberry
	}
}
void ObstacleDelete() 
{
	for (int i = 0; i < ObstacleNumber; i++)
	{
		Obstacle[i].x = - 1; 
		Obstacle[i].y = - 1; 
	}	
	ObstacleNumber = ObstacleNumber + 5;
}
void MusicPlay()
{
	if (MusicChoice == 1) {music.openFromFile("Music/Move Your Body - Ria - Alan Walker Remix.wav"); music.play(); MusicStatus = 1; music.setLoop(false); EndingMusicTime = 311;	}
	if (MusicChoice == 2) {music.openFromFile("Music/Fade (Hell's Speaker Remix) Ft. Isabel Park - Alan Walker inspired.wav"); music.play(); MusicStatus = 1; music.setLoop(false); EndingMusicTime = 234;}
	if (MusicChoice == 3) {music.openFromFile("Music/N30N - Speed Nightcore.wav"); music.play(); MusicStatus = 1; music.setLoop(false); EndingMusicTime = 136;	}
	if (MusicChoice == 4) {music.openFromFile("Music/Khau thi tam phi Remix.wav"); music.play(); MusicStatus = 1; music.setLoop(false); EndingMusicTime = 316;	}
	if (MusicChoice == 5) {music.openFromFile("Music/Two Steps From Hell - Victory.wav"); music.play(); MusicStatus = 1; music.setLoop(false); EndingMusicTime = 328;	}
	if (MusicChoice == 6) {music.openFromFile("Music/Unknown Name.wav"); music.play(); MusicStatus = 1; music.setLoop(false); EndingMusicTime = 206;	}
}

void Restart() 	
{
	Snake[0].x = 0; Snake[0].y = Space; score = 0; dir = 0; 
	Snake_2[0].x = 1; Snake_2[0].y = Space; score_2 = 0; dir_2 = 0;
	Food.x = (N - 1) / 2; Food.y = (M - 1 + Space) / 2;
	ObstacleDelete(); ObstacleNumber = 10;  
}

void SingleEasy()
{  
    char nameTemporary[100];
	srand(time(0)); //Seed the random 

    RenderWindow window(VideoMode(Width, Height), "Snake Game!"); // Make usable file
	window.setVerticalSyncEnabled(true);	
    Texture t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; 						//Set texture t0 -> t13 and convert into sprite 
    t0.loadFromFile("Images/Obstacle.png"); 					Sprite sprite0(t0);				//t0 = Obstacle
	t1.loadFromFile("Images/Snake_Map.png"); 					Sprite sprite1(t1);				//t1 = Snake's Map
    t2.loadFromFile("Images/Play_Background.png");				Sprite sprite2(t2);				//t2 = Play _Background used for printing status
	// Snake
	t3.loadFromFile("Images/Snake/Snake_Head_Left.png");		Sprite sprite3(t3);	
    t4.loadFromFile("Images/Snake/Snake_Tail_Left.png");		Sprite sprite4(t4);	
    t5.loadFromFile("Images/Snake/Snake_Head_Right.png");		Sprite sprite5(t5);
    t6.loadFromFile("Images/Snake/Snake_Tail_Right.png");		Sprite sprite6(t6);
	t7.loadFromFile("Images/Snake/Snake_Head_Up.png");			Sprite sprite7(t7);
    t8.loadFromFile("Images/Snake/Snake_Tail_Up.png");			Sprite sprite8(t8);
	t9.loadFromFile("Images/Snake/Snake_Head_Down.png");		Sprite sprite9(t9);	
    t10.loadFromFile("Images/Snake/Snake_Tail_Down.png");		Sprite sprite10(t10);		  
	t11.loadFromFile("Images/Snake/Snake_Body.png");			Sprite sprite11(t11);
	//Food beginning
	t12.loadFromFile("Images/Fruit/Apple.png"); 				Sprite sprite12(t12);
	FoodChoice = rand() % 3 + 1;	
	
    //Count time by timer and set delay. Delay (s) will determined the speed of Snake. Small 'delay' variable causes the Snake moving faster, vice versa
	Clock clock;
	float timer = 0, delay = 0.2;	          
	float temp = delay;
    //Initialize
	float SpeedIncrease; 					//Buff Speed 
	Restart();                //Initial position for the food and Snake (applicable once only)   
	
	String playerInput; Text playerText; 
	 				
    while (window.isOpen())                       					 //Running the file and keep open
    {
        float time = clock.getElapsedTime().asSeconds();            //Take the Elapsed Time value (s) and assign to 'time' variable
        clock.restart();
        timer = timer + time;                                       //Increment the 'timer' by time 
		SpeedIncrease = SpeedIncrease + time;						//Increment the 'SpeedIncrease' by time 			
		ObstacleRealTime = ObstacleRealTime + time;					//Increment the 'ObstacleRealTime' by time 	
		MusicDuration = MusicDuration + time;						//Increment the 'MusicDuration' by time 
		RealTime = RealTime + time;									//Counting timeplay
		
		Text text4, text5, text7; 	//GameStatus & Music Status
		if (MusicStatus == 0) {text4.setString("PAUSED");	}
		else if (MusicStatus == 1) {text4.setString("PLAYED");	}
		if (delay > 1000) {text7.setString("PAUSED");}
		else {text7.setString("PLAYED");}
        Event e; 													//Set the Event and name as e       
		
		if (RestartStatus == 0) {Restart(); RestartStatus = 1;}                         
        while (window.pollEvent(e)) //Doing event consequently
        {
			if (e.type == Event::Closed) {window.close();}      //Close the window
            if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {window.close(); GUI();				}
				//Reset game and music
				if (Keyboard::isKeyPressed(Keyboard::R))	
				{music.play();  MusicStatus = 1; text4.setString("PLAYED"); Restart(); text7.setString("PLAYED");}  
				//Game Status
				if (Keyboard::isKeyPressed(Keyboard::G) and Keyboard::isKeyPressed(Keyboard::A))
				{delay = 10000; text7.setString("PAUSED");}  	//pause the game
				if (Keyboard::isKeyPressed(Keyboard::G) and Keyboard::isKeyPressed(Keyboard::L))
				{delay = temp; text7.setString("PLAYED");}
				//Music
				if (Keyboard::isKeyPressed(Keyboard::M) and Keyboard::isKeyPressed(Keyboard::A)) {music.pause(); MusicStatus = 0; text4.setString("PAUSED"); }						//pause the music
				if (Keyboard::isKeyPressed(Keyboard::M) and Keyboard::isKeyPressed(Keyboard::L)) {music.play();  MusicStatus = 1; text4.setString("PLAYED");}						//continue playing music
			}  
        }
		//Pressing and Snake's Movement
        if (Keyboard::isKeyPressed(Keyboard::Left)) 	dir = 1;     //If pressing left, set dir = 1 and keeps 'dir', not keeps turning Left (keep the Snake move to the Left at the time press Left)
        if (Keyboard::isKeyPressed(Keyboard::Right)) 	dir = 2;     //If pressing Right, set dir = 2 and keeps 'dir', not keeps turning Right (keep the Snake move to the Left at the time press Right)
        if (Keyboard::isKeyPressed(Keyboard::Up)) 		dir = 3;	 //If pressing Up, set dir = 3 and keeps 'dir', not keeps turning Up (keep the Snake move to the Left at the time press Up)
        if (Keyboard::isKeyPressed(Keyboard::Down)) 	dir = 0; 	 //If pressing Down, set dir = 0 and keeps 'dir', not keeps turning Down (keep the Snake move to the Left at the time press Down)
		if (timer > delay) 	{timer = 0; EasyMode();}             	 //When timer > delay, reconstruct the 'timer' variable to zero and do 'Tick' function where Snake can move
		
		if (SpeedIncrease >= 20) //Each 20s passed, the speed is increased by 5% from its value and reset SpeedIncrease	
		{delay = 95 * delay / 100; temp = delay; SpeedIncrease = 0;	}     
        //Music
        if (MusicDuration > EndingMusicTime) {MusicChoice = rand() % 6 + 1; MusicPlay(); MusicDuration = 0;} // Reset Music
        if (MusicChoice == 1) {text5.setString("Move Your Body - Ria - Alan Walker Remix");}
        if (MusicChoice == 2) {text5.setString("Fade (Hell's Speaker Remix) Ft. Isabel Park - Alan Walker inspired");}
        if (MusicChoice == 3) {text5.setString("N30N - Speed Nightcore");}
		if (MusicChoice == 4) {text5.setString("Khau thi tam phi Remix");}
		if (MusicChoice == 5) {text5.setString("Two Steps From Hell - Victory");}
		if (MusicChoice == 6) {text5.setString("Unknown Name");}
        
   	
	// ----- DRAWING THE WINDOW ----//
    	window.clear();                              //Clean the window
		//--- Drawing the Snake's Map ---
   		for (int i = 0; i < N; i++) 
      		for (int j = 0; j < M; j++) 
        		{ sprite1.setPosition(i*size, (j + Space)*size);  window.draw(sprite1); }
    	//--- Drawing the empty place for printing status
		for (int i = 0; i < N; i++)
    		for(int j = 0; j < Space; j++)
    			{ sprite2.setPosition(i*size, j*size);  window.draw(sprite2); }                 
    
		//---Drawing the Snake---
		if (dir == 1) //Left
    	{	
			sprite3.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite3);
			if (Snake_Length > 1) {sprite4.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite4);}
		}
		if (dir == 2) //Right
    	{
			sprite5.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite5);
			if (Snake_Length > 1) {sprite6.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite6);}
		}
		if (dir == 3) //Up
    	{
			sprite7.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite7);
			if (Snake_Length > 1) {sprite8.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite8);}
		}
		if (dir == 0) //Down
    	{
			sprite9.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite9);
			if (Snake_Length > 1) {sprite10.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite10);	}	
		}
		for (int i = 1;i < Snake_Length - 1;i++)
        {sprite11.setPosition(Snake[i].x*size, Snake[i].y*size);  window.draw(sprite11);} 
   		
		//--- Drawing Food --- 
    	sprite12.setPosition(Food.x*size, Food.y*size);  window.draw(sprite12);                             
		//--- Drawing Obstacles ---
		if (ObstacleRealTime > 15)
		{
			if (ObstacleCount == 1)
			{
				for (int i = 0; i < ObstacleNumber; i++)
				{		
					Obstacle[i].x = rand() % N; 
					Obstacle[i].y = rand() % M + Space; 
				}
			}
			for (int i = 0; i < ObstacleNumber; i++) {	sprite0.setPosition( Obstacle[i].x*size, Obstacle[i].y*size); window.draw(sprite0); }  
			ObstacleCount = 0; ObstacleDuration = ObstacleDuration + time;
			if (ObstacleDuration > 20)	{ObstacleRealTime = 0; ObstacleDuration = 0; ObstacleCount = 1; ObstacleDelete(); } //20 seconds on and off
		}
	
		//Print the text 
		Text text0, text1, text2, text3, text6, text8; font.loadFromFile("Images/Times-New-Romans.ttf");
	
		text0.setFont(font); 			text0.setString("Score:");
		text0.setCharacterSize(16); 	text0.setFillColor(Color::White);
		text0.setStyle(Text::Bold); 	text0.setPosition(2, 4); 
		window.draw(text0);	
		char scoreString[1000]; 		itoa(score, scoreString, 10);                    //convert score from char to string
		text1.setFont(font); 			text1.setString(scoreString);
		text1.setCharacterSize(16); 	text1.setFillColor(Color::White);
		text1.setStyle(Text::Bold); 	text1.setPosition(55, 4); 
		window.draw(text1);	
	
		text3.setFont(font); 			text3.setString("Music's Status:                 - Music: ");
		text3.setCharacterSize(16); 	text3.setFillColor(Color::White);
		text3.setStyle(Text::Bold); 	text3.setPosition(2, 24); 
		window.draw(text3);	
		text4.setFont(font); 			
		text4.setCharacterSize(16); 	text4.setFillColor(Color::White);
		text4.setStyle(Text::Bold); 	text4.setPosition(125, 24); 
		window.draw(text4);	
		text5.setFont(font); 			
		text5.setCharacterSize(16); 	text5.setFillColor(Color::White);
		text5.setStyle(Text::Bold); 	text5.setPosition(270, 24); 
		window.draw(text5);	
	
		text6.setFont(font); 			text6.setString("Game Mode: Single Easy - Status: ");
		text6.setCharacterSize(16); 	text6.setFillColor(Color::White);
		text6.setStyle(Text::Bold); 	text6.setPosition(2, 44); 
		window.draw(text6);	
		text7.setFont(font); 			
		text7.setCharacterSize(16); 	text7.setFillColor(Color::White);
		text7.setStyle(Text::Bold); 	text7.setPosition(265, 44); 
		window.draw(text7);
	
    	window.display(); // Show the screen
    	
    	//Dead if violating
    	for (int i = 0; i < ObstacleNumber; i++)
    	{
    		if ( (Snake[0].x == Obstacle[i].x) && (Snake[0].y == Obstacle[i].y) )
    		{
    			delay = 20000; Player[PlayerNumber].score = score;
				window.close();		
			}
		}  	
    }
    
	//Sorting achievement
	PlayerNumber = PlayerNumber + 1;
	for (int i = 0; i < PlayerNumber; i++)
	{
		for (int j = 0; j < PlayerNumber - 1; j++)
		{
			if (Player[j].score < Player[j+1].score)
			{
				scoreTemporary = Player[j+1].score;
				Player[j+1].score = Player[j].score;
				Player[j].score = scoreTemporary;
				
				strcpy(nameTemporary, Player[j+1].name);
				strcpy(Player[j+1].name, Player[j].name);
				strcpy(Player[j].name, nameTemporary);
			}
		}
	}
	RenderWindow window1(VideoMode(Width, Height), "Snake Game!"); 
	while (window1.isOpen())
	{
		window1.clear();
		Event e;
		while (window1.pollEvent(e)) //Doing event consequently
        {
			if (e.type == Event::Closed) {window1.close();}     //Close the window
            if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {GUI(); window1.close();}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::E))
				{ 
					window1.close(); Restart(); SingleEasy();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::H))
				{ 
					window1.close(); Restart(); SingleHard();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::E))
				{ 
					window1.close(); Restart(); DoubleEasy();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::H))
				{ 
					window1.close(); Restart(); DoubleHard();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
				}	
			}          
        }
        for (int i = 0; i < N; i++)
    		for (int j = 0; j < M + Space; j++)
    			{ sprite2.setPosition(i*size, j*size);  window1.draw(sprite2); } 
		char Counter[1000], Score_Temporary[1000];
		//---Drawing the map ---	
		Text text10, text11, text12, text13, text14; font.loadFromFile("Images/Times-New-Romans.ttf");
		text10.setFont(font); 			text10.setString("You have completed the game \nS+E = Single Easy Mode; S+H = Single Hard Mode; \nD+E = Double Easy Mode; D+H = Double Hard Mode; \nEsc = Return");
		text10.setCharacterSize(40); 	text10.setFillColor(Color::Red);
		text10.setStyle(Text::Bold); 	text10.setPosition(100, 25); 
		window1.draw(text10);
		text10.setFont(font); 			text10.setString("-----------------------------------------");
		text10.setCharacterSize(48); 	text10.setFillColor(Color::Red);
		text10.setStyle(Text::Bold); 	text10.setPosition(50, 200); 
		window1.draw(text10);	
		for (int i = 0; i < PlayerNumber; i++)
		{
			itoa((i + 1), Counter, 10);
			text11.setFont(font); 			text11.setString(Counter);
			text11.setCharacterSize(32); 	text11.setFillColor(Color::Red);
			text11.setStyle(Text::Bold); 	text11.setPosition(150, 220 + (i+1)*32);
			window1.draw(text11);

			text12.setFont(font); 			text12.setString(Player[i].name);
			text12.setCharacterSize(32); 	text12.setFillColor(Color::Red);
			text12.setStyle(Text::Bold); 	text12.setPosition(220, 220 + (i+1)*32);
			window1.draw(text12);
				
			itoa(Player[i].score, Score_Temporary, 10);
			text13.setFont(font); 			text13.setString(Score_Temporary);
			text13.setCharacterSize(32); 	text13.setFillColor(Color::Red);
			text13.setStyle(Text::Bold); 	text13.setPosition(450, 220 + (i+1)*32);
			window1.draw(text13);		
		}
		window1.display();			
	}    		
}

void SingleHard()
{
	char nameTemporary[100];
	srand(time(0)); //Seed the random 

    RenderWindow window(VideoMode(Width, Height), "Snake Game!"); // Make usable file
	window.setVerticalSyncEnabled(true);	
    Texture t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; 						//Set texture t0 -> t13 and convert into sprite 
    t0.loadFromFile("Images/Obstacle.png"); 					Sprite sprite0(t0);				//t0 = Obstacle
	t1.loadFromFile("Images/Snake_Map.png"); 					Sprite sprite1(t1);				//t1 = Snake's Map
    t2.loadFromFile("Images/Play_Background.png");				Sprite sprite2(t2);				//t2 = Play _Background used for printing status
	// Snake
	t3.loadFromFile("Images/Snake/Snake_Head_Left.png");		Sprite sprite3(t3);	
    t4.loadFromFile("Images/Snake/Snake_Tail_Left.png");		Sprite sprite4(t4);	
    t5.loadFromFile("Images/Snake/Snake_Head_Right.png");		Sprite sprite5(t5);
    t6.loadFromFile("Images/Snake/Snake_Tail_Right.png");		Sprite sprite6(t6);
	t7.loadFromFile("Images/Snake/Snake_Head_Up.png");			Sprite sprite7(t7);
    t8.loadFromFile("Images/Snake/Snake_Tail_Up.png");			Sprite sprite8(t8);
	t9.loadFromFile("Images/Snake/Snake_Head_Down.png");		Sprite sprite9(t9);	
    t10.loadFromFile("Images/Snake/Snake_Tail_Down.png");		Sprite sprite10(t10);		  
	t11.loadFromFile("Images/Snake/Snake_Body.png");			Sprite sprite11(t11);
	//Food beginning
	t12.loadFromFile("Images/Fruit/Apple.png"); 				Sprite sprite12(t12);
	FoodChoice = rand() % 3 + 1;	
	
    //Count time by timer and set delay. Delay (s) will determined the speed of Snake. Small 'delay' variable causes the Snake moving faster, vice versa
	Clock clock;
	float timer = 0, delay = 0.1;	          
	float temp = delay;
    //Initialize
	float SpeedIncrease; 					//Buff Speed
    Snake[0].x = 0; Snake[0].y = Space; score = 0; dir = 0; 
	Restart();                //Initial position for the food and Snake (applicable once only)   
	
	String playerInput; Text playerText; 
	 				
    while (window.isOpen())                       					 //Running the file and keep open
    {
        float time = clock.getElapsedTime().asSeconds();            //Take the Elapsed Time value (s) and assign to 'time' variable
        clock.restart();
        timer = timer + time;                                       //Increment the 'timer' by time 
		SpeedIncrease = SpeedIncrease + time;						//Increment the 'SpeedIncrease' by time 			
		ObstacleRealTime = ObstacleRealTime + time;					//Increment the 'ObstacleRealTime' by time 	
		MusicDuration = MusicDuration + time;						//Increment the 'MusicDuration' by time 
		RealTime = RealTime + time;									//Counting timeplay
		
		Text text4, text5, text7; 	//GameStatus & Music Status
		if (MusicStatus == 0) {text4.setString("PAUSED");	}
		else if (MusicStatus == 1) {text4.setString("PLAYED");	}
		if (delay > 1000) {text7.setString("PAUSED");}
		else {text7.setString("PLAYED");}
        Event e; 													//Set the Event and name as e          
		if (RestartStatus == 0) {Restart(); RestartStatus = 1;}                           
        while (window.pollEvent(e)) //Doing event consequently
        {
			if (e.type == Event::Closed) {window.close();}      //Close the window
            if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {window.close(); GUI();				}
				//Reset game and music
				if (Keyboard::isKeyPressed(Keyboard::R))	
				{music.play();  MusicStatus = 1; text4.setString("PLAYED"); Restart(); text7.setString("PLAYED");}  
				//Game Status
				if (Keyboard::isKeyPressed(Keyboard::G) and Keyboard::isKeyPressed(Keyboard::A))
				{delay = 10000; text7.setString("PAUSED");}  	//pause the game
				if (Keyboard::isKeyPressed(Keyboard::G) and Keyboard::isKeyPressed(Keyboard::L))
				{delay = temp; text7.setString("PLAYED");}
				//Music
				if (Keyboard::isKeyPressed(Keyboard::M) and Keyboard::isKeyPressed(Keyboard::A)) {music.pause(); MusicStatus = 0; text4.setString("PAUSED"); }						//pause the music
				if (Keyboard::isKeyPressed(Keyboard::M) and Keyboard::isKeyPressed(Keyboard::L)) {music.play();  MusicStatus = 1; text4.setString("PLAYED");}						//continue playing music
			}  
        }
		//Pressing and Snake's Movement
        if (Keyboard::isKeyPressed(Keyboard::Left)) 	dir = 1;     //If pressing left, set dir = 1 and keeps 'dir', not keeps turning Left (keep the Snake move to the Left at the time press Left)
        if (Keyboard::isKeyPressed(Keyboard::Right)) 	dir = 2;     //If pressing Right, set dir = 2 and keeps 'dir', not keeps turning Right (keep the Snake move to the Left at the time press Right)
        if (Keyboard::isKeyPressed(Keyboard::Up)) 		dir = 3;	 //If pressing Up, set dir = 3 and keeps 'dir', not keeps turning Up (keep the Snake move to the Left at the time press Up)
        if (Keyboard::isKeyPressed(Keyboard::Down)) 	dir = 0; 	 //If pressing Down, set dir = 0 and keeps 'dir', not keeps turning Down (keep the Snake move to the Left at the time press Down)
		if (timer > delay) 	{timer = 0; HardMode();}             	 //When timer > delay, reconstruct the 'timer' variable to zero and do 'Tick' function where Snake can move
		
		if (SpeedIncrease >= 20) //Each 20s passed, the speed is increased by 10% from its value and reset SpeedIncrease	
		{delay = 90 * delay / 100; temp = delay; SpeedIncrease = 0;	}     
        //Music
        if (MusicDuration > EndingMusicTime) {MusicChoice = rand() % 6 + 1; MusicPlay(); MusicDuration = 0;} // Reset Music
        if (MusicChoice == 1) {text5.setString("Move Your Body - Ria - Alan Walker Remix");}
        if (MusicChoice == 2) {text5.setString("Fade (Hell's Speaker Remix) Ft. Isabel Park - Alan Walker inspired");}
        if (MusicChoice == 3) {text5.setString("N30N - Speed Nightcore");}
		if (MusicChoice == 4) {text5.setString("Khau thi tam phi Remix");}
		if (MusicChoice == 5) {text5.setString("Two Steps From Hell - Victory");}
		if (MusicChoice == 6) {text5.setString("Unknown Name");}
        
   	
	// ----- DRAWING THE WINDOW ----//
    	window.clear();                              //Clean the window
		//--- Drawing the Snake's Map ---
   		for (int i = 0; i < N; i++) 
      		for (int j = 0; j < M; j++) 
        		{ sprite1.setPosition(i*size, (j + Space)*size);  window.draw(sprite1); }
    	//--- Drawing the empty place for printing status
		for (int i = 0; i < N; i++)
    		for(int j = 0; j < Space; j++)
    			{ sprite2.setPosition(i*size, j*size);  window.draw(sprite2); }                 
    
		//---Drawing the Snake---
		if (dir == 1) //Left
    	{	
			sprite3.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite3);
			if (Snake_Length > 1) {sprite4.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite4);}
		}
		if (dir == 2) //Right
    	{
			sprite5.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite5);
			if (Snake_Length > 1) {sprite6.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite6);}
		}
		if (dir == 3) //Up
    	{
			sprite7.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite7);
			if (Snake_Length > 1) {sprite8.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite8);}
		}
		if (dir == 0) //Down
    	{
			sprite9.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite9);
			if (Snake_Length > 1) {sprite10.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite10);	}	
		}
		for (int i = 1; i < Snake_Length - 1;i++)
        {sprite11.setPosition(Snake[i].x*size, Snake[i].y*size);  window.draw(sprite11);} 
   		
		//--- Drawing Food --- 
    	sprite12.setPosition(Food.x*size, Food.y*size);  window.draw(sprite12);                             
		//--- Drawing Obstacles ---
		if (ObstacleRealTime > 15)
		{
			if (ObstacleCount == 1)
			{
				for (int i = 0; i < ObstacleNumber; i++)
				{		
					Obstacle[i].x = rand() % N; 
					Obstacle[i].y = rand() % M + Space; 
				}
			}
			for (int i = 0; i < ObstacleNumber; i++) {	sprite0.setPosition( Obstacle[i].x*size, Obstacle[i].y*size); window.draw(sprite0); }  
			ObstacleCount = 0; ObstacleDuration = ObstacleDuration + time;
			if (ObstacleDuration > 30)	{ObstacleRealTime = 0; ObstacleDuration = 0; ObstacleNumber = ObstacleNumber + 10; ObstacleCount = 1; ObstacleDelete(); } //20 seconds on and off
		}
	
		//Print the text 
		Text text0, text1, text2, text3, text6, text8; font.loadFromFile("Images/Times-New-Romans.ttf");
	
		text0.setFont(font); 			text0.setString("Score:");
		text0.setCharacterSize(16); 	text0.setFillColor(Color::White);
		text0.setStyle(Text::Bold); 	text0.setPosition(2, 4); 
		window.draw(text0);	
		char scoreString[1000]; 		itoa(score, scoreString, 10);                    //convert score from char to string
		text1.setFont(font); 			text1.setString(scoreString);
		text1.setCharacterSize(16); 	text1.setFillColor(Color::White);
		text1.setStyle(Text::Bold); 	text1.setPosition(55, 4); 
		window.draw(text1);	
	
		text3.setFont(font); 			text3.setString("Music's Status:                 - Music: ");
		text3.setCharacterSize(16); 	text3.setFillColor(Color::White);
		text3.setStyle(Text::Bold); 	text3.setPosition(2, 24); 
		window.draw(text3);	
		text4.setFont(font); 			
		text4.setCharacterSize(16); 	text4.setFillColor(Color::White);
		text4.setStyle(Text::Bold); 	text4.setPosition(125, 24); 
		window.draw(text4);	
		text5.setFont(font); 			
		text5.setCharacterSize(16); 	text5.setFillColor(Color::White);
		text5.setStyle(Text::Bold); 	text5.setPosition(270, 24); 
		window.draw(text5);	
	
		text6.setFont(font); 			text6.setString("Game Mode: Single Hard - Status: ");
		text6.setCharacterSize(16); 	text6.setFillColor(Color::White);
		text6.setStyle(Text::Bold); 	text6.setPosition(2, 44); 
		window.draw(text6);	
		text7.setFont(font); 			
		text7.setCharacterSize(16); 	text7.setFillColor(Color::White);
		text7.setStyle(Text::Bold); 	text7.setPosition(265, 44); 
		window.draw(text7);
	
    	window.display(); // Show the screen
    	
    	//Dead if violating
    	for (int i = 0; i < ObstacleNumber; i++) //Hiting Obstacle
    	{
    		if ( (Snake[0].x == Obstacle[i].x) && (Snake[0].y == Obstacle[i].y) )
    		{
    			delay = 10000; Player[PlayerNumber].score = score;
				window.close();		
			}
		}  	
		for (int i = 1; i < Snake_Length; i++) //Hiting the Snake
    	{
    		if ( (Snake[0].x == Snake[i].x) && (Snake[0].y == Snake[i].y) )
    		{
    			delay = 10000; Player[PlayerNumber].score = score;
				window.close();		
			}
		}  
		if ( (Snake[0].x > N - 1) or (Snake[0].x < 0) or (Snake[0].y > M - 1 + Space) or (Snake[0].y < Space)) //Hitting the Wall
		{	delay = 10000; Player[PlayerNumber].score = score;	window.close();	 }	
    }
    
	//Sorting achievement
	PlayerNumber = PlayerNumber + 1;
	for (int i = 0; i < PlayerNumber; i++)
	{
		for (int j = 0; j < PlayerNumber - 1; j++)
		{
			if (Player[j].score < Player[j+1].score)
			{
				scoreTemporary = Player[j+1].score;
				Player[j+1].score = Player[j].score;
				Player[j].score = scoreTemporary;
				
				strcpy(nameTemporary, Player[j+1].name);
				strcpy(Player[j+1].name, Player[j].name);
				strcpy(Player[j].name, nameTemporary);
			}
		}
	}
	RenderWindow window1(VideoMode(Width, Height), "Snake Game!"); 
	while (window1.isOpen())
	{
		window1.clear();
		Event e;
		while (window1.pollEvent(e)) //Doing event consequently
        {
			if (e.type == Event::Closed) {window1.close();}     //Close the window
            if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {GUI(); window1.close();}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::E))
				{ 
					window1.close(); Restart(); SingleEasy();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::H))
				{ 
					window1.close(); Restart(); SingleHard();
				fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::E))
				{ 
					window1.close(); Restart(); DoubleEasy();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::H))
				{ 
					window1.close(); Restart(); DoubleHard();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
			}          
        }
        for (int i = 0; i < N; i++)
    		for (int j = 0; j < M + Space; j++)
    			{ sprite2.setPosition(i*size, j*size);  window1.draw(sprite2); } 
		char Counter[1000], Score_Temporary[1000];
		//---Drawing the map ---	
		Text text10, text11, text12, text13, text14; font.loadFromFile("Images/Times-New-Romans.ttf");
		text10.setFont(font); 			text10.setString("You have completed the game \nS+E = Single Easy Mode; S+H = Single Hard Mode; \nD+E = Double Easy Mode; D+H = Double Hard Mode; \nEsc = Return");
		text10.setCharacterSize(40); 	text10.setFillColor(Color::Red);
		text10.setStyle(Text::Bold); 	text10.setPosition(100, 25); 
		window1.draw(text10);
		text10.setFont(font); 			text10.setString("-----------------------------------------");
		text10.setCharacterSize(48); 	text10.setFillColor(Color::Red);
		text10.setStyle(Text::Bold); 	text10.setPosition(50, 200); 
		window1.draw(text10);	
		for (int i = 0; i < PlayerNumber; i++)
		{
			itoa((i + 1), Counter, 10);
			text11.setFont(font); 			text11.setString(Counter);
			text11.setCharacterSize(32); 	text11.setFillColor(Color::Red);
			text11.setStyle(Text::Bold); 	text11.setPosition(150, 220 + (i+1)*32);
			window1.draw(text11);

			text12.setFont(font); 			text12.setString(Player[i].name);
			text12.setCharacterSize(32); 	text12.setFillColor(Color::Red);
			text12.setStyle(Text::Bold); 	text12.setPosition(220, 220 + (i+1)*32);
			window1.draw(text12);
				
			itoa(Player[i].score, Score_Temporary, 10);
			text13.setFont(font); 			text13.setString(Score_Temporary);
			text13.setCharacterSize(32); 	text13.setFillColor(Color::Red);
			text13.setStyle(Text::Bold); 	text13.setPosition(450, 220 + (i+1)*32);
			window1.draw(text13);		
		}
		window1.display();			
	}
} 

void EasyMode_2 ()
{
	//Snake Movement Algorithm for the whole body -- Starting from its tails
	for (int i = Snake_Length_2; i > 0 ; --i)
    {
		Snake_2[i].x = Snake_2[i-1].x; 
		Snake_2[i].y = Snake_2[i-1].y;
	}
	// Snake Movement Algorithm for the head movement
    if (dir_2 == 0) Snake_2[0].y += 1;      if (dir_2 == 1) Snake_2[0].x -= 1;        
	if (dir_2 == 2) Snake_2[0].x += 1;      if (dir_2 == 3) Snake_2[0].y -= 1;   
	// If Snake eats Food
	if ((Snake_2[0].x == Food.x) && (Snake_2[0].y == Food.y)) 
    {
		if (FoodChoice == 1) {score_2 = score_2 + 2;}  		//Apple
		if (FoodChoice == 2) {score_2 = score_2 + 5;}		//Melon
		if (FoodChoice == 3) {score_2 = score_2 + 10;} 		//Strawberry
		
		Snake_Length_2 = Snake_Length_2 + 1; 		//Increment the Snake's Length by 1
		Food.x = rand() % N; 			 		//Set up new position for food at x-axis
		Food.y = rand() % M + Space;			//Set up new position for food at y-axis
		// Setting the next food
		FoodChoice = rand() % 3 + 1;
		if (FoodChoice == 1) {t12.loadFromFile("Images/Fruit/Apple.png"); 		Sprite sprite12(t12);}  	//Apple
		if (FoodChoice == 2) {t12.loadFromFile("Images/Fruit/Melon.png"); 		Sprite sprite12(t12);}		//Melon
		if (FoodChoice == 3) {t12.loadFromFile("Images/Fruit/Strawberry.png"); 	Sprite sprite12(t12);} 		//Strawberry
	}
	//If Snake Passed Wall -- Give him available at the other size (for Easy Mode)
    if (Snake_2[0].x > N - 1) 			Snake_2[0].x = 0;  
	if (Snake_2[0].x < 0) 				Snake_2[0].x = N - 1;
    if (Snake_2[0].y > M - 1 + Space) 	Snake_2[0].y = Space;  
	if (Snake_2[0].y < Space) 			Snake_2[0].y = M - 1 + Space;	
}
void HardMode_2()
{
	//Snake Movement Algorithm for the whole body -- Starting from its tails
	for (int i = Snake_Length_2; i > 0 ; --i)
    {
		Snake_2[i].x = Snake_2[i-1].x; 
		Snake_2[i].y = Snake_2[i-1].y;
	}
	// Snake Movement Algorithm for the head movement
    if (dir_2 == 0) Snake_2[0].y += 1;      if (dir_2 == 1) Snake_2[0].x -= 1;        
	if (dir_2 == 2) Snake_2[0].x += 1;      if (dir_2 == 3) Snake_2[0].y -= 1;   
	// If Snake eats Food
	if ((Snake_2[0].x == Food.x) && (Snake_2[0].y == Food.y)) 
    {
		if (FoodChoice == 1) {score_2 = score_2 + 2;}  		//Apple
		if (FoodChoice == 2) {score_2 = score_2 + 5;}		//Melon
		if (FoodChoice == 3) {score_2 = score_2 + 10;} 		//Strawberry
		
		Snake_Length_2 = Snake_Length_2 + 1; 		//Increment the Snake's Length by 1
		Food.x = rand() % N; 			 		//Set up new position for food at x-axis
		Food.y = rand() % M + Space;			//Set up new position for food at y-axis
		// Setting the next food
		FoodChoice = rand() % 3 + 1;
		if (FoodChoice == 1) {t12.loadFromFile("Images/Fruit/Apple.png"); 		Sprite sprite12(t12);}  	//Apple
		if (FoodChoice == 2) {t12.loadFromFile("Images/Fruit/Melon.png"); 		Sprite sprite12(t12);}		//Melon
		if (FoodChoice == 3) {t12.loadFromFile("Images/Fruit/Strawberry.png"); 	Sprite sprite12(t12);} 		//Strawberry
	}
}

void DoubleEasy()
{
	char nameTemporary[100];
	srand(time(0)); //Seed the random 

    RenderWindow window(VideoMode(Width, Height), "Snake Game!"); // Make usable file
	window.setVerticalSyncEnabled(true);	
    Texture t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; 						//Set texture t0 -> t13 and convert into sprite 
    t0.loadFromFile("Images/Obstacle.png"); 					Sprite sprite0(t0);				//t0 = Obstacle
	t1.loadFromFile("Images/Snake_Map.png"); 					Sprite sprite1(t1);				//t1 = Snake's Map
    t2.loadFromFile("Images/Play_Background.png");				Sprite sprite2(t2);				//t2 = Play _Background used for printing status
	// Snake #1
	t3.loadFromFile("Images/Snake/Snake_Head_Left.png");		Sprite sprite3(t3);	
    t4.loadFromFile("Images/Snake/Snake_Tail_Left.png");		Sprite sprite4(t4);	
    t5.loadFromFile("Images/Snake/Snake_Head_Right.png");		Sprite sprite5(t5);
    t6.loadFromFile("Images/Snake/Snake_Tail_Right.png");		Sprite sprite6(t6);
	t7.loadFromFile("Images/Snake/Snake_Head_Up.png");			Sprite sprite7(t7);
    t8.loadFromFile("Images/Snake/Snake_Tail_Up.png");			Sprite sprite8(t8);
	t9.loadFromFile("Images/Snake/Snake_Head_Down.png");		Sprite sprite9(t9);	
    t10.loadFromFile("Images/Snake/Snake_Tail_Down.png");		Sprite sprite10(t10);		  
	t11.loadFromFile("Images/Snake/Snake_Body.png");			Sprite sprite11(t11);
	//Food beginning
	t12.loadFromFile("Images/Fruit/Apple.png"); 				Sprite sprite12(t12);
	FoodChoice = rand() % 3 + 1;	
	
	Texture t20, t21, t22, t23, t24, t25, t26, t27, t28;
	// Snake #2
	t20.loadFromFile("Images/Snake - 2/Snake_Head_Left.png");		Sprite sprite20(t20);	
    t21.loadFromFile("Images/Snake - 2/Snake_Tail_Left.png");		Sprite sprite21(t21);	
    t22.loadFromFile("Images/Snake - 2/Snake_Head_Right.png");		Sprite sprite22(t22);
    t23.loadFromFile("Images/Snake - 2/Snake_Tail_Right.png");		Sprite sprite23(t23);
	t24.loadFromFile("Images/Snake - 2/Snake_Head_Up.png");			Sprite sprite24(t24);
    t25.loadFromFile("Images/Snake - 2/Snake_Tail_Up.png");			Sprite sprite25(t25);
	t26.loadFromFile("Images/Snake - 2/Snake_Head_Down.png");		Sprite sprite26(t26);	
    t27.loadFromFile("Images/Snake - 2/Snake_Tail_Down.png");		Sprite sprite27(t27);		  
	t28.loadFromFile("Images/Snake - 2/Snake_Body.png");			Sprite sprite28(t28);
	
    //Count time by timer and set delay. Delay (s) will determined the speed of Snake. Small 'delay' variable causes the Snake moving faster, vice versa
	Clock clock;
	float timer = 0, delay = 0.2;	          
	float temp = delay;
    //Initialize
	float SpeedIncrease; 					//Buff Speed
    Restart();                //Initial position for the food and Snake (applicable once only)
	
	String playerInput; Text playerText; 		
    while (window.isOpen())                       					 //Running the file and keep open
    {
        float time = clock.getElapsedTime().asSeconds();            //Take the Elapsed Time value (s) and assign to 'time' variable
        clock.restart();
        timer = timer + time;                                       //Increment the 'timer' by time 
		SpeedIncrease = SpeedIncrease + time;						//Increment the 'SpeedIncrease' by time 			
		ObstacleRealTime = ObstacleRealTime + time;					//Increment the 'ObstacleRealTime' by time 	
		MusicDuration = MusicDuration + time;						//Increment the 'MusicDuration' by time 
		RealTime = RealTime + time;									//Counting timeplay
		
		Text text4, text5, text7; 	//GameStatus & Music Status
		if (MusicStatus == 0) {text4.setString("PAUSED");	}
		else if (MusicStatus == 1) {text4.setString("PLAYED");	}
		if (delay > 1000) {text7.setString("PAUSED");}
		else {text7.setString("PLAYED");}
        Event e; 													//Set the Event and name as e        
		if (RestartStatus == 0) {Restart(); RestartStatus = 1;}                            
        while (window.pollEvent(e)) //Doing event consequently
        {
			if (e.type == Event::Closed) {window.close();}      //Close the window
            if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {window.close(); GUI();				}
				//Reset game and music
				if (Keyboard::isKeyPressed(Keyboard::R))	
				{music.play();  MusicStatus = 1; text4.setString("PLAYED"); Restart(); text7.setString("PLAYED");}  
				//Game Status
				if (Keyboard::isKeyPressed(Keyboard::G) and Keyboard::isKeyPressed(Keyboard::A))
				{delay = 10000; text7.setString("PAUSED");}  	//pause the game
				if (Keyboard::isKeyPressed(Keyboard::G) and Keyboard::isKeyPressed(Keyboard::L))
				{delay = temp; text7.setString("PLAYED");}
				//Music
				if (Keyboard::isKeyPressed(Keyboard::M) and Keyboard::isKeyPressed(Keyboard::A)) {music.pause(); MusicStatus = 0; text4.setString("PAUSED"); }						//pause the music
				if (Keyboard::isKeyPressed(Keyboard::M) and Keyboard::isKeyPressed(Keyboard::L)) {music.play();  MusicStatus = 1; text4.setString("PLAYED");}						//continue playing music
			}  
        }
		//Pressing and Snake's Movement
        //Snake #1
		if (Keyboard::isKeyPressed(Keyboard::Left)) 	dir = 1;     //If pressing left, set dir = 1 and keeps 'dir', not keeps turning Left (keep the Snake move to the Left at the time press Left)
        if (Keyboard::isKeyPressed(Keyboard::Right)) 	dir = 2;     //If pressing Right, set dir = 2 and keeps 'dir', not keeps turning Right (keep the Snake move to the Left at the time press Right)
        if (Keyboard::isKeyPressed(Keyboard::Up)) 		dir = 3;	 //If pressing Up, set dir = 3 and keeps 'dir', not keeps turning Up (keep the Snake move to the Left at the time press Up)
        if (Keyboard::isKeyPressed(Keyboard::Down)) 	dir = 0; 	 //If pressing Down, set dir = 0 and keeps 'dir', not keeps turning Down (keep the Snake move to the Left at the time press Down)
		//Snake #2
		if (Keyboard::isKeyPressed(Keyboard::A)) 	dir_2 = 1;     //If pressing left, set dir = 1 and keeps 'dir', not keeps turning Left (keep the Snake move to the Left at the time press Left)
        if (Keyboard::isKeyPressed(Keyboard::D)) 	dir_2 = 2;     //If pressing Right, set dir = 2 and keeps 'dir', not keeps turning Right (keep the Snake move to the Left at the time press Right)
        if (Keyboard::isKeyPressed(Keyboard::W)) 	dir_2 = 3;	 //If pressing Up, set dir = 3 and keeps 'dir', not keeps turning Up (keep the Snake move to the Left at the time press Up)
        if (Keyboard::isKeyPressed(Keyboard::S)) 	dir_2 = 0; 	 //If pressing Down, set dir = 0 and keeps 'dir', not keeps turning Down (keep the Snake move to the Left at the time press Down)
		
		if (timer > delay) 	{timer = 0; EasyMode(); EasyMode_2();}             	 //When timer > delay, reconstruct the 'timer' variable to zero and do 'Tick' function where Snake can move
		
		if (SpeedIncrease >= 20) //Each 20s passed, the speed is increased by 5% from its value and reset SpeedIncrease	
		{delay = 95 * delay / 100; temp = delay; SpeedIncrease = 0;	}     
        //Music
        if (MusicDuration > EndingMusicTime) {MusicChoice = rand() % 6 + 1; MusicPlay(); MusicDuration = 0;} // Reset Music
        if (MusicChoice == 1) {text5.setString("Move Your Body - Ria - Alan Walker Remix");}
        if (MusicChoice == 2) {text5.setString("Fade (Hell's Speaker Remix) Ft. Isabel Park - Alan Walker inspired");}
        if (MusicChoice == 3) {text5.setString("N30N - Speed Nightcore");}
		if (MusicChoice == 4) {text5.setString("Khau thi tam phi Remix");}
		if (MusicChoice == 5) {text5.setString("Two Steps From Hell - Victory");}
		if (MusicChoice == 6) {text5.setString("Unknown Name");}
        
   	
	// ----- DRAWING THE WINDOW ----//
    	window.clear();                              //Clean the window
		//--- Drawing the Snake's Map ---
   		for (int i = 0; i < N; i++) 
      		for (int j = 0; j < M; j++) 
        		{ sprite1.setPosition(i*size, (j + Space)*size);  window.draw(sprite1); }
    	//--- Drawing the empty place for printing status
		for (int i = 0; i < N; i++)
    		for(int j = 0; j < Space; j++)
    			{ sprite2.setPosition(i*size, j*size);  window.draw(sprite2); }                 
    
		//---Drawing the Snake #1---
		if (dir == 1) //Left
    	{	
			sprite3.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite3);
			if (Snake_Length > 1) {sprite4.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite4);}
		}
		if (dir == 2) //Right
    	{
			sprite5.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite5);
			if (Snake_Length > 1) {sprite6.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite6);}
		}
		if (dir == 3) //Up
    	{
			sprite7.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite7);
			if (Snake_Length > 1) {sprite8.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite8);}
		}
		if (dir == 0) //Down
    	{
			sprite9.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite9);
			if (Snake_Length > 1) {sprite10.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite10);	}	
		}
		for (int i = 1;i < Snake_Length - 1;i++)
        {sprite11.setPosition(Snake[i].x*size, Snake[i].y*size);  window.draw(sprite11);} 
   		
   		//---Drawing the Snake #2---
		if (dir_2 == 1) //Left
    	{	
			sprite20.setPosition(Snake_2[0].x*size, Snake_2[0].y*size);  window.draw(sprite20);
			if (Snake_Length_2 > 1) {sprite21.setPosition(Snake_2[Snake_Length_2 - 1].x*size, Snake_2[Snake_Length_2 - 1].y*size);  window.draw(sprite21);}
		}
		if (dir_2 == 2) //Right
    	{
			sprite22.setPosition(Snake_2[0].x*size, Snake_2[0].y*size);  window.draw(sprite22);
			if (Snake_Length_2 > 1) {sprite23.setPosition(Snake_2[Snake_Length_2 - 1].x*size, Snake_2[Snake_Length_2 - 1].y*size);  window.draw(sprite23);}
		}
		if (dir_2 == 3) //Up
    	{
			sprite24.setPosition(Snake_2[0].x*size, Snake_2[0].y*size);  window.draw(sprite24);
			if (Snake_Length_2 > 1) {sprite25.setPosition(Snake_2[Snake_Length_2 - 1].x*size, Snake_2[Snake_Length_2 - 1].y*size);  window.draw(sprite25);}
		}
		if (dir_2 == 0) //Down
    	{
			sprite26.setPosition(Snake_2[0].x*size, Snake_2[0].y*size);  window.draw(sprite26);
			if (Snake_Length_2 > 1) {sprite27.setPosition(Snake_2[Snake_Length_2 - 1].x*size, Snake_2[Snake_Length_2 - 1].y*size);  window.draw(sprite27);}	
		}
		for (int i = 1; i < Snake_Length_2 - 1;i++)
        {sprite28.setPosition(Snake_2[i].x*size, Snake_2[i].y*size);  window.draw(sprite28);} 
        
		//--- Drawing Food --- 
    	sprite12.setPosition(Food.x*size, Food.y*size);  window.draw(sprite12);                             
		//--- Drawing Obstacles ---
		if (ObstacleRealTime > 15)
		{
			if (ObstacleCount == 1)
			{
				for (int i = 0; i < ObstacleNumber; i++)
				{		
					Obstacle[i].x = rand() % N; 
					Obstacle[i].y = rand() % M + Space; 
				}
			}
			for (int i = 0; i < ObstacleNumber; i++) {	sprite0.setPosition( Obstacle[i].x*size, Obstacle[i].y*size); window.draw(sprite0); }  
			ObstacleCount = 0; ObstacleDuration = ObstacleDuration + time;
			if (ObstacleDuration > 20)	{ObstacleRealTime = 0; ObstacleDuration = 0; ObstacleCount = 1; ObstacleDelete(); } //20 seconds on and off
		}
	
		//Print the text 
		Text text0, text1, text2, text3, text6, text8; font.loadFromFile("Images/Times-New-Romans.ttf");
	
		text0.setFont(font); 			text0.setString("Score:");
		text0.setCharacterSize(16); 	text0.setFillColor(Color::White);
		text0.setStyle(Text::Bold); 	text0.setPosition(2, 4); 
		window.draw(text0);	
		
		char scoreString_1[1000]; 		itoa(score, scoreString_1, 10);                    //convert score from char to string
		text1.setFont(font); 			text1.setString(scoreString_1);
		text1.setCharacterSize(16); 	text1.setFillColor(Color::White);
		text1.setStyle(Text::Bold); 	text1.setPosition(55, 4); 
		window.draw(text1);	
		
		char scoreString_2[1000];		itoa(score_2, scoreString_2, 10);
		text2.setFont(font); 			text2.setString(scoreString_2);
		text2.setCharacterSize(16); 	text2.setFillColor(Color::White);
		text2.setStyle(Text::Bold); 	text2.setPosition(130, 4); 
		window.draw(text2);
		
		text3.setFont(font); 			text3.setString("Music's Status:                 - Music: ");
		text3.setCharacterSize(16); 	text3.setFillColor(Color::White);
		text3.setStyle(Text::Bold); 	text3.setPosition(2, 24); 
		window.draw(text3);	
		text4.setFont(font); 			
		text4.setCharacterSize(16); 	text4.setFillColor(Color::White);
		text4.setStyle(Text::Bold); 	text4.setPosition(125, 24); 
		window.draw(text4);	
		text5.setFont(font); 			
		text5.setCharacterSize(16); 	text5.setFillColor(Color::White);
		text5.setStyle(Text::Bold); 	text5.setPosition(270, 24); 
		window.draw(text5);	
	
		text6.setFont(font); 			text6.setString("Game Mode: Double Easy - Status: ");
		text6.setCharacterSize(16); 	text6.setFillColor(Color::White);
		text6.setStyle(Text::Bold); 	text6.setPosition(2, 44); 
		window.draw(text6);	
		text7.setFont(font); 			
		text7.setCharacterSize(16); 	text7.setFillColor(Color::White);
		text7.setStyle(Text::Bold); 	text7.setPosition(270, 44); 
		window.draw(text7);
	
    	window.display(); // Show the screen
    	
    	//Dead if violating
    	for (int i = 0; i < ObstacleNumber; i++)
    	{
    		if ( ((Snake[0].x == Obstacle[i].x) && (Snake[0].y == Obstacle[i].y)) or ((Snake_2[0].x == Obstacle[i].x) && (Snake_2[0].y == Obstacle[i].y)) )
    		{
    			delay = 10000; Player[PlayerNumber].score = score; Player_2[PlayerNumber].score = score;
				window.close();		
			}
		}  	
    }
	RenderWindow window1(VideoMode(Width, Height), "Snake Game!"); 
	while (window1.isOpen())
	{
		window1.clear();
		Event e;
		while (window1.pollEvent(e)) //Doing event consequently
        {
			if (e.type == Event::Closed) {window1.close();}     //Close the window
            if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {GUI(); window1.close();}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::E))
				{ 
					window1.close(); Restart(); SingleEasy();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::H))
				{ 
					window1.close(); Restart(); SingleHard();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::E))
				{ 
					window1.close(); Restart(); DoubleEasy();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::H))
				{ 
					window1.close(); Restart(); DoubleHard();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
			}          
        }
        for (int i = 0; i < N; i++)
    		for (int j = 0; j < M + Space; j++)
    			{ sprite2.setPosition(i*size, j*size);  window1.draw(sprite2); } 
		//---Drawing the map ---	
		Text text10, text11, text12; font.loadFromFile("Images/Times-New-Romans.ttf");
		text10.setFont(font); 			text10.setString("You have completed the game \nS+E = Single Easy Mode; S+H = Single Hard Mode; \nD+E = Double Easy Mode; D+H = Double Hard Mode; \nEsc = Return");
		text10.setCharacterSize(40); 	text10.setFillColor(Color::Red);
		text10.setStyle(Text::Bold); 	text10.setPosition(100, 25); 
		window1.draw(text10);
		
		text12.setFont(font); 			text12.setString("----------------------------------------------------------------------------------------------------------------------");
		text12.setCharacterSize(48); 	text12.setFillColor(Color::Red);
		text12.setStyle(Text::Bold); 	text12.setPosition(0, 200); 
		window1.draw(text12);	
		
		if (score > score_2) {text11.setString("Player #1 wins");}
		else if (score < score_2) {text11.setString("Player #2 wins");}
		else {text11.setString("DRAW");}
		text11.setFont(font); 			
		text11.setCharacterSize(32); 	text11.setFillColor(Color::White);
		text11.setStyle(Text::Bold); 	text11.setPosition(450, 220 + 32);
		window1.draw(text11);
	
		window1.display();			
	}    		
}

void DoubleHard()
{
	char nameTemporary[100];
	srand(time(0)); //Seed the random 

    RenderWindow window(VideoMode(Width, Height), "Snake Game!"); // Make usable file
	window.setVerticalSyncEnabled(true);	
    Texture t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; 						//Set texture t0 -> t13 and convert into sprite 
    t0.loadFromFile("Images/Obstacle.png"); 					Sprite sprite0(t0);				//t0 = Obstacle
	t1.loadFromFile("Images/Snake_Map.png"); 					Sprite sprite1(t1);				//t1 = Snake's Map
    t2.loadFromFile("Images/Play_Background.png");				Sprite sprite2(t2);				//t2 = Play _Background used for printing status
	// Snake #1
	t3.loadFromFile("Images/Snake/Snake_Head_Left.png");		Sprite sprite3(t3);	
    t4.loadFromFile("Images/Snake/Snake_Tail_Left.png");		Sprite sprite4(t4);	
    t5.loadFromFile("Images/Snake/Snake_Head_Right.png");		Sprite sprite5(t5);
    t6.loadFromFile("Images/Snake/Snake_Tail_Right.png");		Sprite sprite6(t6);
	t7.loadFromFile("Images/Snake/Snake_Head_Up.png");			Sprite sprite7(t7);
    t8.loadFromFile("Images/Snake/Snake_Tail_Up.png");			Sprite sprite8(t8);
	t9.loadFromFile("Images/Snake/Snake_Head_Down.png");		Sprite sprite9(t9);	
    t10.loadFromFile("Images/Snake/Snake_Tail_Down.png");		Sprite sprite10(t10);		  
	t11.loadFromFile("Images/Snake/Snake_Body.png");			Sprite sprite11(t11);
	//Food beginning
	t12.loadFromFile("Images/Fruit/Apple.png"); 				Sprite sprite12(t12);
	FoodChoice = rand() % 3 + 1;	
	
	Texture t20, t21, t22, t23, t24, t25, t26, t27, t28;
	// Snake #2
	t20.loadFromFile("Images/Snake - 2/Snake_Head_Left.png");		Sprite sprite20(t20);	
    t21.loadFromFile("Images/Snake - 2/Snake_Tail_Left.png");		Sprite sprite21(t21);	
    t22.loadFromFile("Images/Snake - 2/Snake_Head_Right.png");		Sprite sprite22(t22);
    t23.loadFromFile("Images/Snake - 2/Snake_Tail_Right.png");		Sprite sprite23(t23);
	t24.loadFromFile("Images/Snake - 2/Snake_Head_Up.png");			Sprite sprite24(t24);
    t25.loadFromFile("Images/Snake - 2/Snake_Tail_Up.png");			Sprite sprite25(t25);
	t26.loadFromFile("Images/Snake - 2/Snake_Head_Down.png");		Sprite sprite26(t26);	
    t27.loadFromFile("Images/Snake - 2/Snake_Tail_Down.png");		Sprite sprite27(t27);		  
	t28.loadFromFile("Images/Snake - 2/Snake_Body.png");			Sprite sprite28(t28);
	
    //Count time by timer and set delay. Delay (s) will determined the speed of Snake. Small 'delay' variable causes the Snake moving faster, vice versa
	Clock clock;
	float timer = 0, delay = 0.1;	          
	float temp = delay;
    //Initialize
	float SpeedIncrease; 					//Buff Speed
	Restart();                //Initial position for the food and Snake (applicable once only)
	
	String playerInput; Text playerText; 
	 				
    while (window.isOpen())                       					 //Running the file and keep open
    {
		float time = clock.getElapsedTime().asSeconds();            //Take the Elapsed Time value (s) and assign to 'time' variable
        clock.restart();
        timer = timer + time;                                       //Increment the 'timer' by time 
		SpeedIncrease = SpeedIncrease + time;						//Increment the 'SpeedIncrease' by time 			
		ObstacleRealTime = ObstacleRealTime + time;					//Increment the 'ObstacleRealTime' by time 	
		MusicDuration = MusicDuration + time;						//Increment the 'MusicDuration' by time 
		RealTime = RealTime + time;									//Counting timeplay
		
		Text text4, text5, text7; 	//GameStatus & Music Status
		if (MusicStatus == 0) {text4.setString("PAUSED");	}
		else if (MusicStatus == 1) {text4.setString("PLAYED");	}
		if (delay > 1000) {text7.setString("PAUSED");}
		else {text7.setString("PLAYED");}
        Event e; 													//Set the Event and name as e   
		if (RestartStatus == 0) {Restart(); RestartStatus = 1;}                                  
        while (window.pollEvent(e)) //Doing event consequently
        {
			if (e.type == Event::Closed) {window.close();}      //Close the window
            if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {window.close(); GUI();				}
				//Reset game and music
				if (Keyboard::isKeyPressed(Keyboard::R))	
				{music.play();  MusicStatus = 1; text4.setString("PLAYED"); Restart(); text7.setString("PLAYED");}  
				//Game Status
				if (Keyboard::isKeyPressed(Keyboard::G) and Keyboard::isKeyPressed(Keyboard::A))
				{delay = 10000; text7.setString("PAUSED");}  	//pause the game
				if (Keyboard::isKeyPressed(Keyboard::G) and Keyboard::isKeyPressed(Keyboard::L))
				{delay = temp; text7.setString("PLAYED");}
				//Music
				if (Keyboard::isKeyPressed(Keyboard::M) and Keyboard::isKeyPressed(Keyboard::A)) {music.pause(); MusicStatus = 0; text4.setString("PAUSED"); }						//pause the music
				if (Keyboard::isKeyPressed(Keyboard::M) and Keyboard::isKeyPressed(Keyboard::L)){music.play();  MusicStatus = 1; text4.setString("PLAYED");}						//continue playing music
			}  
        }
		//Pressing and Snake's Movement
        //Snake #1
		if (Keyboard::isKeyPressed(Keyboard::Left)) 	dir = 1;     //If pressing left, set dir = 1 and keeps 'dir', not keeps turning Left (keep the Snake move to the Left at the time press Left)
        if (Keyboard::isKeyPressed(Keyboard::Right)) 	dir = 2;     //If pressing Right, set dir = 2 and keeps 'dir', not keeps turning Right (keep the Snake move to the Left at the time press Right)
        if (Keyboard::isKeyPressed(Keyboard::Up)) 		dir = 3;	 //If pressing Up, set dir = 3 and keeps 'dir', not keeps turning Up (keep the Snake move to the Left at the time press Up)
        if (Keyboard::isKeyPressed(Keyboard::Down)) 	dir = 0; 	 //If pressing Down, set dir = 0 and keeps 'dir', not keeps turning Down (keep the Snake move to the Left at the time press Down)
		//Snake #2
		if (Keyboard::isKeyPressed(Keyboard::A)) 	dir_2 = 1;     //If pressing left, set dir = 1 and keeps 'dir', not keeps turning Left (keep the Snake move to the Left at the time press Left)
        if (Keyboard::isKeyPressed(Keyboard::D)) 	dir_2 = 2;     //If pressing Right, set dir = 2 and keeps 'dir', not keeps turning Right (keep the Snake move to the Left at the time press Right)
        if (Keyboard::isKeyPressed(Keyboard::W)) 	dir_2 = 3;	 //If pressing Up, set dir = 3 and keeps 'dir', not keeps turning Up (keep the Snake move to the Left at the time press Up)
        if (Keyboard::isKeyPressed(Keyboard::S)) 	dir_2 = 0; 	 //If pressing Down, set dir = 0 and keeps 'dir', not keeps turning Down (keep the Snake move to the Left at the time press Down)
		
		if (timer > delay) 	{timer = 0; HardMode(); HardMode_2();}             	 //When timer > delay, reconstruct the 'timer' variable to zero and do 'Tick' function where Snake can move
		
		if (SpeedIncrease >= 20) //Each 20s passed, the speed is increased by 10% from its value and reset SpeedIncrease	
		{delay = 90 * delay / 100; temp = delay; SpeedIncrease = 0;	}     
        //Music
        if (MusicDuration > EndingMusicTime) {MusicChoice = rand() % 6 + 1; MusicPlay(); MusicDuration = 0;} // Reset Music
        if (MusicChoice == 1) {text5.setString("Move Your Body - Ria - Alan Walker Remix");}
        if (MusicChoice == 2) {text5.setString("Fade (Hell's Speaker Remix) Ft. Isabel Park - Alan Walker inspired");}
        if (MusicChoice == 3) {text5.setString("N30N - Speed Nightcore");}
		if (MusicChoice == 4) {text5.setString("Khau thi tam phi Remix");}
		if (MusicChoice == 5) {text5.setString("Two Steps From Hell - Victory");}
		if (MusicChoice == 6) {text5.setString("Unknown Name");}
        
   	
	// ----- DRAWING THE WINDOW ----//
    	window.clear();                              //Clean the window
		//--- Drawing the Snake's Map ---
   		for (int i = 0; i < N; i++) 
      		for (int j = 0; j < M; j++) 
        		{ sprite1.setPosition(i*size, (j + Space)*size);  window.draw(sprite1); }
    	//--- Drawing the empty place for printing status
		for (int i = 0; i < N; i++)
    		for(int j = 0; j < Space; j++)
    			{ sprite2.setPosition(i*size, j*size);  window.draw(sprite2); }                 
    
		//---Drawing the Snake #1---
		if (dir == 1) //Left
    	{	
			sprite3.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite3);
			if (Snake_Length > 1) {sprite4.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite4);}
		}
		if (dir == 2) //Right
    	{
			sprite5.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite5);
			if (Snake_Length > 1) {sprite6.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite6);}
		}
		if (dir == 3) //Up
    	{
			sprite7.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite7);
			if (Snake_Length > 1) {sprite8.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite8);}
		}
		if (dir == 0) //Down
    	{
			sprite9.setPosition(Snake[0].x*size, Snake[0].y*size);  window.draw(sprite9);
			if (Snake_Length > 1) {sprite10.setPosition(Snake[Snake_Length - 1].x*size, Snake[Snake_Length - 1].y*size);  window.draw(sprite10);	}	
		}
		for (int i = 1;i < Snake_Length - 1;i++)
        {sprite11.setPosition(Snake[i].x*size, Snake[i].y*size);  window.draw(sprite11);} 
   		
   		//---Drawing the Snake #2---
		if (dir_2 == 1) //Left
    	{	
			sprite20.setPosition(Snake_2[0].x*size, Snake_2[0].y*size);  window.draw(sprite20);
			if (Snake_Length_2 > 1) {sprite21.setPosition(Snake_2[Snake_Length_2 - 1].x*size, Snake_2[Snake_Length_2 - 1].y*size);  window.draw(sprite21);}
		}
		if (dir_2 == 2) //Right
    	{
			sprite22.setPosition(Snake_2[0].x*size, Snake_2[0].y*size);  window.draw(sprite22);
			if (Snake_Length_2 > 1) {sprite23.setPosition(Snake_2[Snake_Length_2 - 1].x*size, Snake_2[Snake_Length_2 - 1].y*size);  window.draw(sprite23);}
		}
		if (dir_2 == 3) //Up
    	{
			sprite24.setPosition(Snake_2[0].x*size, Snake_2[0].y*size);  window.draw(sprite24);
			if (Snake_Length_2 > 1) {sprite25.setPosition(Snake_2[Snake_Length_2 - 1].x*size, Snake_2[Snake_Length_2 - 1].y*size);  window.draw(sprite25);}
		}
		if (dir_2 == 0) //Down
    	{
			sprite26.setPosition(Snake_2[0].x*size, Snake_2[0].y*size);  window.draw(sprite26);
			if (Snake_Length_2 > 1) {sprite27.setPosition(Snake_2[Snake_Length_2 - 1].x*size, Snake_2[Snake_Length_2 - 1].y*size);  window.draw(sprite27);}	
		}
		for (int i = 1; i < Snake_Length_2 - 1;i++)
        {sprite28.setPosition(Snake_2[i].x*size, Snake_2[i].y*size);  window.draw(sprite28);}
        
		//--- Drawing Food --- 
    	sprite12.setPosition(Food.x*size, Food.y*size);  window.draw(sprite12);                             
		//--- Drawing Obstacles ---
		if (ObstacleRealTime > 15)
		{
			if (ObstacleCount == 1)
			{
				for (int i = 0; i < ObstacleNumber; i++)
				{		
					Obstacle[i].x = rand() % N; 
					Obstacle[i].y = rand() % M + Space; 
				}
			}
			for (int i = 0; i < ObstacleNumber; i++) {	sprite0.setPosition( Obstacle[i].x*size, Obstacle[i].y*size); window.draw(sprite0); }  
			ObstacleCount = 0; ObstacleDuration = ObstacleDuration + time;
			if (ObstacleDuration > 20)	{ObstacleRealTime = 0; ObstacleDuration = 0; ObstacleCount = 1; ObstacleDelete(); } //20 seconds on and off
		}
	
		//Print the text 
		Text text0, text1, text2, text3, text6, text8; font.loadFromFile("Images/Times-New-Romans.ttf");
	
		text0.setFont(font); 			text0.setString("Score:");
		text0.setCharacterSize(16); 	text0.setFillColor(Color::White);
		text0.setStyle(Text::Bold); 	text0.setPosition(2, 4); 
		window.draw(text0);	
		
		char scoreString_1[1000]; 		itoa(score, scoreString_1, 10);                    //convert score from char to string
		text1.setFont(font); 			text1.setString(scoreString_1);
		text1.setCharacterSize(16); 	text1.setFillColor(Color::White);
		text1.setStyle(Text::Bold); 	text1.setPosition(55, 4); 
		window.draw(text1);	
		
		char scoreString_2[1000];		itoa(score_2, scoreString_2, 10);
		text2.setFont(font); 			text2.setString(scoreString_2);
		text2.setCharacterSize(16); 	text2.setFillColor(Color::White);
		text2.setStyle(Text::Bold); 	text2.setPosition(130, 4); 
		window.draw(text2);
		
		text3.setFont(font); 			text3.setString("Music's Status:                 - Music: ");
		text3.setCharacterSize(16); 	text3.setFillColor(Color::White);
		text3.setStyle(Text::Bold); 	text3.setPosition(2, 24); 
		window.draw(text3);	
		text4.setFont(font); 			
		text4.setCharacterSize(16); 	text4.setFillColor(Color::White);
		text4.setStyle(Text::Bold); 	text4.setPosition(125, 24); 
		window.draw(text4);	
		text5.setFont(font); 			
		text5.setCharacterSize(16); 	text5.setFillColor(Color::White);
		text5.setStyle(Text::Bold); 	text5.setPosition(270, 24); 
		window.draw(text5);	
	
		text6.setFont(font); 			text6.setString("Game Mode: Double Hard - Status: ");
		text6.setCharacterSize(16); 	text6.setFillColor(Color::White);
		text6.setStyle(Text::Bold); 	text6.setPosition(2, 44); 
		window.draw(text6);	
		text7.setFont(font); 			
		text7.setCharacterSize(16); 	text7.setFillColor(Color::White);
		text7.setStyle(Text::Bold); 	text7.setPosition(270, 44); 
		window.draw(text7);
	
    	window.display(); // Show the screen
    	
    	//Dead if violating
    	for (int i = 0; i < ObstacleNumber; i++) //Hiting Obstacle
    	{
    		if ( ((Snake[0].x == Obstacle[i].x) && (Snake[0].y == Obstacle[i].y)) or ((Snake_2[0].x == Obstacle[i].x) && (Snake_2[0].y == Obstacle[i].y)) )
    		{
    			delay = 10000; Player[PlayerNumber].score = score; Player_2[PlayerNumber].score = score;
				window.close();		
			}
		}  	
		if ( (Snake[0].x > N - 1) or (Snake[0].x < 0) or (Snake[0].y > M - 1 + Space) or (Snake[0].y < Space) or (Snake_2[0].x > N - 1) or (Snake_2[0].x < 0) or (Snake_2[0].y > M - 1 + Space) or (Snake_2[0].y < Space)	) //Hitting the Wall
		{	
			delay = 10000; Player[PlayerNumber].score = score; Player_2[PlayerNumber].score = score; 
			window.close();	 
		} 	
		for (int i = 1; i < Snake_Length; i++) 
    	{
    		if ( (Snake[0].x == Snake[i].x) && (Snake[0].y == Snake[i].y) ) 	//Hiting the Snake #1 himself
    		{
    			delay = 10000; Player[PlayerNumber].score = score; Player_2[PlayerNumber].score = score;
				window.close();		
			}
			if ( (Snake_2[0].x == Snake[i].x) && (Snake_2[0].y == Snake[i].y) )
			{
				delay = 10000; Player[PlayerNumber].score = score; Player_2[PlayerNumber].score = score;
				window.close();
			}
		}
		for (int i = 1; i < Snake_Length_2; i++) //Hiting the Snake #2 himself
    	{
    		if ( (Snake_2[0].x == Snake_2[i].x) && (Snake_2[0].y == Snake_2[i].y) )
    		{
    			delay = 10000; Player[PlayerNumber].score = score; Player_2[PlayerNumber].score = score;
				window.close();		
			}
			if ( (Snake[0].x == Snake_2[i].x) && (Snake[0].y == Snake_2[i].y) )
			{
				delay = 10000; Player[PlayerNumber].score = score; Player_2[PlayerNumber].score = score;
				window.close();
			}
		}
		
    }
    
	RenderWindow window1(VideoMode(Width, Height), "Snake Game!"); 
	while (window1.isOpen())
	{
		window1.clear();
		Event e;
		while (window1.pollEvent(e)) //Doing event consequently
        {
			if (e.type == Event::Closed) {window1.close();}     //Close the window
            if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {GUI(); window1.close();}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::E))
				{ 
					window1.close(); Restart(); SingleEasy();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::H))
				{ 
					window1.close(); Restart(); SingleHard();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::E))
				{ 
					window1.close(); Restart(); DoubleEasy();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::H))
				{ 
					window1.close(); Restart(); DoubleHard();
					fflush(stdin); n = strlen(Player[PlayerNumber - 1].name);
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = Player[PlayerNumber - 1].name[i];}
					PlayerNumber = PlayerNumber + 1;
				}
			}          
        }
        for (int i = 0; i < N; i++)
    		for (int j = 0; j < M + Space; j++)
    			{ sprite2.setPosition(i*size, j*size);  window1.draw(sprite2); } 
		//---Drawing the map ---	
		Text text10, text11, text12; font.loadFromFile("Images/Times-New-Romans.ttf");
		text10.setFont(font); 			text10.setString("You have completed the game \nS+E = Single Easy Mode; S+H = Single Hard Mode; \nD+E = Double Easy Mode; D+H = Double Hard Mode; \nEsc = Return");
		text10.setCharacterSize(40); 	text10.setFillColor(Color::Red);
		text10.setStyle(Text::Bold); 	text10.setPosition(100, 25); 
		window1.draw(text10);
		
		text12.setFont(font); 			text12.setString("----------------------------------------------------------------------------------------------------------------------");
		text12.setCharacterSize(48); 	text12.setFillColor(Color::Red);
		text12.setStyle(Text::Bold); 	text12.setPosition(0, 200); 
		window1.draw(text12);	
		
		if (score > score_2) {text11.setString("Player #1 wins");}
		else if (score < score_2) {text11.setString("Player #2 wins");}
		else {text11.setString("DRAW");}
		text11.setFont(font); 			
		text11.setCharacterSize(32); 	text11.setFillColor(Color::White);
		text11.setStyle(Text::Bold); 	text11.setPosition(450, 220 + 32);
		window1.draw(text11);
	
		window1.display();			
	}    	
}
void GUI()
{
	RenderWindow window0(VideoMode(1200, 784), "Snake Game!", Style::Default);
	window.setVerticalSyncEnabled(true);
	while (window0.isOpen())
	{
		Event e;
		while (window0.pollEvent(e))
		{
			if (e.type == Event::TextEntered) {playerInput +=e.text.unicode; playerText.setString(playerInput);			}
			if (e.type == Event::Closed) {window0.close();}    	
			if (e.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {window0.close(); GUI();				}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::E)) 
				{ 
					//Name Conversion
					int n = playerInput.getSize() - 1;
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = playerInput[i];}
					Player[PlayerNumber].name[n] = '_'; Player[PlayerNumber].name[n+1] = 'S'; Player[PlayerNumber].name[n+2] = 'E'; 
					Restart(); window0.close(); SingleEasy(); RestartStatus = 0; Restart();	
				}
				if (Keyboard::isKeyPressed(Keyboard::S) and Keyboard::isKeyPressed(Keyboard::H)) 
				{ 
					//Name Conversion
					int n = playerInput.getSize() - 1;
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = playerInput[i];}
					Player[PlayerNumber].name[n] = '_'; Player[PlayerNumber].name[n+1] = 'S'; Player[PlayerNumber].name[n+2] = 'H';
					Restart(); window0.close(); SingleHard(); RestartStatus = 0; Restart();	
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::E)) 
				{ 
					//Name Conversion
					int n = playerInput.getSize() - 1;
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = playerInput[i];}
					Player[PlayerNumber].name[n] = '_'; Player[PlayerNumber].name[n+1] = 'D'; Player[PlayerNumber].name[n+2] = 'E';
					Restart(); window0.close(); DoubleEasy(); RestartStatus = 0; Restart();	
				}
				if (Keyboard::isKeyPressed(Keyboard::D) and Keyboard::isKeyPressed(Keyboard::H)) 
				{ 
					//Name Conversion
				 	int n = playerInput.getSize() - 1; 
					for (int i = 0; i < n; i++) {Player[PlayerNumber].name[i] = playerInput[i];}
					Player[PlayerNumber].name[n] = '_'; Player[PlayerNumber].name[n+1] = 'D'; Player[PlayerNumber].name[n+2] = 'H';
					Restart(); window0.close(); DoubleHard(); RestartStatus = 0; Restart();
				}
			}
		}
		 
		Texture t0, t1; 
		t0.loadFromFile("Images/Screen/Opening #1.jpg"); Sprite sprite0(t0); //Source: https://apkpure.com/vn/snake-rivals-new-snake-games-in-3d/com.supersolid.snake
		t1.loadFromFile("Images/Screen/Textbox.png"); Sprite sprite1(t1);
		font.loadFromFile("Images/Times-New-Romans.ttf");
		//--- Drawing GUI ---
		window0.clear();
		sprite0.setPosition(0, 0); window0.draw(sprite0);
		sprite1.setPosition(0, 530); window0.draw(sprite1);
		Text text1, text2, text3, text4; 
		
		text1.setFont(font); 			text1.setString("How to play");
		text1.setCharacterSize(36); 	text1.setFillColor(Color::Red);
		text1.setStyle(Text::Bold | Text::Underlined); 	text1.setPosition(15, 535);
		window0.draw(text1);
		
		text2.setFont(font); 			text2.setString("Player #1: Use Arrows to control. \nPlayer #2: W(Up), S(Down), A(Left), D(Right). \n ----------------------------------------");
		text2.setCharacterSize(24); 	text2.setFillColor(Color::White);
		text2.setStyle(Text::Bold); 	text2.setPosition(15, 585);
		window0.draw(text2);
		
		text3.setFont(font); 			text3.setString("\n\nEsc: Return to GUI - R: Replay \nG + A: Game Paused - G + L: Game Played \nM + A: Music Paused - M + L: Music Played \nS + E = Single Easy Mode; S + H = Single Hard Mode; \nD + E = Double Easy Mode; D + H = Double Hard Mode; ");
		text3.setCharacterSize(20); 	text3.setFillColor(Color::White);
		text3.setStyle(Text::Bold); 	text3.setPosition(15, 620);
		window0.draw(text3);
		
		text4.setFont(font); 			text4.setString("SNAKE GAME");
		text4.setCharacterSize(100); 	text4.setFillColor(Color::Blue);
		text4.setStyle(Text::Bold); 	text4.setPosition(270, 100);
		window0.draw(text4);
		
		window0.display();
	}
}

int main()
{
	GUI();
	return 0;
}