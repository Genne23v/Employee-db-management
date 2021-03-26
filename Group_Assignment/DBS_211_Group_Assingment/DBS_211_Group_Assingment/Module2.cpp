#include <iostream>
#include <string>
#include <cstring>
#include "Module1.h"

using namespace std;

namespace sdds
{
	void updateEmployee(Connection* conn, int employeeNumber) 
	{
		/*
			\ updates the phone extension for the given employee.
			If employee does exist, display the employee’s last nameand first nameand then ask the
			user to enter the new phone extension.Store the new extension in table employees for the given
			employee number.*/
		try {
			Statement* stmt = conn->createStatement();

			stmt->executeUpdate();

			conn->commit();
			conn->terminateStatement(stmt);
		}
		catch (SQLException& sqlExcp) {
			std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
		}
	}
	
}