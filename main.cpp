#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <math.h>

using namespace std;
typedef pair<string,string> vp;
//--------------------------------------------------------------------------------VECTOR DE COORDENADAS ABSOLUTAS DEL CAMPO
/*pair<string, vp> coordenadasABS = {
        {"cornersupizq", {"-52.5","-34"}},
        {"cornersupder", {"52.5","-34"}},
        {"cornerinfizq", {"-52.5","34"}},
        {"cornerinfder", {"52.5","34"}},
        {"centrosup", {"0","-34"}},
        {"centro", {"0","0"}},
        {"centroinf", {"0","34"}},
        {"areasupizq", {"-36","-20"}},
        {"areacentroizq", {"-36","0"}},
        {"areainfizq", {"-36","20"}},
        {"areasupder", {"36","-20"}},
        {"areacentroder", {"36","0"}},
        {"areainfder", {"36","20"}},
        {"portsupder", {"52.5","-7"}},
        {"portcentroder",{"52.5","0"}},
        {"portinfder", {"52.5","7"}},
        {"portsupizq", {"-52.5","-7"}},
        {"portcentroizq", {"-52.5","0"}},
        {"portinfizq", {"-52.5","7"}}
    };
*/
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
void rellenaContenedor(visioncampo &container, const string &p, vector<string> &v) {
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
        {"((f r t 10f ", &container.bandader20mb},
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
    for (const auto &flagPair : flagMap) {
        auto resultados = buscarValores(p, flagPair.first);
        if (resultados.first == "-1") {
            *(flagPair.second) = {"-1", "-1"};
        } else {
            *(flagPair.second) = resultados;
            
            if(auxflag == flagPair.first){ //no puedo comparar la ultima parte (los numeros)

            }else{
                auxflag = flagPair.first;
            }
           //if(v.size()==2)
        }
    }
}

pair<vp,string> calcularCoordenadas(struct visioncampo const &container, string palabra){
    struct visioncampo micontainer = container;
    rellenaContenedor(micontainer, palabra);
    vp aux{"-1","-1"};

    int flag;

    for(auto t: micontainer){
        
    }



}




int main(){
    string palabra="(see 0 ((f r t) 50.4 -42) ((f r b) 50.4 42) ((f g r b) 38.1 11 0 0) ((g r) 37.3 0) ((f g r t) 38.1 -11) ((f p r b) 29.1 44) ((f p r c) 20.9 0 0 0) ((f p r t) 29.1 -44 0 0) ((f t r 40) 46.5 -57) ((f t r 50) 52.5 -48) ((f b r 40) 46.5 57) ((f b r 50) 52.5 48) ((f r 0) 42.5 0) ((f r t 10) 43.8 -13) ((f r t 20) 47 -25) ((f r t 30) 51.9 -35) ((f r b 10) 43.8 13) ((f r b 20) 47 25) ((f r b 30) 51.9 35) ((l r) 37.3 90))\00";

    struct visioncampo micontainer;
    rellenaContenedor(micontainer, palabra);

    
    return 0;
}
