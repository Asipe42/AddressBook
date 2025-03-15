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
	USERDATA* pTmp = g_Head.pNext;
	while (pTmp != NULL) {
		if (strcmp(pTmp->szName, pszName) == 0)
			return pTmp;

		pTmp = pTmp->pNext;
	}

	return NULL;
}

int AddNewNode(char* pszName, char* pszPhone)
{
	USERDATA* pNewUser = NULL;

	if (FindNode(pszName) != NULL)
	{
		return 0;
	}

	pNewUser = (USERDATA*)malloc(sizeof(USERDATA));
	memset(pNewUser, 0, sizeof(USERDATA));

	sprintf_s(pNewUser->szName, sizeof(pNewUser->szName), "%s", pszName);
	sprintf_s(pNewUser->szPhone, sizeof(pNewUser->szPhone), "%s", pszPhone);
	pNewUser->pNext = NULL;

	pNewUser->pNext = g_Head.pNext;
	g_Head.pNext = pNewUser;

	return 1;
}

void Add()
{
	char szName[32] = { 0 };
	char szPhone[32] = { 0 };

	printf("Input name : ");
	fflush(stdin);
	gets_s(szName, sizeof(szName));

	printf("Input phone number : ");
	fflush(stdin);
	gets_s(szPhone, sizeof(szPhone));

	AddNewNode(szName, szPhone);
}

void Search()
{
	char szName[32] = { 0 };
	USERDATA* pNode = NULL;

	printf("Input name : ");
	fflush(stdin);
	gets_s(szName, sizeof(szName));

	pNode = FindNode(szName);
	if (pNode != NULL) {
		printf("[%p] %s\t%s [%p]\n",
			pNode,
			pNode->szName, pNode->szPhone,
			pNode->pNext);
	}

	else {
		puts("ERROR: 데이터를 찾을 수 없습니다.");
	}

	_getch();
}

void PrintAll()
{
	USERDATA* pTmp = g_Head.pNext;
	while (pTmp != NULL) {
		printf("[%p] %s\t%s [%p]\n",
			pTmp,
			pTmp->szName, pTmp->szPhone,
			pTmp->pNext);

		pTmp = pTmp->pNext;
	}

	_getch();
}

int RemoveNode(char* pszName)
{
	USERDATA* pPrevNode = &g_Head;
	USERDATA* pDelete = NULL;

	while (pPrevNode->pNext != NULL) {
		pDelete = pPrevNode->pNext;

		if (strcmp(pDelete->szName, pszName) == 0) {
			pPrevNode->pNext = pDelete->pNext;
			free(pDelete);

			return 1;
		}

		pPrevNode = pPrevNode->pNext;
	}

	return 0;
}

void Remove()
{
	char szName[32] = { 0 };

	printf("Input name : ");
	fflush(stdin);
	gets_s(szName, sizeof(szName));

	RemoveNode(szName);
}

int PrintUI()
{
	int nInput = 0;

	system("cls");
	printf("[1] Add\t [2] Search\t [3] Print all\t [4] Remove\t [0] Exit\n:");

	scanf_s("%d", &nInput);

	return nInput;
}

int LoadList(char* pszFileName)
{
	FILE* fp = NULL;
	USERDATA user = { 0 };

	fopen_s(&fp, pszFileName, "rb");

	if (fp == NULL)
		return 0;

	ReleaseList();

	while (fread(&user, sizeof(USERDATA), 1, fp)) {
		AddNewNode(user.szName, user.szPhone);
	}

	fclose(fp);

	return 0;
}

int SaveList(char* pszFileName)
{
	FILE* fp = NULL;
	USERDATA* pTmp = g_Head.pNext;

	fopen_s(&fp, pszFileName, "wb");

	if (fp == NULL) {
		puts("ERROR: 리스트 파일을 쓰기 모드로 열지 못했습니다.");
		_getch();

		return 0;
	}

	while (pTmp != NULL)
	{
		if (fwrite(pTmp, sizeof(USERDATA), 1, fp) != -1)
			printf("ERROR: %s에 대한 정보를 저장하는 데 실패했습니다.\n", pTmp->szName);

		pTmp = pTmp->pNext;
	}

	fclose(fp);

	return 1;
}

void ReleaseList()
{
	USERDATA* pTmp = g_Head.pNext;
	USERDATA* pDelete = NULL;

	while (pTmp != NULL) {
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		free(pDelete);
	}

	memset(&g_Head, 0, sizeof(USERDATA));
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