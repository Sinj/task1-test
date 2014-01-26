#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
using namespace std;


// Reads .txt file 
double* readTXT(char *fileName, int sizeR, int sizeC);

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and Q=1 for binary images.
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);




class Matrix{

public:
	//if you didnt have a data set
	Matrix(int sizeR, int sizeC, double val);
	//if you have data to work with
	Matrix(int sizeR, int sizeC, double* pData);
	//Copy constructor
	Matrix(const Matrix& X);
	//call the destructor class
	~Matrix(){ /*cout <<"~Matrix() Destructor is invoked ..." << endl;*/ delete[] data; }

	//Operators
	Matrix operator+(const Matrix& X);
	Matrix operator-(const Matrix& X);
	Matrix operator*(const Matrix& X);
	Matrix operator/(const Matrix& X);
	Matrix operator=(const Matrix& X);
	Matrix operator++();//increment
	Matrix operator--();//decrement
	double operator()(int i, int j)const{ cout << "Matrix::operator() is invoked..." << endl; return data[i*N + j]; }; // Operator () == get function

	//get the value from the matrix class data
	double get(int i, int j) const { return data[i*N + j]; }// const will stop the function from changing values in the matrix

	//set a new value for a element in the martix class data
	void set(int i, int j, double val){ data[i*N + j] = val; }

	//Matrix getblock 
	Matrix getblock(int start_row, int end_row, int start_col, int end_col);

	//get M
	int getM()const{ return M; };

	//get N
	int getN()const { return N; };

	//output the whole matrix
	void Output_Matrix(int row, int col){
		for (int i = 0; i < row; i++)    //This loops on the rows.
		{
			for (int j = 0; j < col; j++) //This loops on the columns
			{
				cout << data[i*N + j] << "  ";
			}
			cout << endl;
		}
	};


protected:
	int M; //number of rows
	int N; //number of columns
	double* data;

};

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

double SSD(BinaryImage, BinaryImage);

