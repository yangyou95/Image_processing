#include "ImageFunctions.h"
#include "header.h"


using namespace std;
void openIOFiles(ifstream& fin, ofstream& fout, char inputFilename[])
{
	// define filestreams
	char outputFilename[MAXLEN];

	//define files' paths (Yang)
	string input_file_path,output_file_path;

	// prompt user for input file
	cout << "enter filename ";
	cin >> inputFilename;


	//define the input file path (Yang)
	input_file_path = input_binary_folder_path + inputFilename;

	// open .ppm binary file for input
	fin.open(input_file_path, ios::binary);

	if (!fin) {
		cout << "could not open file:"<< input_file_path  <<" bye" << endl;
		
		exit(1);
	}

	// generate meaningful output filename
	strcpy(outputFilename, inputFilename);

	// terminate output fielname at .
	char* loc = strchr(outputFilename, '.');
	*loc = '\0';

	// add extension to name
	strcat(outputFilename, "P3.ppm");

	//change the file path to the processed folder (Yang)
	output_file_path = output_folder_path + outputFilename;

	// open .ppm ascii file for output, add truncate mode to clear the previous data(Yang).
	fout.open(output_file_path, ios::trunc);

	if (!fout) {
		cout << "cannot open output file: bye" << endl;
	}
}

void convertP6ToP3(ifstream& bin, ofstream& out, vector<vector<Pixel> >& image, int info[1])
{
	readHeader(bin, out, info);
	int width = info[0], height = info[1];
	readAndWriteImageData(bin, out, image, width, height);
}

 //tested, smoothing (Yang)
void smooth(vector<vector<Pixel> >& image, vector<vector<Pixel> >& output)
{
	int h = image.size();
	int w = image[0].size();

	// allocate memory for the output piexel
	output.resize(h); // allocate h rows
	for (int i = 0; i < h; i++)
	{
		output[i].resize(w);   // for each row allocate w columns
	}

	Pixel sum;
	for (int i=1; i<h-1; i++)
		for (int j = 1; j < w - 1; j++)
		{
			sum =  image[i + 1][j] + image[i - 1][j] + image[i][j + 1] + image[i][j - 1];
			sum = sum / 4;
			if (sum.getBlue() >= 255) {
				sum.setBlue(255);
			}
			else if (sum.getBlue() <= 0) {
				sum.setBlue(0);
			};
			if (sum.getGreen() >= 255) {
				sum.setGreen(255);
			}
			else if (sum.getGreen() <= 0) {
				sum.setGreen(0);
			};
			if (sum.getRed() >= 255) {
				sum.setRed(255);
			}
			else if (sum.getRed() <= 0) {
				sum.setRed(0);
			};
			output[i][j] = sum;
		}
}

//Written by yang
void sharpen(vector<vector<Pixel> >& image, vector<vector<Pixel> >& output)
{
	int h = image.size();
	int w = image[0].size();

	// allocate memory for the output piexel
	output.resize(h); // allocate h rows
	for (int i = 0; i < h; i++)
	{
		output[i].resize(w);   // for each row allocate w columns
	}

	Pixel sum;
	for (int i = 1; i < h - 1; i++) {
		for (int j = 1; j < w - 1; j++)
		{

			//First sharpen filter: Laplacian operator. (f(i,j) = g(i,j) - c*s(i,j)), cofficient c = 1.0
			//int C = 1.0; // Cofficient
			//int blue = image[i][j].getBlue() + C*( image[i][j].getBlue() * 8 - (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]).getBlue());
			//int green = image[i][j].getGreen() + C* (image[i][j].getGreen() * 8 - (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]).getGreen() );
			//int red = image[i][j].getRed()+ C*(image[i][j].getRed() * 8 - (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]).getRed() );
			
			//Laplacian operator could be also used for edge detection. -S(i,j)
			int blue = (image[i][j].getBlue() * 8 - (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]).getBlue());
			int green = (image[i][j].getGreen() * 8 - (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]).getGreen());
			int red = (image[i][j].getRed() * 8 - (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]).getRed());

			//Second sharpen filter
			//int blue = image[i][j].getBlue() * 12 - (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]).getBlue();
			//int green = image[i][j].getGreen() * 12 - (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]).getGreen();
			//int red = image[i][j].getRed() * 12 - (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]).getRed();
			//blue = blue / 4;
			//green = green / 4;
			//red = red / 4;

			//prevent overflow
			if (blue >= 255) {
				blue = 255;
			}
			else if (blue <= 0) {
				blue = 0;
			};
			if (green >= 255) {
				green = 255;
			}
			else if (green <= 0) {
				green =0 ;
			};
			if (red >= 255) {
				red = 255;
			}
			else if (red <= 0) {
				red = 0;
			};
			output[i][j].setBlue(blue); 
			output[i][j].setGreen(green);
			output[i][j].setRed(red);
		}
	}
}

