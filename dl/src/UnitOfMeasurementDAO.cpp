#include<string.h>
#include<c:\sqlite3\include\sqlite3.h>
#include<dl/iuom>
#include<dl/uom>
#include<dl/daoexception>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<fstream>
#include<common/stringutils>
using namespace std;
using namespace inventory;
using namespace data_layer;
using namespace stringutils;


int rowHandler(void *ptr, int columnCount, char **dataPtr, char **columnNamePtr)
{
forward_list<string> *list = (forward_list<string> *)ptr;
forward_list<string>::iterator it = list->before_begin();
for(int x=0 ; x<columnCount; x++)
{
if(dataPtr[x] == NULL)
{
it = list->insert_after(it,"");
}
else
{
it = list->insert_after(it,dataPtr[x]);
}
}
return 0;
}


void UnitOfMeasurementDAO:: add(abc::IUnitOfMeasurement* unitOfMeasurement)
{
if(unitOfMeasurement == NULL)
{
throw DAOException("Invalid IUnitOfMeasurement pointer");
}
const string vTitle = unitOfMeasurement->getTitle();
string title = trimmed(vTitle);
if(title.length() == 0)
{
throw DAOException("Title required, length is zero");
}
if(title.length() > 50)
{
throw DAOException("Title exceeded 50 characters");
}
if(unitOfMeasurement->getCode() != 0)
{
throw DAOException("Code is not zero");
}
sqlite3 *dataFile;
int result;
char sql[1001];
char *errorMessage;
result = sqlite3_open(FILE_NAME.c_str(),&dataFile);
if(result != SQLITE_OK)
{
string errMsg = errorMessage;
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
throw DAOException(string("Unable to connect, reason : ")+errMsg);
}
result = sqlite3_exec(dataFile, "create table uomTable(code Integer primary key AUTOINCREMENT, title char[51] not null unique collate nocase)",0,0,&errorMessage);
sprintf(sql,"insert into uomTable(title) values('%s');", title.c_str());
result = sqlite3_exec(dataFile,sql,0,0,&errorMessage);
if(result != SQLITE_OK)
{
string errMsg = errorMessage;
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
throw DAOException("Cannot insert record, reason : "+errMsg);
}
int code = sqlite3_last_insert_rowid(dataFile);
sqlite3_close(dataFile);
unitOfMeasurement->setCode(code);
}



