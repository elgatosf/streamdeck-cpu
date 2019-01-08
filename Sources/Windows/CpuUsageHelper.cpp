//==============================================================================
/**
@file       CpuUsageHelper.cpp

@brief		Calculate the current CPU percentage

@copyright  (c) 2018, Corsair Memory, Inc.
			This source code is licensed under the MIT-style license found in the LICENSE file.

**/
//==============================================================================

#include "CpuUsageHelper.h"

CpuUsageHelper::CpuUsageHelper() 
{
	PdhOpenQuery(nullptr, NULL, &mCpuQuery);
	PdhAddEnglishCounter(mCpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &mCpuTotal);
	PdhCollectQueryData(mCpuQuery);
	GetCurrentCPUValue();
}

int CpuUsageHelper::GetCurrentCPUValue()
{
	PDH_FMT_COUNTERVALUE counterVal;

	PdhCollectQueryData(mCpuQuery);
	PdhGetFormattedCounterValue(mCpuTotal, PDH_FMT_LONG, NULL, &counterVal);
	return (int)counterVal.longValue;
}