#include "stdafx.h"
#include "matrix.h"

Matrix::Matrix(): rows(0), cols(0), m(nullptr)
{
}

Matrix::Matrix(Matrix const& m): Matrix(m.rows, m.cols)
{
	this->copyContent(m);
}

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols)
{
	this->alloc();
}

Matrix::Matrix(int rows, int cols, int** m): rows(rows), cols(cols), m(m)
{
}


int** Matrix::getContent() const
{
	return this->m;
}

void Matrix::setRow(int r)
{
	this->rows = r;
}

int Matrix::getRow() const
{
	return this->rows;
}

void Matrix::setCol(int l)
{
	this->cols = l;
}

int Matrix::getCol() const
{
	return this->cols;
}

void Matrix::copyContent(Matrix const& m)
{
	if (this->getContent() == nullptr)
		this->alloc();
	if (!isSizeMatch(m))
		throw exception("Cann't copy matrix from different shape.");

	for (int r = 0; r < this->getRow(); ++r)
	{
		for (int l = 0; l < this->getCol(); ++l)
		{
			this->getContent()[r][l] = m.getContent()[r][l];
		}
	}
}

void Matrix::free()
{
	if (this->getContent() == nullptr)
		return;

	int** matrix = this->getContent();
	for (int r = 0; r < this->getRow(); ++r)
	{
		if (matrix[r] != nullptr)
			delete[] matrix[r];
	}
	delete[] matrix;
}

void Matrix::alloc()
{
	if (this->getContent() != nullptr)
	{
		throw exception("Matrix had been allocated.");
		return;
	}


	this->m = new int*[this->getRow()];
	for (int i = 0; i < this->getRow(); ++i)
	{
		this->m[i] = new int[this->getCol()]{0};
	}
}

matrixSize Matrix::size() const
{
	return make_tuple(this->getRow(), this->getCol());
}

void Matrix::printSize() const
{
	cout << this->getRow() << "x" << this->getCol();
}

bool Matrix::isSizeMatch(Matrix const& m) const
{
	matrixSize inputSize{m.size()};
	matrixSize selfSize{this->size()};
	if (inputSize != selfSize)
	{
		cout << "Operation needs input be the same size." << endl;
		this->printSize();
		cout << " != ";
		m.printSize();
		cout << "\n";
		return false;
	}
	else
	{
		return true;
	}
}

bool Matrix::isSizeMatch(Matrix const& leftMatrix, Matrix const& rightMatrix)
{
	if (leftMatrix.size() != rightMatrix.size())
	{
		cout << "Operation needs input be the same size." << endl;
		leftMatrix.printSize();
		cout << " != ";
		rightMatrix.printSize();
		cout << "\n";
		return false;
	}
	else
	{
		return true;
	}
}

bool Matrix::isShapeMatch(Matrix const& m) const
{
	int selfCols = this->getCol();
	int inputRows = m.getRow();
	if (selfCols != inputRows)
	{
		cout << "mul operation shape doesn't match." << endl;
		this->printSize();
		cout << " X ";
		m.printSize();
		cout << "\n";
		return false;
	}
	else
		return true;
}

bool Matrix::isShapeMatch(Matrix const& leftMatrix, Matrix const& rightMatrix)
{
	int leftNum = leftMatrix.getCol();
	int rightNum = rightMatrix.getRow();
	if (leftNum != rightNum)
	{
		cout << "mul operation shape doesn't match." << endl;
		leftMatrix.printSize();
		cout << " X ";
		rightMatrix.printSize();
		cout << "\n";
		return false;
	}
	else
		return true;
}

Matrix Matrix::mul(Matrix const& m)
{
	if (!isShapeMatch(m))
	{
		throw exception("Shape not match!");
	}
	else
	{
		int outRows = this->getRow();
		int outCols = m.getCol();
		int mulSteps = this->getCol();

		Matrix outMatrix(outRows, outCols);

		for (int r = 0; r < outRows; ++r)
		{
			for (int c = 0; c < outCols; ++c)
			{
				outMatrix.getContent()[r][c] = 0;
				for (int s = 0; s < mulSteps; ++s)
				{
					outMatrix.getContent()[r][c] += this->getContent()[r][s] * m.getContent()[s][c];
				}
			}
		}
		return outMatrix;
	}
}

