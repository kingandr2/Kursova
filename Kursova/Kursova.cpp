// Kursova.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "FileManager.cpp"
#include "Counters.cpp"
#include <locale>

using namespace std;

string getFileName(bool isRead) {
	if (isRead) return "empty example.txt";
	else return "result.txt";
	/*string fileName;
	cout << "Enter the file name:" << endl;
	getline(cin, fileName);
	return fileName;*/
}

int main()
{
	setlocale(LC_ALL, "Russian");

	//cout << locale().name();
	string readFileName = getFileName(true);
	string writeFileName = getFileName(false);
	FileManager* manager = nullptr;
	wstring read;
	while (true) {
		try {
			manager = new FileManager(readFileName, writeFileName);
			read = manager->read();
			if (read.empty()) {
				cout << "Entered file is empty. Try again:" << endl;
				getline(cin, readFileName);
				continue;
			}
			else break;
		}
		catch (FileInvalidException e) {
			cout << "Invalid file. Try again:" << endl;
			getline(cin, readFileName);
			continue;
		}

	}
	try {
		while (manager->available()) {
			read = manager->read();
		}
	}
	catch (exception e) { cout << "There was an exception when reading the file. It may have not been analysed fully." << endl; }
	wprintf(L"Це було прочитано: ");
	wcout << endl << read << endl;
	manager->write(read);

	cout << "Processing information..." << endl;
	CountVoiceless count1 = CountVoiceless();
	CountVoiced count2 = CountVoiced();
	//CountVoiceless count3 = CountVoiceless();
	//CountLowercase count4 = CountLowercase();
	try {
		cout << "Amount of words starting with voiceless letters: " << count1.count(read) << endl;
		cout << "Amount of words starting with voiced letters: " << count2.count(read) << endl;
		//cout << "Amount of words starting with uppercase letter: " << count3.count(read) << endl;
		//cout << "Amount of words starting with lowercase letter: " << count4.count(read) << endl;
	}
	catch (UnsupportedCharacterException e) { cout << "Unsupported character detected." << endl; }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
