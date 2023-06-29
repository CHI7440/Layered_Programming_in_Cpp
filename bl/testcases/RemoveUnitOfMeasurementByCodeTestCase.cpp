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
unitOfMeasurement.removeUnitOfMeasurementByCode(code);
cout<<"Unit Of Measurement removed with code : "<<code<<endl;
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