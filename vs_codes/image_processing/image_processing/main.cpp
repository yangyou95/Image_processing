#include "ImageFunctions.h"
#include "header.h"


using namespace std;
void image_process(vector<vector<Pixel>> &imagepiexel, char filename[]);

int main(){
	string inputfile;
	ifstream input; // define input stream
	ofstream output; // define output stream
	char filename[50]; // set maximum size of filename
	int imageInfo[3]; //set image info number
	vector<vector<Pixel>> imagepiexel; // define a pixel var in Pixel class
	int type;// the type of ppm file
	cout << "Please choose the number of which kind of ppm type you want process: 1. P3 or 2. P6." << endl;
	cin >> type;
	if (type == 1) { // PROBLEM!
		openIOFiles(input, output, filename,type); // call open function
		readP3Header(input, output, imageInfo);
		int w = imageInfo[0],h = imageInfo[1];
		readAndWriteImageData(input, output,imagepiexel, w, h); //read P3 type data; causing problem, because of byte read?
		image_process(imagepiexel,filename); // image process function
	}
	else if(type ==2)
	{
		openIOFiles(input, output, filename,type); // call open function
		convertP6ToP3(input, output, imagepiexel, imageInfo);//convert P6 type to P3 
		image_process(imagepiexel, filename); // image process function
	}
	else {
		cout << "No such kind of type!" << endl;
	}
}


void image_process(vector<vector<Pixel>> &imagepiexel, char filename[]) {
	int chosen; // the chosen value for process
	char comment[MAXLEN] = { "# Edited by Yang" }; // define the comment 		
	vector<vector<Pixel>> outputpiexel; // define a output pixel to store the information
	cout << "Please enter the number of which process you want choose: 1.Smooth; 2. Sharpen; 3. Edge detection." << endl;
	cin >> chosen;
	if (chosen == 1) {
		//test smooth the image (Tested)
		smooth(imagepiexel);
		//test output the p3 image (Tested)
		ofstream output_smooth;
		//change the file path to the processed folder (Yang)
		string output_smooth_file_path = output_folder_path + filename + "smoothed.ppm";
		output_smooth.open(output_smooth_file_path, ios::trunc);
		writeP3Image(output_smooth, imagepiexel, comment, 255);
	}
	else if (chosen == 2) {
		//test smooth the image 
		vector<vector<Pixel>> outputpiexel;
		sharpen(imagepiexel, outputpiexel);
		//test output the p3 image (
		ofstream output_sharpen;
		//change the file path to the processed folder (Yang)
		string output_sharpen_file_path = output_folder_path + filename + "sharpened.ppm";
		output_sharpen.open(output_sharpen_file_path, ios::trunc);
		writeP3Image(output_sharpen, outputpiexel, comment, 255);
	}
	else if (chosen == 3) {
		//test edge detection
		edgedetection(imagepiexel, outputpiexel);
		ofstream output_edge;
		//change the file path to the processed folder (Yang)
		string output_edge_file_path = output_folder_path + filename + "edges.ppm";
		output_edge.open(output_edge_file_path, ios::trunc);
		writeP3Image(output_edge, outputpiexel, comment, 255);
	}
	else {
		cout << "Wrong value!" << endl;
	}
}