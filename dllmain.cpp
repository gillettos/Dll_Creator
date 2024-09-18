#include <windows.h> // Include Windows headers first
#include "pch.h"
#include "TcAdsDef.h"
#include "TcAdsAPI.h" // Include the ADS library
#include <iostream>

// Your existing code...



long nErr;
AmsAddr Addr;
PAmsAddr pAddr = &Addr;

using namespace std;
void InitAds()
{
    // Set AMS Net ID and port of the PLC
    pAddr->netId.b[0] = 5;
    pAddr->netId.b[1] = 143;
    pAddr->netId.b[2] = 125;
    pAddr->netId.b[3] = 242;
    pAddr->netId.b[4] = 1;
    pAddr->netId.b[5] = 1;
    pAddr->port = 851; // Default port for TwinCAT 3 PLC

    std::cout << "ADS initialized successfully." << std::endl;  
    
    // Initialize ADS
    nErr = AdsPortOpen();
    if (nErr)
    {
        std::cerr << "Error: AdsPortOpen: " << nErr << std::endl;
        return;
    }


    // Get local AMS Net ID
    nErr = AdsGetLocalAddress(pAddr);
    if (nErr)
    {
        std::cerr << "Error: AdsGetLocalAddress: " << nErr << std::endl;
        return;
    }


}


void SetVariable(const char* varName, bool value)
{
    long nErr;
    uint32_t hVar;
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(hVar), &hVar, strlen(varName), (void*)varName);
    if (nErr)
    {
        std::cerr << "Error: AdsSyncReadWriteReq (handle): " << nErr << std::endl;
        return;
    }

    nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, hVar, sizeof(value), &value);
    if (nErr)
    {
        std::cerr << "Error: AdsSyncWriteReq: " << nErr << std::endl;
        return;
    }

    std::cout << "Variable " << varName << " set to " << (value ? "True" : "False") << std::endl;

    // Release the handle
    AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(hVar), &hVar);
}


//GET THE LIVE VALUE FROM THE PLC
bool GetVariable(const char* varName, bool& value)
{
    long nErr;
    uint32_t hVar;
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(hVar), &hVar, strlen(varName), (void*)varName);
    if (nErr)
    {
        std::cerr << "Error: AdsSyncReadWriteReq (handle): " << nErr << std::endl;
        return false;
    }

    nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, hVar, sizeof(value), &value);
    if (nErr)
    {
        std::cerr << "Error: AdsSyncReadReq: " << nErr << std::endl;
        AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(hVar), &hVar);
        return false;
    }

    std::cout << "Variable " << varName << " is reading " << (value ? "True" : "False") << std::endl;

    // Release the handle
    AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(hVar), &hVar);

    return true;
}






// EXPORT THE FUNCTIONS SO THE CALLER APP (exe), Can Access them

extern "C" __declspec(dllexport) void SetAxis1Enable()
{
    InitAds();
    SetVariable("Main.fbAxis1.bEnable", true);
    AdsPortClose();
}

extern "C" __declspec(dllexport) void SetAxis1Disable()
{
    InitAds();
    SetVariable("Main.fbAxis1.bEnable", false);
    AdsPortClose();
}



/*

extern "C" __declspec(dllexport) void ReadAxis1Enable()
{
    // Initialize ADS communication
    if (AdsPortOpen() == 0)
    {
        std::cerr << "Failed to open ADS port" << std::endl;
        return;
    }

    // Initialize the ADS address (replace with your actual address)
    AmsAddr pAddr;
    memset(&pAddr, 0, sizeof(pAddr));
    pAddr.netId.b[0] = 169; // Example IP address
    pAddr.netId.b[1] = 254;
    pAddr.netId.b[2] = 250;
    pAddr.netId.b[3] = 195;

    pAddr.port = 851;

    bool value;
    if (GetVariable("Main.fbAxis1.bEnable", value))
    {
        std::cout << "Axis 1 Enable is " << (value ? "True" : "False") << std::endl;
    }
    else
    {
        std::cerr << "Failed to read Axis 1 Enable" << std::endl;
    }

    // Close ADS communication
    AdsPortClose();
}

*/







// All Goes wrong when doing a Batch Build with the below included.....!?!?
/*

//READ AN INTEGER
//Define a new GetVariable function for int values:

extern "C" __declspec(dllexport) bool GetVariable(const char* varName, int& value)
{
    long nErr;
    uint32_t hVar;
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(hVar), &hVar, strlen(varName), (void*)varName);
    if (nErr)
    {
        std::cerr << "Error: AdsSyncReadWriteReq (handle): " << nErr << std::endl;
        return false;
    }

    nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, hVar, sizeof(value), &value);
    if (nErr)
    {
        std::cerr << "Error: AdsSyncReadReq: " << nErr << std::endl;
        AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(hVar), &hVar);
        return false;
    }

    std::cout << "Variable " << varName << " is " << value << std::endl;

    // Release the handle
    AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(hVar), &hVar);

    return true;
}

//Use the new GetVariable function in your code :

void Get_nIntToRead_Function()
{
    int value;
    if (GetVariable("Main.nIntToRead", value))
    {
        std::cout << "nIntToRead is reading a value of " << value << std::endl;
    }
    else
    {
        std::cerr << "Failed to read nIntToRead" << std::endl;
    }
}

*/
