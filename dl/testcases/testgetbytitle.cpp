#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurement *m;
UnitOfMeasurementDAO unitOfMeasurement;
try
{
string title;
cout<<"Enter unit of measurement : ";
getline(cin,title,'\n');
abc::IUnitOfMeasurement *g;
g = unitOfMeasurement.getByTitle(title);
cout<<"Unit Of Measurement "<<g->getTitle()<<" is having code : "<<g->getCode()<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}