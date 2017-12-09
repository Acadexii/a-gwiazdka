// ConsoleApplication8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>




using namespace std;
float F = 0;
float H;
float G = 2;
float minf = 99999;
float wylf = 0;
int aX = 0, aY = 0;
int tab[20][20] = { 0 };
int tabKoncowe[20][20] = { 0 };
int hx, hy, bx, by;
int LO[20][20] = { 0 };
int LZ[20][20] = { 0 };
int rodzicX[20][20] = { 0 };
int rodzicY[20][20] = { 0 };
int startx = 0, starty = 0, metax = 19, metay = 19;
int xxx;
int pox[4] = { 0,0,-1,1 };
int poy[4] = { 1,-1,0,0 };
int wartoscG[20][20] = { 0 };
int d, e;

void zaladujtablice()
{
	cout << "Wczytywanie danych z pliku\n";

	string nazwap = "grid.txt";
	int wym2 = 20;
	int wym1 = 20;

	//teraz deklarujemy dynamicznie tablice do, której wczytamyu nasz plik,
	int rows = wym2 + 1;
	double **G;
	G = new double*[rows];
	while (rows--) G[rows] = new double[wym1 + 1];

	cout << "\n\nNacisnij ENTER aby wczytac tablice o nazwie " << nazwap;
	getchar();

	std::ifstream plik(nazwap.c_str());

	for (unsigned int i = 1; i < wym2 + 1; i++)
	{
		for (unsigned int j = 1; j < wym1 + 1; j++)
		{
			plik >> G[i][j];
		}
	}
	plik.close();

	cout << "\nWypisujemy na ekran\n\n";
	for (int i = 1; i < wym2 + 1; i++)
	{
		for (int j = 1; j < wym1 + 1; j++)
		{
			cout << " " << G[i][j];
			tab[(i - 1)][(j - 1)] = G[i][j];
		}cout << "\n";
	}

	//na koniec czyœcimy pamiêæ po naszej tablicy
	for (int i = 0; i < wym2 + 1; i++)
	{
		delete[] G[i];
	}//czyscimy wiersze
	delete[] G;//zwalniamy tablice wskaznikow do wierszy

	cout << "\n\nNacisnij ENTER aby zakonczyc";
	getchar();
	for (int i = 0; i < wym2; i++)
	{
		for (int j = 0; j < wym1; j++)
		{
			cout << " " << tab[i][j];

		}cout << "\n";
	}
	getchar();
}
float PoliczH(int x, int y)
{
	//return  H = (sqrt((hx - 0)*(hx - 0) + (hy - 4)*(hy - 4)));
	return  H = (sqrt((x - 19)*(x - 19) + (y - 19)*(y - 19)));
}
float PoliczF(int x, int y)
{
	return wylf = H + wartoscG[x][y];
}
void nadanieRodzica(int x, int y)
{
	rodzicX[x][y] = aX;
	rodzicY[x][y] = aY;
}
void kierunki(int x, int y) // 0 0
{
	int i = 0;
	for (i; i < 4; i++)
	{
		//LZ[(x + pox[i])][(y = poy[i]) == 1]
		if ((x + pox[i]) < 0 || (x + pox[i]) > 19 || (y + poy[i]) < 0 || (y + poy[i]) > 19 || LZ[(x + pox[i])][(y + poy[i])] == 1 || LO[(x + pox[i])][(y + poy[i])] == 1 || tab[(x + pox[i])][(y + poy[i])] == 5)
		{
			/*cout << "poza tablic¹ lub sciana   " << (x + pox[i])<<   "   "  << y << "     " << (y + poy[i]) <<endl;*/
		}
		else {
			hx = x + pox[i];
			hy = y + poy[i];
			bx = x;
			by = y;
			wartoscG[hx][hy] = (wartoscG[x][y] + 1);
			nadanieRodzica(hx, hy);
			LO[hx][hy] = 1;
			/*cout << "otwarty LO :" << hx << "  " << hy << endl;*/
		}
	}
}


void najmniejszef(int x, int y)
{
	PoliczH(x, y);
	PoliczF(x, y);
	if (minf > wylf)
	{
		minf = wylf;
		aX = x;
		aY = y;
		//nadanieRodzica(bx, by);
	}
}

void przeszukanieLO()
{
	minf = 99999;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if ((LO[i][j] == 1 && LZ[i][j] != 1 && tab[i][j] != 5))
			{
				najmniejszef(i, j);
			}
		}
	}
	//d = i; e = j;
	/*cout << "Najmniejsze elf " << wylf << endl;*/
}


int main()
{
	LO[0][0] = 1;
	zaladujtablice();
	bool koniec = false;
	while (koniec != true && !(aX == 19 && aY == 19))
	{
		kierunki(aX, aY);
		LZ[aX][aY] = 1;
		int d = aX;
		int e = aY;
		przeszukanieLO();
		if ((aX == d && aY == e))
		{
			//return 0;
			koniec = true;
		}

	}
	if (koniec == false) {
		cout << endl<<"Lista zamknieta :" << endl;
		for (int i = 0; i < 20; i++)
		{
			cout << endl;
			for (int j = 0; j < 20; j++)
			{
				cout << LZ[i][j] << "  ";
			}
		}
		cout << endl << endl << "Rodzic X" << endl;
		for (int i = 0; i < 20; i++)
		{
			cout << endl;
			for (int j = 0; j < 20; j++)
			{
				cout << rodzicX[i][j] << "   ";

			}
		}
		cout << endl << endl << "Rodzic Y " << endl;
		for (int i = 0; i < 20; i++)
		{
			cout << endl;
			for (int j = 0; j < 20; j++)
			{
				cout << rodzicY[i][j] << "   ";
			}
		}
		cout << endl << endl;
		int xx = metax;
		int yy = metay;
		tab[metax][metay] = 3;
		tab[startx][starty] = 3;
		while (!(rodzicX[xx][yy] == startx && rodzicY[xx][yy] == starty))
		{
			tab[rodzicX[xx][yy]][rodzicY[xx][yy]] = 3;
			xxx = xx;
			xx = rodzicX[xx][yy];
			yy = rodzicY[xxx][yy];
		}
		cout << endl << " Mapka z sciezka i przeszkodami i wogole:" << endl;
		for (int i = 0; i < 20; i++)
		{
			cout << endl;
			for (int j = 0; j < 20; j++)
			{
				cout << tab[i][j] << " ";
			}
		}
		cout << endl << endl;
	}
	else {
		cout <<endl<< "Nie ma sciezki" << endl;
	}
	getchar();
	return 0;
}

