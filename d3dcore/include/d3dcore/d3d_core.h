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

    /// @brief traverse_callback_t(const wchar_t* path, const std::wstring& value)
    /// "path" is hierarchical path, where child containers are separated with "." symbol,
    /// "value" is a value string representation
    using traverse_callback_t = void(*)(const wchar_t*, const std::wstring&);

    /// @brief Fill out a DXDIAG_INIT_PARAMS struct and pass it to IDxDiagContainer::Initialize
    /// Passing in TRUE for bAllowWHQLChecks, allows DxDiag to check if drivers are 
    /// digital signed. It may connect via internet to update WHQL certificates.    
    D3DInfo();

    /// @brief Release IDxDiagProvider and IDxDiagContainer interfaces
    virtual ~D3DInfo();

    /// @brief Traverse over Direct3D containers and perform callback for every path and value
    /// @param callback: function with has prototype callback(const wchar_t* path, const std::wstring& value),
    /// where "path" is hierarchical path, where child containers are separated with "." symbol,
    /// and "value" is a value string representation
    void traverse(traverse_callback_t callback);

private:

    /// param callback: callback function to be performed for every D3D parameter
    /// param parent_container_name: name of D3D container, NULL for root
    /// param dxdiag_current_container: pointer for current D3D container, so that process its own properties
    /// and recursively call his children
    void traverse_container(traverse_callback_t callback, const wchar_t* parent_container_name, IDxDiagContainer* dxdiag_current_container);

    /// Direct3D Provider
    IDxDiagProvider* m_dxdiag_provider = nullptr;

    /// Direct3D root container
    IDxDiagContainer* m_dxdiag_root = nullptr;
};

} // namespace d3dcore