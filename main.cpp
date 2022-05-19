#include <iostream>
#include <string.h>

using namespace std;

int numarProduse;
int numarClienti;
int numarComenzi;

class IOInterface {
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& write(ostream& out) = 0;
};

class Produs: IOInterface{
protected:
    string nume;
    float pret;
    bool disponibil;
    int nrRatinguri;
    int* rating;
    string culoare;

public:
    Produs(){
        this->nume = "Anonim";
        this->pret = 0;
        this->disponibil = false;
        this->rating = NULL;
        this->nrRatinguri = 0;
        this->culoare = "-";
    }

    Produs(string nume, float pret, bool disponibil, int nrRatinguri, int* rating,  string culoare){
        this->nume = nume;
        this->pret = pret;
        this->disponibil = disponibil;
        this->nrRatinguri = nrRatinguri;
        this->rating = new int[this->nrRatinguri];
        for(int i=0; i<this->nrRatinguri; i++)
            this->rating[i]=rating[i];
        this->culoare = "-";
    }

    Produs(const Produs& prod){
        this->nume = prod.nume;
        this->pret = prod.pret;
        this->disponibil = prod.disponibil;
        this->nrRatinguri = prod.nrRatinguri;
        this->rating = new int[this->nrRatinguri];
        for(int i=0; i<this->nrRatinguri; i++)
            this->rating[i] = prod.rating[i];
        this->culoare = prod.culoare;
    }

    ~Produs(){
        if(this->rating != NULL)
            delete[] this->rating;
    }

    Produs& operator=(const Produs& prod){
        if(this != &prod){
            if(this->rating != NULL)
                delete[] this->rating;
            this->nume = prod.nume;
            this->pret = prod.pret;
            this->disponibil = prod.disponibil;
            this->nrRatinguri = prod.nrRatinguri;
            this->rating = new int[this->nrRatinguri];
            for(int i = 0; i < this->nrRatinguri; i++)
                this->rating[i] = prod.rating[i];
            this->culoare = prod.culoare;
        }
        return *this;
    }

    istream& read(istream&in){
       cout<<"Numele produsului este: ";
        in>>this->nume;
        cout<<"Pretul produsului este: ";
        in>>this->pret;
        cout<<"Produsul este disponibil(0/1): ";
        in>>this->disponibil;
        cout<<"Numarul de ratinguri ale produsului este: ";
        in>>this->nrRatinguri;
        cout<<"Ratinguri: ";
        this->rating = new int[this->nrRatinguri];
        for (int i=0; i<this->nrRatinguri; i++)
            in>>this->rating[i];
        cout<<"Culoarea produsului este: ";
        in>>this->culoare;
        cout<<endl;
        return in;
    }

    friend istream& operator>>(istream& in, Produs& prod){
        return prod.read(in);
    }

    ostream& write(ostream& out){
        out<<"Numele produsului este "<<this->nume<<endl;
        out<<"Pretul produsului este "<<this->pret<<endl;
        if(this->disponibil)
            out<<"Produsul este disponibil"<<endl;
        else out<<"Produsul nu este disponibil"<<endl;
        out<<"Produsul are "<<this->nrRatinguri<<" ratinguri"<<endl;
        if (this->nrRatinguri){
            out<<"Acestea sunt urmatoarele: ";
            for (int i=0; i<this->nrRatinguri; i++)
                out<<this->rating[i]<<"/10 ";
            out<<endl;}
        out<<"Culoarea produsului este "<<this->culoare<<endl<<endl;
        return out;
    }

    friend ostream& operator<<(ostream& out, Produs& prod){
        return prod.write(out);
    }

    virtual void specProdus(){
        cout<<"Produsul nu este complet";
    };
};

class Tastatura : public Produs{
private:
    int nrTaste;
    bool display;
public:
    Tastatura():Produs(){
        this->nrTaste = 0;
        this->display = false;
    }

