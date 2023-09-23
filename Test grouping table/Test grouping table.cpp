#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include<iomanip>
#include<vector>
#include<math.h>

using namespace std;

class hoba
{
private:
    string name;
    int x=0;
    int y=0;
    string type;
    long double time;
    static int n;//object's number in base/////////////////////////
    int nomb;//private object's number/////////////////////////////
    static fstream bob;
    static int gm;//group marker for function
    string gn;//group name
    static int count;//quantity of elements in group
    int distance = 0;

public:

    hoba()
    {
        auto now = chrono::system_clock::now();
        time_t end_time = chrono::system_clock::to_time_t(now);
        time = end_time;
        n++;
        nomb = n;
        gn = "ungroup";
    }
    ~hoba(){}

    void add()
    {
        cout << "input data: Name_X_Y_Type"<<'\n';
        cin >> name >> x  >> y  >> type;
    }
    void getinf(vector<hoba*> opa, int n)
    {
        void* peremen = NULL;
        void* peremen2 = NULL;
        void* peremen3 = NULL;
        double per = 0;
        double per2 = 0;
        double per3 = 0;

        for (int f = 0; f < n-1; f++)
        {
            switch (hoba::gm)
            {
            case 1: peremen = &opa[f]->name;  peremen2 = &opa[f + 1]->name; if (f != 0) peremen3 = &opa[f - 1]->name; break;
            case 2: peremen = &opa[f]->type;  peremen2 = &opa[f + 1]->type; if (f != 0) peremen3 = &opa[f - 1]->type; break;
            case 3: peremen = &opa[f]->time;  peremen2 = &opa[f + 1]->time; if (f != 0) peremen3 = &opa[f - 1]->time; break;
            case 4: 
                 per = sqrt((opa[f]->x * opa[f]->x) + (opa[f]->y * opa[f]->y)); 
                 per2 = sqrt((opa[f + 1]->x * opa[f + 1]->x) + (opa[f + 1]->y * opa[f + 1]->y)); 
                 per3 = sqrt((opa[f - 1]->x * opa[f - 1]->x) + (opa[f - 1]->y * opa[f-1]->y));  break;
            case 5: peremen = &opa[f]->type; peremen2 = &opa[f + 1]->type; if (f != 0) peremen3 = &opa[f - 1]->type; break;
            }

            if (f == 0)cout << peremen << '\n';
            else {
                if ((peremen == peremen2) && (peremen != peremen3)) { check(opa, f, n); cout << peremen << '\n'; };
            }
        }
        cout << setw(30) << setiosflags(ios::right) << nomb << " " << name << " " << x << " " << y << " " << type << " " << fixed << time << endl;
    }
    static void open_file();
    void wri() { hoba::open_file(); bob<<nomb<<'\n'<< name << '\n' << x << '\n' << y << '\n' << type << '\n' << time; }
    void read() { hoba::open_file();  bob.setf(ios::skipws); bob >> nomb >> name >> x >> y >> type >> time; }////проверить или через getline стринги ловить
    void clearf() { bob.close(); bob.open("Database.txt", ios::out | ios::trunc); bob.close(); }
    friend bool by_name(const hoba& lh, const hoba& rh);
    friend bool by_type(const hoba& lh, const hoba& rh);
    friend bool by_time(const hoba& lh, const hoba& rh);
    friend bool by_distance(const hoba& lh, const hoba& rh);
    friend bool by_name_name(const hoba& lh, const hoba& rh);
    friend bool by_type_name(const hoba& lh, const hoba& rh);
    friend void check(vector<hoba*> op, int f, int n);
};

int hoba::n = 0;
fstream hoba::bob;
int hoba:: gm=0;
int hoba::count = 3;

bool (* choise_sort)(const hoba& lh, const hoba& rh);

void hoba::open_file()//open file
{
    hoba::bob.open("Database.txt", ios::in | ios::out | ios::app);
    hoba::bob.unsetf(ios::skipws);
}

