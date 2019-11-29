#include<algorithm>
#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<utility>
using namespace std;

struct driver
{
    string name;
    int seats;
    int is;
    int js;
    vector<pair<int,int> > assign;
    vector<pair<int,int> > drop;
};
typedef struct driver driver;
int modDiff(int a,int b)
{
    if(a<b)
        return (b-a);
    return (a-b);
}
int absoluteDistance(pair<int,int> a,pair<int,int> b)
{
    return modDiff(a.first,b.first) + modDiff(a.second,b.second);
    
}
int findDist(driver driver, pair<int,int> a)
{
    int i=0;
    int distance=0;
    pair<int,int> p;
    p=make_pair(driver.is,driver.js);
    if(driver.assign.size() == 0)
    {
        return absoluteDistance(p,a);
    }
    distance = absoluteDistance(p,driver.assign[0]);
    while(i<driver.assign.size()-1)
    {
        distance=distance + absoluteDistance(driver.assign[i],driver.assign[i+1]);
        i=i+1;
    }
    distance = distance+ absoluteDistance(driver.assign[driver.assign.size()-1],a);
    return distance;
}
int  findNearestDriverWithSeats(vector<driver>& driverArr,pair<int,int> a)
{
    int minDist=INT_MAX;
    int index=-1;
    int i=0;
    while(i<driverArr.size())
    {
        int dist=findDist(driverArr[i],a);
        if(dist<minDist && driverArr[i].seats>0)
        {
            minDist=dist;
            index=i;
        }
        i=i+1;
    }
    return index;
}
void travel(vector<driver>& driverArr,vector<string>& customerNames,vector<pair<int,int> >& source,vector<pair<int,int> >& destination)
{
    vector<pair<int,int> > index;
    int j=0;
    while(j<driverArr.size())
    {
        pair<int,int> p;
        p.first=0;
        p.second=0;
        index.push_back(p);
        j=j+1;
    }
    int k=0;
    int dist=0;
    int ind=-1;
    int pickup=-1;
    int min =INT_MAX;
    while(k<driverArr.size())
    {
        if(index[k].first == 0)
        {
            pair<int,int> p;
            //pair<int,int> q;
            p=make_pair(driverArr[k].is,driverArr[k].js);
            dist=absoluteDistance(p, driverArr[k].assign[index[k].second]);
            if(dist < min)
            {
                min = dist;
                ind=k;
                pickup=0;
            }
        }
        else
        {
           
            pair<int,int> p;
            //pair<int,int> q;
            p=make_pair(driverArr[k].is,driverArr[k].js);
            dist=absoluteDistance(p, driverArr[k].drop[index[k].second]);
            if(dist < min)
            {
                min = dist;
                ind=k;
                pickup=1;
            }
            
        }
        k=k+1;
    }
    if(pickup==0)
    {
        driverArr[ind].is=driverArr[ind].assign[index[ind].second].first;
        driverArr[ind].js=driverArr[ind].assign[index[ind].second].second;
        index[ind].second=index[ind].second+1;
        if(index[ind].second == driverArr[ind].assign.size())
        {
            index[ind].first=1;
            index[ind].second=0;
        }
        findIndex(source,driverArr)
        cout<<driverArr[ind].name<<"is picking up "<<;
    }
    else
    {
        driverArr[ind].is=driverArr[ind].drop[index[ind].second].first;
        driverArr[ind].js=driverArr[ind].drop[index[ind].second].second;
        index[ind].second=index[ind].second+1;
        cout<<driverArr[ind].name<<"is dropping "<<;
    }

}
void assigningPassengers(vector<pair<int,int>>& source , vector<pair<int,int>>& destination ,vector<string>& customerNames,vector<driver>& driverArr)
{
    int i=0;
    while(i< source.size())
    {
        pair<int,int> p;
        p=source[i];
        int index=findNearestDriverWithSeats(driverArr,p);
        driverArr[index].assign.push_back(p);
        driverArr[index].drop.push_back(destination[i]);
        driverArr[index].seats= driverArr[index].seats-1;
        i=i+1;
    }
    int j=0;
    while(j<driverArr.size())
    {
        int k=0;
        while(k<driverArr[j].assign.size())
        {
            cout<<driverArr[j].assign[k].first<<" "<<driverArr[j].assign[k].second<<endl;
            k=k+1;
        }
        j=j+1;
    }
    travel(driverArr,customerName,source,destination);
}
int main()
{
    int n;
    cout<<"enter the size of the grid"<<endl;
    cin>>n;
    int numUsers;
    cout<<"enter the number of users"<<endl;
    cin>>numUsers;
    int i=0;
    vector<pair<int,int>>   source;
    vector<pair<int,int>>   destination;
    vector<string> customerNames;
    vector<driver> driverArr;
    int numDrivers;
    cout<<"enter the number of drivers"<<endl;
    cin>>numDrivers;
    int k=0;
    while(k< numDrivers)
    {
        unordered_set<string> persons;
        string  name;
        cout<<"enter the name of the driver"<<endl;
        cin>>name;
        if(persons.find(name)!= persons.end())
        {
            cout<<"This name is already taken, enter another name "<<endl;
            continue;
        }
        int seats;
        cout<<"which seater car is alloted "<<endl;
        cin>>seats;
        driver temp;
        temp.name=name;
        temp.seats=seats;
        int di;
        int dj;
        cout<<"enter the drivers location"<<endl;
        cin>>di;
        cin>>dj;
        temp.is=di;
        temp.js=dj;
        driverArr.push_back(temp);
        k=k+1;
    }
    while(i<numUsers)
    {
        pair<int,int> p;
        pair<int,int> q;
        unordered_set<string> persons;
        string name;
        cout<<"enter the name please"<<endl;
        cin>>name;
        if(persons.find(name)!= persons.end())
        {
            cout<<"This name already exists,Please enter a new name"<<endl;
            continue;
        }
        persons.insert(name);
        cout<<"enter the pickup points"<<endl;
        int is;
        int js;
        cin>>is;
        cin>>js;
        cout<<"enter the drop points"<<endl;
        int id;
        int jd;
        cin>>id;
        cin>>jd;
        if(is < 0 ||  is >= n || js < 0 ||  js >= n || id < 0 ||  id >= n || js < 0 ||  jd >= n)
        {
            cout<<"enter again please,No such Location"<<endl;
            continue;
        }
        p=make_pair(is,js);
        q=make_pair(id,jd);
        customerNames.push_back(name);
        source.push_back(p);
        destination.push_back(q);
        i=i+1;
    }
    assigningPassengers(source,destination,customerNames,driverArr);
}
