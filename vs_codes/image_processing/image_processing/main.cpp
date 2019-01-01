#include "ImageFunctions.h"
#include "header.h"

void openIOFiles(ifstream& fin, ofstream& fout, char inputFilename[]);
using namespace std;
int main(){
	string inputfile;
	

	ifstream input;
	ofstream output;
	char filename[10];
	openIOFiles(input, output, filename);
	

}