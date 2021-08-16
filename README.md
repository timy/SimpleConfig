SimpleConfig is an easy-to-use utility managing the configuration file of line-based text format. Each line in the file allows holding different types of variables, open to extension to adapt to your own specification.

The core functionality is encapsulated in class `CfgFileItems` implemented in a single header file `SimpleConfig.h`.
- `CfgFileItems::add` essentially "binds" a line in the configuration file to a variable of any type (2 arguments), a comment (1 argument), or a blank line (no argument), or vice versa.
- `CfgFileItems::read` loads variable(s) from the file; `CfgFileItems::write` dumps variable(s) to the file.

We now show how to use it. Firstly, we add variables by calling function `add`, establishing a one-to-one relation inside class `CfgFileItems`,
```cpp
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
```
Then we dump the variables into a file,
```cpp
	std::string filename = "config.ini";
	std::ofstream fw(filename);
	items.write(fw);
	fw.close();
```
We check the generated .ini file (or whatever extension you call it). The configuration file is exactly as we expected,
```ini
# You may modify the value of variables, but don't touch anything else.

[Process]
fileName = /my/wonder/land

IP_Address = 10.2.2.191
port = 8080
```
Reversely, we read the configuration file and all data can be correctly filled.
```cpp
	std::ifstream fr(filename);
	items.read(fr);
	fr.close();
```
So far, the variable to export or import is a single one of a primitive type, like `int`, `double`, a single word of `string`. But it is really easy to extend for variables of more complicated types, like arrays, customerized struct or class. Assuming we have a variable of type `YourOwnStruct`, we only need to provide a class `CFG_TYPE_YOU_WISH` derived from `CFG_TYPE_ABSTRACT`, overriding the `write` and `read` functions to write/read concrete data as you wish, then we register this type in the `CfgFileItems::add` like
```cpp
	void add(std::string key, YourOwnStruct& value) {
		lines.push_back(new CFG_TYPE_YOU_WISH(key, value));
	}
```
In this way, we can write multiple data in a single line for arbitrary type. The extension is pretty straightforward!
