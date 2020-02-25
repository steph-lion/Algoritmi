#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template<class H>void swap(H *v,int i,int j){
	H h=v[i];
	v[i]=v[j];
	v[j]=h;
}


template<class H> void selectionSort(H* v,int n){
	for(int i=0;i<n-1;i++){
		int min=i;
		for(int j=i+1;j<n;j++){
			if(v[min]>v[j])
				min=j;
		}
		swap(v,min,i);
	}
}




template<class H>class Graph{

	private:
		H* keys;
		bool **m;
		int nk;
		int len;
		
	public:
		Graph(int len){
			this->len=len;
			nk=0;
			keys=new H[len];
			m=new bool*[len];
			for(int i=0;i<len;i++){
				m[i]=new bool[len];
				for(int j=0;j<len;j++)
					m[i][j]=0;
			}
			
		}
		int findIndex(H x){
			for(int i=0;i<len;i++)
				if(keys[i]==x)
					return i;
			return -1;
		}
		
		void addKey(H x){
			if(nk<len)
				keys[nk++]=x;
		}
		
		void addEdge(H a,H b){
			int ai=findIndex(a);
			int bi=findIndex(b);
			if(ai==-1 || bi==-1)
				return;
			m[ai][bi]=1;
		}
		
		void print(stringstream &ss){
			ss.clear();
			for(int i=0;i<len;i++){
				ss<<"("<<keys[i];
				for(int j=0;j<len;j++){
					if(m[i][j]==1)
						ss<<" "<<keys[j];
				}
				ss<<") ";
			}
		}

		void orderVet(){
			selectionSort(keys,len);
		}




};


template<class H>void _print(fstream & in ,fstream & out,Graph<H>* gr,int nk,int ne){
	for(int i=0;i<nk;i++){
		H x;
		in>>x;
		gr->addKey(x);
	}
	gr->orderVet();
	string str;
	stringstream split;
	for(int j=0;j<ne;j++){	
		in>>str;
		for(int i=1;i<str.length();i++){
			split<<str[i];
		}
		H a;
		split>>a;
		split.clear();
		//-----------------
		in>>str;
		for(int i=0;i<str.length()-1;i++){
			split<<str[i];
		}
		H b;
		split>>b;
		split.clear();
		
		gr->addEdge(a,b);
	}
	stringstream ss;
	gr->print(ss);
	out<<ss.str()<<endl;
	
};


int main(){
	fstream in("input.txt",fstream::in);
	fstream out("output.txt",fstream::out);
	while(in.good()){
		int nk,ne;
		string type;
		in>>nk>>ne>>type;
		cout<<"ok"<<endl;
		if(type=="int"){
			Graph<int>* gr=new Graph<int>(nk);
			_print(in,out,gr,nk,ne);
		}
		if(type=="double"){
			Graph<double>* gr=new Graph<double>(nk);
			_print(in,out,gr,nk,ne);
		}
		if(type=="char"){
			Graph<char>* gr=new Graph<char>(nk);
			_print(in,out,gr,nk,ne);
		}
		if(type=="bool"){
			Graph<bool>* gr=new Graph<bool>(nk);
			_print(in,out,gr,nk,ne);
		}
	}

}







