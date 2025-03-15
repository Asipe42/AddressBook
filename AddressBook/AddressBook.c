#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE_NAME "Address.dat"

void ReleaseList();

typedef struct _USERDATA
{
	char szName[32];
	char szPhone[32];

	struct _USERDATA* pNext;
} USERDATA;

USERDATA g_Head = { 0 };

USERDATA* FindNode(char* pszName)
{

}

int AddNewNode(char* pszName, char* pszPhone)
{
	
}

/// <summary>
/// 이름과 휴대전화 번호를 입력받아 리스트에 추가한다.
/// </summary>
void Add()
{
	char szName[32] = { 0 };
	char szPhone[32] = { 0 };

	printf("Please input name: ");
	fflush(stdin);
	rewind(stdin);
	gets_s(szName, sizeof(szName));

	printf("Please input phone number: ");
	fflush(stdin);
	rewind(stdin);
	gets_s(szPhone, sizeof(szPhone));

	AddNewNode(szName, szPhone);
}

void Search()
{
	
}

void PrintAll()
{
	
}

int RemoveNode(char* pszName)
{
	
}

void Remove()
{
	
}

int PrintUI()
{
	int nInput = 0;

	system("cls");
	printf("[1] Add\n");
	printf("[2] Search\n");
	printf("[3] Print all\n");
	printf("[4] Remove\n");
	printf("[0] Exit\n");

	scanf_s("%d", &nInput);

	return nInput;
}

int LoadList(char* pszFileName)
{
	
}

int SaveList(char* pszFileName)
{
	
}

void ReleaseList()
{
	
}

void main()
{
	int nMenu = 0;
	LoadList(DATA_FILE_NAME);

	while ((nMenu = PrintUI()) != 0) {
		switch (nMenu)
		{
		case 1:
			Add();
			break;
			
		case 2:
			Search();
			break;

		case 3:
			PrintAll();
			break;

		case 4:
			Remove();
			break;
		}
	}

	SaveList(DATA_FILE_NAME);
	ReleaseList();
}