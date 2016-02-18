

#include "SQLhandler.hpp"
#include <cppconn/prepared_statement.h>


bool SQLhandler::Validate (connection_ptr conn_ptr_, uint64_t id, string& passwd)
{

    try
    {
        cout <<  "id: " << id << "password: " << passwd <<endl;
        // 检查连接是否还有效
        if (!conn_ptr_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        conn_ptr_->setSchema("account");

        sql::PreparedStatement  *prep_stmt =
        conn_ptr_->prepareStatement("SELECT * FROM userinfo WHERE id=? AND password=?");

        prep_stmt->setString(1,to_string(id));
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



bool SQLhandler::ReadInfo(connection_ptr conn_, uint64_t userid_, vector<string>& result_)
{

    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }



        conn_->setSchema("account");

        sql::PreparedStatement* prep_stmt =
            conn_->prepareStatement("SELECT * FROM userinfo WHERE id=?");


        prep_stmt->setString(1, to_string(userid_));
        sql::ResultSet* res = prep_stmt->executeQuery();


        while (res->next())
        {
            result_.push_back(res->getString("Name"));
            result_.push_back(res->getString("NickName"));
        }


        delete prep_stmt;
        delete res;

        return true;

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
