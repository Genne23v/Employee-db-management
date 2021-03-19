#include <iostream>
#include <string>
#include <cstring>
#include "Module1.h"

int menu(void)
{
	int selection;
	bool valid = false;

	do
	{
		std::cout << "********************* HR Menu *********************" << std::endl;
		std::cout << "1) Find Employee" << std::endl;
		std::cout << "2) Employees Report" << std::endl;
		std::cout << "3) Add Employee" << std::endl;
		std::cout << "4) Update Employee" << std::endl;
		std::cout << "5) Remove Employee" << std::endl;
		std::cout << "0) Exit" << std::endl;
		std::cout << "Enter an option (0-5): ";
		std::cin >> selection;

		if (selection >= 0 && selection <= 5)
		{
			valid = true;
		}
		else
		{
			std::cout << "Invalid selection, please re-enter" << std::endl;
		}

	} while (valid != true);

	return selection;
}

int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp)
{
	bool found = false;
	std::string empNum = std::to_string(employeeNumber);

	std::string query = "SELECT employeenumber, lastname, firstname, extension, email, officecode, reportsto, jobtitle FROM employees WHERE employeenumber =";
	query.append(empNum);
	Statement* stmt = conn->createStatement(query);
	ResultSet* rs = stmt->executeQuery();

	if (rs->next())
	{
		found = true;

		emp->employeeNumber = rs->getInt(1);
		emp->lastName = rs->getString(2);
		//strcpy(emp->lastName, result->getString(2));
		emp->firstName = rs->getString(3);
		emp->extension = rs->getString(4);
		emp->email = rs->getString(5);
		emp->officeCode = rs->getString(6);
		emp->reportsTo = rs->getInt(7);
		emp->jobTitle = rs->getString(8);

		std::cout << "-------------- Employee Information -------------" << std::endl;
		std::cout << "Employee Number: " << emp->employeeNumber << std::endl;
		std::cout << "Last Name: " << emp->lastName << std::endl;
		std::cout << "First Name: " << emp->firstName << std::endl;
		std::cout << "Extension: " << emp->extension << std::endl;
		std::cout << "Email: " << emp->email << std::endl;
		std::cout << "Office Code: " << emp->officeCode << std::endl;
		std::cout << "Manager ID: " << emp->reportsTo << std::endl;
		std::cout << "Job Title: " << emp->jobTitle << std::endl;
	}

	conn->terminateStatement(stmt);

	return found;
}

void displayEmployee(Connection* conn, struct Employee emp)
{

}
void displayAllEmployee(Connection* conn)
{

}

void insertEmployee(struct Employee* emp)
{

}
void insertEmployee(Connection* conn, struct Employee emp)
{

}

void updateEmployee(Connection* conn, int employeeNumber)
{

}
void deleteEmployee(Connection* conn, int employeeNumber)
{

}