#include "stdafx.h"
using namespace std;

void VolDown()
{
    // COMの初期化
    CoInitialize(NULL);

    // デフォルトのオーディオデバイスを取得
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;
    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    // IAudioEndpointVolumeインターフェースを取得
    IAudioEndpointVolume *endpointVolume = NULL;
    defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    // 現在の音量レベルを取得
    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevel(&currentVolume);

    // 音量レベルを0.50 dB下げる
    float newVolume = (float)(currentVolume - 0.50);
    // 音量レベルが-65.25 dB以下にならないようにする
    if (newVolume < -65.25) {
        newVolume = -65.25;
    }
    // 音量レベルを設定する
    endpointVolume->SetMasterVolumeLevel(newVolume, NULL);

    // IAudioEndpointVolumeインターフェースを解放
    endpointVolume->Release();

    // COMの終了
    CoUninitialize();
}

void VolUp()
{
    // COMの初期化
    CoInitialize(NULL);

    // デフォルトのオーディオデバイスを取得
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;
    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    // IAudioEndpointVolumeインターフェースを取得
    IAudioEndpointVolume *endpointVolume = NULL;
    defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    // 現在の音量レベルを取得
    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevel(&currentVolume);

    // 音量レベルを0.50 dB上げる
    float newVolume = (float)(currentVolume + 0.50);
    // 音量レベルが0 dB以上にならないようにする
    if (newVolume > 0) {
        newVolume = 0;
    }
    // 音量レベルを設定する
    endpointVolume->SetMasterVolumeLevel(newVolume, NULL);

    // IAudioEndpointVolumeインターフェースを解放
    endpointVolume->Release();

    // COMの終了
    CoUninitialize();
}


void SendKey(char key)
{
// キーを送信する
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey(key, MAPVK_VK_TO_VSC);
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = key;
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
