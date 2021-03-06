// matrix_practice.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <tuple>
#include "matrix.h"
#include <string>

using namespace std;
template <typename T>
T getUserInput(void);
tuple<int, int> getDimFromUserInput(void);
Matrix getMatrixFromUserInput(matrixSize);
void freeMatrix(int**, int);

void test()
{
	cout << "############" << endl;
	int** a1{new int*[2]};
	int a11[]{1, 2};
	int a12[]{3, 4};
	a1[0] = a11;
	a1[1] = a12;
	int** b1{new int*[2]};
	int b11[]{2, 0};
	int b12[]{1, 2};
	b1[0] = b11;
	b1[1] = b12;
	Matrix matrixA{2, 2, a1};
	Matrix matrixB{2, 2, b1};
	cout << "MatrixA" << "\n";
	matrixA.print();
	cout << "MatrixB" << "\n";
	matrixB.print();
	Matrix sum{};
	sum = matrixA.add(matrixB);
	cout << "sum" << endl;
	sum.print();
	Matrix mul{};
	mul = matrixA.mul(matrixB);
	cout << "Mul" << endl;
	mul.print();
	Matrix sub{};
	sub = matrixA.sub(matrixB);
	cout << "Sub" << endl;
	sub.print();
	Matrix trans{};
	trans = matrixA.transpose();
	cout << "Transpose A" << endl;
	trans.print();
	cout << "\n";

	Matrix matrixC{matrixA};
	cout << "Mutating matrixC content.\n";
	matrixC.getContent()[0][0] = 222;
	matrixA.printSize();
	cout << "\n";
	matrixA.print();
	cout << "\n";
	matrixC.printSize();
	cout << "\n";
	matrixC.print();
	cout << "\n";
}

void runCase(Matrix (*fptr)(Matrix const&, Matrix const&), Matrix matrixA, Matrix matrixB)
{
	bool done = false;
	try
	{
		if (done == true) return;
		Matrix result{fptr(matrixA, matrixB)};
		result.print();
		cout << "###########################\n";
		done = true;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	try
	{
		if (done == true) return;
		cout << "Trying transpose A...\n";
		Matrix T_matrixA{matrixA.transpose()};
		Matrix result{fptr(T_matrixA, matrixB)};
		result.print();
		cout << "###########################\n";
		done = true;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Failed...\n";
	}
	try
	{
		if (done == true) return;
		cout << "Trying transpose B...\n";
		Matrix T_matrixB{matrixB.transpose()};
		Matrix result{fptr(matrixA, T_matrixB)};
		result.print();
		cout << "###########################\n";
		done = true;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Failed...\n";
	}
	if (done == true) return;
	cout << "matrixA:\n";
	matrixA.print();
	cout << "\n";
	cout << "matrixB:\n";
	matrixB.print();
	cout << "\n";
	cout << "###########################\n";
}

int main()
{
	matrixSize dimA = getDimFromUserInput();
	Matrix matrixA = getMatrixFromUserInput(dimA);


	matrixSize dimB = getDimFromUserInput();
	Matrix matrixB = getMatrixFromUserInput(dimB);

	cout << "Mul: " << endl;
	runCase(&Matrix::mul, matrixA, matrixB);
	cout << "Add: " << endl;
	runCase(&Matrix::add, matrixA, matrixB);
	cout << "Sub: " << endl;
	runCase(&Matrix::sub, matrixA, matrixB);
	//test();
	return 0;
}


tuple<int, int> getDimFromUserInput(void)
{
	cout << "Please input matrix dim. EX: AxB" << endl;
	string input = getUserInput<string>();
	istringstream iss{input};
	string token{};
	const int dim{2};
	int xy[dim]{};
	for (int j = 0; j < dim; ++j)
	{
		getline(iss, token, 'x');
		if (iss.fail())
		{
			cout << "Wrong format" << input << endl;
			cout << "Ex:2x2" << endl;
			return getDimFromUserInput();
		}
		xy[j] = stoi(token);
	}
	return make_tuple(xy[0], xy[1]);
}


void freeMatrix(int** m, int rows)
{
	for (int i = 0; i < rows; ++i)
	{
		delete[] m[i];
	}
	delete[] m;
}


Matrix getMatrixFromUserInput(matrixSize ms)
{
	int rows = get<0>(ms);
	int cols = get<1>(ms);
	cout << "Please input " << rows << "x" << cols << " matrix content. Values seperated by comma." << '\n';
	Matrix outMatrix{rows, cols};
	for (int r = 0; r < rows; ++r)
	{
		string input = getUserInput<string>();
		istringstream iss{input};
		string token{};
		for (int c = 0; c < cols; ++c)
		{
			getline(iss, token, ',');
			if (iss.fail())
			{
				cout << "Input size does not match." << endl;
				cout << "Clean matrix..." << endl;
				outMatrix.free();
				return getMatrixFromUserInput(ms);
			}
			outMatrix.getContent()[r][c] = stoi(token);
		}
		iss.ignore(32767, '\n');
	}
	return outMatrix;
}

template <typename T>
T getUserInput(void)
{
	T input{};
	std::cin >> input;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "Oops, that input is invalid.  Please try again.\n";
		return getUserInput<T>();
	}
	else
	{
		return input;
	}
}
