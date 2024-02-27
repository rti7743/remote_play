#include "stdafx.h"
using namespace std;

void VolDown()
{
    // COM�̏�����
    CoInitialize(NULL);

    // �f�t�H���g�̃I�[�f�B�I�f�o�C�X���擾
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;
    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    // IAudioEndpointVolume�C���^�[�t�F�[�X���擾
    IAudioEndpointVolume *endpointVolume = NULL;
    defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    // ���݂̉��ʃ��x�����擾
    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevel(&currentVolume);

    // ���ʃ��x����0.50 dB������
    float newVolume = (float)(currentVolume - 0.50);
    // ���ʃ��x����-65.25 dB�ȉ��ɂȂ�Ȃ��悤�ɂ���
    if (newVolume < -65.25) {
        newVolume = -65.25;
    }
    // ���ʃ��x����ݒ肷��
    endpointVolume->SetMasterVolumeLevel(newVolume, NULL);

    // IAudioEndpointVolume�C���^�[�t�F�[�X�����
    endpointVolume->Release();

    // COM�̏I��
    CoUninitialize();
}

void VolUp()
{
    // COM�̏�����
    CoInitialize(NULL);

    // �f�t�H���g�̃I�[�f�B�I�f�o�C�X���擾
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;
    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    // IAudioEndpointVolume�C���^�[�t�F�[�X���擾
    IAudioEndpointVolume *endpointVolume = NULL;
    defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    // ���݂̉��ʃ��x�����擾
    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevel(&currentVolume);

    // ���ʃ��x����0.50 dB�グ��
    float newVolume = (float)(currentVolume + 0.50);
    // ���ʃ��x����0 dB�ȏ�ɂȂ�Ȃ��悤�ɂ���
    if (newVolume > 0) {
        newVolume = 0;
    }
    // ���ʃ��x����ݒ肷��
    endpointVolume->SetMasterVolumeLevel(newVolume, NULL);

    // IAudioEndpointVolume�C���^�[�t�F�[�X�����
    endpointVolume->Release();

    // COM�̏I��
    CoUninitialize();
}


void SendKey(char key)
{
// �L�[�𑗐M����
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
    // wstring �� SJIS
    int iBufferSize = WideCharToMultiByte( CP_OEMCP, 0, oWString.c_str()
        , -1, (char *)NULL, 0, NULL, NULL );
 
    // �o�b�t�@�̎擾
    CHAR* cpMultiByte = new CHAR[ iBufferSize ];
 
    // wstring �� SJIS
    WideCharToMultiByte( CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
        , iBufferSize, NULL, NULL );
 
    // string�̐���
    std::string oRet( cpMultiByte, cpMultiByte + iBufferSize - 1 );
 
    // �o�b�t�@�̔j��
    delete [] cpMultiByte;
 
    // �ϊ����ʂ�Ԃ�
    return( oRet );
}
