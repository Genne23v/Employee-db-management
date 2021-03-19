#include <iostream>
#include <occi.h>
#include "Module1.h"

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

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
		Employee* emp = nullptr;
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
				if (!findEmployee(conn, empNum, emp))
				{
					cout << "Employee " << empNum << " does not exist." << endl;
				}
				break;
			case 2:
				//displayAllEmployee(Connection * conn);
				//displayEmployee(Connection * conn, struct Employee emp);
				break;
			case 3:
				//insertEmployee(struct Employee* emp);
				//insertEmployee(Connection * conn, struct Employee emp);
				break;
			case 4:
				//updateEmployee(Connection * conn, int employeeNumber);
				break;
			case 5:
				//deleteEmployee(Connection * conn, int employeeNumber);
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