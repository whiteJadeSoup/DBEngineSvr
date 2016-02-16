

#include "SQLhandler.hpp"
#include <cppconn/prepared_statement.h>

using namespace std;
bool SQLhandler::Validate (connection_ptr conn_ptr_, std::string& id, std::string& passwd)
{

    try
    {
        std::cout <<  "id: " << id << "password: " << passwd << std::endl;
        // 检查连接是否还有效
        if (!conn_ptr_->isValid())
        {
            std::cout << "conn is invalid!" << std::endl;
            return false;
        }

        conn_ptr_->setSchema("account");

        sql::PreparedStatement  *prep_stmt =
        conn_ptr_->prepareStatement("SELECT * FROM userinfo WHERE id=? AND password=?");

        prep_stmt->setString(1,id);
        prep_stmt->setString(2, passwd);

        sql::ResultSet* rs = prep_stmt->executeQuery();


        bool result = false;
        if (rs->rowsCount())
        {
            result = true;
        }

        delete prep_stmt;
        delete rs;

        return result;

    }
    catch (sql::SQLException& e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return false;
    }
}
