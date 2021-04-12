#pragma once
#include <string>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

#ifndef SDDS_MODULE1_H
#define SDDS_MODULE1_H
namespace sdds{
	struct Employee
	{
		int employeeNumber;
		char lastName[50];
		char firstName[50];
		char extension[10];
		char email[100];
		char officecode[10];
		int reportsTo;
		char jobTitle[50];
	};

	int menu(void);
	int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp);

	void displayEmployee(struct Employee emp);
	void displayAllEmployee(Connection* conn);

	void insertEmployee(struct Employee* emp);
	void insertEmployee(Connection* conn, struct Employee emp);

	void updateEmployee(Connection* conn, int employeeNumber);
	void deleteEmployee(Connection* conn, int employeeNumber);
}
#endif // !SDDS_MODULE1_H