//CIDR合并
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
//#include <bits/stdc++.h>

using namespace std;
struct IP
{
    string addr;//二进制存储
    int len = -1;
    IP(string v_addr,int v_len){
        addr = v_addr;
        len = v_len;
    }
    IP(){
        len = -1;
    }

    //friend bool operator<(const IP &,const IP &);
    friend inline
    bool operator<(const IP &a,const IP &b){
        //这段代码可以学习下
        if(a.addr !=  b.addr){
            return a.addr<b.addr;
        }else{
            return a.len < b.len;
        }
    }
};

void printIps(list<IP> ips){
    for(list<IP>::iterator iter = ips.begin(); iter != ips.end(); iter++){
        cout << iter->addr << "/" << iter->len << endl;
    }
}


void s1(string s,int i,IP &ip);
void s2(string s,int i,IP &ip);
void s3(string s,int i,IP &ip);

int dec_bit(string dec,string &bit)
{
    //读取string并用stoi转换为10进制
    string::size_type sz;
    int n = stoi(dec,&sz,10);
    //用itoa转换为2进制
    char buf[50];
    itoa(n,buf,2);
    bit = buf;

    return sz;//非数字字符的位置
}
/*
void test_dec_bit()
{
    string str;
    int n = dec_bit("123aa",str);
    cout << str << " " << n << "\n";
}
*/
void s1(string s,int i,IP &ip) //不需要返回值
{
    if( isdigit(s[i]) )
    {
        string addr;
        int idx = dec_bit(s.substr(i),addr);
        ip.addr += string(8-addr.size(),'0') + addr;

        int next = i + idx;
        if(s[next] == '.')
        {
            s2(s,next,ip);
        }
        else if(s[next] == '/')
        {
            s3(s,next,ip);
        }
    }
}

void s2(string s,int i,IP &ip)
{
    if(s[i] == '.')
    {
        s1(s,i+1,ip);
    }
}

void s3(string s,int i,IP &ip)
{
    if(s[i] == '/')
    {
        ip.len = stoi(s.substr(i+1));
        return ;
    }
}

IP ip_format(string s)
{
    IP ip;
    s1(s,0,ip);
    if(ip.len == -1)
    {
        ip.len = ip.addr.size();
    }
    if(ip.addr.size() < 32)
    {
        ip.addr += string(32-ip.addr.size(),'0');
    }

    return ip;
}

bool match(IP it1,IP it2)
{
    if(it1.len > it2.len){//之前没有判断这个
        return false;//不过好像这个在排序之后是多余的
    }

    int len = it1.len;
    if(it1.addr.substr(0,len) == it2.addr.substr(0,len)){
        return true;
    }else{
        return false;
    }
}

/*
void Merge1(list<IP> &ips)
{
    for(list<IP>::iterator it = ips.begin(); it != prev(ips.end()); it++)
    {
        list<IP>::iterator itt = next(it);
        while(match(*it,*itt)){
            itt = ips.erase(itt);//这里itt是不是可能为end，我好像没判断
        }
    }
}*/
void Merge1(list<IP> &ips)
{
    auto i = ips.begin(),j = ips.begin();
    for(++j; j != ips.end(); ){
        if(match(*i,*j)){
            j = ips.erase(j);//删除j，j指针后移
        }else{
            i++;
            j++;
        }
    }
}

bool canUnit(IP ip1,IP ip2)
{
    if(ip1.len != ip2.len){
        return false;
    }else{
        int len = ip1.len;//ip1和ip2len相同
        if(ip1.addr.substr(0,len-1) == ip2.addr.substr(0,len-1) && ip1.addr[len-1] != ip2.addr[len-1]){//前len-1位都相同，且第len位一个为0一个为1，则可以合并
            return true;
        }else{
            return false;
        }
    }
    return false;
}

/*
一直90分是这个函数的算法理解错了，它回溯的时候只要it1--,it2--就好了,我想的太复杂了
void Merge2(list<IP> &ips)
{
    list<IP>::iterator it1 = ips.begin();
    while( it1 != prev(ips.end()) ){//
        list<IP>::iterator it2 = next(it1);
        if( canUnit(*it1,*it2) ){
            do{
                IP ip(it1->addr,it1->len-1);
                //a b c d
                //  ^ ^
                ips.erase(it2);//从后面开始删
                it1 = ips.erase(it1);//
                //a d
                //  ^
                it1 = ips.insert(it1,ip);
                //a e d
                //  ^
                if(it1 != ips.begin()){
                    it2 = prev(it1);
                //a e d
                //^ ^
                }else{0
                    break;
                }
            }while(canUnit(*it1,*it2));
        }else{
            it1++;
        }
    }
}*/

void Merge2(list<IP> &ips)
{
    auto i = ips.begin(),j = ips.begin();
    for(++j; j!=ips.end();){
        if(canUnit(*i,*j)){
            j = ips.erase(j);
            i->len--;
            if(i != ips.begin()){
                i--;
                j--;
            }
        }else{
            i++;
            j++;
        }
    }
}

int main()
{
/*
    //测试ip_format
    IP ip = ip_format("192.168.1");
    cout << ip.addr << "/" << ip.len;
*/

    /*
    //测试重载的等于号
    while(1){
        string ss;
        cin >> ss;
        IP a = ip_format(ss);
        cin >> ss;
        IP b = ip_format(ss);
        if(a < b){
            cout << a.addr << "<" << "\n" << b.addr << endl;
        }else{
            cout << b.addr << "<" << "\n" << a.addr << endl;
        }
    }*/

    list<IP> ips;
    int N;
    cin >> N;
    while(N--)
    {
        string ss;
        cin >> ss;
        IP ip = ip_format(ss);
        ips.push_back(ip);
    }
    //printIps(ips);

    ips.sort();
    //puts("排序后");
    //printIps(ips);

    Merge1(ips);
    //puts("从小到大合并");
    //printIps(ips);

    Merge2(ips);
    //puts("同类合并");
    //printIps(ips);

    for(list<IP>::iterator it = ips.begin(); it != ips.end(); it++){
        for(int i = 0; i < 4; i++){
            string str = it->addr.substr(i*8,8);
            int num = stoi(str,nullptr,2);
            if(i < 3) cout << num << ".";
            else cout << num << "/" << it->len << endl;
        }
    }


    return 0;
}


