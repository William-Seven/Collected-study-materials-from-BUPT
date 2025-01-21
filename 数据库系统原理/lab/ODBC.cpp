#include <windows.h>

#include <sqlext.h>

#include <iostream>
#include <string>

// 辅助函数：检查SQL操作的返回值并报告结果
void checkResult(SQLRETURN retcode, const std::string& action) {
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        std::cout << action << " succeeded.\n";
    } else {
        std::cerr << action << " failed.\n";
        exit(EXIT_FAILURE);
    }
}

int main() {
    SQLHENV hEnv;       // ODBC 环境句柄
    SQLHDBC hDbc;       // 数据库连接句柄
    SQLHSTMT hStmt;     // SQL语句句柄
    SQLRETURN retcode;  // SQL操作返回值

    // Step 1: 初始化ODBC环境
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);  // 分配环境句柄
    checkResult(retcode, "SQLAllocHandle (Environment)");

    // 设置ODBC版本为3.0
    retcode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    checkResult(retcode, "SQLSetEnvAttr");

    // 分配数据库连接句柄
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    checkResult(retcode, "SQLAllocHandle (Connection)");

    // Step 2: 建立数据库连接
    SQLCHAR connStr[] = "DSN=databaseclass;UID=root;PWD=abc123;DATABASE=test3;";
    retcode = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    checkResult(retcode, "SQLDriverConnect");

    std::cout << "Connection established successfully!\n";

    // 分配SQL语句句柄
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    checkResult(retcode, "SQLAllocHandle (Statement)");

    // Step 3: 查询所有记录
    std::cout << "\nQuerying all records in the diary table:\n";
    const char* query = "SELECT title, authorID, destination, content, popularity, rating, score FROM diary;";
    retcode = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);  // 执行查询
    checkResult(retcode, "SQLExecDirect (Query All)");

    // 用于存储查询结果的变量
    SQLCHAR title[256], authorID[256], destination[256], content[256];
    SQLINTEGER popularity, rating;
    SQLDOUBLE score;

    // 提取并显示查询结果
    while (SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_CHAR, title, sizeof(title), NULL);
        SQLGetData(hStmt, 2, SQL_C_CHAR, authorID, sizeof(authorID), NULL);
        SQLGetData(hStmt, 3, SQL_C_CHAR, destination, sizeof(destination), NULL);
        SQLGetData(hStmt, 4, SQL_C_CHAR, content, sizeof(content), NULL);
        SQLGetData(hStmt, 5, SQL_C_SLONG, &popularity, 0, NULL);
        SQLGetData(hStmt, 6, SQL_C_SLONG, &rating, 0, NULL);
        SQLGetData(hStmt, 7, SQL_C_DOUBLE, &score, 0, NULL);
        std::cout << "Title: " << title << ", AuthorID: " << authorID << ", Destination: " << destination
                  << ", Content: " << content << ", Popularity: " << popularity
                  << ", Rating: " << rating << ", Score: " << score << "\n";
    }
    SQLFreeStmt(hStmt, SQL_CLOSE);

    // Step 4: 删除一条记录
    std::cout << "\nDeleting a record from the diary table:\n";
    const char* deleteStmt = "DELETE FROM diary WHERE authorID = 'Kimi';";
    retcode = SQLExecDirect(hStmt, (SQLCHAR*)deleteStmt, SQL_NTS);
    checkResult(retcode, "SQLExecDirect (Delete)");
    std::cout << "Record deleted successfully!\n";
    SQLLEN rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    printf("%d rows affected.\n", rowCount);

    // Step 5: 修改记录
    std::cout << "\nUpdating a record in the diary table:\n";
    const char* updateStmt = "UPDATE diary SET content = 'Updated Content', popularity = 100 WHERE authorID = 'Lucia';";
    retcode = SQLExecDirect(hStmt, (SQLCHAR*)updateStmt, SQL_NTS);
    checkResult(retcode, "SQLExecDirect (Update)");
    std::cout << "Record updated successfully!\n";
    rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    printf("%d rows affected.\n", rowCount);

    // Step 6: 插入一条记录
    std::cout << "\nInserting a record into the diary table:\n";
    const char* insertStmt = "INSERT INTO diary (title, authorID, destination, content, popularity, rating, score) VALUES ('New Title', 'A123', 'New York', 'New Content', 5000, 500, 4.5);";
    retcode = SQLExecDirect(hStmt, (SQLCHAR*)insertStmt, SQL_NTS);
    checkResult(retcode, "SQLExecDirect (Insert)");
    std::cout << "Record inserted successfully!\n";
    rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    printf("%d rows affected.\n", rowCount);

    // Step 7: 再次查询并显示所有记录
    std::cout << "\nQuerying and displaying all records from the diary table:\n";
    const char* queryagain = "SELECT title, authorID, destination, content, popularity, rating, score FROM diary;";
    retcode = SQLExecDirect(hStmt, (SQLCHAR*)queryagain, SQL_NTS);  // 执行查询
    checkResult(retcode, "SQLExecDirect (Query All)");

    // 提取并显示查询结果
    while (SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_CHAR, title, sizeof(title), NULL);
        SQLGetData(hStmt, 2, SQL_C_CHAR, authorID, sizeof(authorID), NULL);
        SQLGetData(hStmt, 3, SQL_C_CHAR, destination, sizeof(destination), NULL);
        SQLGetData(hStmt, 4, SQL_C_CHAR, content, sizeof(content), NULL);
        SQLGetData(hStmt, 5, SQL_C_SLONG, &popularity, 0, NULL);
        SQLGetData(hStmt, 6, SQL_C_SLONG, &rating, 0, NULL);
        SQLGetData(hStmt, 7, SQL_C_DOUBLE, &score, 0, NULL);
        std::cout << "Title: " << title << ", AuthorID: " << authorID << ", Destination: " << destination
                  << ", Content: " << content << ", Popularity: " << popularity
                  << ", Rating: " << rating << ", Score: " << score << "\n";
    }
    SQLFreeStmt(hStmt, SQL_CLOSE);

    // Clean up
    std::cout << "\nCleaning up resources...\n";
    SQLFreeStmt(hStmt, SQL_CLOSE);        // 释放语句句柄
    SQLDisconnect(hDbc);                  // 断开数据库连接
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);  // 释放数据库连接句柄
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);  // 释放环境句柄
    std::cout << "All resources freed.\n";

    return 0;
}
