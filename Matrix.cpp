/*
 * Matrix.cpp
 *
 *  Created on: January 2015
 *      Author: Student number : 15102411
 */

#include "Matrix.h"
#include "SquareMatrix.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
// Public Function
int Matrix::GetIndex (const int rowIdx, const int columnIdx) const {
	// Returns the index in the vector data relating to the row index and Column index
	
	// Initalise
	int output;
	
	// Find index and assign to output
	output = (rowIdx + columnIdx*noOfRows); 	// column by column
	//output = (rowIdx*noOfColumns + columnIdx); 	//  row by row
	
	// Return Output
	return output;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * DEFAULT CONSTRUCTORS  * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Matrix::Matrix () {
	// cout << "Matrix::Matrix default constructor" << endl; //DEBUG 
	Matrix tmp(1,1);
	*this = tmp;
}



Matrix::Matrix (const int Rows, const int Cols) {
	// cout << "Matrix::Matrix default constructor" << endl; //DEBUG 
	
	// Initalise
	this->noOfRows = Rows; 
	this->noOfColumns = Cols; // Renaming variables (for my sake)
	int index = Rows*Cols;
	data = new double[index]; // Dynamic memory
	
	// Loop over matrix and assign elements to 0
	for (int i =0; i < Rows; i++ ) {
		for (int j = 0; j < Cols ; j++) {
			// Get index
			int Index = GetIndex(i,j);			
			data[Index] = 0 ;
		}
	}
}


Matrix::Matrix (const Matrix& input) {
	// Copy Constructor
	
	// Gets the number of rows and columns
	this->noOfColumns = input.noOfColumns;
	this->noOfRows = input.noOfRows;

	// Initalise index
	int index = noOfRows*noOfColumns;
	
	// New dynamic memory
	data = new double[index];
	
	// Copy elements
	for (int i = 0; i < index; i++) {
			data[i] = input.data[i];
	}
} 

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * DEFAULT DESTRUCTOR  * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


// Default Destructor
Matrix::~Matrix () {
	// Delete Dynamic array
	//cout << "Matrix::~Matrix Default Destructor" << endl; // DEBUG
	if (data != NULL) {
		delete [] data;
		data = NULL;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * OPERATORS * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Matrix& Matrix::operator= (const Matrix& rhs) {
	// Assignment operator // could use copy constructor
	//cout << " Assignment operator"<< endl;
	// Gets the number of rows and columns
	this->noOfColumns = rhs.noOfColumns;
	this->noOfRows = rhs.noOfRows;

	//	
	int index = noOfRows*noOfColumns;
	
	// Delete old data
	if (data != NULL) {
		delete [] data;
		data = NULL;
	}
	
	// New dynamic memory
	data = new double[index];
	
	// Copy data
	for (int i = 0; i < index; i++) {
			data[i] = rhs.data[i];
	}
	
	return *this;
}


Matrix operator* (const Matrix& lhs, const Matrix& rhs){
	// Multiplication Operator
	//cout << " Multiplier operator " << endl;	// DEBUG
	
	// Set Rows and Columns
	int Rows = lhs.noOfRows;
	int Cols = rhs.noOfColumns;
	int inside = lhs.noOfColumns;
	
	// Initialise output matrix
	Matrix output(Rows,Cols) ;

	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Cols; j++) {
			//temporary variable for summing
			double tmp = 0;
				for (int k = 0; k < inside; k++) {
					//cout << " R:" << rhs.data[k*Rows+j] << endl; // DEBUG
					//cout << " L:" << lhs.data[i*inside+k] << endl;  //DEBUG
					
					// Get Index
					int Index1 = rhs.GetIndex(k,j);
					int Index2 = lhs.GetIndex(i,k);
					
					tmp = tmp + ((rhs.data[Index1]) * (lhs.data[Index2])) ;  				

				}
			
	
			//cout << "index = " << rhs.GetIndex(i,j) << endl; //DEBUG
			//output.data[output.GetIndex(i,j)] =  tmp;		//DEBUG
			
			// assign sum to output element
			int IndexOut = output.GetIndex(i,j);
			output.data[IndexOut] =  tmp;
		}
	}
	
	// Return 
	return output;
}


Matrix& Matrix::operator*= (const Matrix& rhs) {
	Matrix tmp = (*this)*rhs; // Use predefined operator* from before
	*this = tmp;
	return *this;
}

// For using Cout
ostream& operator<< (ostream& out, const Matrix& rhs) {
	// Write Variables
	int R = rhs.noOfRows; int C = rhs.noOfColumns;
	int index = R * C;
	//out << " Number of Rows = " << R << endl; 			// DEBUG
	//out << " Number of Columns = " << C << endl; 			// DEBUG
	
	out << endl;											// Space
	
	double tmp = 0;											// Dummy Variable
	
	// Loop printing with if statements for asthetic purposes (2 digit number in line)
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			out.precision(4);
			int Index = rhs.GetIndex(i,j);
			//tmp = rhs.data[ (i*C) + j];
			tmp = rhs.data[Index];	
			
			// Incase of truncation errors
			double abb = abs(tmp);
			if (abb < (1e-14) ) {
				tmp = 0;
			}
			out << tmp << "\t";
		}
		out << endl;					// Space
	}
	return out;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * STATIC FUNCTIONS  * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	
