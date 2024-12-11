// Arvosana 4 toteutus. Lisä ominaisuudet ovat alennus, random huone määrä ja käyttäjä voi valita itse huoneen tai antaa ohjelman arpoa käyttäjälle huoneen

// Tarvitaan peruskirjasto tietvirtojen käsittelemiseen
#include <iostream>
// String -tyyppinen kirjasto nimen tallentamista varten
#include <string>
// Peruskirjaston rinnalle tarvittava kirjasto
#include <iomanip>
// Arvontaan tarvittava kirjasto
#include <ctime>
// Tarvitaan pitämään listaa huoneista ja varauksista
#include <vector>

using namespace std;

// Funktio, joka etsii huoneen numeron nimellä taulukosta
vector<int> etsi_huone_numerot_nimella(string kayttajan_nimi, vector<string> &varauksien_nimet) {    
    vector<int> kayttajan_huoneet;
    for(int i=0;i<varauksien_nimet.size(); i++) {
        if(varauksien_nimet[i] == kayttajan_nimi) {
            kayttajan_huoneet.push_back(i);
        }
    }
    return kayttajan_huoneet;
}
// Tehdään funktio, joka etsii huone varauksen numerolla taulukosta
vector<int> etsi_huone_numerot_varaus_numerolla(int varaus_numero, vector<int> &varaus_numerot) {
    vector<int> kayttajan_huoneet; 
    for(int i=0;i<varaus_numerot.size(); i++) {
        if(varaus_numerot[i] == varaus_numero) {
            kayttajan_huoneet.push_back(i);
        }
    }
    return kayttajan_huoneet;
}

// Funktio, joka tarkistaa onko huone yhden hangen huone vai kahden hengen huono
bool onko_yhden_hengen_huone(int huoneen_numero, int huoneiden_maara)
{
    return huoneen_numero <= huoneiden_maara / 2;
}

// Tehdään hotellihuoneen hinnalle ja alennukselle funktio, joka laskee hotellihuoneen alennuksen ja hinnan, jos käyttäjä sellaisen saa
double hotellihuoneen_hinta(double huoneen_hinta, double huone_alennus, int hotelli_yot)
{
    double hinta = (1.0 - huone_alennus) * huoneen_hinta * hotelli_yot;    
    return hinta;
}
// Tehdään huoneen kokonaishinnan laskeva funktio
double kokonais_hinta(string kayttajan_nimi, vector<string> &varauksien_nimet, double huone_alennus, int hotelli_yot) {
    vector<int> kayttajan_huoneet = etsi_huone_numerot_nimella(kayttajan_nimi, varauksien_nimet);
    
    int hinta_1hh = 100;
    int hinta_2hh = 150;
    double hinta;
    for(int i=0;i<kayttajan_huoneet.size();i++) {
        int huone_hinta = hinta_2hh;
        if(onko_yhden_hengen_huone(kayttajan_huoneet[i], varauksien_nimet.size())) {
            huone_hinta = hinta_1hh;
        }
        hinta+=hotellihuoneen_hinta(huone_hinta, huone_alennus, hotelli_yot);        
    }
    return hinta;
}

// Funktio huoneen varauksen tarkistamiseen
bool huone_varattu(int huoneen_numero, vector<int> &varaus_numerot)
{
    int varaus_numero = varaus_numerot[huoneen_numero];
    return varaus_numero > 0;
}

// Tehdään funktio, joka tarkistaa onko kaikki huoneet varattu
bool kaikki_huoneet_varattu(vector<int> &varaus_numerot)
{
    bool kaikki_varattu = false;
    for (int i = 0; i < varaus_numerot.size(); i++)
    {
        kaikki_varattu = huone_varattu(i, varaus_numerot);
        if (!kaikki_varattu)
        {
            break;
        }
    }
    return kaikki_varattu;
}

// Tehdään funktio, jolla tehdään huonevaraus ja tallentaa se
void varaa_huone(int huone_numero, int varaus_numero, string kayttajan_nimi, vector<int> &varaus_numerot, vector<string> &varauksien_nimet)
{
    varaus_numerot[huone_numero-1] = varaus_numero;
    varauksien_nimet[huone_numero-1] = kayttajan_nimi;
}
// Tehdään valikko, josta voidaan valita eri vaihtoehtoja. Esimerkiksi valikosta voidaan etsiä nimellä, etsiä numerolla ja mennä takaisin

