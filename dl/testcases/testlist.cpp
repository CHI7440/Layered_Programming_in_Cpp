#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;

int main()
{
forward_list<abc::IUnitOfMeasurement *> *list;
UnitOfMeasurementDAO unitOfMeasurement;
try
{
list = unitOfMeasurement.getAll();
forward_list<abc::IUnitOfMeasurement *>::iterator it = list->begin();
for(;it != list->end();++it)
cout<<"Code : "<<(*it)->getCode()<<" ,Title : "<<(*it)->getTitle()<<endl;
}catch(DAOException daoexception)
{
cout<<daoexception.what();
}
return 0;
}