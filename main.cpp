

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

template<class X>
X inmultire(X x,X y)
{
    return x*y;
}

class Cast{
protected:
    vector<string> numeComplet, rol, dietaRo, dietaEn;
    vector<string> nume_act_si_fig, machiajRo, machiajEn;
    const string machiaj1[5] = {"Vampir", "Varcolac", "Sirena", "Clarvazator", "Om"};
    const string makeup[5] = {"Vampire", "Werewolf", "Mermaid", "Clairvoyant", "Human"};
    const int costM[5] = {230, 555, 345, 157, 55};
    const string dietRo[3] = {"Omnivori", "Vegetarian", "Flexitarian"};
    const string dietEn[3] = {"Omnivorous", "Vegetarian", "Flexitarian"};
    const int costDiet[3] = {40,33,46};
    
public:
    void writeFigurants(){
        ifstream f;
        ofstream g,h;
        f.open("numeRandom.csv",ios::in);
        g.open("wednesdayCastEn.csv", ios::app);
        h.open("wednesdayCastRo.csv", ios::app);

        string nume[21], prenume[21],figurant[200];
        string num,prenum;
        int n = 132;
        string line;

        for(int i = 0; i < 21; i++){
            getline(f,line);
            stringstream s(line);
            getline(s, num , ',');
            getline(s, prenum, '\n');
            nume[i] = num;
            prenume[i] = prenum;
        }
        for(int j = 0; j < n; j++){
            stringstream ss;
            ss<<prenume[rand()%21]<<" "<<nume[rand()%21];
            figurant[j] = ss.str();
            g<<figurant[j]<<",extra\n";
            h<<figurant[j]<<",figurant\n";
        }
        f.close();
        g.close();
        h.close();
    }

    void getCast(){
    ifstream f;
    f.open("wednesdayCastEn.csv", ios::in);
    string line;
    string nume_complet, rol1;

    while(getline(f,line)){
        stringstream s(line);
        getline(s, nume_complet, ',');
        getline(s, rol1, '\n');
        numeComplet.push_back(nume_complet);
        rol.push_back(rol1);
        
    }

    f.close();
}

    unsigned long int transport(){
        int n = numeComplet.size() - 1;
 
        int numar_autocare = n / 50;
        int persoane_cu_loc = numar_autocare * 50;
        if ((n-persoane_cu_loc) % 50 != 0){
            numar_autocare++;
        
        }
        int costAutocare = inmultire<unsigned long int>(numar_autocare,5680);
        return costAutocare;
    }

    void searchCast(){
      
        int n = numeComplet.size() - 1;
        string act = "actor", fig = "extra";
        for (int i = 0; i < n; i++){
            if(rol[i].find(act) != -1 || rol[i].find(fig) != -1)
            {
                nume_act_si_fig.push_back(numeComplet[i]);
            }
        }
    }
    
    void getMachiaj(){
        int nr;
        int m = nume_act_si_fig.size() - 1;
        
        for(int i = 0; i < m; i++){
            nr = rand()%5;
            machiajRo.push_back(machiaj1[nr]);
            machiajEn.push_back(makeup[nr]);
        }
    }

    unsigned long int costMachiaj(int perioada){
        int i;
        int n = nume_act_si_fig.size() - 1;
        int cost_machiaj = 0;
        for(i = 0; i < n; i++){
            for(int j = 0; j < 5; j++){
                if(machiajRo[i] == machiaj1[j]){
                    cost_machiaj = cost_machiaj + costM[j];
                }
            }
        }
        unsigned long int costMachiajTotal = inmultire<unsigned long int>(perioada,cost_machiaj);
        return costMachiajTotal;
    }

    void getDiet(){
        int n = numeComplet.size() - 1;
        for(int i = 0; i < n; i++){
            int nr;
            nr = rand()%3;
            dietaEn.push_back(dietEn[nr]);
            dietaRo.push_back(dietRo[nr]);
        }
    }

    unsigned long int costMancare(int perioada){
        int n = numeComplet.size() - 1;
        int i;
        int cost_mancare = 0;
        for(i = 0; i < n; i++){
            for(int j = 0; j < 3; j++){
                if(dietaEn[i] == dietEn[j]){
                    cost_mancare = cost_mancare + costDiet[j];
                }
            }
        }
        unsigned long int costMancareTotal = inmultire<unsigned long int>(perioada,cost_mancare);
        return costMancareTotal;     
    }
    
