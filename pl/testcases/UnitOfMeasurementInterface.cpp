#include<iostream>
#include<forward_list>
#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
using namespace inventory;
using namespace business_layer;
using namespace std;

void uomMenu()
{
int code;
string title;
int ch;
while(true)
{
UnitOfMeasurementManager manager;
UnitOfMeasurement uom;
abc::IUnitOfMeasurement *_uom;
cout<<endl<<endl<<"----------------------------Unit Of Measurement Module----------------------------"<<endl<<endl;
cout<<"1.Add Unit Of Measurement"<<endl;
cout<<"2.Update Unit Of Measurement"<<endl;
cout<<"3.Remove Unit Of Measurement By Code"<<endl;
cout<<"4.Remove Unit Of Measurement By Title"<<endl;
cout<<"5.Search Unit Of Measurement By Code"<<endl;
cout<<"6.Search Unit Of Measurement By Title"<<endl;
cout<<"7.Get All Of Measurements"<<endl;
cout<<"8.Total Unit Of Measurements"<<endl;
cout<<"9.Search for code existence"<<endl;
cout<<"10.Search for title existence"<<endl;
cout<<"11.Exit"<<endl;
cout<<"Enter your choice : ";
cin>>ch;


if(ch<=0 || ch>11)
{
cout<<"Invalid choice"<<endl;
return;
}


if(ch==1)
{
cout<<"Enter title : ";
cin>>title;
uom.setTitle(title);
try
{
manager.addUnitOfMeasurement(&uom);
cout<<title<<" Added"<<endl;
}catch(BLException blException)
{
cout<<"Some Problem "<<endl;
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<"Code : "<<blException.getPropertyException("code")<<endl<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<"Title : "<<blException.getPropertyException("title")<<endl<<endl;
}
}
}


if(ch==2)
{
cout<<"Enter code : ";
cin>>code;
cout<<"Enter title : ";
cin>>title;
uom.setCode(code);
uom.setTitle(title);
try
{
manager.updateUnitOfMeasurement(&uom);
cout<<"Unit of measurement with code : "<<code<<" and Title : "<<title<<" Updated."<<endl<<endl;
}catch(BLException blException)
{
cout<<"Some Problem "<<endl<<endl;
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<"Code : "<<blException.getPropertyException("code")<<endl<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<"Title : "<<blException.getPropertyException("title")<<endl<<endl;
}
}
}


if(ch==3)
{
cout<<"Enter code : ";
cin>>code;
try
{
manager.removeUnitOfMeasurementByCode(code);
cout<<"Unit of measurement with code : "<<code<<" deleted."<<endl<<endl;
}catch(BLException blException)
{
cout<<"Some Problem "<<endl<<endl;
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<"Code : "<<blException.getPropertyException("code")<<endl<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<"Title : "<<blException.getPropertyException("title")<<endl<<endl;
}
}
}


if(ch==4)
{
cout<<"Enter title : ";
cin>>title;
try
{
manager.removeUnitOfMeasurementByTitle(title);
cout<<"Unit of measurement with title : "<<title<<" deleted."<<endl<<endl;
}catch(BLException blException)
{
cout<<"Some Problem "<<endl<<endl;
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<"Code : "<<blException.getPropertyException("code")<<endl<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<"Title : "<<blException.getPropertyException("title")<<endl<<endl;
}
}
}


if(ch==5)
{
cout<<"Enter code to search : ";
cin>>code;
_uom=manager.getUnitOfMeasurementByCode(code);
if(_uom!=NULL) cout<<_uom->getCode()<<","<<_uom->getTitle()<<endl<<endl;
else cout<<"Unit Of Measurement with code : "<<code<<" not found."<<endl<<endl;
}


if(ch==6)
{
cout<<"Enter title to search : ";
cin>>title;
_uom=manager.getUnitOfMeasurementByTitle(title);
if(_uom!=NULL) cout<<_uom->getCode()<<","<<_uom->getTitle()<<endl<<endl;
else cout<<"Unit Of Measurement with title : "<<title<<" not found."<<endl<<endl;
}


if(ch==7)
{
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements=manager.getUnitOfMeasurements();
forward_list<abc::IUnitOfMeasurement *>::iterator it;
it=unitOfMeasurements->begin();
if(it==unitOfMeasurements->end())
{
cout<<"No Unit Of Measurement is added earlier, File empty"<<endl<<endl;
}
for(it=unitOfMeasurements->begin();it!=unitOfMeasurements->end();++it)
{
_uom=*it;
cout<<_uom->getCode()<<","<<_uom->getTitle()<<endl<<endl;
}
}


if(ch==8)
{
cout<<"Number of Unit Of Measurements : "<<manager.getUnitOfMeasurementCount()<<endl<<endl;
}


if(ch==9)
{
cout<<"Enter code : ";
cin>>code;
if(manager.unitOfMeasurementCodeExists(code)) cout<<code<<" exists."<<endl<<endl;
else cout<<code<<" does not exists."<<endl<<endl;
}


if(ch==10)
{
cout<<"Enter title : ";
cin>>title;
if(manager.unitOfMeasurementTitleExists(title)) cout<<title<<" exists."<<endl<<endl;
else cout<<title<<" does not exists."<<endl<<endl;
}
if(ch==11) return;
}
}


int main()
{
uomMenu();
return 0;
}