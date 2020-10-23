/*
 * SquareMatrixTest.cpp
 *
 *  Created on: January, 2015
 *		  Edit: Student number : 15102411
 *
 * Using the base test script from Gary Zhang [1]
 * [1] Gary Zhang, Programming Foundations for Medical Image Analysis, MPHYGB24	C/C++ lecture notes, 
 * 2015/2016, University College London.
 */

#include "SquareMatrix.h"
#include <iostream>
#include <cstdlib>
#include <typeinfo>

using namespace std;

// Declare Functions

void wait () ;
void ConstructorsTesting();					// Square Matrix Constructors
void Assignment ();							// Testing Assignment and types
void SpecialConstructors();					// Using Special Constuctors , Ones, Zeros, Eye		
void TransposeTesting();					// Testing Transpose
void NonStaticFuncs () ;					// Testing non-static member functions
void TriuTril () ;							// Testing Triu and tril
void LUnopiv () ;							// testing LU without a pivot
void LUwithpiv () ;							// Testing LU with a pivot
void ForwardBackward () ;					// Testing the forward and backward pass

// ==================================================================================================
// MAIN PROGRAM 
// ==================================================================================================
int main () {

	for (;;) {
		cout << "Choose to test one of the following:" << endl;
		cout << "  Enter \'1\' for the constructors" << endl;
		cout << "  Enter \'2\' for the assignment testing" << endl;
		cout << "  Enter \'3\' for the special constructors" << endl;
		cout << "  Enter \'4\' for the transpose testing" << endl;
		cout << "  Enter \'5\' for the other functions" << endl;
		cout << "  Enter \'6\' for the Triu and Tril functions" << endl;
		cout << "  Enter \'7\' for the LU with no pivot function "<< endl;
		cout << "  Enter \'8\'for the LU with pivoting function " << endl;
		cout << "  Enter \'9\'for Gaussian Elimination and Least Squares" << endl; 
		cout << ">> ";
		char choice;
		cin >> choice;
		switch (choice) {
			case '1':	ConstructorsTesting();
						break;
			case '2':	Assignment ();
						break;
			case '3':	SpecialConstructors();			
						break;			
			case '4':	TransposeTesting();	
						break;				
			case '5':	NonStaticFuncs () ;					
						break;
			case '6':	TriuTril () ;							
						break;
			case '7':	LUnopiv () ;							
						break;
			case '8':	LUwithpiv () ;							
						break;
			case '9':	ForwardBackward () ;			
						break;
		}
		
		cout << "Enter \'0\' to exit or \'1\' to choose another test" << endl;
		cout << ">> ";
		cin >> choice;
		if (choice == '0') {
			return 0;
		}
	}

}

// =====================================================================================================
//	FUNCTION DEFINITIONS
//	====================================================================================================

// wait press any key function
void wait () {
	// waits for a system input to carry on, to prevent huge amount of print to screen
	cout << endl;
	cout << "Press any key to continue ..." << flush;
	system("read");
	cout << endl;
}

// CONSTRUCTORS
void ConstructorsTesting() {

	{
		cout << " Test 1 : Defualt constructor and destructor with one input " << endl;
		cout << " SquareMatrix mat(4); " << endl;
		SquareMatrix mat(4);										// Initialise Squarematrix
		cout << mat << endl;
	}

	wait();
	cout << "=======================================================================" << endl;
	{
		cout << " Test 2 : Default copy constructor" << endl;
		Matrix mat1(5,5);											// New matrix
		cout << " New matrix class : " << mat1 << endl;				// Matrix Class
		cout << " copy constructor: SquareMatrix mat2(mat1); " << endl;	// Copy Constructor
		SquareMatrix mat2(mat1);
		cout << " Square Matrix : mat2 " << endl;
		cout << mat2 << endl;
	}
	
	wait();
	cout << "=======================================================================" << endl;
	{
	cout << " Test 3 : Copy constructor with Rectangular input" << endl;
	cout << " New rectangular matrix " << endl;
	Matrix mat(3,1);
	cout << mat << endl;
	cout << "Attempt at using Copy Constructor : " << endl;
	SquareMatrix mat1(mat); 
	cout << mat1 << endl;
	cout << " It does not allow a rectangular matrix to be copied to a square matrix " << endl;
	}


}

