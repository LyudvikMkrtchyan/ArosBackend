#include "../includes/finances.hpp"
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <memory>

Finances::Finances(sql::Connection* conn):connection(conn){}

void Finances::setTransactionWashFinance(int washerId, int amount,std::string code){
    std::string todayDate = time->getTodaysDate();

    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(Insert into Finances
                                                                (worker_id, amount, transaction_type, transaction_date, description)
                                                                Values(?,?,'expense', ?, ?))"));
    pstmt->setInt(1, washerId);
    pstmt->setInt(2, amount);
    pstmt->setDateTime(3, todayDate);
    pstmt->setString(4, code);

    pstmt->execute();

}