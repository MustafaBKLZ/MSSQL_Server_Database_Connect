
#include  <iostream>
#include <locale.h>
#include <string>


#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Turkish");



#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000
	//define handles and variables
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
	//initializations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;
	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		goto COMPLETED;
	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		goto COMPLETED;
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		goto COMPLETED;
	//output
	cout << "Attempting connection to SQL Server...";
	cout << "\n";
	//connect to SQL Server  
	//I am using a trusted connection and port 14808
	//it does not matter if you are using default or named instance
	//just make sure you define the server name and the port
	//You have the option to use a username/password instead of a trusted connection
	//but is more secure to use a trusted connection
	switch (SQLDriverConnect(sqlConnHandle,
		NULL,
		//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=username;PWD=password;",
		(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 46250;DATABASE=master;Trusted=true;",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {
	case SQL_SUCCESS:
		cout << "Successfully connected to SQL Server";
		cout << "\n";
		break;
	case SQL_SUCCESS_WITH_INFO:
		cout << "Successfully connected to SQL Server";
		cout << "\n";
		break;
	case SQL_INVALID_HANDLE:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		goto COMPLETED;
	case SQL_ERROR:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		goto COMPLETED;
	default:
		break;
	}
	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		goto COMPLETED;
	//output
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";
	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT @@VERSION", SQL_NTS)) {
		cout << "Error querying SQL Server";
		cout << "\n";
		goto COMPLETED;
	}
	else {
		//declare output variable and pointer
		SQLCHAR sqlVersion[SQL_RESULT_LEN];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, &ptrSqlVersion);
			//display query result
			cout << "\nQuery Result:\n\n";
			cout << sqlVersion << endl;
		}
	}
	//close connection and free resources
COMPLETED:
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	//pause the console window - exit when key is pressed



	cout << "\nPress any key to exit...";
	getchar();
}





/////////////////////
//
//#include <iostream>
//#include <locale.h>
//#include <string>
//#include <windows.h>
//#include <sqlext.h>
//#include <sqltypes.h>
//#include <sql.h>
//
//
//using namespace std;
//
//
//SQLHANDLE sqlConnHandle;
//SQLHANDLE sqlStmtHandle;
//SQLHANDLE sqlEnvHandle;
//SQLWCHAR retconstring[1];
//
//void ConnectSQL()
//{
//	// sql configuration manager üzerinden tcp/ip uzaktan bulma ayarlarýnýn yapýlmasý gerekiyor. 
//// yani port ile baðlantýya izin vermemiz lazým.
//
//#define SQL_RESULT_LEN 240
//#define SQL_RETURN_CODE_LEN 1000
//	//define handles and variables
//	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
//	//initializations
//	sqlConnHandle = NULL;
//	sqlStmtHandle = NULL;
//	//allocations
//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
//		goto COMPLETED;
//	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
//		goto COMPLETED;
//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
//		goto COMPLETED;
//	//output
//	cout << "Attempting connection to SQL Server...";
//	cout << "\n";
//	//connect to SQL Server  
//	switch (SQLDriverConnect(sqlConnHandle,
//		NULL,
//		//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=username;PWD=password;",
//		(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;Trusted=true;",
//		SQL_NTS,
//		retconstring,
//		1024,
//		NULL,
//		SQL_DRIVER_NOPROMPT)) {
//	case SQL_SUCCESS:
//		cout << "Successfully connected to SQL Server";
//		cout << "\n";
//		break;
//	case SQL_SUCCESS_WITH_INFO:
//		cout << "Successfully connected to SQL Server";
//		cout << "\n";
//		break;
//	case SQL_INVALID_HANDLE:
//		cout << "Could not connect to SQL Server";
//		cout << "\n";
//		goto COMPLETED;
//	case SQL_ERROR:
//		cout << "Could not connect to SQL Server";
//		cout << "\n";
//		goto COMPLETED;
//	default:
//		break;
//	}
//	//if there is a problem connecting then exit application
//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
//		goto COMPLETED;
//
//
//
//
//COMPLETED:
//	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
//	/*SQLDisconnect(sqlConnHandle);
//	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
//	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);*/
//
//	//pause the console window - exit when key is pressed
//	//cout << "\nPress any key to exit...";
//	//getchar();
//
//}
//
//
//
//void showSQLError(unsigned int handleType, const SQLHANDLE& handle)
//{
//	SQLWCHAR SQLState[1024];
//	SQLWCHAR message[1024];
//	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
//		// Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information
//		cout << "SQL driver message: " << message << "\nSQL state: " << SQLState << "." << endl;
//}
//
//SQLRETURN retCode = 0;
//
//void main()
//{
//
//	setlocale(LC_ALL, "Turkish");
//	ConnectSQL();
//	char SQLQuery[] = "SELECT [gdr_RECno] as age, [gdr_Gider_Ad] as name  FROM  Gelir_Gider_Takip.GIDER_TIPLERI ";
//
//
//	do {
//
//
//
//		switch (SQLDriverConnect(sqlConnHandle,
//			NULL,
//			//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=username;PWD=password;",
//			(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;Trusted=true;",
//			SQL_NTS,
//			retconstring,
//			1024,
//			NULL,
//			SQL_DRIVER_NOPROMPT))
//
//		{
//
//		case SQL_SUCCESS:
//			break;
//		case SQL_SUCCESS_WITH_INFO:
//			break;
//		case SQL_NO_DATA_FOUND:
//			showSQLError(SQL_HANDLE_DBC, sqlConnHandle);
//			retCode = -1;
//			break;
//		case SQL_INVALID_HANDLE:
//			showSQLError(SQL_HANDLE_DBC, sqlConnHandle);
//			retCode = -1;
//			break;
//		case SQL_ERROR:
//			showSQLError(SQL_HANDLE_DBC, sqlConnHandle);
//			retCode = -1;
//			break;
//		default:
//			break;
//		}
//
//		if (retCode == -1)
//			break;
//
//		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
//			// Allocates the statement
//			break;
//
//		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)SQLQuery, SQL_NTS)) {
//			// Executes a preparable statement
//			showSQLError(SQL_HANDLE_STMT, sqlStmtHandle);
//			break;
//		}
//		else {
//			char name[256];
//			int age;
//			while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
//				// Fetches the next rowset of data from the result
//				SQLGetData(sqlStmtHandle, 1, SQL_C_DEFAULT, &name, sizeof(name), NULL);
//				SQLGetData(sqlStmtHandle, 2, SQL_C_DEFAULT, &age, sizeof(age), NULL);
//				// Retrieves data for a single column in the result set
//				cout << name << " " << age << endl;
//			}
//		}
//	} while (FALSE);
//
//
//
//
//
//}
//
//
//

