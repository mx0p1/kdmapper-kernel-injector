#pragma once

#include <Windows.h>
#include <string>
#include <cstdlib>
#include "shellcode.h"
#include "xor.h"

#define patch_shell xor_w(L"\\SoftwareDistribution\\Download\\")

inline std::string random_string()
{
	std::string str = xor_a("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890");
	std::string newstr;
	int pos;
	while (newstr.size() != 32)
	{
		pos = ((rand() % (str.size() + 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr + "";
}

inline std::wstring random_string_w()
{
	std::wstring str = xor_w(L"QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890");
	std::wstring newstr;
	int pos;
	while (newstr.size() != 5)
	{
		pos = ((rand() % (str.size() + 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

inline std::wstring get_parent(const std::wstring& path)
{
	if (path.empty())
		return path;

	auto idx = path.rfind(L'\\');
	if (idx == path.npos)
		idx = path.rfind(L'/');

	if (idx != path.npos)
		return path.substr(0, idx);
	else
		return path;
}

inline std::wstring get_exe_directory()
{
	wchar_t imgName[MAX_PATH] = { 0 };
	DWORD len = ARRAYSIZE(imgName);
	QueryFullProcessImageNameW(GetCurrentProcess(), 0, imgName, &len);
	std::wstring sz_dir = (std::wstring(get_parent(imgName)) + xor_w(L"\\"));
	return sz_dir;
}

inline std::wstring get_files_directory()
{
	WCHAR system_dir[256];
	GetWindowsDirectoryW(system_dir, 256);
	std::wstring sz_dir = (std::wstring(system_dir) + xor_w(L"\\SoftwareDistribution\\Download\\"));
	return sz_dir;
}

inline std::wstring get_random_file_name_directory(std::wstring type_file)
{
	std::wstring sz_file = get_files_directory() + random_string_w() + type_file;
	return sz_file;
}

inline void run_us_admin(std::wstring sz_exe, bool show)
{
	ShellExecuteW(NULL, xor_w(L"runas"), sz_exe.c_str(), NULL, NULL, show);
}

inline void run_us_admin_and_params(std::wstring sz_exe, std::wstring sz_params, bool show)
{
	ShellExecuteW(NULL, xor_w(L"runas"), sz_exe.c_str(), sz_params.c_str(), NULL, show);
}

inline bool drop_mapper(std::wstring path)
{
	HANDLE h_file;
	BOOLEAN b_status = FALSE;
	DWORD byte = 0;

	h_file = CreateFileW(path.c_str(), GENERIC_ALL, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() == ERROR_FILE_EXISTS)
		return true;

	if (h_file == INVALID_HANDLE_VALUE)
		return false;

	b_status = WriteFile(h_file, shell_mapper, sizeof(shell_mapper), &byte, nullptr);
	CloseHandle(h_file);

	if (!b_status)
		return false;

	return true;
}

inline bool drop_driver(std::wstring path)
{
	HANDLE h_file;
	BOOLEAN b_status = FALSE;
	DWORD byte = 0;

	h_file = CreateFileW(path.c_str(), GENERIC_ALL, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() == ERROR_FILE_EXISTS)
		return true;

	if (h_file == INVALID_HANDLE_VALUE)
		return false;

	b_status = WriteFile(h_file, shell_driver, sizeof(shell_driver), &byte, nullptr);
	CloseHandle(h_file);

	if (!b_status)
		return false;

	return true;
}

inline std::wstring get_files_path()
{
	WCHAR system_dir[256];
	GetWindowsDirectoryW(system_dir, 256);
	return (std::wstring(system_dir) + patch_shell);
}

inline void Mapper()
{
	std::wstring sz_driver = get_random_file_name_directory(xor_w(L".sys"));
	std::wstring sz_mapper = get_random_file_name_directory(xor_w(L".exe"));
	std::wstring sz_params_map = xor_w(L"-map ") + sz_driver;

	DeleteFileW(sz_driver.c_str());
	DeleteFileW(sz_mapper.c_str());

	Sleep(1000);

	drop_driver(sz_driver);
	drop_mapper(sz_mapper);

	run_us_admin_and_params(sz_mapper, sz_params_map, false);
	Sleep(6000);

	DeleteFileW(sz_driver.c_str());
	DeleteFileW(sz_mapper.c_str());
}