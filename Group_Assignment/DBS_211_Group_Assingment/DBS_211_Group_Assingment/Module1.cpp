#include <iostream>
#include <string>
#include <cstring>
#include "Module1.h"

using namespace std;

namespace sdds{

	int menu(void){
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

		} while(!valid);

		return selection;
	}

	int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp){
		bool found = false;
		std::string empNum = std::to_string(employeeNumber);

		std::string query = "SELECT employeenumber, lastname, firstname, extension, email, officecode, reportsto, jobtitle FROM employees WHERE employeenumber =";
		query.append(empNum);
		Statement* stmt = conn->createStatement(query);
		ResultSet* rs = stmt->executeQuery();

		if(rs->next())
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
			displayEmployee(emp);

		}

		conn->terminateStatement(stmt);

		return found;
	}
	void displayEmployee(const struct Employee emp){
		std::cout << "\n-------------- Employee Information -------------" << std::endl;
		std::cout << "Employee Number: " << emp->employeeNumber << std::endl;
		std::cout << "Last Name: " << emp->lastName << std::endl;
		std::cout << "First Name: " << emp->firstName << std::endl;
		std::cout << "Extension: " << emp->extension << std::endl;
		std::cout << "Email: " << emp->email << std::endl;
		std::cout << "Office Code: " << emp->officeCode << std::endl;
		std::cout << "Manager ID: " << emp->reportsTo << std::endl;
		std::cout << "Job Title: " << emp->jobTitle << std::endl;
	}
	void displayAllEmployee(Connection* conn){
		try {
			string eeQuery = "SELECT * FROM employee;"; //TODO: Define inquiry
			int num = 0;
			Statement* stmt = conn->createStatement(eeQuery);
			ResultSet* rs = stmt->executeQuery();

			// TODO: displayHeader(1, "Employee");
			// TODO: displayTitle();
			if(!rs->next()) {

				cout << "Result Set is empty." << endl;
			} else {
				do {
					std::cout << "\n------   ---------------   ---------------------------------  ----------------  ---------  -----------------" << std::endl;
					std::cout.setf(ios::left);
					std::cout.width(9);
					std::cout << "ID";
					std::cout.width(18);
					std::cout << "Employee Name";
					std::cout.width(35);
					std::cout << "Email";
					std::cout.width(18);
					std::cout << "Phone";
					std::cout.width(11);
					std::cout << "Extension";
					std::cout << "Manager Name" << std::endl;
				} while(rs->next());

			}

			conn->terminateStatement(stmt);

		} catch(SQLException& sqlExcp) {
			cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
		}


	}

	void insertEmployee(struct Employee* emp){

	}
	void insertEmployee(Connection* conn, struct Employee emp){

	}

	void updateEmployee(Connection* conn, int employeeNumber){

	}
	void deleteEmployee(Connection* conn, int employeeNumber){

	}
}