void Assignment () {
	
	{
		cout << " Assigning different Matrices with Matrix and SquareMatrix class " << endl;
		
		cout << " Test 1 : Assign SquareMatrix to Matrix " << endl;
		
		Matrix A(3,3);
		cout << " New Matrix A : " << A << endl;
		cout << " A has Type : " << typeid(A).name() << endl << endl;
		
		SquareMatrix B(4);	
		cout << " New Matrix B : " << B << endl;
		cout << " B has Type :  "<< typeid(B).name() << endl << endl;
	
		wait();
		
		cout << " Assigning A to B : B = A" << endl;
		B = A;
		cout << "Matrix B" << B << endl;
		cout << "B has type : " << typeid(B).name() << endl << endl;
		cout << "Matrix A" << A << endl;
		cout << "A has type : " << typeid(A).name() << endl << endl;
		cout << " A matrix can be assigned to a SquareMatrix Class " << endl;
		wait();
		
		cout << "=======================================================================" << endl;		
		// Test 2
		cout << " Test 2 : Assign SquareMatrix to Matrix " << endl;
		cout << " Matrix A : " << A << endl;
		cout << " A has Type : " << typeid(A).name() << endl << endl;
		
			// New matrix
		SquareMatrix C(4);		
		cout << " New SquareMatrix C : " << C << endl;
		cout << " C has Type : " << typeid(C).name() << endl << endl;
		
		wait();
		cout << " Assigning C to A : A = C " << endl;
		A = C;
		cout << "Matrix C" << C << endl;
		cout << "C has type : " << typeid(C).name() << endl << endl;
		cout << "Matrix A" << A << endl;
		cout << "A has type : " << typeid(A).name() << endl << endl;
		cout << " A SquareMatrix can be assigned to a Matrix Class " << endl;
		wait();		
		
		cout << "=======================================================================" << endl;		
		// Test 3
		cout << "Test 3 : Assigning a SquareMatrix to a SquareMatrix " << endl;		
		cout << " Matrix C and B" << endl;
		cout << "C has Type : " << typeid(C).name() << endl << endl;		
		cout << "B has Type : " << typeid(B).name() << endl << endl;
		wait();
		cout << " Assigning B to C :  C = B " << endl;
		C = B;
		cout << " Matrix C : " << C << endl;		
		cout << "C has Type " << typeid(C).name() << endl << endl;
		cout << " Matrix B : " << B << endl;		
		cout << "B has Type " << typeid(B).name() << endl << endl;

	}
}

// SPECIAL CONSTRUCTORS
void SpecialConstructors() {
	{
	cout << " Test 1 : testing SquareMatrix::Zeros(4) " << endl;
	SquareMatrix mat = SquareMatrix::Zeros(4);
	cout << mat << endl;
	}
	wait();	
	{
	cout << " Test 2 : testing SquareMatrix::Ones(4) " << endl;
	SquareMatrix mat = SquareMatrix::Ones(4);
	cout << mat << endl;
	}
	wait();	
	{
	cout << " Test 3 : testing SquareMatrix::Eye(4) " << endl;
	SquareMatrix mat = SquareMatrix::Eye(4);
	cout << mat << endl;
	}
	wait();	
	{
	cout << " Test 4 : Check SquareMatrix::Toeplitz(vec,dim) " << endl;
	double vec[4] = {0 ,1 ,2 , 3 } ;
	cout << "The vector " << endl;
	Matrix::Print(vec,1,4);
	cout << "SquareMatrix::Toeplitz(vec,4)" << endl;
	SquareMatrix mat = SquareMatrix::Toeplitz(vec,4);
	cout << mat << endl;
	}
	wait();
	{
	cout << " Test 5 : Check SquareMatrix::Toeplitz(vec,vec,dim) " << endl;
	double vec[4] = {0 ,1 ,2 , 3 } ;
	double vec2[4] = {4 ,3 ,2 , 1 } ;
	cout << "The first vector " << endl;
	Matrix::Print(vec,1,4);
	cout << " The second vector " << endl; 
	Matrix::Print(vec2,1,4);
	cout << "SquareMatrix::Toeplitz(vec,vec2,4)" << endl;
	SquareMatrix mat = SquareMatrix::Toeplitz(vec,vec2,4);
	cout << mat << endl;
	}
	
}


