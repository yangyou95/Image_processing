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
	readHeader(input,output,imageInfo);
	

}