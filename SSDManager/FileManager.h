#pragma once
#include <iostream>
#include <fstream>

class FileManager
{
public:
	FileManager();
	std::fstream* open(std::string);
	bool write(std::fstream* fs, int index, unsigned int value);
	bool write(std::fstream* fs, unsigned int value);
	bool close(std::fstream* fs);
};