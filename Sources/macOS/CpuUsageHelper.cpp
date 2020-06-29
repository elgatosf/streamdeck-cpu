//==============================================================================
/**
@file		CpuUsageHelper.cpp

@brief		Calculate the current CPU percentage

@copyright	(c) 2018, Corsair Memory, Inc.
			This source code is licensed under the MIT-style license found in the LICENSE file.

**/
//==============================================================================

#include "CpuUsageHelper.h"

#include <cmath>

CpuUsageHelper::CpuUsageHelper() 
{
	int mib[2U] = { CTL_HW, HW_NCPU };
	size_t sizeOfNumCPUs = sizeof(mNumberOfCPUs);
	int status = sysctl(mib, 2U, &mNumberOfCPUs, &sizeOfNumCPUs, NULL, 0U);
	if(status)
	{
		mNumberOfCPUs = 1;
	}
}

int CpuUsageHelper::GetCurrentCPUValue()
{
	if(mNumberOfCPUs <= 0)
		return 0;
	
	double cpuPercentage = 0;
	
	natural_t processorCount = 0;
	kern_return_t err = host_processor_info(mach_host_self(), PROCESSOR_CPU_LOAD_INFO, &processorCount, &mProcessorInfo, &mProcessorInfoCnt);
	if(err == KERN_SUCCESS)
	{
		for(unsigned int cpuIndex = 0 ; cpuIndex < mNumberOfCPUs; cpuIndex++)
		{
			double inUse = 0.0;
			double total = 0.0;
			
			if(mOldProcessorInfo != NULL)
			{
				inUse = (
						 (mProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_USER]	- mOldProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_USER])
						 + (mProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_SYSTEM] - mOldProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_SYSTEM])
						 + (mProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_NICE]	  - mOldProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_NICE])
						 );
				total = inUse + (mProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_IDLE] - mOldProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_IDLE]);
			}
			else
			{
				inUse = mProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_USER] + mProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_SYSTEM] + mProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_NICE];
				total = inUse + mProcessorInfo[(CPU_STATE_MAX * cpuIndex) + CPU_STATE_IDLE];
			}
			
			cpuPercentage += inUse / total;
		}

		if(mOldProcessorInfo)
		{
			size_t prevCpuInfoSize = sizeof(integer_t) * mOldProcessorInfoCnt;
			vm_deallocate(mach_task_self(), (vm_address_t)mOldProcessorInfo, prevCpuInfoSize);
		}
		
		mOldProcessorInfo = mProcessorInfo;
		mOldProcessorInfoCnt = mProcessorInfoCnt;

		mProcessorInfo = NULL;
		mProcessorInfoCnt = 0;
	}
	
	return (int)lround(100.0 * cpuPercentage / mNumberOfCPUs);
}
