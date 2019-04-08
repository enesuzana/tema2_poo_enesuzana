#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
//derived classes need parametrized constructors , destructors
// constr de init, parametr, de copiere, destructor,
// >> << = overloaded
// operatorii -> fc membre ale claselol, ma putin >> << )
// MOSTENIRI/ FC VIRTUALE/ CLASE ABSTRACTE/INTERFETE
// templates +1p
//d
class Nod{
    char info;
    Nod *next;
public:
    Nod(){
        info = 0;
        next = NULL;
    }
    Nod(char inf, Nod *n){
        info = inf;
        next = n;
    }
    Nod(const Nod &n){ info = n.info;
                       next = n.next;}
    virtual ~Nod(){
    }

    virtual int getInfo(){
        return (int)info;
    }
    void setInfo(char val){ info = val; }
    Nod *getNext(){ return next;}
    void setNext(Nod *nod){ next = nod; }
    friend class ListaSimpluInlantuita;
    Nod* operator=(Nod *p2){
        info = p2->getInfo();
        next = p2->getNext();
        return this;
    }
};

class Nod_dublu:public Nod{
    Nod_dublu *ante;
    int info;
    Nod_dublu *next;
public:
    //constr simplu
    Nod_dublu(){ante = NULL; info = -1; next = NULL;}
    //parametrizat
    Nod_dublu(char i, Nod_dublu *anterior,  Nod_dublu *nextn):Nod(i, nextn){
        ante = anterior;
        info = i;
        next = nextn;
    }
    //de copiere
    Nod_dublu(const Nod_dublu &n): Nod(n){ ante = n.ante;
        next = n.next;
        info = n.info;}
    //destructor
    virtual ~Nod_dublu(){
    }
    //getteri, setteri
    void setInfo(int inf){ info = inf;}
    virtual int getInfo(){return info;}
    Nod_dublu *getNext(){ return next;}
    Nod_dublu *getAnte(){ return ante; }
    void setAnte(Nod_dublu *nod){ ante = nod; }
    void setNext(Nod_dublu *nod){ next = nod; }
    //= e ok
    Nod_dublu* operator=(const Nod_dublu &nod){
        ante = nod.ante;
        info = nod.info;
        next = nod.next;
        return this;
    }
    friend class ListaDubluInlantuita;
};

class Nod_prioritate:public Nod_dublu{
    int prio;
    int info;
    Nod_prioritate *ante;
    Nod_prioritate *next;
public:
    //constr simplu
    Nod_prioritate(){ prio = 0; ante = next = NULL; }
    //parametrizat
    Nod_prioritate(char i, Nod_prioritate *a, Nod_prioritate *n, int pr):Nod_dublu(i, a, n){
        prio = pr;
        ante = a;
        next = n;
        info = i;
    }
    //de copiere
    Nod_prioritate(const Nod_prioritate &n):Nod_dublu(n){
        ante = n.ante;
        next = n.next;
        info = n.info;
        prio = n.prio;
    }
    //destructor
    ~Nod_prioritate(){}
    //getteri, setteri
    int getPrio(){ return prio; }
    void setPrio(int pr){prio = pr; }

    void setInfo(int inf){ info = inf;}
    virtual int getInfo(){return info;}

    Nod_prioritate *getNext(){ return next;}
    Nod_prioritate *getAnte(){ return ante; }

    void setAnte(Nod_prioritate *nod){ ante = nod; }
    void setNext(Nod_prioritate *nod){ next = nod; }
    //operator
    Nod_prioritate* operator=(const Nod_prioritate &nod){
        ante = nod.ante;
        info = nod.info;
        next = nod.next;
        prio = nod.prio;
        return this;
    }
    friend class CoadaDePrioritati;
};

//uses Nod elements
class ListaSimpluInlantuita{
    Nod *head;
    Nod *tail;
    Nod *nod;
    int n;
public:
    ListaSimpluInlantuita(){ head = new Nod(-1, NULL);
                             tail = head;
                             n = 0;
                           }
    ListaSimpluInlantuita(Nod *h, Nod*t, int nr){
        head = h;
        tail = t;
        n = nr;
    }
    ListaSimpluInlantuita(const ListaSimpluInlantuita &l);
    ~ListaSimpluInlantuita();

