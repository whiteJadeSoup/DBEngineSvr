

#include "SQLhandler.hpp"
#include <cppconn/prepared_statement.h>
#include <sstream>
#include <iterator>

bool SQLhandler::validate (db_connect_ptr conn_ptr_, int64_t id, string& passwd)
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
        conn_ptr_->prepareStatement("SELECT * FROM t_user_auth WHERE id=? AND password=?");

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



bool SQLhandler::read_info(db_connect_ptr conn_, int64_t userid_, vector<string>& result_)
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
            conn_->prepareStatement("SELECT name,nick_name,sex FROM t_user_info WHERE id=?");


        prep_stmt->setString(1, to_string(userid_));
        sql::ResultSet* res = prep_stmt->executeQuery();


        while (res->next())
        {
            result_.push_back(res->getString("name"));
            result_.push_back(res->getString("nick_name"));
            result_.push_back(res->getString("sex"));
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



bool SQLhandler::read_contacts(db_connect_ptr conn_, int64_t user_id_, vector<string>& vPassData)
{

    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");


        vector<string> contact_ids;
        // 获得联系人列表
        sql::PreparedStatement* prep_stmt =
            conn_->prepareStatement("SELECT c_id FROM t_contacts WHERE u_id=?");

        prep_stmt->setString(1, to_string(user_id_));
        sql::ResultSet* res = prep_stmt->executeQuery();

        while (res->next())
        {
            contact_ids.push_back(res->getString("c_id"));
        }


        // 获得联系人具体信息
        prep_stmt = conn_->prepareStatement("SELECT name, nick_name, sex FROM t_user_info WHERE id=?");

        auto it = contact_ids.begin();
        for(; it != contact_ids.end(); ++it)
        {
            prep_stmt->setString(1, *it);
            res = prep_stmt->executeQuery();

            if (res->next())
            {
                vPassData.push_back(*it);                               // id
                vPassData.push_back(res->getString("name"));            // name
                vPassData.push_back(res->getString("nick_name"));       // nick_name
                vPassData.push_back(res->getString("sex"));
            }
            else
            {
                cout << "No data: " << __FILE__ << endl;
            }
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


bool SQLhandler::save_channel_offline_message(db_connect_ptr conn_, vector<string>& vPassData_)
{

    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");

        // 保存离线消息
        sql::PreparedStatement* prep_stmt = conn_->prepareStatement(
        "insert into t_channel_message(i_send_id,i_recv_id,i_channel_id,vch_content, d_send_time, i_flag,v_send_name) values(?,?,?,?,?,0,?)");


        for(int i = 0;  i < vPassData_.size(); i += 6)
        {
            int64_t send_id     = stoi(vPassData_[i]);
            int64_t recv_id     = stoi(vPassData_[i+1]);
            int32_t ch_id       = stoi(vPassData_[i+2]);
            string content      = move(vPassData_[i+3]);
            string send_tm      = move(vPassData_[i+4]);
            string send_nm      = move(vPassData_[i+5]);


            istringstream iss(content);

            prep_stmt->setInt(1, send_id);
            prep_stmt->setInt(2, recv_id);
            prep_stmt->setInt(3, ch_id);
            prep_stmt->setBlob(4, &iss);
            prep_stmt->setString(5, send_tm);
            prep_stmt->setString(6, send_nm);


            prep_stmt->executeUpdate();

        }

        delete prep_stmt;

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



bool SQLhandler::save_offline_message(db_connect_ptr conn_, vector<string>& vPassData)
{
    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }


        int64_t send_id = stoi(vPassData[0]);
        int64_t recv_id = stoi(vPassData[1]);
        string content = move(vPassData[2]);
        string send_tm = move(vPassData[3]);
        string send_nm = move(vPassData[4]);


        // 数据库
        conn_->setSchema("account");

        // 保存离线消息
        sql::PreparedStatement* prep_stmt = conn_->prepareStatement(
          "insert into t_message(send_id, recv_id, content, send_time, flag, send_name) values(?,?,?,?,0,?)");


        istringstream iss(content);

        prep_stmt->setInt(1, send_id);
        prep_stmt->setInt(2, recv_id);
        prep_stmt->setBlob(3, &iss);
        prep_stmt->setString(4, send_tm);
        prep_stmt->setString(5, send_nm);

        prep_stmt->execute();


        delete prep_stmt;

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


bool SQLhandler::read_channel_offline_message(db_connect_ptr conn_, int64_t req_id, vector<string>& vResult)
{
    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");

        // 获得离线消息
        sql::PreparedStatement* prep_stmt = conn_->prepareStatement(
          "select i_send_id, i_channel_id, vch_content, d_send_time, v_send_name from t_channel_message where i_recv_id = ? and i_flag = 0");

        prep_stmt->setInt(1, req_id);

        sql::ResultSet* res = prep_stmt->executeQuery();
        while (res->next())
        {
            vResult.push_back(res->getString("i_send_id"));
            vResult.push_back(res->getString("i_channel_id"));
            vResult.push_back(GetString(res->getBlob("vch_content")));
            vResult.push_back(res->getString("d_send_time"));
            vResult.push_back(res->getString("v_send_name"));
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



bool SQLhandler::read_offline_message(db_connect_ptr conn_, int64_t req_id, vector<string>& vResult)
{
    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");

        // 获得离线消息
        sql::PreparedStatement* prep_stmt = conn_->prepareStatement(
          "select send_id, content, send_time, send_name from t_message where recv_id = ? and flag = 0");

        prep_stmt->setInt(1, req_id);

        sql::ResultSet* res = prep_stmt->executeQuery();
        while (res->next())
        {
            vResult.push_back(res->getString("send_id"));
            vResult.push_back(GetString(res->getBlob("content")));
            vResult.push_back(res->getString("send_time"));
            vResult.push_back(res->getString("send_name"));
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

bool SQLhandler::save_channel_history(db_connect_ptr conn_, vector<string>& vPassData)
{

    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");

        // 删除离线消息
        sql::PreparedStatement* prep_update_stmt = conn_->prepareStatement(
          "delete from t_channel_message where i_send_id = ? and i_recv_id = ? and i_channel_id = ? and i_flag = 0");

        // 插入历史信息
        string str_sql =string("insert into t_channel_message(i_send_id, i_recv_id, i_channel_id, vch_content, d_send_time, i_flag, v_send_name)")+
        string("values(?, ?, ?, ?, ?, 1, ?)");
        sql::PreparedStatement* prep_insert_stmt = conn_->prepareStatement(str_sql);




        // 更新离线消息
        for(int i = 0; i < vPassData.size(); i +=6)
        {
            prep_update_stmt->setInt(1, stoi(vPassData[i]));
            prep_update_stmt->setInt(2, stoi(vPassData[i+1]));
            prep_update_stmt->setInt(3, stoi(vPassData[i+2]));

            prep_update_stmt->executeUpdate();
        }



        for (int i = 0; i < vPassData.size(); i+=6)
        {
            istringstream iss(vPassData[i+3]);

            prep_insert_stmt->setInt(1, stoi(vPassData[i]));
            prep_insert_stmt->setInt(2, stoi(vPassData[i+1]));
            prep_insert_stmt->setInt(3, stoi(vPassData[i+2]));
            prep_insert_stmt->setBlob(4, &iss);
            prep_insert_stmt->setString(5, vPassData[i+4]);
            prep_insert_stmt->setString(6, vPassData[i+5]);
            prep_insert_stmt->executeUpdate();
        }




    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }

}



bool SQLhandler::save_to_history(db_connect_ptr conn_, int64_t recv_id_, vector<string>& vPassData)
{

    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");

        // 删除离线消息
        sql::PreparedStatement* prep_update_stmt = conn_->prepareStatement(
          "delete from t_message where recv_id = ? and send_id = ? and flag = 0");

        // 插入历史信息
        sql::PreparedStatement* prep_insert_stmt = conn_->prepareStatement(
          "insert into t_message(recv_id, send_id, content, send_time, flag, send_name) values(?, ?, ?, ?, 1, ?)");



        // 更新离线消息
        for(int i = 0; i < vPassData.size(); i +=4)
        {
            prep_update_stmt->setInt(1, recv_id_);
            prep_update_stmt->setInt(2, stoi(vPassData[i]));

            prep_update_stmt->executeUpdate();
        }



        for (int i = 0; i < vPassData.size(); i+=4)
        {
            istringstream iss(vPassData[i+1]);


            prep_insert_stmt->setInt(1, recv_id_);
            prep_insert_stmt->setInt(2, stoi(vPassData[i]));
            prep_insert_stmt->setBlob(3, &iss);
            prep_insert_stmt->setString(4, vPassData[i+2]);
            prep_insert_stmt->setString(5, vPassData[i+3]);
            prep_insert_stmt->executeUpdate();
        }




    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }

}




bool SQLhandler::read_channels(db_connect_ptr conn_, vector<string>& vResult)
{
    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");

        // 获得频道列表
        sql::PreparedStatement* prep_channels_stmt = conn_->prepareStatement(
          "select i_id,s_name from t_channel");
        // 获得所属指定频道的玩家
        sql::PreparedStatement* prep_users_stmt = conn_->prepareStatement(
          "select i_user_id from t_channel_member where i_channel_id=?");



        sql::ResultSet* res = prep_channels_stmt->executeQuery();
        vector<string> vUserInfo;

        while (res->next())
        {
            int nChannelId = stoi(res->getString("i_id"));
            string channel_name = res->getString("s_name");

            vResult.push_back(to_string(nChannelId));
            vResult.push_back(channel_name);


            // 查询频道成员
            prep_users_stmt->setInt(1, nChannelId);
            sql::ResultSet* user_res = prep_users_stmt->executeQuery();


            // 成员数
            int nRowCount = user_res->rowsCount();
            vResult.push_back(to_string(nRowCount));

            while(user_res->next())
            {
                vUserInfo.clear();

                // 获取指定玩家信息
                int64_t user_id = (int64_t)stoi(user_res->getString("i_user_id"));
                read_info(conn_, user_id, vUserInfo);


                vResult.push_back(to_string(user_id));
                copy(vUserInfo.begin(), vUserInfo.end(), back_inserter(vResult));
            }

            delete user_res;
        }

        delete res;
        delete prep_channels_stmt;
        delete prep_users_stmt;

    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }
}



bool SQLhandler::join_channel(db_connect_ptr conn_, vector<string>& vPassData, vector<string>& vResult)
{
    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");


        sql::PreparedStatement* prep_insert_stmt = conn_->prepareStatement(
          "insert into t_channel_member(i_channel_id, i_user_id, d_join_time ) values(?,?,now())");


        int64_t user_id         = (int64_t)stoi(vPassData[0]);
        int32_t channel_id      = (int32_t)stoi(vPassData[1]);


        prep_insert_stmt->setInt(1, channel_id);
        prep_insert_stmt->setInt(2, user_id);

        int update_count = prep_insert_stmt->executeUpdate();

        vResult.push_back( update_count ? "1" : "0" );

    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }

}


    // 读取历史消息
bool SQLhandler::read_history(db_connect_ptr conn_, int64_t send_id, int64_t recv_id, vector<string>& result)
{
    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");


        sql::PreparedStatement* prep_stmt = conn_->prepareStatement(
          "select  content, send_time,send_name from t_message where flag = 1 and recv_id in (?,?) and send_id in (?,?) order by send_time");


        prep_stmt->setInt(1, send_id);
        prep_stmt->setInt(2, recv_id);
        prep_stmt->setInt(3, send_id);
        prep_stmt->setInt(4, recv_id);

        sql::ResultSet* res = prep_stmt->executeQuery();

        while (res->next())
        {
            result.push_back(res->getString("content"));
            result.push_back(res->getString("send_time"));
            result.push_back(res->getString("send_name"));
        }

        delete res;
        delete prep_stmt;


    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }

}
    // 读取频道历史消息
bool SQLhandler::read_channel_history(db_connect_ptr conn_, int32_t channel_id, vector<string>& result)
{
    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");


        sql::PreparedStatement* prep_stmt = conn_->prepareStatement(
          "select i_recv_id, i_send_id, i_channel_id, vch_content, d_send_time, v_send_name from t_channel_message where i_channel_id= ? and i_flag = 1 order by d_send_time;");


        prep_stmt->setInt(1, channel_id);

        sql::ResultSet* res = prep_stmt->executeQuery();

        while (res->next())
        {
            result.push_back(res->getString("i_recv_id"));
            result.push_back(res->getString("i_send_id"));
            result.push_back(res->getString("i_channel_id"));
            result.push_back(res->getString("vch_content"));
            result.push_back(res->getString("d_send_time"));
            result.push_back(res->getString("v_send_name"));
        }


        delete res;
        delete prep_stmt;
    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }

}




bool SQLhandler::exit_channel(db_connect_ptr conn_, vector<string>& vPassData, vector<string>& vResult)
{
    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");


        sql::PreparedStatement* prep_dele_stmt = conn_->prepareStatement(
          "delete from t_channel_member where i_channel_id=? and i_user_id=?");


        int64_t user_id         = (int64_t)stoi(vPassData[0]);
        int32_t channel_id      = (int32_t)stoi(vPassData[1]);


        prep_dele_stmt->setInt(1, channel_id);
        prep_dele_stmt->setInt(2, user_id);

        int update_count = prep_dele_stmt->executeUpdate();

        vResult.push_back( update_count ? "1" : "0" );

    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }

}



string SQLhandler::GetString(istream* is)
{
    istreambuf_iterator<char> end_pos;
    string content(istreambuf_iterator<char>(*is), end_pos);

    return content;
}















