//CIDR
#include <stdio.h>
#include <string>
#include <list>
#include <algorithm>
#include <stdlib.h>

using namespace std;

struct IP{
	public: 
		int p[4];
		int mask;
		int q[4][8];
	IP(){}

	private:
	int num = 0;//用来标记是第几个数字
	//接受字符串状态机
	//q1----数字--->q1
	//q1----"."---->q1
	//q1----"/"---->q2
	//q1----"\0"--->q3

	//读取数字并存入p中
	void q1(char* s,int k)
	{
		p[num] = 0;
		for(; s[k]!='\0'&&isdigit(s[k]); k++){
			p[num] *= 10;
			p[num] += s[k]-'0';
		}
		//状态转移
		if(s[k]=='.'){
			num++;
			q1(s,++k);
		}else if(s[k]=='/'){
			num++;
			q2(s,++k);
		}else if(s[k]=='\0'){
			num++;
			q3();
		}
	}
	//读取掩码，同时如果遇到省略后缀型的，要补0
	void q2(char* s,int k){
		for(int i=num; i<4; i++){//省略后缀型
			p[i] = 0;
		}
	
		mask = 0;
		for(; s[k]!='\0'&&isdigit(s[k]); k++){
			mask *= 10;
			mask += s[k]-'0';
		}
	}
	//省略长度型
	void q3()
	{
		for(int i=num; i<4; i++){
			p[i] = 0;
		}
		mask = num*8;
	}

	void dec2bin(int n,int* s)//十进制转2进制
	{
		int k=7;
		while(n>0){
			s[k--] = n&1;
			n >>= 1;
		}
	}

	public:
	void str2IP(char* s){//解析入口
		num = 0;
		q1(s,0);
		for(int i=0; i<4; i++){
			dec2bin(p[i], (int*)q[i]);	
		}
	}
		
	public:
	bool operator <(const IP& b)const {
		for(int i=0; i<4; i++){
			if(p[i] != b.p[i]){
				return p[i]<b.p[i];
			}
		}
		return mask < b.mask;
	}

	bool operator ==(const IP& b) const {
		return !(*this<b)&&!(b<*this);
	}
};

//判断a的ip地址列表是否包含了b
int isContain(const IP& a,const IP& b)
{
	if(a.mask > b.mask)	return 0;

	int mask = a.mask;//取a的mask
	int flag = 1;
	//判断ip的前mask位是否相同，相同表示包含，否则不包含
	for(int i=0; i<4; i++)
	for(int j=1; j<=8 && i*8+j<=mask; j++)//这里写的风格有点让人不舒服
	{
		if(a.q[i][j-1] != b.q[i][j-1]){
			flag = 0;
			break;
		}
	}
	return flag;
}

//同级合并
int CanMerge(const IP& a,const IP &b)
{
	if(a.mask != b.mask)	return 0;	

	int mask = a.mask;//取a的mask或者b的mask
	int flag = 1;
	//判断ip的前mask-1位是否相同	
	for(int i=0; i<4; i++)
	for(int j=1; j<=8 && i*8+j<=mask-1; j++)
	{
		if(a.q[i][j-1] != b.q[i][j-1]){
			flag = 0;
			break;
		}
	}
	//如果ip前mask-1位相同，且第mask位不同，则可以合并，否则不可以
	return flag  && a.q[(mask-1)/8][(mask-1)%8]!=b.q[(mask-1)/8][(mask-1)%8];
}

IP L[110000];
int main()
{
	freopen("1.txt","r",stdin);	
	int len;
	int i,k,n;
	char s[50];
	
	scanf("%d", &n);
	len = n;
	for(i=0; i<n; i++){
		scanf("%s", s);
		L[i].str2IP(s);
	}
	
	sort(L, L+len);
	
	//merge1  原地赋值，没有开辟一个新的空间
	i=0;
	k=0;
	while(i<len){
		if(i==0){
			L[k++] = L[i++];
			continue;//L[0]
		}else if(isContain(L[k-1],L[i])){//如果包含，则不需要保存L[i]了
			i++;
			continue;
		}else{//not contain
			L[k++] = L[i++];
			continue;
		}
	}
	len = k;
	
	
	//merge2
	k = 0;
	i = 0;
	while(i<len){//注意这里有i++
		if(i==0){
			L[k++] = L[i++];
		}
		else if(CanMerge(L[i],L[k-1]))
		{
			L[k-1].mask--;
			while(k>2 && CanMerge(L[k-1],L[k-2])){//向前查看是否可以合并 
			//k=2时，列表中只有2个元素，即L[0]和L[1];k=1时，只有一个元素，就不会出现合并了
				L[k-2].mask--;//合并，只留下L[k-2]和L[k-1]的并集
				k--;
			}
			i++;
		}else{
			L[k++]=L[i++];
		}
	}
	len = k;
	
	for(i=0; i<len; i++)
		printf("%d.%d.%d.%d/%d\n",L[i].p[0],L[i].p[1],L[i].p[2],L[i].p[3],L[i].mask);

	return 0;
}
