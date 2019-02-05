//
// Created by samby on 01/11/2018.
//

#ifndef ASSIGNMENT_IMAGE_H
#define ASSIGNMENT_IMAGE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <cctype>
#include <ctime>
#include <utility>
#include <math.h>
#include <cmath>

using namespace std;

class Base_Image{
private:
    unsigned char *image;
    int i, j;
    float sum, temp1, temp2, sqsum1, sqsum2, Wm, Sm;
protected:
    int size, RowC, ColumnC;
    pair <double,int> ColumnsAndRows;
public:
    virtual double* read_text(char* fileName);
    virtual pair <int,int> getColumnsAndRows(char* file);
    void write_pgm(char *filename, const vector<double>& data, const int& sizeR, const int& sizeC, const int& Q);
    void deleteData(double* item);
    void deleteData (double** item, const int& h);
    bool checkFile(const string& fileName);
    float NCC(double**& Wally, double**& Section, const int& smallC, const int& smallR);
    double** circleImage(double**& Full_Image, const int& xpos, const int& ypos);
    ~Base_Image();
};

class Ref_Image:public Base_Image{
private:
    int length, height,offsetx, offsety, counter1, counter2, check2, check1;
    double** tempmat;
public:
    Ref_Image();
    Ref_Image(const int& rows, const int& columns);
    pair <int,int> getColumnsAndRows(char* file)override;
    double* read_text( char*fileName) override;
    double** getSection(double**& Full_Image, int& Xoffset, int& Yoffset);
    ~Ref_Image();
};

class Large_Image:public Base_Image{
private:
    int width, elevation;
public:
    Large_Image();
    Large_Image(const int& rows, const int& columns);
    pair <int,int> getColumnsAndRows(char* file)override;
    double* read_text(char *fileName) override;
    ~Large_Image();
};

class Matrix{
private:
    int length, height, n, m;
    double* array;
public:
    Matrix(const int& rows, const int& columns);
    double** matrixCreate(double array[]);
    vector<double> matrixDestroy(double**& mat);
    void operator- ();
    void operator+ ();
    int getlength();
    int getheight();
    ~Matrix();
};

#endif //ASSIGNMENT_IMAGE_H
