#ifndef _TEMPLATE_ARRAY_H_
#define _TEMPLATE_ARRAY_H_

template<class T>
class BasicArray{
    T*parent;
    T*v;
public:
    BasicArray(void){parent=0;v=0;}
    ~BasicArray(void){
	if(parent==0){if(v)delete v;v=0;}
    }
    void Create(int size0){
	if(parent==0){if(v)delete v;v=0;}
	v=new T[size0];
    }
    operator T*(void)const{return v;}
    T&operator[](int i)const{return v[i];}
    T*Top(void)const{return v;}
    void operator=(T*v0){
	if(parent==0){if(v)delete v;v=0;}
	v=parent=v0;
    }
    void operator=(BasicArray<T>&a){
	if(parent==0){if(v)delete v;v=0;}
	v=parent=a->v;
    }
};

template<class T>
class SizeArray{
    T*parent;
    T*v;
    int size;
public:
    SizeArray(void){parent=v=0;size=0;}
    ~SizeArray(void){
	if(parent==0){if(v)delete v;v=0;}
	size=0;
    }
    void Create(int size0){
	if(parent==0){if(v)delete v;v=0;}
	v=new T[size=size0];
    }
    operator T*(void){return v;}
    T&operator[](int i)const{return v[i];}
    T*Top(void)const{return v;}
    int Size(void)const{return size;}
    void SetSize(int i){size=i;}
    void operator=(T*v0){
	if(parent==0){if(v)delete v;v=0;}
	v=parent=v0;
    }
    void Set(T*v0,int size0){
	if(parent==0){if(v)delete v;v=0;}
	v=parent=v0;
	size=size0;
    }
};

template<class T>
class RingArray{
    int n;
    int m;
    int c;
    T*v;
public:
    int get_index(int i){
	if(i>=c)return -1;
	if(c<m)return i;
	int j=n+i;return j>=10?j-10:j;
    }
    void create(int m0){c=n=0;m=m0;v=new T[m];}
    void Append(T&x){v[n++]=x;if(n>=m)n=0;c++;}
    void push_back(T&x){Append(x);}
    T operator[](int i){
	int j=get_index(i);
	return j<0?0:v[j];
    }
    void reset(void){c=n=0;}
    int GetSize(void){return n;}
    int GetMax(void){return m;}
};

template<class T>
class BQueue{
    int n,m;
    T*v;
public:
    BQueue(void){n=m=0;v=0;}
    ~BQueue(void){n=m=0;if(v){delete v;v=0;}}
    int Size(void)const{return n;}
    int GetSize(void)const{return n;}
    int GetMax(void)const{return m;}
    void Create(int m0){n=0;v=new T[m=m0];}
    void Destroy(void){if(v)delete v;v=0;n=m=0;}
    void Resize(int m0){
	if(m0==m)return;
	else if(m0>m){
	    T*v0=v;
	    v=new T[m0];
	    int i;
	    for(i=0;i<n;i++)v[i]=v0[i];
	    if(v0)delete v0;
	}else{
	    T*v0=v;
	    v=new T[m0];
	    int i,i0=0;
	    if(n>m0-1){
		i0=n;
		n=m0-1;
		i0-=n;
	    }
	    for(i=0;i<n;i++)v[i]=v0[i+i0];
	    if(v0)delete v0;
	}
	m=m0;
    }
    void Reset(void){
	n=0;
    }
    void Remove(void){
	if(n>0){
	    int i;
	    for(i=1;i<n;i++)v[i-1]=v[i];
	    n--;
	}
    }
    void Append(T&x){
	if(n>=m){
	    int i;
	    for(i=1;i<n;i++)v[i-1]=v[i];
	    v[n-1]=x;
	}else{
	    v[n++]=x;
	}
    }
    T*Front(void)const{
	return v;
    }
    T&operator[](int i)const{
	return v[i];
    }
    T&GetLast(void)const{
	return v[n-1];
    }
    T&GetLast2(void)const{
	return v[n-2];
    }
    T&GetLast3(void)const{
	return v[n-3];
    }
};

template<class T>
class BStack{
    int n,m;
    T*v;
public:
    BStack(void){n=m=0;v=0;}
    int Size(void)const{return n;}
    int GetSize(void)const{return n;}
    int GetMax(void)const{return m;}
    void Create(int m0){n=0;v=new T[m=m0];}
    void Destroy(void){if(v)delete v;v=0;n=m=0;}
    void Resize(int m0){
	m=m0;
	T*v0=v;
	v=new T[m];
	int i;
	for(i=0;i<n;i++)v[i]=v0[i];
	if(v0)delete v0;
    }
    void Check(void){
	if(n>=m){
	    Resize(m==0?10:m*2);
	}
    }
    void Push(const T&x){
	Check();
	v[n++]=x;
    }
    void Pop(T&x){
	if(n>0)n--;
	x=v[n];
    }
    void operator<(T&x){Push(x);}
    void operator>(T&x){Pop(x);}
};

#endif
