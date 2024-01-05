// SecretBro.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "qWatcher.h"


using namespace std;

BOOL TerminateProcessByName(LPCTSTR szProcessName, UINT uExitCode)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapShot == INVALID_HANDLE_VALUE) {
        return(FALSE);
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    BOOL bResult = Process32First(hSnapShot, &pe);
    while (bResult) {
        if (_tcsicmp(pe.szExeFile, szProcessName) == 0) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                (DWORD)pe.th32ProcessID);
            if (hProcess != NULL) {
                TerminateProcess(hProcess, uExitCode);
                CloseHandle(hProcess);
            }
        }
        bResult = Process32Next(hSnapShot, &pe);
    }

    CloseHandle(hSnapShot);
    return(TRUE);
}

void SendFKey()
{
// Fキーを送信する
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey('F', MAPVK_VK_TO_VSC);
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = 'F';
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
}


std::wstring GetUrlFromUrlFile(const std::wstring& url_file_path) 
{
    std::wifstream url_file(url_file_path);
    std::wstring line;
    while (std::getline(url_file, line)) {
        if (line.find(L"URL=") == 0) {
            return line.substr(4);
        }
    }
    return L"";
}


std::wstring get_extension(const std::wstring& path)
{
    size_t dot_pos = path.find_last_of(L".");
    if (dot_pos == std::string::npos)
    {
        return L"";
    }
    else
    {
        std::wstring extension = path.substr(dot_pos + 1);
        return extension;
    }
}

std::string WStringToString(const std::wstring& oWString)
{
    // wstring → SJIS
    int iBufferSize = WideCharToMultiByte( CP_OEMCP, 0, oWString.c_str()
        , -1, (char *)NULL, 0, NULL, NULL );
 
    // バッファの取得
    CHAR* cpMultiByte = new CHAR[ iBufferSize ];
 
    // wstring → SJIS
    WideCharToMultiByte( CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
        , iBufferSize, NULL, NULL );
 
    // stringの生成
    std::string oRet( cpMultiByte, cpMultiByte + iBufferSize - 1 );
 
    // バッファの破棄
    delete [] cpMultiByte;
 
    // 変換結果を返す
    return( oRet );
}

void Execute(const std::wstring& path)
{
	TerminateProcessByName(L"chrome.exe",0);
	TerminateProcessByName(L"mpc-hc.exe",0);

	const wstring extension = get_extension(path);
	if (extension == L"url")
	{
		const wstring url = GetUrlFromUrlFile(path);
		if (url != L"")
		{
			DeleteFileW(path.c_str());

			std::string exec = "start chrome --incognito --disable-features=InfiniteSessionRestore "+WStringToString(url);
			system(exec.c_str());
			Sleep(15000);
			SendFKey();
			return ;
		}
	}

	{
        ShellExecuteW(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
		Sleep(2000);
		DeleteFileW(path.c_str());
		Sleep(1500);
		SendFKey();
	}
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
    wcscpy_s(nid.szTip, L"SecretBro");
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

    return 0;
}
