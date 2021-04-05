#include <iostream>
#include <string>
#include <cstring>
#include "Module1.h"

using namespace std;

namespace sdds
{
	void insertEmployee(struct Employee* emp)
	{
		//TODO: INPUT VALIDATION
		cout << "Employee Number: ";
		cin >> emp->employeeNumber;
		cout << "Last Name: ";
		cin >> emp->lastName;
		cout << "First Name: ";
		cin >> emp->firstName;
		cout << "Extension: ";
		cin >> emp->extension;
		cout << "Email: ";
		cin >> emp->email;
		cout << "Office Code: ";
		cin >> emp->officecode;
		cout << "Manager ID: ";
		cin >> emp->reportsTo;
		cout << "Job Title: ";
		cin >> emp->jobTitle;

		//cout << "The new employee is added successfully." << endl;
	}

	void insertEmployee(Connection* conn, struct Employee emp)
	{
		bool found = true;

		if (findEmployee(conn, emp.employeeNumber, &emp))
		{
			std::cout << "\nAn employee with the same employee number exists." << endl << endl;
		}
		else
		{
			found = false;
		}

		if (found == false) {
			try {
				Statement* stmt = conn->createStatement();
				stmt->setSQL("INSERT INTO employees2 VALUES(:1,:2,:3,:4,:5,:6,:7,:8)");
				stmt->setInt(1, emp.employeeNumber);
				stmt->setString(2, emp.lastName);
				stmt->setString(3, emp.firstName);
				stmt->setString(4, emp.extension);
				stmt->setString(5, emp.email);
				stmt->setString(6, emp.officecode);
				stmt->setInt(7, emp.reportsTo);
				stmt->setString(8, emp.jobTitle);

				stmt->executeUpdate();
				conn->commit();
				std::cout << "\nThe new employee is added successfully. " << endl << endl;

				conn->terminateStatement(stmt);

			}
			catch (SQLException& sqlExcp) {
				std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
			}
		}

	}

	void updateEmployee(Connection* conn, int employeeNumber)
	{
		try {
			std::string empNum = std::to_string(employeeNumber);
			std::string ext; 

			cout << "Last Name: " << endl;
			cout << "First Name: " << endl;
			cout << "Extension: ";
			cin >> ext;

			std::string query = "UPDATE employees2 SET extension = '";
			query.append(ext);
			std::string queryEnding = "' WHERE employeenumber =";
			query.append(queryEnding);
			query.append(empNum);
			
			Statement* stmt = conn->createStatement(query);
			stmt->executeUpdate();
			conn->commit();

			cout << "The employee's extension is updated successfully." << endl << endl;

			conn->terminateStatement(stmt);
		}
		catch (SQLException& sqlExcp) {
			std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
		}
	}
}