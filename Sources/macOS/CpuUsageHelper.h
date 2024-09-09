//==============================================================================
/**
@file       CpuUsageHelper.h

@brief		Calculate the current CPU percentage

@copyright  (c) 2018, Corsair Memory, Inc.
			This source code is licensed under the MIT-style license found in the LICENSE file.

**/
//==============================================================================

#pragma once

#include <sys/sysctl.h>
#include <sys/types.h>
#include <mach/mach.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>

class CpuUsageHelper
{
public:
	CpuUsageHelper();
	~CpuUsageHelper() {};
	
	int GetCurrentCPUValue();
	void OpenSystemMonitor();

private:
	
	processor_info_array_t mProcessorInfo = nullptr;
	mach_msg_type_number_t mProcessorInfoCnt = 0;
	
	processor_info_array_t mOldProcessorInfo = nullptr;
	mach_msg_type_number_t mOldProcessorInfoCnt = 0;
	
	unsigned mNumberOfCPUs = 0;
};
