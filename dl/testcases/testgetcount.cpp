#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurement;
cout<<"Number of Records in context to Unit Of Measurement : "<<unitOfMeasurement.getCount()<<endl;
return 0;
}