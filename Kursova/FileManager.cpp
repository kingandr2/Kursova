#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class FileInvalidException : public exception {
public:
	FileInvalidException(): exception() {}
};

class FileManager {
	private:
		fstream file;
		string writeFile;
		~FileManager() {
		    file.close();
		    delete &file;
		}
	public:
		FileManager(string readFile, string writeFile) {
		    file = fstream(writeFile);
		    if (file.fail()) throw FileInvalidException();
		    else this->writeFile = writeFile;
			file = fstream(readFile);
			if (file.fail()) throw FileInvalidException();
		}
		string read() {
			string result = "";
			getline(file, result);
			string line = "";
            while(!file.eof()){
                getline(file, line);
                result += " " + line;
            }
            return result;
		}
		void write(string line) {
		    file.close();
		    file.open(writeFile, ios::app);
			file.write(&(line[0]), line.length());
			file.put('\n');
			file.flush();
		}
};