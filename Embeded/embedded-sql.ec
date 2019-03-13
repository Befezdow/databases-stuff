#include <string.h>

#include "embedded-sql.h"

void do_commit() 
{
	EXEC SQL COMMIT;
}

#define SQLCHECK if(sqlca.sqlcode) { \
	printf("SQLERROR(%d): '%s' '%.5s' %ld\n", __LINE__, sqlca.sqlerrm.sqlerrmc, sqlca.sqlstate, sqlca.sqlcode);\
	do_commit(); \
	return 1;\
	}

int db_connect(const char * password) 
{

	EXEC SQL BEGIN DECLARE SECTION;
	const char * sql_password = password;
	EXEC SQL END DECLARE SECTION;

	EXEC SQL CONNECT TO db@localhost:5432 USER befezdow IDENTIFIED BY :sql_password;
	SQLCHECK;
	
	EXEC SQL COMMIT;
	return 0;	
}

int task_a(int fee, char* day) 
{
	EXEC SQL BEGIN DECLARE SECTION;
		char bank_name[128];
		char exchange_day[128];
		int ins_fee;
	EXEC SQL END DECLARE SECTION;

	strcpy(exchange_day, day);
	ins_fee = fee;

	EXEC SQL DECLARE cursor_a CURSOR FOR
		SELECT DISTINCT bank.name FROM exchange 
		INNER JOIN exchange_machine ON exchange.machine = exchange_machine.id 
		INNER JOIN bank ON exchange.bank_addressee = bank.id
		WHERE bank.address != exchange_machine.address AND exchange_machine.insurance_fee < :ins_fee AND exchange.day <= :exchange_day;
		 
	SQLCHECK;
	
	EXEC SQL OPEN cursor_a;
	SQLCHECK;
	
	while(1) {
		EXEC SQL FETCH cursor_a INTO :bank_name;
		if(sqlca.sqlcode) 
		{
			break;
		}
		
		printf("%s\r\n", bank_name);
	}

	EXEC SQL CLOSE cursor_a;
	SQLCHECK;
	
	EXEC SQL COMMIT;
	return 0;
}

EXEC SQL BEGIN DECLARE SECTION;
struct SQL_MACHINE 
{
	int id;
	char specification[128];
};
EXEC SQL END DECLARE SECTION;

int task_b()
{
	EXEC SQL BEGIN DECLARE SECTION;
		struct SQL_MACHINE machine;
	EXEC SQL END DECLARE SECTION;

	EXEC SQL DECLARE cursor_b CURSOR FOR
		SELECT DISTINCT exchange_machine.id, exchange_machine.specification 
		FROM exchange_machine 
		INNER JOIN bank ON exchange_machine.address = bank.address;

	SQLCHECK;

	EXEC SQL OPEN cursor_b;
	SQLCHECK;
	
	while(1) 
	{
		EXEC SQL FETCH cursor_b INTO :machine;
		if(sqlca.sqlcode) 
		{
			break;
		}
		
		printf("%d\t%s\r\n", machine.id, machine.specification);
	}

	EXEC SQL CLOSE cursor_b;
	SQLCHECK;
	
	EXEC SQL COMMIT;
	return 0;
}

int task_c(int val)
{
	EXEC SQL BEGIN DECLARE SECTION;
		int exchange_val;
		char bank_name[128];
	EXEC SQL END DECLARE SECTION;

	exchange_val = val;

	EXEC SQL DECLARE cursor_c CURSOR FOR
	SELECT DISTINCT bank.name FROM exchange 
	INNER JOIN bank ON exchange.bank_addressee = bank.id 
	GROUP BY bank.name HAVING SUM(exchange.value) > :exchange_val;

	SQLCHECK;

	EXEC SQL OPEN cursor_c;
	SQLCHECK;

	while(1) 
	{
		EXEC SQL FETCH cursor_c INTO :bank_name;
		if(sqlca.sqlcode) 
		{
			break;
		}
		
		printf("%s\r\n", bank_name);
	}

	EXEC SQL CLOSE cursor_c;
	SQLCHECK;

	EXEC SQL COMMIT;
	return 0;
}

int task_d(int val)
{
	EXEC SQL BEGIN DECLARE SECTION;
	int exchange_val;
	char currency_name[128];
	EXEC SQL END DECLARE SECTION;

	exchange_val = val;

	EXEC SQL DECLARE cursor_d CURSOR FOR
		SELECT DISTINCT currency_type.name FROM exchange 
		INNER JOIN currency_type ON exchange.currency = currency_type.id 
		WHERE exchange.value > :exchange_val;

	SQLCHECK;

	EXEC SQL OPEN cursor_d;
	SQLCHECK;

	while(1) 
	{
		EXEC SQL FETCH cursor_d INTO :currency_name;
		if(sqlca.sqlcode) 
		{
			break;
		}
		
		printf("%s\r\n", currency_name);
	}

	EXEC SQL CLOSE cursor_d;
	SQLCHECK;

	EXEC SQL COMMIT;
	return 0;
}