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
string title;
cout<<"Enter title : ";
cin>>title;
m = unitOfMeasurement.getUnitOfMeasurementByTitle(title);
cout<<"Unit Of Measurement "<<title<<" exists with code : "<<m->getCode()<<endl;
}catch(BLException blException)
{
if(blException.hasPropertyException("title"))
{
cout<<blException.getPropertyException("title")<<endl;
}
}
return 0;
}