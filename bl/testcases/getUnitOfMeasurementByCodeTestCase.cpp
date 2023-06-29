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
m = unitOfMeasurement.getUnitOfMeasurementByCode(code);
cout<<"Unit Of Measurement "<<m->getTitle()<<" exists with code : "<<m->getCode()<<endl;
}catch(BLException blException)
{
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}
}
return 0;
}