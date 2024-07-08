#pragma once
#include <string>

using namespace std;

class TestShell {
public:
	void run(void);
	void execute(string smd);
	virtual bool write(string cmd);
	virtual bool read(string cmd);
	virtual bool exit(void);
	virtual bool help(void);
	virtual bool fullwrite(string cmd);
	virtual bool fullread(void);
private:
	bool isValidCommand(string cmd);
};