// TRANSPOSE TESTING
void TransposeTesting() {
	{
	cout << " Test 1 : Transpose with SquareMAtrix " << endl;
	
	// Vectors
	double vec[4] = {0,1,2,3};
	cout << " Vector 1 :" << endl;
	Matrix::Print(vec,1,4);
	double vec2[4] = {0,3,2,1};
	cout << " Vector 2 :" << endl;
	Matrix::Print(vec2,1,4);
	
	// Toeplitz
	SquareMatrix mat = SquareMatrix::Toeplitz(vec,vec2,4);
	cout << mat <<endl;
	cout << "Toe has Type " << typeid(mat).name() << endl << endl;
	
	// Transpose
	cout << " Transpose function: SquareMatrix::Transpose(mat);  " << endl;
	SquareMatrix mat2 = SquareMatrix::Transpose(mat);
	cout << mat2 << endl;

	}	
	
	wait();	

	cout << "=======================================================================" << endl;	
	{
	cout << " Test 2: Transpose function of a SquareMatrix initialised with the Matrix class" << endl;
	
	// Vectors
	double vec[4] = {0,1,2,3};
	cout << " Vector 1 :" << endl;
	Matrix::Print(vec,1,4);
	double vec2[4] = {0,3,2,1};
	cout << " Vector 2 :" << endl;
	Matrix::Print(vec2,1,4);
	
	// Matrix	
	cout << " Matrix mat = Matrix::Toeplitz(vec,4,vec2,4); " << endl;
	Matrix mat = Matrix::Toeplitz(vec,4,vec2,4);
	cout << " Our Matrix class, square matrix is " << endl;
	cout << mat << endl;
	cout << "Toe has Type " << typeid(mat).name() << endl << endl;
	
	wait();
	
	// Transpose
	cout << "SquareMatrix mat2 = SquareMatrix::Transpose(mat);" << endl;
	SquareMatrix mat2 = SquareMatrix::Transpose(mat);
	cout << " Our Returned SquareMatrix type from the Matrix input is " << endl;
	cout << mat2 << endl;
	cout << " New object has type : " << typeid(mat2).name() << endl << endl;
	
	wait();
	cout << "SquareMatrix::Transpose(mat) can transpose a Matrix type input and return a Squarematrix type " 			<< endl;
	}
}

// Non Static functions
void NonStaticFuncs () {

	{
	cout << " Test 1 : Testing non-static member functions " << endl;
	double vec[4] = {1,2,3,4};
	double vec1[4] = {4,3,2,1};
	SquareMatrix mat1 = SquareMatrix::Toeplitz(vec,vec1,4);
	SquareMatrix mat = mat1;
	
	// Set up Toeplitz
	cout << " This is the SquareMatrix initialised with toeplitz" << endl;
	cout << mat << endl;
	
	wait();
	// Transpose
	cout << " Test transpose : mat.Transpose() " << endl;
	mat.Transpose();
	cout << mat << endl;
	
	wait();
	
	// Zeros
	cout << " Test Zeros : mat.Zeros() " << endl;
	mat.Zeros();
	cout << mat << endl;
	
	wait();
	
	// Identity
	cout << " Test Identity : mat.Eye() " << endl;
	mat.Eye();
	cout << mat << endl;
	
	wait();
	
	// Ones
	
	cout << " Test Ones : mat.Ones() " << endl;
	mat.Ones();
	cout << mat << endl;
	
	wait();
	cout << "=======================================================================" << endl;	
	cout << " Test 2: Exchange Rows and COlumns " << endl;
	// Exchangey Things
	cout << " Before Exchanging " << endl;
	cout << mat1 << endl;

	cout << " Exchchange rows 2 & 4: mat1.ExchangeRows(1,3)" << endl;
	mat1.ExchangeRows(1,3);
	cout<<mat1 << endl;
	
	wait();

	cout << " Exchange Columns 1 & 2 : 	mat1.ExchangeColumns(0,1);" << endl;
	mat1.ExchangeColumns(0,1);
	cout << mat1 << endl;

	wait();
	cout << "=======================================================================" << endl;	
	// Test multiplication
	cout << "Test 3: test multiply " << endl;
	cout << " First Matrix A : " << endl << mat1 << endl;

	cout << " Second Matrix B : " << mat << endl;
	cout << endl << "A * B" << endl;
	
	wait();
	
	SquareMatrix out = mat1*mat; //  multiplication is wrong need to change
	
	cout << out <<endl;
	
	wait();
	
	cout << " Can still use operatons for Matrix class too, ie mat.Matrixx::Ones() "<<endl;
	cout << " would still work " << endl << endl;
	}
	
}