    Tastatura(int nrTaste, bool display, string nume, float pret, bool disponibil, int nrRatinguri, int* rating,  string culoare):Produs(nume, pret, disponibil, nrRatinguri, rating,  culoare){
        this->nrTaste = nrTaste;
        this->display = display;
    }

    ~Tastatura(){}

    Tastatura(const Tastatura& tastatura) : Produs(tastatura){
        this->nrTaste = tastatura.nrTaste;
        this->display = tastatura.display;
    }

    Tastatura& operator=(const Tastatura& tastatura){
        if (this!=&tastatura){
            Produs::operator=(tastatura);
            this->nrTaste = tastatura.nrTaste;
            this->display = display;
        }
        return *this;
    }

    istream& read(istream& in){
        Produs::read(in);
        cout << "Cate taste are: ";
        in >> this->nrTaste;
        cout << "Are display (1/0): ";
        in >> this->display;
        cout << endl<<endl;
        return in;
    }

    friend istream& operator>>(istream& in, Tastatura& tastatura){
        return tastatura.read(in);
    }

    ostream& write(ostream& out){
        Produs::write(out);
        out << "Numar de taste: ";
        out << this->nrTaste<<endl;
        out << "Are display: ";
        out << this->display<<endl<<endl;
        return out;
    }

    friend ostream& operator<<(ostream& out, Tastatura& tastatura){
        return tastatura.write(out);
    }

    void set(int nr){
        this->nrTaste=nr;
    }

    void set(bool bol){
        this->display = bol;
    }

    void specProdus()const{
        cout << "Are " << this->nrTaste << " taste"<<endl;
        if (this->display == false)
            cout<<"Nu are display"<<endl;
        else cout<<"Are display"<<endl;
    }
};

class Mouse : public Produs{
private:
    int dpi;
public:
    Mouse():Produs(){
        this->dpi = 0;
    }

    Mouse(int dpi, string nume, float pret, bool disponibil, int nrRatinguri, int* rating,  string culoare):Produs(nume, pret, disponibil, nrRatinguri, rating, culoare){
        this->dpi = this->dpi;
    }

    ~Mouse(){}

    Mouse(const Mouse& mouse) : Produs(mouse){
        this->dpi = mouse.dpi;
    }

    Mouse& operator=(const Mouse& mouse){
        if (this!=&mouse){
            Produs::operator=(mouse);
            this->dpi = mouse.dpi;
        }
        return *this;
    }

    istream& read(istream& in){
        Produs::read(in);
        cout << "Cati DPI are: ";
        in >> this->dpi;
        cout<<endl;
        return in;
    }

    friend istream& operator>>(istream& in, Mouse& mouse){
        return mouse.read(in);
    }

    ostream& write(ostream& out){
        Produs::write(out);
        out << "Numar DPI: ";
        out << this->dpi<<endl<<endl;
        return out;
    }

    friend ostream& operator<<(ostream& out, Mouse& mouse){
        return mouse.write(out);
    }

    void specProdus(){
        cout << "Are " << this->dpi << " DPI"<<endl;
    }
};


class Client{
private:
    char* nume;
    string adresa;
    string mail;
    float puncteLoialitate;
    int nrComenzi;
    int* idComenzi;

public:
    Client(){
        this->nume = new char[strlen("Anonim")+1];
        strcpy(this->nume,"Anonim");
        this->adresa = "-";
        this->mail = "-";
        this->puncteLoialitate = 0;
        this->nrComenzi = 0;
        this->idComenzi = NULL;
    }

    Client(char* nume , string adresa , string mail , float puncteLoialitate , int nrComenzi , int* idComenzi ){
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
        this->adresa = adresa;
        this->mail = mail;
        this->puncteLoialitate = puncteLoialitate;
        this->nrComenzi = nrComenzi;
        this->idComenzi = new int[this->nrComenzi];
        for(int i = 0; i < this->nrComenzi; i++)
            this->idComenzi[i]=idComenzi[i];
    }

