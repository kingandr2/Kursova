#include <iostream>
#include <string>
#include "FileManager.cpp"
#include "Counters.cpp"
#include <locale>
#include <algorithm>

using namespace std;


int main()
{
	setlocale(LC_ALL, "ukrainian");
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