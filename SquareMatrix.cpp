/*
 * SquareMatrix.cpp
 *
 *  Created on: January 2015
 *      Author: Student number : 15102411
 */

#include "SquareMatrix.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

//==================================================================================================
//Default constructors
//==================================================================================================

SquareMatrix::SquareMatrix(const Matrix& input) : Matrix(input) {
	//Uses defualt constructor
	// cout << "Copy constructor " <<endl; // DEBUG
	Matrix tmp = input;
	
	if (tmp.GetNoOfRows() != tmp.GetNoOfColumns() ) {
		// Check if Square, otherwise return 0
		cout << " ERROR: copied matrix is not square, returning 0 " << endl;
		// exit(1);
		SquareMatrix tmp(1);
		this->noOfRows = 1;
		this->noOfColumns = 1;
		this->data[0] = 0;
	} 

}

SquareMatrix::SquareMatrix (const int noOfRowsCols) : Matrix(noOfRowsCols,noOfRowsCols) {
	// Uses default Matrix constuctor
}


//==================================================================================================
// Default Destructors
//==================================================================================================

SquareMatrix::~SquareMatrix () {
	//cout << " SquareMatrix::~SquareMatrix() : Calling Default Destructor " << endl;

}

//==================================================================================================
// Static Member functions
//==================================================================================================

SquareMatrix SquareMatrix::Zeros( const int dim) {
	// Square Matrix Zeros
	SquareMatrix tmp(dim);								// Use default constructor
	return tmp;
}


SquareMatrix SquareMatrix::Ones (const int dim) {
	// Square Matrix Ones
	SquareMatrix tmp = Matrix::Ones(dim,dim);			// Use Matrix static function
	return tmp;
}


SquareMatrix SquareMatrix::Eye (const int dim){
	// Square Matrix Eye
	SquareMatrix tmp(dim);								// Zeros matrix
	for (int i = 0; i < dim ;i++) {
		tmp.data[i*dim +i] = 1;							// Assign Diagonals to 1
	}
	return tmp;
}

SquareMatrix SquareMatrix::Toeplitz (const double *vec, const int dim) {
	// Toeplitz vec
	SquareMatrix tmp = Matrix::Toeplitz(vec,dim,vec,dim);
	return tmp;
}

SquareMatrix SquareMatrix::Toeplitz (const double *vec1,const double *vec2, const int dim) {
	// Toeplitz vec
	SquareMatrix tmp = Matrix::Toeplitz(vec1,dim,vec2,dim);
	return tmp;
}


SquareMatrix SquareMatrix::Transpose (const Matrix& mat) {
	SquareMatrix out(mat);
	SquareMatrix tmp = SquareMatrix::Transpose(out);
	return tmp;
}

SquareMatrix SquareMatrix::Transpose (const SquareMatrix& mat) {
	// New Transpose
	SquareMatrix output = Matrix::Transpose(mat);
	return output; 

}


SquareMatrix SquareMatrix::Triu ( const SquareMatrix& mat) {
	// TriU function wants to return the upper part of the matrix
	int dim = mat.noOfRows;							// Dimension for-loop limit
	SquareMatrix tmp = mat;
//	cout << tmp << endl; // DEBUG
	
	// Decide if the element is below the diagonal and set to 0
	for (int i = 0; i < dim ; i++) {
		for (int j = 0; j < dim ; j++) {
			// conditional to decide if below
			if ( (i-j) > 0) {
				// Sets lower half to 0
				int Index = tmp.GetIndex(i,j);
				tmp.data[ Index ] = 0;			
			}
		}
	}
	
	return tmp;
}

SquareMatrix SquareMatrix::Tril ( const SquareMatrix& mat) {
	// TruL funciton wants to return the lower part of the matrix
	// Just uses the previous defined function for simplicity
	SquareMatrix tmp = SquareMatrix::Transpose(mat);
	tmp = SquareMatrix::Triu(tmp);
	tmp = SquareMatrix::Transpose(tmp);
	return tmp;
}