    unsigned long int costCazare(int perioada){
        int nrCastInitial = 0;
        int nrFiguranti = 0;
        int n = numeComplet.size() - 1;
        for(int i = 0; i < n; i++){
            if(rol[i] == "extra"){
                nrFiguranti++;
            }
            else{
            nrCastInitial++;
            }
            }
        int camereCast = nrCastInitial / 2;
        int locuriOcupateCast = camereCast * 2;
        int camereFiguranti = nrFiguranti / 3;
        if((nrCastInitial - locuriOcupateCast) % 2 !=0){
            camereCast++;
        }//Figuranti sunt 132 deci e divizibil cu 3 si nu mai facem operatia de mai sus
        unsigned long int costCast = inmultire<unsigned long int>(camereCast,350);
        unsigned long int costFiguranti = inmultire<unsigned long int>(camereFiguranti,420);
        unsigned long int cost_cazare = inmultire<unsigned long int>(costCast,perioada) + inmultire<unsigned long int>(costFiguranti,perioada);
        return cost_cazare;
    }

    unsigned long int costBauturi(int perioada){
        int n = numeComplet.size() - 1;
        int cantitateApa = n;
        int cantitateCafea = n * 0.5;
        int cantitateSuc = n * 0.8;
        int sticleApa = cantitateApa/2;
        int sticleCafea = cantitateCafea;
        int sticleSuc = cantitateSuc;
        if(cantitateApa % 2 !=0){
            sticleApa++;
        }
        if(n % 2 !=0){
            sticleCafea++;
        }
        if(cantitateSuc % 2 !=0){
            sticleSuc++;
        }
        int cost_bauturi = inmultire<int>(sticleApa,6) + inmultire<int>(sticleCafea,30) + inmultire<int>(sticleSuc,8);
       unsigned long int costBauturaTotal = inmultire<int>(cost_bauturi,perioada);
        return costBauturaTotal;

    }

    unsigned long int costCastel(int perioada){
        unsigned long int cost_Castel = perioada * 10000 - 2000 * perioada / 10;
        return cost_Castel;
    }

    ~Cast(){
        // cout << "Object is being deleted" << endl;
    }
};

class Pret:public Cast{
public:
    Pret(){
        ofstream f,g;
        f.open("Cost.csv",ios::app);
        g.open("Costuri.csv",ios::app);
        g << "Perioada,Transport,Cazare,Machiaj,Mancare si bautura,Inchiriere spatiu,Total\n";
        f << "Time,Transport,Hotel rent,Makeup,Food and drinks,Castel rent,Total\n";
    }

    void get_pret(int perioada,Cast test){
        
        unsigned long int castel = test.costCastel(perioada);
        unsigned long int bauturi = test.costBauturi(perioada);
        unsigned long int cazare = test.costCazare(perioada);
        unsigned long int mancare = test.costMancare(perioada);
        unsigned long int machiaj = test.costMachiaj(perioada);
        unsigned long int transport = test.transport() ;
        unsigned long int total = (castel + bauturi + cazare + mancare + machiaj + transport);
        unsigned long int cursDollar = 5; // I aproximated the dollar to 5 , because if I would made it float it would show numebers like :5.0575e+06$
        ofstream f,g;
        f.open("Cost.csv",ios::app);
        g.open("Costuri.csv",ios::app);
        g <<"\n"<< perioada << " zile," << transport << "RON," << cazare << "RON," << machiaj << "RON," << mancare + bauturi << "RON," << castel << "RON," << total << "RON\n";
        f <<"\n"<< perioada << " days," << transport/cursDollar << "$," << cazare/cursDollar << "$," << machiaj/cursDollar << "$," << (mancare + bauturi)/cursDollar << "$," << castel/cursDollar << "$," << total/cursDollar << "$\n";
        f.close();
        g.close();
    }

    friend class Meniu;

};

