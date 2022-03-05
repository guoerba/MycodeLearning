#pragma once



#define BUFFERSIZE		256

struct ICDData {
	std::string code;
	std::string description;
	std::string etc;
	ICDData *next;
};

class ICDHandler
{
public:
	typedef enum SearchType {
		code,
		description
	};

	ICDHandler(const char *filename,int Mode);
	~ICDHandler();
	void Read();//输出到屏幕
	void Search(const char *str,SearchType st = SearchType::code);//输出到屏幕	
private:
	void queryRow(ICDData *icd);//解析一行数据，并返回相应字段，该函数只负责解析，不负责创建数据结构，它默认icd在内存中已经存在
	int clearBuffer();

	int createDatabase();
	int deleteDatabase();
	void queryDatabase();

	std::vector<ICDData*> SearchICDCode(const char * icdcode);
	std::vector<ICDData*> SearchICDContent(const char *content);

	char *buffer;
	std::fstream *File;
	ICDData *head;
};

