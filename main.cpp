#include <iostream>
#include <Windows.h>
#include <shlobj.h>
#include <ctime>
#include <random>
#include <thread>
#include <chrono>
#include "Communication/api.h"
#include "Communication/Utils.h"
#include "driver/driver.h"
#include "Injection/injector.h"
using namespace std;

std::wstring random_string_w(size_t length = 16)
{
    const wchar_t characters[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, (sizeof(characters) / sizeof(wchar_t)) - 2);
    std::this_thread::sleep_for(std::chrono::milliseconds(0));

    std::wstring random_str;
    for (size_t i = 0; i < length; ++i) {
        random_str += characters[distribution(generator)];
    }
    return random_str;
}

void SetColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ForceAdmin()
{
    if (!IsUserAnAdmin())
    {
        wchar_t szPath[MAX_PATH];
        GetModuleFileNameW(NULL, szPath, MAX_PATH);
        ShellExecuteW(NULL, L"runas", szPath, NULL, NULL, SW_NORMAL);
        ExitProcess(0);
    }
}

void PrintTime() {
    const std::time_t now = std::time(nullptr);
    std::tm calendar_time;
    localtime_s(&calendar_time, &now);
    std::cout << "[" << calendar_time.tm_hour << ":" << calendar_time.tm_min << ":" << calendar_time.tm_sec << "] ";
}

void StartMovingTitle()
{
    std::thread([]() {
        while (true) {
            std::wstring moving_title = random_string_w(8) + L"-" + random_string_w(8) + L"-" + random_string_w(8);
            SetConsoleTitleW(moving_title.c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(0));
        }
        }).detach();
}

int main()
{
    ForceAdmin();
    StartMovingTitle();

    SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    PrintTime();
    std::cout << "[+] Initializing Loader...\n";

    
    DriverClass& driver = DRV();
    driver.DriverHANDLE();

    if (!driver.isLoaded())
    {
        Mapper(); 
        driver.DriverHANDLE(); 
    }

    
    Sleep(2000);

    if (!driver.isLoaded())
    {
        SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        PrintTime();
        std::cout << "[-] Failed to Initialize Loader... \n";
        SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(4000);
        return 1;
    }

    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    PrintTime();
    std::cout << "[+] Loader initialized successfully!\n";
    SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    PrintTime();
    std::cout << "[*] Looking for test.dll...\n";

    wchar_t current_dir[MAX_PATH];
    GetModuleFileNameW(NULL, current_dir, MAX_PATH);

    std::wstring path_str(current_dir);
    size_t last_backslash = path_str.find_last_of(L"\\");
    std::wstring parent_dir = (last_backslash != std::wstring::npos) ? path_str.substr(0, last_backslash) : path_str;
    std::wstring dll_path = parent_dir + L"\\cheat.dll";

    PVOID dll_buffer = GetDLLFile(dll_path.c_str());
    if (!dll_buffer)
    {
        SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        PrintTime();
        std::cout << "[-] Failed to find or read 'test.dll' in the loader directory!\n";
        SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(4000);
        return 1;
    }

    PrintTime();
    std::cout << "[*] Waiting for notepad.exe (notepad.exe)...\n";

    DWORD proc_id = 0;
    while (proc_id == 0)
    {
        proc_id = GetProcId("notepad.exe");
        Sleep(1000);
    }

    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    PrintTime();
    std::cout << "[+] process found! PID: " << proc_id << "\n";
    SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    PrintTime();
    std::cout << "[*] Injecting...\n";

    bool injection_status = Enject((BYTE*)dll_buffer, "notepad.exe");

    if (injection_status)
    {
        SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        PrintTime();
        std::cout << "[+] Successfully Injected Enjoy!!\n";
        SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
    {
        SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        PrintTime();
        std::cout << "[-] Injection failed!.\n";
        SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }

    Sleep(4000);
    return 0;
}