//Written by Yang
void edgedetection(vector<vector<Pixel> >& image, vector<vector<Pixel> >& output, vector<vector<Pixel> >& vectorial, vector<vector<Pixel> >& horizontal)
{
	int h = image.size();
	int w = image[0].size();

	int vertical_filter[3][3] = { 1,2,1,
								0,0,0,
								-1,-2,-1 };

	int horizontal_filter[3][3] = { 1,0,-1,
									2,0,-2,
									1,0,-1
	};





	int sum_blue;
	int sum_green;
	int sum_red;
	// allocate memory for the output piexel
	output.resize(h); // allocate h rows
	vectorial.resize(h);
	horizontal.resize(h);

	for (int i = 0; i < h; i++)
	{
		output[i].resize(w);   // for each row allocate w columns
		vectorial[i].resize(w);   // for each row allocate w columns
		horizontal[i].resize(w);   // for each row allocate w columns
	}

	Pixel sum_vertical, sum_horizontal;

	for (int i = 1; i < h - 1; i++) {
		for (int j = 1; j < w - 1; j++)
		{
			//Vertical value variables' definition
			int blue_vertical; 
			int green_vertical;
			int red_vertical;

			//Horizontal value variables' definition
			int blue_horizontal;
			int green_horizontal;
			int red_horizontal;	

			//Initialize sum variables by 0
			int sum_blue_vertical = 0;
			int sum_green_vertical = 0;
			int sum_red_vertical = 0;
			int sum_blue_horizontal = 0;
			int sum_green_horizontal = 0;
			int sum_red_horizontal = 0;

			//filter process 
			for(int row =i - 1; row <= i+1;row++)
				for (int col = j - 1; col <= j + 1; col++) {	
					int a = row - (i -1);
					int b = col - (j - 1);
					//verical filter
					blue_vertical = image[row][col].getBlue() * vertical_filter[a][b];
					green_vertical = image[row][col].getGreen() * vertical_filter[a][b];
					red_vertical = image[row][col].getRed() * vertical_filter[a][b];

					sum_blue_vertical = sum_blue_vertical + blue_vertical;
					sum_green_vertical = sum_green_vertical + green_vertical;
					sum_red_vertical = sum_red_vertical + red_vertical;

					//horizontal filter
					blue_horizontal = image[row][col].getBlue() * horizontal_filter[a][b];
					green_horizontal = image[row][col].getGreen() * horizontal_filter[a][b];
					red_horizontal = image[row][col].getRed() * horizontal_filter[a][b];

					sum_blue_horizontal = sum_blue_horizontal + blue_horizontal;
					sum_green_horizontal = sum_green_horizontal + green_horizontal;
					sum_red_horizontal = sum_red_horizontal + red_horizontal;
				}
			//prevent vertical process overflow 
			if (sum_blue_vertical >= 255) {
				sum_blue_vertical = 255;
			}
			else if (sum_blue_vertical <= 0) {
				sum_blue_vertical = 0;
			};
			if (sum_green_vertical >= 255) {
				sum_green_vertical = 255;
			}
			else if (sum_green_vertical <= 0) {
				sum_green_vertical = 0;
			};
			if (sum_red_vertical >= 255) {
				sum_red_vertical = 255;
			}
			else if (sum_red_vertical <= 0) {
				sum_red_vertical = 0;
			};
			//prevent horizontal process overflow 
			if (sum_blue_horizontal >= 255) {
				sum_blue_horizontal = 255;
			}
			else if (sum_blue_horizontal <= 0) {
				sum_blue_horizontal = 0;
			};
			if (sum_green_horizontal >= 255) {
				sum_green_horizontal = 255;
			}
			else if (sum_green_horizontal <= 0) {
				sum_green_horizontal = 0;
			};
			if (sum_red_horizontal >= 255) {
				sum_red_horizontal = 255;
			}
			else if (sum_red_horizontal <= 0) {
				sum_red_horizontal = 0;
			};

			//vertical filter process result
			vectorial[i][j].setBlue(sum_blue_vertical);
			vectorial[i][j].setGreen(sum_green_vertical);
			vectorial[i][j].setRed(sum_red_vertical);
			//horizontal filter process result
			horizontal[i][j].setBlue(sum_blue_horizontal);
			horizontal[i][j].setGreen(sum_green_horizontal);
			horizontal[i][j].setRed(sum_red_horizontal);

			sum_blue = sqrt((pow(sum_blue_horizontal,2)) + (pow(sum_blue_vertical , 2)));
			sum_green = sqrt((pow(sum_green_horizontal , 2)) + (pow(sum_green_vertical,2)));
			sum_red = sqrt((pow(sum_red_horizontal , 2)) + (pow(sum_red_vertical ,2)));

			if (sum_blue >= 255) {
				sum_blue = 255;
			}
			else if (sum_blue <= 0) {
				sum_blue = 0;
			};
			if (sum_green >= 255) {
				sum_green = 255;
			}
			else if (sum_green <= 0) {
				sum_green = 0;
			};
			if (sum_red >= 255) {
				sum_red = 255;
			}
			else if (sum_red <= 0) {
				sum_red = 0;
			};
			output[i][j].setBlue(sum_blue);
			output[i][j].setGreen(sum_green);
			output[i][j].setRed(sum_red);

			sum_blue = 0;
			sum_green = 0;
			sum_red = 0;

		}
	}
}