// static functions
Matrix Matrix::Zeros (const int Rows,const int Cols) {
	//Matrix output(Rows,Cols);	// new variable outptu class
	// cout << " Matrix::Zeros constructor " << endl; DEBUG
	
	// initialise - default constructor is 0's
	Matrix output(Rows,Cols);
	return output;
}

Matrix Matrix::Ones (const int Rows,const int Cols) {
	//Matrix output(Rows,Cols);	// new variable outptu class
	//cout << " Matrix::Ones constructor " << endl; // DEBUG

	// initialise
	Matrix output(Rows,Cols);
	
	// Index amount
	int index = Rows*Cols;

	// Set all values to 0
	for (int ind = 0; ind < index; ind++) {
		output.data[ind] = +1;
	}
	
	// Return output
	return output;
}

Matrix Matrix::Toeplitz(const double *column, const int Rows,const double *row, const int Columns)  {
	// Toeplitz
	//cout << " In toeplitz Function " << endl; // For Debugging
	
	// Initalise Matrix for dynamic memoory allocation
	Matrix output(Rows,Columns);
	
	// Reassign components of the matrix
	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Columns; j++) {
			int Index = output.GetIndex(i,j);
			if ( (i-j) >= 0) {
				output.data[ Index] = column[i-j];				
			} else {
				output.data[ Index ] = row[j-i];
			}
		}
	}
	return output;
}
	
void Matrix::Print(const double *vec,const int noOfRows,const int noOfColumns) {
	// Print Function for a toeplitz vector
	//cout << " In Printing Function " << endl; 	// For Debugging
	
	// Reassigns the vector to a temporary matrix for nice printing ( Asthetics ) 
	Matrix tmp(noOfRows,noOfColumns);
	
	for (int i = 0; i < noOfRows; i++) {
		for (int j = 0; j < noOfColumns; j++) {
		
				int index = tmp.GetIndex(i,j);  
				tmp.data[index] = ( vec[i+j*noOfRows] ) ;
		}
	}

	// Using defined printing function for asthetics
	cout << tmp << endl;
}  

Matrix Matrix::Transpose(const Matrix& rhs) {
	// Transpose Function
	int Rows = rhs.noOfColumns;					// New Rows is the number of columns
	int Columns = rhs.noOfRows;					// New columns is the number of rows
	Matrix output(Rows,Columns);				// Initalise new matrix of the right dimensions
	
	// Loop over rows and columns
	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Columns; j++) {
				
				// Get Indexs
				int Indexout = output.GetIndex(i,j);
				int Indexrhs = rhs.GetIndex(j,i);
				output.data[Indexout] = rhs.data[Indexrhs];	
				
		}
	}
	return output; 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * NON STATIC FUNCTIONS * * * * * * * * * * *  * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



