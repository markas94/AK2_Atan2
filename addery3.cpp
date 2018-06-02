//c++ code to implement Half Adder  
#include "addery.h"
#include <iostream>
using namespace std;

int main()
{
	int k = 5; // IL. BITÓW

	int* wynik = new int[2 * k];

	// x = 01010
	// y = 10010

	int* x = new int[k];
	int* y = new int[k];

	int x0 = 0;
	int y0 = 0;

	int x1 = 1;
	int y1 = 1;

	int x2 = 0;
	int y2 = 0;

	int x3 = 1;
	int y3 = 0;

	int x4 = 0;
	int y4 = 1;

	x[0] = x0;
	y[0] = y0;

	x[1] = x1;
	y[1] = y1;

	x[2] = x2;
	y[2] = y2;

	x[3] = x3;
	y[3] = y3;

	x[4] = x4;
	y[4] = y4;

	HA* ha = new HA[k - 1];
	FA** fa = new FA*[k - 2]; //iloœæ linii "œrodkowych" FA na schemacie (bez linii HA i bez koñcowej)

	HA ha_k;
	FA* fa_k = new FA[k - 2]; //osobna tablica FA dla koñcowej linii na schemacie

	for (int i = 0; i < k - 2; i++)	// generowanie pojedynczych FA w ka¿dej linii œrodkowej (linie FA 2,3,4. pozycji x na schemacie Biernata)
	{
		fa[i + 2] = new FA[k - 1];
	}

	for (int i = 0; i < k - 1; i++) //generowanie pierwszej linii HA
	{
		cout << "HA" << i << ": " << endl;

		int pomocnicza_x = x[i] * y[1];
		int pomocnicza_y = x[i + 1] * y[0];
		ha[i].HalfAdderSum(pomocnicza_x, pomocnicza_y);
		ha[i].HalfAdderCarry(pomocnicza_x, pomocnicza_y);

		cout << "Suma: " << ha[i].sum << endl;
		cout << "Carry: " << ha[i].carry << endl;

		cout << endl;
	}

	int counter_i = 0;	//elementy FA (0-2) w jednej linii
	int counter_j = 0; // iloœæ linii FA
	int z_index = 2; //drugi skladnik mnozenie y ma w jednej linii przy mnozeniu staly indeks (np. a0x2)
	for (int j = 0; j < k - 2; j++)		//iloœæ linii FA
	{
		int i;
		for (i = 0; i < k - 2; i++)	//dla wiêkszoœci FA w jednej linii
		{
			fa[j + 2][i].FullAdderSum((x[i] * y[z_index]), ha[i + 1].sum, ha[i].carry);
			fa[j + 2][i].FullAdderCOut((x[i] * y[z_index]), ha[i + 1].sum, ha[i].carry);

			if (j == 1)
			{
				cout << "fa[j + 2][i] for i =  " << i  << "and z_index = " << z_index << ": " << fa[j + 2][i] << endl;
			}
		}
		fa[j + 2][i].FullAdderSum((x[i] * y[z_index]), (x[i + 1] * y[z_index - 1]), ha[i].carry);	//ostatni FA w linii jest inny
		fa[j + 2][i].FullAdderCOut((x[i] * y[z_index]), (x[i + 1] * y[z_index - 1]), ha[i].carry);

		/*if (j == 0 && z == 2)
		{
			cout << "fa[j + 2][i] for i =  " << i << ": " << fa[j + 2][i] << endl;
		}*/


		counter_i = i;
		counter_j = j;
		z_index++;
	}

	//OSTATNIA LINIA
	ha_k.HalfAdderSum(fa[counter_j + 2][counter_i - counter_i].sum, fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);		// pojedynczy HA ostatniej linii
	ha_k.HalfAdderCarry(fa[counter_j + 2][counter_i - counter_i].sum, fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);

	/*for (int i = 0; i < k - 2; i++)
	{
		fa_k[i];
	}*/

	int fak_i = 0;
	fa_k[fak_i].FullAdderSum(ha_k.carry, fa[counter_j + 2][(counter_i - counter_i) + 2].sum, fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);	//pierwszy FA koñcowy
	fa_k[fak_i].FullAdderCOut(ha_k.carry, fa[counter_j + 2][(counter_i - counter_i) + 2].sum, fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);
	int fak_srodkowe = 1;
	for (fak_i = 1; fak_i < k - 3; fak_i++)
	{
		fa_k[fak_i].FullAdderSum(fa_k[fak_i - 1].c_out, fa[counter_j + 2][(counter_i - counter_i) + 2].sum, fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);	//œrodkowe FA koñcowe 
		fa_k[fak_i].FullAdderCOut(fa_k[fak_i - 1].c_out, fa[counter_j + 2][(counter_i - counter_i) + 2].sum, fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);
		fak_srodkowe++;
	}
	fa_k[fak_i].FullAdderSum(fa_k[fak_i - 1].c_out, (x[counter_i + 1] * y[counter_j + 2]), fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);		//ostatni FA koñcowy
	fa_k[fak_i].FullAdderCOut(fa_k[fak_i - 1].c_out, (x[counter_i + 1] * y[counter_j + 2]), fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);

	//***Wydruk testowy***
	//FA
	for (int i = 0; i < k - 2; i++)
	{
		for (int j = 0; j < k - 1; j++)
		{
			cout << "fa[" << i + 2 << "][" << j << "]: " << endl << endl;
			cout << "x: " << fa[i + 2][j].x << endl;
			cout << "y: " << fa[i + 2][j].y << endl;
			cout << "c_in: " << fa[i + 2][j].c_in << endl;
			cout << "Suma: " << fa[i + 2][j].sum << endl;
			cout << "c_out: " << fa[i + 2][j].c_out << endl;
			cout << endl;
		}
	}

	//HA_K
	cout << "ha_k: " << endl << endl;
	cout << "x: " << ha_k.x << endl;
	cout << "y: " << ha_k.y << endl;
	cout << "Suma: " << ha_k.sum << endl;
	cout << "Carry: " << ha_k.carry << endl;
	cout << endl;

	//FA_K
	for (int i = 0; i < k - 2; i++)
	{
		cout << "fa_k[" << i << "]: " << endl << endl;
		cout << "x: " << fa_k[i].x << endl;
		cout << "y: " << fa_k[i].y << endl;
		cout << "c_in: " << fa_k[i].c_in << endl;
		cout << "Suma: " << fa_k[i].sum << endl;
		cout << "c_out: " << fa_k[i].c_out << endl;
		cout << endl;
	}
	//*********

	//WYNIK

	for (int i = 0; i < 2 * k; i++)
	{
		wynik[i] = 2;		//inicjalizacja pól tablicy wyniku
	}

	wynik[0] = x[0] * y[0];
	wynik[1] = ha[0].sum;
	for (int i = 2; i < k; i++)
	{
		wynik[i] = fa[i][0].sum;
	}
	wynik[k] = ha_k.sum;
	int zeruj_warun = 0;
	for (int i = k + 1; zeruj_warun < fak_srodkowe; i++)
	{
		wynik[i] = fa_k[i - (k + 1)].sum;
		zeruj_warun++;
	}
	wynik[k + fak_srodkowe + 1] = fa_k[fak_i].sum;
	wynik[k + fak_srodkowe + 2] = fa_k[fak_i].c_out;

	//drukuj wynik
	cout << "Wynik mnozenia: ";
	for (int i = (2 * k) - 1; i >= 0; i--)
	{
		cout << wynik[i];
	}
	cout << endl;


	delete[] x;
	delete[] y;

	delete[] ha;
	delete[] fa;

	delete[] fa_k;

	delete[]wynik;

	cout << endl;
	system("PAUSE");
	return 0;
}