void SquareMatrix::LU( const SquareMatrix& mat, SquareMatrix& L, SquareMatrix& U) {
	// Does the LU decomposition for the matrix, plus three return matrices which are modified directly

	// First modify the input matrices as they may be different sizes
	int dim = mat.noOfRows; 						// get dimensions
	L = SquareMatrix::Eye(dim);						// initialise with identity
	U = SquareMatrix::SquareMatrix(mat);			// initalise with input matrix
	
	
	// Testing incase of 0 errors
	
	int test = 1;									// Pass or fail test
	for (int t = 0; t < dim ; t++) {				// loop over diagonals
		
		if (U.data[U.GetIndex(t,t)]==0) {			// if diagonal element is 0
			test = 0;								// if above then failed test
		}
	}
	
	
	// Algorithm
	
	if (test == 1){									// Do algorithm if test passed
		// Algorithm 1								
		for (int k = 0; k < (dim-1) ; k++ ) {			// Loop over indices
			for (int j = (k+1) ; j < dim ; j++ ) {		// loop from the index to the end of the row
				
				// Divide 
				L.data[L.GetIndex(j,k)] = U.data[U.GetIndex(j,k)] / U.data[U.GetIndex(k,k)];

			
				for (int i = k; i< dim;i++) {	// loop for operation for the rest of the row
					
					U.data[U.GetIndex(j,i)] = U.data[U.GetIndex(j,i)] - (L.data[L.GetIndex(j,k)]) * (U.data		[U.GetIndex(k,i)]) ;
					

				}
			}
		}
		
		L = SquareMatrix::Tril(L);								// To get rid of round off errors
		U = SquareMatrix::Triu(U); 								// Get rid of round off errors
	} else {
		// For 0 errors
		cout << endl;
		cout << "ERROR : Pivot = 0 " << endl;					// Send ERROR to screen/ divide by 0
			cout << endl << " Cannot LU compute as pivots are 0 " << endl;
		cout << " Matrices have not been altered " << endl;
	}
}

void SquareMatrix::LU( const SquareMatrix& mat, SquareMatrix& L, SquareMatrix& U, SquareMatrix& P) {
	// Does the LU decomposition for the matrix, plus three return matrices which are modified directly
	// First modify the input matrices as they may be different sizes
	int dim = mat.noOfRows; 									// get dimensions
	L = SquareMatrix::Eye(dim);									// Initalise with identity
	U = SquareMatrix::SquareMatrix(mat);						// set U to the input matrix
	P = SquareMatrix::Eye(dim);									// Initialise the P Matrix identity
	
	int test = 1;												// Test flag
	// Algorithm 2
	
	for (int k = 0; k < (dim-1) ; k++ ) {
	
		// Select i >= k to maximuse Uik
		int ind = 0;
		double tmp = 0;
		
		// Finding the highest value
		for (int ia = k ; ia < dim ; ia++) {
			int tmId = U.GetIndex(ia,k);
			double ab = abs( U.data[tmId] );

			 if (ab > tmp) {									// is the next value bigger than first
			 	tmp = U.data[tmId];								// if true then set the tmp to the bigger
			 	ind = ia;										// set index to the index of the biggest 
			 } 
		}

		// Permutations of the matrices
		// Interchange Uk,km UiKm
		U.ExchangeRows(k,ind,k,dim);							// Echange row for U
				
		// Interchange Lk, 1:k-1 and Li, 1:k-1
		L.ExchangeRows(k,ind,0, (k-1) );						// Echange row for L
		
		// Interchange Pk and Pi		
		P.ExchangeRows(k,ind);									// Echange row for P
			

		for (int j = (k+1) ; j < dim ; j++ )
		{
			// Test to check if the algorithm is correct
			int tmID2 = U.GetIndex(k,k);
			if (U.data[tmID2] == 0) {
				test = 0;
				U.data[tmID2] = 1; // Just so division doesnt break
			}
			
			// Back to algorithm
			L.data[L.GetIndex(j,k)] = U.data[U.GetIndex(j,k)] / U.data[U.GetIndex(k,k)];
			for (int i = k; i< dim;i++) {
				U.data[U.GetIndex(j,i)] = U.data[U.GetIndex(j,i)] - (L.data[L.GetIndex(j,k)]) * (U.data[U.GetIndex(k,i)]) ;
			}
		}
	}
	
	// Testing
	if (test == 1) {											// If test has passed
		L = SquareMatrix::Tril(L);								// TRIu and TriL for roundoff errors
		U = SquareMatrix::Triu(U); 
	} else {													// If test failed
		cout << endl << " ERROR : Singular Matrix " << endl;	// Output error to screen
		cout << " Zero Error : Origional Matrices have been returned " << endl;
		L = SquareMatrix::Eye(dim);								// reset the input matrices
		U = SquareMatrix::SquareMatrix(mat);					// to return the output
		P = SquareMatrix::Eye(dim);
				
	}
		
}




