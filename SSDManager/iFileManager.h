#ifndef IFILEMANAGER_H
#define IFILEMANAGER_H

#include<fstream> 
using namespace std; 

class   FileManager {
public : 
	virtual bool write(fstream* fs, int index, unsigned int  value) = 0;
	virtual bool init() = 0;
	virtual bool close(fstream* fs) = 0;

};

#endif