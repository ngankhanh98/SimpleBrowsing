// SimpleBrowsing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>


int main()
{
	const int BUFFER_SIZE = 255;
	WCHAR buffer[BUFFER_SIZE];
	GetLogicalDriveStrings(BUFFER_SIZE, buffer);
	WCHAR *locate;

	// thay thế '\0' = ' ' --> buffer = "C:\ D:\ E:\"
	while (locate = wcschr(buffer, L'\0'))
	{
		buffer[locate - buffer] = ' ';
		if (buffer[locate - buffer + 1] == '\0')
			break;
	}

	// duyệt hết chuỗi buffer để tìm các ổ đĩa
	HANDLE hFile;
	WIN32_FIND_DATA data;
	WCHAR disk[BUFFER_SIZE];
	int i = 0;

	do {

		wcsncpy_s(disk, buffer, 3);
		wprintf(L"\n\n\tDirectory of %s\n\n", disk);
		wcsncat_s(disk, L"\\*.*", 4);


		hFile = FindFirstFile(disk, &data); // Tìm tập tin đầu tiên

		do {
			// Chuyển đổi sang local time
			SYSTEMTIME stUTC, stLocal;
			FileTimeToSystemTime(&data.ftLastAccessTime, &stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

			wprintf(L"%02d/%02d/%d", stLocal.wDay, stLocal.wMonth, stLocal.wYear);

			LARGE_INTEGER size;
			size.HighPart = data.nFileSizeHigh;
			size.LowPart = data.nFileSizeLow;
			wprintf(L"\t%10lu", size.QuadPart);

			wprintf(L"\t%s\n", data.cFileName);
		} while (FindNextFile(hFile, &data)); // Cho đến khi không còn tập tin kế

		// kết thúc buffer > break
		*buffer = buffer[4 * ++i];
		if (!(*buffer))
			break;

	} while (1);

	FindClose(hFile);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

