#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#define red_color "\x1b[31m"
#define green_color "\x1b[32m"
#define yellow_color "\x1b[33m"
#define cyan_color "\x1b[36m"
#define reset_color "\x1b[0m"
using namespace std;

class Masa {
private:
    int id;
    int capacitate;
    string disponibil;
    string nume;
    string prenume;
    int zi;
    int luna;
    int an;
    int ora;


public:
    Masa(){};
    int get_id(){
        return this -> id;
    }
    int get_capacitate(){
        return this -> capacitate;
    }
    string get_disponibil(){
        return this -> disponibil;
    }
    string get_nume() {
        return this -> nume;
    }
    string get_prenume() {
        return this -> prenume;
    }
    int get_zi() {
        return this -> zi;
    }
    int get_luna() {
        return this -> luna;
    }
    int get_an() {
        return this -> an;
    }
    int get_ora() {
        return this -> ora;
    }
    void set_id(int i){
        this -> id = i;
    }
    void set_capacitate(int c){
        this -> capacitate = c;
    }
    void set_disponibil(string d){
        this -> disponibil = d;
    }
    void set_nume(string n) {
        this -> nume = n;
    }
    void set_prenume(string p) {
        this -> prenume = p;
    }
    void set_zi(int z) {
        this -> zi = z;
    }
    void set_luna(int l) {
        this -> luna = l;
    }
    void set_an(int a) {
        this -> an = a;
    }
    void set_ora(int o) {
        this -> ora = o;
    }
};

