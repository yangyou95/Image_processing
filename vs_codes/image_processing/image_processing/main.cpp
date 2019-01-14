#include "ImageFunctions.h"
#include "header.h"


using namespace std;
void image_process(vector<vector<Pixel>> &imagepiexel, char filename[]);

int main() {
	cout << "This program is used to process P6 type ppm image, Please slect the file needed to process in the binary folder, the output image will be stored as type P3." << endl;
	string inputfile;
	ifstream input; // define input stream
	ofstream output; // define output stream
	char filename[50]; // set maximum size of filename
	int imageInfo[3]; //set image info number
	vector<vector<Pixel>> imagepiexel; // define a pixel var in Pixel class
	openIOFiles(input, output, filename); // call open function
	convertP6ToP3(input, output, imagepiexel, imageInfo);//convert P6 type to P3 
	image_process(imagepiexel, filename); // call image process function
}

//Image processing function
void image_process(vector<vector<Pixel>> &imagepiexel, char filename[]) {
	int chosen; // the chosen value for process
	char comment[MAXLEN] = { "# Edited by Yang" }; // define the comment 		
	vector<vector<Pixel>> outputpiexel; // define a output pixel to store the information
	cout << "Please enter the number of which process you want choose: 1.Smooth; 2.Sharpen; 3. Edge detection." << endl;
	cin >> chosen;
	if (chosen == 1) {
		//image smoothing 
		smooth(imagepiexel,outputpiexel);
		//output the p3 image 
		ofstream output_smooth;
		//change the file path to the processed folder (Yang)
		string output_smooth_file_path = output_folder_path + filename + "_smoothed.ppm";
		output_smooth.open(output_smooth_file_path, ios::trunc);
		writeP3Image(output_smooth, outputpiexel, comment, 255);
	}
	else if (chosen == 2) {
		// image sharpening
		vector<vector<Pixel>> sharpenoutputpiexel;
		sharpen(imagepiexel, sharpenoutputpiexel);
		//output the p3 image 
		ofstream output_sharpen;
		//change the file path to the processed folder (Yang)
		string output_sharpen_file_path = output_folder_path + filename + "_sharpened.ppm";
		output_sharpen.open(output_sharpen_file_path, ios::trunc);
		writeP3Image(output_sharpen, sharpenoutputpiexel, comment, 255);
	}
	else if (chosen == 3) {
		//edge detection
		vector<vector<Pixel>> edgeoutputpiexel;
		vector<vector<Pixel>> h_edgeoutputpiexel;
		vector<vector<Pixel>> v_edgeoutputpiexel;
		edgedetection(imagepiexel, edgeoutputpiexel, v_edgeoutputpiexel,h_edgeoutputpiexel);
	
		ofstream output_v_edge;
		//change the file path to the processed folder (Yang)
		string output_v_edge_file_path = output_folder_path + filename + "v_edges.ppm";
		output_v_edge.open(output_v_edge_file_path, ios::trunc);
		writeP3Image(output_v_edge, v_edgeoutputpiexel, comment, 255);

		ofstream output_h_edge;
		//change the file path to the processed folder (Yang)
		string output_h_edge_file_path = output_folder_path + filename + "h_edges.ppm";
		output_h_edge.open(output_h_edge_file_path, ios::trunc);
		writeP3Image(output_h_edge, h_edgeoutputpiexel, comment, 255);
		
		ofstream output_edge;
		//change the file path to the processed folder (Yang)
		string output_edge_file_path = output_folder_path + filename + "_edges.ppm";
		output_edge.open(output_edge_file_path, ios::trunc);
		writeP3Image(output_edge, edgeoutputpiexel, comment, 255);
	}
	else {
		cout << "Wrong value!" << endl;
	}
}