void UnitOfMeasurementDAO:: update(abc::IUnitOfMeasurement* unitOfMeasurement)
{
if(unitOfMeasurement == NULL)
{
throw DAOException("Invalid IUnitOfMeasurement pointer");
}
const string vTitle = unitOfMeasurement->getTitle();
string title = trimmed(vTitle);
if(title.length() == 0)
{
throw DAOException("Title required, length is zero");
}
if(title.length() > 50)
{
throw DAOException("Title exceeded 50 characters");
}
if(unitOfMeasurement->getCode() <= 0)
{
throw DAOException("Code should be greater than zero");
}
sqlite3 *dataFile;
int result;
char arr[101];
char sql[1001];
char *errorMessage;
UnitOfMeasurementDAO uomdao;
result = sqlite3_open_v2(FILE_NAME.c_str(),&dataFile,SQLITE_OPEN_READONLY,NULL);
if(result != SQLITE_OK)
{
sprintf(arr,"Invalid Unit Of Measurement Code : %d",unitOfMeasurement->getCode());
throw DAOException(arr);
}
sqlite3_close(dataFile);
sqlite3_open(FILE_NAME.c_str(),&dataFile);
result = sqlite3_exec(dataFile, "create table uomTable(code Integer primary key AUTOINCREMENT, title char[51] not null unique collate nocase)",0,0,&errorMessage);
if(result == SQLITE_OK	)
{
sqlite3_exec(dataFile, "drop table uomTable",0,0,&errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
sprintf(arr,"Invalid Unit Of Measurement Code : %d",unitOfMeasurement->getCode());
throw DAOException(arr);
}
int code = unitOfMeasurement->getCode();
if(uomdao.codeExists(code) == 0)
{
sqlite3_close(dataFile);
sprintf(arr,"Invalid Unit Of Measurement Code : %d",unitOfMeasurement->getCode());
throw DAOException(arr);
}
sprintf(sql,"update uomTable set title = '%s' where code=%d;",title.c_str(),code);
result = sqlite3_exec(dataFile,sql,0,0,&errorMessage);
if(result != SQLITE_OK	)
{
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
sprintf(arr,"Title %s already exists with another code",vTitle.c_str());
throw DAOException(arr);
}
sqlite3_close(dataFile);
}



void UnitOfMeasurementDAO:: remove(int code)
{
if(code <= 0)
{
throw DAOException("Code should be greater than zero");
}
sqlite3 *dataFile;
int result;
char arr[101];
char sql[1001];
char *errorMessage;
UnitOfMeasurementDAO uomdao;
if(uomdao.codeExists(code) == 0)
{
sprintf(arr,"Invalid Unit Of Measurement Code : %d",code);
throw DAOException(arr);
}
result = sqlite3_open_v2(FILE_NAME.c_str(),&dataFile,SQLITE_OPEN_READONLY,NULL);
if(result != SQLITE_OK)
{
sprintf(arr,"Invalid Unit Of Measurement Code : %d",code);
throw DAOException(arr);
}
sqlite3_close(dataFile);
sqlite3_open(FILE_NAME.c_str(),&dataFile);
result = sqlite3_exec(dataFile, "create table uomTable(code Integer primary key AUTOINCREMENT, title char[51] not null unique collate nocase)",0,0,&errorMessage);
if(result == SQLITE_OK	)
{
sqlite3_exec(dataFile, "drop table uomTable",0,0,&errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
sprintf(arr,"Invalid Unit Of Measurement Code : %d",code);
throw DAOException(arr);
}
sprintf(sql,"delete from uomTable where code=%d;", code);
result = sqlite3_exec(dataFile,sql,0,0,&errorMessage);
if(result != SQLITE_OK)
{
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
sprintf(arr,"Invalid Unit Of Measurement Code : %d",code);
throw DAOException(arr);
}
sqlite3_close(dataFile);
}





abc::IUnitOfMeasurement* UnitOfMeasurementDAO::getByCode(int code)
{
if(code <= 0)
{
throw DAOException("Code should be greater than zero");
}
sqlite3 *dataFile;
int result;
char arr[101];
char sql[1001];
char *errorMessage;
forward_list<string> tempList;
UnitOfMeasurementDAO uomdao;
result = sqlite3_open_v2(FILE_NAME.c_str(),&dataFile,SQLITE_OPEN_READONLY,NULL);
if(result != SQLITE_OK)
{
sprintf(arr,"Invalid Unit Of Measurement Code : %d",code);
throw DAOException(arr);
}
sqlite3_close(dataFile);
sqlite3_open(FILE_NAME.c_str(),&dataFile);
result = sqlite3_exec(dataFile, "create table uomTable(code Integer primary key AUTOINCREMENT, title char[51] not null unique collate nocase)",0,0,&errorMessage);
if(result == SQLITE_OK	)
{
sqlite3_exec(dataFile, "drop table uomTable",0,0,&errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
sprintf(arr,"Invalid Unit Of Measurement Code : %d",code);
throw DAOException(arr);
}
sprintf(sql,"select title from uomTable where code = %d;",code);
result = sqlite3_exec(dataFile,sql,rowHandler,&tempList,&errorMessage);
if(result != SQLITE_OK || tempList.empty())
{
sprintf(arr,"Invalid Unit Of Measurement Code : %d",code);
sqlite3_close(dataFile);
throw DAOException(arr);
}
string title = tempList.front();
UnitOfMeasurement *unitOfMeasurement = new UnitOfMeasurement;
unitOfMeasurement->setCode(code);
unitOfMeasurement->setTitle(title);
sqlite3_close(dataFile);
return unitOfMeasurement;
}





abc::IUnitOfMeasurement* UnitOfMeasurementDAO::getByTitle(string title)
{
string vTitle = trimmed(title);
if(vTitle.length() == 0)
{
throw DAOException(string("Invalid Unit Of Measurement : ")+title);
}
if(vTitle.length() > 50)
{
throw DAOException(string("Invalid Unit Of Measurement : ")+title);
}
sqlite3 *dataFile;
int result;
char sql[1001];
char *errorMessage;
forward_list<string> tempList;
UnitOfMeasurementDAO uomdao;
result = sqlite3_open_v2(FILE_NAME.c_str(),&dataFile,SQLITE_OPEN_READONLY,NULL);
if(result != SQLITE_OK)
{
throw DAOException(string("Invalid Unit Of Measurement : ")+title);
}
sqlite3_close(dataFile);
sqlite3_open(FILE_NAME.c_str(),&dataFile);
result = sqlite3_exec(dataFile, "create table uomTable(code Integer primary key AUTOINCREMENT, title char[51] not null unique collate nocase)",0,0,&errorMessage);
if(result == SQLITE_OK	)
{
sqlite3_exec(dataFile, "drop table uomTable",0,0,&errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
throw DAOException(string("Invalid Unit Of Measurement : ")+title);
}
sprintf(sql,"select code from uomTable where title = '%s';",vTitle.c_str());
result = sqlite3_exec(dataFile,sql,rowHandler,&tempList,&errorMessage);
if(result != SQLITE_OK || tempList.empty())
{
sqlite3_close(dataFile);
throw DAOException(string("Invalid Unit Of Measurement : ")+title);
}
int code = stoi(tempList.front());
UnitOfMeasurement *unitOfMeasurement = new UnitOfMeasurement;
unitOfMeasurement->setCode(code);
unitOfMeasurement->setTitle(vTitle);
sqlite3_close(dataFile);
return unitOfMeasurement;
}





forward_list<abc::IUnitOfMeasurement*> * UnitOfMeasurementDAO::getAll()
{
sqlite3 *dataFile;
int result;
char sql[1001];
char *errorMessage;
forward_list<string> tempList;
result = sqlite3_open_v2(FILE_NAME.c_str(),&dataFile,SQLITE_OPEN_READONLY,NULL);
if(result != SQLITE_OK)
{
throw DAOException("No Unit of Measurements exists");
}
sqlite3_close(dataFile);
sqlite3_open(FILE_NAME.c_str(),&dataFile);
result = sqlite3_exec(dataFile, "create table uomTable(code Integer primary key AUTOINCREMENT, title char[51] not null unique collate nocase)",0,0,&errorMessage);
if(result == SQLITE_OK	)
{
sqlite3_exec(dataFile, "drop table uomTable",0,0,&errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
throw DAOException("No Unit Of Measurements exist");
}
result = sqlite3_exec(dataFile,"select * from uomTable;",rowHandler,&tempList,&errorMessage);
if(result != SQLITE_OK || tempList.empty())
{
sqlite3_close(dataFile);
throw DAOException("No Unit Of Measurements exist");
}
forward_list<abc::IUnitOfMeasurement*> *list = new forward_list<abc::IUnitOfMeasurement*>;
forward_list<string>::iterator it = tempList.begin();
while(it != tempList.end())
{
if(it == tempList.end()) break;
int code = stoi((*it));
++it;
if(it == tempList.end()) break;
string title = (*it);
++it;
abc::IUnitOfMeasurement *unitOfMeasurement = new UnitOfMeasurement;
unitOfMeasurement->setCode(code);
unitOfMeasurement->setTitle(title);
list->push_front(unitOfMeasurement);
}
sqlite3_close(dataFile);
return list;
}





int UnitOfMeasurementDAO::getCount()
{
sqlite3 *dataFile;
int result;
char arr[101];
char sql[1001];
char *errorMessage;
forward_list<string> tempList;
result = sqlite3_open_v2(FILE_NAME.c_str(),&dataFile,1,NULL);
if(result != SQLITE_OK)
{
return 0;
}
result = sqlite3_exec(dataFile, "create table uomTable(code Integer primary key AUTOINCREMENT, title char[51] not null unique collate nocase);",0,0,&errorMessage);
if(result == SQLITE_OK	)
{
sqlite3_exec(dataFile, "drop table uomTable;",0,0,&errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
return 0;
}
result = sqlite3_exec(dataFile,"select count(*) from uomTable;",rowHandler,&tempList,&errorMessage);
int numberOfRecords = stoi(tempList.front());
sqlite3_close(dataFile);
return numberOfRecords;
}




int UnitOfMeasurementDAO::codeExists(int code)
{
sqlite3 *dataFile;
int result;
char sql[1001];
char *errorMessage;
forward_list<string> tempList;
result = sqlite3_open_v2(FILE_NAME.c_str(),&dataFile,1,NULL);
if(result != SQLITE_OK)
{
return false;
}
result = sqlite3_exec(dataFile, "create table uomTable(code Integer primary key AUTOINCREMENT, title char[51] not null unique collate nocase);",0,0,&errorMessage);
if(result == SQLITE_OK	)
{
sqlite3_exec(dataFile, "drop table uomTable;",0,0,&errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
return false;
}
sprintf(sql,"select * from uomTable where code = %d;", code);
result = sqlite3_exec(dataFile,sql,rowHandler,&tempList,&errorMessage);
if(result != SQLITE_OK || tempList.empty())
{
sqlite3_close(dataFile);
return false;
}
sqlite3_close(dataFile);
return true;
}




int UnitOfMeasurementDAO::titleExists(string title)
{
sqlite3 *dataFile;
int result;
char sql[1001];
char *errorMessage;
forward_list<string> tempList;
string vTitle = trimmed(title);
if(vTitle.length() == 0)
{
sqlite3_close(dataFile);
return false;
}
if(vTitle.length() > 50)
{
sqlite3_close(dataFile);
return false;
}
result = sqlite3_open_v2(FILE_NAME.c_str(),&dataFile,1,NULL);
if(result != SQLITE_OK)
{
return false;
}
result = sqlite3_exec(dataFile, "create table uomTable(code Integer primary key AUTOINCREMENT, title char[51] not null unique collate nocase);",0,0,&errorMessage);
if(result == SQLITE_OK	)
{
sqlite3_exec(dataFile, "drop table uomTable;",0,0,&errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(dataFile);
return false;
}
sprintf(sql,"select * from uomTable where title = '%s';", vTitle.c_str());
result = sqlite3_exec(dataFile,sql,rowHandler,&tempList,&errorMessage);
if(result != SQLITE_OK || tempList.empty())
{
return false;
}
sqlite3_close(dataFile);
return true;
}
