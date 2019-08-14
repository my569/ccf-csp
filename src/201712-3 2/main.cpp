#include <bits/stdc++.h>
using namespace std;

string month[13] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
string week[7] =   {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

struct Cron
{
    string line, s[5], cmd;		//整行，<><><><><>，command
    set<long long> a[5];		//标记可行的日期
} cron;

struct Result	//需要输出的内容
{
    long long res;
    string cmd;
    Result(long long a, string& b): res(a), cmd(b) {}
};

inline int to_int(const string& a)	//评测系统不支持C++11，所以写了这个函数
{
    int res;
    stringstream ss;
    ss << a;
    ss >> res;
    return res;
}

inline string to_str(int a)		//评测系统不支持C++11，所以写了这个函数
{
    string res;
    stringstream ss;
    ss << a;
    ss >> res;
    return res;
}
/*
void splitByDot(string str,vector<string> &v){//splited by ","
    size_t k=0,last=0;
    if((k=str.find(",")) != string::npos){
        v.push_back(str.substr(0,k-0)); last=k+1;
        while((k=str.find(",",last)) != string::npos){
            v.push_back(str.substr(last,k-last)); last=k+1;
        }
        v.push_back(str.substr(last));
    }else{
        v.push_back(str);
    }
}*/

void deal_cron(Cron& t)
{
    //拆解line为5个子串
    stringstream ss;
    ss << t.line;
    for(int i = 0; i < 5; ++i)
        ss >> t.s[i];
    ss >> t.cmd;

    //将英文全转化为大写
    transform(t.s[3].begin(), t.s[3].end(), t.s[3].begin(), ::toupper);
    transform(t.s[4].begin(), t.s[4].end(), t.s[4].begin(), ::toupper);

    //把英文转化为数字
    size_t p;
    for(int i = 1; i < 13; ++i)
    {
        p = t.s[3].find(month[i]);
        if(p != string::npos) t.s[3].replace(p, 3, to_str(i));
    }
    for(int i = 0; i < 7; ++i)
    {
        p = t.s[4].find(week[i]);
        if(p != string::npos) t.s[4].replace(p, 3, to_str(i));
    }

    //分别处理五个子串
    /*string tmp;
    for(int i = 0; i < 5; ++i)
    {
        vector<string> vs;
        splitByDot(t.s[i],vs);
        for(auto it = vs.begin(); it != vs.end(); it++)
        {
            tmp = *it;
     */
    string tmp;
    for(int i = 0; i < 5; ++i)
    {

        //把','转化为' '
        for(size_t j = 0; j < t.s[i].size(); ++j)
            if(t.s[i][j] == ',') t.s[i][j] = ' ';
        ss.clear();
        ss << t.s[i];

        //填充集合a[i]
        while(ss >> tmp)
        {
            if(tmp == "*")		//如果是*，全部放入set
            {
                if(i == 0)
                {
                    for(int j = 0; j <= 59; ++j)
                        t.a[i].insert(j);
                }
                else if(i == 1)
                {
                    for(int j = 0; j <= 23; ++j)
                        t.a[i].insert(j);
                }
                else if(i == 2)
                {
                    for(int j = 1; j <= 31; ++j)
                        t.a[i].insert(j);
                }
                else if(i == 3)
                {
                    for(int j = 1; j <= 12; ++j)
                        t.a[i].insert(j);
                }
                else if(i == 4)
                {
                    for(int j = 0; j <= 6; ++j)
                        t.a[i].insert(j);
                }
                break;
            }

            p = tmp.find("-");
            if(p != string::npos)		//如果有'-'，就取2个数字的范围
            {
                for(int j = to_int(tmp.substr(0, p)); j <= to_int(tmp.substr(p + 1)); ++j)
                    t.a[i].insert(j);
            }
            else t.a[i].insert(to_int(tmp));	//没有'-'，就直接插入这个数字
        }
    }
}

long long n, s, t, res, year, year1, j;	//year：起始年份  year1：终止年份   j：当前年份
/*
const int mon_daysTab[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};//每月的天数
int month_day(int year,int mon){
    if(mon == 2) return year==366? 29:28;
    else return mon_daysTab[mon];
}*/

vector<Result> result;
set<long long>::iterator p0, p1, p2, p3, p4;

int year_day(int year){ return ((year%4==0 && year%100!=0) || year%400==0)? 366:365; }
/*
long long year_day(int y)
{
    if((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) return 366;
    else return 365;
}
*/
long long month_day(int year, int month)
{
    if(month == 2)
        return year_day(year) - 337;
    if(month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else return 31;
}
bool isLegal_week(long long year, long long mon, long long day)	//星期数是否合法
{
    long long days = 0, wee;
    for(int i = 1970; i < year; ++i)
        days += year_day(i);
    for(int i = 1; i < mon; ++i)
        days += month_day(year, i);
    days += day - 1;
    wee = (4 + days) % 7;

    if(cron.a[4].find(wee) == cron.a[4].end()) return 0;		//如果此星期数符合取值范围，返回1
    else return 1;
}

bool isLegal()	//是否合法
{
    if(res >= s && res < t && *p1 <= month_day(j, *p0) && isLegal_week(j, *p0, *p1))	//日期范围、天数是否符合月份、星期数是否相符
        return 1;
    return 0;
}

bool cmp(const Result& a, const Result& b)
{
    return a.res < b.res;
}

void print_result()
{
    for(vector<Result>::iterator p = result.begin(); p != result.end(); ++p)
        cout << p->res << " " << p->cmd << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> s >> t;
    cin.get();

    year = s / 100000000;
    year1 = t / 100000000;
    for(int i = 0; i < n; ++i)
    {
        getline(cin, cron.line);
        for(j = 0; j < 5; ++j)
            cron.a[j].clear();
        deal_cron(cron);

        for(j = year; j <= year1; ++j)												//年
            for(p0 = cron.a[3].begin(); p0 != cron.a[3].end(); ++p0)				//月
                for(p1 = cron.a[2].begin(); p1 != cron.a[2].end(); ++p1)			//日
                    for(p2 = cron.a[1].begin(); p2 != cron.a[1].end(); ++p2)		//时
                        for(p3 = cron.a[0].begin(); p3 != cron.a[0].end(); ++p3)	//分
                        {
                            res = j * 100000000 + *p0 * 1000000 + *p1 * 10000 + *p2 * 100 + *p3;
                            if(isLegal()) result.push_back(Result(res, cron.cmd));
                        }
    }

    stable_sort(result.begin(), result.end(), cmp);
    print_result();
    return 0;
}
