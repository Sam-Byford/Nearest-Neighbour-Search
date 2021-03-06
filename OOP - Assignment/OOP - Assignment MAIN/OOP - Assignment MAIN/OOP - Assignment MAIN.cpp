/****************************************************PLEASE READ*****************************************************
   The code has been tested and does work in the labs without any modifications or alterations to Visual Studio needed.
   However this was a problem on my home PC so I feel the need to include this note anyway.
   
   Please disable "Predefined headers" in the properties section of the project
   Code has been copied over from CLion and does not like the lack of Predefined headers
   Code Does work on VS with these disabled and CLion without any modificaitons needed
 */

#include "Image.h"

int main() {
	//Timer
	int start = clock();
	//Standard variable/collection definition;
	pair <int, int> result;
	int smallC, smallR, largeR, largeC, Xoffset = 0, Yoffset = 0, ClosestX = 0, ClosestY = 0, LargeSize;
	float equal, ClosestNCC = -1;
	bool check;
	vector<double> alteredarr;
	//Pointers and dynamic variables
	double* Bigarray;
	double* smallarray;
	double** Full_Image;
	double** Wally_Image;
	double** tempmat;
	double** alterdmat;
	// Base Object declaration
	Base_Image *LargePtr; //base image object pointing to derived class object 'Large_Image'
	Base_Image *SmallPtr; //base image object pointing to derived class object 'Small_Image'

	//**********Large file**************************************************
	cout << "\n*****LARGE FILE*****" << endl;
	char Large_File[] = "Cluttered_scene.txt";

	Large_Image Linitialiser;
	LargePtr = &Linitialiser; //initial value of base pointer

	check = LargePtr->checkFile("Cluttered_scene.txt");
	if (check == 0) {
		return 0;
	}

	//Counting the number of rows and columns in the files
	result = LargePtr->getColumnsAndRows(Large_File);
	largeR = result.first;
	largeC = result.second;

	Large_Image Scene(largeR, largeC);
	LargePtr = &Scene; //base pointer value changed to accommodate initialisation of columns and rows

	cout << "Number of Rows in Large file = " << largeR << endl;
	cout << "Number of Columns in Large file = " << largeC << endl;

	//Reading files into program
	Bigarray = LargePtr->read_text(Large_File);

	//Converting files into matrix form
	Matrix table(largeR, largeC);
	Full_Image = table.matrixCreate(Bigarray);

	LargePtr->deleteData(Bigarray);

	//**********Wally file**************************************************
	cout << "\n*****WALLY FILE*****" << endl;
	char Small_File[] = "Wally_grey.txt";

	Ref_Image Sinitialiser;
	SmallPtr = &Sinitialiser;

	check = SmallPtr->checkFile("Wally_grey.txt");
	if (check == 0) {
		return 0;
	}

	//Counting the number of rows and columns in the files
	result = SmallPtr->getColumnsAndRows(Small_File);
	smallR = result.first;
	smallC = result.second;

	Ref_Image Wally(smallR, smallC);
	SmallPtr = &Wally; //base pointer value changed to accommodate initialisation of columns and rows

	cout << "Number of Rows in small file = " << smallR << endl;
	cout << "Number of Columns in small file = " << smallC << endl;

	//Reading files into program
	smallarray = SmallPtr->read_text(Small_File);

	cout << "\n*****OPERATOR OVERLOADING*****" << endl;
	//Converting files into matrix form
	//Using -table in order to set the new length and height of the matrix class to the smaller,
	//...reference image size of 36 columns and 49 rows
	//Prevents me from having to create another object with different height and width and demonstrates overloading skills
	cout << "Before overloading: Matrix dimensions = [" << table.getheight() << "*" << table.getlength() << "]" << endl;
	-table;
	cout << "After overloading: Matrix dimensions = [" << table.getheight() << "*" << table.getlength() << "]" << endl;
	Wally_Image = table.matrixCreate(smallarray);

	SmallPtr->deleteData(smallarray);

	cout << "\n*****COMPARISON*****" << endl;
	LargeSize = 712080; //The number of comparisons needed to search the whole image
	cout << "This step may take around 2 mins to complete" << endl;
	cout << "Calculating comparisons..." << endl;
	for (int i = 0; i < LargeSize; i++) {
		if ((Xoffset + smallC) > largeC) {
			Yoffset++;
			Xoffset = 0;
		}
		tempmat = Wally.getSection(Full_Image, Xoffset, Yoffset);

		equal = LargePtr->NCC(Wally_Image, tempmat, smallC, smallR);

		LargePtr->deleteData(tempmat, smallR);

		if (equal > ClosestNCC) {
			ClosestNCC = equal;
			ClosestX = Xoffset - 1;
			ClosestY = Yoffset;
		}
	}

	SmallPtr->deleteData(Wally_Image, smallR);

	//Output NCC results
	cout << "\n*****RESULTS*****" << endl;
	cout << "The closest match starts at x: " << ClosestX << " y: " << ClosestY << endl;
	cout << "The match has the NCC value " << ClosestNCC << endl;
	cout << "The values in the closest matching matrix are; " << endl;
	cout << endl;
	for (int y = ClosestY; y < (ClosestY + smallR); y++) {
		for (int x = ClosestX; x < (ClosestX + smallC); x++) {
			cout << Full_Image[y][x] << " ";
		}
	}
	cout << endl;
	//Circling wally
	
	//OVERLOAD '+' OPERATOR TO TURN TABLE'S HEIGHT AND LENGTH BACK TO GREATER VALUE
	cout << "\n*****OPERATOR OVERLOADING II*****" << endl;
	cout << "Before overloading: Matrix dimensions = [" << table.getheight() << "*" << table.getlength() << "]" << endl;
	+table;
	cout << "After overloading: Matrix dimensions = [" << table.getheight() << "*" << table.getlength() << "]" << endl;
	alterdmat = LargePtr->circleImage(Full_Image, ClosestX, ClosestY);

	alteredarr = table.matrixDestroy(alterdmat);

	LargePtr->deleteData(Full_Image, largeR);

	//Writing modified Image to file
	cout << "\n*****IMAGE WRITE*****" << endl;
	char Output_File[] = "Output_file.pgm";
	LargePtr->write_pgm(Output_File, alteredarr, largeR, largeC, 255);
	cout << "Image successfully written to file" << endl;

	//Calculate program execution time
	cout << "\n*****EXECUTION TIME*****" << endl;
	int stop = clock();
	cout << "Time: " << (stop - start) / double(CLOCKS_PER_SEC) << "s" << endl;

	cout << "\n*****DESTRUCTORS*****" << endl;
	return 0;
}
