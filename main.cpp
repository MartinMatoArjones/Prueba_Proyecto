#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#define pi 3.14159

using namespace std;
typedef pair<string,string> vp;

pair<float,float> calcularCoordenadas(vector<pair<string,vp>> coordenadas, vector<pair<string,vp>>coordenadasABS, bool horizontales);

//--------------------------------------------------------------------------------VECTOR DE COORDENADAS ABSOLUTAS DEL CAMPO
vector<pair<string,vp>>coordenadasABS = {
        // {"cornersupizq", {"-52.5","-34"}},
        // {"cornersupder", {"52.5","-34"}},
        // {"cornerinfizq", {"-52.5","34"}},
        // {"cornerinfder", {"52.5","34"}},
        {"centrosup", {"0","-34"}},
        {"centro", {"0","0"}},
        {"centroinf", {"0","34"}},
        // {"areasupizq", {"-36","-20"}},
        // {"areacentroizq", {"-36","0"}},
        // {"areainfizq", {"-36","20"}},
        // {"areasupder", {"36","-20"}},
        // {"areacentroder", {"36","0"}},
        // {"areainfder", {"36","20"}},
        {"portsupder", {"52.5","-7"}},
        {"portcentroder",{"52.5","0"}},
        {"portinfder", {"52.5","7"}},
        {"portsupizq", {"-52.5","-7"}},
        {"portcentroizq", {"-52.5","0"}},
        {"portinfizq", {"-52.5","7"}},
        // //banda superior
        // {"((f t l 50) ",{"-50","-39"}},
        // {"((f t l 40) ",{"-40","-39"}},
        // {"((f t l 30) ",{"-30","-39"}},
        // {"((f t l 20) ",{"-20","-39"}},
        // {"((f t l 10) ",{"-10","-39"}},
        // {"((f t) ",{"0","-39"}},
        // {"((f t r 50) ",{"50","-39"}},
        // {"((f t r 40) ",{"40","-39"}},
        // {"((f t r 30) ",{"30","-39"}},
        // {"((f t r 20) ",{"20","-39"}},
        // {"((f t r 10) ",{"10","-39"}},
        // //banda inferior
        // {"((f b l 50) ",{"-50","39"}},
        // {"((f b l 40) ",{"-40","39"}},
        // {"((f b l 30) ",{"-30","39"}},
        // {"((f b l 20) ",{"-20","39"}},
        // {"((f b l 10) ",{"-10","39"}},
        // {"((f b) ",{"0","39"}},
        // {"((f b r 50) ",{"50","39"}},
        // {"((f b r 40) ",{"40","39"}},
        // {"((f b r 30) ",{"30","39"}},
        // {"((f b r 20) ",{"20","39"}},
        // {"((f b r 10) ",{"10","39"}},
        // //banda derecha
        // {"((f r b 30) ",{"57.5","30"}},
        // {"((f r b 20) ",{"57.5","20"}},
        // {"((f r b 10) ",{"57.5","10"}},
        {"((f r 0) ",{"57.5","0"}},
        // {"((f r t 30) ",{"57.5","-30"}},
        // {"((f r t 20) ",{"57.5","-20"}},
        {"((f r t 10) ",{"57.5","-10"}},
        // //banda izquierda
        // {"((f l b 30) ",{"-57.5","30"}},
        // {"((f l b 20) ",{"-57.5","20"}},
        // {"((f l b 10) ",{"-57.5","10"}},
        // {"((f l 0) ",{"-57.5","0"}},
        // {"((f l t 30) ",{"-57.5","-30"}},
        // {"((f l t 20) ",{"-57.5","-20"}},
        // {"((f l t 10) ",{"-57.5","-10"}},

    };

//-------------------------------------------------------------------------------------------------------FUNCIONES
vector<string> separarPalabras(const string &palabra)
{
    int ncaracteres = palabra.size();
    vector<string> resultado;
    string aux;

    for (int i = 0; i < ncaracteres; i++)
    {
        ;
        if (palabra[i] == '(' || palabra[i] == ')')
            continue;
        if (palabra[i] == ' ')
        {
            resultado.push_back(aux);
            aux = "";
            continue;
        }
        aux += palabra[i];
    }
    resultado.push_back(aux); // última palabra
    return resultado;
}

