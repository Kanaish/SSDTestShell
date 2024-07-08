#include <fstream>
#include   "iFileManager.h"
#include <iostream>
class SSDWriter {

public :
	SSDWriter(FileManager* fm) :fm{ fm } {
		fm->init();
	}
	void writer(int index, unsigned int value) {



	}
private : 
	FileManager *fm;
	std::fstream file;


};