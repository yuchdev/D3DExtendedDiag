//#include "dxdiag.h"
#include <assert.h>
#include <iostream>
#include <string>

#include "complexContainer.h"
#include "leafContainer.h"


#include "d3d_Info.h"

//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_BSTR_FREE(x)    if(x) { SysFreeString( x ); x = NULL; }
#define EXPAND(x)            x, sizeof(x)/sizeof(TCHAR)


namespace d3dcore {

	D3DInfo::D3DInfo()
	{
		m_pDxDiagProvider = nullptr;
		m_pDxDiagRoot = nullptr;
		m_rootContainer = std::make_shared<ComplexContainer>("DirectX");
	}


	D3DInfo::~D3DInfo()
	{
	}

	void D3DInfo::GetInfo()
	{		

		Traverse(m_pDxDiagRoot);


	}

}





std::string d3dcore::D3DInfo::GetPropertyValue(IDxDiagContainer * dxContainer, WCHAR * propName)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);
	std::string result;

	if (FAILED(hr = dxContainer->GetProp(propName, &var))) return std::string();
		

	switch (var.vt) {

	case VT_I4:
		result = std::to_string(var.intVal);
		break;

	case VT_UI4:
		result = std::to_string(var.uintVal);
		break;

	case VT_BOOL:
		result = var.boolVal != 0 ? std::string("true") : std::string("false");
		break;

	/*case VT_BSTR:

#ifdef _UNICODE
		wcsncpy(strValue, var.bstrVal, 256); //todo: update the length of string
#else
		wcstombs(strValue, var.bstrVal, nStrLen);
#endif
		strValue[nStrLen - 1] = TEXT('\0');

		break;*/
	
	default: std::cout << "No value for property" << std::endl;

	}	
	VariantClear(&var);


	return result;

	
}

std::string d3dcore::D3DInfo::WCharToString(WCHAR * wChar)
{	
	char ch[256];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, wChar, -1, ch, 260, &DefChar, NULL);
	
	//A std:string  using the char* constructor.
	std::string ss(ch);

	return ss;
}

HRESULT d3dcore::D3DInfo::Init(int dxVersion)
{
	HRESULT hr;

	hr = CoInitialize(NULL);
	//m_bCleanupCOM = SUCCEEDED(hr);

	hr = CoCreateInstance(CLSID_DxDiagProvider,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IDxDiagProvider,
		(LPVOID*)&m_pDxDiagProvider);
	if (FAILED(hr))
		return hr;

	if (m_pDxDiagProvider == NULL)
	{
		hr = E_POINTER;
		return hr;
	}

	// Fill out a DXDIAG_INIT_PARAMS struct and pass it to IDxDiagContainer::Initialize
	// Passing in TRUE for bAllowWHQLChecks, allows dxdiag to check if drivers are 
	// digital signed as logo'd by WHQL which may connect via internet to update 
	// WHQL certificates.    
	DXDIAG_INIT_PARAMS dxDiagInitParam;
	ZeroMemory(&dxDiagInitParam, sizeof(DXDIAG_INIT_PARAMS));

	dxDiagInitParam.dwSize = sizeof(DXDIAG_INIT_PARAMS);
	dxDiagInitParam.dwDxDiagHeaderVersion = dxVersion;//DXDIAG_DX9_SDK_VERSION;
	dxDiagInitParam.bAllowWHQLChecks = true;//bAllowWHQLChecks;
	dxDiagInitParam.pReserved = NULL;

	hr = m_pDxDiagProvider->Initialize(&dxDiagInitParam);
	if (FAILED(hr))
		return hr;

	hr = m_pDxDiagProvider->GetRootContainer(&m_pDxDiagRoot);
	return hr;
	
}

HRESULT d3dcore::D3DInfo::Traverse(IDxDiagContainer * parentContainer)
{
	IDxDiagContainer*	pChildContainer;
	DWORD 	dwChildCount;
	DWORD	dwChildIndex;
	WCHAR	wszChildName[256];

	HRESULT hr = parentContainer->GetNumberOfChildContainers(&dwChildCount);
	assert(SUCCEEDED(hr));

	for (dwChildIndex = 0; dwChildIndex < dwChildCount; dwChildIndex++)
	{
		hr = m_pDxDiagRoot->EnumChildContainerNames(dwChildIndex, wszChildName, 256);
		
		std::string ss = WCharToString(wszChildName);
		std::cout << ss << std::endl;
		//create a new D3DContainer here:

		//end of creation
		assert(SUCCEEDED(hr));

		hr = m_pDxDiagRoot->GetChildContainer(wszChildName, &pChildContainer);
		assert(SUCCEEDED(hr));

		// Do something with pChildContainer.		
		hr = Traverse(pChildContainer);
		
		assert(SUCCEEDED(hr));

		SAFE_RELEASE(pChildContainer);
	}

	return S_OK;

}
	

