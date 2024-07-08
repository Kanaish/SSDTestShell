#pragma once
#include <string>

using namespace std;

class TestShell {
public:
	void execute(string smd);
	bool write(string cmd);
	bool read(string cmd);
	bool exit(void);
	bool help(void);
	bool fullwrite(string cmd);
	bool fullread(void);
private:
	bool isValidCommand(string cmd);
};