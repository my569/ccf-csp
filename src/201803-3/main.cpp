#include <iostream>
#include <cctype>
#include <regex>

using namespace std;

struct Url{
    string name;
    vector<string> re;

    public:
    Url(string s,string name){
        this->name = name;
        this->re = str2re(s);
    }

    vector<string> str2re(string s){
        vector<string> v;
        while(s != ""){
            v.push_back("/");
            s = s.substr(1);
            size_t next = s.find("/");
            if(next != std::string::npos){
                v.push_back(s.substr(0,next));
                s = s.substr(next);
            }else{
                if(s.length()){
                    v.push_back(s.substr(0));
                    s = "";
                }
            }
        }
        return v;
    }

    bool match(string str){
        vector<string> v = str2re(str);

        unsigned int lv = v.size();
        unsigned int lr = this->re.size();

        unsigned int k=0,p=0;
        string res = this->name;

        while(k<lv && p<lr){
            string element = v[k];
            string r = re[p];

            if(element == r){
                k++;p++;continue;
            }
            if(r == "<path>"){
                res += " ";
                while(k < lv){
                    element = v[k];
                    res += element;
                    k++;
                }

                p++;
            }else if(r == "<int>"){
                size_t le = element.length();
                size_t i = 0;
                while(i < le && isdigit(element[i])) i++;
                if(i != 0 && i >= le){//这里容易忘记i=0的特殊情况，这种情况下s为空串
                    int kk = 0;
                    while(element[kk] == '0') kk++;
                    element = element.substr(kk);
                    res += " " + element;
                    k++;p++;continue;
                }else{
                    break;
                }
            }else if(r == "<str>"){
                res += " " + element;
                k++;p++; continue;
            }else{
                break;
            }

        }

        if(k == lv && p == lr){
            cout << res << endl;
            return true;
        }
        return false;
    }
};

int main()
{
    //freopen("1.txt","r",stdin);

    int n,m;
    vector<Url> urls;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        string s,name;
        cin >> s >> name;
        urls.push_back(Url(s,name));
    }
    for(int i = 0; i < m; i++){
        string s;
        cin >> s;

        bool flag = false;
        for(int j = 0; j < n; j++){
            flag = urls[j].match(s);
            if(flag) break;
        }
        if(!flag){
            cout << "404" << endl;
        }
    }


    return 0;
}



/*#include <iostream>
#include <cctype>
#include <regex>

using namespace std;

struct Url{
    string name;
    vector<string> re;

    public:
    Url(string s,string name){
        this->name = name;
        int k = 0;
        int len = s.size();
        while(k < len && s[k++] == '/'){//假设输入都是正确格式
            if(k >= len) break;//如果'/'后面是字符串末尾
            else{//如果'/'后面是一个规则
                string element = "";
                while(k < len && s[k] != '/')//如果到了字符串末尾或者遇到了下一个'/'就停止
                    element += s[k++];
                //cout << element << " ";
                this->re.push_back(element);
            }
        }
        //cout << "\t" << name << endl;
    }

    bool match(string s){
        unsigned int ls = s.length();
        unsigned int lr = this->re.size();

        unsigned int k=0,p=0;
        string res = this->name;
        while(k<ls && p<lr){
            string r = re[p];

            if(s[k] == '/') k++;//跳过一个'/'

            string element = "";
            while(k < ls && s[k] != '/'){
                element += s[k];
                k++;
            }

            if(element == r){
                p++; continue;
            }
            if(r == "<path>"){
                res += " /" + element;
                res += s.substr(k);
                k = ls;
                p++;
            }else if(r == "<int>"){
                size_t le = element.length();
                if(le == 0) break;
                size_t i = 0;
                while(i < le && isdigit(element[i])) i++;
                if(i != 0 && i >= le){//这里容易忘记i=0的特殊情况，这种情况下s为空串
                    int kk = 0;
                    while(element[kk] == '0') kk++;
                    element = element.substr(kk);
                    res += " " + element;
                    p++; continue;
                }else{
                    break;
                }
            }else if(r == "<str>"){
                if(element.length() == 0) {break;}
                res += " " + element;
                p++; continue;
            }else{
                k = -1;
                break;
            }
        }
        if(k == ls-1 && s[k] == '/') k++;
        if(k == ls && p == lr){
            cout << res << endl;
            return true;
        }
        return false;
    }
};

int main()
{
    freopen("1.txt","r",stdin);

    int n,m;
    vector<Url> urls;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        string s,name;
        cin >> s >> name;
        urls.push_back(Url(s,name));
    }
    for(int i = 0; i < m; i++){
        string s;
        cin >> s;
        bool flag = false;
        for(int j = 0; j < n; j++){
            flag = urls[j].match(s);
            if(flag) break;
        }
        if(!flag){
            cout << "404" << endl;
        }
    }


    return 0;
}
*/