    Client(const Client& client){
        if(client.nume!=NULL){
            this->nume = new char[strlen(client.nume)+1];
            strcpy(this->nume, client.nume);}
        this->adresa = client.adresa;
        this->mail = client.mail;
        this->puncteLoialitate = client.puncteLoialitate;
        this->nrComenzi = client.nrComenzi;
        this->idComenzi = new int[nrComenzi];
        for(int i=0; i<this->nrComenzi; i++)
            this->idComenzi[i] = client.idComenzi[i];
    }

    ~Client(){
        if(this->nume != NULL)
            delete[] this->nume;
        if(this->idComenzi != NULL)
            delete[] this->idComenzi;
    }

    Client& operator=(const Client& client){
        if (this != &client){
            if(this->idComenzi != NULL)
                delete[] this->idComenzi;
            if(this->nume != NULL)
                delete[] this->nume;
            if(client.nume != NULL)
                this->nume = new char[strlen(client.nume)+1];
            strcpy(this->nume,client.nume);
            this->adresa = client.adresa;
            this->mail = client.mail;
            this->puncteLoialitate = client.puncteLoialitate;
            this->nrComenzi = client.nrComenzi;
            this->idComenzi = new int[this->nrComenzi];
            for(int i=0; i<this->nrComenzi; i++)
                this->idComenzi[i]=client.idComenzi[i];
        }
    }

    friend istream& operator>>(istream&in, Client& client){
        cout<<"Numele clientului este: ";
        char auxnume[25];
        in>>auxnume;
        delete[] client.nume;
        client.nume = new char[strlen(auxnume)+1];
        strcpy(client.nume, auxnume);
        cout<<"Adresa clientului este: ";
        in>>client.adresa;
        cout<<"Mailul clientului este: ";
        in>>client.mail;
        cout<<"Cate puncte de loialitate are clientul: ";
        in>>client.puncteLoialitate;
        cout<<endl;
        return in;
    }

    friend ostream& operator<<(ostream&out, const Client& client){
        if(client.nume)
            out<<"Numele clientului este "<<client.nume<<endl;
        out<<"Adresa clientului este "<<client.adresa<<endl;
        out<<"Mailul clientului este "<<client.mail<<endl;
        out<<"Clientul are "<<client.puncteLoialitate<<" puncte de loialitate"<<endl;
        out<<"Clientul are "<<client.nrComenzi<<" comenzi"<<endl;
        if (client.nrComenzi){
            out<<"\nAcestea sunt urmatoarele: ";
            for(int i=0; i<client.nrComenzi; i++)
                out<<"Comanda cu id "<<client.idComenzi[i]<<endl;
            }
        cout<<endl;
        return out;
    }

    void afisareComenziClient(){
        if(this->nrComenzi){
            cout<<this->nume<<" are "<<this->nrComenzi<<" comenzi"<<endl;
            cout<<"Acestea sunt urmatoarele: ";
            for(int i = 0; i<this->nrComenzi; i++)
                cout<<this->idComenzi[i];

        }
    }

};

class Comanda{
private:
    Client client;
    int nrProduse;
    Produs *produse;
    const int idComanda;
    static int contorComenzi;

public:
    Comanda():idComanda(contorComenzi++){
        Client client;
        this->client = client;
        this->nrProduse = 0;
        this->produse = NULL;
    }

    Comanda(Client client, int nrProduse, Produs* produse):idComanda(contorComenzi++){
        this->client = client;
        this->nrProduse = nrProduse;
        this->produse = new Produs[this->nrProduse];
        for(int i = 0; i < this->nrProduse; i++)
            this->produse[i]=produse[i];
    }

    Comanda(const Comanda& cmd):idComanda(cmd.idComanda){
        this->client = cmd.client;
        this->nrProduse = cmd.nrProduse;
        this->produse = new Produs[this->nrProduse];
        for(int i = 0; i < this->nrProduse; i++)
            this->produse[i] = cmd.produse[i];
    }

    ~Comanda(){
        if(this->produse != NULL)
            delete[] this->produse;
    }

