#include <string>
#include <iostream>

using namespace std;

class UnsupportedCharacterException : exception {
public: 
	UnsupportedCharacterException() : exception(/*"Unsupported characted found in line"*/) {

	}
};

    class Counter {
    	public:
    		virtual int count(string str) { return 0; }
    };

class CountVoiceless : Counter {
	private:
	    string voiceless = "птсцшчхкфПТСЦШЧХКФ";
	public:
		int count(string str) {
		    string str2 = str;
			int counter = 0;
			for (int i = 0; i < voiceless.length() - 1; i += 2){
			    if (str2[0] == voiceless[i] && str2[1] == voiceless[i + 1]){
			        counter++;
			        break;
			    }
			}
			for (int i = str2.find(' '); i != -1 && i < str2.length() - 2; i = str2.find(' ')) {
				for (int j = 0; j < voiceless.length() - 1; j += 2) {
				    if (voiceless[j] == str2[i + 1] && voiceless[j + 1] == str2[i + 2]){ 
				        counter++;
				        break;
				    }
			    }
				str2 = str2.substr(i + 1, str2.length());
			}
			return counter;
		}
};

class CountVoiced: Counter {
	private:
		string voiced = "бдзжгґБДЗЖГҐ";
	public:
		int count(string str) {
		    string str2 = str;
			int counter = 0;
			for (int i = 0; i < voiced.length() - 1; i += 2){
			    if (str2[0] == voiced[i] && str2[1] == voiced[i + 1]){
			        counter++;
			        break;
			    }
			}
			for (int i = str2.find(' '); i != -1 && i < str2.length() - 2; i = str2.find(' ')) {
				for (int j = 0; j < voiced.length() - 1; j += 2) {
				    if (voiced[j] == str2[i + 1] && voiced[j + 1] == str2[i + 2]){ 
				        counter++;
				        break;
				    }
			    }
				str2 = str2.substr(i + 1, str2.length());
			}
			return counter;
		}
};

class CountSoft : Counter {
	private:
		string soft = "дтлнрзцсДТЛНРЗЦС";
		string softener = "єїюяіьІЄЮЇЯЬ";
	public:
		int count(string str) {
			int counter = 0;
			string str2 = str;
			for (int i = 0; i < soft.length() - 1; i += 2){
			    if (str2[0] == soft[i] && str2[1] == soft[i + 1]){
			        for (int j = 0; j < softener.length(); j++){
			            if (str2[2] == softener[j] && str[3] == softener[j + 1]){
			                counter++;
			                break;
			            }
			        }
			    }
			}
			for (int i = str2.find(' '); i != -1 && i < str2.length() - 4; i = str2.find(' ')) {
				for (int j = 0; j < soft.length() - 1; j += 2) {
				    if (soft[j] == str2[i + 1] && soft[j + 1] == str2[i + 2]){
				        for (int k = 0; k < softener.length() - 1; k += 2){
				            if (softener[k] == str2[i + 2] && softener[k + 1] == str2[i + 3]){
				                counter++;
				                break;
				            }
				        }
				    }
			    }
				str2 = str2.substr(i + 1, str2.length());
			}
			return counter;
		}
};

class CountHard : Counter {
	private:
		string hard = "дтлнрзцсДТЛНРЗЦС";
	public:
		int count(string str) {
			int counter = 0;
			string str2 = str;
			for (int i = 0; i < hard.length() - 1; i += 2){
			    if (str2[0] == hard[i] && str2[1] == hard[i + 1]){
			        counter++;
			        break;
			    }
			}
			for (int i = str2.find(' '); i != -1 && i < str2.length() - 2; i = str2.find(' ')) {
				for (int j = 0; j < hard.length() - 1; j += 2) {
				    if (hard[j] == str2[i + 1] && hard[j + 1] == str2[i + 2]){ 
				        counter++;
				        break;
				    }
			    }
				str2 = str2.substr(i + 1, str2.length());
			}
			return counter;
		}
};
