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
UnitOfMeasurementManager unitOfMeasurement;
string title;
cout<<"Enter title : ";
cin>>title;
unitOfMeasurement.removeUnitOfMeasurementByTitle(title);
cout<<"Unit Of Measurement remove with title : "<<title<<endl;
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