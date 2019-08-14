#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Ball{
    int pos;
    int dir;//direction方向 -1为向左←  1为向右→
    int No;
    Ball(int _pos,int _dir,int _No){
        pos = _pos;
        dir = _dir;
        No = _No;
    }
};

void printBalls(const vector<Ball> &balls){
    for(auto it = balls.begin(); it != balls.end(); it++){
        cout << it->pos << (it->dir==1? ">":"<") << " ";
    }
    cout << endl;
}

struct cmpByPos{//使用重载括号的结构体
    bool operator() (const Ball& a,const Ball& b) const{
         return a.pos < b.pos;
    }
}cmpByPosObject;//cmpByPosObject是类的一个对象

bool cmpByNo(const Ball& a,const Ball& b){
    return a.No < b.No;
}

void checkCollosion(vector<Ball> &balls){
    sort(balls.begin(),balls.end(),cmpByPosObject);
    for(unsigned int i=0,j=1; j<balls.size(); i++,j++){
        if(balls[i].pos == balls[j].pos){
            balls[i].dir *= -1;//方向反转
            balls[j].dir *= -1;
        }
    }
    //printBalls(balls);
}

void moveBalls(vector<Ball> &balls,int l)
{
    for(unsigned int i = 0; i < balls.size(); i++)
    {
        Ball& ball = balls[i];
        ball.pos += ball.dir;
        if(ball.pos == 0 || ball.pos == l){//与墙壁的碰撞在这里解决
            ball.dir *= -1;
        }
    }
    checkCollosion(balls);
}

int main()
{
    freopen("1.txt","r",stdin);

    vector<Ball> balls;
    int n,l,t;
    cin >> n >> l >> t;
    for(int i = 0; i < n; i++){
        int pos;
        cin >> pos;
        balls.push_back(Ball(pos,1,i));//默认向右
    }
    //printBalls(balls);

    while(t--){
        moveBalls(balls,l);
        printBalls(balls);
    }

    //sort(balls.begin(),balls.end(),cmpByNo);
    for(auto it = balls.begin(); it != balls.end(); it++){
        if(it != balls.begin()) cout << " " << it->pos;
        else cout << it->pos;
    }
    cout << endl;

    return 0;
}
