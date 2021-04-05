#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
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
				valid = false;
				//Clears input buffer
				std::cin.ignore(10000, '\n');
				std::cin.clear();
			}

		} while(!valid);

		return selection;
	}

	int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp){
		bool found = false;
		//Employee ptrCvt;
		std::string empNum = std::to_string(employeeNumber);

		std::string query = "SELECT employeenumber, lastname, firstname, extension, email, officecode, reportsto, jobtitle FROM employees2 WHERE employeenumber =";
		query.append(empNum);
		Statement* stmt = conn->createStatement(query);
		ResultSet* rs = stmt->executeQuery();

		if(rs->next())
		{
			found = true;

			emp->employeeNumber = rs->getInt(1);
			strcpy(emp->lastName, rs->getString(2).c_str());
			strcpy(emp->firstName, rs->getString(3).c_str());
			strcpy(emp->extension, rs->getString(4).c_str());
			strcpy(emp->email, rs->getString(5).c_str());
			strcpy(emp->officecode, rs->getString(6).c_str());
			emp->reportsTo = rs->getInt(7);
			strcpy(emp->jobTitle, rs->getString(8).c_str());
			
			//ptrCvt = *emp;
			//displayEmployee(conn, ptrCvt);
		}

		conn->terminateStatement(stmt);

		return found;
	}
	void displayEmployee(Connection *conn, struct Employee emp){
		//WHAT IS THIS conn FOR?
		std::cout << "\n-------------- Employee Information -------------" << std::endl;
		std::cout << "Employee Number: " << emp.employeeNumber << std::endl;
		std::cout << "Last Name: " << emp.lastName << std::endl;
		std::cout << "First Name: " << emp.firstName << std::endl;
		std::cout << "Extension: " << emp.extension << std::endl;
		std::cout << "Email: " << emp.email << std::endl;
		std::cout << "Office Code: " << emp.officecode << std::endl;
		std::cout << "Manager ID: " << emp.reportsTo << std::endl;
		std::cout << "Job Title: " << emp.jobTitle << std::endl;
		std::cout << endl;
	}
	void displayHeader() {
		std::cout << "------   ---------------   ---------------------------------  ----------------  ---------  -----------------" << std::endl;
		std::cout << "ID       Employee Name     Email                              Phone             Extension  Manager Name     " << std::endl;
		std::cout << "------   ---------------   ---------------------------------  ----------------  ---------  -----------------" << std::endl;
	}
	void displayAllEmployee(Connection* conn){
		try {
			string eeQuery = "SELECT emp.employeenumber, emp.firstname || ' ' || emp.lastname, emp.email, phone, emp.extension, mgr.firstname || ' ' || mgr.lastname FROM employees2 emp LEFT JOIN employees2 mgr ON emp.reportsto = mgr.employeenumber JOIN offices ofc ON ofc.officecode = emp.officecode ORDER BY 1"; //TODO: Define inquiry
			Statement* stmt = conn->createStatement(eeQuery);
			ResultSet* rs = stmt->executeQuery();

			// TODO: displayHeader(1, "Employee");
			// TODO: displayTitle();
			if(!rs->next()) {

				cout << "Result Set is empty." << endl;
			} else {
				displayHeader();
				do {
					
					cout << left << setw(9) << rs->getInt(1) << setw(18) << rs->getString(2) << setw(35) << rs->getString(3) << setw(18) << rs->getString(4) << setw(11) << rs->getString(5) << setw(20) << rs->getString(6) << endl;

				} while(rs->next());
				cout << endl;
			}

			conn->terminateStatement(stmt);

		} catch(SQLException& sqlExcp) {
			cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
		}


	}
	
	void deleteEmployee(Connection* conn, int employeeNumber)
	{
		struct Employee emp;
		if(findEmployee(conn, employeeNumber, &emp) == 1)
		{
			Statement* stmt = conn->createStatement();
			try{
				
				stmt->setSQL("DELETE FROM employees2 WHERE employeenumber=:1");
				stmt->setInt(1, emp.employeeNumber);
				stmt->executeUpdate();
				conn->commit();
			} catch(SQLException& sqlExcp) {
				std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
			}
				conn->terminateStatement(stmt);

			cout << "The employee with ID " << employeeNumber << " is deleted successfully." << endl << endl;
		} else
		{
			cout << "The employee with ID " << employeeNumber << " does not exist." << endl << endl;
		}

	}
}