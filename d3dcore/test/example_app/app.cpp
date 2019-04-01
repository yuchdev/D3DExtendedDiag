#include <d3dcore/d3d_core.h>

#include <iostream>

using namespace d3dcore;
using std::wcout;
using std::wcerr;


void print_direct3d_param(const wchar_t* path, const std::wstring& value)
{

}

int main(int argc, char* argv[])
{
    D3DInfo d3d_info;
    d3d_info.traverse();
    return 0;
}
