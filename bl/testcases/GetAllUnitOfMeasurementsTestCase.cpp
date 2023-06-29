#include<iostream>
#include<bl/uommanager>
#include<bl/iuom>
#include<bl/uom>
#include<bl/BLException>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
UnitOfMeasurementManager unitOfMeasurement;
unitOfMeasurements = unitOfMeasurement.getUnitOfMeasurements();
forward_list<abc::IUnitOfMeasurement *>::iterator it = unitOfMeasurements->begin();
for(it; it!=unitOfMeasurements->end(); ++it)
{
abc::IUnitOfMeasurement *m = *it;
cout<<m->getCode()<<", "<<m->getTitle()<<endl;
}
return 0;
}