// Testing Triu and Tril
void TriuTril () {
	{
	cout << " Test 1 : Testing the triU matrix function " << endl;
	cout << " Create A Squarematrix with Toeplitz " << endl;
	double vec[4] = {1,2,3,4};
	double vec1[4] = {4,3,2,1};
	SquareMatrix mat = SquareMatrix::Toeplitz(vec,vec1,4);
	cout << mat << endl;

	wait();	

	cout << " This is the TriU function of the matrix" << endl;
	SquareMatrix matU = SquareMatrix::Triu(mat);
	cout << matU << endl;
	
	wait();	
	
	cout << " This is the TriL function of the squarematrix " << endl;
	SquareMatrix matL = SquareMatrix::Tril(mat);
	cout << matL << endl;
	
	}

}

// Testing LU with no pivot
void LUnopiv () {

	{
	cout << " Test 1: Testing the LU with Symmetrical Matrix" << endl;
	cout << endl << " Need to define matrix to decompose and two zero matrices for L U " << endl;

	// Set up matrix
	double vec1[4] = {4,3,2,1};
	SquareMatrix mat = SquareMatrix::Toeplitz(vec1,4);

	cout << endl <<" it Does not matter what the input L U  matrices are as long as they " << endl;
	cout << " are SquareMatrix class" << endl;
	
	// Other matrices
	SquareMatrix L(2);
	SquareMatrix U(4);
	
	// function
	SquareMatrix::LU(mat,L,U);
	
	// print
	cout << endl << " Printing out the matrices " << endl;
	cout << " Origional " << endl << mat << endl;
	wait();
	cout << " L matrix " << endl << L << endl;
	cout << " U matrix " << endl << U << endl;
	wait();
	cout << " The multiple should return the origional L*U"  << endl;
	cout << (L*U) << endl;
	
	}
	wait();
	
	cout << "=======================================================================" << endl;
	// Test 2
	{
	cout << " Test 2: Testing the LU with Asymmetrical Matrix" << endl;
	cout << " Need to define matrix to decompose and three zero matrices " << endl;

	// Set up matrix
	SquareMatrix mat(4);

	mat.SetEntry(0,0,1); mat.SetEntry(0,1,3); mat.SetEntry(0,2,1); mat.SetEntry(0,3,2);
	mat.SetEntry(1,0,-1); mat.SetEntry(1,1,2); mat.SetEntry(1,2,1); mat.SetEntry(1,3,2);
	mat.SetEntry(2,0,3); mat.SetEntry(2,1,1); mat.SetEntry(2,2,4); mat.SetEntry(2,3,1);
	mat.SetEntry(3,0,3); mat.SetEntry(3,1,3); mat.SetEntry(3,2,-3); mat.SetEntry(3,3,-3);
	
	// Other matrices
	SquareMatrix L(2);
	SquareMatrix U(4);
	
	// function
	SquareMatrix::LU(mat,L,U);
	cout << " Printing out the matrices " << endl;
	cout << " Origional " << endl << mat << endl;
	wait();
	cout << " L matrix " << endl << L << endl;
	cout << " U matrix " << endl << U << endl;
	wait();
	cout << " The multiple should return the origional L*U"  << endl;
	cout << (L*U) << endl;
	
	}
	
	wait();
	cout << "=======================================================================" << endl;
	// Test 3
	{
	cout << " Test 3: Testing the LU with zero diagonals" << endl;

	// Set up matrix
	SquareMatrix mat(4);

	mat.SetEntry(0,0,0); mat.SetEntry(0,1,3); mat.SetEntry(0,2,1); mat.SetEntry(0,3,2);
	mat.SetEntry(1,0,-1); mat.SetEntry(1,1,0); mat.SetEntry(1,2,1); mat.SetEntry(1,3,2);
	mat.SetEntry(2,0,3); mat.SetEntry(2,1,1); mat.SetEntry(2,2,4); mat.SetEntry(2,3,1);
	mat.SetEntry(3,0,3); mat.SetEntry(3,1,3); mat.SetEntry(3,2,-3); mat.SetEntry(3,3,-3);
	
	// Other matrices
	SquareMatrix L(2);
	SquareMatrix U(4);
	
	// function
	SquareMatrix::LU(mat,L,U);
	cout << " Printing out the matrices " << endl;
	cout << " Origional " << endl << mat << endl;
	wait();
	cout << " L matrix " << endl << L << endl;
	cout << " U matrix " << endl << U << endl;
	wait();
	cout << " The multiple should return the origional L*U"  << endl;
	cout << (L*U) << endl;
	
	wait();
	cout << " If there are 0 on the diagonals it returns the origional matrices " << endl << endl;
	
	}
}