int main(){

	//M = Rows and N = columns in the image,
	int M = 512; int N = 512;
	//threshhold
	double thresh = 150, sd = 1000, sdcom;
	int start_row = 0, end_row = 31, start_col = 0, end_col = 31;
	//store both images data
	double* input_data_noise = 0;
	double* input_data_shuffle = 0;


	cout << endl;
	cout << "-------------- Reading Data from text file --------------" << endl;

	// input text filepath

	//char* inputFileName = "C:\\Users\\computing\\Desktop\\Assignment 1 - files\\Task1files\\logo_with_noise.txt";
	char* inputFileName = "C:\\Users\\Sinjun\\Desktop\\Assignment 1 - files\\Task1files\\logo_with_noise.txt";
	input_data_noise = readTXT(inputFileName, M, N);
	//inputFileName = "C:\\Users\\computing\\Desktop\\Assignment 1 - files\\Task1files\\logo_shuffled.txt";
	inputFileName = "C:\\Users\\Sinjun\\Desktop\\Assignment 1 - files\\Task1files\\logo_shuffled.txt";
	input_data_shuffle = readTXT(inputFileName, M, N);

	//for (int i = 0; i < 31; i++)    //This loops on the rows.
	//{
	//	for (int j = 0; j < 31; j++) //This loops on the columns
	//	{
	//		cout << input_data_shuffle[i*N + j] << "  ";
	//	}
	//	cout << endl;
	//}
	int o = 0, count = 0;
	BinaryImage A(M, N, input_data_noise, thresh);
	BinaryImage B(M, N, input_data_shuffle, thresh);

	//BinaryImage E(M, N, 0.0, thresh);

	for (int i = 0; i < 16; i++)
	for (int j = 0; j < 16; j++){
		BinaryImage C = A.getblock(i * 32, i * 32 + 31, j * 32, j * 32 + 31);//get a block from unnoised, to compare agienst
		for (int ii = 0; ii < 16; ii++)
		for (int jj = 0; jj < 16; jj++){//check agienst 16 times

			BinaryImage	D = B.getblock(jj * 32, jj * 32 + 31, jj * 32, jj * 32 + 31);//takea block from shuffled, to compare agienst
			//D.Output_Matrix(32,32)
			sdcom = SSD(C, D);
			if (sdcom < sd)
			{
				if (){}


				//for (int i = 0; i < 31; i++)    //This loops on the rows.
				//{
				//	for (int j = 0; j < 31; j++) //This loops on the columns
				//	{
				//		cout << input_data_shuffle[i*N + j] << "-";
				//	}
				//	cout << endl << endl;
				//}
				for (int i = 0; i < 32; i++)    //This loops on the rows.
				{
					for (int j = o; j < 32; j++) //This loops on the columns
					{
						input_data_shuffle[(ii * 32) + i] = D.get(i, j);
						//count++;
					}
				}
				//for (int i = 0; i < 31; i++)    //This loops on the rows.
				//{
				//	for (int j = 0; j < 31; j++) //This loops on the columns
				//	{
				//		cout << input_data_shuffle[i*N + j] << "-";
				//	}
				//	cout << endl<<endl;
				//}
				//o++;
				sd = sdcom;
			}

		}
		//for (int i = 0; i < 31; i++)    //This loops on the rows.
		//{
		//	for (int j = 0; j < 31; j++) //This loops on the columns
		//	{
		//	input_data_shuffle[i*N + j] == E.get(i,j);
		//	}
		//	cout << endl;
		//}

	}


	// outputs image path(where the image will be)

	//char* outputFileName = "C:\\Users\\computing\\Desktop\\Assignment 1 - files\\Task1files\\logo_with_noise.pgm";
	char* outputFileName = "C:\\Users\\\Sinjun\\Desktop\\Assignment 1 - files\\Task1files\\logo_with_noise.pgm";
	// Use Q = 255 for greyscale images and 1 for binary images.
	int Q = 255;
	WritePGM(outputFileName, input_data_noise, M, N, Q);
	//outputFileName = "C:\\Users\\computing\\Desktop\\Assignment 1 - files\\Task1files\\logo_shuffled.pgm";
	outputFileName = "C:\\Users\\\Sinjun\\Desktop\\Assignment 1 - files\\Task1files\\logo_shuffled.pgm";
	WritePGM(outputFileName, input_data_shuffle, M, N, Q);
	delete[] input_data_noise;
	delete[] input_data_shuffle;

	return 0;
}

double SSD(BinaryImage X, BinaryImage Z)
{
	//BinaryImage Y(32,32,0.0,170);

	double ssd = 0.0;

	//Z - X;
	//X.Output_Matrix(32,32);
	//cout << "-----------------------------------" << endl;
	//Z.Output_Matrix(32, 32);
	for (int i = 0; i < 32; i++)    //This loops on the rows.
	for (int j = 0; j < 32; j++) //This loops on the columns
	{
		/*Z.set(i, j, Z.get(i, j)*Z.get(i, j));
		ssd += Z.get(i, j);*/
		//cout << "Z.get(i, j) " << Z.get(i, j) << " - " << X.get(i, j) << " = " << Z.get(i, j) - X.get(i, j)<<endl;
		ssd += (Z.get(i, j) - X.get(i, j))*(Z.get(i, j) - X.get(i, j));
	}


	return ssd;
}

// Read .txt file with image of size RxC, and convert to an array of doubles
double* readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i > sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;
}

// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i, j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i < sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;
}

