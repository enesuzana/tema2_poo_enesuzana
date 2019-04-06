#include <iostream>

using namespace std;

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

    int getInfo(){
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
public:
    Nod_dublu(){ante = NULL;}
    Nod_dublu(char i, Nod_dublu *anterior,  Nod_dublu *nextn):Nod(i, nextn){
        ante = anterior;
    }
    Nod_dublu(const Nod_dublu &n): Nod(n){ ante = n.ante;}
    virtual ~Nod_dublu(){
    }
    Nod_dublu *getAnte(){ return ante; }
    void setAnte(Nod_dublu *nod){ ante = nod; }
};

class Nod_prioritate:public Nod_dublu{
    int prio;
public:
    Nod_prioritate(){ prio = 0; }
    Nod_prioritate(char i, Nod_prioritate *anterior, Nod_prioritate *nextn, int priority):Nod_dublu(i, anterior, nextn){
        prio = priority;
    }
    Nod_prioritate(const Nod_prioritate &n):Nod_dublu(n){prio = n.prio;}
    ~Nod_prioritate(){}
    int getPrio(){ return prio; }
    void setPrio(int pr){prio = pr; }//f

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
    //~ListaSimpluInlantuita();
    Nod* getHead(){ return head;}
    void setHead(int val){ head->setInfo((int)val);}
    Nod* getTail(){ return tail;}
    void setTail(char val){ tail->setInfo(val);}

    Nod* getNextNod(){ return nod->getNext();}
    void setNextNod(Nod *next){ nod->setNext(next);}

    int getNodInfo(){ return nod->getInfo();}
    void setNodInfo(int inf){ nod->setInfo(inf);}

    void setCounter(int c){ n = c;}
    int getCounter(){ return n;}

    Nod* getNod(){return nod;}

    virtual void push(int val, int poz);
    virtual void del(int val);
    virtual ListaSimpluInlantuita operator+(ListaSimpluInlantuita l2);
    friend ostream& operator<<(ostream& out,const ListaSimpluInlantuita &lista);
    friend istream& operator>>(istream& in, ListaSimpluInlantuita &lista);
};

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
/*
ListaSimpluInlantuita::~ListaSimpluInlantuita(){
    Nod *p = head;
    Nod *q;
    while( p!= NULL){
        q = p;
        p = p->next;
        delete q;
    }
}*/

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
class ListaDubluInlantuita:ListaSimpluInlantuita{
    Nod_dublu *head;
    Nod_dublu *tail;
    Nod_dublu *nod;
public:
    ListaDubluInlantuita(){}
    ListaDubluInlantuita(Nod_dublu *head, Nod_dublu *tail, int i):ListaSimpluInlantuita(head, tail, i){}
    void setAnteNod(Nod_dublu *prev){ nod->setAnte(prev); }
    Nod_dublu* getAnteNod(){ return nod->getAnte(); }
};
//uses Nod_prioritate
class CoadaDePrioritati:ListaDubluInlantuita{
    Nod_prioritate *head;
    Nod_prioritate *tail;
    Nod_prioritate *nod;
    int prio;
public:
    CoadaDePrioritati(){prio = 0;}
    CoadaDePrioritati(Nod_prioritate *head, Nod_prioritate *tail, int i, int priority):
        ListaDubluInlantuita(head, tail, i){prio = priority;
    }
    void setPrioNod(int pr){ nod->setPrio(pr);}
    int getPrioNod(){ return nod->getPrio();}
};

int main(){/*
    Nod *t = new Nod(1,NULL);
    Nod_dublu *p3 = new Nod_dublu(5, NULL, NULL);
    Nod_dublu *p1= new Nod_dublu(1, NULL, p3);
    Nod_dublu *p = new Nod_dublu(2, p1 , NULL);*/
    // inh + constr param ok
    /*
    Nod_prioritate *prio1 = new Nod_prioritate(12, NULL, NULL, 1);
    Nod_prioritate *prio2 = new Nod_prioritate(9, prio1, NULL, 4);
    Nod_prioritate *prio3 = new Nod_prioritate(20, prio2, prio1, 6);
    //cout << prio3->getNext()->getInfo();
    delete prio3;
    cout << prio3;
    //priorit nod ok */

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
    //ListaSimpluInlantuita l3= l1+(l2);

    //constructor de copiere:
    ListaSimpluInlantuita l3(l1);
    cout << l3;
    //

    return 0;
}