    virtual Nod* getHead(){ return head;}
    void setHead(int val){ head->setInfo((int)val);}
    Nod* getTail(){ return tail;}
    void setTail(char val){ tail->setInfo(val);}

    void setCounter(int c){ n = c;}
    int getCounter(){ return n;}

    Nod* getNod(){return nod;}

    virtual void push(int val, int poz);
    virtual void del(int val);
    //operatori:
    virtual ListaSimpluInlantuita operator=(ListaSimpluInlantuita l);
    virtual ListaSimpluInlantuita operator+(ListaSimpluInlantuita l2);
    friend ostream& operator<<(ostream& out,const ListaSimpluInlantuita &lista);
    friend istream& operator>>(istream& in, ListaSimpluInlantuita &lista);

};

ListaSimpluInlantuita ListaSimpluInlantuita::operator=(ListaSimpluInlantuita l){
    ListaSimpluInlantuita l3(l);
    return l3;
}

ListaSimpluInlantuita::ListaSimpluInlantuita(const ListaSimpluInlantuita &l){
    head = new Nod(-1, NULL);
    tail = head;
    int k = 0;
    setCounter(k);
    Nod *p = l.head;
    cout<<p->info;
    int i;
    for(i = 0; i < l.n; i++){
        push(p->getInfo(), i);
        p = p->getNext();
    }
}

ListaSimpluInlantuita::~ListaSimpluInlantuita(void){
    Nod *p = head;
    Nod *q;
    while( p!= NULL){
        q = p;
        p = p->next;
        delete q;
    }
}

void ListaSimpluInlantuita::push(int val, int poz){
    if(poz > n || poz < 0 ){ cout << "Position error";}
    else{
        Nod *pushed = new Nod(val, NULL); //decl new nod
        if( head->getInfo() == -1 && poz == 0){cout<<"o creez"<<endl;
            head = pushed;
            tail = pushed;
        }
        else{
            if( poz == 0 ){ //prima poz
                cout<<"sunt pe 0"<<endl;
                pushed->next = head;
                head = pushed;
            }
            else{
                if( poz == n ){
                    cout<<"sunt pe n"<<endl;
                    tail->setNext(pushed);
                    tail = pushed;
                }
                else{
                    cout<<"sunt in int"<<endl;
                    Nod *p = head;
                    for( int i = 0; i < poz-1; i++){
                        p = p->getNext();
                    }
                    pushed->setNext(p->next);
                    p->setNext(pushed);
                }
            }
        }
        n++;
    }
}

ostream& operator<<(ostream& out, ListaSimpluInlantuita &lista){
    Nod *p = lista.getHead();
    int c = 0;
    while(c < lista.getCounter() ){
        out << p->getInfo() << " ";
        p = p->getNext();
        c++;
    }
    out << endl;
    return out;
}

istream& operator>>(istream& in, ListaSimpluInlantuita &lista){
    int nr;
    cout<< "Enter val: ";
    in >> nr;
    lista.push(nr, lista.getCounter());
    return in;
}

void ListaSimpluInlantuita::del(int val){
     Nod *p = head;
     // daca e primul
     if( p->getInfo() == val){
        head = p->getNext();
        delete p;
     }
     else{//altfel caut pana gasesc valoarea
        int contor = 0;
        while( p->getNext()->getInfo() != val ){
            p = p->getNext();
            contor++;
        }
        if(contor != n-1){
            Nod *q = p->getNext();
            p->setNext(p->getNext()->getNext());
            delete q;
        }
        else{
            Nod *q = p->getNext();
            p->setNext(NULL);
            tail = p;
            delete q;
        }
     }
     n--;
}

ListaSimpluInlantuita ListaSimpluInlantuita::operator+(ListaSimpluInlantuita l2){
    ListaSimpluInlantuita l3;
    int k = 0;
    l3.setCounter(k);
    Nod *p = getHead();
    int i;
    for(i = 0; i < getCounter(); i++){
        l3.push(p->getInfo(), i);
        p = p->getNext();
    }

    p = l2.getHead();

    for(int k = 0; k < l2.getCounter(); k++){
        l3.push(p->getInfo(), i);
        i++;
        p = p->getNext();
    }

    return l3;
}

