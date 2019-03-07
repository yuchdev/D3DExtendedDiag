#include <iostream>
#include <string>
#include <exception>
#include <d3ddiagex/command_line_parser.h>

#include "d3dcore/d3d_info.h"
#include "system3d_info/console_visitor.h"
#include "system3d_info/graphic_container.h"


#include <boost/program_options.hpp>

using namespace std;
using namespace d3ddiagex;
using namespace system3d_info;
using namespace d3dcore;

static CommandLineParams& get_params()
{
    static CommandLineParams p;
    return p;
}

void usage()
{
    cout << get_params().options_descript() << endl;
    exit(EXIT_SUCCESS);
}


void print_version()
{
    // TODO: add version
    cout << "version" << endl;
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]){

    setlocale(0, "");
	

    try {
        get_params().read_params(argc, argv);
        const CommandLineParams& cmd_line_params = get_params();

        if (cmd_line_params.is_help()) {
            usage();
        }

        if (cmd_line_params.is_version()) {
            print_version();
        }
        // TODO: Add application code here
		std::cout << "Display Information of DirectX!\n";
		std::cout << "Waiting........" << std::endl;

		d3dcore::D3DInfo<system3d_info::GraphicContainer> d3dInfo;
		ConsoleVisitor console_visitor;
		d3dInfo.init();
		d3dInfo.query_info();

		auto rootContainer = d3dInfo.get_root_container();
		rootContainer->accept(console_visitor);

		std::cout << "DONE!!!!!!!!!!!!!!!!" << std::endl;

    }
    // boost::program_options exception reports
    // about wrong command line parameters usage
    catch (const boost::program_options::error& e) {
        cout << "Program option error: " << e.what() << endl;
        cout << get_params().options_descript() << endl;
        usage();
    }
	catch (std::system_error& e)
	{
		std::cout << "ERROR: " << e.what() << "\nError code: " << e.code() << "\n";
	}


    return 0;
}
