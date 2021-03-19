#pragma once
#include <string>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;

struct Employee
{
	int employeeNumber;
	std::string lastName;
	//char lastName[50];
	std::string firstName;
	//char firstName[50];
	std::string extension;
	//char extension[10];
	std::string email;
	//char email[100];
	std::string officeCode;
	//char officecode[10];
	int reportsTo;
	std::string jobTitle;
	//char jobTitle[50];
};

int menu(void);
int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp);

void displayEmployee(Connection* conn, struct Employee emp);
void displayAllEmployee(Connection* conn);

void insertEmployee(struct Employee* emp);
void insertEmployee(Connection* conn, struct Employee emp);

void updateEmployee(Connection* conn, int employeeNumber);
void deleteEmployee(Connection* conn, int employeeNumber);