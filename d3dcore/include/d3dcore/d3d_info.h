#pragma once

#define INITGUID
#include "dxdiag.h"
#include <Windows.h>

#include "d3d_utils.h"

#include <string>
#include <memory>
#include <assert.h>
#include <iostream>
#include <string>
#include <any>


//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_BSTR_FREE(x)    if(x) { SysFreeString( x ); x = NULL; }
#define EXPAND(x)            x, sizeof(x)/sizeof(TCHAR)



namespace d3dcore {

	/*enum class SDKVersion {
	DX9: DXDIAG_DX9_SDK_VERSION,
	DX11: 112,		
	};*/

	template<typename Container>
	class D3DInfo
	{
	public:
		D3DInfo();
		~D3DInfo();


	private:
		//property
		IDxDiagProvider* m_dxdiag_provider;
		IDxDiagContainer* m_dxdiag_root;
		std::shared_ptr<Container> m_root_container;
		//private method
		std::string get_property_value(IDxDiagContainer* dxContainer, WCHAR* propName); //todo: update with sdt::any
		
		
	public:
		void init(int dxVersion = DXDIAG_DX9_SDK_VERSION);
		void traverse(IDxDiagContainer*, std::shared_ptr<Container> parent);
		void query_info();
		std::shared_ptr<Container> get_root_container();
	};

}


using namespace d3dcore;

template<typename Container>
D3DInfo<Container>::D3DInfo()
{
	m_dxdiag_provider = nullptr;
	m_dxdiag_root = nullptr;
	m_root_container = std::make_shared<Container>("DirectX");
}

template<typename Container>
D3DInfo<Container>::~D3DInfo()
{
	SAFE_RELEASE(m_dxdiag_provider);
	SAFE_RELEASE(m_dxdiag_root);
}

template<typename Container>
void D3DInfo<Container>::query_info()
{

	traverse(m_dxdiag_root, m_root_container);


}

template<typename Container>
std::shared_ptr<Container> D3DInfo<Container>::get_root_container()
{
	return this->m_root_container;
}

//}




template<typename Container>
std::string D3DInfo<Container>::get_property_value(IDxDiagContainer * dxContainer, WCHAR * propName)
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

	default: result = std::string("Default Value");//std::cout << "No value for property" << std::endl;

	}
	VariantClear(&var);


	return result;


}

template<typename Container>
void D3DInfo<Container>::init(int dxVersion)
{
	HRESULT hr;

	hr = CoInitialize(NULL);
	throw_if_failed(hr, "Can not CoInitialize() COM");		

	//m_bCleanupCOM = SUCCEEDED(hr);

	hr = CoCreateInstance(CLSID_DxDiagProvider,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IDxDiagProvider,
		(LPVOID*)&m_dxdiag_provider);

	throw_if_failed(hr, "Can not CoCreateInstance CLSID_DxDiagProvider ");

	/*if (m_dxdiag_provider == NULL)
	{
		hr = E_POINTER;
		return hr;
	}*/

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

	hr = m_dxdiag_provider->Initialize(&dxDiagInitParam);
	throw_if_failed(hr, "Can not Initialize DXDIAG_INIT_PARAMS ");
	//if (FAILED(hr))
	//	return hr;

	hr = m_dxdiag_provider->GetRootContainer(&m_dxdiag_root);
	throw_if_failed(hr, "GetRootContainer from Provider Failed ");

}

template<typename Container>
void D3DInfo<Container>::traverse(IDxDiagContainer * parentContainer, std::shared_ptr<Container> parent)
{
	IDxDiagContainer*	pChildContainer;
	DWORD 	dwChildCount;
	DWORD 	dwPropCount;
	DWORD	dwChildIndex;
	WCHAR	wszChildName[256];
	WCHAR	wszPropName[256];

	HRESULT hr = parentContainer->GetNumberOfChildContainers(&dwChildCount);
	throw_if_failed(hr, "Can not GetNumberOfChildContainers ");
	

	for (dwChildIndex = 0; dwChildIndex < dwChildCount; dwChildIndex++)
	{
		hr = parentContainer->EnumChildContainerNames(dwChildIndex, wszChildName, 256); //get the IdxContainer Child's name		
		std::string container_name = WChar_to_string(wszChildName);
		
		//end of creation
		//assert(SUCCEEDED(hr));
		throw_if_failed(hr, "Can not GetNumberOfChildContainers ");
		hr = parentContainer->GetChildContainer(wszChildName, &pChildContainer);
		throw_if_failed(hr, "Can not GetChildContainer ");
		//assert(SUCCEEDED(hr));
		//create a new D3DContainer here:
		/*check if the child container has children*/
		DWORD 	dwCount;
		HRESULT hr = pChildContainer->GetNumberOfChildContainers(&dwCount);
		throw_if_failed(hr, "Can not GetNumberOfChildContainers ");
		std::shared_ptr<Container> d3d_child;
		
		d3d_child = std::make_shared<Container>(container_name);
		
		//end of checking children container of pChildContainer		

		// recursive traverse with pChildContainer and d3d_child.		
		traverse(pChildContainer, d3d_child);
		//assert(SUCCEEDED(hr));
		SAFE_RELEASE(pChildContainer);
		parent->add_child_container(d3d_child);
	}
	//adding list of property into Parent container
	//int nbProperties = 0;
	hr = parentContainer->GetNumberOfProps(&dwPropCount);
	throw_if_failed(hr, "Can not GetNumberOfProps ");
	for (auto idx = 0; idx < dwPropCount; ++idx) {
		hr = parentContainer->EnumPropNames(idx, wszPropName, 256); //get the IdxContainer Child's name
		throw_if_failed(hr, "Can not EnumPropNames ");
		auto prop_value = get_property_value(parentContainer, wszPropName);
		auto prop_name = WChar_to_string(wszPropName);
		parent->add_property(prop_name, prop_value);
	}

	

}





