#include <iostream>

using namespace std;

//0-r r~r+g r+g~r+g+y
//0~y y~y+r y+r~t+r+g

//k=1 r
//k=2 y
//k=3 g

int getDis(int k,int kt,int r,int y,int g)//红灯和黄灯距离绿灯亮起还要多久，如果是绿灯，表示绿灯亮起了多久，为负数
{
    switch(k){
    case 1://r 0~r
        return kt;//红灯过去就是绿灯
    case 2://y
        return kt+r;//黄灯过去，红灯也过去才是绿灯
    case 3://g
        return -(g-kt);//此时即是绿灯,kt表示还有多久绿灯结束
    }
    return -1;
}



int main()
{
    //freopen("1.txt","r",stdin);

    int r,y,g;
    int N;
    int t = 0;
    long long int s = 0;//此处必须是long long，否则只有6分

    cin >> r >> y >> g;
    cin >> N;
    int m = r+y+g;
    while(N--){
        int k,kt;
        cin >> k >> kt;
        if(k == 0){
            t = (t+kt)%m;
            s += kt;
            //cout << s << " " << t << endl;
        }else{
            int left = getDis(k,kt,r,y,g);
            int ans = (m-left+t)%m;//ans是相对时间，距离上一次绿灯亮起过了多久
            if(ans >= 0 && ans < g){
                continue;//时间不变
            }else{
                int tt = m-ans;//距离下一次路灯亮起的时间
                t = (t+tt)%m;
                s += tt;
            }

            //cout << s << " " << t << endl;
        }
        //m - ((m-left+t)%m);
        //m - ((m-left)%m+t%m)%m;
    }
    cout << s << endl;



    return 0;
}
