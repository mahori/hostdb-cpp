#include "SubCommand.hpp"

using namespace std;

SubCommand::SubCommand( const string &host, size_t port, const string &user, const string &password, const string &database, const string &collection )
{
  instance_ = make_shared<mongocxx::instance>();
}
