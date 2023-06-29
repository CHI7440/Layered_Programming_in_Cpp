#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
string title;
UnitOfMeasurement m;
cout<<"Enter code : ";
cin>>code;
cout<<"Enter title : ";
cin>>title;
m.setCode(code);
m.setTitle(title);
UnitOfMeasurementDAO unitOfMeasurementdao;
try
{
unitOfMeasurementdao.update(&m);
cout<<"Unit Of Measurement updated"<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}