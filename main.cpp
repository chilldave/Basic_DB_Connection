#include <iostream>
#include <mysql/mysql.h>


struct connection_details{

    const char *server, *user, *paswd, *database;
};  


MYSQL* mysql_connection_setup(struct connection_details mysql_details)
{
    MYSQL*connection = mysql_init(NULL);
    if(!mysql_real_connect(connection,mysql_details.server,mysql_details.user,
    mysql_details.paswd,mysql_details.database,3306,NULL,0)){

        std::cout<<"Connection Error"<<mysql_error(connection)<<std::endl;
        exit(1);
    }

    return connection;
}

MYSQL_RES* mysql_execute_query(MYSQL*connection, const char *sql_query){

    if(mysql_query(connection,sql_query))
    {
        std::cout<<"MySQL Query Error: "<<mysql_error(connection)<<std::endl;
        exit(1);
    }
    std::cout<<"Successful Connection... \n\n";
    return mysql_use_result(connection);
}
int main(int argc, char const *argv[])
{
    MYSQL *con;
    MYSQL_RES *res;
    MYSQL_ROW row;
     
    struct connection_details mysqlDataBase;
    mysqlDataBase.server = "localhost";
    mysqlDataBase.user = "root";
    mysqlDataBase.paswd = "password";
    mysqlDataBase.database = "students";

    con = mysql_connection_setup(mysqlDataBase);

    res = mysql_execute_query(con,"select * from people;");


    // if((row = mysql_fetch_row(res))!= NULL)
    
        std::cout<<"Displaying database output: \n"<<std::endl;
         std::cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - \n";
        std::cout<<"| ID | Name            | Age | Course     \n";
        std::cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - \n";
        while((row = mysql_fetch_row(res))!= NULL)
        {
            std::cout<<"| "<<row[0] <<"  | "<<row[1]<<" | "<<row[2]<<"  | "<<row[3]<<std::endl;
        }
        // }else{
         std::cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - \n";

            // std::cout<<"\nThe table is empty.\n\n";
        
    

    mysql_free_result(res) ;
    mysql_close(con);    // std::cout<<
}