//==============================================================================
/**
@file       CpuUsageHelper.cpp

@brief		Calculate the current CPU percentage

@copyright  (c) 2018, Corsair Memory, Inc.
			This source code is licensed under the MIT-style license found in the LICENSE file.

**/
//==============================================================================

#include "CpuUsageHelper.h"
#include <string>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

CpuUsageHelper::CpuUsageHelper()
{
	PdhOpenQuery(nullptr, NULL, &mCpuQuery);
	PdhAddEnglishCounter(mCpuQuery, L"\\Processor Information(_Total)\\% Processor Utility", NULL, &mCpuTotal);
	PdhCollectQueryData(mCpuQuery);
	GetCurrentCPUValue();
}

int CpuUsageHelper::GetCurrentCPUValue()
{
	PDH_FMT_COUNTERVALUE counterVal;

	PdhCollectQueryData(mCpuQuery);
	PdhGetFormattedCounterValue(mCpuTotal, PDH_FMT_LONG, NULL, &counterVal);
	return (int)(MIN(counterVal.longValue, 100L));
}

// Open Windows Task Manager
void CpuUsageHelper::OpenSystemMonitor()
{
	char buffer[MAX_PATH];
	int length = GetSystemDirectoryA(buffer, MAX_PATH);

	if (length > 0 && length <= MAX_PATH) {
		ShellExecuteA(NULL, "open", (std::string(buffer) + "\\Taskmgr.exe").c_str(), NULL, NULL, SW_SHOWDEFAULT);
	}
}
