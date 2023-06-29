#include<iostream>
#include<bl/uommanager>
#include<bl/uom>
#include<bl/BLException>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
abc::IUnitOfMeasurement *m;
UnitOfMeasurementManager unitOfMeasurement;
string title;
cout<<"Enter title : ";
cin>>title;
if(unitOfMeasurement.unitOfMeasurementTitleExists(title))
cout<<title<<" exists"<<endl;
else
cout<<title<<" not exists"<<endl;
return 0;
}