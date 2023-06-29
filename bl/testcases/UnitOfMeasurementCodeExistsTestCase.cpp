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
int code;
cout<<"Enter code : ";
cin>>code;
if(unitOfMeasurement.unitOfMeasurementCodeExists(code))
cout<<code<<" exists"<<endl;
else
cout<<code<<" not exists"<<endl;
return 0;
}