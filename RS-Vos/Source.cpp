
#define _WIN32_WINNT 0x0A00        //Win 10
#include <windows.h>
#include <atlimage.h>
#include <iostream>


int main()
{
	RECT rc;
	RECT rc1;
	HWND hwnd = FindWindow(TEXT("SunAwtFrame"), NULL);    //the window can't be min
	if (hwnd == NULL)
	{
		std::cout << "it can't find the specified window" << std::endl;
		return 0;
	}
	GetClientRect(hwnd, &rc);

	//create
	HDC hdcScreen = GetDC(NULL);
	HDC hdc = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen,
		rc.right - rc.left, rc.bottom - rc.top);
	SelectObject(hdc, hbmp);
	
	//Print to memory hdc
	PrintWindow(hwnd, hdc, PW_CLIENTONLY);
	
	//copy to clipboard
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbmp);
	CloseClipboard();
	
	CImage img;
	img.Attach(hbmp);
	std::cout << hbmp;
	img.Save(_T("hello"), Gdiplus::ImageFormatBMP);
	
	//release
	DeleteDC(hdc);
	DeleteObject(hbmp);
	ReleaseDC(NULL, hdcScreen);

	std::cout << "success copy to clipboard, please paste it to the 'mspaint'" << std::endl;

	return 0;
}