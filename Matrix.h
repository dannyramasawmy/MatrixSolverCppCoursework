/*
 * Matrix.h
 *
 *  Created on: Januray 2015
 *      Author: Student number : 15102411
 */

#ifndef MATRIX_H_
#define MATRIX_H_


#include <iostream>

using namespace std;

class Matrix {
protected:
	// These are the only member variables allowed!
	int noOfRows;
	int noOfColumns;
	double *data;

	int GetIndex (const int rowIdx, const int columnIdx) const;

public:
	// Defualt Constructors
	Matrix ();
	Matrix (const int noOfRows, const int noOfCols);
	Matrix (const Matrix& input);
	
	// Default Destructor
	virtual ~Matrix ();
	
	// Operators
	Matrix& operator= (const Matrix& rhs);
	friend Matrix operator* (const Matrix& lhs, const Matrix& rhs);
	Matrix& operator*= (const Matrix& rhs);
	friend ostream& operator<< (ostream& out, const Matrix& rhs);	
	
	// static functions
	static Matrix Zeros (const int a, const int b);
	static Matrix Ones (const int a, const int b);
	static Matrix Toeplitz(const double *column, const int Rows,const double *row, const int Columns);	
	static void Print(const double *vec,const int noOfRows,const int noOfColumns);
	static Matrix Transpose(const Matrix& rhs);

	// non-static Functions
	virtual Matrix& ExchangeRows(const int row1,const int row2, const int col1, const int col2);
	virtual Matrix& ExchangeRows(const int row1,const int row2);
	virtual Matrix& ExchangeColumns(const int col1, const int col2);
	virtual Matrix& ExchangeColumns(const int col1, const int col2, const int row1, const int row2);
	
	virtual Matrix& Transpose ();
	virtual Matrix& Zeros();
	virtual Matrix& Ones();
	
	// accessors
	int GetNoOfRows() const;
	int GetNoOfColumns() const ;
	double GetEntry (const int i, const int j) const;

	// modifiers
	void SetEntry (const int i, const int j, const double value) const;
	
	static Matrix LeastSquares(const Matrix& A, const Matrix& B);

};

#endif  /*MATRIX_H_*/


