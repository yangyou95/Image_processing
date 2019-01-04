#include "ImageFunctions.h"
#include "header.h"


using namespace std;
int main(){
	string inputfile;
	

	ifstream input; // define input stream
	ofstream output; // define output stream
	char filename[20]; // set maximum size of filename
	int imageInfo[3]; //set image info number
	openIOFiles(input, output, filename); // call open function
	// readHeader(input,output,imageInfo); // Test readHeader success

	//Test converting function
	vector<vector<Pixel>> imagepiexel;

	convertP6ToP3(input, output, imagepiexel,imageInfo); //no problem







	//test smooth the image
	smooth(imagepiexel);


	//test output the p3 image
	char comment[MAXLEN] = { "# Edited by Yang" };
	ofstream output_smooth;
	//change the file path to the processed folder (Yang)
	string output_smooth_file_path = output_folder_path + filename + "smoothed.ppm";
	output_smooth.open(output_smooth_file_path);
	writeP3Image(output_smooth,imagepiexel,comment,255); 
}