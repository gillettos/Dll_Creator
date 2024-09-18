// DLL_Creater.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "DLL_Creater.h"


// This is an example of an exported variable
DLLCREATER_API int nDLLCreater=0;

// This is an example of an exported function.
DLLCREATER_API int fnDLLCreater(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CDLLCreater::CDLLCreater()
{
    return;
}
