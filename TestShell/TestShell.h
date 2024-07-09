#pragma once
#include <string>

using namespace std;

class TestShell {
public:
	void run(void);
	void execute(string cmd);
	virtual bool write(string cmd);
	virtual bool read(string cmd);
	bool exit(void);
	bool help(void);
	bool fullWrite(string cmd);
	bool fullRead(void);
private:
	bool isValidCommand(string cmd);
};