#include <string>
#include <iostream>

using namespace std;

class UnsupportedCharacterException : exception {
public: 
	UnsupportedCharacterException() : exception("Unsupported characted found in line") {

	}
};

class Counter {
	protected:
		int counter = 0;
		bool contains(wchar_t set[], int size, char c) {
			for (int i = 0; i < size; i++) {
				if (set[i] == c) return true;
			}
			return false;
		}
	public:
		virtual int count(string str) { return 0; }
};

class CountVoiced : Counter {
	private:
		wchar_t voiced[12] = {'б', 'д', 'ґ', 'г', 'з', 'ж', 'Б', 'Д', 'Ґ', 'Г', 'З', 'Ж'};
		int size = sizeof(voiced) / sizeof(char);
	public:
		int count(wstring str) {
			counter = 0;
			if (contains(voiced, size, str[0])) counter++;
			for (int i = str.find(' '); i != -1 && i < str.length() - 1; i = str.find(' ')) {
				if (contains(voiced, size, str[i + 1])) counter++;
				str = str.substr(i + 1, str.length());
			}
			return counter;
		}
};

class CountVoiceless: Counter {
	private:
		wchar_t voiced[18] = { 'п', 'т', 'к', 'х', 'с', 'ш', 'ч', 'ц', 'ф', 'П', 'Т', 'К', 'Х', 'С', 'Ш', 'Ч', 'Ц', 'Ф'};
		int size = sizeof(voiced) / sizeof(char);
	public:
		int count(wstring str) {
			counter = 0;
			if (contains(voiced, size, str[0])) counter++;
			for (int i = str.find(' '); i != -1 && i < str.length() - 1; i = str.find(' ')) {
				if (contains(voiced, size, str[i + 1])) counter++;
				str = str.substr(i + 1, str.length());
			}
			return counter;
		}
};

//class CountVowels : Counter {
//	public:
//		int count(string str) {
//			counter = 0;
//			//if (valid(str[0])) throw UnsupportedCharacterException();
//			for (int i = str.find(' '); i != -1 && i < str.length() - 1; i = str.find(' ')) {
//				str = str.substr(i + 1, str.length());
//			}
//			return counter;
//		}
//};
//
//class CountLowercase : Counter {
//	public:
//		int count(string str) {
//			counter = 0;
//			for (int i = str.find(' '); i != -1 && i < str.length() - 1; i = str.find(' ')) {
//				str = str.substr(i + 1, str.length());
//			}
//			return counter;
//		}
//};