    Comanda& operator=(const Comanda& cmd){
        this->client = cmd.client;
        this->nrProduse = cmd.nrProduse;
        this->produse = new Produs[this->nrProduse];
        for(int i = 0; i< this->nrProduse; i++)
            this->produse[i] = cmd.produse[i];
    }

    friend istream& operator>>(istream&in, Comanda& cmd){
        cin>>cmd.client;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Comanda& cmd){
        out<<"Comanda este data de:"<<endl<<cmd.client;
        out<<"Comanda are "<<cmd.nrProduse<<" produse"<<endl;
        out<<"Acestea sunt: "<<endl;
        for(int i = 0; i< cmd.nrProduse; i++){
            out<<cmd.produse[i];
           // cout<<endl;
        }
        //out<<endl;
        out<<"Comanda are id-ul "<<cmd.idComanda<<endl<<endl;
    }
};
int Comanda::contorComenzi=1000;

class Magazin{
private:
    string nume;
    int nrProduse;
    Produs *produse[100];
    Client clienti[100];
    Comanda comenzi[100];
    string adresa;
    double vanzariTotale;

public:
    Magazin(){
        this->nume = "PeriPC";
        this->nrProduse = 0;
        this->adresa = "str. Perifericelor";
        this->vanzariTotale = 69420.3;
    }

    Magazin(string nume, int nrProduse, Produs* produse, string adresa, double vanzariTotale){
        this->nume = nume;
        this->nrProduse = nrProduse;
        for(int i = 0; i< this->nrProduse; i++){
            this->produse[i] = &produse[i];
            }
        this->adresa = adresa;
        this->vanzariTotale = vanzariTotale;
    }

    Magazin(const Magazin& mag){
        this->nume = mag.nume;
        this->nrProduse = mag.nrProduse;
        for(int i = 0; i < this->nrProduse; i++)
            this->produse[i] = mag.produse[i];
        this->adresa = mag.adresa;
        this->vanzariTotale = mag.vanzariTotale;
    }

    ~Magazin(){
        if(this->produse != NULL)
            delete[] this-> produse;
        if(this->clienti != NULL)
            delete[] this-> clienti;
        if(this->comenzi != NULL)
            delete[] this-> comenzi;
    }

    Magazin& operator=(const Magazin& mag){
        this->nume = mag.nume;
        this->nrProduse = mag.nrProduse;
        for(int i = 0; i < this->nrProduse; i++)
            this->produse[i] = mag.produse[i];
        this->adresa = mag.adresa;
        this->vanzariTotale = mag.vanzariTotale;
    }

    friend istream& operator>>(istream&in, Magazin& mag){
        cout<<"Numele magazinului este: ";
        in>>mag.nume;
        cout<<"Adresa magazinului este: ";
        in>>mag.adresa;
        int alegere, continua = 1;
        mag.nrProduse = 0;
        while(continua == 1){
            cout<<"1.Add product\n";
            cout<<"2.Stop\n"<<endl;
            cin>>alegere;
            cout<<endl;
            switch (alegere){
                case 1:{
                    Produs* aux = new Produs[mag.nrProduse];
                    for(int i = 0; i< mag.nrProduse; i++)
                        //aux[i] = mag.produse[i];
                    delete[] mag.produse;
                    mag.nrProduse++;
                    Produs prod;
                    cin>>prod;
                    for(int i = 0; i < mag.nrProduse-1; i++)
                      //  mag.produse[i]=aux[i];
                  //  mag.produse[mag.nrProduse-1]=prod;
                    break;
                }
                case 2:{
                    continua = 0;
                    break;
                }
                default: {
                    cout<<"Comanda incorecta\n"<<endl;
                    break;
                }
            }
        }
    }

    friend ostream& operator<<(ostream& out, const Magazin& mag){
        out<<"Magazinul se numeste "<<mag.nume<<endl;
        out<<"Adresa magazinului este "<<mag.adresa<<endl;
        out<<"Magazinul are vanzari totale in valoare de "<<mag.vanzariTotale<<" lei"<<endl<<endl;
    }