void writeP3Image(ofstream& out, vector<vector<Pixel> >& image, char comment[], int maxColor)
{
	int h, w, pCount(0);
	char magicNumber[3] = "P3";
	h = (int)image.size();
	w = (int)image[0].size();

	writeHeader(out, magicNumber, comment, w, h, maxColor);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
		{
			out << image[i][j];
			++pCount;
			if (pCount == 10) {
				out << newline;
				pCount = 0;
			}
			else out << ' ';
		}
	}
}


void readAndWriteImageData(ifstream& fin, ofstream& fout, vector<vector<Pixel> >& image, int w, int h)
{
	// read and write image data
	// define input variables

	int charCount = 0;
	char colorByte;

	//test for P3 read
	int p3value;

	unsigned char aChar;
	unsigned int triple[3];   // red, green, blue

	// allocate memory
	image.resize(h); // allocate h rows

	for (int i = 0; i < h; i++)
	{
		image[i].resize(w);   // for each row allocate w columns
		for (int j = 0; j < w; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				// read one byte
				fin.read(&colorByte, 1);

				// convert to unsigned char
				aChar = (unsigned char)colorByte;

				// save as unsigned int
				triple[k] = (unsigned int)aChar;

				// write as int
				fout << triple[k] << ' ';
			}
			// CR printed over 32 pixels
			++charCount;
			if (charCount == 32) {
				fout << "\r\n";
				charCount = 0;
			}
			image[i][j].setPixel(triple[0], triple[1], triple[2]);
		}
	}
}

void readHeader(ifstream& fin, ofstream& fout, int imageInfo[])
{
	// define and initialise input variables
	char bData[MAXLEN] = { 0 }, magicNumber[MAXWIDTH], comment[MAXLEN] = { "#" };
	int bIndex = 0, charCount = 0, infoCount = 0;
	char ch, aNumber[MAXWIDTH];
	// input first line of text header(magic number)
	// if the magic number is not P6 exit the program
	fin.getline(magicNumber, 3); // can get (3-1=2) chars to "magicNumber" (Yang)
	
	if (strcmp(magicNumber, "P6") != 0)
	{
		cout << "unexpected file format\n";
		exit(1);
	}
	// clear bData array and reset bIndex
	// input next line of text header
	strcpy(bData, " ");
	bIndex = 0;
	fin.getline(bData, MAXLEN);
	do {
		// is this the beginning of a comment
		ch = bData[bIndex]; // the first character after "magicNumber" (Yang)
		if (ch == '#') {
			// comment has been read
			// get all characters until a newline is found
			charCount = 0;
			while (ch != terminator && charCount < MAXLEN) {  //terminator value is "@", it should be newline "OA" ? (Yang)
				comment[charCount] = ch;
				++bIndex;
				++charCount;
				ch = bData[bIndex];
				cout << ch;			
			}			
			//This part causing problem (Yang)
			if ((charCount == MAXLEN) && (ch != newline)) {
				cout << " comment exceeded max length of " << MAXLEN << endl;
				exit(1);
			}
			// get the next line of data
			strcpy(bData, " ");
			bIndex = 0;
			fin.getline(bData, MAXLEN);
		}
		else {
			// this is not a comment
			// parse bData for image information
			charCount = 0;
			// look past whitespace
			while (bIndex < MAXLEN && isspace(bData[bIndex])) {
				++bIndex;
			}
			// may be the beginning of a decimal value
			while (bIndex < MAXLEN && isdigit(bData[bIndex]))
			{
				aNumber[charCount] = bData[bIndex];
				++bIndex;
				++charCount;
				if (charCount == MAXWIDTH)
				{
					cerr << "Maximum width of " << MAXWIDTH << " digits was exceeded.. " << endl;
					exit(1);
				}
			}
			// look at size of aNumber
			if (charCount > 0) {
				// we have image information, terminate string
				aNumber[charCount] = nullChar;
				// convert from ascii to integer
				imageInfo[infoCount] = atoi(aNumber);
				++infoCount;
				// verify input
				switch (infoCount) {
				case 1: cout << "a width of " << imageInfo[infoCount - 1] << " has been read " << endl;
					break;
				case 2: cout << " a height of " << imageInfo[infoCount - 1] << " has bene read " << endl;
					break;
				case 3: cout << "maxcolor of " << imageInfo[infoCount - 1] << " has been read " << endl;
					break;
				}
			}
			else if (infoCount < 3) {
				// aNumber has 0 digits and infoCount < 3
				// we need more image information
				// get next line of data and parse for image information
				strcpy(bData, " ");
				bIndex = 0;
				fin.getline(bData, MAXLEN);
			}
		}
	} while (infoCount < 3 && !fin.eof());
	if (infoCount < 3) {
		cerr << "image information could not be found " << endl;
		exit(1);
	}
	// we have all of the information
	// write header to ascii file
	strcpy(magicNumber, "P3");
	writeHeader(fout, magicNumber, comment, imageInfo[0], imageInfo[1], imageInfo[2]);
}

