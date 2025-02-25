#include <iostream>
#include <string>
#include "FileManager.cpp"
#include "Counters.cpp"
#include <locale>
#include <algorithm>
#include <codecvt>

using namespace std;

bool isMultiByte(char c) {
	if ((c & 0x80) == 0) return 1;   // ASCII (1 байт)
	if ((c & 0xE0) == 0xC0) return 2; // 110xxxxx → 2 байти (кирилиця)
	if ((c & 0xF0) == 0xE0) return 3; // 1110xxxx → 3 байти
	if ((c & 0xF8) == 0xF0) return 4; // 11110xxx → 4 байти
	return -1;  // Некоректний UTF-8 символ
}
std::wstring utf8_to_wstring(const std::string& str) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.from_bytes(str);
}

// Функція для конвертації std::wstring у std::string (UTF-8)
std::string wstring_to_utf8(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.to_bytes(wstr);
}
int main()
{
	system("chcp 65001");
	setlocale(0, "ua_UA.UTF-8");
    string readFile, writeFile;
    cout << "Введіть файл з даними:" << endl;
    cin >> readFile;
    cout << "Введіть файл для результатів:" << endl;
    cin >> writeFile;
	FileManager *manager = nullptr;
	string read;
	while (true) {
	    if (!(readFile.compare(readFile.length() - 4, 4, ".txt") == 0) || !(writeFile.compare(writeFile.length() - 4, 4, ".txt") == 0)){
	        cout << "Файл не є текстовим. Спробуйте ще раз: " << endl;
	        cin >> readFile;
	        cin >> writeFile;
	        continue;
	    }
		try {
			manager = new FileManager(readFile, writeFile);
			read = manager->read();
			if (read.empty()) {
				cout << "Введений файл пустий. Спробуйте ще раз:" << endl;
                cin >> readFile;
				continue;
			}
			else break;
		}
		catch (FileInvalidException e) {
			cout << "Недійсний файл. Спробуйте ще раз:" << endl;
			cin >> readFile;
			cin >> writeFile;
			continue;
		}
	}
    
	CountVoiceless count1 = CountVoiceless();
	CountVoiced count2 = CountVoiced();
	CountSoft count3 = CountSoft();
	CountHard count4 = CountHard();
	cout << "Прочитано з файлу: " << endl << read << endl;
	/*for (char a : read){
		manager->write();
	}*/
	string read2 = read;
	string error = "";
	string abetka = " абвгґдеєжзиіїйклмнопрстуфхцчьюяАБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧЬЮЯ";
	bool isWrong = true;
	cout << abetka.length() << endl << read2.length();

	for (int i = 0; i < read2.length() - 1; i++) {
		if (isMultiByte(read2[i]) == 2) {
			for (int j = 0; j < abetka.length() - 1; j ++/*= 2*/) {
				if (j == 66) string p = read2.substr(j - 2, j + 2);
				if (read2.substr(i, isMultiByte(read2[i])) == abetka.substr(j, isMultiByte(abetka[j]))/*read2[i] == abetka[j] && read2[i + 1] == abetka[j + 1]*/) {
					isWrong = false;
					break;
				}
				//cout << j << "end" << i << endl;
			}
			i++;
		}
		if (isMultiByte(read2[i]) == 3) {
			for (int j = 0; j < abetka.length() - 1; j += 2) {
				if (j == 66) string p = read2.substr(j - 2, j + 2);
				if (read2[i] == abetka[j] && read2[i + 1] == abetka[j + 1]) {
					isWrong = false;
					break;
				}
				//cout << j << "end" << i << endl;
			}
			i += 2;
		}
		//cout << "END" << endl;
		if (isWrong) {
			error += "Помилка в " + read2.substr(i, read2.find(' ', i)) + ". Недійсний символ." + '\n';
			//i = read2.find(' ', i);
		}
		isWrong = true;
	}
	cout << error << endl;
	manager->write(error);

	string voiceless = "Кількість слів, що починаються з глухих голосних літер: ";
	string voiced = "Кількість слів, що починаються з дзвінких голосних літер: ";
	string soft = "Кількість слів, що починаються з м'яких приголосних літер: ";
	string hard = "Кількість слів, що починаються з твердих приголосних літер: ";
	voiceless.append(to_string(count1.count(read)));
	voiced.append(to_string(count2.count(read)));
	soft.append(to_string(count3.count(read)));
	hard.append(to_string(count4.count(read)));
	cout << voiceless << endl;
	cout << voiced << endl;
	cout << soft << endl;
	cout << hard << endl;
	manager->write(voiceless);
	manager->write(voiced);
	manager->write(soft);
	manager->write(hard);
}