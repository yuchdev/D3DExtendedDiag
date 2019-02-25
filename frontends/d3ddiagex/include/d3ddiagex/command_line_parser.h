#pragma once
#include <memory>
#include <string>
#include <boost/program_options.hpp>

// The header contains command-line parser for the SMBIOS command line utility
// It uses Boost.ProgramOptions

namespace d3ddiagex {

/// @brief Storage for all passed and default command-line params
class CommandLineParams {
public:

    /**@brief Should have a constructor by default */
    CommandLineParams();

    /**@brief Parse raw command-line parameters */
    void read_params(int argc, char* argv[]);

    /**@brief Set some logical param */
    void set_flag(const boost::program_options::variables_map& vm, bool& flag, const char* str);

    /**@brief Get available options list*/
    boost::program_options::options_description& options_descript(){ return cmd_options_description; }

    // Accessors

    bool is_help() const{
        return _help;
    }

    bool is_version() const {
        return _version;
    }


private:

    /// Show help
    bool _help = false;

    /// Show version
    bool _version = false;

    /// Command-line params description
    boost::program_options::options_description cmd_options_description;
};

} // namespace smbios
