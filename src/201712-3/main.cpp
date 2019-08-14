#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>//注意头文件名称不是stringstream
#include <set>
#include <queue>
//开始时间可以取，t不可取（没考虑，-10分）
//有些year-month-day是不存在的 -15
//split逗号出错 -15
//暴力法会超时
using namespace std;
const int mon_daysTab[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};//每月的天数
const int sumTab[] = {60,24,31,12,7};////分 时 日 月 星期 个数
map<string,int> monthMap;//月份英文简称与int形成映射
map<string,int> weekMap;//月份英文简称与int形成映射


int year_days(int year){ return ((year%4==0 && year%100!=0) || year%400==0)? 366:365; }
int month_days(int year,int mon){
    if(mon == 2) return year_days(year)==366? 29:28;
    else return mon_daysTab[mon];
}
int getWeek(int year,int mon,int day){///获取星期
    int days = 0;
    for(int i = 1970; i < year; i++) days += year_days(i);
    for(int i = 1; i < mon; i++) days += month_days(year,i);
    for(int i = 1; i < day; i++) days++;

    int k = 4;//星期4  0为星期日，1为星期一...
    for(int i = 0; i < days; i++){
        k=(k+1)%7;;
    }
    return k;
}
bool checkDate(int year,int mon,int day){
    return day<=month_days(year,mon);
}

struct Cmd{
    set<int> p[5];
    string time;
    int id;
    string name;
};

struct Time{
    int year;
    int mon;
    int day;
    int hour;
    int min;
    int week;

    Time(){week=-1;}
    Time(int _year,int _mon,int _day,int _hour,int _min):year(_year),mon(_mon),day(_day),hour(_hour),min(_min){}
public:
    void setTime(string s){
        year = stoi(s.substr(0,4));mon = stoi(s.substr(4,2));day = stoi(s.substr(4+2,2));
        hour = stoi(s.substr(4+2+2,2));min = stoi(s.substr(4+2+2+2,2));
    }

    bool operator <(const Time& b)const{
        if(year!=b.year)    return year < b.year;
        if(mon!=b.mon)      return mon < b.mon;
        if(day!=b.day)      return day < b.day;
        if(hour!=b.hour)    return hour < b.hour;
        return min < b.min;
    }
    bool operator ==(const Time& b)const{
        return !((*this)<b || b<(*this));
    }
    bool operator <=(const Time& b)const{
        return (*this)<b || b==(*this);
    }
    bool operator >=(const Time& b)const{
        return b<(*this) || b==(*this);
    }
};

struct Result{
    string time;
    string name;
    int id;

    Result(string _time,string _name,int _id) : time(_time),name(_name),id(_id){}

    Result(int year,int mon,int day,int hour,int min,string _name,int _id):name(_name),id(_id){
        time = std::to_string(year)
        + (mon<10?  "0"+std::to_string(mon)  : std::to_string(mon))//三目运算符返回值要一致，不能一个string一个int
        + (day<10?  "0"+std::to_string(day)  : std::to_string(day))
        + (hour<10? "0"+std::to_string(hour) : std::to_string(hour))
        + (min<10?  "0"+std::to_string(min)  : std::to_string(min));
    }

    bool operator <(const Result& b) const{
        return time!=b.time? time<b.time : id<b.id;//从小到大排序
    }
};

void init(){
    monthMap["jan"]=1; monthMap["feb"]=2; monthMap["mar"]=3;
    monthMap["apr"]=4; monthMap["may"]=5; monthMap["jun"]=6;
    monthMap["jul"]=7; monthMap["aug"]=8; monthMap["sep"]=9;
    monthMap["oct"]=10;monthMap["nov"]=11;monthMap["dec"]=12;

    weekMap["sun"]=0;weekMap["mon"]=1;weekMap["tue"]=2;weekMap["wed"]=3;
    weekMap["thu"]=4;weekMap["fri"]=5;weekMap["sat"]=6;
}

