#include <iostream>
#include <string>
#include <d3ddiagex/command_line_parser.h>

using namespace std;
using namespace d3ddiagex;

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
    }
    // boost::program_options exception reports
    // about wrong command line parameters usage
    catch (const boost::program_options::error& e) {
        cout << "Program option error: " << e.what() << endl;
        cout << get_params().options_descript() << endl;
        usage();
    }

    return 0;
}
