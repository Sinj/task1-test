//Matrix.h file
#ifndef __BinaryImage_H_INCLUDED__   // if x.h hasn't been included yet...
#define __BinaryImage_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "Matrix.h"

class BinaryImage : public Matrix{

public:
	BinaryImage(int M, int N, double* input_data, double thresh);
	BinaryImage(int R, int C, double val, double thresh);
	BinaryImage(const BinaryImage&);
	//~BinaryImage(){ cout << "~BinaryImage() Destructor is invoked ..." << endl; delete[] data; }

	//
	BinaryImage operator+(const BinaryImage& X);
	BinaryImage operator-(const BinaryImage& X);
	BinaryImage operator*(const BinaryImage& X);
	//getblock
	BinaryImage getblock(int start_row, int end_row, int start_col, int end_col);

protected:

};




#endif