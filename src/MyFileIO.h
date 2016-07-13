#ifndef		__MYFILEIO_H__
#define		__MYFILEIO_H__

#include<string>


class cMyFileIO{

private:
public:
	cMyFileIO();
	~cMyFileIO();

	static bool MyLoadFile(char * , char * , size_t);
	static int GetIntInText(char* fileName, char* numName);
	static double GetDoubleInText(char* fineName, char* numName);
	static std::string GetTextInText(char* fileName, char* textName);
	static void ReadCsv(const char* fileName, unsigned char* buf, unsigned size);
};

#endif		__MYFILEIO_H__