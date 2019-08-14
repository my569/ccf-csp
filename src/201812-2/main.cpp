#include <iostream>

using namespace std;

//0-r r~r+g r+g~r+g+y
//0~y y~y+r y+r~t+r+g

//k=1 r
//k=2 y
//k=3 g

int getDis(int k,int kt,int r,int y,int g)//��ƺͻƵƾ����̵�����Ҫ��ã�������̵ƣ���ʾ�̵������˶�ã�Ϊ����
{
    switch(k){
    case 1://r 0~r
        return kt;//��ƹ�ȥ�����̵�
    case 2://y
        return kt+r;//�Ƶƹ�ȥ�����Ҳ��ȥ�����̵�
    case 3://g
        return -(g-kt);//��ʱ�����̵�,kt��ʾ���ж���̵ƽ���
    }
    return -1;
}



int main()
{
    //freopen("1.txt","r",stdin);

    int r,y,g;
    int N;
    int t = 0;
    long long int s = 0;//�˴�������long long������ֻ��6��

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
            int ans = (m-left+t)%m;//ans�����ʱ�䣬������һ���̵�������˶��
            if(ans >= 0 && ans < g){
                continue;//ʱ�䲻��
            }else{
                int tt = m-ans;//������һ��·�������ʱ��
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
