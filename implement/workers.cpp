#include "../includes/workers.hpp"
#include <memory>
#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

Workers::Workers(sql::Connection* conn):connection(conn){}

std::pair<std::string, int> Workers::getRole(std::string login, std::string password){
     std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement("SELECT role, id FROM Workers WHERE password=SHA2(?, 256) AND login=?"));
    pstmt->setString(1, password);  
    pstmt->setString(2, login);     
    std::cout << "ok" << std::endl;
    sql::ResultSet* res = pstmt->executeQuery();

    if(res->next()){
        return {res->getString("role"), res->getInt("id")};  // Получаем значения по именам колонок
    }else{
        return {}; 
    }
}
int Workers::getWorkerSalary(int workerId){
    int salary = 0;
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement("Select salary From Workers Where id=?;"));
    pstmt->setInt(1, workerId);

    std::unique_ptr<sql::ResultSet>  res(pstmt->executeQuery());
    if(res->next()){
        salary = res->getInt("salary");
    }
    return salary;
}
void Workers::addWorker(nlohmann::json& json){
   std::cout << json.dump(4) << std::endl;
   std::cout << json.begin().key() << std::endl;
   std::string login    = json["login"];
   std::string password = json["password"];
   std::string name     = json["name"];
   std::string surname  = json["surname"];
   std::string phone    = json["phone"];
   std::string role     = json["role"];
   int salary           = json["salary"];
  
   std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(INSERT INTO Workers 
                                    (login, password, name, surname, phone, role, salary)
                                    VALUES (?, SHA2(?, 256), ?, ?, ?, ?, ?);)"));
   pstmt->setString(1, login);     
   pstmt->setString(2, password);     
   pstmt->setString(3, name);     
   pstmt->setString(4, surname);     
   pstmt->setString(5, phone);     
   pstmt->setString(6, role);     
   pstmt->setInt(7, salary);
   pstmt->execute();

}
nlohmann::json Workers::getAllWorker(){
    nlohmann::json answerJson;
    
     std::unique_ptr<sql::Statement> stmt(connection->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(R"(Select name, surname, role, id From Workers;)"));
    
    while(res->next()) {
        nlohmann::json tmp;

        tmp["name"] = res->getString("name");
        tmp["surname"] = res->getString("surname");
        tmp["role"] = res->getString("role");
        tmp["id"] = res->getInt("id");  
     
        answerJson.push_back(tmp); 
    }
    return answerJson;
}

nlohmann::json Workers::getUserForChange(int workerId){
    nlohmann::json answerJson;
    
    sql::PreparedStatement* stmt = connection->prepareStatement("(Select * From Workers Where id=?)");
    stmt->setInt(1, workerId);
     std::unique_ptr<sql::ResultSet>  res(stmt->executeQuery());
    
    if(res->next()) {
        answerJson["login"]     = res->getString("login");
        answerJson["name"] = res->getString("name");
        answerJson["surname"] = res->getString("surname");
        answerJson["phone"] = res->getString("phone");
        answerJson["salary"] = res->getString("salary");
        answerJson["role"] = res->getString("role");
        answerJson["id"] = res->getInt("id");   
    }
    return answerJson;
}
void Workers::updateWorker(nlohmann::json& json){
    std::cout << "flag" << std::endl;
    int workerId = json["workerId"];
    std::string login   = json["login"];
    std::string name    = json["name"];
    std::string surname = json["surname"];
    std::string phone   = json["phone"];
    std::string role    = json["role"];
    int salary          = json["salary"];

    sql::PreparedStatement* pstmt = connection->prepareStatement(R"(UPDATE Workers 
                                                                        set login=?,
                                                                        name=?,
                                                                        surname=?,
                                                                        phone=?,
                                                                        role=?,
                                                                        salary=? 
                                                                        Where id=? )");
    pstmt->setString(1, login);
    pstmt->setString(2, name);
    pstmt->setString(3, surname);
    pstmt->setString(4, phone);
    pstmt->setString(5, role);
    pstmt->setInt(6, salary);
    pstmt->setInt(7, workerId);
    pstmt->execute();
}