//==================================================================================================
// nonstatic Member functions
//==================================================================================================
SquareMatrix& SquareMatrix::Transpose () {
	*this = Matrix::Transpose(*this); // Uses Previous Transpose Function
	return *this;
}


SquareMatrix& SquareMatrix::Zeros() {
	// Using previous functions 
	SquareMatrix tmp = SquareMatrix::Zeros(noOfRows);
	*this = tmp;
	return *this;
}

SquareMatrix& SquareMatrix::Ones() {
	// Using ones function
	SquareMatrix tmp = SquareMatrix::Ones(noOfRows);
	*this = tmp;
	return *this;
}

SquareMatrix& SquareMatrix::Eye() {
	// Using ones function
	SquareMatrix tmp = SquareMatrix::Eye(noOfRows);
	*this = tmp;
	return *this;
}

//==================================================================================================
// nonstatic Member functions - Special
//==================================================================================================

Matrix SquareMatrix::ForwardSub (const Matrix& b, const SquareMatrix& L) {
	// Forward Substituion
	// b needs to be pB
	// Solves Ly = Pb

	// get dimension
	int m = L.noOfRows;
	
	// define output matrix, whcih will have same dimensions as b
	Matrix y(b);																					
	
	// set all initial values to 0
	y.Zeros();
	
	// set first index
	int Index1 = L.GetIndex(0,0);
	
	double tmp =  b.GetEntry(0,0) / L.data[Index1];
	y.SetEntry(0,0,tmp) ;
	tmp = 0;

	// For loop for other elements
	for (int k = 1 ; k < m ; k++) {
		//cout << "This is K" << k << endl;
		tmp = 0;
		// Calculate Numerator
		for (int i = 0 ; i < (k) ; i++) {
			//cout << " this is i" <<  i << endl;
			tmp = tmp + ( L.GetEntry(k,i) ) * (y.GetEntry(i,0)) ;					
		}
		
		double div = (b.GetEntry(k,0)-tmp )/ ( L.data[L.GetIndex(k,k)] ) ;

		y.SetEntry(k,0,div);
		
	}
	return y;

}


Matrix SquareMatrix::BackwardSub(const Matrix& b, const SquareMatrix& U) {
	// Initialise output matrix
	Matrix x(b);														// Make Identical sized matrix
	x.Matrix::Zeros();													// Set output matrix to 0's
	
	int m = (U.noOfRows - 1 );											// Iteration limit
	
	// Set last element of out put matrix
	double bl = b.GetEntry(m,0) / U.GetEntry(m,m);						// Set last element in the output
	x.SetEntry(m,0,bl);

	for (int k = (m-1 ); k >= 0 ; k--) {								// loop backwards from last element
//		cout << k << endl; // DEBUG Line
		double tmp = 0;													// Temporary variables
		double total = 0;
		
		// Sum the bits	
		for (int j = (k+1) ; j <= m ; j++) {							// Sum of the rest of the row
			total = total + U.GetEntry(k,j) * x.GetEntry(j,0) ;
		}
		
		double total2 = b.GetEntry(k,0) - total;
		
		// Divide
		tmp = total2 / U.GetEntry(k,k);									// for element in output matrix
		x.SetEntry(k,0,tmp);											// set entry to the temporary variable
	}

	return x;
}



Matrix SquareMatrix::LinSolve(const SquareMatrix& A, const Matrix& B) {

	// Initialise output
	Matrix X(B);
	X.Matrix::Zeros();
	
	// Do LU decomp
	SquareMatrix L(1);
	SquareMatrix U(1);
	SquareMatrix P(1);
	SquareMatrix::LU(A,L,U,P);
	
	// Define PB
	Matrix PB = P * B ;
	
	// Forward Substitution
	Matrix Y = SquareMatrix::ForwardSub(PB,L); // Solves Ly = Pb
	
	// Backward Substitution
	X = SquareMatrix::BackwardSub(Y,U); // Solves Ux = y
	
	return X;
}

	
	
