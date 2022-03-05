#include "pch.h"
#include "ICDHandler.h"

ICDHandler::ICDHandler(const char *filename, int Mode):
	head(NULL)
{
	buffer = new char[BUFFERSIZE];
	for (int i = 0; i < BUFFERSIZE; i++)
		buffer[i] = 0;
	
	File = new std::fstream(filename, Mode);
	if (!File->is_open())
	{
		std::cerr << "file open is failed!" << std::endl;	
	}
	createDatabase();
}

ICDHandler::~ICDHandler()
{
	File->close();
	delete File;
	File = NULL;

	delete[] buffer;
	buffer = NULL;

	deleteDatabase();
}

void ICDHandler::Read()
{
	queryDatabase();
}

void ICDHandler::queryRow(ICDData *icd)
{
	int section = 0,i = 0,j = 0;
	char temp[BUFFERSIZE] = { 0 };
	while (buffer[i])
	{
		if ( buffer[i] == ';')
		{
			//std::cout << temp << std::endl;
			switch (section++)
			{
			case 0:icd->code.append(temp); break;
			case 1:icd->description.append(temp); break;
			default:icd->etc.append(temp);
			}		
			j = 0;
		}
		else
		{ 			
			temp[j++] = buffer[i];
		}			
		i++;
	}
}

int ICDHandler::createDatabase()
{
	int i = 0;
	ICDData *node = NULL;
	while (!File->eof())
	{
		clearBuffer();
		File->getline(buffer, BUFFERSIZE);
				
		if (0 == i++)
		{
			head = new ICDData;
			node = head;
			queryRow(head);			
		}			
		else
		{				
			ICDData *nnode = new ICDData;		
			nnode->next = NULL;
			queryRow(nnode);
			node->next = nnode;
			node = nnode;
		}
	}
	return 0;
}

int ICDHandler::deleteDatabase()
{
	if (!head)
		return -1;
	ICDData *node = head,*del = NULL;
	while (node)
	{
		node->code.clear();
		node->description.clear();
		node->etc.clear();
		del = node;
		node = node->next;
		delete del;		
	}
	node = NULL;
	return 0;
}

void ICDHandler::queryDatabase()
{
	ICDData *node = head;
	while (node)
	{
		std::cout << node->code << ':' << node->description << std::endl;
		node = node->next;
	}
}

int ICDHandler::clearBuffer()
{
	if (!buffer)
		return -1;
	for (int i = 0; i < BUFFERSIZE; i++)
		buffer[i] = 0;
	return 0;
}

std::vector<ICDData*> ICDHandler::SearchICDCode(const char *icdcode)
{
	std::vector<ICDData *> list;
	ICDData *node = head;
	while (node)
	{
		if (node->code.find(icdcode) != -1)
			list.push_back(node);
		node = node->next;
	}
	return list;
}

std::vector<ICDData*> ICDHandler::SearchICDContent(const char *content)
{	
	char copy[256] = {0};
	strcpy_s(copy, 256, content);
	if (copy[0] > 96 && copy[0] < 123)//Ê××ÖÄ¸Ð¡Ð´	
		copy[0] -= 32;
	else if (copy[0] > 64 && copy[0] < 91)
		copy[0] += 32;	

	std::vector<ICDData*> list;
	ICDData *node = head;	
	
	while (node)
	{
		if (node->description.find(content) != -1)
			list.push_back(node);
		if (node->description.find(copy) != -1)
			list.push_back(node);
		node = node->next;
	}
	
	return list;
}

void ICDHandler::Search(const char *str, SearchType st)
{
	//ICDData *result = (st == SearchType::code) ? SearchICDCode(str) : SearchICDContent(str);
	//!result ? std::cout << "no data find!" << std::endl : std::cout << result->code << ":" << result->description << std::endl;
	std::vector<ICDData*> results;
	if (st == SearchType::code)	
		results = SearchICDCode(str);			
	else	
		results = SearchICDContent(str);	
	int s = results.size();
	for (int i = 0; i < s; i++)	
		std::cout << results[i]->code << ":" << results[i]->description << std::endl;	
	std::cout << results.size() << " entries found\n\n\n" << std::endl;
	results.clear();
}