pair<string, string> buscarValores(const std::string &input, const std::string &inicio) {
    if (input.find(inicio) == string::npos) {
        return {"-1", "-1"};
    }

    std::string fin = ")";
    size_t inicio_len = inicio.length();

    size_t pos = input.find(inicio);
    while (pos != std::string::npos) {
        // Encontrar el fin de la cadena de valores
        size_t end_pos = input.find(fin, pos + inicio_len);
        if (end_pos == std::string::npos) {
            break; // No se encontró el final de la cadena esperada
        }

        // Extraer la subcadena que contiene los valores
        std::string subcadena = input.substr(pos + inicio_len, end_pos - (pos + inicio_len));
        auto palabras = separarPalabras(subcadena);

        // Asegurarse de que hay suficientes palabras
        if (palabras.size() >= 2) {
            return {palabras[0], palabras[1]};
        }

        // Avanzar la posición para buscar la siguiente ocurrencia del prefijo
        pos = input.find(inicio, end_pos);
    }

    return {"-1", "-1"};
}

//------------------------------------------------------------------------------------------CONTENEDOR DE COORDENADAS INSTANTANEAS DEL JUGADOR (SOLO LAS QUE VE)

struct visioncampo{
    vp cornersupizq; //flt
    vp cornersupder; //frt
    vp cornerinfizq; //flb
    vp cornerinfder; //frb
    vp centrosup; //fct
    vp centro; //fc
    vp centroinf; //fcb
    vp areasupizq; //fplt
    vp areacentroizq; //fplc
    vp areainfizq; //fplb
    vp areasupder; //fprt
    vp areacentroder; //fprc
    vp areainfder; //fprb
    vp portsupizq; //fglt
    vp portcentroizq; //fglc
    vp portinfizq; //fglb
    vp portsupder; //fgrt
    vp portcentroder; //fgrc
    vp portinfder; //fgrb
                                //banda exterior superior derecha e izquierda 
    vp bandasup50ml; //ftl50
    vp bandasup40ml; //ftl40
    vp bandasup30ml; //ftl30
    vp bandasup20ml; //ftl20
    vp bandasup10ml; //ftl10
    vp bandasup50mr; //ftr50
    vp bandasup40mr; //ftr40
    vp bandasup30mr; //ftr30
    vp bandasup20mr; //ftr20
    vp bandasup10mr; //ftr10
    vp bandasup0m; //ft
                                //banda exterior inferior derecha e izquierda
    vp bandainf50ml; //fbl50
    vp bandainf40ml; //ftl40
    vp bandainf30ml; //ftl30
    vp bandainf20ml; //ftl20
    vp bandainf10ml; //ftl10
    vp bandainf50mr; //ftr50
    vp bandainf40mr; //ftr40
    vp bandainf30mr; //ftr30
    vp bandainf20mr; //ftr20
    vp bandainf10mr; //ftr10
    vp bandainf0m; //fb
                                //banda exterior derecha 
    vp bandader30mt; //frt30
    vp bandader20mt; //frt20
    vp bandader10mt; //frt10
    vp bandader30mb; //frb30
    vp bandader20mb; //truct visioncampo const &container,frb20
    vp bandader10mb; //frb10
    vp bandader0m; //fr0
                                //banda exterior izquierda
    vp bandaizq30mt; //flt30
    vp bandaizq20mt; //flt20
    vp bandaizq10mt; //flt10
    vp bandaizq30mb; //flb30
    vp bandaizq20mb; //flb20
    vp bandaizq10mb; //flb10
    vp bandaizq0m; //fl0



};

