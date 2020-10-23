/*
 * SquareMatrix.h
 *
 *  Created on: January 2015
 *      Author: Student number : 15102411
 */


#ifndef _SquareMatrix_H
#define _SquareMatrix_H

#include "Matrix.h"

class SquareMatrix : public Matrix {
	private: 
		// No new member variables
		// data from before
		// noOfColumns
		// noOfRows

	public:
	
	// Default Constructors and desturctors
	SquareMatrix (const Matrix& mat);
	SquareMatrix (const int noOfRowsCols );
	~SquareMatrix (); 
	

	// Static Member functions
	
	static SquareMatrix Zeros (const int dim);
	static SquareMatrix Ones (const int dim);
	static SquareMatrix Eye (const int dim);

	static SquareMatrix Toeplitz(const double *vec, const int dim);
	static SquareMatrix Toeplitz(const double *vec1, const double *vec2, const int dim);

	// Two types of transpose for a normal matrix input returning a Square or Square Matrix
	static SquareMatrix Transpose(const SquareMatrix& mat);
	static SquareMatrix Transpose(const Matrix& mat);
	
	// More Interesting Functions
	static SquareMatrix Triu(const SquareMatrix& mat);
	static SquareMatrix Tril(const SquareMatrix& mat);

	
	static void LU( const SquareMatrix& mat, SquareMatrix& L, SquareMatrix& U); 
	static void LU( const SquareMatrix& mat, SquareMatrix& L, SquareMatrix& U, SquareMatrix& P); 
	
	// The other special functions
	static Matrix ForwardSub (const Matrix& b, const SquareMatrix& L) ;
	static Matrix BackwardSub(const Matrix& b, const SquareMatrix& U) ;
	
	// combined solver
	static Matrix LinSolve(const SquareMatrix& A, const Matrix& B);
	
	// Nonstatic member functions

	virtual SquareMatrix& Transpose ();	
	virtual SquareMatrix& Zeros ();
	virtual SquareMatrix& Ones ();
	virtual SquareMatrix& Eye ();
	
//	SquareMatrix& operator= (const Matrix& rhs);
}; 



#endif


