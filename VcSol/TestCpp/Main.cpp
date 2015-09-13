#include <windows.h>
#include <iostream>



void main() {
	WIN32_FIND_DATA findfiledata;
	HANDLE hfind = FindFirstFile("D:\\Varuna\\Projects\\VcStuff\\VcSol\\Release\\*.dll", &findfiledata);
	if(hfind  == INVALID_HANDLE_VALUE) {
		std::cerr << "Invalid handle returned" << std::endl;
    }
	while(FindNextFile(hfind, &findfiledata)) {
		std::cout << "File " << findfiledata.cFileName << std::endl;
	}
	FindClose(hfind);
	getchar();
}