//uses Nod_dublu
class ListaDubluInlantuita: public ListaSimpluInlantuita{
    Nod_dublu *head;
    Nod_dublu *tail;
    Nod_dublu *nod;
    int n;
public:
    ListaDubluInlantuita(){ head = new Nod_dublu(-1, NULL,NULL);
                            tail = head;
                            n = 0;}
    ListaDubluInlantuita(Nod_dublu *h, Nod_dublu *t, int i):ListaSimpluInlantuita(h, t, i){
        head = h;
        tail = t;
        n = i;
    }
    ListaDubluInlantuita(const ListaDubluInlantuita &l);
    ~ListaDubluInlantuita(){}

    Nod_dublu* getHead(){ return head;}
    void setHead(int val){ head->setInfo((int)val);}

    Nod_dublu* getTail(){ return tail;}
    void setTail(char val){ tail->setInfo(val);}

    void setCounter(int c){ n = c;}
    int getCounter(){ return n;}


    virtual void push(int val, int poz);
    virtual void del(int val);
    //operatori:
    virtual ListaDubluInlantuita operator=(ListaDubluInlantuita l);
    virtual ListaDubluInlantuita operator+(ListaDubluInlantuita l2);
    friend ostream& operator<<(ostream& out,const ListaDubluInlantuita &lista);
    friend istream& operator>>(istream& in, ListaDubluInlantuita &lista);
};



ListaDubluInlantuita::ListaDubluInlantuita(const ListaDubluInlantuita &l){
    head = new Nod_dublu(1, NULL, NULL);
    tail = head;
    int k = 0;
    setCounter(k);
    Nod *p = l.head;
    int i;
    for(i = 0; i < l.n; i++){
        push(p->getInfo(), i);
        p = p->getNext();
    }
}

ListaDubluInlantuita ListaDubluInlantuita::operator=(ListaDubluInlantuita l){
    ListaDubluInlantuita l3(l);
    return l3;
}

ListaDubluInlantuita ListaDubluInlantuita::operator+(ListaDubluInlantuita l2){
    ListaDubluInlantuita l3;
    int k = 0;
    l3.setCounter(k);
    Nod_dublu *p = getHead();
    int i;
    for(i = 0; i < getCounter(); i++){
        l3.push(p->getInfo(), i);
        p = p->getNext();
    }

    p = l2.getHead();

    for(int k = 0; k < l2.getCounter(); k++){
        l3.push(p->getInfo(), i);
        i++;
        p = p->getNext();
    }

    return l3;
}

void ListaDubluInlantuita::del(int val){
     Nod_dublu *p = head;
     // daca e primul
     if( p->getInfo() == val){
        p->getNext()->setAnte(NULL);
        head = p->getNext();
        delete p;
     }
     else{//altfel caut pana gasesc valoarea
        int contor = 0;
        while( p->getNext()->getInfo() != val ){
            p = p->getNext();
            contor++;
        }
        if(contor != n-1){
            Nod_dublu *q = p->getNext();
            p->setNext(q->getNext());
            q->getNext()->setAnte(p);
            delete q;
        }
        else{
            Nod_dublu *q = p->getNext();
            p->setNext(NULL);
            tail = p;
            delete q;
        }
     }
     n--;
}

ostream& operator<<(ostream& out, ListaDubluInlantuita &lista){
    Nod_dublu *p = lista.getHead();
    int c = 0;
    while(c < lista.getCounter() ){
        out << p->getInfo() << " ";
        p = p->getNext();
        c++;
    }
    out << endl;
    out << "In sens invers: " << endl;
    p = lista.getTail();

    for(int i = lista.getCounter()-1; i >= 0; i--){
        out << p->getInfo() << " ";
        p = p->getAnte();
    }
    out << endl;
    return out;
}

istream& operator>>(istream& in, ListaDubluInlantuita &lista){
    int nr;
    cout<< "Enter val: ";
    in >> nr;
    lista.push(nr, lista.getCounter());
    return in;
}

