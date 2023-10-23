/**
 * @file 安全性算法.cpp 
 * @author: 7qisui
 * @date: 2023-10-23 09:33:54
 * 
 **/

#include <iostream>
using namespace std;

//各种变量
int p;//进程数
int r;//资源种类数
int maxs[15][15];//最大需求矩阵max，不使用max是因为与库中函数重名
int available[15];//可用资源向量
int allocation[15][15];//分配矩阵
int need[15][15];//需求矩阵
int request[10];//请求量

//初始时矩阵的元素输入
void matex_input(){
	int i,j;
	cout << "输入初始最大需求矩阵:"<<endl;
	//输入初始最大需求矩阵
	for(i=0;i<p;i++){
		for(j=0;j<r;j++){
			cin >> maxs[i][j];
		}
	}
	cout<<"输入分配矩阵:"<<endl;
	//输入分配矩阵
	for(i=0;i<p;i++){
		for(j=0;j<r;j++){
			cin >> allocation[i][j];
		}
	}
	cout <<"输入需求矩阵:"<<endl;
	//输入需求矩阵
	for(i=0;i<p;i++){
		for(j=0;j<r;j++){
			cin >> need[i][j];
		}
	}
	cout << "输入可利用向量资源:"<<endl;
	//输入可利用向量资源
	for(i=0;i<r;i++){
		cin >> available[i];
	}
}

//比较函数
//m>n,返回1
int compare(int m[],int n[]){
	int i;
	for(i=0;i<r;i++){
		if(m[i] < n[i]){
			return 0;
		}
	}
	return 1;
}

//检测是否含有安全序列
int research_matex(){
	int i,j,k,l;
	int work[r];//工作向量
	int finish[p];
	
	for(i=0;i<p;i++){
		finish[i] = 0;
	}
	for(i=0;i<r;i++){
		work[i] = available[i];
	}
	cout << "分配序列："<<endl;
	cout << "		allocation		need		available" <<endl;
	//p个进程，所以需要p次循环
	for(k=0;k<p;k++){
		for(i=0;i<p;i++){
			if(finish[i]==1){
				continue;
			}
			else{
				if(compare(work,need[i])){
					finish[i] = 1;
					cout<<'\n'<<"进程"<<i<<'\t'<<'\t';
					//设标记位，当进程释放后再次碰到不用运行此else内容
					//flag = 1;
					//打印allocation,没什么变化
					for(j=0;j<r;j++){
						cout << allocation[i][j]<<"  ";
					}
					cout << "		";
					//打印need，没什么变化
					for(j=0;j<r;j++){
						cout << need[i][j]<<"  ";
					}
					cout << "		";
					//打印available，每次都有变化
					//available=work+allocation
					for(j=0;j<r;j++){
						cout << work[j] + allocation[i][j] << "  ";
						//cout << available[j] <<"  ";
					}
					//该进程的l资源使用完毕，释放
					for(l=0;l<r;l++){
						work[l] = work[l] + allocation[i][l];
					}
					break;
				}
			}
			/*if(flag==1){
				break;
			}*/
		}
	}
	cout << endl;
	//不安全
	for(l=0;l<p;l++){
		if(finish[l]==0){
			return 0;
		}
	}
	return 1;//存在安全序列
}

//检测能否分配资源
void research_set(int n){
	int j;
	if(compare(available,request)&&compare(need[n],request)){
		for(j=0;j<r;j++){
			allocation[n][j] = allocation[n][j]+request[j];
			need[n][j] = need[n][j] -request[j];
			available[j] = available[j] - request[j];
		}
	
		//再检查此时是否安全
		if(research_matex()==1){
			cout <<"系统安全，允许给进程"<<n<<"分配资源!"<<endl;
		}else{
			cout <<"不允许给进程"<<n<<"分配资源！"<<endl;
			//把假设的内容换回来
			for(j=0;j<r;j++){
				allocation[n][j] = allocation[n][j]-request[j];
				need[n][j] = need[n][j]+request[j];
				available[j] = available[j] + request[j];
			}
		}
	}
	else{
		cout <<"请求的资源太多，无法分配！"<<endl;
	}
}

//主函数
int main(){
	cout << "请输入进程数目：";
	cin >> p;
	cout << "请输入资源种类数目：";
	cin >> r;
	matex_input();
	if(research_matex()==1){
		cout<<"存在安全序列，初始状态安全。\n";
	}else{
		cout << "不存在安全区列！\n";
	}
	int n;
	cout << "请输入发出请求的进程编号：";
	cin >> n;
	cout << "请输入请求资源矩阵："<<endl;
	for(int i=0;i<r;i++){
		cin >> request[i];
	}
	//research_matex();
	research_set(n);
	return 0;
}

