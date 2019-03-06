/*
Name: Gilbert Grundy
Assignment: Lab #4
*/

#include <iostream>
#include <fstream>
#include <cstring>

struct matrix
{
	matrix(int size);
	~matrix();
	int load(float *first_row);
	int display();
	float ** values;
	bool ** added;
	int col_row;
};

using namespace std;

int main()
{
	float temp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int j = 0;
	
	cout << "Gilbert Grundy CS251 Lab #4.\n";

	cin >> temp[0];
	j++;

	while(cin.get() != '\n')
	{
		cin >> temp[j];
		++j;
	}


	matrix wam(j);
	matrix mst(j);
	wam.load(temp);
	wam.display();

		
	return 0;
}


matrix::matrix(int size)
{
	col_row = size;
	values = new float * [col_row];
	added = new bool * [col_row];
	
	for(int i = 0; i < col_row; ++i)
	{
		values[i] = new float [col_row];
		added[i] = new bool [col_row];
	}
	
	for(int i = 0; i < col_row; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			added[i][j] = false;
			values[i][j] = 0;
		}
	}
}

matrix::~matrix()
{
	for(int i = 0; i < col_row; ++i)
	{
		if(added[i]) delete [] added[i];
		if(values[i]) delete [] values[i];
	}
	
	if(added) delete [] added;	
	if(values) delete [] values;
}

int matrix::load(float *first_row)
{
	int success = 0;
	for(int i = 0; i < col_row; ++i)
	{
		values[0][i] = first_row[i];
		++success;
	}
	
	for(int i = 1; i < col_row; ++i)
	{
		for(int j = 0; j < col_row; ++j)
		{
			cin >> values[i][j];
			++success;
		}
	}

	return success;
}

int matrix::display()
{
	int success = 0;
	
	cout << "WAM is:\n\n";

	for(int i = 0; i < col_row; ++i)
	{
		for(int j = 0; j < col_row; ++j)
		{
			cout << values[i][j] << " ";
			++success;
		}
		cout << endl;
	}

	return success;
}

