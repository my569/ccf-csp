#include <stdio.h>
#include <cstring>
#include <cctype>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

//#define debug

using namespace std;

struct Node
{
	string lable;
	string id;
	int pri;
	int parent;
};

Node stringToNode(const string &s)
{
    //���Ի����Զ���
    Node tnode;

    int k = 0;
    while(s[k] == '.') k++;//�Զ��� �Ե����е�
    tnode.pri = k/2;

    string lable = "";
    while(isalpha(s[k]) || isdigit(s[k])) lable += tolower(s[k++]);//��ǩ��Сд������
    tnode.lable = lable;

    string id = "";
    if(s[k++] == ' ' && s[k++] == '#')
        while(isalpha(s[k]) || isdigit(s[k])) id += s[k++];//ID���Դ�Сд����
    tnode.id = id;

    return tnode;
}


int getParent(vector<Node> node,int p)
{
	if(node[p].pri == 0){//�����
		return -1;
	}

	int parentPri = node[p].pri - 1;
	for(int i = p-1; i >= 0; i--)
	{
		if(node[i].pri == parentPri){
			return i;
		}
	}

	return -2;//����
}

vector<string> split(string s){
    vector<string> v;
    string p = "";
    for(int i=0; ; i++)
    {
        if(s[i] == '\0'){
            v.push_back(p);
            break;
        }else if(s[i] == ' '){
            v.push_back(p);
            p = "";
        }else{
            p += s[i];
        }
    }

    return v;
}

bool isSingleSelected(Node tnode,string selector)//����ѡ������ƥ��
{
    if(selector[0] == '#' && selector.substr(1) == tnode.id) return true;
    transform(selector.begin(),selector.end(),selector.begin(),::tolower);
    if(selector == tnode.lable) return true;
    return false;
}

bool isSelected(vector<Node> node,int idx,vector<string> selectors)
{
    int j = selectors.size()-1;
    if( isSingleSelected(node[idx],selectors[j]) ){//��һ��������
        j--;
        for(int parent = node[idx].parent; parent != -1 && j >= 0; parent = node[parent].parent){//����paren1t
            if( isSingleSelected(node[parent],selectors[j]) )  j--;
        }
        if(j == -1) return true;
        else return false;
    }else{
        return false;
    }
}


int main()
{
    #ifdef debug
        freopen("1.txt","r",stdin);
    #endif // debug
	int n,m;
	vector<Node> node;

    cin >> n >> m;//n���ĵ� m��ѡ����
    cin.get();

	for(int i = 0; i < n; i++)
	{
	    string s;
	    getline(cin,s);
	    Node tnode = stringToNode(s);
        node.push_back(tnode);
	}
	//���㸸���
	for(int i = 0; i < n; i++)
	{
		node[i].parent = getParent(node,i);
	}

	for(int i = 0; i < m; i++)//m��ѡ����
	{
	    string s;
        getline(cin,s);
        vector<string> selectors = split(s);
        vector<int> ans;

        for(unsigned int i = 0; i < node.size(); i++){
            if(isSelected(node,i,selectors)){
                ans.push_back(i);
            }
        }

        if(ans.size() == 0) cout << "0" << endl;
        else{
            cout << ans.size();
            for(auto it = ans.begin(); it != ans.end(); it++)
                cout << " " << (*it)+1;
            cout << endl;
        }

	}


	return 0;
}


