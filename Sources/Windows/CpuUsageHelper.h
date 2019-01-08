//==============================================================================
/**
@file       CpuUsageHelper.h

@brief		Calculate the current CPU percentage

@copyright  (c) 2018, Corsair Memory, Inc.
			This source code is licensed under the MIT-style license found in the LICENSE file.

**/
//==============================================================================

#pragma once
#pragma comment(lib, "Pdh.lib")
#include "pdh.h"

class CpuUsageHelper
{
public:
	CpuUsageHelper();
	~CpuUsageHelper() {};
	
	int GetCurrentCPUValue();

private:
	PDH_HQUERY mCpuQuery;
	PDH_HCOUNTER mCpuTotal;
};
