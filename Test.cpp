#include <bits/stdc++.h>
using namespace std;
int n, a[1000];
void Init(){
	cin>>n;
}
void in(){
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
void back_track(int x){
	for(int j=0;j<=1;j++){
		a[x]=j;
		if(x==n) in();
		else back_track(x+1);
	}
}
int main(){
	int t; cin>>t;
	while(t--){
		Init();
	 	back_track(1);
	}
	return 0;
}
