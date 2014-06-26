//Qt
#include <QImage>
//c++ std
#include <iostream>
#include <fstream>
//c std
#include <cstdlib>
#include <cstring>

using namespace std;

const char P2A_COLORS[][8] = {
	"\e[30m",
	"\e[31m",
	"\e[32m",
	"\e[33m",
	"\e[34m",
	"\e[35m",
	"\e[36m",
	"\e[37m",
	"\e[40m",
	"\e[41m",
	"\e[42m",
	"\e[43m",
	"\e[44m",
	"\e[45m",
	"\e[46m",
	"\e[47m"
};


void render(ostream& out, QImage& img, int* indexs) {
	for (int y = 0; y < img.height()/2; ++y) {
		for (int x = 0; x < img.width(); ++x) {
			int c1 = indexs[img.pixelIndex(x,2 * y)];
			int c2 = indexs[img.pixelIndex(x,2 * y + 1)];
			if (c1 == c2)
				out << P2A_COLORS[c1] << "█";
			else 
				out << P2A_COLORS[c1 + 8]  << P2A_COLORS[c2] << "▄";
		}
		out << "\e[0m" << endl;
	}
}

int main(int argc,const  char** argv) {
	int indexInputName = 1;
	const char* OutputName = NULL;
	if(argc <= 1) {
		cout 
		<< "pix2ascii [-o OUTFILE] FILE COLOR..." << endl
		<< "COLOR:" << endl
		<< "\t0 = black"   << endl
		<< "\t1 = red"     << endl
		<< "\t2 = green"   << endl
		<< "\t3 = yellow"  << endl
		<< "\t4 = blue"    << endl
		<< "\t5 = magenta" << endl
		<< "\t6 = cyan"    << endl
		<< "\t7 = white"   << endl
		<< "EXAMPLE:" << endl
		<< "\tpix2ascii -o out.ascii in.png 7 5 0" << endl
		<< "First color will be changed to white, second to magenta and third to black." << endl;
		return 0;
	}
	if (!strcmp(argv[1],"-o")) {
		OutputName = argv[2];
		indexInputName = 3;
	}
	QImage img(argv[indexInputName++]);
	img = img.convertToFormat(QImage::Format_Indexed8);
	int* indexs = new int[argc - indexInputName];
	for (int i = 0; i < argc - indexInputName; ++i) {
		int index = atoi(argv[i + indexInputName]);
		indexs[i] = index;
	}
	if (OutputName) {
		ofstream out(OutputName);
		out << "#!/bin/bash" << endl << "echo -en \"";
		render(out,img,indexs);
		out << '"';
		out.close();
	} else { 
		render(cout,img,indexs);
	}
	return 0;
}
