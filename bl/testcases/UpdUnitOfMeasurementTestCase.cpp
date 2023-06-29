#include<iostream>
#include<bl/uommanager>
#include<bl/uom>
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
int code;
cout<<"Enter code : ";
cin>>code;
string title;
cout<<"Enter title : ";
cin>>title;
m = new UnitOfMeasurement(code,title);
unitOfMeasurement.updateUnitOfMeasurement(m);
cout<<"Unit Of Measurement updated with code : "<<m->getCode()<<" and title : "<<m->getTitle()<<endl;
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