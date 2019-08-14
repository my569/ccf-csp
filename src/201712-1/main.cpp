#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    vector<int> v;
    cin >> n;
    while(n--){
        int t;
        cin >> t;
        v.push_back(t);
    }
    sort(v.begin(),v.end());
    /*for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;*/

    int min = v[1] - v[0];//n>=2
    int i = 1;
    for(++i; i < v.size(); i++){
        int t = v[i] - v[i-1];
        if(t < min) min = t;
    }
    cout << min << endl;



    return 0;
}