// Testing LU with pivoting
void LUwithpiv () {
	{
	// TEST 1
	
	cout << "Test 1 : Testing the LU With Pivoting" << endl;
	cout << " Create A Squarematrix with Toeplitz " << endl;
	
	// set up toepltiz
	double vec[4] = {1,2,3,4};
	double vec1[4] = {4,3,2,1};
	SquareMatrix mat = SquareMatrix::Toeplitz(vec,vec1,4);

	cout << " This is the Asymmetrix Matrix " << endl;
	cout << mat << endl;
		cout << " it Does not matter what the input L U P matrices are as long as the are SquareMatrix class" <<endl;
	
	// other inputs
	SquareMatrix L(2);
	SquareMatrix U(4);
	SquareMatrix P(5);
	
	// Function
	SquareMatrix::LU(mat,L,U,P);

	// Printing
	cout << " Printing out the matrices " << endl;
	cout << " Origional " << endl << mat << endl;
	wait();
	cout << " L matrix " << endl << L << endl;
	cout << " U matrix " << endl << U << endl;
	wait();
	cout << " P matrix " << endl << P << endl;
	// Check
	cout << " The multiple should return the origional P*A = L*U"  << endl;
	wait();
	cout << " P*A : " << endl << (P*mat) << "   " ;
	wait();
	cout << " L*U : " << endl << (L*U) << endl;

	}
	
	wait();
	
	// TEST 2
	cout << "=======================================================================" << endl;	
	{
	cout << "Test 2 : Testing the LU With Pivoting for a different case" << endl;
	cout << " Create A Squarematrix with Toeplitz " << endl;
	SquareMatrix mat(4);
	// SEt up matrix
	mat.SetEntry(0,0,1); mat.SetEntry(0,1,3); mat.SetEntry(0,2,1); mat.SetEntry(0,3,2);
	mat.SetEntry(1,0,-1); mat.SetEntry(1,1,2); mat.SetEntry(1,2,1); mat.SetEntry(1,3,2);
	mat.SetEntry(2,0,3); mat.SetEntry(2,1,1); mat.SetEntry(2,2,4); mat.SetEntry(2,3,1);
	mat.SetEntry(3,0,3); mat.SetEntry(3,1,3); mat.SetEntry(3,2,-3); mat.SetEntry(3,3,-3);

	cout << " This is the Asymmetrix Matrix " << endl;
	cout << mat << endl;
	
	// set up other matrices
	SquareMatrix L(2);
	SquareMatrix U(4);
	SquareMatrix P(5);
	
	// Function
	SquareMatrix::LU(mat,L,U,P);
	
	// Printing
	cout << " Printing out the matrices " << endl;
	cout << " Origional " << endl << mat << endl;
	wait();
	cout << " L matrix " << endl << L << endl;
	cout << " U matrix " << endl << U << endl;
	wait();
	cout << " P matrix " << endl << P << endl;
	
	// Checking they are right
	cout << " If correct P*A = L*U"  << endl;
	wait();
	cout << " P*A : " << endl << (P*mat) << "   " ;
	wait();
	cout << " L*U : " << endl << (L*U) << endl;

	}	
	
	wait();
	cout << "=======================================================================" << endl;	
	/// Test 3
	{
	cout << " Test 3 : Testing the LU With Pivoting with a singluar matrix" << endl;
	SquareMatrix mat = SquareMatrix::Ones(4);
	cout << " This is the Origional Matrix " << endl;
	cout << mat << endl;
	
	// Other Definitions
	SquareMatrix L(2);
	SquareMatrix U(4);
	SquareMatrix P(5);
	
	// Functions
	SquareMatrix::LU(mat,L,U,P);

	// Printing
	cout << " Printing out the matrices " << endl;
	cout << " Origional " << endl << mat << endl;
	wait();
	cout << " L matrix " << endl << L << endl;
	cout << " U matrix " << endl << U << endl;
	wait();
	cout << " P matrix " << endl << P << endl;
	wait();
	cout << " If correct P*A = L*U"  << endl;
	cout << " P*A : " << endl << (P*mat) << "   " ;
	cout << " L*U : " << endl << (L*U) << endl;
	wait();
	
	cout << " If it is singluar then it returns the origional matrices " << endl;
	}
	
	wait();
	cout << "=======================================================================" << endl;	
	// TEST 4
	{
	cout << " Test 4: Testing the LU With Pivoting test for row or coloumn of 0's" << endl;
	cout << " Need to define matrix to decompose and three zero matrices " << endl;
	SquareMatrix mat(4);
	
	// Set up matrix	
	mat.SetEntry(0,0,0); mat.SetEntry(0,1,1); mat.SetEntry(0,2,1); mat.SetEntry(0,3,0);
	mat.SetEntry(1,0,0); mat.SetEntry(1,1,3); mat.SetEntry(1,2,3); mat.SetEntry(1,3,1);
	mat.SetEntry(2,0,0); mat.SetEntry(2,1,7); mat.SetEntry(2,2,9); mat.SetEntry(2,3,5);
	mat.SetEntry(3,0,0); mat.SetEntry(3,1,7); mat.SetEntry(3,2,9); mat.SetEntry(3,3,8);

	cout << " This is the input Matrix " << endl;
	cout << mat << endl;
	wait();
	
	// Other Matrices
	SquareMatrix L(2);
	SquareMatrix U(4);
	SquareMatrix P(5);
	
	// Function
	SquareMatrix::LU(mat,L,U,P);

	// Printing
	cout << " Printing out the matrices " << endl;
	cout << " Origional " << endl << mat << endl;
	wait();
	cout << " L matrix " << endl << L << endl;
	cout << " U matrix " << endl << U << endl;
	cout << " P matrix " << endl << P << endl;
	wait();
	cout << " The multiple should return the origional P*A = L*U"  << endl;
	cout << " P*A : " << endl << (P*mat) << "   " ;
	cout << " L*U : " << endl << (L*U) << endl;
	
	cout << " This matrix is also singular " << endl;
	cout << " If it is singluar then it returns the origional matrices " << endl;

	}
	
	wait();
	cout << "=======================================================================" << endl;
	// TEST 5
	{
	cout << " Test 5: Special singluar cases for 2 by 2 matrices" << endl;
	SquareMatrix mat(2);
	
	// Set up matrix	
	mat.SetEntry(0,0,3); mat.SetEntry(0,1,1); 
	mat.SetEntry(1,0,3); mat.SetEntry(1,1,1); 
	cout << " This is the input Matrix, it is  singular " << endl;
	cout << mat << endl;
	wait();
	
	// Other Matrices
	SquareMatrix L(2);
	SquareMatrix U(2);
	SquareMatrix P(2);
	
	// Function
	SquareMatrix::LU(mat,L,U,P);

	// Printing
	cout << " Printing out the matrices " << endl;
	cout << " Origional " << endl << mat << endl;
	wait();
	cout << " L matrix " << endl << L << endl;
	cout << " U matrix " << endl << U << endl;
	cout << " P matrix " << endl << P << endl;
	wait();
	cout << " The multiple should return the origional P*A = L*U"  << endl;
	cout << " P*A : " << endl << (P*mat) << "   " ;
	cout << " L*U : " << endl << (L*U) << endl;
	
	cout << " This matrix is also singular " << endl;
	cout << " It works for singluar 2 by 2 matrices " << endl << endl;
	}
}

