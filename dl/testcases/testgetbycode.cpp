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
int code;
cout<<"Enter Code : ";
cin>>code;
abc::IUnitOfMeasurement *g;
g = unitOfMeasurement.getByCode(code);
cout<<"Unit Of Measurement with Code "<<g->getCode()<<" is : "<<g->getTitle()<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}