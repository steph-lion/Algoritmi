#include <iostream>
#include <fstream>
#include <sstream>

#define WHITE 0
#define GRAY 1
#define BLACK 2
using namespace std;

template<class H>class Node{
	private:
		Node<H>* next;
		H key;
	public:
		Node(H x){
			key=x;
			next=NULL;
		}
		Node<H>* getNext(){
			return next;
		}
		H getKey(){
			return key;
		}
		void setNext(Node<H>* x){
			next=x;
		}
		void setKey(H x){
			key=x;
		}
};

template<class H>class List{
	private:
		Node<H>* head;
	public:	
		List(){
			head=NULL;
		}
		void push(H x){
			Node<H>* obj =new Node<H>(x);
			obj->setNext(head);
			head=obj;
		}
		void print(fstream& out){
			Node<H>* current=head;
			while(current){
				out<<current->getKey()<<" ";
				current=current->getNext();
			}
			out<<endl;
		}
};

template<class H>class Graph{
	private:
		int len,n,*color;
		bool**m;
		H* keys;
		List<H>* list;
	public:
		Graph(int l){
			len=l;
			n=0;
			color=new int[len];
			keys=new H[len];
			list=new List<H>();
			m=new bool*[len];
			for(int i=0;i<len;i++){
				m[i]=new bool[len];
				for(int j=0;j<len;j++)
					m[i][j]=0;
			}
		}
		int findIndex(H x){
			for(int i=0;i<n;i++)
				if(keys[i]==x)
					return i;
			return -1;
		}
		void addKey(H x){
			if(n<len){
				keys[n++]=x;
			}
		}
		void addEdge(H a,H b){
			int ai=findIndex(a);
			int bi = findIndex(b);
			if(ai==-1 || bi==-1)
				return;
			m[ai][bi]=1;
		}
		
		void DFSVisit(int i){
			color[i]=GRAY;
			for(int j=0;j<n;j++){
				if(m[i][j]==1 && color[j]==WHITE)
						DFSVisit(j);
			}
			color[i]=BLACK;
			list->push(keys[i]);
		}
		
		void DFS(){
			for(int i=0;i<n;i++){
				color[i]=WHITE;
			}
			for(int i=0;i<n;i++){
				if(color[i]==WHITE)
					DFSVisit(i);
			}
		}
		
		void topologicalSort(fstream&out){
			DFS();
			list->print(out);
		}
};

template<class H>void print(fstream & in , fstream & out,Graph<H>* gr,int n,int ne){
	for(int i =0;i<n;i++){
		H x;
		in>>x;
		gr->addKey(x);
	}
	for(int j=0;j<ne;j++){
		string str;
		stringstream split;
		H a;
		in>>str;
		for(int i=1;i<str.length();i++)
			split<<str[i];
		split>>a;
		split.clear();
		H b;
		in>>str;
		for(int i=0;i<str.length()-1;i++)
			split<<str[i];
		split>>b;
		split.clear();
		gr->addEdge(a,b);
	}
	gr->topologicalSort(out);
	
} 

int main(){
	fstream in("input.txt",fstream::in);
	fstream out("output.txt",fstream::out);
	
	while(in.good()){
		int n,ne;
		string type;
		in>>n>>ne>>type;
		if(type=="int"){
			Graph<int>* gr=new Graph<int>(n);
			print(in,out,gr,n,ne);
		}
		if(type=="double"){
			Graph<double>* gr=new Graph<double>(n);
			print(in,out,gr,n,ne);
		}
		if(type=="char"){
			Graph<char>* gr=new Graph<char>(n);
			print(in,out,gr,n,ne);
		}		
		
	}

}
