#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int main()
{
    list<int> ls;
    int n,k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) ls.push_back(i);
    list<int>::iterator it = ls.begin();
    int i = 1;
    while(n > 1){
        if(i%k == 0 || i%10 == k){
            //cout << " " << *it << endl;
            //删除后更新到下一个
            i++;
            it = ls.erase(it);
            if(it == ls.end()) it = ls.begin();
            n--;
        }else{
            //更新到下一个
            i++;
            it++;
            if(it == ls.end()) it = ls.begin();
        }

    }
    cout << *it;
    return 0;
}
