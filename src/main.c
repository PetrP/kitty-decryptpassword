
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

void argv(int pos, char* out, char* defaultValue)
{
	int nArgs;
	LPWSTR* szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (nArgs > pos)
	{
		LPWSTR w = szArglist[pos];
		wcstombs(out, w, wcslen(w));
	}
	else
	{
		memcpy(out, defaultValue, strlen(defaultValue));
	}
}

void env(char* name, char* out)
{
	LPCTSTR lpName;
	DWORD nSize = 4096;
	TCHAR lpBuffer[nSize];
	DWORD ret = GetEnvironmentVariable(name, &lpBuffer, nSize);
	if (ret > 0)
	{
		memcpy(out, lpBuffer, strlen(lpBuffer));
	}
	else
	{
		memcpy(out, "", 0);
	}
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmdline, int show) {

	char password[4096] = "";
	char mode[4096] = "";
	char host[4096] = "";
	char termtype[4096] = "";
	env("PASSWORD", &password);
	argv(1, &mode, "");
	argv(2, &host, "");
	argv(3, &termtype, "xterm");

	if (strlen(mode) == 0 || strcmp(mode, "--help") == 0)
	{
		fprintf(stderr, "HELP\n");
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "	PASSWORD=<password> kitty-decryptpassword.exe <mode> <host> [<termtype>]\n");
		fprintf(stderr, "	PASSWORD=<password> WINEDEBUG='-all' wine kitty-decryptpassword.exe <mode> <host> [<termtype>]\n");
		fprintf(stderr, "	kitty-decryptpassword.exe --help\n");
		fprintf(stderr, "Where:\n");
		fprintf(stderr, "	- <password> is 'Password' from 'kitty.sav'.\n");
		fprintf(stderr, "	- <mode> is 0 or 1. Probably should be 0.\n");
		fprintf(stderr, "	- <host> is 'HostName' from 'kitty.sav'.\n");
		fprintf(stderr, "	- <termtype> is 'TerminalType' from 'kitty.sav', default 'xterm'.\n");
		fprintf(stderr, "	- The decrypted password is printed to stdout. No integrity checks so output is random for wrong mode/host/termtype.\n");
		return 1;
	}

	char* pst;
	memcpy(pst, password, strlen(password));
	decryptpassword(atoi(mode), pst, host, termtype);
	//MASKPASS(atoi(mode), pst);

	printf(pst);
	return 0;
}

int GetUserPassSSHNoSave() { return 0; }