Matrix& Matrix::ExchangeRows(const int row1,const int row2,const int col1,const int col2) {
	// Exhange row1 for row2
	Matrix tmp = *this;							// Dummy Variable
	
	// Loop over Dimensions of Columns for exchanging rows
		for (int j = 0; j < noOfColumns; j++) {
			
			// Exchange *this with the temporary other row	
			// If statement for between i and j columns. Set to (0, end) if all the row
			
			if ( (j >= col1) && (j <= col2) ) {
			
				int Index1 = tmp.GetIndex(row1,j);
				int Index2 = tmp.GetIndex(row2,j);
				this->data[Index2] =  tmp.data[Index1];
				this->data[Index1] =  tmp.data[Index2];	

			}
		}
	return *this;
}


Matrix& Matrix::ExchangeRows(const int row1, const int row2) {
	// Exhange row1 for row2
	Matrix tmp = *this;							// Dummy Variable
	tmp.ExchangeRows(row1,row2,0,noOfColumns);	// Exchange Rows more complete function
	*this = tmp;								// Reassign this
	return *this;
}

Matrix& Matrix::ExchangeColumns(const int col1, const int col2) {
	// Exchange columns, using Exchange Row functions, reusing code
	Matrix tmp = *this;							// Initalise dummy variable
	tmp.Transpose();							// Transpose to use row exchange function
	tmp.ExchangeRows(col1,col2,0,noOfRows);		// Row exchange
	tmp.Transpose();							// Transpose back
	*this = tmp;								// reassign this
	return *this;
}

Matrix& Matrix::ExchangeColumns(const int col1,const int col2,const int row1,const int row2) {
	// Exchange Columns using Exchange Row functions between certain limits, reusing code
	Matrix tmp = *this;							// Initalise dummy variable
	tmp.Transpose();							// Transpose to use row exchange
	tmp.ExchangeRows(col1,col2,row1,row2);		// Row Exchange
	tmp.Transpose();							// Transpose back
	*this = tmp;								// Reassign this
	return *this;
}

Matrix& Matrix::Transpose () {
	// Uses Previous Transpose Function
	*this = Matrix::Transpose(*this); 
	return *this;
}

Matrix& Matrix::Zeros() {
	// Using previous functions
	*this = Matrix::Zeros(noOfRows,noOfColumns);
	return *this;
}

Matrix& Matrix::Ones() {
	// Using ones function
	*this = Matrix::Ones(noOfRows,noOfColumns);
	return *this;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * ACCESSORS * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int Matrix::GetNoOfRows() const {
	// Return an int for the number of rows
	return noOfRows;
}

int Matrix::GetNoOfColumns() const {
	// Return an int for the number of columns
	return noOfColumns;
}

double Matrix::GetEntry (const int i, const int j) const {
	// Gets the entry at index i, j ( remembering c++ first index = 0
	return data[GetIndex(i,j)];
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * MODIFIERS * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


// modifiers // Though not needed
void Matrix::SetEntry (const int i, const int j, const double value) const {
	// Set Entry at index i, j (remembering c++ first index is 0)
	this->data[GetIndex(i,j)] = value; 
}

//==========================================================================================
// Sepcial Functions
// =========================================================================================
// linsolve


 Matrix Matrix::LeastSquares(const Matrix& A, const Matrix& B) {
 	// Solving A'A X = A'B
 	
 	// Declare Output
 	Matrix output = Matrix::Zeros(1,1);
 	
// 	cout << "noOfROws"<< A.noOfRows << endl;				// DEBUG
// 	cout << "noOfROws"<< B.noOfRows << endl;				// DEBUG
 	 	
 	if (A.noOfRows == B.noOfRows) {
 	// Create a transpose of Matrix A
 	Matrix trA = A;					
 	trA.Transpose();
 	
 	// New LHS and RHS 
 	SquareMatrix LHS = trA * A;						// A'A
 	//cout << " THIS IS THE A'A " << LHS << endl;
 	
 	Matrix RHS = trA * B;							// A'B
 	//cout << " THis IS THE A'B " <<  RHS << endl;
 	
 	// Use function from before
 	output = SquareMatrix::LinSolve(LHS,RHS);
 	} else {
 	// Error Message if wrong
 	cout << " ERROR: Dimensions do not match" << endl;
 	}
 	return output;
 }

