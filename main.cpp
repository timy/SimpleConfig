#include "SimpleConfig.h"

using std::cout;
using std::endl;

// a simple test case

int main(int argc, char* argv[]) {

	std::string fileName = "/my/wonder/land";
	std::string IP_address = "10.2.2.191";
	unsigned int port = 8080;

	CfgFileItems items;
	items.add("# You may modify the value of variables, "
		"but don't touch anything else."); // a comment
	items.add();                           // a blank line
	items.add("[Process]");                // a comment
	items.add("fileName", fileName);       // a variable of string
	items.add();                           // a blank line
	items.add("IP_Address", IP_address);   // a variable of string
	items.add("port", port);               // a variable of unsigned int

	std::string filename = "config.ini";

	std::ofstream fw(filename);
	items.write(fw);
	fw.close();

	std::ifstream fr(filename);
	items.read(fr);
	fr.close();

	cout << "Variables read from configuration file \"" << filename << "\":" << endl;
	cout << "fileName:   " << fileName << endl;
	cout << "IP_address: " << IP_address << endl;
	cout << "port:       " << port << endl;

	return 0;
}