void ListaDubluInlantuita::push(int val, int poz){
    if(poz > getCounter() || poz < 0 ){ cout << "Position error";}
    else{
        //decl new nod
        if( head->getInfo() == -1 && poz == 0){cout<<"o creez"<<endl;
            Nod_dublu *pushed = new Nod_dublu(val,NULL,NULL);
            head = pushed;
            tail = pushed;
        }
        else{
            if( poz == 0 ){ //prima poz
                Nod_dublu *pushed = new Nod_dublu(val, NULL, head);
                cout<<"sunt pe 0"<<endl;
                head = pushed;
            }
            else{
                if( poz == getCounter() ){
                    Nod_dublu *pushed = new Nod_dublu(val, tail, NULL);
                    cout<<"sunt pe n"<<endl;
                    tail->setNext(pushed);
                    tail = pushed;
                }
                else{
                    cout<<"sunt in int"<<endl;
                    Nod_dublu *p = head;
                    Nod_dublu *pushed = new Nod_dublu(val, NULL, NULL);
                    for( int i = 0; i < poz-1; i++){
                        p = p->getNext();
                    }
                    pushed->setNext(p->getNext());
                    p->getNext()->setAnte(pushed);
                    p->setNext(pushed);
                    pushed->setAnte(p);
                }
            }
        }
        setCounter(getCounter()+1);
    }
}

//uses Nod_prioritate
class CoadaDePrioritati:ListaDubluInlantuita{
    Nod_prioritate *head;
    Nod_prioritate *tail;
    int n;
public:
    CoadaDePrioritati(){ head = new Nod_prioritate(-1, NULL,NULL, 0);
                         tail = head;
                         n = 0;}
    CoadaDePrioritati(Nod_prioritate *h, Nod_prioritate *t, int i):ListaDubluInlantuita(h,t,i){
        head = h;
        tail = t;
        n = i;
    }
    CoadaDePrioritati(const CoadaDePrioritati &l);
    ~CoadaDePrioritati(){}
    Nod_prioritate* getHead(){ return head;}
    void setHead(int val){ head->setInfo((int)val);}

    Nod_prioritate* getTail(){ return tail;}
    void setTail(char val){ tail->setInfo(val);}

    void setCounter(int c){ n = c;}
    int getCounter(){ return n;}

    virtual void push(int val, int poz);
    virtual void pop();
    //operatori:
    virtual CoadaDePrioritati operator=(CoadaDePrioritati l);
    virtual CoadaDePrioritati operator+(CoadaDePrioritati l2);
    friend ostream& operator<<(ostream& out,const CoadaDePrioritati &lista);
};

void CoadaDePrioritati::push(int val, int prio){
    if(prio<0 ){ cout << "Prio error";}
    else{
        //decl new nod
        if( head->getInfo() == -1 ){ cout<<"o creez"<<endl;
            Nod_prioritate *pushed = new Nod_prioritate(val,NULL,NULL,prio);
            head = pushed;
            tail = pushed;
        }
        else{
            //prio e mai mare ca prio de primul elem, inserez la inceput
            if( prio < head->getPrio()){
                    Nod_prioritate *pushed = new Nod_prioritate(val, NULL, head, prio);
                    cout<<"sunt pe 0"<<endl;
                    head = pushed;
            }
            //e mai mare ca a ultimului
            else if(prio >= tail->getPrio()){
                    Nod_prioritate *pushed = new Nod_prioritate(val, tail, NULL, prio);
                    cout<<"sunt pe n"<<endl;
                    tail->setNext(pushed);
                    tail = pushed;
                }
                else{cout<<"sunt pe undeva";
                    Nod_prioritate *pushed = new Nod_prioritate(val, NULL, NULL, prio);
                    Nod_prioritate *q = head->getNext();
                    while(q->getPrio() > prio ){
                        q = q->getNext();
                    }
                    q->getAnte()->setNext(pushed);
                    pushed->setNext(q->getAnte());
                    pushed->setAnte(q->getAnte()->getNext());
                    q->setAnte(pushed->getNext());

                }
            }
        }
    setCounter(getCounter()+1);
}

CoadaDePrioritati::CoadaDePrioritati(const CoadaDePrioritati &c){
    head = new Nod_prioritate(1, NULL, NULL,0);
    tail = head;
    int k = 0;
    setCounter(k);
    Nod *p = c.head;
    int i;
    for(i = 0; i < c.n; i++){
        push(p->getInfo(), i);
        p = p->getNext();
    }
}


ostream& operator<<(ostream& out, CoadaDePrioritati &coada){
    Nod_dublu *p = coada.getHead();
    int c = 0;

    while(c < coada.getCounter()-1 ){
        out << p->getInfo() << " ";
        p = p->getNext();
        c++;
    }
    out << endl;
    return out;
}
//removes element with least priority
void CoadaDePrioritati::pop(){
    Nod_prioritate *p = head;
    head = head->getNext();
    delete p;
    if( head == NULL ){
        tail = NULL;
    }
}

