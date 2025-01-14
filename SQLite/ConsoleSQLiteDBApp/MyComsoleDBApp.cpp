// MyComsoleDBApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "sqlite3.h"


//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}



static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int argc, char **argv) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
		return(1);
	}
	rc = sqlite3_open(argv[1], &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}
	if (argc > 2)
	{
		rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
	}
	sqlite3_close(db);
	return 0;
}


