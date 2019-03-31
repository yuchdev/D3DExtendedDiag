#pragma once

class IDxDiagProvider;
class IDxDiagContainer;

namespace d3dcore {

class D3DInfo
{
public:
	
	// Fill out a DXDIAG_INIT_PARAMS struct and pass it to IDxDiagContainer::Initialize
	// Passing in TRUE for bAllowWHQLChecks, allows dxdiag to check if drivers are 
	// digital signed as logo'd by WHQL which may connect via internet to update 
	// WHQL certificates.    
	D3DInfo();
	virtual ~D3DInfo() = default;

private:
	//property
	IDxDiagProvider* m_dxdiag_provider = nullptr;
	IDxDiagContainer* m_dxdiag_rootnullptr;
};

} // namespace d3dcore