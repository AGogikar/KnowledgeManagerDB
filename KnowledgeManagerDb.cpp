#include "knowledgeManagerDb.h"
#include <iostream>

// Constructor and Destructor remain the same

bool KnowledgeManagerDb::insertRecord(int id, const std::string& data) {
    const char* sql = "INSERT INTO my_table (id, data) VALUES (?, ?)";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare insert statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, data.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

std::vector<std::string> KnowledgeManagerDb::selectRecord(int id) {
    const char* sql = "SELECT data FROM my_table WHERE id = ?";
    sqlite3_stmt* stmt;
    std::vector<std::string> results;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare select statement: " << sqlite3_errmsg(db) << std::endl;
        return results;
    }

    sqlite3_bind_int(stmt, 1, id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        if (text) {
            results.emplace_back(reinterpret_cast<const char*>(text));
        }
    }

    sqlite3_finalize(stmt);
    return results;
}


