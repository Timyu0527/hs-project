#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h> 

using namespace std;

void Setup(), Draw(), Move(), Eat(), Turn(), Over(), Start(), End();

int len = 1, dif = 0, score = 0;
int headx, heady, bodyx[50], bodyy[50];
int foodx, foody, testx, testy;
int textx, texty, maxx, maxy, WallMode = 0;
char ch, arr[50];
enum Direction{UP, DOWN, RIGHT, LEFT};
Direction dir;
bool GameOver = false;

int main()
{
	initwindow(1344, 704, "Snake Game");
	Setup();
	Start();
	while (!GameOver) 
	{
		Turn();
		Move();
		Draw();
		Eat();
		Over();
		delay(dif);
	}
	delay(250);
	cleardevice();
	setbkcolor(BLACK);
	End();
	closegraph();
	getch();					
}
void Setup()
{
	srand(time(NULL));
	maxx = getmaxx() / 2;
	maxy = getmaxy() / 2;
	headx = 600;
	heady = 300;
	foodx = rand() % 1000 + 200;
	foody = rand() % 300 + 200;
	if(foodx % 20 != 0 || foody % 20 != 0)
	{
		foodx -= foodx % 20;
		foody -= foody % 20;
	}
}
void Draw()
{
	setcolor(WHITE);
	setlinestyle(0, 0, 10);
	setfillstyle(SOLID_FILL, BLACK);
	bar3d(100, 100, 1200, 600, 0, 1);
	
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	sprintf(arr, "Score: %d", score);
	outtextxy(0, 0, arr);
	
	setcolor(WHITE);
	setlinestyle(0, 0, 2);
	setfillstyle(SOLID_FILL, RED);
	bar3d(foodx - 7, foody - 7, foodx + 7, foody + 7, 0, 1);
	
	setcolor(WHITE);
	setlinestyle(0, 0, 2);
	setfillstyle(SOLID_FILL, GREEN);
	bar3d(headx - 10, heady - 10, headx + 10, heady + 10, 0, 1);
	
	for(int i = 0; i < len; i++)
	{
		setfillstyle(SOLID_FILL, GREEN);
		bar3d(bodyx[i] - 8, bodyy[i] - 8, bodyx[i] + 8, bodyy[i] + 8, 0, 1);
	}
}
void Move()
{
	int prevx = bodyx[0];
    int prevy = bodyy[0];
    int prev2x, prev2y;
    bodyx[0] = headx;
    bodyy[0] = heady;
    for (int i = 1; i < len; i++)
    {
        prev2x = bodyx[i];
        prev2y = bodyy[i];
        bodyx[i] = prevx;
        bodyy[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch(dir)
    {
       	case UP:
       		heady += 20;
       		break;
       	case DOWN:
       		heady -= 20;
       		break;
       	case RIGHT:
       		headx += 20;
       		break;
       	case LEFT:
       		headx -= 20;
       		break;
	}
}
void Eat()
{
	if(headx + 9 >= foodx - 9 && heady + 9 <= foody + 9 && heady + 9 >= foody - 9 && headx + 9 <= foodx + 9)
	{
		testx = rand() % 1000 + 200;
		testy = rand() % 360 + 200;
		len++;
		score++;
	}
	else if(headx - 9 >= foodx - 9 && heady - 9 <= foody + 9 && heady - 9 >= foody - 9 && headx - 9 <= foodx + 9)
	{
		testx = rand() % 1000 + 200;
		testy = rand() % 360 + 200;
		len++;
		score++;
	}
	else if(headx + 9 >= foodx - 9 && heady - 9 <= foody + 9 && heady - 9 >= foody - 9 && headx + 9 <= foodx + 9)
	{
		testx = rand() % 1000 + 200;
		testy = rand() % 360 + 200;
		len++;
		score++;
	}
	else if(headx - 9 >= foodx - 9 && heady + 9 <= foody + 9 && heady + 9 >= foody - 9 && headx - 9 <= foodx + 9)
	{
		testx = rand() % 1000 + 200;
		testy = rand() % 360 + 200;
		len++;
		score++;
	}
	for(int i = 0; i < len; i++)
	{
		if(bodyx[i] == testx && bodyy[i] == testy)
		{
			testx = rand() % 1000 + 200;
			testy = rand() % 360 + 200;
		}
	}
	if(testx % 20 != 0 || testy % 20 != 0)
	{
		foodx = testx - testx % 20;
		foody = testy - testy % 20;
	}
}
void Turn()
{
	if(kbhit())
	{
    	switch(getch())
		{
     		case 0x50: // UP
     			if(dir != DOWN) dir = UP;
     			break;
     		case 0x48: // DOWN
    			if(dir != UP) dir = DOWN;
    			break;
    		case 0x4d: // Right
    			if(dir != LEFT) dir = RIGHT;
    			break;
    		case 0x4b: // Left
				if(dir != RIGHT) dir = LEFT;
     			break;
     	}
    }
}
void Over()
{
	switch(WallMode)
	{
		case '1':
			if(headx - 10 <= 100 || headx + 10 >= 1200 || heady - 10 <= 100 || heady + 10 >= 600)
				GameOver = true;
			break;
		case '2':
			if(headx + 9 >= 1180 ) headx = 120;
			if(headx - 9 <= 120) headx = 1180;
			if(heady - 9 <= 120) heady = 580;
			if(heady + 9 >= 580) heady = 120;
			break;				
	}
	if(len == 51)
	{
		GameOver = true;
	}
	for(int i = 0; i < len; i++)
	{
		if(headx == bodyx[i] && heady == bodyy[i])
		{
			GameOver = true;
		}
	}
}
void Start()
{
	while(!kbhit())
	{
		setbkcolor(BLACK);
		setcolor(GREEN);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 6);
		outtextxy(maxx - textwidth("Snake") / 2, maxy - textheight("Snake") / 2 - 30, "Snake");
		
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 6);
		outtextxy(maxx - textwidth("Game") / 2 ,maxy - textheight("Game") / 2 + 30, "Game");
		
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
		outtextxy(maxx - textwidth("Press the Enter to continue") / 2, maxy - textheight("Press the Enter to continue") + 100, "Press the Enter to continue");
		
	}
	cleardevice();
	while(dif == 0)
	{
		setbkcolor(BLACK);
		setcolor(GREEN);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 6);
		outtextxy(maxx- textwidth("Speed:") / 2, maxy - textheight("Speed:") / 2 - 200, "Speed:");
		outtextxy(maxx - textwidth("1.Slow") / 2, maxy - textheight("1.Slow") / 2 - 100, "1.Slow");
		outtextxy(maxx - textwidth("2.Normal") / 2, maxy - textheight("2.Normal") / 2, "2.Normal");
		outtextxy(maxx - textwidth("3.Fast") / 2, maxy - textheight("3.Fast") / 2 + 100, "3.Fast");
		if(kbhit)
		{
			switch(getch())
			{
				case '1':
					dif = 150;
					break;
				case '2':
					dif = 100;
					break;
				case '3':
					dif = 50;
					break;
			}
		}
	}
	cleardevice();
	while(WallMode == 0)
	{
		setbkcolor(BLACK);
		setcolor(GREEN);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 6);
		outtextxy(maxx - textwidth("1.Wall") / 2, maxy - textheight("1.Wall") / 2, "1.Wall");
		outtextxy(maxx - textwidth("2.No Wall") / 2, maxy - textheight("2.No Wall") / 2 + 100, "2.No Wall");
		WallMode = getch();
	}
}
void End()
{
	if(GameOver && len == 51)
	{
		setcolor(YELLOW);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
		outtextxy(maxx - textheight("You Win"), maxy - textwidth("You Win"), "You Win");
	}
	else if(GameOver)
	{
		setcolor(RED);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
		outtextxy(maxx - textwidth("Game Over") / 2, maxy - textheight("Game Over") / 2, "Game Over");
		
	}
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	sprintf(arr, "Score: %d", score);
	outtextxy(maxx - textwidth("Score:") / 2 - 10, maxy - textheight("Score:") / 2 + 50, arr);
	while(GameOver && !kbhit())
	{
		delay(10);
	}
}