bool by_name(const hoba& lh, const hoba& rh) { hoba::gm = 1; return lh.name.compare(rh.name) > 0; }//by name
bool by_type(const hoba& lh, const hoba& rh) { hoba::gm = 2; return lh.type.compare(rh.type) > 0; }//by type
bool by_time(const hoba& lh, const hoba& rh) { hoba::gm = 3; return lh.time>rh.time; }//by time
bool by_distance(const hoba& lh,const hoba& rh) { hoba::gm = 4; return sqrt((lh.x*lh.x)+(lh.y*lh.y)) > sqrt((rh.x * rh.x) + (rh.y * rh.y)); }//by distance
bool by_name_name(const hoba& lh, const hoba& rh) { hoba::gm = 5; return by_name(lh, rh) || lh.name.compare(rh.name) == 0 && by_name(lh, rh); }//by name_name
bool by_type_name(const hoba& lh, const hoba& rh)// type and name
{
    hoba::gm = 5;
    return by_type(lh, rh) || lh.type.compare(rh.type) == 0 && by_name(lh, rh);
}

void check(vector<hoba*> op, int f, int n)
{ 
    int co = 0;
    for (int i = f; i < n-1; i++)
    {
        if (op[f]->gn == op[f + 1]->gn) co++;
    }
    if (co >= hoba::count){ for (int t = f; t <= co; t++) op[t]->gn = op[t+1]->gn; }
}

int pres(vector<hoba*> mas, int start, int end, bool(*a)(const hoba& lh, const hoba& rh))
{
    int ind = start;
    hoba prep = *mas[end];

    for (int i = ind; i <= end; i++)
    {
        if (a(*mas[i], *mas[end])) { swap(*mas[i], *mas[ind]); ind++; }
    }
    swap(*mas[ind], *mas[end]);
    return ind;
}
 
void sort(vector<hoba*> mas, int start, int end, bool(*a)(const hoba& lh, const hoba& rh))
{
    if (start >= end)return;
    int perem = pres(mas, start, end, a);
    sort(mas, start, perem - 1, a);
    sort(mas, perem + 1, end, a);
}

int main()
{
    char ch = 'y';
    vector<hoba*> opa;
    hoba* ptr = NULL;

    while (ch =='y')
    {
        int i;
        int n;
        cout << "choose your act" << '\n' <<
            "1. Add object" << '\n' <<
            "2. Group objects" << '\n' <<
            "3. Save info" << '\n' <<
            "4. Read file" << '\n'<<
            "5. Show table"<<'\n'<<
            "6. Exit" << endl;
        cin >> i;
        switch (i)
        {
        case 1: { ptr = new hoba; ptr->add(); opa.push_back(ptr); } break;
        case 2: {cout << "choose type of sort" << '\n'; int p;
            cout <<
                "1. by_name"<<'\n'<<
                "2. by type" <<'\n'<<
                "3. by time" << '\n' <<
                "4. by distance" << '\n'<<
                "5. by type_name" << endl;
            cin >> p;
            switch (p)
            {
            case 1: choise_sort = by_name_name; break;
            case 2: choise_sort = by_type; break;
            case 3: choise_sort = by_time; break;
            case 4: choise_sort = by_distance; break;
            case 5: choise_sort = by_type_name; break;
            default: continue;
            }
            n = opa.size();
            sort(opa, 0, n - 1, choise_sort); 
        }
              break;
        case 3:
        {
        n = opa.size();
        for (int f = 0; f < n; f++)  opa[f]->wri(); } break;
        
        case 4: {n = opa.size(); for (int f = 0; f < n; f++) { ptr = new hoba; opa.push_back(ptr); opa[f]->read(); }} break;

        case 5: { n = opa.size();
            for (int f = 0; f < n; f++)
            {
                opa[f]->getinf(opa, n);
            }
            break;
        }
        case 6: {exit(0); }
        default: continue;
        }   
        cin.ignore(10, '\n');
        continue;
    } 
}