void etsi_varauksia_valikko(vector<int> &varaus_numerot, vector<string> &varauksien_nimet) {
    int huoneiden_maara_hotellissa = varaus_numerot.size();
    cout << "Valitse seuraavista: " << endl;
    int etsi_varauksia_valikko_valinta = 0;
    while(etsi_varauksia_valikko_valinta != 3) {
        cout << "Valikon valinnat:" << endl;
        cout << "1. Etsi nimellä" << endl;
        cout << "2. Etsi varausnumerolla" << endl;
        cout << "3. Takaisin" << endl;
        cout << "Valinta: ";
        cin >> etsi_varauksia_valikko_valinta;
        cout << endl;
        cin.ignore();       

        // Etsitään varaus, jonka henkilö on tehnyt
        if(etsi_varauksia_valikko_valinta == 1) {
            string nimi; 
            cout << "Anna nimi: ";
            getline(cin, nimi);
            cout << endl;
            vector<int> varatut_huoneet = etsi_huone_numerot_nimella(nimi, varauksien_nimet);
            // Jos varauksia ei löydy, ohjelma ilmoittaa "Varauksia ei löytynyt"
            if(varatut_huoneet.size() == 0) {
                cout << "Varauksia ei löytynyt!" << endl;
            } else {
                for(int i=0;i<varatut_huoneet.size();i++) {
                    int huone = varatut_huoneet[i];
                    int huonekoko = 2;
                    if(onko_yhden_hengen_huone(huone, huoneiden_maara_hotellissa)) {
                        huonekoko = 1;
                    }
                    cout << "Huone " << varatut_huoneet[i]+1 << " (" << huonekoko << "hh)" << endl;
                }                
            }            
            // Etsitään varausnumero, joka käyttäjälle on luotu
        } else if(etsi_varauksia_valikko_valinta == 2) {
            int varaus_numero;
            cout << "Anna varausnumero: ";
            cin >> varaus_numero;
            cout << endl;
            vector<int> varatut_huoneet = etsi_huone_numerot_varaus_numerolla(varaus_numero, varaus_numerot);
            // Jos käyttäjän varausnumeroa ei ole, ohjelma ilmoittaa "Varauksia ei löytynyt!"
            if(varatut_huoneet.size() == 0) {
                cout << "Varauksia ei löytynyt!" << endl;
            } else {
            // Tulostetaan huoneen numero ja koko
                for(int i=0; i<varatut_huoneet.size();i++) {
                    int huone = varatut_huoneet[i];
                    int huonekoko = 2;
                    if(onko_yhden_hengen_huone(huone, huoneiden_maara_hotellissa)) {
                        huonekoko = 1;
                    }
                    cout << "Huone " << varatut_huoneet[i]+1 << " (" << huonekoko << "hh)" << endl;
                }
            }
        }
    }
}

