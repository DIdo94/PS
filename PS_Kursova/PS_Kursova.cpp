// PS_Kursova.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PS_Kursova.h"
#include<vector>
#include<string>
#include<iterator>
#include"Missile.h"
#include"Enemy.h"
#include"Ship.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HDC hdc;
HDC hDCComp;
HBITMAP hBmp, playerShip, alien;
PAINTSTRUCT ps;
HBRUSH missileBrush;
HGDIOBJ hObj;
std::vector<Missile*> missiles;
std::vector<Enemy*> enemies;

int pos = 300;
int posY = 400;

Ship* player = new Ship(pos, posY, 100);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PS_KURSOVA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PS_KURSOVA));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PS_KURSOVA));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PS_KURSOVA);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		0, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	
	
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_FILE_START:
			SetTimer(hWnd, 3, 200, NULL);
			SetTimer(hWnd, 0, 5000, NULL);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		if (player->GetHealth() <= 0)
		{
			//Sleep(5000);
			MessageBox(hWnd, "Your Score is 0", "Game over", NULL);

			PostQuitMessage(0);
		}
		else
		{
			
			hDCComp = CreateCompatibleDC(hdc);
			hBmp = LoadBitmap(hInst, LPCSTR(IDB_BITMAP1));
			playerShip = LoadBitmap(hInst, LPCSTR(IDB_BITMAP2));
			alien = LoadBitmap(hInst, LPCSTR(IDB_BITMAP3));

			SelectObject(hDCComp, hBmp);

			BitBlt(hdc, 0, 0, 1000, 1100, hDCComp, 0, 0, SRCCOPY);

			SelectObject(hDCComp, playerShip);
			player->SetX(pos);
			BitBlt(hdc, player->GetX(), player->GetY(), 128, 128, hDCComp, 0, 0, SRCPAINT);

			SelectObject(hDCComp, alien);
			for (auto& enemy : enemies)
			{
				BitBlt(hdc, enemy->GetX(), enemy->GetY(), 128, 128, hDCComp, 0, 0, SRCPAINT);
			}


			missileBrush = CreateSolidBrush(RGB(255, 123, 101));
			hObj = SelectObject(hdc, missileBrush);
			for (auto& missile : missiles)
			{
				Ellipse(hdc, missile->GetX() + 55, missile->GetY() - 30, missile->GetX() + 75, missile->GetY() - 10);
			}

			// TODO: Add any drawing code that uses hdc here...		
		}
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_TIMER:
	{
		if (wParam==0)
		{
			for (auto& enemy : enemies) 
			{
				enemy->Move();
			}
			enemies.push_back(new Enemy(0, 0));
			enemies.push_back(new Enemy(200, 0));
			enemies.push_back(new Enemy(400, 0));	
			enemies.push_back(new Enemy(600, 0));
			//UpdateWindow(hWnd);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			//InvalidateRect(hWnd, NULL, TRUE);
		}
		
		else if(wParam==3)
		{
			for (std::vector<Enemy*>::iterator i = enemies.begin(); i!=enemies.end();)
			{
				
				if ((*i)->GetY()+128 > player->GetY())
				{
					if (((*i)->GetX() - player->GetX())<128)
					{
						player->AddHealth(-100);
						i=enemies.erase(i);
						break;
					}
					else
					{
						player->AddHealth(-25);
						i=enemies.erase(i);
						if (player->GetHealth()<=0)
						{
							break;
						}
					}			
				}
				else
				{
					++i;
				}
			}

			for (std::vector<Missile*>::iterator j = missiles.begin(); j != missiles.end();)
			{
				(*j)->Move();
				bool isHit = false;
				for (std::vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end();++i)
				{
					bool cond = ((*j)->GetX()<=(*i)->GetX() + 128) && ((*j)->GetX()>= (*i)->GetX()-128);
					if (((*j)->GetY()-30 <= (*i)->GetY()+128) && (cond))
					{					
						j=missiles.erase(j);
						enemies.erase(i);
						isHit = true;
						break;
					}
				}
				if (!isHit)
				{
					++j;
				}

			}
			for (std::vector<Enemy*>::iterator j = enemies.begin(); j != enemies.end();)
			{
				if ((*j)->GetY() == -1)
				{
					j=enemies.erase(j);
				}
				else if(j!=enemies.end())
				{
					++j;
				}
			}
			//UpdateWindow(hWnd);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			//InvalidateRect(hWnd, NULL, TRUE);
		}
		
	}
	break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
		{
			pos -= 20;
			InvalidateRect(hWnd, NULL, TRUE);

		}
		break;
		case VK_RIGHT:
		{
			pos += 20;	
			//UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		case VK_SPACE:
		{
			// TODO vector of missiles
			missiles.push_back(new Missile(pos,posY));
			//UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		default:
			break;
		}
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
