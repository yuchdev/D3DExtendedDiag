#include <Windows.h>
#include <dxdiag.h>

#include <d3dcore/d3d_core.h>
#include <d3dcore/resource.h>

#include <stdexcept>

using namespace d3dcore;

void throw_if_failed(HRESULT hr, const char* msg)
{
    if (FAILED(hr))
        throw std::runtime_error(msg);
}


D3DInfo::D3DInfo()
{
    HRESULT hr;

    hr = CoInitialize(NULL);
    throw_if_failed(hr, "Can not CoInitialize() COM");

    hr = CoCreateInstance(CLSID_DxDiagProvider,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IDxDiagProvider,
        (LPVOID*)&m_dxdiag_provider);

    throw_if_failed(hr, "Can not CoCreateInstance CLSID_DxDiagProvider");

    DXDIAG_INIT_PARAMS dxDiagInitParam;
    ZeroMemory(&dxDiagInitParam, sizeof(DXDIAG_INIT_PARAMS));

    dxDiagInitParam.dwSize = sizeof(DXDIAG_INIT_PARAMS);
    dxDiagInitParam.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
    dxDiagInitParam.bAllowWHQLChecks = true;
    dxDiagInitParam.pReserved = NULL;

    hr = m_dxdiag_provider->Initialize(&dxDiagInitParam);
    throw_if_failed(hr, "Can not Initialize DXDIAG_INIT_PARAMS ");
}


#if 0
std::string D3DInfo::get_property_value(IDxDiagContainer* dxContainer, WCHAR* propName)
{
    HRESULT hr{};
    VARIANT var{};
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

    default: result = std::string("Default Value");

    }
    VariantClear(&var);

    return result;
}

void D3DInfo::traverse(IDxDiagContainer* parent_container, std::shared_ptr<Container> parent)
{
    IDxDiagContainer*	pChildContainer;
    DWORD 	dwChildCount;
    DWORD 	dwPropCount;
    DWORD	dwChildIndex;
    WCHAR	wszChildName[256];
    WCHAR	wszPropName[256];

    HRESULT hr = parent_container->GetNumberOfChildContainers(&dwChildCount);
    throw_if_failed(hr, "Can not GetNumberOfChildContainers ");


    for (dwChildIndex = 0; dwChildIndex < dwChildCount; dwChildIndex++)
    {
        hr = parent_container->EnumChildContainerNames(dwChildIndex, wszChildName, 256); //get the IdxContainer Child's name		
        std::string container_name = WChar_to_string(wszChildName);

        throw_if_failed(hr, "Can not GetNumberOfChildContainers ");
        hr = parent_container->GetChildContainer(wszChildName, &pChildContainer);
        throw_if_failed(hr, "Can not GetChildContainer ");

        /*check if the child container has children*/
        DWORD 	dwCount;
        HRESULT hr = pChildContainer->GetNumberOfChildContainers(&dwCount);
        throw_if_failed(hr, "Can not GetNumberOfChildContainers");
        std::shared_ptr<Container> d3d_child;

        d3d_child = std::make_shared<Container>(container_name);

        //end of checking children container of pChildContainer		

        // recursive traverse with pChildContainer and d3d_child.		
        traverse(pChildContainer, d3d_child);
        SAFE_RELEASE(pChildContainer);
        parent->add_child_container(d3d_child);
    }
    //adding list of property into Parent container

    hr = parent_container->GetNumberOfProps(&dwPropCount);
    throw_if_failed(hr, "Can not GetNumberOfProps ");
    for (auto idx = 0; idx < dwPropCount; ++idx) {
        hr = parent_container->EnumPropNames(idx, wszPropName, 256); //get the IdxContainer Child's name
        throw_if_failed(hr, "Can not EnumPropNames ");
        auto prop_value = get_property_value(parent_container, wszPropName);
        auto prop_name = WChar_to_string(wszPropName);
        parent->add_property(prop_name, prop_value);
    }

}
#endif
