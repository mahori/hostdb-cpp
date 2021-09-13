#include "SubCommand.hpp"
#include <curl/curl.h>
#include <boost/format.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using namespace std;

namespace
{

string encode_password( const string &password )
{
  string result;

  CURL *curl = ::curl_easy_init();
  if ( curl ) {
    char *encode = ::curl_easy_escape( curl, password.c_str(), password.length() );
    if ( encode ) {
      result.assign( encode );
      ::curl_free( encode );
    }
    curl_easy_cleanup( curl );
  }

  return result;
}

string connection_string( const string &host, size_t port, const string &user, const string &password )
{
  boost::format format;
  if ( user.empty() || password.empty() ) {
    format = boost::format( "mongodb://%1%:%2%" ) % host % port;
  } else {
    format = boost::format( "mongodb://%s:%s@%s:%s" ) % user % password % host % port;
  }

  return format.str();
}

}

SubCommand::SubCommand( const string &host, size_t port, const string &user, const string &password, const string &database, const string &collection )
{
  string encode;
  if ( !password.empty() ) {
    encode = ::encode_password( password );
  }

  string connection_string = ::connection_string( host, port, user, encode );

  mongocxx::uri uri( connection_string );

  instance_ = make_shared<mongocxx::instance>();
  client_   = make_shared<mongocxx::client>( uri );
}
