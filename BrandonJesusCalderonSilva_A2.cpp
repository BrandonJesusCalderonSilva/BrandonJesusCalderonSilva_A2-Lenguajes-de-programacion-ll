// BrandonJesusCalderonSilva_A2.cpp : Conexion a base de datos.
//

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>

using namespace std;
int main() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;

    // Asignar un gestor de entorno
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    // Asignar un gestor de conexión
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Conectarse a la base de datos
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"sqlserver", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {

        cout << "Conectado a la base de datos exitosamente." << endl;

        SQLHSTMT hstmt;
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hstmt);
       
        //Select a la base de datos
        ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"SELECT * FROM Empleados", SQL_NTS);

        wcout << L"+------------------+---------------+--------------+-----------+-----+---------------+-------+------------+ " << endl;
        wcout << L"| No.  | Nombre    | Apellido pat. | Apellido mat.| F. de Nac.| RFC | Centro trabajo| Puesto| Descripcion| " << endl;
        wcout << L"+------------------+---------------+--------------+-----------+-----+---------------+-------+------------+ " << endl;



        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            int num_empleado;
            SQLWCHAR name[50];
            while (SQLFetch(hstmt) == SQL_SUCCESS) {
                SQLGetData(hstmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
                SQLGetData(hstmt, 2, SQL_C_WCHAR, name, sizeof(name), NULL);

              
               


                //wcout << " " << num_empleado << "      " << name << endl;

            }
            
        }
        // Liberar el manejador
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

    }
    else {
        cout << "Fallo la conexion a la base de datos" << endl;
    }

    // Desconectar y liberar manejadores
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
    return 0;
}



