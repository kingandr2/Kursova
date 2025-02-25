#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class FileInvalidException : public exception {
public:
	FileInvalidException(): exception("Invalid file") {}
};

class FileManager {
	private:
		wofstream writer;
		wifstream reader;
		~FileManager() {
			writer.close();
			reader.close();
			delete& writer;
			delete& reader;
		}
	public:
		FileManager(string readFile, string writeFile) {
			//writer = ofstream(fileName);
			//reader = ifstream(fileName);
			//if (!writer.is_open() || !reader.is_open()) {
			//	throw FileInvalidException();// "Invalid file";
			//}
			/*locale utf8_locale(locale(), new locale->codecvt_utf8<char>());
				fstreambuf_iterator<char>());*/
			//file = wfstream();
			//file.open(fileName/*, ios::binary*/);
			//locale utf8_locale = utf8(locale(), new codecvt_utf8<wchar_t>());
			//file.imbue(locale("uk-UA.UTF-8"));
			//file.imbue(utf8_locale);
			reader = wifstream(readFile);
			writer = wofstream(writeFile, ios::in);
			if (reader.fail() || writer.fail()) throw FileInvalidException();
		}
		
		void newFile(string readFile, string writeFile) {
			if (!readFile.empty()) {
				reader.close();
				reader.open(readFile);
			}
			if (!writeFile.empty()) {
				writer.close();
				writer.open(writeFile);
			}
		}
		bool available() {
			return !reader.eof();
		}
		wstring read() {
			/*file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
			std::wstringstream wss;
			wss << wif.rdbuf();
			return wss.str();*/
			/*if (s.length() < 10)
				s.resize(10);
			reader.read(&(s[0]), 1);*/
			wstring s = L"Placeholder";
			for (int i = 0; !reader.eof(); i++) {
				s.resize(s.length() + 1);
				reader.read(&(s[i]), 1);
			}
			return s;
		}
		void write(wstring w) {
			writer.write(w.c_str(), w.length());
		}
};

