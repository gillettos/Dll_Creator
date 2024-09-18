// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DLLCREATER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DLLCREATER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLLCREATER_EXPORTS
#define DLLCREATER_API __declspec(dllexport)
#else
#define DLLCREATER_API __declspec(dllimport)
#endif

// This class is exported from the dll
class DLLCREATER_API CDLLCreater {
public:
	CDLLCreater(void);
	// TODO: add your methods here.
};

extern DLLCREATER_API int nDLLCreater;

DLLCREATER_API int fnDLLCreater(void);
