//c++ code to implement Half Adder  
#include "addery.h"
#include <iostream>
using namespace std;

int main()
{
	int k = 1; // IL. BITÓW

	int* wynik = new int[2 * k];

	// x = 01010
	// y = 10010

	int* x = new int[k];
	int* y = new int[k];

	int x0 = 0;
	int y0 = 0;

	/*int x1 = 1;
	int y1 = 1;

	int x2 = 0;
	int y2 = 0;

	int x3 = 1;
	int y3 = 0;

	int x4 = 0;
	int y4 = 1;

	int x5 = 1;
	int y5 = 1;
	*/

	x[0] = x0;
	y[0] = y0;

	/*x[1] = x1;
	y[1] = y1;

	x[2] = x2;
	y[2] = y2;

	x[3] = x3;
	y[3] = y3;

	x[4] = x4;
	y[4] = y4;

	x[5] = x5;
	y[5] = y5;*/


	switch (k)
	{
		case 0:
		{
			cout << "il. bitow (k) = 0 !" << endl;
			break;
		}
		case 1:
		{
			//WYNIK
			int wynik_1 = x[0] * y[0];
			cout << "Wynik mnozenia: " << wynik_1 << endl;

			cout << endl;
			system("PAUSE");

			break;
		}
		case 2:
		{
			HA ha;
			HA ha_k;
			
			int pomocnicza_x = x[0] * y[1];
			int pomocnicza_y = x[1] * y[0];
			ha.HalfAdderSum(pomocnicza_x, pomocnicza_y);
			ha.HalfAdderCarry(pomocnicza_x, pomocnicza_y);

			//LINIA KONCOWA
			ha_k.HalfAdderSum(ha.carry, (x[1] * y[1]));		// pojedynczy HA ostatniej linii
			ha_k.HalfAdderCarry(ha.carry, (x[1] * y[1]));
			
			//WYNIK
			wynik[0] = x[0] * y[0];
			wynik[1] = ha.sum;
			wynik[2] = ha_k.sum;
			wynik[3] = ha_k.carry;
			
			//drukuj wynik
			cout << "Wynik mnozenia: ";
			for (int i = (2 * k) - 1; i >= 0; i--)
			{
				cout << wynik[i];
			}
			
			cout << endl;
			system("PAUSE");

			//ZWALNIANIE PAMIECI
			wynik = nullptr;
			delete[] wynik;

			x = nullptr;
			delete[] x;
			y = nullptr;
			delete[] y;

			break;
		}
		case 3:
		{
			HA* ha = new HA[k - 1];
			HA ha_k;

			FA** fa = new FA*[k - 2]; //iloœæ linii "œrodkowych" FA na schemacie (bez linii HA i bez koñcowej)
			FA* fa_k = new FA[k - 2]; //osobna tablica FA dla koñcowej linii na schemacie

			for (int i = 0; i < k - 2; i++)	// generowanie pojedynczych FA w ka¿dej linii œrodkowej (linie FA 2,3,4. pozycji x na schemacie Biernata)
			{
				fa[i + 2] = new FA[k - 1];
			}
			
			for (int i = 0; i < k - 1; i++) //generowanie pierwszej linii HA
			{
				int pomocnicza_x = x[i] * y[1];
				int pomocnicza_y = x[i + 1] * y[0];
				ha[i].HalfAdderSum(pomocnicza_x, pomocnicza_y);
				ha[i].HalfAdderCarry(pomocnicza_x, pomocnicza_y);
			}
			
			//PIERWSZA LINIA SRODKOWA FA
			int i_fa_w_linii;
			for (i_fa_w_linii = 0; i_fa_w_linii < k - 2; i_fa_w_linii++)	//dla wiêkszoœci FA w jednej linii
			{
				fa[2][i_fa_w_linii].FullAdderSum((x[i_fa_w_linii] * y[2]), ha[i_fa_w_linii + 1].sum, ha[i_fa_w_linii].carry);
				fa[2][i_fa_w_linii].FullAdderCOut((x[i_fa_w_linii] * y[2]), ha[i_fa_w_linii + 1].sum, ha[i_fa_w_linii].carry);

			}
			fa[2][i_fa_w_linii].FullAdderSum((x[i_fa_w_linii] * y[2]), (x[i_fa_w_linii + 1] * y[1]), ha[i_fa_w_linii].carry);	//ostatni FA w linii jest inny
			fa[2][i_fa_w_linii].FullAdderCOut((x[i_fa_w_linii] * y[2]), (x[i_fa_w_linii + 1] * y[1]), ha[i_fa_w_linii].carry);

			//POZOSTALE LINIE SRODKOWE FA - tylko inicjalizacja zmiennych	
			int counter_i = i_fa_w_linii;	//elementy FA (0-2) w jednej linii
			int counter_j = 0; // ilosc linii FA
			//OSTATNIA LINIA
			ha_k.HalfAdderSum(fa[counter_j + 2][counter_i - counter_i].c_out, fa[counter_j + 2][(counter_i - counter_i) + 1].sum);		// pojedynczy HA ostatniej linii
			ha_k.HalfAdderCarry(fa[counter_j + 2][counter_i - counter_i].c_out, fa[counter_j + 2][(counter_i - counter_i) + 1].sum);
			
			int fak_i = 0;
			int fak_srodkowe_dla_wyniku = 1;	//to samo co w int fak_srodkowe, ale globalnie
			fa_k[fak_i].FullAdderSum(ha_k.carry, (x[counter_i + 1] * y[counter_j + 2]), fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);		//ostatni FA koñcowy
			fa_k[fak_i].FullAdderCOut(ha_k.carry, (x[counter_i + 1] * y[counter_j + 2]), fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);
			
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

			wynik[k + 1] = fa_k[fak_i].sum;
			wynik[k + 2] = fa_k[fak_i].c_out;
			
			//drukuj wynik
			cout << "Wynik mnozenia: ";
			for (int i = (2 * k) - 1; i >= 0; i--)
			{
				cout << wynik[i];
			}
			
			cout << endl;
			system("PAUSE");

			//ZWALNIANIE PAMIECI
			wynik = nullptr;
			delete[] wynik;

			fa_k = nullptr;
			delete[] fa_k;

			for (int i = 0; i < k - 2; i++)
			{
				fa[i + 2] = nullptr;
				delete[] fa[i + 2];
			}
			fa = nullptr;
			delete[] fa;

			ha = nullptr;
			delete[] ha;

			x = nullptr;
			delete[] x;
			y = nullptr;
			delete[] y;

			break;
		}
		default:
		{
			HA* ha = new HA[k - 1];
			HA ha_k;

			FA** fa = new FA*[k - 2]; //iloœæ linii "œrodkowych" FA na schemacie (bez linii HA i bez koñcowej)
			FA* fa_k = new FA[k - 2]; //osobna tablica FA dla koñcowej linii na schemacie

			for (int i = 0; i < k - 2; i++)	// generowanie pojedynczych FA w ka¿dej linii œrodkowej (linie FA 2,3,4. pozycji x na schemacie Biernata)
			{
				fa[i + 2] = new FA[k - 1];
			}
			
			for (int i = 0; i < k - 1; i++) //generowanie pierwszej linii HA
			{
				int pomocnicza_x = x[i] * y[1];
				int pomocnicza_y = x[i + 1] * y[0];
				ha[i].HalfAdderSum(pomocnicza_x, pomocnicza_y);
				ha[i].HalfAdderCarry(pomocnicza_x, pomocnicza_y);
			}

			//PIERWSZA LINIA SRODKOWA FA
			int i_fa_w_linii;
			for (i_fa_w_linii = 0; i_fa_w_linii < k - 2; i_fa_w_linii++)	//dla wiêkszoœci FA w jednej linii
			{
				fa[2][i_fa_w_linii].FullAdderSum((x[i_fa_w_linii] * y[2]), ha[i_fa_w_linii + 1].sum, ha[i_fa_w_linii].carry);
				fa[2][i_fa_w_linii].FullAdderCOut((x[i_fa_w_linii] * y[2]), ha[i_fa_w_linii + 1].sum, ha[i_fa_w_linii].carry);

			}
			fa[2][i_fa_w_linii].FullAdderSum((x[i_fa_w_linii] * y[2]), (x[i_fa_w_linii + 1] * y[1]), ha[i_fa_w_linii].carry);	//ostatni FA w linii jest inny
			fa[2][i_fa_w_linii].FullAdderCOut((x[i_fa_w_linii] * y[2]), (x[i_fa_w_linii + 1] * y[1]), ha[i_fa_w_linii].carry);

			//POZOSTALE LINIE SRODKOWE FA	
			int counter_i = i_fa_w_linii;	//elementy FA (0-2) w jednej linii
			int counter_j = 0; // ilosc linii FA
			int z_index = 3; //drugi skladnik mnozenie y ma w jednej linii przy mnozeniu staly indeks (np. a0x2)
			for (int j = 1; j < k - 2; j++)		//iloœæ linii FA
			{
				int i;
				for (i = 0; i < k - 2; i++)	//dla wiêkszoœci FA w jednej linii
				{
					fa[j + 2][i].FullAdderSum((x[i] * y[z_index]), fa[j + 1][i + 1].sum, fa[j + 1][i].c_out);
					fa[j + 2][i].FullAdderCOut((x[i] * y[z_index]), fa[j + 1][i + 1].sum, fa[j + 1][i].c_out);

				}
				fa[j + 2][i].FullAdderSum((x[i] * y[z_index]), (x[i + 1] * y[z_index - 1]), fa[j + 1][i].c_out);	//ostatni FA w linii jest inny
				fa[j + 2][i].FullAdderCOut((x[i] * y[z_index]), (x[i + 1] * y[z_index - 1]), fa[j + 1][i].c_out);

				counter_i = i;
				counter_j = j;
				z_index++;
			}
			//OSTATNIA LINIA
			ha_k.HalfAdderSum(fa[counter_j + 2][counter_i - counter_i].c_out, fa[counter_j + 2][(counter_i - counter_i) + 1].sum);		// pojedynczy HA ostatniej linii
			ha_k.HalfAdderCarry(fa[counter_j + 2][counter_i - counter_i].c_out, fa[counter_j + 2][(counter_i - counter_i) + 1].sum);
			
			int fak_i = 0;
			int fak_srodkowe_dla_wyniku = 1;	//to samo co w int fak_srodkowe, ale globalnie
			fa_k[fak_i].FullAdderSum(ha_k.carry, fa[counter_j + 2][(counter_i - counter_i) + 2].sum, fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);	//pierwszy FA koñcowy
			fa_k[fak_i].FullAdderCOut(ha_k.carry, fa[counter_j + 2][(counter_i - counter_i) + 2].sum, fa[counter_j + 2][(counter_i - counter_i) + 1].c_out);
			int fak_srodkowe = 1;
			for (fak_i = 1; fak_i < k - 3; fak_i++)
			{
				fa_k[fak_i].FullAdderSum(fa_k[fak_i - 1].c_out, fa[counter_j + 2][fak_srodkowe + 2].sum, fa[counter_j + 2][fak_srodkowe + 1].c_out);	//œrodkowe FA koñcowe 
				fa_k[fak_i].FullAdderCOut(fa_k[fak_i - 1].c_out, fa[counter_j + 2][fak_srodkowe + 2].sum, fa[counter_j + 2][fak_srodkowe + 1].c_out);
				fak_srodkowe++;
			}
			fa_k[fak_i].FullAdderSum(fa_k[fak_i - 1].c_out, (x[counter_i + 1] * y[counter_j + 2]), fa[counter_j + 2][fak_srodkowe + 1].c_out);		//ostatni FA koñcowy
			fa_k[fak_i].FullAdderCOut(fa_k[fak_i - 1].c_out, (x[counter_i + 1] * y[counter_j + 2]), fa[counter_j + 2][fak_srodkowe + 1].c_out);
			fak_srodkowe_dla_wyniku = fak_srodkowe;
			
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
			for (int i = k + 1; zeruj_warun < fak_srodkowe_dla_wyniku; i++)
			{
				wynik[i] = fa_k[i - (k + 1)].sum;
				zeruj_warun++;
			}
			wynik[k + fak_srodkowe_dla_wyniku + 1] = fa_k[fak_i].sum;
			wynik[k + fak_srodkowe_dla_wyniku + 2] = fa_k[fak_i].c_out;
			
			//drukuj wynik
			cout << "Wynik mnozenia: ";
			for (int i = (2 * k) - 1; i >= 0; i--)
			{
				cout << wynik[i];
			}
			
			cout << endl;
			system("PAUSE");

			//ZWALNIANIE PAMIECI
			wynik = nullptr;
			delete[] wynik;

			fa_k = nullptr;
			delete[] fa_k;

			for (int i = 0; i < k - 2; i++)
			{
				fa[i + 2] = nullptr;
				delete[] fa[i + 2];
			}
			fa = nullptr;
			delete[] fa;

			ha = nullptr;
			delete[] ha;

			x = nullptr;
			delete[] x;
			y = nullptr;
			delete[] y;
			break;
		}
	}

	wynik = nullptr;
	delete[] wynik;

	return 0;
}