void varaus_valikko(int min_varaus_numero, int max_varaus_numero, int huoneiden_maara, vector<int> &varaus_numerot, vector<string> &varauksien_nimet)
{
    string kayttajan_nimi;
    char vastaus;
    int kayttajan_valitsema_huonenumero;
    int huone_tyyppi;
    int kayttajan_yot;

    // Otetaan varaajan nimi ylos varauksen tarkastelua varten
    cout << "Anna nimesi, jotta saamme nimesi ylos varausta varten: ";
    getline(cin, kayttajan_nimi);    

    // Arvotaan kayttajalle varausnumero
    int kayttajan_varausnumero = min_varaus_numero + (rand()) % (max_varaus_numero - min_varaus_numero + 1);
    cout << "Tassa on varausnumerosi: " << kayttajan_varausnumero << endl;

valikko:
    // Ohjelma kysyy käyttäjältä, haluaako tämä itse valita vapaan huoneen vai antaako ohjelman itse arpoa
    cout << "Tasta paaset varaamaan huoneita hotelliimme. " << kayttajan_nimi << ", haluatko valita itse huoneen (k/e)?: ";
    cin >> vastaus;
kayttajanvalinta:
    // Jos vastaukseksi tulee k eli kyllä, ohjelma antaa käyttäjän itse valita huoneen
    if (vastaus == 'k' || vastaus == 'K')
    {
        // Pyydetään käyttäjää syöttämään huonenumero
        cout << "Syota haluamasi huone numero (Huonenumero voi olla vain hotellihuoneen maksimi numero!): ";
        cin >> kayttajan_valitsema_huonenumero;
        // Jos huonenumero on yli huoneiden määrän hotelissa, käyttäjä palaa takaisin huoneennumeron syöttämiseen
        if (kayttajan_valitsema_huonenumero > huoneiden_maara)
        {
            cout << "Virheellinen numero!" << endl;
            goto kayttajanvalinta;
        }
        else if (huone_varattu(kayttajan_valitsema_huonenumero, varaus_numerot))
        {
            cout << "Huone on jo varattu!" << endl;
            goto kayttajanvalinta;
        }
        // Jos käyttäjä valitsi validin huoneen, ohjelma vie käyttäjän takaisin valinta valikkoon ja antaa valita lisää huoneita
        else
        {
            varaa_huone(kayttajan_valitsema_huonenumero, kayttajan_varausnumero, kayttajan_nimi, varaus_numerot, varauksien_nimet);
            cout << "Valitsit huone nro. " << kayttajan_valitsema_huonenumero << ". Haluatko viela valita lisaa huoneita (k/e)?: ";
            cin >> vastaus;
            if (vastaus == 'k' || vastaus == 'K')
            {
                goto kayttajanvalinta;
            }
            if (vastaus == 'e' || vastaus == 'E')
            {
                goto kayttajan_valitsemien_huoneiden_yot;
            }
        }
    }
    if (vastaus == 'e' || vastaus == 'E')
    {
        // Jos vastaukseksi tulee e eli ei, ohjelma vielä varmistaa haluaako käyttäjä varmasti jatkaa ja antaa ohjelman arpoa vapaan huoneen
        cout << "Ohjelma arpoo sinulle siis vapaan huoneen. Haluatko varmasti jatkaa (k/e)?: ";
        cin >> vastaus;
        if (vastaus == 'e' || vastaus == 'E')
        {
            goto valikko;
        }
        // Jos käyttäjä vastaa k eli kyllä, ohjelma arpoo käyttäjälle vapaan huoneen
        else if (vastaus == 'k' || vastaus == 'K')
        {
        huone_arvonta:
            // Alustetaan arvonta
            srand(time(0));

            // Jos kaikki huoneet ovat varattu, ohjelma ei anna käyttäjän varata huonetta
            if (kaikki_huoneet_varattu(varaus_numerot))
            {
                cout << "Hotellissa ei valitettavasti ole yhtakaan vapaata huonetta. Pahoittelut!" << endl;
                return;
            }
            // Kysytään haluaako käyttäjä yhden vai kahden hengen huoneen:
            cout << "Haluatko yhden vai kahden hengen huoneen (1/2)?: ";
            cin >> huone_tyyppi;
            int isoin_huone_numero = huoneiden_maara;
            int pienin_huone_numero = 1;

            // Alustetaan yhden huoneen arvontaa
            if (huone_tyyppi == 1)
            {
                isoin_huone_numero = huoneiden_maara / 2;
            }
            else
            {
                pienin_huone_numero = huoneiden_maara / 2 + 1;
            }
            // Kone arpoo huoneita
            int koneen_arpoma_vapaa_huone = pienin_huone_numero + (rand()) % (isoin_huone_numero - pienin_huone_numero + 1);

            // Kone etsii arvonnan avulla huoneita, jotka voisivat olla vapaana
            while (huone_varattu(koneen_arpoma_vapaa_huone, varaus_numerot))
            {
                koneen_arpoma_vapaa_huone = pienin_huone_numero + (rand()) % (isoin_huone_numero - pienin_huone_numero + 1);
            }
            // Kone löytää vapaan huoneen ja ilmoittaa sen käyttäjälle
            cout << "Huone nro. " << koneen_arpoma_vapaa_huone << " on vapaana. Haluaisitteko varata kyseisen huoneen (k/e)?: ";
            cin >> vastaus;
            // Jos käyttäjä vastaa k eli kyllä, ohjelma tallentaa käyttäjän varauksen. Sen lisäksi kysytään vielä käyttäjälyä, haluaako tämä valita lisää huoneita.
            if (vastaus == 'k' || vastaus == 'K')
            {
                varaa_huone(koneen_arpoma_vapaa_huone, kayttajan_varausnumero, kayttajan_nimi, varaus_numerot, varauksien_nimet);
                cout << "Varuksesi on talennettu onnistuneesti. Haluaisitteko varata viela lisaa huoneita (k/e)?: ";
                cin >> vastaus;
                if (vastaus == 'k' || vastaus == 'K')
                {
                    goto huone_arvonta;
                }
                else
                {
                    goto kayttajan_valitsemien_huoneiden_yot;
                }
            }
            else
            {
                goto huone_arvonta;
            }
        }
    }

kayttajan_valitsemien_huoneiden_yot:
    // Lasketaan loppu summa selvittämällä käyttäjältä, kuinka monta yötä tämä yöpyy hotellissa ja määritetään huoneille hinnat. Määritellään myös funktiolle sopivat muuttuja nimet.
    int huoneen_hinta = 0;
    if (huone_tyyppi == 1)
    {
        huoneen_hinta = 100;
    }
    else
    {
        huoneen_hinta = 150;
    }
    cout << "Nyt kun huoneesi on varattu, kuinka monta yota viivyt?: ";
    cin >> kayttajan_yot;
    if (kayttajan_yot <= 0)
    {
        cout << "Hotelisamme voi yopya vahintaan yhden yon. Kokeile syottaa yoiden maara uudelleen. ";
        goto kayttajan_valitsemien_huoneiden_yot;
    }
    // Tulostetaan öiden loppusumma tähän ja mahdolliset alennukset
    else
    {
        srand(time(NULL));
        double alennus_taulukko[3] = {0.0, 0.1, 0.2};
        int alennus_indeksi = rand() % 3;
        double alennus = alennus_taulukko[alennus_indeksi];        

        double hotelli_oiden_summa = kokonais_hinta(kayttajan_nimi, varauksien_nimet, alennus, kayttajan_yot);
        // double hotelli_oiden_summa = hotellihuoneen_hinta(huoneen_hinta, alennus_taulukko[alennus_indeksi], kayttajan_yot);
        cout << "Huoneiden loppusummaksi jaa " << hotelli_oiden_summa << "€ (alennus: " << alennus * 100 << "%), kun viivytte " << kayttajan_yot << " yota hotellissa" << endl;
    }    
}