Matrix Matrix::mul(Matrix const& leftMatrix, Matrix const& rightMatrix)
{
	if (!Matrix::isShapeMatch(leftMatrix, rightMatrix))
	{
		throw exception("Shape not match!");
	}
	else
	{
		int outRows = leftMatrix.getRow();
		int outCols = rightMatrix.getCol();
		int mulSteps = leftMatrix.getCol();

		Matrix outMatrix(outRows, outCols);

		for (int r = 0; r < outRows; ++r)
		{
			for (int c = 0; c < outCols; ++c)
			{
				outMatrix.getContent()[r][c] = 0;
				for (int s = 0; s < mulSteps; ++s)
				{
					outMatrix.getContent()[r][c] += leftMatrix.getContent()[r][s] * rightMatrix.getContent()[s][c];
				}
			}
		}
		return outMatrix;
	}
}

Matrix Matrix::add(Matrix const& m)
{
	int outRows = this->getRow();
	int outCols = this->getCol();
	if (!isSizeMatch(m))
	{
		throw exception("size not match!");
	}
	else
	{
		Matrix outMatrix = Matrix(*this);
		for (int i = 0; i < outRows; ++i)
		{
			for (int j = 0; j < outCols; ++j)
			{
				outMatrix.getContent()[i][j] = m.getContent()[i][j] + this->getContent()[i][j];
			}
		}
		return outMatrix;
	}
}

Matrix Matrix::add(Matrix const& leftMatrix, Matrix const& rightMatrix)
{
	int outRows = leftMatrix.getRow();
	int outCols = leftMatrix.getCol();
	if (!Matrix::isSizeMatch(leftMatrix, rightMatrix))
	{
		throw exception("size not match!");
	}
	else
	{
		Matrix outMatrix = Matrix(leftMatrix);
		for (int i = 0; i < outRows; ++i)
		{
			for (int j = 0; j < outCols; ++j)
			{
				outMatrix.getContent()[i][j] = rightMatrix.getContent()[i][j] + leftMatrix.getContent()[i][j];
			}
		}
		return outMatrix;
	}
}

Matrix Matrix::sub(Matrix const& m)
{
	int outRows = this->getRow();
	int outCols = this->getCol();
	if (!isSizeMatch(m))
	{
		throw exception("size not match!");
	}
	else
	{
		Matrix outMatrix = Matrix(*this);
		for (int r = 0; r < outRows; ++r)
		{
			for (int c = 0; c < outCols; ++c)
			{
				outMatrix.getContent()[r][c] = this->getContent()[r][c] - m.getContent()[r][c];
			}
		}
		return outMatrix;
	}
}

Matrix Matrix::sub(Matrix const& leftMatrix, Matrix const& rightMatrix)
{
	int outRows = leftMatrix.getRow();
	int outCols = leftMatrix.getCol();
	if (!Matrix::isSizeMatch(leftMatrix, rightMatrix))
	{
		throw exception("size not match!");
	}
	else
	{
		Matrix outMatrix = Matrix(leftMatrix);
		for (int r = 0; r < outRows; ++r)
		{
			for (int c = 0; c < outCols; ++c)
			{
				outMatrix.getContent()[r][c] = leftMatrix.getContent()[r][c] - rightMatrix.getContent()[r][c];
			}
		}
		return outMatrix;
	}
}

Matrix Matrix::transpose()
{
	int outRows = this->getRow();
	int outCols = this->getCol();
	Matrix outMatrix = Matrix(outCols, outRows);
	for (int r = 0; r < outRows; r++)
	{
		for (int c = 0; c < outCols; c++)
		{
			outMatrix.getContent()[c][r] = this->getContent()[r][c];
		}
	}
	return outMatrix;
}

void Matrix::print() const
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			cout << setw(6) << this->m[i][j] << "|";
		}
		cout << "\n";
	}
}