void splitByDot(string s,vector<string> &v){//splited by ","
    size_t k=0,last=0;
    if((k=s.find(",")) != string::npos){
        v.push_back(s.substr(0,k-0)); last=k+1;
        while((k=s.find(",",last)) != string::npos){
            v.push_back(s.substr(last,k-last)); last=k+1;
        }
        v.push_back(s.substr(last));
    }else{
        v.push_back(s);
    }
}
inline int toInt(string s){
    if(monthMap.count(s)) return monthMap[s];
    else if(weekMap.count(s)) return weekMap[s];
    else return stoi(s);
}

void getInfo(string s,set<int>& si,int index){
    vector<string> vs;
    transform(s.begin(),s.end(),s.begin(),::tolower);//transfrom函数在algorithm中

    if(s == "*"){
        if(index==0 || index==1 || index==4)
            for(int j=0; j<sumTab[index]; j++) si.insert(j);//分 时 星期从0开始
        else
            for(int j=1; j<=sumTab[index]; j++) si.insert(j);//日 月从1开始
        return;
    }

    splitByDot(s,vs);//根据逗号分离了string，结果存在vs[i]这个vector里面

    for(size_t i = 0; i < vs.size(); i++){
        size_t k = 0;
        if((k=vs[i].find("-")) != string::npos){
            int a = toInt(vs[i].substr(0,k));
            int b = toInt(vs[i].substr(k+1));//k位置是"-"，要跳过去
            for(int p=a; p<=b; p++) si.insert(p);
        }else{
            int p = toInt(vs[i]);
            si.insert(p);
        }
    }
}



int main()
{
    //bool debug = true;
    bool debug = false;
    if(debug) freopen("1.txt","r",stdin);

    Time start,end;
    int n;

    init();//
    string s1,s2;
    cin >> n >> s1 >> s2;
    start.setTime(s1);
    end.setTime(s2);

    vector<Cmd> cmds;
    for(int id = 0; id < n; id++){
        string s[5];
        string name;//命令
        cin>>s[0]>>s[1]>>s[2]>>s[3]>>s[4]>>name;
        Cmd cmd;
        cmd.id = id;
        cmd.name = name;

        for(int i = 0; i < 5; i++){//分 时 日 月 星期
            getInfo(s[i],cmd.p[i],i);
        }
        cmds.push_back(cmd);
    }

    if(debug){
        for(size_t i=0; i<cmds.size(); i++){
            Cmd& cmd = cmds[i];
            for(size_t j=0; j<5; j++){
                set<int>& si = cmd.p[j];
                for(set<int>::iterator it=si.begin(); it!=si.end(); it++){
                    cout << *it << " ";
                }
                cout << "|";
            }
            cout << '\n';
        }
    }


    vector<Result> Q;
    for(size_t i=0; i<cmds.size(); i++){
        Cmd& cmd = cmds[i];
        for(int year=start.year; year<=end.year; year++){
            set<int> mins=cmd.p[0],hours=cmd.p[1],days=cmd.p[2],mons=cmd.p[3],weeks=cmd.p[4];
            for(auto mon=mons.begin(); mon!=mons.end(); mon++)
            for(auto day=days.begin(); day!=days.end(); day++){
                if(!checkDate(year,*mon,*day)) continue;//判断日期合法性

                int week = getWeek(year,*mon,*day);
                if(!weeks.count(week)) continue;//根据星期是否对应剪枝

                for(auto hour=hours.begin(); hour!=hours.end(); hour++)
                for(auto min=mins.begin(); min!=mins.end(); min++){
                    Time time(year,*mon,*day,*hour,*min);
                    if(time >= start && time < end){//题目要求 包含开始时间，不包含结束时间
                        Q.push_back(Result(year,*mon,*day,*hour,*min,cmd.name,cmd.id));
                    }
                }

            }
        }
    }

    sort(Q.begin(),Q.end());
    for(auto it = Q.begin(); it!=Q.end(); it++)
        cout << it->time << " " << it->name << "\n";
    return 0;
}
