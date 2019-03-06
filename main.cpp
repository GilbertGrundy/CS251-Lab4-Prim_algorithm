/*
Name: Gilbert Grundy
Assignment: Lab #4
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <float.h>

struct matrix
{
	matrix(int size);
	~matrix();
	int load(float *first_row);
	int display();
	int prim();
	void output_prim();
	bool check_tree();
	float ** values;
	bool ** added;
	bool * vertices;
	int col_row;
};

using namespace std;

int main()
{
	float temp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int j = 0;
	
	cout << "Gilbert Grundy CS251 Lab #4.\n";

	cout << "Enter WAM:\n\n";

	cin >> temp[0];
	j++;

	while(cin.get() != '\n')
	{
		cin >> temp[j];
		++j;
	}


	matrix wam(j);
	wam.load(temp);
	wam.display();
	cout << endl;
	wam.prim();
	wam.output_prim();

	cout << "\n\n";
		
	return 0;
}


matrix::matrix(int size)
{
	col_row = size;
	vertices = new bool [col_row];
	values = new float * [col_row];
	added = new bool * [col_row];
	
	for(int i = 0; i < col_row; ++i)
	{
		values[i] = new float [col_row];
		added[i] = new bool [col_row];
	}
	
	for(int i = 0; i < col_row; ++i)
	{
		vertices[i] = false;
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
	
	if(vertices) delete [] vertices;
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
	
	//cout << "WAM is:\n\n";

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

int matrix::prim()
{
	float smallest = FLT_MAX;
	int row = 0;
	int column = 0;
	int k = 0;

	cout << "Iteration  |  Vertice added  |    Edge added     |     Weight\n";
	cout << "-------------------------------------------------------------------\n";

	vertices[k] = true;
	k++;

	cout << "    0      |       V1        |                   |\n";

	while(!check_tree())
	{
		for(int i = 0; i < col_row; ++i)
		{
			if(vertices[i])
			{
				for(int j = 0; j < col_row; ++j)
				{
					if((values[i][j] <= smallest) && (values[i][j] > 0) && (!added[i][j]))
					{
						row = i;
						column = j;
						smallest = values[i][j];
					} 
				}
			}
		}

		cout << "    " << (k) << "      |       V";
		cout << (column + 1) << "        |      V";
		cout << (row + 1) << "-V" << (column + 1);
		cout << "        |      " << smallest << "\n";

		k++;
		vertices[column] = true;
		added[row][column] = true;
		added[column][row] = true;
		smallest = FLT_MAX;
		row = 0;
		column = 0;
	}

	cout << "\n\n";
	
	return k;
}

void matrix::output_prim()
{
	float sum = 0;
	cout << "The output from Prim's Algorithm is:\n\n";

	for(int i = 0; i < col_row; ++i)
	{
		for(int j = 0; j < col_row; ++j)
		{
			if(added[i][j])
			{
				cout << values[i][j] << " ";
				sum += values[i][j];
			}
			else cout << "0 ";
		}
		cout << endl;
	}

	cout << "\nThe total weight of the graph is ";
	cout << (sum / 2);

	return;
}

bool matrix::check_tree()
{
	bool check = true;
	for(int i = 0; i < col_row; ++i)
	{
		if(!vertices[i]) check = false;
	}
	return check;
}