class Meniu{
private:
    string Tip_de_mancare;
protected:
    string meniu_supe_omnivori_Ro[7] = {"Ciorba de perisoare", "Supa de pui cu galuste", "Bors de gaina cu taitei", "Ciorba radauteana", "Ciorba de vacuta", "Ciorba ardeleneasca de vitel cu smantana", "Ciorba de fasole cu ciolan afumat"};
    string meniu_fel_principal_omnivori_Ro[7] = {"Piept de rata in sos de rodii", "Piept de pui la gratar cu orez", "Tocanita de vita cu ciuperci", "Coaste de porc la cuptor", "Piept de pui invelit in prosciutto", "Hamburger Black Angus", "Cartofi gratinati cu ciuperci"};
    string meniu_desert_omnivori_Ro[7] = {"Tiramisu", "Pudinca", "Inghetata", "Salata de fructe cu frisca", "Placinta cu visine", "Mousse de ciocolata alba", "Briosa"};
    string meniu_supe_vegetarieni_Ro[7] = {"Ciorba de fasole", "Mancare mazare", "Supa de rosii", "Ciorba de frunze de sfecla", "Supa cu broccoli", "Supa crema de legume", "Gulas de post"};
    string meniu_fel_principal_vegetarieni_Ro[7] = {"Legume la cuptor", "Rondele de vinete la cuptor", "Ratatouille", "Burger vegetarian", "Snitele de soia cu piure", "Dovlecei pane", "Ghiveci de vara"};
    string meniu_desert_vegetarieni_Ro[7] = {"Cheesecake cu lamaie", "Budinca", "Placinta cu mere", "Placinta cu visine", "Tort cu caramel", "Tiramisu", "Briosa"};
    string meniu_supe_flexitarian_Ro[7] = {"Ciorba de peste", "Ciorba de fasole", "Supa de rosii", "Ciorba de frunze de sfecla", "Ciorba radauteana", "Gulas de post", "Supa crema de legume"};
    string meniu_fel_principal_flexitarian_Ro[7] = {"Legume la cuptor", "Rondele de vinete la cuptor", "Ratatouille", "Somon la cuptor", "pastrav la cuptor", "Crap la cuptor cu legume", "Macrou cu rosii si usturoi la cuptor"};
    string meniu_desert_flexitarian_Ro[7] = {"Cheesecake cu lamaie", "Budinca", "Placinta cu mere", "Placinta cu visine", "Tort cu caramel", "Tiramisu", "Briosa"};
    string menu_soup_omnivorous_En[7] = {"Meatballs soup", "Chicken soup with dumplings", "Chicken borscht with noodles", "Radauteana soup", "Beef soup", "Transylvanian veal soup with cream", "Bean soup with bone corn"};
    string menu_main_dish_omnivorous_En[7] ={"Duck breast in pomegranate sauce", "Grilled chicken breast with rice", "Beef stew with mushrooms", "Baked pork ribs", "Prosciutto-wrapped chicken breast", "Black Angus hamburger", "Potatoes au gratin with mushrooms"};
    string menu_desert_omnivorous_En[7] ={"Tiramisu", "Pudding", "Ice cream", "Fruit salad with whipped cream", "Cherry pie", "White chocolate mousse", "Muffin"};
    string menu_soup_vegetarian_En[7] = {"Bean soup", "Pea dish", "Tomato soup", "Beet leaf soup", "Broccoli soup", "Vegetable cream soup", "Lent stew"};
    string menu_main_dish_vegetarian_En[7] = {"Baked vegetables", "Baked aubergine slices", "Ratatouille", "Vegetarian burger", "Soy schnitzel with puree", "Bread zucchini", "Summer pots"};
    string menu_desert_vegetarian_En[7] = {"Cheesecake with lemon", "Pudding", "Apple pie", "Cherry pie", "Caramel cake", "Tiramisu", "Muffin"};
    string menu_soup_flexitarian_En[7] = {"Fish soup", "Bean soup", "Tomato soup", "Beet leaf soup", "Radauteana soup", "Post stew", "Vegetable cream soup"};
    string menu_main_dish_flexitarian_En[7] = {"Baked vegetables", "Baked eggplant slices", "Ratatouille", "Baked salmon", "Baked trout", "Baked carp with vegetables", "Baked mackerel with tomatoes and garlic"};
    string menu_desert_flexitarian_En[7] = {"Cheesecake with lemon", "Pudding", "Apple pie", "Cherry pie", "Caramel cake", "Tiramisu", "Muffin"};
   
public:
    Meniu(){
        ofstream f,g;
        f.open("Menu.csv",ios::app);
        g.open("Meniu.csv",ios::app);
        int k = rand()%7;
        f << "Menu omnivorous\n"  << menu_soup_omnivorous_En[k] << "," << menu_main_dish_omnivorous_En[k] << "," << menu_desert_omnivorous_En[k] << "\n" ;
        g << "Meniu omnivori\n" << meniu_supe_omnivori_Ro[k] << "," << meniu_fel_principal_omnivori_Ro[k] << "," << meniu_desert_omnivori_Ro << "\n" ;
        k = rand()%7;
        f << menu_soup_omnivorous_En[k] << "," << menu_main_dish_omnivorous_En[k] << "," << menu_desert_omnivorous_En[k] << "\n" ;
        g << meniu_supe_omnivori_Ro[k] << "," << meniu_fel_principal_omnivori_Ro[k] << "," << meniu_desert_omnivori_Ro << "\n" ;
        k = rand()%7;
        f  << menu_soup_omnivorous_En[k] << "," << menu_main_dish_omnivorous_En[k] << "," << menu_desert_omnivorous_En[k] << "\n";
        g << meniu_supe_omnivori_Ro[k] << "," << meniu_fel_principal_omnivori_Ro[k] << "," << meniu_desert_omnivori_Ro << "\n" ;
        k = rand()%7;
        f << "\nMenu vegetarian\n" << menu_soup_vegetarian_En[k] << "," << menu_main_dish_vegetarian_En[k] << "," << menu_desert_vegetarian_En[k] << "\n";
        g << "\nMeniu vegetarieni\n" << meniu_supe_vegetarieni_Ro[k] << "," << meniu_fel_principal_vegetarieni_Ro[k] << "," << meniu_desert_vegetarieni_Ro[k] << "\n";
        k = rand()%7;
        f << menu_soup_vegetarian_En[k] << "," << menu_main_dish_vegetarian_En[k] << "," << menu_desert_vegetarian_En[k] << "\n";
        g << meniu_supe_vegetarieni_Ro[k] << "," << meniu_fel_principal_vegetarieni_Ro[k] << "," << meniu_desert_vegetarieni_Ro[k] << "\n";
        k = rand()%7;
        f << menu_soup_vegetarian_En[k] << "," << menu_main_dish_vegetarian_En[k] << "," << menu_desert_vegetarian_En[k] << "\n";
        g << meniu_supe_vegetarieni_Ro[k] << "," << meniu_fel_principal_vegetarieni_Ro[k] << "," << meniu_desert_vegetarieni_Ro[k] << "\n";
        k = rand()%7;
        f << "\nMenu flexitarian\n"  << menu_soup_flexitarian_En[k] << "," << menu_main_dish_flexitarian_En[k] << "," << menu_desert_flexitarian_En[k] << "\n";
        g << "\nMeniu flexitarieni\n" << meniu_supe_flexitarian_Ro[k] << "," << meniu_fel_principal_flexitarian_Ro[k] << "," << meniu_desert_flexitarian_Ro[k] << "\n";
        k = rand()%7;
        f << menu_soup_flexitarian_En[k] << "," << menu_main_dish_flexitarian_En[k] << "," << menu_desert_flexitarian_En[k] << "\n";
        g << meniu_supe_flexitarian_Ro[k] << "," << meniu_fel_principal_flexitarian_Ro[k] << "," << meniu_desert_flexitarian_Ro[k] << "\n";
        k = rand()%7;
        f << menu_soup_flexitarian_En[k] << "," << menu_main_dish_flexitarian_En[k] << "," << menu_desert_flexitarian_En[k] ;
        g << meniu_supe_flexitarian_Ro[k] << "," << meniu_fel_principal_flexitarian_Ro[k] << "," << meniu_desert_flexitarian_Ro[k] << "\n";
        

    };
};

int main(){
    Cast cast_obj;
    Pret pret_obj;
    Meniu meniu_obj;
    cast_obj.writeFigurants();
    cast_obj.getCast();
    cast_obj.searchCast();
    cast_obj.getDiet();
    cast_obj.getMachiaj();
    cout<<"=================COD NAME : MONSTERS AND LIONS================\n";
    cout<<"=============================================================\n";
    cout<<"==================== WELCOME TIM BURTON =====================\n";
    cout<<"=============================================================\n";
    cout<<"========= Don't worry everything is set! ====================\n";
    cout<<"================== ACTION,CAMERA,GO! =======================\n";
    cout<<"=============================================================\n";
    cout<<"=============================================================\n";
    pret_obj.get_pret(30,cast_obj);
    pret_obj.get_pret(45,cast_obj);
    pret_obj.get_pret(60,cast_obj);
    pret_obj.get_pret(100,cast_obj);



    

}
