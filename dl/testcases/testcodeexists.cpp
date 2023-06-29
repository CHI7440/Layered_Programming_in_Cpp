#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;

int main()
{
forward_list<abc::IUnitOfMeasurement *> *fl;
abc::IUnitOfMeasurement *m;
UnitOfMeasurementDAO unitOfMeasurement;
int code;
cout<<"Enter code : ";
cin>>code;
if(unitOfMeasurement.codeExists(code))
{
cout<<"Code : "<<code<<" is already in list"<<endl;
}
else
{
cout<<"Code : "<<code<<" is not in list"<<endl;
}
return 0;
}