//Matrix constructors
Matrix::Matrix(int sizeR, int sizeC, double val){
	//cout << "Matrix(int, int, double) Constructor is invoked ..." << endl;
	M = sizeR;
	N = sizeC;
	data = new double[M*N];

	for (int ii = 0; ii < M; ii++){
		for (int jj = 0; jj < N; jj++){
			data[ii*N + jj] = val;
		}
	}
}
Matrix::Matrix(int sizeR, int sizeC, double* pData){
	//cout << "Matrix(int, int, double*) Constructor is invoked ..." << endl;
	M = sizeR;
	N = sizeC;

	data = new double[M*N];

	for (int ii = 0; ii < M; ii++){
		for (int jj = 0; jj < N; jj++){
			data[ii*N + jj] = pData[ii*N + jj];
		}
	}

}
Matrix::Matrix(const Matrix& X)
{
	//cout << "Matrix::Matrix(const Matrix& X) is invoked" << endl;

	M = X.M;
	N = X.N;
	data = new double[M*N];

	for (int i = 0; i < M*N; i++)
	{
		data[i] = X.data[i];
	}
}

//Matrix operators 
Matrix Matrix::operator+(const Matrix& X)
{
	//cout << "Matrix::operator+ is invoked..." << endl;
	double val = 0;
	Matrix Z(M, N, val);
	for (int i = 0; i < M; i++)
	for (int j = 0; j < N; j++){
		val = data[i*N + j] + X(i, j);
		Z.set(i, j, val);
	}
	return Z;
}
Matrix Matrix::operator-(const Matrix& X)
{//A-B
	//cout << "Matrix::operator- is invoked..." << endl;
	double val = 0;
	Matrix Z(M, N, val);
	for (int i = 0; i < M; i++)
	for (int j = 0; j < N; j++){
		val = data[i*N + j] - X(i, j);
		Z.set(i, j, val);
	}
	return Z;
}
Matrix Matrix::operator*(const Matrix& X)
{
	//cout << "Matrix::operator* is invoked..." << endl;
	double val = 0;
	Matrix Z(M, N, val);
	for (int i = 0; i < M; i++)
	for (int j = 0; j < N; j++){
		val = data[i*N + j] * X(i, j);
		Z.set(i, j, val);
	}
	return Z;
}
Matrix Matrix::operator/(const Matrix& X)
{
	//cout << "Matrix::operator/ is invoked..." << endl;
	double val = 0;
	Matrix Z(M, N, val);
	for (int i = 0; i < M; i++)
	for (int j = 0; j < N; j++){
		val = data[i*N + j] / X(i, j);
		Z.set(i, j, val);
	}
	return Z;
}
Matrix Matrix::operator=(const Matrix& X)
{
	//cout << "Matrix::operator= is invoked..." << endl;
	//for (int i = 0; i < 31; i++)    //This loops on the rows.
	//{
	//	for (int j = 0; j < 31; j++) //This loops on the columns
	//	{
	//		cout << X.data[i*N + j] << " ";
	//	}
	//	cout << endl;
	//}



	//check if X == X
	if (&X == this)
	{
		return X;
	}
	else
	{

		//delete current data
		delete[] data;

		//overwrite M and N
		M = X.getM();
		N = X.getN();

		//make new data
		for (int i = 0; i < M; i++){
			for (int j = 0; j < N; j++){
				set(i, j, X.data[i*N + j]);
			}
		}
		return *this;
	}
}
Matrix Matrix::operator++ ()
{
	//cout << "Matrix::operator++ is invoked..." << endl;
	for (int i = 0; i < M; i++){
		for (int j = 0; j < N; j++){
			set(i, j, get(i, j) + 1);
		}
	}
	return *this;
}
Matrix Matrix::operator-- ()
{
	//cout << "Matrix::operator-- is invoked..." << endl;
	{
		for (int i = 0; i < M; i++){
			for (int j = 0; j < N; j++){
				set(i, j, get(i, j) - 1);
			}
		}
		return *this;
	}
}

