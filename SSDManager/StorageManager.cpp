#include <string>

class StorageManager {
public:
	virtual void splitBySpace(std::string cmd) = 0;
	virtual bool isValidCommand() = 0;
	//virtual std::string intToHexString(unsigned int value) = 0;
};