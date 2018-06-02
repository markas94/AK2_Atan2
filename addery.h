#include <iostream>
using namespace std;

class HA
{
public:
	int x, y, sum, carry;

	HA();
	//~HA();
	
	int HalfAdderSum(int x, int y)
	{
		this->x = x;
		this->y = y;

		sum = x ^ y;

		this->sum;

		return sum;
	}

	int HalfAdderCarry(int x, int y)
	{
		this->x = x;
		this->y = y;

		carry = x & y;

		this->carry;

		return carry;
	}

	friend ostream & operator<< (ostream &wyjscie, HA &czytobiektHA);

};

HA::HA()
{
	x = y = sum = carry = 2;
}

class FA
{
public:
	int x, y, c_in, sum, c_out;

	FA();
	//~FA();

	int FullAdderSum(int x, int y, int c_in)
	{
		this->x = x;
		this->y = y;
		this->c_in = c_in;

		sum = ((x ^ y) ^ c_in);

		this->sum = sum;

		return sum;
	}

	int FullAdderCOut(int x, int y, int c_in)
	{
		this->x = x;
		this->y = y;
		this->c_in = c_in;

		c_out = (((x ^ y) & c_in) | (x & y));

		this->c_out = c_out;

		return c_out;
	}

	friend ostream & operator<< (ostream &wyjscie, FA &czytobiektFA);
};

FA::FA()
{
	x = y = c_in = sum = c_out = 3;
}

ostream & operator<< (ostream &wyjscie, HA &czytobiektHA)
{
	return wyjscie << "HA.x: " << czytobiektHA.x << " HA.y: " << czytobiektHA.y << " HA.sum: " << czytobiektHA.sum << " HA.carry: " << czytobiektHA.carry << endl;
}

ostream & operator<< (ostream &wyjscie, FA &czytobiektFA)
{
	return wyjscie << "FA.x: " << czytobiektFA.x << " FA.y: " << czytobiektFA.y << " FA.c_in: " << czytobiektFA.c_in << " FA.sum: " << czytobiektFA.sum << " FA.c_out: " << czytobiektFA.c_out << endl;
}


