//
// Created by samby on 01/11/2018.
//

#include "Image.h"

using namespace std;
//Destructors
Base_Image::~Base_Image() {
	cout << "Base image destructor called" << endl;
};
Large_Image::~Large_Image() {
	cout << "Large image destructor called" << endl;
}
Ref_Image::~Ref_Image() {
	cout << "Ref image destructor called" << endl;
}

//Constructors
Large_Image::Large_Image() {
	cout << "Large Image default constructor called" << endl;
}
Large_Image::Large_Image(const int& rows, const int& columns) {
	width = columns;
	elevation = rows;
};
Ref_Image::Ref_Image() {
	cout << "Ref Image default constructor called" << endl;
}
Ref_Image::Ref_Image(const int& rows, const int& columns) {
	length = columns;
	height = rows;
};

bool Base_Image::checkFile(const string& FileName) {
	ifstream Reffile(FileName);
	if (Reffile.is_open()) {
		cout << "File loaded successfully" << endl;
		return 1;
	}
	else cout << "Unable to open file" << endl;

	return 0;
}

double** Ref_Image::getSection(double**& Full_Image, int& Xoffset, int& Yoffset) {
	tempmat = nullptr;
	counter1 = 0;
	counter2 = 0;

	//Get the upper limits for for loop
	check1 = height + Yoffset;
	check2 = length + Xoffset;

	//get lower limits for for loop
	offsetx = Xoffset;
	offsety = Yoffset;

	tempmat = new double *[height];
	for (int h = offsety; h < check1; h++) {
		tempmat[counter1] = new double[length];
		counter2 = 0;
		for (int l = offsetx; l < check2; l++) {
			tempmat[counter1][counter2] = Full_Image[h][l];
			counter2++;
		}
		counter1++;
	}

	Xoffset++;
	return tempmat;
};

float Base_Image::NCC(double**& Wally, double**& Section, const int& smallC, const int& smallR) {
	sum = 0;
	temp1 = 0;
	temp2 = 0;
	sqsum1 = 0;
	sqsum2 = 0;
	Wm = 0;
	Sm = 0;
	size = smallC * smallR;

	for (int h = 0; h < smallR; h++) {
		for (int l = 0; l < smallC; l++) {
			temp1 += Wally[h][l];
		}
	}

	for (int h = 0; h < smallR; h++) {
		for (int l = 0; l < smallC; l++) {
			temp2 += Section[h][l];
		}
	}

	Wm = temp1 / size;
	Sm = temp2 / size;

	for (int x = 0; x < smallR; x++) {
		for (int y = 0; y < smallC; y++) {
			sum += (Wally[x][y] - Wm) * (Section[x][y] - Sm);
			sqsum1 += pow((Wally[x][y] - Wm), 2);
			sqsum2 += pow((Section[x][y] - Sm), 2);
		}
	}
	float result = (sum / (sqrt(sqsum1*sqsum2)));
	return result;
};

double** Base_Image::circleImage(double**& Full_Image, const int& xpos, const int& ypos) {
	//Above
	for (int x = xpos; x <= (xpos + 36); x++) {
		Full_Image[ypos][x] = 0;
	}
	//Below
	for (int x = xpos; x <= (xpos + 36); x++) {
		Full_Image[(ypos + 50)][x] = 0;
	}
	//Left
	for (int y = ypos; y <= (ypos + 50); y++) {
		Full_Image[y][(xpos - 1)] = 0;
	}
	//Right
	for (int y = ypos; y <= (ypos + 50); y++) {
		Full_Image[y][(xpos + 37)] = 0;
	}
	return Full_Image;
};

//Delete Data
void Base_Image::deleteData(double *item) {
	delete[] item;
	item = nullptr;
}
void Base_Image::deleteData(double **item, const int& h) {
	for (int x = 0; x < h; x++) {
		delete[] item[x];
	}
	delete[] item;
	item = nullptr;
}

//Get number of columns and rows in file
pair <int, int> Base_Image::getColumnsAndRows(char *file) {
	cout << "This class will be overriden. Nothing should display" << endl;
	pair<int, int> nothing(0, 0);
	return nothing;
};
pair <int, int> Ref_Image::getColumnsAndRows(char* file) {
	cout << "Ref_Image derived 'getColumnsAndRows' class called" << endl;
	RowC = 0;
	ColumnC = 0;
	string Columns;
	string rows;

	//Work out number of rows
	ifstream Rfile(file);
	while (getline(Rfile, rows)) {
		RowC++;
	}
	Rfile.close();

	//Work out number of columns
	ifstream Cfile(file);
	getline(Cfile, Columns);
	ColumnC = Columns.length() / 16;
	Cfile.close();

	ColumnsAndRows = make_pair(RowC, ColumnC);
	return ColumnsAndRows;
};
pair <int, int> Large_Image::getColumnsAndRows(char* file) {
	cout << "Large_Image derived 'getColumnsAndRows' class called" << endl;
	RowC = 0;
	ColumnC = 0;
	string Columns;
	string rows;

	//Work out number of rows
	ifstream Rfile(file);
	while (getline(Rfile, rows)) {
		RowC++;
	}
	Rfile.close();

	//Work out number of columns
	ifstream Cfile(file);
	getline(Cfile, Columns);
	ColumnC = Columns.length() / 16;
	Cfile.close();

	ColumnsAndRows = make_pair(RowC, ColumnC);
	return ColumnsAndRows;
};

double* Base_Image::read_text(char* fileName) {
	cout << "This class will be overriden. Nothing should display" << endl;
	return 0;
}
double* Ref_Image::read_text(char *fileName) {
	cout << "Ref_Image derived 'read_text' class called" << endl;
	size = height * length;
	double* data = new double[size];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i > size - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out.
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;
};
double* Large_Image::read_text(char *fileName) {
	cout << "Large_Image derived 'read_text' class called" << endl;
	size = width * elevation;
	double* data = new double[size];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i > size - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out.
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;
};

void Base_Image::write_pgm(char *filename, const vector<double>& data, const int& sizeR, const int& sizeC, const int& Q) {
	ofstream myfile;
	size = sizeR * sizeC;
	image = (unsigned char *) new unsigned char[size];

	// convert the integer values to unsigned char

	for (i = 0; i < size; i++) {
		image[i] = (unsigned char)data[i];
	}
	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC) * sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

};