#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurement;
try
{
int code;
cout<<"Enter code : ";
cin>>code;
unitOfMeasurement.remove(code);
cout<<"Unit Of Measurement deleted successfully"<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}