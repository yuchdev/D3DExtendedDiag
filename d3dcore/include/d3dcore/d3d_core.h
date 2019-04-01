#pragma once
#include <string>

class IDxDiagProvider;
class IDxDiagContainer;

namespace d3dcore {

/// @brief Provide Windows-specific information about Direct3D (same as DirectX) subsystem
/// All the information is organized in a hierarchical tree-like structure,
/// so it is fetched by traversing callback
class D3DInfo
{
public:
	
    /// @brief Fill out a DXDIAG_INIT_PARAMS struct and pass it to IDxDiagContainer::Initialize
	/// Passing in TRUE for bAllowWHQLChecks, allows DxDiag to check if drivers are 
	/// digital signed. It may connect via internet to update WHQL certificates.    
	D3DInfo();

    /// @brief
    /// Release IDxDiagProvider and IDxDiagContainer interfaces
	virtual ~D3DInfo();

    void traverse();
    void traverse_container(const wchar_t* parent_container_name, IDxDiagContainer* dxdiag_current_container);

private:

	IDxDiagProvider* m_dxdiag_provider = nullptr;
	IDxDiagContainer* m_dxdiag_root = nullptr;
};

} // namespace d3dcore