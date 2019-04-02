#include <d3dcore/d3d_core.h>

#include <iostream>

using namespace d3dcore;
using std::wcout;
using std::wcerr;


void print_direct3d_param(const wchar_t* container_name, const wchar_t* property_name, const std::wstring& property_value)
{
    if (container_name) {
        wcout << container_name << '.' << property_name << " = " << property_value << '\n';
    }
    else {
        wcout << property_name << " = " << property_value << '\n';
    }

}

int main(int argc, char* argv[])
{
    D3DInfo d3d_info;
    d3d_info.traverse(&print_direct3d_param);
    return 0;
}
