#include<iostream>
#include<bl/uommanager>
#include<bl/uom>
#include<forward_list>
#include<bl/BLException>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
try
{
abc::IUnitOfMeasurement *m;
UnitOfMeasurementManager unitOfMeasurement;
string title;
cout<<"Enter title : ";
cin>>title;
m = new UnitOfMeasurement(0,title);
unitOfMeasurement.addUnitOfMeasurement(m);
cout<<"Unit Of Measurement added with code : "<<m->getCode()<<endl;
forward_list<abc::IUnitOfMeasurement *>* unitOfMeasurements = unitOfMeasurement.getUnitOfMeasurements();
for(abc::IUnitOfMeasurement *uom : *unitOfMeasurements)
{
cout<<uom->getCode()<<" "<<uom->getTitle()<<endl;
}
}catch(BLException blException)
{
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<blException.getPropertyException("title")<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}
}

return 0;
}