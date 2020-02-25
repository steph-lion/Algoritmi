//#include<life.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template<class T>class Node{
	private:
		Node<T>* next,*prev;
		T key;
	public:	
		Node(T key){
			this->key=key;
			next=prev=NULL;
		}
		Node()
		{
			prev = next = NULL;
		}
		void setPrev(Node<T>* x){prev=x;}
		void setNext(Node<T>* x){next=x;}
		void setKet(T* x){key=x;}
		T getKey() { return key; }
		Node<T>* getNext() { return next; }
		Node<T>* getPrev() { return prev; }
};


template<class T>class DLinkedList{
	private:
		Node<T>* head,*tail,*current;
		int n;
		
	public:
		DLinkedList(){
			n=0;
			head = new Node<T>;
			tail = new Node<T>;
			head->setNext(tail);
			head->setPrev(NULL);
			tail->setPrev(head);
			tail->setNext(NULL);
			current = head;
		}
		int getN(){return n;}
		
		void insert (T x){
			n++;
			Node<T> * node=new Node <T>(x);
			Node<T> * succ=head->getNext();
			while((succ!=tail)&&(succ->getKey()<node->getKey()))
				succ=succ->getNext();
			Node<T>* prev=succ->getPrev();
			node->setNext(succ);
			node->setPrev(prev);
			succ->setPrev(node);
			prev->setNext(node);
		}
		
		bool isEmpty(){
		if(head->getNext()==tail)
			return true;
		return false;
		}
	
	Node<T>* next(){
		if(current!=NULL){
			current=current->getNext();
			if(current!=tail){
				return current;
			}
			return NULL;
		}
		return NULL;
	}
	
	void reset(){
		current=head;
	}
};


template<class T>class Graph{
	private:
		int n;
		DLinkedList<T>* list;
		T* keys;
		int indexKey;
		
	public:	
		Graph(int n){
			//cout<<"si"<<endl;
			this->n=n;
			list=new DLinkedList<T>[n];
			//cout<<"dopo Dlin"<<endl;
			keys=new T[n];
			indexKey=0;
		}
		
		void insertKey(T key){
			if(indexKey < n)
			{
				keys[indexKey] = key;
			//	cout<<"inserito valore"<<endl;
				indexKey++;
				return;
			}
			return;
		}
		
		
		int findIndex(T key){
			
			for(int i=0;i<n;i++){
				if(keys[i]==key){
					return i;
				}
			}
			return -1;
		}
		
		void selectionSort(){
			for(int i=0; i<n; i++)
			{
				int min = i;
				for(int j=i+1; j<n; j++){
					if(keys[j] < keys[min])
						min = j;
				}	
				T temp = keys[i];
				keys[i] = keys[min];
				keys[min] = temp;
			}
		}	
		
		void insertEdge(T key1,T key2){
			int index1=findIndex(key1);
			if(index1==-1)
				return;
			//cout<<"inserito arco"<<endl;
			list[index1].insert(key2);
		}
		
		void printEdges(stringstream &ss)
		{
			for(int i=0; i<n; i++){				//ciclo sul numero di liste di adiacenza
				ss<< "(" << keys[i];	
				list[i].reset();				//iteratore	
				Node<T> *node;		
				int number = list[i].getN();
				//cout<<number<<endl;		
				for(int k=0; k<number; k++){
					node = list[i].next();
					ss<< ","<<node->getKey();
				}		
				ss << ") ";
			}
		}
		
};



template<class T> void print(fstream &input,fstream &output,Graph<T>* gr,int n,int nOp){
	
	for(int i=0;i<n;i++){
		T x;
		input>>x;
		gr->insertKey(x);
	}
	gr->selectionSort();
	stringstream split;
	string str;
	for(int j=0;j<nOp;j++){
		input>>str;
		for(int i=1;i<str.length();i++){
			split<<str[i];
		}
		T a;
		split>>a;
		//cout<<"a: "<<a<<endl;
		split.clear();
		input>>str;
		for(int i=0;i<str.length()-1;i++){
			split<<str[i];
		}
		T b;
		split>>b;
		//cout<<"b: "<<b<<endl;
		split.clear();
		gr->insertEdge(a,b);
	}
	stringstream ss;
	gr->printEdges(ss);
	output<<ss.str()<<endl;
};




int main(){
	
	fstream input("input.txt",fstream::in)	;
	fstream output("output.txt",fstream::out)	;
	while(input.good()){
		int n,nOp;
		string type;
		input>>n>>nOp>>type;
		//cout<<"n :"<<n<<" nOp:"<<nOp<<endl;
		if(type=="int"){
			Graph<int>* gr=new Graph<int>(n);
			//cout<<"entra nel print "<<endl;
			print(input,output,gr,n,nOp);
		}
		if(type=="double"){
			Graph<double>* gr=new Graph<double>(n);
			//cout<<"entra nel print "<<endl;
			print(input,output,gr,n,nOp);
		}
			if(type=="char"){
			Graph<char>* gr=new Graph<char>(n);
			//cout<<"entra nel print "<<endl;
			print(input,output,gr,n,nOp);
		}
			if(type=="bool"){
			Graph<bool>* gr=new Graph<bool>(n);
			//cout<<"entra nel print "<<endl;
			print(input,output,gr,n,nOp);
		}
	
	}
	

	
}






