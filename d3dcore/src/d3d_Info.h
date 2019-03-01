#pragma once

#define INITGUID
 #include "dxdiag.h"

#include <string>
#include <memory>

namespace d3dcore {

	class ComplexContainer;

	class D3DInfo
	{
	public:
		D3DInfo();
		~D3DInfo();

		
		

	private:
		//property
		IDxDiagProvider* m_pDxDiagProvider;
		IDxDiagContainer* m_pDxDiagRoot;
		std::shared_ptr<ComplexContainer> m_rootContainer;
		//private method
		std::string GetPropertyValue(IDxDiagContainer* dxContainer, WCHAR* propName); //todo: update with sdt::any
		std::string WCharToString(WCHAR* wChar);
	public:
		HRESULT Init(int dxVersion = DXDIAG_DX9_SDK_VERSION);
		HRESULT Traverse(IDxDiagContainer*);
		void GetInfo();
	};
}