int main()
{
    // Määritellään muuttujat ja asetetaan huoneille minimi- ja maksimiarvo, sekä varausnumerolle mini- ja maksimiarvo
    int yhden_henkilon_huone, kahden_henkilon_huone;
    int min_huone_maara = 40;
    int max_huone_maara = 300;
    int min_varaus_numero = 10000;
    int max_varaus_numero = 99999;    
    char vastaus;
    int huone_tyyppi;
    string yhden_hengen_huone;
    int kayttajan_valitsema_huonenumero;
    int kayttajan_yot;
    double hotelli_alennus;

    // Alustetaan arvonta huoneiden määrän arpomista varten
    srand(time(NULL));
    // Tehdään huoneiden määrästä parillinen ja arvotaan huoneiden määrä
    int huoneiden_maara = 1;
    while (huoneiden_maara % 2 != 0)
    {
        huoneiden_maara = min_huone_maara + (rand()) % (max_huone_maara - min_huone_maara + 1);
    }

    // Tehdään taulukot varausnumeroista ja varauksen tehneen nimestä
    // Int varaus_numerot[huoneiden_maara] = {};
    // String varauksien_nimet[huoneiden_maara] = {};
    vector<int> varaus_numerot(huoneiden_maara, 0);
    vector<string> varauksien_nimet(huoneiden_maara, "");    
    
    // Tulostetaan ulos huoneiden lukumäärä
    cout << "Tervetuloa hottelliin! Hotellissa on " << huoneiden_maara << " huonetta. " << endl;
    int paavalikko_valinta = 0;
    // Tehdään valikko huoneen varaamista varten
    while(paavalikko_valinta != 3) {
        cout << "Valikon valinnat:" << endl;
        cout << "1. Etsi varauksia" << endl;
        cout << "2. Varaa huoneita" << endl;
        cout << "3. Poistu" << endl;
        cout << "Valinta: ";
        cin >> paavalikko_valinta;
        cout << endl;
        cin.ignore();
    // Etsitään varaus
        if(paavalikko_valinta == 1) {
            etsi_varauksia_valikko(varaus_numerot, varauksien_nimet);
        // Tehdään huoneenvaraus mahdollisuus valikkoon
        } else if (paavalikko_valinta == 2) {
            varaus_valikko(min_varaus_numero, max_varaus_numero, huoneiden_maara, varaus_numerot, varauksien_nimet);
        }
    }
    
    return 0;
}