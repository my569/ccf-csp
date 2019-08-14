#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //vector<int> v;
    int q = 0;
    int s = 0;
    int t;
    while(cin >> t && t != 0){
        if(t == 1) q = 1;
        else{
            if(q == 1 || q == 0) q = 2;
            else q = q + 2;
        }
        s += q;
    }
    cout << s << endl;

    return 0;
}