// testing forward and backward pass
void ForwardBackward () {
	// Test 1

	
	{
	cout << endl << "Test 1 :  Forward and Backward pass for solving equations " << endl;
	
	cout << endl << " Ax=B," << endl;
	
	// Set up matrix
	SquareMatrix mat(4);
	mat.SetEntry(0,0,2); mat.SetEntry(0,1,1); mat.SetEntry(0,2,1); mat.SetEntry(0,3,0);
	mat.SetEntry(1,0,4); mat.SetEntry(1,1,3); mat.SetEntry(1,2,3); mat.SetEntry(1,3,1);
	mat.SetEntry(2,0,8); mat.SetEntry(2,1,7); mat.SetEntry(2,2,9); mat.SetEntry(2,3,5);
	mat.SetEntry(3,0,6); mat.SetEntry(3,1,7); mat.SetEntry(3,2,9); mat.SetEntry(3,3,8);
	
	// Set up B matrix/ vector
	Matrix b(4,1);
	b.SetEntry(0,0,1); 
	b.SetEntry(1,0,0); 
	b.SetEntry(2,0,0); 
	b.SetEntry(3,0,0); 
	
	cout << " This is the matrix A " << mat << endl;
	wait();
	
	cout << " This is matrix B : " << b << endl;
	wait();
	
	// Test forward substitution 
	SquareMatrix L(4);
	SquareMatrix U(4);
	SquareMatrix P(4);
	
	cout << endl << " First the SquareMatrix has to use LU decomposition for triangular matrices "<< endl;
	
	// Lu function
	SquareMatrix::LU(mat,L,U,P);
	cout << "This is L : " << L << endl;
	cout << " This is u"<< U << endl;
	cout << " this is P : " << P << endl;
	wait();
	
	// Define PB	
	Matrix PB = P * b ;
	// Forward Substitution
	cout << endl << " Doing the Forward Substitution " << endl;
	Matrix Y = SquareMatrix::ForwardSub(PB,L); // Solves Ly = Pb
	
	cout << " Ly = Pb " << endl;
	cout << "Ly" << L*Y << endl;
	wait();
	cout << "Pb" << PB << endl;
	
	wait();
	cout << " This is Y " << Y << endl;

	// Backward Substitution
	cout << endl << " Doing the Backward Substitution " << endl;
	Matrix X = SquareMatrix::BackwardSub(Y,U); // Solves Ux = y

	//cout << " Solutions to the Equations " << endl;
	cout << " This is Matrix x: " << endl;
	cout << X << endl;
	cout << " U*x = Y " << U*X << endl;
	}
	
	wait();
	cout << "=======================================================================" << endl;
		
	{
	cout << " Test 2 : Everything combined in a Single Function " << endl;
	cout << endl << " Set up Matrices " << endl;
	
	// Set up
	SquareMatrix A(4);
	A.SetEntry(0,0,2); A.SetEntry(0,1,1); A.SetEntry(0,2,1); A.SetEntry(0,3,0);
	A.SetEntry(1,0,4); A.SetEntry(1,1,3); A.SetEntry(1,2,3); A.SetEntry(1,3,1);
	A.SetEntry(2,0,8); A.SetEntry(2,1,7); A.SetEntry(2,2,9); A.SetEntry(2,3,5);
	A.SetEntry(3,0,6); A.SetEntry(3,1,7); A.SetEntry(3,2,9); A.SetEntry(3,3,8);
	
	// Set up B matrix/ vector
	Matrix B(4,1);
	B.SetEntry(0,0,1); 
	B.SetEntry(1,0,0); 
	B.SetEntry(2,0,0); 
	B.SetEntry(3,0,0); 
	
	cout << " This is the matrix A " << A << endl;
	wait();
	
	cout << " This is matrix B " << B << endl;
	wait();
	
	cout << "X = LinSolve(A,B) : " << endl;
	Matrix X = SquareMatrix::LinSolve(A,B);
//	Matrix X = Matrix::LeastSquares(A,B);
	
	wait();
	
	cout << " This is X  " << X << endl ;
	wait();
	cout << " AX = B " << endl;
	cout << " This is B " << B << endl;
	cout << " This is A*X " << A*X << endl;
	cout << " LinSolve works for Square Matrices ie same unknowns and equations " << endl;
	
	}
	
	wait();
	cout << "=======================================================================" << endl;
		
	{
	cout << " Test 3 : Everything combined in a Single Function " << endl;
	cout << endl << " Set up Matrices " << endl;
	
/*	// Set up DEBUGGING TEST
	SquareMatrix A(3);
	A.SetEntry(0,0,2); A.SetEntry(0,1,1); A.SetEntry(0,2,1);
	A.SetEntry(1,0,4); A.SetEntry(1,1,3); A.SetEntry(1,2,3);
	A.SetEntry(2,0,8); A.SetEntry(2,1,7); A.SetEntry(2,2,9); 

	
	// Set up B matrix/ vector
	Matrix B(3,1);
	B.SetEntry(0,0,1); 
	B.SetEntry(1,0,0); 
	B.SetEntry(2,0,0); 
 
 
	
	cout << " This is the matrix A " << A << endl;
	wait();
	
	cout << " This is matrix B " << B << endl;
	wait();
	
	cout << "X = LinSolve(A,B) : " << endl;
	Matrix X = SquareMatrix::LinSolve(A,B);
	
	wait();
	
	cout << " This is X  " << X << endl ;
	wait();
	cout << " AX = B " << endl;
	cout << " This is B " << B << endl;
	cout << " This is A*X " << A*X << endl;
	cout << " LinSolve works for Square Matrices ie same unknowns and equations " << endl;
	
	
	// Other Matrices
	SquareMatrix L(2);
	SquareMatrix U(2);
	SquareMatrix P(2);
	
	wait();
	// Function
	SquareMatrix::LU(A,L,U,P);

	// Printing
	cout << " Printing out the matrices " << endl;
	cout << " Origional " << endl << A << endl;
	wait();
	cout << " L matrix " << endl << L << endl;
	cout << " U matrix " << endl << U << endl;
	cout << " P matrix " << endl << P << endl;
	wait();
	cout << " The multiple should return the origional P*A = L*U"  << endl;
	cout << " P*A : " << endl << (P*A) << "   " ;
	cout << " L*U : " << endl << (L*U) << endl;
	
	Matrix Y = SquareMatrix::ForwardSub( (P*B) ,L);
	cout << "This is Y " << Y << endl;
	
	
	Matrix OUT = SquareMatrix::BackwardSub(Y,U);
	
	cout << " This is X vector " << OUT << endl;
	}  */
	
	
	cout << " Testing LinSolve in matrix class, with least squares " << endl;
	cout << endl << " Set up Matrices " << endl;
	
	// Set up
	Matrix A(4,3);
	A.SetEntry(0,0,2); A.SetEntry(0,1,1); A.SetEntry(0,2,1); 
	A.SetEntry(1,0,4); A.SetEntry(1,1,3); A.SetEntry(1,2,3); 
	A.SetEntry(2,0,8); A.SetEntry(2,1,7); A.SetEntry(2,2,9); 
	A.SetEntry(3,0,6); A.SetEntry(3,1,7); A.SetEntry(3,2,9);
	
	// Set up B matrix/ vector
	Matrix B(4,1);
	B.SetEntry(0,0,1); 
	B.SetEntry(1,0,0); 
	B.SetEntry(2,0,0); 
	B.SetEntry(3,0,0); 

// OTher testS
/*	Matrix A(3,2);
	A.SetEntry(0,0,2); A.SetEntry(0,1,0); 
	A.SetEntry(1,0,-1); A.SetEntry(1,1,1); 
	A.SetEntry(2,0,0); A.SetEntry(2,1,2); 

	
	// Set up B matrix/ vector
	Matrix B(3,1);
	B.SetEntry(0,0,1); 
	B.SetEntry(1,0,0); 
	B.SetEntry(2,0,-1); */

/*	SquareMatrix A(4);
	A.SetEntry(0,0,16); A.SetEntry(0,1,2); A.SetEntry(0,2,3); A.SetEntry(0,3,13);
	A.SetEntry(1,0,5); A.SetEntry(1,1,11); A.SetEntry(1,2,10); A.SetEntry(1,3,8);
	A.SetEntry(2,0,9); A.SetEntry(2,1,7); A.SetEntry(2,2,6); A.SetEntry(2,3,12);
	A.SetEntry(3,0,4); A.SetEntry(3,1,14); A.SetEntry(3,2,15); A.SetEntry(3,3,1);
	
	// Set up B matrix/ vector
	Matrix B(4,1);
	B.SetEntry(0,0,81); 
	B.SetEntry(1,0,89); 
	B.SetEntry(2,0,89); 
	B.SetEntry(3,0,81); */

	
	cout << " This is the matrix A " << A << endl;
	wait();
	
	cout << " This is matrix B " << B << endl;
	wait();
	
	cout << "X = LeastSquares(A,B) : " << endl;
	Matrix X = Matrix::LeastSquares(A,B);
	
	wait();
	
	cout << " This is X  " << X << endl ;
	wait();
	
	
	}
	wait();
	cout << "=======================================================================" << endl;
		
	{
	cout << " Test 4 : Mismatching Dimensions ERROR " << endl;
	cout << endl << " Set up Matrices " << endl;
	
	// Set up
	Matrix A(4,3);
	A.SetEntry(0,0,2); A.SetEntry(0,1,1); A.SetEntry(0,2,1); 
	A.SetEntry(1,0,4); A.SetEntry(1,1,3); A.SetEntry(1,2,3); 
	A.SetEntry(2,0,8); A.SetEntry(2,1,7); A.SetEntry(2,2,9); 
	A.SetEntry(3,0,6); A.SetEntry(3,1,7); A.SetEntry(3,2,9);
	
	// Set up B matrix/ vector
	Matrix B(3,1);
	B.SetEntry(0,0,1); 
	B.SetEntry(1,0,0); 
	B.SetEntry(2,0,0); 

	
	cout << " This is the matrix A " << A << endl;

	cout << " This is matrix B " << B << endl;
	wait();
	
	cout << "X = LeastSquares(A,B) : " << endl;
	Matrix X = Matrix::LeastSquares(A,B);
	
	wait();
	
	cout << " This is X  " << X << endl ;
	wait();
	
	}
	

}












