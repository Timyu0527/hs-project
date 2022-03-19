#ifndef GOLLIB_H_INCLUDED
#define GOLLIB_H_INCLUDED
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;
const int ROW = 21, COLUMN = 21, frameRate = 240;
class Cell
{
    private:
        int around;
        bool isCell, isMouse;
        Cell() : isCell(false), isMouse(false), around(0) {}
        Cell(int orginX, int orginY) : isCell(false), isMouse(true), around(0) {}
        void setAroundCell(int iAround) {around = iAround;}
        bool callIsCell() {return isCell;}
        int callAround() {return around;}
        void modifyIsCell(bool iIsCell) {isCell = iIsCell;}
        void modifyIsMouse(bool iIsMouse) {isMouse = iIsMouse;}
        void display()
        {
            if(isMouse) cout << "[]";
            else if(isCell) cout << "▉";
            else cout << "  ";
        }
    public:
        friend class GameMap;
};

class GameMap
{
	private:
		vector<vector<Cell> > cells;
		pair<int, int> mouse;
		int row, column;
		bool play;
	public:
		GameMap() : mouse(pair<int, int>(1, 1)), row(ROW), column(COLUMN), play(false)
		{
			for(int i = -1; i < row+1; ++i)
			{
				vector<Cell> columnCell;
				for(int j = -1; j < column+1; ++j)
				{
					if(!i && !j) columnCell.push_back(Cell(j, i));
					else columnCell.push_back(Cell());
				}
				cells.push_back(columnCell);
			}
		}

		bool isPlay(){return play;}
		void countAroundCell()
		{
			int aroundCells;
			cells.at(mouse.first).at(mouse.second).modifyIsMouse(false);
			for(int i = 1; i < cells.size()-1; ++i)
			{
				for(int j = 1; j < cells.at(i).size()-1; ++j)
				{
					aroundCells = 0;
					for(int h = -1; h <= 1; ++h)
					{
						for(int k = -1; k <= 1; ++k)
						{
							if(cells.at(i+h).at(j+k).callIsCell() && (h != 0 || k != 0))
							{
								aroundCells++;
							}
						}
					}
					cells.at(i).at(j).setAroundCell(aroundCells);
				}
			}
		}

		void modifyAllMapIsCell()
		{
			for(int i = 1; i < cells.size(); ++i)
			{
				for(int j = 1; j < cells.at(i).size(); ++j)
				{
					if(cells.at(i).at(j).callAround() > 3 && cells.at(i).at(j).callIsCell())
					{
						cells.at(i).at(j).modifyIsCell(false);
					}
					else if(cells.at(i).at(j).callAround() == 3 && !cells.at(i).at(j).callIsCell())
					{
						cells.at(i).at(j).modifyIsCell(true);
					}
					else if(cells.at(i).at(j).callAround() < 2 && cells.at(i).at(j).callIsCell())
					{
						cells.at(i).at(j).modifyIsCell(false);
					}
				}
			}
		}

		void action()
        {
            if(kbhit())
            {
                int pressButton;
                cells.at(mouse.first).at(mouse.second).isMouse = false;
                pressButton = getch();
                if(pressButton == 224)
                {
                    pressButton = getch();
                    switch(pressButton)
                    {
                        case 75://UP
                            if(mouse.second > 1) --mouse.second;
                            break;
                        case 77://DOWN
                            if(mouse.second < row) ++mouse.second;
                            break;
                        case 72://LEFT
                            if(mouse.first > 1) --mouse.first;
                            break;
                        case 80://RIGHT
                            if(mouse.first < column) ++mouse.first;
                            break;
                    }
                }
                else if(pressButton == 32) cells.at(mouse.first).at(mouse.second).isCell = true;
                else if(pressButton == 13) play = true;
				cells.at(mouse.first).at(mouse.second).isMouse = true;
            }
        }

		void display()
		{
			cout << " ╔════════════════════════════════════════════╗ " << endl;
			for(int i = 1; i < cells.size()-1; ++i)
			{
				cout << " ║ ";
				for(int j = 1; j < cells.at(i).size()-1; ++j)
				   cells.at(i).at(j).display();
				cout << " ║ " << endl;
			}
			cout << " ╚════════════════════════════════════════════╝ " << endl;
			Sleep(1000/frameRate);
			system("cls");
		}

		void excute()
		{
            while(true)
            {
                action();
                if(isPlay())
                {
                    countAroundCell();
                    modifyAllMapIsCell();
                }
                display();
            }
		}
};
#endif // GOLLIB_H_INCLUDED