    void meniu(){
    int alegere, continua = 1;
    while(continua){
        cout<<"Menu"<<endl;
        cout<<"1.Create"<<endl;
        cout<<"2.Read"<<endl;
        //cout<<"3.Update"<<endl;
        //cout<<"4.Delete"<<endl;
        cout<<"0.Stop"<<endl;
        cout<<endl;
        cin>>alegere;
        cout<<endl;
        switch(alegere){
            case 1:{
                int alegereDoi;
                cout<<"1.Create product"<<endl;
                cout<<"2.Create order"<<endl;
                cout<<"3.Create customer"<<endl;
                cout<<"0.Cancel"<<endl;
                cout<<endl;
                cin>>alegereDoi;
                cout<<endl;

                switch(alegereDoi){
                    case 1:{
                        int ans;
                        cout<<"Tastatura (0) sau Mouse(1)? ";
                        cin>>ans;
                        if (ans == 0){
                            Tastatura aux;
                            cin>>aux;
                            produse[nrProduse] = new Tastatura(aux);
                            this->nrProduse++;
                        }
                        if (ans == 1){
                            Mouse aux;
                            cin>>aux;
                            produse[nrProduse] = new Mouse(aux);
                            this->nrProduse++;
                        }
                        break;
                    }
                    case 2:{
                        cout<<"Add customer number ";
                        int custnrr, nrProd, idProd;
                        cin>>custnrr;
                        cout<<endl;
                      //  Comanda c(this->clienti[custnrr]);
                        //cout<<c;
                        cout<<"Add number of products ";
                        cin>>nrProd;
                        cout<<endl;
                        Produs *produse[nrProd];
                        for(int i = 0; i < nrProd; i++){
                            cout<<"Enter product ID ";
                            cin>>idProd;
                            cout<<endl;
                            produse[i] = this->produse[idProd];
                        }
                        Comanda c(this->clienti[custnrr], nrProd, *produse);
                        comenzi[numarComenzi++] = c;
                        //cin>>this->comenzi[numarComenzi++];
                        break;
                    }
                    case 3:{
                        cin>>this->clienti[numarClienti++];
                        break;
                    }
                    case 0:{
                        cout<<"Creation cancelled"<<endl<<endl;
                        break;
                    }
                    default:{
                        cout<<"Wrong command"<<endl<<endl;
                        break;
                    }
                }
                break;}
            case 2:{
                int alegereTrei;
                cout<<"1.Read product"<<endl;
                cout<<"2.Read order"<<endl;
                cout<<"3.Read customer"<<endl;
                cout<<"0.Cancel"<<endl;
                cout<<endl;
                cin>>alegereTrei;
                cout<<endl;
                switch(alegereTrei){
                    case 1:{
                        int prodnr;
                        cout<<"Product number? ";
                        cin>>prodnr;
                        cout<<endl;
                        cout<<*produse[prodnr];
                        break;
                    }
                    case 2:{
                        int ordnr;
                        cout<<"Order number? ";
                        cin>>ordnr;
                        cout<<endl;
                        cout<<this->comenzi[ordnr];
                        break;
                    }
                    case 3:{
                        int custnr;
                        cout<<"Customer number? ";
                        cin>>custnr;
                        cout<<endl;
                        cout<<this->clienti[custnr];
                        break;
                    }
                    case 0:{
                        cout<<"Read cancelled"<<endl<<endl;
                        break;
                    }
                    default:{
                        cout<<"Wrong command"<<endl<<endl;
                        break;
                    }
                }
                break;}
            case 3:{
                cout<<"Updating is not yet allowed"<<endl<<endl;
                break;}
            case 4:{
                cout<<"Deleting is not yet allowed"<<endl<<endl;
                break;}
            case 0:{
                continua = 0;
                cout<<"Menu has been closed"<<endl;
                break;}
            default:{
                cout<<"Wrong command"<<endl;
                break;}
            }
        }
    }
};

int main(){
    Magazin mag;
    cout<<mag;
    mag.meniu();

    return 0;
}
