#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

#define WIN_32_LEAN_AND_MEAN

void WriteToRegistry(void)
{
	cout << "---Write key to registry---" << endl;

	DWORD lRv;
	HKEY hKey;

	lRv = RegOpenKeyEx(
		HKEY_CURRENT_USER,
		L"Software\\KarlenokCalculator",
		0,
		KEY_WRITE,       
		&hKey
	);

	if (lRv != ERROR_SUCCESS)
	{
		DWORD dwDisposition;

		lRv = RegCreateKeyEx( 
			HKEY_CURRENT_USER,
			L"Software\\KarlenokCalculator",
			0,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,         
			NULL,                    
			&hKey,
			&dwDisposition
		);

		TCHAR sr[] = TEXT("calc.exe");

		RegSetValueEx(
			hKey,
			L"Calculator",
			0,
			REG_SZ,
			reinterpret_cast<BYTE *>(&sr),
			24
		);

		RegCloseKey(hKey);
	}
}

void ReadValueFromRegistry(void)
{
	cout << "---Reading keys and open calc.exe---" << endl;

	HKEY hKey;

	DWORD lRv = RegOpenKeyEx(
		HKEY_CURRENT_USER,
		L"Software\\KarlenokCalculator",
		0,
		KEY_READ,
		&hKey
	);

	if (lRv == ERROR_SUCCESS)
	{
		DWORD BufferSize = sizeof(DWORD);
		DWORD dwRet;
		DWORD cbData;
		DWORD cbVal = 0;

		BYTE byteArray[100];
		DWORD dataSize = sizeof(byteArray);

		dwRet = RegQueryValueEx(
			hKey,
			L"Calculator",
			NULL,
			NULL,
			reinterpret_cast<BYTE*>(&byteArray),
			&dataSize
		);

		LPWSTR text = reinterpret_cast<LPWSTR>(&byteArray);

		if (dwRet == ERROR_SUCCESS)
		{
			char nameproc[100];
			for (int i = 0; i < dataSize / sizeof(WCHAR); i++)
			{
				nameproc[i] = (char)text[i];
			}
			nameproc[dataSize / sizeof(WCHAR)] = '\0';
			system(nameproc);
		}
		else
		{
			cout << "\nRegQueryValueEx failed " << dwRet << endl;
		}
	}
	else
	{
		cout << "RegOpenKeyEx failed " << lRv << endl;
	}
}

int DeleteRegistryKey()
{
	cout << "---Deleting keys---" << endl;
	int lReturn = RegDeleteKey(HKEY_CURRENT_USER, L"Software\\KarlenokCalculator");
	return lReturn;
}

int main()
{
	//WriteToRegistry();
	//system("pause");

	//ReadValueFromRegistry();
	//system("pause");

	//DeleteRegistryKey();
	//system("pause");
	return 0;
}