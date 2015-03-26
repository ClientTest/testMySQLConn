// testMySQLConn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "mysql/mysql_quote.h"
#include "mysql/mysql_connection.h" 
#include "mysql/mysql_driver.h"  
#include "mysql/cppconn/statement.h"  
using namespace sql;  
using namespace std; 

void RunConnectMySQL()   
{  
	mysql::MySQL_Driver *driver;  
	Connection *con;  
	Statement *state;  
	ResultSet *result;  
	// 初始化驱动  
	driver = sql::mysql::get_mysql_driver_instance();  
	// 建立链接 
	try
	{
		con = driver->connect("tcp://127.0.0.1:3306", "whg", "whg123456"); 
	}
	catch (...)
	{
		return;
	}
	state = con->createStatement();  
	//切换到agui数据库
	try
	{
		state->execute("use agui");
	}
	catch (...)
	{
		return;
	}
 
	// 查询  
	try
	{
		result = state->executeQuery("select * from user where userid < 1002");  //agui.user
	}
	catch (...)
	{
		return;
	}
	
	// 输出查询  
	while(result->next())  
	{  
		int id = result->getInt("userid");
		sql::SQLString pw = result->getString("password");  
		sql::SQLString name = result->getString("username");
		
		cout << id  << " : " << pw.c_str() << " : " << name.c_str() << endl;  

		/*string spw =   pw.c_str();  
		string sname = name.c_str();
		cout << id  << " : " << spw << " : " << sname << endl;*/

		/*char spw[49],sname[49];
		strcpy(spw,pw.c_str());
		strcpy(sname,name.c_str());
		cout << id  << " : " << spw << " : " << sname << endl;*/
	}  
	delete state;  
	delete con;  
} 

int _tmain(int argc, _TCHAR* argv[])
{
	RunConnectMySQL();  
	getchar();  
	return 0;
}