CoadaDePrioritati CoadaDePrioritati::operator=(CoadaDePrioritati c){
    CoadaDePrioritati c3(c);
    return c3;
}

CoadaDePrioritati CoadaDePrioritati::operator+(CoadaDePrioritati c2){
    CoadaDePrioritati c3;
    int k = 0;
    c3.setCounter(k);
    Nod_prioritate *p = getHead();
    int i;
    for(i = 0; i < getCounter(); i++){
        c3.push(p->getInfo(), i);
        p = p->getNext();
    }

    p = c2.getHead();

    for(int k = 0; k < c2.getCounter(); k++){
        c3.push(p->getInfo(), i);
        i++;
        p = p->getNext();
    }

    return c3;
}

int main(){


    cout<< "exemplu de push in lista, << , >>";
    ListaSimpluInlantuita l1;
    l1.push(1,0);
    l1.push(2,1);
    l1.push(3,2);
    l1.push(9,0);
    l1.push(11, 2);
    //l1.del(3);
    cout<<l1;
    cout<<endl<<"Enter pt l2:"<<endl;
    ListaSimpluInlantuita l2;
    l2.push(14,0);
    l2.push(111,1);
    l2.push(90,2);
    cout<<endl <<"Concatenare:" << endl;
    ListaSimpluInlantuita l3= l1+(l2);

    //constructor de copiere:
    //ListaSimpluInlantuita l3(l1);
    cout << l3;


    ListaDubluInlantuita ld;
    ld.push(1,0);
    ld.push(7,1);
    ld.push(10,2);
    ld.push(54,0);
    ld.push(16,1);
    cout << ld;
    cin >> ld;
    cout << ld;
    ld.del(10);
    cout<<"dupa stergere 10:"<<ld;

    //exemplu fisier
    /*
    ListaSimpluInlantuita fisierEx;
    fin >> fisierEx >> fisierEx >> fisierEx;
    fout << fisierEx;*/

    Nod_prioritate *prio1 = new Nod_prioritate(10,NULL,NULL, 1);
    Nod_prioritate *prio2 = new Nod_prioritate(9, prio1, NULL, 4);
    Nod_prioritate *prio3 = new Nod_prioritate(20, prio2, prio1, 6);

    Nod_prioritate *prio4(prio3);
    cout <<"Prioriatea dupa constructor de copiere "<< prio4->getPrio() << endl;

    Nod_prioritate *prio5 = prio1;
    cout << "prio5 op = prio1 " << prio5->getInfo() << endl;
    //priorit nod ok*/

    CoadaDePrioritati c1;
    c1.push(1,0);
    c1.push(3,1);
    c1.push(10,10);
    c1.push(2,1);

    //Citire, mem, afisare

    int n;
    int x;
    cout << endl <<"Cate liste simple? ";
    cin >> n;
    ListaSimpluInlantuita lista[n];

    //citirea listelor
    for(int i = 0 ; i < n; i++){
        cout << "Cate elemente pentru lista " << i <<" ?" << endl;
        cin >> x;
        for( int k = 0; k < x ; k++ ){
            cin >> lista[i];
        }
    }
    //afisare
    for(int i = 0 ; i < n; i++){
        cout<<lista[i];
    }

    int n2;
    int x2;
    cout << endl <<"Cate liste duble? ";
    cin >> n2;
    ListaDubluInlantuita lista2[n];

    //citirea listelor
    for(int i = 0 ; i < n2; i++){
        cout << "Cate elemente pentru lista " << i <<" ?" << endl;
        cin >> x2;
        for( int k = 0; k < x2 ; k++ ){
            cin >> lista2[i];
        }
    }
    //afisare
    for(int i = 0 ; i < n2; i++){
        cout<<lista2[i];
    }

    int n3;
    int x3;
    cout << endl <<"Cate cozi? ";
    cin >> n3;
    ListaDubluInlantuita coada3[n];

    //citirea listelor
    for(int i = 0 ; i < n3; i++){
        cout << "Cate elemente pentru coada " << i <<" ?" << endl;
        cin >> x3;
        for( int k = 0; k < x3 ; k++ ){
            cin >> coada3[i];
        }
    }
    //afisare
    for(int i = 0 ; i < n3; i++){
        cout<<coada3[i];
    }
    return 0;
}
