#include <assert.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#pragma warning(disable:4996)


void getDate(char* str) {
	char date[64];
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	assert(strftime(date, sizeof(date), "%c", tm));
	memcpy(str, date, 64);
}


int main(void) {
	char date[64];
	bool exit = false;
	bool cb = false;
	bool wrong = false;
	char input=NULL;
	char newInput = NULL;
	while (!exit) {
		system("cls");
		if(cb) printf("Previously, you copied the date to the clipboard\n");
		printf("Press X, to quit, press D to copy the current date to the clipboard\n");
		input = getch();
		if (input == 'x') {
			exit = true;
			break;
		}
		if (input == 'd') {
			getDate(date);

			char* pStr = date;
			int wLen = 0;
			while (date[wLen] != '\0') {
				wLen++;
			}

			LPTSTR  lptstrCopy;
			HGLOBAL hglbCopy;

			if (!OpenClipboard(NULL))
				return FALSE;
			EmptyClipboard();
			hglbCopy = GlobalAlloc(GHND, (DWORD)wLen + 1);
			if (hglbCopy == NULL) {
				CloseClipboard();
				return FALSE;
			}
			lptstrCopy = GlobalLock(hglbCopy);
			memcpy(lptstrCopy, pStr, wLen + 1);
			GlobalUnlock(hglbCopy);
			SetClipboardData(CF_TEXT, hglbCopy);
			CloseClipboard();
			cb = true;
			system("cls");
			printf("Done! Date is in clipboard.\n");
			Sleep(1500);
		}

	}

	return 0;
}
