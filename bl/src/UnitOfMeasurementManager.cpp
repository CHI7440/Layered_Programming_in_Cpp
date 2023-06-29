#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<dl/DAOException>
#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<common/stringutils>
#include<map>
#include<forward_list>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace business_layer;
using namespace stringutils;

bool UnitOfMeasurementTitleComparator::operator ()(string *left, string *right)
{
return compareStringIgnoreCase(left->c_str(), right->c_str())<0;
}

UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel;

UnitOfMeasurementManager::DataModel::DataModel()
{
populateDataStructure();
}
UnitOfMeasurementManager::DataModel::~DataModel()
{
map<int,_UnitOfMeasurement *>::iterator it = dataModel.codeWiseMap.begin();
for(it; it != dataModel.codeWiseMap.end(); ++it)
{
delete it->second;
}
dataModel.codeWiseMap.clear();
dataModel.titleWiseMap.clear();
}
void UnitOfMeasurementManager::DataModel::populateDataStructure()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement*> * dlUnitOfMeasurements;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
_UnitOfMeasurement *blUnitOfMeasurement;
try
{
dlUnitOfMeasurements = unitOfMeasurementDAO.getAll();
forward_list<inventory::data_layer::abc::IUnitOfMeasurement*>::iterator it;
int code;
string *title;
for(it = dlUnitOfMeasurements->begin(); it != dlUnitOfMeasurements->end(); ++it)
{
dlUnitOfMeasurement = *it;
code = dlUnitOfMeasurement->getCode();
title = new string(dlUnitOfMeasurement->getTitle());
blUnitOfMeasurement = new _UnitOfMeasurement;
blUnitOfMeasurement->code = code;
blUnitOfMeasurement->title = title;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code, blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(title, blUnitOfMeasurement));
delete dlUnitOfMeasurement;
}
dlUnitOfMeasurements->clear();
delete dlUnitOfMeasurements;
}catch(inventory::data_layer::DAOException daoException)
{
// do nothing
}
}

