#pragma once

#include "../Core/Active.h"

#include "QueryResult.h"

DEFINE_LOGGED_EXCEPTION(DatabaseException);

class DatabaseConnection
{
public:
	DatabaseConnection(
		std::string host,
		s16 port,
		std::string username,
		std::string password,
		std::string database
	);

	DatabaseConnection& operator=(const DatabaseConnection&) = delete;
	DatabaseConnection(const DatabaseConnection&) = delete;

	DatabaseConnection& operator=(DatabaseConnection&& other);
	DatabaseConnection(DatabaseConnection&& other);

	~DatabaseConnection();

	void NonQueryBackground(const std::string& queryString);
	void NonQuery(const std::string& queryString);
	QueryResult Query(const std::string& queryString);

	//returns error messages
	const char* Error();

	//returns the number of rows e.g. returned by a SELECT
	u32 AffectedRows();

	size_t NumPendingQueries() const { return _pActive->NumPending(); }

private:
	void connect();

	std::unique_ptr<Active> _pActive;
	std::recursive_mutex _dbMutex;

	std::string _host;
	s16 _port;
	std::string _username;
	std::string _password;
	std::string _database;

	bool _isInitialized = false;
	MYSQL _mySQL;
};