//------------------------------------------------------------------------------------------FUNCION QUE RELLENA EL CONTENEDOR EN CADA ITERACIÓN 
pair<float,float>  rellenaContenedor(visioncampo &container, const string &p) {
    vector<pair<string, vp*>> flagMap = {
        //{"((f l t) ", &container.cornersupizq},
        //{"((f r t) ", &container.cornersupder},
        //{"((f l b) ", &container.cornerinfizq},
        //{"((f r b) ", &container.cornerinfder},
        {"((f c t) ", &container.centrosup},
        {"((f c) ", &container.centro},
        {"((f c b) ", &container.centroinf},
        //{"((f p l t) ", &container.areasupizq},
        //{"((f p l c) ", &container.areacentroizq},
        //{"((f p l b) ", &container.areainfizq},
        //{"((f p r t) ", &container.areasupder},
        //{"((f p r c) ", &container.areacentroder},
        //{"((f p r b) ", &container.areainfder},
        {"((f g r t) ", &container.portsupder},
        {"((f g r c) ", &container.portcentroder},
        {"((f g r b) ", &container.portinfder},
        {"((f g l t) ", &container.portsupizq},
        {"((f g l c) ", &container.portcentroizq},
        {"((f g l b) ", &container.portinfizq},

        // Banda exterior superior derecha e izquierda 
        {"((f t l 50) ", &container.bandasup50ml},
        {"((f t l 40) ", &container.bandasup40ml},
        {"((f t l 30) ", &container.bandasup30ml},
        {"((f t l 20) ", &container.bandasup20ml},
        {"((f t l 10) ", &container.bandasup10ml},
        {"((f t r 50) ", &container.bandasup50mr},
        {"((f t r 40) ", &container.bandasup40mr},
        {"((f t r 30) ", &container.bandasup30mr},
        {"((f t r 20) ", &container.bandasup20mr},
        {"((f t r 10) ", &container.bandasup10mr},
        {"((f t) ", &container.bandasup0m},

        // Banda exterior inferior derecha e izquierda
        {"((f b l 50) ", &container.bandainf50ml},
        {"((f b l 40) ", &container.bandainf40ml},
        {"((f b l 30) ", &container.bandainf30ml},
        {"((f b l 20) ", &container.bandainf20ml},
        {"((f b l 10) ", &container.bandainf10ml},
        {"((f b r 50) ", &container.bandainf50mr},
        {"((f b r 40) ", &container.bandainf40mr},
        {"((f b r 30) ", &container.bandainf30mr},
        {"((f b r 20) ", &container.bandainf20mr},
        {"((f b r 10) ", &container.bandainf10mr},
        {"((f b) ", &container.bandainf0m},

        // Banda exterior derecha 
        {"((f r t 30) ", &container.bandader30mt},
        {"((f r t 20) ", &container.bandader20mt},
        {"((f r t 10) ", &container.bandader20mb},
        {"((f r b 30) ", &container.bandader30mb},
        {"((f r b 20) ", &container.bandader20mb},
        {"((f r b 10) ", &container.bandader10mb},
        {"((f r 0) ", &container.bandader0m},

        // Banda exterior izquierda
        {"((f l t 30) ", &container.bandaizq30mt},
        {"((f l t 20) ", &container.bandaizq20mt},
        {"((f l t 10) ", &container.bandaizq10mt},
        {"((f l b 30) ", &container.bandaizq30mb},
        {"((f l b 20) ", &container.bandaizq20mb},
        {"((f l b 10) ", &container.bandaizq10mb},
        {"((f l 0) ", &container.bandaizq0m},
    };

    //string auxflag="((f l t) ";
    vector<pair<string,vp>> bandaextizq;
    vector<pair<string,vp>> bandaextder;
    vector<pair<string,vp>> bandaextinf;
    vector<pair<string,vp>> bandaextsup;
    pair<float,float> vacio;
    int aux;
    for (const auto &flagPair : flagMap) {
        auto resultados = buscarValores(p, flagPair.first);
        if (resultados.first == "-1") {
            *(flagPair.second) = {"-1", "-1"};
        } else {
            *(flagPair.second) = resultados;
            
            if(flagPair.first.compare(0,8,"((f l t ")==0||flagPair.first.compare(0,8,"((f l 0)")==0||flagPair.first.compare(0,8,"((f l b ")==0){ //no puedo comparar la ultima parte (los numeros)
                bandaextizq.push_back({flagPair.first,*flagPair.second});
            }else if(flagPair.first.compare(0,8,"((f r t ")==0||flagPair.first.compare(0,8,"((f r 0)")==0||flagPair.first.compare(0,8,"((f r b ")==0){
                bandaextder.push_back({flagPair.first,*flagPair.second});
            }
            else if(flagPair.first.compare(0,8,"((f b l ")==0||flagPair.first.compare(0,6,"((f b)")==0||flagPair.first.compare(0,8,"((f b r ")==0){
                bandaextinf.push_back({flagPair.first,*flagPair.second});
            }
            else if(flagPair.first.compare(0,8,"((f t l ")==0||flagPair.first.compare(0,6,"((f t)")==0||flagPair.first.compare(0,8,"((f t r ")==0){
                bandaextsup.push_back({flagPair.first,*flagPair.second});
            }
           //if(v.size()==2)
        }
    }
    if(bandaextizq.size()>=2){
        auto xy =  calcularCoordenadas(bandaextizq,coordenadasABS,false);
        return xy;
    }
    if(bandaextder.size()>=2){
        auto xy =  calcularCoordenadas(bandaextder,coordenadasABS,false);
        return xy;
    }
    if(bandaextsup.size()>=2){
        auto xy =  calcularCoordenadas(bandaextsup,coordenadasABS,true);
        return xy;
    }
    if(bandaextinf.size()>=2){
        auto xy =  calcularCoordenadas(bandaextinf,coordenadasABS,true);
        return xy;
    }
    return vacio;
}

