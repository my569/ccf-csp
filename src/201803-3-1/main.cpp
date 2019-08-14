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
        int k = 0;
        int len = s.size();
        while(k < len && s[k++] == '/'){//�������붼����ȷ��ʽ
            if(k >= len) break;//���'/'�������ַ���ĩβ
            else{//���'/'������һ������
                string element = "";
                while(k < len && s[k] != '/')//��������ַ���ĩβ������������һ��'/'��ֹͣ
                    element += s[k++];
                //cout << element << " ";
                this->re.push_back(element);
            }
        }
        //cout << "\t" << name << endl;
    }

    bool check(string r,string &s){//������޸�str��ֵ����Ҫ��Ϊ��ȥ��<int>��ǰ����
        string ans = "";
        int k = 0;
        int len = s.length();
        if(r == "<int>"){
            while(k < len && isdigit(s[k])) k++;
            if(k != 0 && k >= len){//������������k=0��������������������sΪ�մ�
                int kk = 0;
                string temp = "";
                while(s[kk] == 0) ;
                s = s.substr(kk);
                return true;
            }
        }else if(r == "<str>"){
            while(k < len && s[k] != '/') k++;

            return k != 0 && k >= len;
        //}else if(r == "<path>"){
        //    return true;
        }else{
            return r == s;
        }
        return false;

    }

    bool match(string s){
        vector<string> vt;
        int k = 0;
        unsigned int p = 0;
        int len = s.length();

        for(; p < re.size() && k < len; p++){
            if(re[p] == "<path>"){//��Ϊ��Ŀ˵<path>֮��һ����ĩβ����path����ƥ�������ַ���
                vt.push_back(s.substr(k));
                p = re.size();
                k = len;
                break;
            }else{
                //��ȡ�Ӵ�
                if(s[k] == '/') k++;//����һ��'/'
                string element = "";
                while(k < len && s[k] != '/'){
                    element += s[k];
                    k++;
                }
                //�ж��Ӵ��Ƿ�ƥ��
                if(check(re[p],element)){
                    if(re[p][0] == '<') vt.push_back(element);
                }else{
                    break;
                }
            }
        }
        if(k < len && s[k] == '/') k++;


        if(p != 0 && p == re.size() && k != 0 && k == len){
            cout << name;
            for(unsigned int i = 0; i < vt.size(); i++)
                cout << " " << vt[i];
            cout << endl;
            return true;
        }else{
            return false;
        }
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
