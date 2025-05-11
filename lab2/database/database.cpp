#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Data/SessionPool.h>

#include "database.h"
#include "config.h"

namespace database {
Database::Database() {
    _connection_string += "host=";
    _connection_string += Config::get().get_host();
    _connection_string += " user=";
    _connection_string += Config::get().get_login();
    _connection_string += " dbname=";
    _connection_string += Config::get().get_database();
    _connection_string += " port=";
    _connection_string += Config::get().get_port();
    _connection_string += " password=";
    _connection_string += Config::get().get_password();

    // Параметры таймаута
    _connection_string += " connect_timeout=3"; // 3 секунды
    _connection_string += " keepalives_idle=30";
    _connection_string += " keepalives_interval=10";
    _connection_string += " keepalives_count=3";                                           

    std::cout << "Connection string:" << _connection_string << std::endl;
    Poco::Data::PostgreSQL::Connector::registerConnector();
    _pool = std::make_unique<Poco::Data::SessionPool>(Poco::Data::PostgreSQL::Connector::KEY, _connection_string);
}

Database& Database::get() {
    static Database _instance;
    return _instance;
}

Poco::Data::Session Database::create_session() {
    if (!_pool) {
        throw std::runtime_error("Session pool is not initialized");
    }
    return _pool->get();
}

Poco::Data::Session Database::get_session() {
    if (!_pool) {
        throw std::runtime_error("Session pool is not initialized");
    }
    return _pool->get();
}
}  // namespace database
