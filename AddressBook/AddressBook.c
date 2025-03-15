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
	USERDATA* pTemp = g_Head.pNext;

	while (pTemp != NULL)
	{
		if (strcmp(pTemp->szName, pszName) == 0)
		{
			return pTemp;
		}

		pTemp = pTemp->pNext;
	}

	return NULL;
}

int AddNewNode(char* pszName, char* pszPhone)
{
	// 이미 같은 이름이 존재할 경우 추가할 수 없다.
	if (FindNode(pszName) != NULL)
	{
		return 0;
	}

	USERDATA* pNewUser = (USERDATA*)malloc(sizeof(USERDATA));
	if (pNewUser == NULL)
	{
		puts("ERROR: 메모리 할당 실패");
		return 0;
	}

	memset(pNewUser, 0, sizeof(USERDATA));

	sprintf_s(pNewUser->szName, sizeof(pNewUser->szName), "%s", pszName);
	sprintf_s(pNewUser->szPhone, sizeof(pNewUser->szPhone), "%s", pszPhone);
	pNewUser->pNext = g_Head.pNext;
	g_Head.pNext = pNewUser;

	return 1;
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

/// <summary>
/// 이름을 기준으로 특정 노드를 검색한다.
/// </summary>
void Search()
{
	char szName[32] = { 0 };

	printf("Please input name: ");
	fflush(stdin);
	rewind(stdin);
	gets_s(szName, sizeof(szName));

	USERDATA* pFound = FindNode(szName);
	if (pFound != NULL)
	{
		printf
		(
			"[%p] %s\t%s [%p]\n",
			pFound,
			pFound->szName,
			pFound->szPhone,
			pFound->pNext
		);
	}
	else
	{
		puts("ERROR: 데이터를 찾을 수 없습니다.");
	}

	_getch();
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
	puts("[1] Add");
	puts("[2] Search");
	puts("[3] Print all");
	puts("[4] Remove");
	puts("[0] Exit");

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