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
	ファイル読み込み関数
	FileName	= 読み込みたいファイルのパス
	buf			= 読み込んだデータを格納するバッファ
	size_t		= バッファのサイズ
	戻り値		= true 読み込み成功　false 読み込み失敗
*/
bool cMyFileIO::MyLoadFile(char *FileName , char *buf , size_t size){

	ifstream fin(FileName);

	if(!fin){
		cout << "入力ファイルが開けません\n";
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
		cout << "入力ファイルが開けません\n";
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
		cout << "入力ファイルが開けません\n";
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
		cout << "入力ファイルが開けません\n";
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
		cout << "ファイルが開けませんでした\n";
		return;
	}

	if(!fout){
		cout << "ファイルが開けませんでした\n";
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
		cout << "ファイルが開けませんでした2\n";
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