//
// Created by samby on 02/11/2018.
//

#include "Image.h"

using namespace std;

Matrix::~Matrix() {
	cout << "Matrix destructor called" << endl;
}

Matrix::Matrix(const int& rows, const int& columns) {
	length = columns;
	height = rows;

	cout << "Matrix Parameterised constructor called with columns " << length << " and rows " << height << endl;
}

double** Matrix::matrixCreate(double array[]) {
	cout << "Matrix create class called" << endl;

	double** matrix = nullptr;
	matrix = new double*[height];

	for (int h = 0; h < height; h++) {
		matrix[h] = new double[length];
		for (int l = 0; l < length; l++) {
			matrix[h][l] = array[(h*length) + l];
		}

	}
	return matrix;
}

vector<double> Matrix::matrixDestroy(double**& mat) {
	vector<double> vect;
	for (n = 0; n < height; n++) {
		for (m = 0; m < length; m++) {
			vect.push_back(mat[n][m]);
		}
	}
	return vect;
}

void Matrix::operator-() {
	length = 36;
	height = 49;
}
void Matrix::operator+() {
	length = 1024;
	height = 768;
}

int Matrix::getheight() {
	return height;
}
int Matrix::getlength() {
	return length;
}