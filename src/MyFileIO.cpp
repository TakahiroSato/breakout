#include "MyFileIO.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;


cMyFileIO::cMyFileIO(){

}

cMyFileIO::~cMyFileIO(){

}


/*
	�t�@�C���ǂݍ��݊֐�
	FileName	= �ǂݍ��݂����t�@�C���̃p�X
	buf			= �ǂݍ��񂾃f�[�^���i�[����o�b�t�@
	size_t		= �o�b�t�@�̃T�C�Y
	�߂�l		= true �ǂݍ��ݐ����@false �ǂݍ��ݎ��s
*/
bool cMyFileIO::MyLoadFile(char *FileName , char *buf , size_t size){

	ifstream fin(FileName);

	if(!fin){
		cout << "���̓t�@�C�����J���܂���\n";
		return false;
	}

	for( unsigned i = 0 ; i < size ; i++ ){
		fin >> *(buf+i);
		if( fin.eof() ) break;
	}

	fin.close();

	return true;
}


int cMyFileIO::GetIntInText(char* fileName, char* numName){

	ifstream fin(fileName);

	if(!fin){
		cout << "���̓t�@�C�����J���܂���\n";
		return 0;
	}

	char buf[256] = "";
	string str;
	unsigned i = 0;

	while(!fin.eof()){
		fin.getline(buf, 256);
		str = buf;
		ZeroMemory(buf, sizeof(char)*256);
		if(str.find(numName) != string::npos){
			for( i = str.find_first_of("0123456789") ; i < str.length() ; i++){
				buf[i-str.find_first_of("0123456789")] = str[i];
			}
			return atoi(buf);
		}
	}
	return 0;
}

double cMyFileIO::GetDoubleInText(char* fileName, char* numName){
	
	ifstream fin(fileName);

	if(!fin){
		cout << "���̓t�@�C�����J���܂���\n";
		return 0.0;
	}

	char buf[256] = "";
	string str;
	unsigned i = 0;

	while(!fin.eof()){
		fin.getline(buf, 256);
		str = buf;
		ZeroMemory(buf, sizeof(char)*256);
		if(str.find(numName) != string::npos){
			for( i = str.find_first_of("0123456789") ; i < str.length() ; i++){
				buf[i-str.find_first_of("0123456789")] = str[i];
			}
			return atof(buf);
		}
	}
	return 0.0;
}

string cMyFileIO::GetTextInText(char* fileName, char* textName){

	ifstream fin(fileName);

	if(!fin){
		cout << "���̓t�@�C�����J���܂���\n";
		return 0;
	}

	char buf[256] = "";
	string str;
	unsigned i = 0;

	while(!fin.eof()){
		fin.getline(buf, 256);
		str = buf;
		ZeroMemory(buf, sizeof(char)*256);

		if(str.find(textName) != string::npos){
			for( i = str.find_first_of("=")+1 ; i < str.length() ; i++){
				buf[i-(str.find_first_of("=")+1)] = str[i];
			}
			str = buf;
			return str;
		}
	}

	return 0;
}

void cMyFileIO::ReadCsv(const char* fileName, unsigned char* buf, unsigned size){

	char tmp_buf[256] = {0};
	unsigned i = 0;
	string str;

	ifstream fin(fileName);
	ofstream fout("tmp");

	if(!fin){
		cout << "�t�@�C�����J���܂���ł���\n";
		return;
	}

	if(!fout){
		cout << "�t�@�C�����J���܂���ł���\n";
		return;
	}

	while(!fin.eof()){
		fin.getline(tmp_buf, 256);
		str = tmp_buf;
		fout << str << ',';
	}

	fin.close();
	fout.close();
	fin.open("tmp");

	if(!fin){
		cout << "�t�@�C�����J���܂���ł���2\n";
		return;
	}

	while(!fin.eof()){
		fin.getline(tmp_buf, 256, ',');
		str = tmp_buf;

		*(buf+i) = atoi(str.c_str());
		i++;
		if(i >= size) break;
	}

	fin.close();
}