/*
Name: Gilbert Grundy
Assignment: Lab #4
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <float.h>


//Data structure to deal with adjacency matrixes,
//and perform prim algorithm
struct matrix
{
	matrix(int size);	//constructor
	~matrix();		//destructor
	int load(float *first_row); //load user inputed matrix
	int display();		//display entered weighted adjacency matrix
	int prim();		//run prim algorithm
	void output_prim();	//display resulting WAM from the prim algorithm
	bool check_tree();	//check if the minimum spanning tree is connected
	float ** values;	//matrix values
	bool ** added;		//values used for the minimum spanning tree
	bool * vertices;	//vertices flag, for when a vertex is added
	int col_row;		//size of matrix
};

using namespace std;

int main()
{	//temporary row to represent a vertex
	float temp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	int j = 0; //index to load the temp vertex
	
	cout << "Gilbert Grundy CS251 Lab #4.\n";

	cout << "Enter WAM:\n\n";

	cin >> temp[0];
	j++;

	//collect first vertex
	while(cin.get() != '\n')
	{
		cin >> temp[j];
		++j;
	}

	matrix wam(j);		//data structure initialized
	wam.load(temp);		//load the values into WAM
	wam.display();		//display entered WAM
	cout << endl;		
	wam.prim();		//run Prim algorithm
	wam.output_prim();	//output resulting WAM

	cout << "\n\n";
		
	return 0;
}


//constructor of the maatrix data structure
//it takes in the size of the first vertex ti
//set up the matrix
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


//destructor deallocates memory of the matrix
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


//loads in the first vertex values, then
//collects the rest from the user
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


//display the user entered WAM
int matrix::display()
{
	int success = 0;

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


//Iterates the Prim algorithm, display each iteration of the
//algorithm as it adds a vertex and edge each step
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

	//while all of the trees vertex are not connnected this will loop
	//WARNING: if the graph is not connected, this will become an infinite loop 
	while(!check_tree())
	{
		for(int i = 0; i < col_row; ++i)
		{	
			if(vertices[i])	//if the vertex is part of the connect tree, then check it's edges
			{		//for the shortest path
				for(int j = 0; j < col_row; ++j)
				{	//if the edge is shorter than the previous shortest
					//and its value is above zero
					//and the edge has not been used already
					//and the edge isn't part of the main diaganol
					//then save this edge to compare
					if((values[i][j] <= smallest) && (values[i][j] > 0) && (!added[i][j]) && (i != j))
					{
						row = i;
						column = j;
						smallest = values[i][j];
					} 
				}
			}
		}
		
		//once out of the loop we know we have the next
		//vertex and edge to add, print out this information.

		cout << "    " << (k) << "      |       V";
		cout << (column + 1) << "        |      V";
		cout << (row + 1) << "-V" << (column + 1);
		cout << "        |      " << smallest << "\n";

		//save the vertex and edge we have found.
		vertices[column] = true;
		added[row][column] = true;
		added[column][row] = true;

		//reset values for next iteration
		k++;
		smallest = FLT_MAX;
		row = 0;
		column = 0;
	}

	cout << "\n\n";
	
	return k;
}


//output the WAM resulting from Prim's algorithm
void matrix::output_prim()
{
	float sum = 0;
	cout << "The output from Prim's Algorithm is:\n\n";

	//search matrix for on flags for values
	for(int i = 0; i < col_row; ++i)
	{
		for(int j = 0; j < col_row; ++j)
		{	//if flag is set then value part of MST
			if(added[i][j])
			{
				cout << values[i][j] << " ";
				sum += values[i][j];
			}//else it is zero
			else cout << "0 ";
		}
		cout << endl;
	}

	cout << "\nThe total weight of the graph is ";
	cout << (sum / 2);

	return;
}


//check if the tree has been connected
bool matrix::check_tree()
{
	bool check = true;
	for(int i = 0; i < col_row; ++i)
	{	//if a vertex flag is false the tree is not
		//fully connected, function will return false.
		if(!vertices[i]) check = false;
	}
	return check;
}
