// SecretBro.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "qWatcher.h"
#include "U.h"
using namespace std;



void Execute(const std::wstring& path)
{
	//見た目は悪いが、taskkillの/Tオプションを入れないとchromeがクラッシュしたと判定されることがある。
	system("taskkill /T /f /im:chrome.exe");
	system("taskkill /T /f /im:mpc-hc.exe");

	const wstring extension = get_extension(path);
	if (extension == L"url")
	{
		const wstring url = GetUrlFromUrlFile(path);
		if (url != L"")
		{
			DeleteFileW(path.c_str());

			std::string exec = "start chrome --incognito "+WStringToString(url);
			system(exec.c_str());
			Sleep(15000);
			SendKey('F');
			return ;
		}
	}

	{
        ShellExecuteW(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
		Sleep(2000);
		DeleteFileW(path.c_str());
		Sleep(1500);
		SendKey('F');
	}
}

bool SpControl(wstring file_path,wstring filename)
{
	if (filename == L"_VolDown.txt")
	{
		VolDown();
		DeleteFileW(file_path.c_str());
		return true;
	}
	if (filename == L"_VolUp.txt")
	{
		VolUp();
		DeleteFileW(file_path.c_str());
		return true;
	}
	if (filename == L"_RewindKey.txt")
	{
		SendKey('J');
		DeleteFileW(file_path.c_str());
		return true;
	}
	if (filename == L"_FastForwardKey.txt")
	{
		SendKey('L');
		DeleteFileW(file_path.c_str());
		return true;
	}
	return false;
}

 
DWORD WINAPI watch_folder(LPVOID lpParam) 
{
    wstring folder_path = *(wstring*)lpParam;
    while (true) {
        HANDLE hDir = CreateFileW(folder_path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
        if (hDir == INVALID_HANDLE_VALUE) {
            cout << "Error: " << GetLastError() << endl;
            return 1;
        }

        DWORD dwBytesReturned;
        char buffer[1024];
        FILE_NOTIFY_INFORMATION* pNotify;
        while (true) {
            if (ReadDirectoryChangesW(hDir, buffer, sizeof(buffer), TRUE, FILE_NOTIFY_CHANGE_FILE_NAME, &dwBytesReturned, NULL, NULL)) {
                pNotify = (FILE_NOTIFY_INFORMATION*)buffer;
                if (pNotify->Action == FILE_ACTION_ADDED) 
				{
					wstring filename = wstring(pNotify->FileName, pNotify->FileNameLength / 2);
                    wstring file_path = folder_path + L"\\" + filename;
					if (SpControl(file_path,filename))
					{
						continue;
					}
					Execute(file_path);
                }
            }
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    wstring folder_path = L"C:\\rti\\q\\q";
    HANDLE hThread = CreateThread(NULL, 0, watch_folder, &folder_path, 0, NULL);
    if (hThread == NULL) {
        cout << "Error: " << GetLastError() << endl;
        return 1;
    }

    NOTIFYICONDATAW nid;
    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = NULL;
    nid.uID = 0;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_USER + 1;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcscpy_s(nid.szTip, L"qWatcher");
    Shell_NotifyIconW(NIM_ADD, &nid);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_USER + 1) {
            switch (msg.lParam) {
            case WM_RBUTTONDOWN:
                HMENU hMenu;
                hMenu = CreatePopupMenu();
                AppendMenuW(hMenu, MF_STRING, 1, L"終了");
                SetForegroundWindow(msg.hwnd);
                TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, msg.pt.x, msg.pt.y, 0, msg.hwnd, NULL);
                DestroyMenu(hMenu);
                break;
            case 1:
                Shell_NotifyIconW(NIM_DELETE, &nid);
                PostQuitMessage(0);
                break;
            }
        }
    }
	CloseHandle(hThread);

    return 0;
}
