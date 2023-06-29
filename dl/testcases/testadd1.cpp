#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
try
{
UnitOfMeasurement *m;
UnitOfMeasurementDAO unitOfMeasurement;
int code = 0;
string title;
cout<<"Enter title : ";
cin>>title;
m = new UnitOfMeasurement(0,title);
unitOfMeasurement.add(m);
cout<<"Unit Of Measurement added with code : "<<m->getCode()<<endl;
}catch(DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}

return 0;
}