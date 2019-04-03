#include <d3dcore/d3d_core.h>

#include <boost/property_tree/ptree.hpp>
#include <iostream>

using namespace d3dcore;
using std::wcout;
using std::wcerr;
namespace boost_pt = boost::property_tree;


void fill_direct3d_tree(const wchar_t* container_name, const wchar_t* property_name, const std::wstring& property_value)
{
    // Create empty property tree object
    boost_pt::ptree tree;
    tree.put("DirectX", 10);
}

/// The application just shows simplest usage of Direct3D traverse callback,
/// printing all properties and values
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
