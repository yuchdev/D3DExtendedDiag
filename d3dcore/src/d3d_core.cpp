#include <d3dcore/d3d_core.h>

#include <Windows.h>
#include <dxdiag.h>
#include <stdexcept>
#include <cassert>
#include <sstream>

using namespace d3dcore;


namespace {

void throw_if_failed(HRESULT hr, const char* msg)
{
    if (FAILED(hr))
        throw std::runtime_error(msg);
}

std::wstring variant_to_string(const VARIANT& variant)
{
    std::wstring result;
    switch (variant.vt)
    {
    case VT_UI4:
        result = std::to_wstring(variant.intVal);
        break;
    case VT_I4:
        result = std::to_wstring(variant.uintVal);
        break;
    case VT_BOOL:
        result = variant.boolVal != 0 ? std::wstring(L"true") : std::wstring(L"false");
        break;
    case VT_BSTR:
        assert(variant.bstrVal != nullptr);
        result = std::wstring(variant.bstrVal, SysStringLen(variant.bstrVal));
        break;
    default:
        result = L"undefined type";
    }
    return result;
}

} // namespace




D3DInfo::D3DInfo()
{
    HRESULT hr = CoInitialize(NULL);
    throw_if_failed(hr, "Can not CoInitialize() COM");

    hr = CoCreateInstance(CLSID_DxDiagProvider,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IDxDiagProvider,
        (LPVOID*)&m_dxdiag_provider);

    throw_if_failed(hr, "Can not CoCreateInstance CLSID_DxDiagProvider");

    DXDIAG_INIT_PARAMS dxdiag_init_params;
    ZeroMemory(&dxdiag_init_params, sizeof(DXDIAG_INIT_PARAMS));

    dxdiag_init_params.dwSize = sizeof(DXDIAG_INIT_PARAMS);
    dxdiag_init_params.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
    dxdiag_init_params.bAllowWHQLChecks = true;
    dxdiag_init_params.pReserved = NULL;

    hr = m_dxdiag_provider->Initialize(&dxdiag_init_params);
    throw_if_failed(hr, "Can not Initialize DXDIAG_INIT_PARAMS");

    hr = m_dxdiag_provider->GetRootContainer(&m_dxdiag_root);
    throw_if_failed(hr, "Can not Initialize DXDIAG_INIT_PARAMS");
}

D3DInfo::~D3DInfo()
{
    m_dxdiag_root->Release();
    m_dxdiag_provider->Release();
}

void D3DInfo::traverse(traverse_callback_t callback)
{
    traverse_container(callback, nullptr, m_dxdiag_root);
}

void D3DInfo::traverse_container(traverse_callback_t callback, const wchar_t* parent_container_name, IDxDiagContainer* dxdiag_current_container)
{
    DWORD container_properties_count{};
    WCHAR property_name[256] = {};
    VARIANT property_value;
    VariantInit(&property_value);

    HRESULT hr = dxdiag_current_container->GetNumberOfProps(&container_properties_count);
    
    // 1.Read current container properties
    if( SUCCEEDED(hr) )
    {
        // Print each property in this container
        for (DWORD property_index = 0; property_index < container_properties_count; ++property_index)
        {
            hr = dxdiag_current_container->EnumPropNames(property_index, property_name, 256);
            if( SUCCEEDED( hr ) )
            {
                hr = dxdiag_current_container->GetProp(property_name, &property_value);
                if( SUCCEEDED( hr ) )
                {
                    std::wstring result = variant_to_string(property_value);

                    // Add the parent name to the front if there's one, so that
                    // its easier to read on the screen
                    callback(parent_container_name, property_name, result);
                    
                    // Clear the variant (this is needed to free BSTR memory)
                    VariantClear(&property_value);
                }
            }
        }
    }

    // 2.Recursively call this function for each of its child containers
    DWORD children_container_count{};
    WCHAR child_container_name[256] = {};
    IDxDiagContainer* child_container = nullptr;
    hr = dxdiag_current_container->GetNumberOfChildContainers(&children_container_count);
    if( SUCCEEDED(hr) )
    {
        for (DWORD child_index = 0; child_index < children_container_count; ++child_index)
        {
            hr = dxdiag_current_container->EnumChildContainerNames(child_index, child_container_name, 256);
            if( SUCCEEDED( hr ) )
            {
                hr = dxdiag_current_container->GetChildContainer(child_container_name, &child_container);
                if( SUCCEEDED( hr ) )
                {
                    // wszFullChildName isn't needed but is used for text output
                    std::wostringstream child_name;
                    if (parent_container_name) {
                        child_name << parent_container_name << '.' << child_container_name;
                    }
                    else {
                        child_name << child_container_name;
                    }
                    traverse_container(callback, child_name.str().c_str(), child_container);

                    child_container->Release();
                }
            }
        }
    }

}

