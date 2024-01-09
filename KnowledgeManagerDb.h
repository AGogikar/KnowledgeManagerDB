#ifndef KNOWLEDGEMANAGERDB_H
#define KNOWLEDGEMANAGERDB_H

#include "sqlite3.h"
#include <string>
#include <vector>

class KnowledgeManagerDb {
public:
    KnowledgeManagerDb(const char* dbPath);
    ~KnowledgeManagerDb();

    bool insertRecord(int id, const std::string& data);
    std::vector<std::string> selectRecord(int id);

private:
    sqlite3* db;
};

#endif // KNOWLEDGEMANAGERDB_H


