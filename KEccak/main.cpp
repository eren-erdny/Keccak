#include "keccak.h"
#include <fstream>
#include "windows.h"
#include <iostream>
#include <map>
#include <cassert>

int HEX_TO_DEC(std::string&, int);
std::string func(std::string);
void addElem(Keccak, std::string s, std::map<std::string, int>&);

int main(int argc, char* argv[]){
#define BLOCK512 64
	setlocale(0, "");
	WIN32_FIND_DATAA f;
	HANDLE h = FindFirstFile("../*", &f);
	if (h != INVALID_HANDLE_VALUE)
	{
		do
		{
			puts(f.cFileName);
		} while (FindNextFile(h, &f));
	}
	else
	{
		fprintf(stderr, "Error opening directory\n");
	}
	Keccak keccak;
	std::string msg = argv[1];
	std::map <std::string, int> m;
	std::string result = func(msg);
	std::cout << result << std::endl;
	addElem(keccak, result, m);
	auto it = m.begin();
	for (int i = 0; it != m.end(); it++, i++) { 
		std::cout << i << ") Ключ " << it->first << ", значение " << it->second << std::endl;
	}
	return 0;
}

std::string func(std::string s){

	std::ifstream fin(s);
	char line[1000];
	if (!fin.is_open()){
		std::cout << "\nFile " << s << " can't be open \n";
	}
	else{
			fin.getline(line, sizeof(line));
		fin.close();
	}
	return line;
}

int HEX_TO_DEC(std::string & st, int len){
	int i, k = 0, p;
	long long int s = 0;
	p = st.length() - 1;
	int tmp = 0;
	for (int i = 0; i < 2; i++)
	{

		switch (toupper(st[p - i]))
		{
		case 'A': k = 10; break;
		case 'B': k = 11; break;
		case 'C': k = 12; break;
		case 'D': k = 13; break;
		case 'E': k = 14; break;
		case 'F': k = 15; break;
		case '1': k = 1; break;
		case '2': k = 2; break;
		case '3': k = 3; break;
		case '4': k = 4; break;
		case '5': k = 5; break;
		case '6': k = 6; break;
		case '7': k = 7; break;
		case '8': k = 8; break;
		case '9': k = 9; break;
		case '0': k = 0; break;
		default:
			;
		}
		tmp = pow(16, i);
		s += k * tmp;
	}
	return s;
}

void addElem(Keccak keccak, std::string s, std::map<std::string, int> &m) {
	std::string result = keccak(s);
	int len = result.length();
	m[s] = HEX_TO_DEC(result, len);
}

