#ifndef __SUBCOMMAND_HPP__
#define __SUBCOMMAND_HPP__

#include <memory>
#include <string>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

class SubCommand
{
public:
  SubCommand( const std::string &host, std::size_t port, const std::string &user, const std::string &password, const std::string &database, const std::string &collection );

private:
  std::shared_ptr<mongocxx::client> client_;
  std::shared_ptr<mongocxx::instance> instance_;
};

#endif