void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) 
{
BLException blException;
if(unitOfMeasurement == NULL)
{
blException.setGenericException(string("Unit Of Measurement required, NULL encountered"));
throw blException;
}
int code = unitOfMeasurement->getCode();
string title = unitOfMeasurement->getTitle();
if(code != 0)
{
blException.addPropertyException("code","Code should be zero");
}
if(title.length() == 0)
{
blException.addPropertyException("title","Title Required");
}
if(title.length()>50)
{
blException.addPropertyException("title","Length of title should not be more than 50");
}
if(blException.hasPropertyExceptions())
{
throw blException;
}
map<string *, _UnitOfMeasurement *>::iterator it;
it = dataModel.titleWiseMap.find(&title);
if(it != dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Title already exists");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
dlUnitOfMeasurement = new inventory::data_layer::UnitOfMeasurement;
dlUnitOfMeasurement->setCode(0);
dlUnitOfMeasurement->setTitle(title);
unitOfMeasurementDAO.add(dlUnitOfMeasurement);
unitOfMeasurement->setCode(dlUnitOfMeasurement->getCode());
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
code = unitOfMeasurement->getCode();
title = unitOfMeasurement->getTitle();
_UnitOfMeasurement *_unitOfMeasurement = new _UnitOfMeasurement();
_unitOfMeasurement->code = code;
string *t = new string(title);
_unitOfMeasurement->title = t;
dataModel.codeWiseMap.insert(pair<int, _UnitOfMeasurement *>(code, _unitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *, _UnitOfMeasurement *>(t, _unitOfMeasurement));
}


void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) 
{
BLException blException;
if(unitOfMeasurement == NULL)
{
blException.setGenericException(string("Unit Of Measurement required, NULL encountered"));
throw blException;
}
int code = unitOfMeasurement->getCode();
string title = unitOfMeasurement->getTitle();
if(code <= 0)
{
blException.addPropertyException("code","Code should be greater than zero");
}
if(title.length() == 0)
{
blException.addPropertyException("title","Title Required");
}
if(title.length()>50)
{
blException.addPropertyException("title","Length of title should not be more than 50");
}
if(blException.hasPropertyExceptions())
{
throw blException;
}
map<int, _UnitOfMeasurement *>::iterator it;
it = dataModel.codeWiseMap.find(code);
if(it == dataModel.codeWiseMap.end())
{
blException.addPropertyException("code","Invalid Unit Of Measurement code");
throw blException;
}
map<string *, _UnitOfMeasurement *>::iterator findTitle;
findTitle = dataModel.titleWiseMap.find(&title);
if(findTitle != dataModel.titleWiseMap.end())
{
_UnitOfMeasurement *_uom = findTitle->second;
if(_uom->code != code)
{
blException.addPropertyException("title","Title exists with another code");
throw blException;
}
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
dlUnitOfMeasurement = new inventory::data_layer::UnitOfMeasurement;
dlUnitOfMeasurement->setCode(code);
dlUnitOfMeasurement->setTitle(title);
unitOfMeasurementDAO.update(dlUnitOfMeasurement);
unitOfMeasurement->setCode(dlUnitOfMeasurement->getCode());
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
_UnitOfMeasurement *_unitOfMeasurement = new _UnitOfMeasurement();
_unitOfMeasurement->code = code;
string *t = new string(title);
_unitOfMeasurement->title = t;
dataModel.codeWiseMap.erase(it);
dataModel.codeWiseMap.insert(pair<int, _UnitOfMeasurement *>(code, _unitOfMeasurement));
dataModel.titleWiseMap.erase(&title);
dataModel.titleWiseMap.insert(pair<string *, _UnitOfMeasurement *>(t, _unitOfMeasurement));
}



void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) 
{
BLException blException;
if(code <= 0)
{
blException.addPropertyException("code","Code should be zero");
}
if(blException.hasPropertyExceptions())
{
throw blException;
}
map<int, _UnitOfMeasurement *>::iterator it;
it = dataModel.codeWiseMap.find(code);
if(it == dataModel.codeWiseMap.end())
{
blException.addPropertyException("code","Invalid Unit Of Measurement code");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
unitOfMeasurementDAO.remove(code);
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
_UnitOfMeasurement *_unitOfMeasurement;
_unitOfMeasurement = it->second;
string *title = _unitOfMeasurement->title;
dataModel.codeWiseMap.erase(it);
dataModel.titleWiseMap.erase(title);
}


void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string title) 
{
BLException blException;
if(title.length() == 0)
{
blException.addPropertyException("title","Title Required");
}
if(title.length()>50)
{
blException.addPropertyException("title","Length of title should not be more than 50");
}
if(blException.hasPropertyExceptions())
{
throw blException;
}
map<string *, _UnitOfMeasurement *>::iterator it;
it = dataModel.titleWiseMap.find(&title);
if(it == dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Title not exists");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
_UnitOfMeasurement *_unitOfMeasurement = it->second;
int code = _unitOfMeasurement->code;
try
{
unitOfMeasurementDAO.remove(code);
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
dataModel.codeWiseMap.erase(code);
dataModel.titleWiseMap.erase(it);
}


abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) 
{
BLException blException;
if(code == 0)
{
blException.addPropertyException("code","Unit of Measurement with given code doesnot exist");
}
if(blException.hasPropertyExceptions())
{
throw blException;
}
map<int, _UnitOfMeasurement *>::iterator it;
it = dataModel.codeWiseMap.find(code);
if(it == dataModel.codeWiseMap.end())
{
blException.addPropertyException("code","Unit of Measurement with given code doesnot exist");
throw blException;
}
_UnitOfMeasurement *_unitOfMeasurement = it->second;
abc::IUnitOfMeasurement * unitOfMeasurement = new UnitOfMeasurement;
unitOfMeasurement->setCode(_unitOfMeasurement->code);
unitOfMeasurement->setTitle(*(_unitOfMeasurement->title));
return unitOfMeasurement;
}


abc::IUnitOfMeasurement *  UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string title) 
{
BLException blException;
abc::IUnitOfMeasurement * unitOfMeasurement = new UnitOfMeasurement;

if(title.length() == 0)
{
blException.addPropertyException("title","Title Required");
}
if(title.length()>50)
{
blException.addPropertyException("title","Length of title should not be more than 50");
}
if(blException.hasPropertyExceptions())
{
throw blException;
}
map<string *, _UnitOfMeasurement *>::iterator it;
it = dataModel.titleWiseMap.find(&title);
if(it == dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Title not exists");
throw blException;
}
_UnitOfMeasurement *_unitOfMeasurement = it->second;
unitOfMeasurement->setCode(_unitOfMeasurement->code);
unitOfMeasurement->setTitle(*(_unitOfMeasurement->title));
return unitOfMeasurement;
}


forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementManager::getUnitOfMeasurements() 
{
_UnitOfMeasurement *unitOfMeasurement;
map<int,_UnitOfMeasurement *>::iterator it = dataModel.codeWiseMap.begin();
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
unitOfMeasurements = new forward_list<abc::IUnitOfMeasurement *>;
forward_list<abc::IUnitOfMeasurement *>::iterator list = unitOfMeasurements->before_begin();
for(it; it!=dataModel.codeWiseMap.end();++it)
{
abc::IUnitOfMeasurement * m;
m = new UnitOfMeasurement;
unitOfMeasurement = it->second;
m->setCode(it->first);
m->setTitle(*(unitOfMeasurement->title));
list = unitOfMeasurements->insert_after(list,m);
}
return unitOfMeasurements;
}


int UnitOfMeasurementManager::unitOfMeasurementTitleExists(string title) 
{

if(title.length() == 0)
{
return false;
}
if(title.length()>50)
{
return false;
}
map<string *, _UnitOfMeasurement *>::iterator it;
it = dataModel.titleWiseMap.find(&title);
if(it == dataModel.titleWiseMap.end())
{
return false;
}
return true;
}


int UnitOfMeasurementManager::unitOfMeasurementCodeExists(int code) 
{
if(code == 0)
{
return false;
}
map<int, _UnitOfMeasurement *>::iterator it;
it = dataModel.codeWiseMap.find(code);
if(it == dataModel.codeWiseMap.end())
{
return false;
}
return true;
}

int UnitOfMeasurementManager::getUnitOfMeasurementCount() 
{
return dataModel.codeWiseMap.size();
}


