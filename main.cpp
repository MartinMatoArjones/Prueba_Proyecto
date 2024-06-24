#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

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


typedef pair<string,string> vp;
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
};

void rellenaContenedor(visioncampo &container, const string &p) {
    vector<pair<string, vp*>> flagMap = {
        {"((f l t) ", &container.cornersupizq},
        {"((f r t) ", &container.cornersupder},
        {"((f l b) ", &container.cornerinfizq},
        {"((f r b) ", &container.cornerinfder},
        {"((f c t) ", &container.centrosup},
        {"((f c) ", &container.centro},
        {"((f c b) ", &container.centroinf},
        {"((f p l t) ", &container.areasupizq},
        {"((f p l c) ", &container.areacentroizq},
        {"((f p l b) ", &container.areainfizq},
        {"((f p r t) ", &container.areasupder},
        {"((f p r c) ", &container.areacentroder},
        {"((f p r b) ", &container.areainfder},
        {"((f g r t) ", &container.portsupder},
        {"((f g r c) ", &container.portcentroder},
        {"((f g r b) ", &container.portinfder},
        {"((f g l t) ", &container.portsupizq},
        {"((f g l c) ", &container.portcentroizq},
        {"((f g l b) ", &container.portinfizq}
    };

    for (const auto &flagPair : flagMap) {
        auto resultados = buscarValores(p, flagPair.first);
        if (resultados.first == "-1") {
            *(flagPair.second) = {"-1", "-1"};
        } else {
            *(flagPair.second) = resultados;
        }
    }
}

int main(){
    string palabra="(see 0 ((f r t) 50.4 -42) ((f r b) 50.4 42) ((f g r b) 38.1 11 0 0) ((g r) 37.3 0) ((f g r t) 38.1 -11) ((f p r b) 29.1 44) ((f p r c) 20.9 0 0 0) ((f p r t) 29.1 -44 0 0) ((f t r 40) 46.5 -57) ((f t r 50) 52.5 -48) ((f b r 40) 46.5 57) ((f b r 50) 52.5 48) ((f r 0) 42.5 0) ((f r t 10) 43.8 -13) ((f r t 20) 47 -25) ((f r t 30) 51.9 -35) ((f r b 10) 43.8 13) ((f r b 20) 47 25) ((f r b 30) 51.9 35) ((l r) 37.3 90))\00";

    struct visioncampo micontainer;
    rellenaContenedor(micontainer,palabra);

    /*
    vector<pair<string, vp>> containerFields = {
        {"cornersupizq", micontainer.cornersupizq},
        {"cornersupder", micontainer.cornersupder},
        {"cornerinfizq", micontainer.cornerinfizq},
        {"cornerinfder", micontainer.cornerinfder},
        {"centrosup", micontainer.centrosup},
        {"centro", micontainer.centro},
        {"centroinf", micontainer.centroinf},
        {"areasupizq", micontainer.areasupizq},
        {"areacentroizq", micontainer.areacentroizq},
        {"areainfizq", micontainer.areainfizq},
        {"areasupder", micontainer.areasupder},
        {"areacentroder", micontainer.areacentroder},
        {"areainfder", micontainer.areainfder},
        {"portsupizq", micontainer.portsupizq},
        {"portcentroizq", micontainer.portcentroizq},
        {"portinfizq", micontainer.portinfizq},
        {"portsupder", micontainer.portsupder},
        {"portcentroder", micontainer.portcentroder},
        {"portinfder", micontainer.portinfder}
    };
    for (const auto &field : containerFields) {
        cout << field.first << ": " << field.second.first << ", " << field.second.second << endl;
    }
    */

   vector<pair<string, vp>> coordenadasABS = {
        {"cornersupizq", {"",""}},
        {"cornersupder", },
        {"cornerinfizq", },
        {"cornerinfder", },
        {"centrosup", },
        {"centro", },
        {"centroinf", },
        {"areasupizq", },
        {"areacentroizq", },
        {"areainfizq", },
        {"areasupder", },
        {"areacentroder", },
        {"areainfder", },
        {"areasupder", },
        {"portcentroder",},
        {"portinfder", },
        {"portsupizq", },
        {"portcentroizq", },
        {"portinfizq", }
    };

    return 0;
}