pair<float,float> calcularCoordenadas(vector<pair<string,vp>> coordenadas, vector<pair<string,vp>>coordenadasABS, bool horizontales){
    float distancia1=99999;
    float distancia2=99999;
    float direccion1;
    float direccion2;
    float x1abs;
    float y1abs;
    float x2abs;
    float y2abs;
    float xabs;
    float yabs;
    string flag1;
    string flag2;
    for(auto t: coordenadas){  
          if(stof(t.second.first)<distancia1){
            distancia2= distancia1;
            direccion2=direccion1;
            flag2=flag1;
            distancia1=stof(t.second.first);
            direccion1=stof(t.second.second);
            flag1=t.first;
          }  
          else if (stof(t.second.first)<distancia2){
            distancia2=stof(t.second.first);
            direccion2=stof(t.second.second);
            flag2=t.first;
          }
    }
    for(auto p: coordenadasABS){  
        if(p.first==flag1){
            x1abs=stof(p.second.first);
            y1abs=stof(p.second.second);
            
        }
        else if(p.first==flag2){
            x2abs=stof(p.second.first);
            y2abs=stof(p.second.second);
            
        }
     }
     float diferencia=(x1abs-x2abs)+(y1abs-y2abs);
     float aux=(distancia1 * sin(fabs((direccion1 - direccion2)*pi/180))) / diferencia;
     float c = asin((distancia1 * sin(fabs((direccion1 - direccion2)*pi/180))) / diferencia);
     if (horizontales){
        xabs=x2abs-distancia2*cos(c);
        yabs=c*cos((pi/2)-c);
     } else{
        xabs=c*sin(c);
        yabs=y2abs-distancia2*cos(c);
     }
     return {xabs,yabs};
     
}




int main(){
    string palabra="(see 0 ((f r t) 50.4 -42) ((f r b) 50.4 42) ((f g r b) 38.1 11 0 0) ((g r) 37.3 0) ((f g r t) 38.1 -11) ((f p r b) 29.1 44) ((f p r c) 20.9 0 0 0) ((f p r t) 29.1 -44 0 0) ((f t r 40) 46.5 -57) ((f t r 50) 52.5 -48) ((f b r 40) 46.5 57) ((f b r 50) 52.5 48) ((f r 0) 42.5 0) ((f r t 10) 43.8 -13) ((f r t 20) 47 -25) ((f r t 30) 51.9 -35) ((f r b 10) 43.8 13) ((f r b 20) 47 25) ((f r b 30) 51.9 35) ((l r) 37.3 90))\00";

    struct visioncampo micontainer;
    
    auto coordenadas = rellenaContenedor(micontainer, palabra);
    
    
    return 0;
}
