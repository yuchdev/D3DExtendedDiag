#include <list>
#include <d3ddiagex/command_line_parser.h>


using namespace d3ddiagex;
namespace po = boost::program_options;
using std::string;

CommandLineParams::CommandLineParams() : cmd_options_description("Command-line options for D3DDiagEx:")
{}

void CommandLineParams::read_params(int argc, char* argv[])
{
    cmd_options_description.add_options()
        ("help,h", "Print usage")
        ("version,v", "Print version")
        ;

    // command line params processing
    po::variables_map cmd_variables_map;
    po::store(parse_command_line(argc, argv, cmd_options_description), cmd_variables_map);
    po::notify(cmd_variables_map);

    set_flag(cmd_variables_map, _help, "help");
    set_flag(cmd_variables_map, _version, "version");

    // do not check debug flags!
    std::list<bool> mutually_exclusives = { _help, _version };
    size_t options_count = std::count(mutually_exclusives.begin(), mutually_exclusives.end(), true);
    if (options_count > 1){
        throw std::logic_error("Incompatible command line parameters set, use only one");
    }

}

void CommandLineParams::set_flag(const po::variables_map& vm, bool& flag, const char* str)
{
    if (vm.count(str)) {
        flag = true;
    }
}
