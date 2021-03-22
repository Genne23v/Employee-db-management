#include <iostream>
#include <string>
#include <cstring>
#include "Module1.h"

int menu(void)
{
	int selection = 0;
	bool valid = true;
	
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

		if(std::cin.fail() || ( selection < 1 && selection > 5 )){
			std::cout << "Invalid selection, please re-enter" << std::endl;
			valid == false;
			//Clears input buffer
			std::cin.ignore(10000, '\n');
			std::cin.clear();
		}

	} while (!valid);

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
	cout << "\n-------------- Employee Information -------------" << endl;
	cout << "Employee Number: " << emp.employeeNumber << endl;
	cout << "Last Name: " << emp.lastName << endl;
	cout << "First Name: " << emp.firstName << endl;
	cout << "Extension: " << emp.extension << endl;
	cout << "Email: " << emp.email << endl;
	cout << "Office Code: " << emp.officeCode << endl;
	cout << "Manager ID: " << emp.reportsTo << endl;
	cout << "Job Title: " << emp.jobTitle << endl << endl;
}
void displayAllEmployee(Connection* conn) {
		try {
			string eeQuery = "";
			string type = "";
			int num = 0;
			Statement* stmt = conn->createStatement(eeQuery);
			ResultSet* rs = stmt->executeQuery();
			/* Statment Variables */
			displayHeader(1, "Employee");
			displayTitle();
			if(!rs->next()) {
				// if the result set is empty
				cout << "Result Set is empty." << endl;
			} else {
				do {
					displayOutput(rs);
				} while(rs->next());

			}

			conn->terminateStatement(stmt);

		} catch(SQLException& sqlExcp) {
			cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
		}


		if(!rs->next())
		{
			// display message if query does not return any rows
			cout << "There is no employees' information to be displayed." << endl;
		} else
		{
			cout << "\n------   ---------------   ---------------------------------  ----------------  ---------  -----------------" << endl;
			cout.setf(ios::left);
			cout.width(9);
			cout << "ID";
			cout.width(18);
			cout << "Employee Name";
			cout.width(35);
			cout << "Email";
			cout.width(18);
			cout << "Phone";
			cout.width(11);
			cout << "Extension";
			cout << "Manager Name" << endl;

			cout << "------   ---------------   ---------------------------------  ----------------  ---------  -----------------" << endl;
			do
			{
				cout.setf(ios::left);
				cout.width(9);
				cout << rs->getInt(1);
				cout.width(18);
				cout << rs->getString(2);
				cout.width(35);
				cout << rs->getString(3);
				cout.width(18);
				cout << rs->getString(4);
				cout.width(11);
				cout << rs->getString(5);
				cout << rs->getString(6) << endl;

			} while(rs->next());
			cout << endl;
		}


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