void writeHeader(ofstream& fout, char magicNumber[], char comment[], int w, int h, int maxPixelVal)
{
	// write image imformation to output file
	fout << magicNumber << newline;
	fout << comment << newline;
	fout << w << ' ' << h << ' ' << maxPixelVal << newline;
}

void readP3Header(ifstream& fin, ofstream& fout, int imageInfo[])
{
	// define and initialise input variables
	char bData[MAXLEN] = { 0 }, magicNumber[MAXWIDTH], comment[MAXLEN] = { "#" };
	int bIndex = 0, charCount = 0, infoCount = 0;
	char ch, aNumber[MAXWIDTH];
	// input first line of text header(magic number)
	// if the magic number is not P6 exit the program
	fin.getline(magicNumber, 3); // can get (3-1=2) chars to "magicNumber" (Yang)

	if (strcmp(magicNumber, "P3") != 0)
	{
		cout << "unexpected file format\n";
		exit(1);
	}
	// clear bData array and reset bIndex
	// input next line of text header
	strcpy(bData, " ");
	bIndex = 0;
	fin.getline(bData, MAXLEN);
	do {
		// is this the beginning of a comment
		ch = bData[bIndex]; // the first character after "magicNumber" (Yang)
		if (ch == '#') {
			// comment has been read
			// get all characters until a newline is found
			charCount = 0;
			while (ch != terminator && charCount < MAXLEN) {  //terminator value is "@", it should be newline "OA" ? (Yang)
				comment[charCount] = ch;
				++bIndex;
				++charCount;
				ch = bData[bIndex];
				cout << ch;
			}
			//This part causing problem (Yang)
			if ((charCount == MAXLEN) && (ch != newline)) {
				cout << " comment exceeded max length of " << MAXLEN << endl;
				exit(1);
			}
			// get the next line of data
			strcpy(bData, " ");
			bIndex = 0;
			fin.getline(bData, MAXLEN);
		}
		else {
			// this is not a comment
			// parse bData for image information
			charCount = 0;
			// look past whitespace
			while (bIndex < MAXLEN && isspace(bData[bIndex])) {
				++bIndex;
			}
			// may be the beginning of a decimal value
			while (bIndex < MAXLEN && isdigit(bData[bIndex]))
			{
				aNumber[charCount] = bData[bIndex];
				++bIndex;
				++charCount;
				if (charCount == MAXWIDTH)
				{
					cerr << "Maximum width of " << MAXWIDTH << " digits was exceeded.. " << endl;
					exit(1);
				}
			}
			// look at size of aNumber
			if (charCount > 0) {
				// we have image information, terminate string
				aNumber[charCount] = nullChar;
				// convert from ascii to integer
				imageInfo[infoCount] = atoi(aNumber);
				++infoCount;
				// verify input
				switch (infoCount) {
				case 1: cout << "a width of " << imageInfo[infoCount - 1] << " has been read " << endl;
					break;
				case 2: cout << " a height of " << imageInfo[infoCount - 1] << " has bene read " << endl;
					break;
				case 3: cout << "maxcolor of " << imageInfo[infoCount - 1] << " has been read " << endl;
					break;
				}
			}
			else if (infoCount < 3) {
				// aNumber has 0 digits and infoCount < 3
				// we need more image information
				// get next line of data and parse for image information
				strcpy(bData, " ");
				bIndex = 0;
				fin.getline(bData, MAXLEN);
			}
		}
	} while (infoCount < 3 && !fin.eof());
	if (infoCount < 3) {
		cerr << "image information could not be found " << endl;
		exit(1);
	}
	// we have all of the information
	// write header to ascii file
	strcpy(magicNumber, "P3");
	writeHeader(fout, magicNumber, comment, imageInfo[0], imageInfo[1], imageInfo[2]);
}