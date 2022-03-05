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
	void Read();//�������Ļ
	void Search(const char *str,SearchType st = SearchType::code);//�������Ļ	
private:
	void queryRow(ICDData *icd);//����һ�����ݣ���������Ӧ�ֶΣ��ú���ֻ��������������𴴽����ݽṹ����Ĭ��icd���ڴ����Ѿ�����
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