bool verificare_data(int ziua, int luna, int an)
{
    if(an >= 2022 && an<= 2025){
        if(luna>=1 && luna<=12){
            if(((ziua>=1 && ziua<=31) && (luna==1 || luna==3 || luna==5 || luna==7 || luna==8 || luna==10 || luna==12)) ||
               ((ziua>=1 && ziua<=30) && (luna==4 || luna==6 || luna==9 || luna==11)) ||
               ((ziua>=1 && ziua<=28) && (luna==2)) ||
               ((ziua==29 && luna==2 && (an%400==0 ||(an%4==0 && an%100!=0))))){
                return false;
            }
        }
    }
    return true;
}
void adaugare_masa(vector <Masa> data, int capacitate) {
    fstream fout;
    fout.open("rezervari.csv", ios::out | ios::app);
    fout << (data.back().get_id())+1 << ","
         << capacitate << ","
         << "Da" << "\n";
}
void stergere_masa(vector<Masa> data, int id){
    fstream fin, fout;
    fin.open("rezervari.csv", ios::in);
    fout.open("temp.csv", ios::out);
    int id_check, count = 0, i;
    string line, word;
    vector<string> row;
    while (!fin.eof()) {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        int row_size = row.size();
        id_check = stoi(row[0]);
        if (id_check != id) {
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else {
            count = 1;
        }
        if (fin.eof())
            break;
    }
    if (count == 1)
        cout << "Masa stearsa cu success\n";
    else
        cout << "Eroare necunoscuta\n";
    fin.close();
    fout.close();
    remove("rezervari.csv");
    rename("temp.csv", "rezervari.csv");
}
void rezervare_masa(vector<Masa> data, int id)
{
    fstream fin, fout;
    fin.open("rezervari.csv", ios::in);
    fout.open("temp.csv", ios::out);
    string nume, prenume;
    int zi, luna, an, ora;
    int id_check, count = 0, i;
    string line, word;
    vector<string> row;


    cout << "Inserati numele: ";
    cin>>nume;
    cin.ignore(100,'\n');
    cout << "Inserati prenumele: ";
    getline(cin, prenume);
    cin.ignore(100,'\n');
    cout << "Inserati ziua: ";
    cin>>zi;
    cout << "Inserati luna: ";
    cin>>luna;
    cout << "Inserati anul: ";
    cin>>an;
    cout << "Inserati ora: ";
    cin>>ora;

    if(zi <= 10 && luna < 6 && an != 2022 ){
        cout<<"Data incorecta pt viitor. Va rugam reintroduce-ti data!"<<endl;
        return;
    }

    if(verificare_data(zi,luna,an)) {
        cout<<"Data incorecta. Va rugam reintroduce-ti data!"<<endl;
        return;
    }

    while (!fin.eof()) {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        id_check = stoi(row[0]);
        int row_size = row.size();
        if (id_check == id) {
            count = 1;
            row[2] = "Nu";
            row.push_back(nume);
            row.push_back(prenume);
            row.push_back(to_string(zi));
            row.push_back(to_string(luna));
            row.push_back(to_string(an));
            row.push_back(to_string(ora));
            row_size = row.size();
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else {
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        if (fin.eof())
            break;
    }
    if (count == 0)
        cout << "ID-ul este invalid, incercati din nou\n";

    fin.close();
    fout.close();
    remove("rezervari.csv");
    rename("temp.csv", "rezervari.csv");
}
void anulare_masa(vector<Masa> data, int id)
{
    fstream fin, fout;
    fin.open("rezervari.csv", ios::in);
    fout.open("temp.csv", ios::out);
    int id_check, count = 0, i;
    string line, word;
    vector<string> row;

    while (!fin.eof()) {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        id_check = stoi(row[0]);
        int row_size = row.size();
        if (id_check == id) {
            count = 1;
            row[2] = "Da";
            row.erase(row.begin()+3,row.end());
            row_size = row.size();
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else {
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        if (fin.eof())
            break;
    }
    if (count == 0)
        cout << "ID-ul este invalid, incercati din nou\n";

    fin.close();
    fout.close();
    remove("rezervari.csv");
    rename("temp.csv", "rezervari.csv");
}
void cautare_masa_capacitate(vector<Masa> data, int capacitate) {
    int count = 0;
    for (auto &i: data) {
        {
            if (i.get_capacitate() == capacitate) {
                count++;
                cout << "ID-ul mesei este: " << i.get_id() << " si capacitatea este de: " << i.get_capacitate()
                     << " persoane" << endl;
            }
        }
    }
    if(count <= 0){
        cout << "Nu exista mese cu aceasta capacitate" << endl;
    }
}
vector <Masa> citire() {
    vector <Masa> content;
    Masa mese;
    string line, word;
    vector < string > row;
    fstream file("rezervari.csv", ios:: in );
    if (file.is_open()) {
        while (getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ',')) {
                row.push_back(word);
            }
            if (row[2] == "Da"){
                mese.set_id(stoi(row[0]));
                mese.set_capacitate(stoi(row[1]));
                mese.set_disponibil(row[2]);
            }else{
                mese.set_id(stoi(row[0]));
                mese.set_capacitate(stoi(row[1]));
                mese.set_disponibil(row[2]);
                mese.set_nume(row[3]);
                mese.set_prenume(row[4]);
                mese.set_zi(stoi(row[5]));
                mese.set_luna(stoi(row[6]));
                mese.set_an(stoi(row[7]));
                mese.set_ora(stoi(row[8]));
            }
            content.push_back(mese);
        }
    } else
        cout << "Nu se poate\n";
    return content;
}

int main() {
    int x, y;
    puts(cyan_color"██████╗░███████╗███████╗███████╗██████╗░██╗░░░██╗░█████╗░██████╗░███████╗  ███╗░░░███╗███████╗░██████╗███████╗" reset_color );
    puts(cyan_color"██╔══██╗██╔════╝╚════██║██╔════╝██╔══██╗██║░░░██║██╔══██╗██╔══██╗██╔════╝  ████╗░████║██╔════╝██╔════╝██╔════╝" reset_color );
    puts(cyan_color"██████╔╝█████╗░░░░███╔═╝█████╗░░██████╔╝╚██╗░██╔╝███████║██████╔╝█████╗░░  ██╔████╔██║█████╗░░╚█████╗░█████╗░░" reset_color );
    puts(cyan_color"██╔══██╗██╔══╝░░██╔══╝░░██╔══╝░░██╔══██╗░╚████╔╝░██╔══██║██╔══██╗██╔══╝░░  ██║╚██╔╝██║██╔══╝░░░╚═══██╗██╔══╝░░" reset_color );
    puts(cyan_color"██║░░██║███████╗███████╗███████╗██║░░██║░░╚██╔╝░░██║░░██║██║░░██║███████╗  ██║░╚═╝░██║███████╗██████╔╝███████╗" reset_color );
    puts(cyan_color"╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝  ╚═╝░░░░░╚═╝╚══════╝╚═════╝░╚══════╝" reset_color );
    do {
        puts("---------------------------------------------------------------------------------------------------------------");
        puts("");
        puts(yellow_color "Apasa 1 pentru a vedea mesele disponibile" reset_color);//Done
        puts(yellow_color "Apasa 2 pentru a adauga o masa" reset_color);
        puts(yellow_color "Apasa 3 pentru a sterge o masa" reset_color);
        puts(yellow_color "Apasa 4 pentru a rezerva o masa" reset_color);
        puts(yellow_color "Apasa 5 pentru a anula o rezervare" reset_color);
        puts(yellow_color "Apasa 6 pentru a cauta o masa dupa capacitate" reset_color);
        puts(red_color "Apasa 0 pentru a iesi" reset_color);
        cout << cyan_color "Tasta: " reset_color;
        cin >> x;
        switch (x) {
            case 1: {
                vector<Masa> mese = citire();
                cout << green_color "Mesele disponibile sunt:" reset_color << endl;
                int count = 0;
                for (auto & i : mese) {
                    if (i.get_disponibil() =="Da"){
                        count++;
                        cout << "ID-ul mesei este: " << i.get_id()<< " si capacitatea este de: " << i.get_capacitate() << " persoane" << endl;
                    }
                }
                if (count <= 0) {
                    cout << "Nu exista mese disponibile";
                }
                break;
            }
            case 2: {
                vector<Masa> mese = citire();
                int capacitate;
                cout << green_color "Introduceti capacitatea mesei: " reset_color;
                cin >> capacitate;
                adaugare_masa(mese, capacitate);
                break;
            }
            case 3: {
                vector<Masa> mese = citire();
                int id;
                for (auto & i : mese) {
                    cout << "ID-ul mesei este: " << i.get_id()<< " si capacitatea este de: " << i.get_capacitate() << " persoane" << endl;
                }
                cout << "Inserati id-ul mesei care doriti sa o stergeti: ";
                cin >> id;
                for (int i = 0; i < mese.size(); i++) {
                    if (mese[i].get_id() == id) {
                        stergere_masa(mese, id);
                    }
                }
                break;
            }
            case 4:
            {
                vector<Masa> mese = citire();
                int id, count = 0;
                for (auto & i : mese) {
                    if (i.get_disponibil() =="Da"){
                        count++;
                        cout << "ID-ul mesei este: " << i.get_id()<< " si capacitatea este de: " << i.get_capacitate() << " persoane" << endl;
                    }
                }
                if(count>0){
                    cout << "Inserati id-ul mesei care doriti sa o rezervati: ";
                    cin >> id;
                    rezervare_masa(citire(),id);
                }else{
                    cout<<"Nu exista mese disponibile pentru inchiriat";
                }

                break;
            }
            case 5:
            {
                vector<Masa> mese = citire();
                int id, count = 0;
                for (auto & i : mese) {
                    if (i.get_disponibil() =="Nu"){
                        count++;
                        cout << "ID-ul mesei este: " << i.get_id()<< " si capacitatea este de: " << i.get_capacitate() << " persoane, " << "pentru numele de: "<< i.get_nume() << endl;
                    }
                }
                if(count>0){
                    cout << "Inserati id-ul mesei caruia doriti sa anulati rezervarea: ";
                    cin >> id;
                    anulare_masa(citire(),id);
                }else{
                    cout<<"Nu exista mese rezervate de anulat";
                }
                break;
            }
            case 6:
            {
                vector<Masa> mese = citire();
                int capacitate;
                cout<<green_color "Introduceti capacitatea cautata: " reset_color;
                cin>>capacitate;
                cautare_masa_capacitate(mese,capacitate);
                break;
            }
            case 0: {
                exit(0);
            }
            default: {
                cout << red_color "Optiune invalida" reset_color << endl;
            }
        }
        puts(green_color "Apasa 1 pentru a reveni la meniul principal" reset_color);
        puts(red_color "Apasa 0 pentru a iesi" reset_color);
        cout << cyan_color "Tasta: " reset_color;
        cin >> y;
        cout << endl;
        if (y == 0)
            exit(0);
    }
    while (1);
    return 0;
}
