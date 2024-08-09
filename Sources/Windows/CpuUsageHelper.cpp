//==============================================================================
/**
@file       CpuUsageHelper.cpp

@brief		Calculate the current CPU percentage

@copyright  (c) 2018, Corsair Memory, Inc.
			This source code is licensed under the MIT-style license found in the LICENSE file.

**/
//==============================================================================

#include "CpuUsageHelper.h"
#include <algorithm>

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
	int result = std::min((int)counterVal.longValue, 100);
	return result;
}
