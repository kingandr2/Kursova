#include <iostream>
#include <string>
#include "FileManager.cpp"
#include "Counters.cpp"
#include <locale>
#include <codecvt>
#include <algorithm>
#include <unordered_set>
#include <regex>
using namespace std;

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
	string read2 = read; // Конвертуємо в wstring
	string error = ""; // Збереження помилок
	//wstring abetka = L"абвгґдеєжзиіїйклмнопрстуфхцчьюяАБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧЬЮЯ";
	wstring abetka_w = L"абвгґдеєжзиіїйклмнопрстуфхцчьюяАБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧЬЮЯ";
	std::unordered_set<wchar_t> abetka(abetka_w.begin(), abetka_w.end());
	bool isWrong = true;
	regex ukr_regex("^[абвгґдеєжзиіїйклмнопрстуфхцчшщьюяАБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ’`\',\\. ]+");
	// Перевірка символів
	for (int i = 0; i != -1 && i < read2.length() - 1; i = read2.find(' ')) {
		string line = read2.substr(i + 1, read2.find(' ', i + 1) - 1);
		if (i + 1 > read2.length() || read2.find(' ', i + 1) == -1) {
			read2 = read2.substr(1, read2.length());
		}
		else
			read2 = read2.substr(read2.find(' ', i + 1), read2.length() - 1);
		if (!regex_match(line, ukr_regex) && line != "")
			error += "Помилка у рядку \"" + line + "\". Невідомий символ.\n";
	}
	cout << error << endl;
	manager->write(error);
	CountVoiceless count1 = CountVoiceless();
	CountVoiced count2 = CountVoiced();
	CountSoft count3 = CountSoft();
	CountHard count4 = CountHard();
	cout << "Прочитано з файлу: " << endl << read << endl;
	/*for (char a : read){
		manager->write();
	}*/
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