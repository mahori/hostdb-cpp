#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include "SubCommand.hpp"

using namespace std;

namespace po = boost::program_options;

static const char * const OPTION_HELP       = "help";
static const char * const OPTION_HOST       = "host";
static const char * const OPTION_PORT       = "port";
static const char * const OPTION_USER       = "user";
static const char * const OPTION_PASSWORD   = "password";
static const char * const OPTION_DATABASE   = "database";
static const char * const OPTION_COLLECTION = "collection";
static const char * const OPTION_SUBCOMMAND = "subcommand";
static const char * const OPTION_ARGS       = "arguments";

int main( int argc, char **argv )
{
  po::options_description options( "options" );
  options.add_options()
    ( OPTION_HELP,                                                          OPTION_HELP       )
    ( OPTION_HOST,       po::value<string>()->default_value( "localhost" ), OPTION_HOST       )
    ( OPTION_PORT,       po::value<size_t>()->default_value( 27017 ),       OPTION_PORT       )
    ( OPTION_USER,       po::value<string>()->default_value( "" ),          OPTION_USER       )
    ( OPTION_PASSWORD,   po::value<string>()->default_value( "" ),          OPTION_PASSWORD   )
    ( OPTION_DATABASE,   po::value<string>(),                               OPTION_DATABASE   )
    ( OPTION_COLLECTION, po::value<string>(),                               OPTION_COLLECTION )
    ( OPTION_SUBCOMMAND, po::value<string>(),                               OPTION_SUBCOMMAND )
    ( OPTION_ARGS,       po::value<vector<string>>(),                       OPTION_ARGS       );

  po::positional_options_description positional;
  positional.add( OPTION_SUBCOMMAND, 1 );
  positional.add( OPTION_ARGS,      -1 );

  po::variables_map variables;

  try {
    po::command_line_parser parser( argc, argv );

    parser.options( options );
    parser.positional( positional );

    po::store( parser.run(), variables );
  }
  catch ( po::invalid_option_value &e ) {
    cerr << options << endl;
    return -1;
  }

  po::notify( variables );

  if ( variables.count( OPTION_HELP ) > 0
       || variables.count( OPTION_DATABASE   ) < 1
       || variables.count( OPTION_COLLECTION ) < 1
       || variables.count( OPTION_SUBCOMMAND ) < 1 ) {
    cerr << options << endl;
    return 1;
  }

  string host       = variables[OPTION_HOST].as<string>();
  size_t port       = variables[OPTION_PORT].as<size_t>();
  string user       = variables[OPTION_USER].as<string>();
  string password   = variables[OPTION_PASSWORD].as<string>();
  string database   = variables[OPTION_DATABASE].as<string>();
  string collection = variables[OPTION_COLLECTION].as<string>();
  string subcommand = variables[OPTION_SUBCOMMAND].as<string>();

  vector<string> args;
  if ( variables.count( OPTION_ARGS ) > 0 ) {
    args = variables[OPTION_ARGS].as<vector<string>>();
  }

  try {
    SubCommand subcommand( host, port, user, password, database, collection );
  }
  catch ( invalid_argument &e ) {
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}