//Matrix get block 
Matrix Matrix::getblock(int start_row, int end_row, int start_col, int end_col)
{
	//cout << "getblock(int start_row, int end_row, int start_col, int end_col) is invoked" << endl;


	Matrix X(end_row - start_row + 1, end_col - start_col + 1, 0.0);

	for (int i = start_row; i <= end_row; i++)
	{
		for (int j = start_col; j <= end_col; j++)
		{
			X.set(i - start_row, j - start_col, data[i*N + j]);

		}
	}
	/*cout<<endl;
	X.Output_Matrix(32,32);
	getchar();*/
	return X;


}

//BinaryImage constructors
BinaryImage::BinaryImage(int M, int N, double* input_data, double thresh) :Matrix(M, N, input_data)
{
	//cout << "BinaryImage::BinaryImage(int M, int N, double* input_data, double thresh) is invoked...." << endl;

	for (int i = 0; i < M; i++){
		for (int j = 0; j<N; j++){
			if (input_data[i*N + j]>thresh){
				data[i*N + j] = 1;
			}
			else
				data[i*N + j] = 0;

		}
	}
}

BinaryImage::BinaryImage(int R, int C, double val, double thresh) :Matrix(R, C, val)
{
	M = R;
	N = C;
	data = new double[M*N];

	for (int ii = 0; ii < M; ii++){
		for (int jj = 0; jj < N; jj++){
			data[ii*N + jj] = val;
		}
	}

}

BinaryImage::BinaryImage(const BinaryImage& X) :Matrix(X)
{
	//cout << " BinaryImage::BinaryImage(const BinaryImage&) is invoked.." << endl;

	M = X.M;
	N = X.N;
	data = new double[M*N];

	for (int i = 0; i < M*N; i++)
	{
		data[i] = X.data[i];
		//cout << "data " << data[i] << " X.data " << X.data[i] <<endl;
	}
}


//BinaryImage operators

BinaryImage BinaryImage::operator+(const BinaryImage& X)
{
	//using Bitwise OR logic, if ethier data == 1 or if both then val = 1
	double val = 0;

	BinaryImage Z(M, N, val, 150);
	for (int i = 0; i < M; i++)
	for (int j = 0; j < N; j++){
		if (data[i*N + j] == 0 && X(i, j) == 0){
			val = 0;
		}
		else
			val = 1;
		Z.set(i, j, val);
	}
	return Z;
}
BinaryImage BinaryImage::operator-(const BinaryImage& X)
{
	//using Bitwise XOR logic, if both data == 1 or 0 then val = 0
	//cout << "BinaryImage::operator- is invoked..." << endl;
	double val = 0;
	int i, j;
	BinaryImage Z(M, N, val, 150);
	for (i = 0; i < M; i++)
	for (j = 0; j < N; j++){
		//cout << "data= " << data[i*N + j] << " x =" << X.data[i*N + j]<<endl;
		if (data[i*N + j] == X.data[i*N + j]){
			val = 0;
		}
		else{
			val = 1.0;
		}
		Z.set(i, j, val);
	}
	Z.Output_Matrix(M, N);
	return Z;
}
BinaryImage BinaryImage::operator*(const BinaryImage& X)
{
	//using Bitwise AND logic, only if both set == 1, than val = 1
	//cout << "BinaryImage::operator* is invoked..." << endl;
	double val = 0;
	BinaryImage Z(M, N, val, 150);
	for (int i = 0; i < M; i++)
	for (int j = 0; j < N; j++){
		if (data[i*N + j] == 1 && X(i, j) == 1){
			val = 1;
		}
		else
			val = 0;
		Z.set(i, j, val);
	}
	return Z;
}

//BinaryImage getblock

BinaryImage BinaryImage::getblock(int start_row, int end_row, int start_col, int end_col)
{
	//cout << "getblock(int start_row, int end_row, int start_col, int end_col) is invoked" << endl;


	BinaryImage X(end_row - start_row + 1, end_col - start_col + 1, 0.0, 170);

	for (int i = start_row; i <= end_row; i++)
	{
		for (int j = start_col; j <= end_col; j++)
		{
			X.set(i - start_row, j - start_col, data[i*N + j]);
		}
	}
	return X;
}