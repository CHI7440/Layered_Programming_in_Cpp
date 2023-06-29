#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
try
{
abc::IUnitOfMeasurement *m;
UnitOfMeasurementDAO unitOfMeasurement;
int code = 0;
string title;
cout<<"Enter title : ";
cin>>title;
m = new UnitOfMeasurement(0,title);
unitOfMeasurement.add(m);
cout<<"Unit Of Measurement added with code : "<<m->getCode()<<endl;
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements = unitOfMeasurement.getAll();
for(auto m : *unitOfMeasurements)
{
cout<<m->getCode()<<" "<<m->getTitle()<<endl;
}
}catch(DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}

return 0;
}