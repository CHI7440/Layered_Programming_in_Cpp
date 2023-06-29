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
string title;
cout<<"Enter title : ";
getline(cin,title,'\n');
if(unitOfMeasurement.titleExists(title))
{
cout<<"Title : "<<title<<" is already in list"<<endl;
}
else
{
cout<<"Title : "<<title<<" is not in list"<<endl;
}
return 0;
}