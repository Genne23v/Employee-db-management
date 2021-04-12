#include <iostream>
#include <occi.h>
#include "Module1.h"

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;
using namespace sdds;

int main(void) {
	Environment* env = nullptr;
	Connection* conn = nullptr;
	
	string user = "dbs211_211h23"; //this is the login assigned to you
	string pass = "58214007"; //this is the password assigned to you
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try {	
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, srv);

		int selection = 0;
		Employee *emp = new Employee;
		Employee ptrCvt;

		do
		{
			selection = menu();
			int empNum = 0;
		
			switch (selection)
			{
			case 0:
				std::cout << "Thank you, good bye!" << std::endl;
				break;
			case 1:
				cout << "Enter Employee Number: ";
				cin >> empNum;
				if (findEmployee(conn, empNum, emp))
				{
					
					displayEmployee(*emp);
				}
				else 
				{
					cout << "Employee " << empNum << " does not exist." << endl << endl;
				}
				break;
			case 2:
				displayAllEmployee(conn);
				break;
			case 3:
				insertEmployee(emp);
				ptrCvt = *emp;
				insertEmployee(conn, ptrCvt);
				break;
			case 4:
				cout << "Enter Employee Number: ";
				cin >> empNum;
				if (findEmployee(conn, empNum, emp))
				{
					cout << "Last Name: " << emp->lastName << endl;
					cout << "First Name: " << emp->firstName << endl;
					updateEmployee(conn, empNum);
				}
				else
				{
					cout << "The employee with ID " << empNum << " does not exist." << endl << endl;
				}
				break;
			case 5:
				cout << "Enter Employee Number: ";
				cin >> empNum;
				deleteEmployee(conn, empNum);
				break;
			default:
				std::cout << "Invalid selection. Please re-enter" << std::endl;
				break;
			}
		} while (selection != 0);

		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << endl;
	}
	return 0;
}