#pragma once
#include <tuple>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

typedef tuple<int, int> matrixSize;

class Matrix
{
	int rows = 0;
	int cols = 0;
	int** m = nullptr;
public:
	Matrix();
	Matrix(Matrix const&);
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, int**);

	matrixSize size() const;

	void printSize() const;
	void copyContent(Matrix const&);
	void print() const;
	void free();

	//Matrix& operator*(Matrix&);
	//Matrix& operator=(Matrix&);

	Matrix mul(Matrix const&);
	Matrix add(Matrix const&);
	Matrix sub(Matrix const&);
	static Matrix mul(Matrix const&, Matrix const&);
	static Matrix add(Matrix const&, Matrix const&);
	static Matrix sub(Matrix const&, Matrix const&);
	Matrix transpose();

	int** getContent() const;
	int getRow() const;
	int getCol() const;
private:
	void alloc();
	void setRow(int);
	void setCol(int);
	bool isSizeMatch(Matrix const&) const;
	static bool isSizeMatch(Matrix const&, Matrix const&);
	bool isShapeMatch(Matrix const&) const;
	static bool isShapeMatch(Matrix const&, Matrix const&);
};
