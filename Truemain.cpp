#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include "Matrix.h"
#include "BinaryImage.h"

using namespace std;


// Reads .txt file 
double* readTXT(char *fileName, int sizeR, int sizeC);

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and Q=1 for binary images.
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

int main(){

	//M = Rows and N = columns in the image,
	int M = 512; int N = 512;
	//threshhold
	double thresh = 150, sd = 1000, sdcom;
	int start_row = 0, end_row = 31, start_col = 0, end_col = 31;
	//store both images data
	double* input_data_noise = 0;
	double* input_data_shuffle = 0;
	int count = 0;

	cout << endl;
	cout << "-------------- Reading Data from text file --------------" << endl;

	// input text filepath

	//char* inputFileName = "C:\\Users\\computing\\Desktop\\Assignment 1 - files\\Task1files\\logo_with_noise.txt";
	char* inputFileName = "C:\\Users\\Sinjun\\Desktop\\Assignment 1 - files\\Task1files\\logo_with_noise.txt";
	input_data_noise = readTXT(inputFileName, M, N);
	//inputFileName = "C:\\Users\\computing\\Desktop\\Assignment 1 - files\\Task1files\\logo_shuffled.txt";
	inputFileName = "C:\\Users\\Sinjun\\Desktop\\Assignment 1 - files\\Task1files\\logo_shuffled.txt";
	input_data_shuffle = readTXT(inputFileName, M, N);

	BinaryImage noise(M, N, input_data_noise, 170);
	BinaryImage shuffle(M, N, input_data_shuffle, 170);

	BinaryImage E(M, N, 0.0, thresh);

	//for (int i = 0; i < 31; i++)    //This loops on the rows.
	//{
	//	for (int j = 0; j < 31; j++) //This loops on the columns
	//	{
	//		cout << input_data_shuffle[i*N + j] << "";
	//	}
	//	cout << endl;
	//}
	double dif = 0;

	for (int i = 0; i < 16; i++)
	for (int j = 0; j < 16; j++){
		BinaryImage C = shuffle.getblock(i * 32, i * 32 + 31, j * 32, j * 32 + 31);//get a block from unnoised, to compare agienst

		for (int ii = 0; ii < 16; ii++)
		for (int jj = 0; jj < 16; jj++){//check agienst 16 times
			BinaryImage	D = noise.getblock(ii * 32, ii * 32 + 31, jj * 32, jj * 32 + 31);//takea block from shuffled, to compare agienst
			//D.Output_Matrix(32,32)
			//sdcom = SSD(C, D);


			for (int k = 0; k < 32; k++)
			for (int l = 0; l < 32; l++)
			{
				//cout << "d.get " << D.get(k, l) << " - " << " c.get " << C.get(k, l) << " = " << D.get(k, l) - C.get(k, l) << endl;
				dif += (D.get(k, l) - C.get(k, l)) * (D.get(k, l) - C.get(k, l));

			}
			//cout << dif << endl;
			//system("PAUSE");
			if (dif == 0)
			{
				for (int b = 0; b < 32; b++)
				for (int v = 0; v < 32; v++)
				{
					E.set((ii * 32) + b, (jj * 32) + v, (C.get(b, v)));


				}

			}
			dif = 0;
			/*
			if (sdcom < sd)
			{



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
			for (int j = 0; j < 32; j++) //This loops on the columns
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
			}*/
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
	for (int i = 0; i < 512; i++)
	for (int j = 0; j < 512; j++)
	{
		input_data_shuffle[count] = E.get(i, j);
		count++;
	}
	//noise.Output_Matrix(32, 32);
	//cout << endl << endl << endl;
	//E.Output_Matrix(32, 32);


	// outputs image path(where the image will be)

	//char* outputFileName = "C:\\Users\\computing\\Desktop\\Assignment 1 - files\\Task1files\\logo_with_noise.pgm";
	char* outputFileName = "C:\\Users\\\Sinjun\\Desktop\\Assignment 1 - files\\Task1files\\logo_with_noise.pgm";
	// Use Q = 255 for greyscale images and 1 for binary images.
	int Q = 1;
	WritePGM(outputFileName, input_data_noise, M, N, Q);
	//outputFileName = "C:\\Users\\computing\\Desktop\\Assignment 1 - files\\Task1files\\logo_shuffled121.pgm";
	outputFileName = "C:\\Users\\\Sinjun\\Desktop\\Assignment 1 - files\\Task1files\\logo_shuffled.pgm";
	WritePGM(outputFileName, input_data_shuffle, M, N, Q);
	delete[] input_data_noise;
	delete[] input_data_shuffle;

	return 0;
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
