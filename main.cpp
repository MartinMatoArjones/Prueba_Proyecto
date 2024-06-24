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

std::vector<std::pair<std::string, std::string>> buscarValores(const std::string &input, const std::string &inicio)
{
    if (input.find(inicio) == string::npos)
    {
        return {{"-1","-1"}};
    }
    std::vector<std::pair<std::string, std::string>> resultados;
    std::string fin = ")";
    size_t inicio_len = inicio.length();

    size_t pos = input.find(inicio);
    while (pos != std::string::npos)
    {
        // Encontrar el fin de la cadena de valores
        size_t end_pos = input.find(fin, pos + inicio_len);
        if (end_pos == std::string::npos)
        {
            break; // No se encontró el final de la cadena esperada
        }

        // Extraer la subcadena que contiene los valores
        std::string subcadena = input.substr(pos + inicio_len, end_pos - (pos + inicio_len));
        auto palabras = separarPalabras(subcadena);

        // Asegurarse de que hay suficientes palabras
        if (palabras.size() >= 2)
        {
            resultados.emplace_back(palabras[1], palabras[2]);
        }

        // Avanzar la posición para buscar la siguiente ocurrencia del prefijo
        pos = input.find(inicio, end_pos);
    }

    return resultados;
}

string palabra="(see 0 ((f r t) 50.4 -42) ((f r b) 50.4 42) ((f g r b) 38.1 11 0 0) ((g r) 37.3 0) ((f g r t) 38.1 -11) ((f p r b) 29.1 44) ((f p r c) 20.9 0 0 0) ((f p r t) 29.1 -44 0 0) ((f t r 40) 46.5 -57) ((f t r 50) 52.5 -48) ((f b r 40) 46.5 57) ((f b r 50) 52.5 48) ((f r 0) 42.5 0) ((f r t 10) 43.8 -13) ((f r t 20) 47 -25) ((f r t 30) 51.9 -35) ((f r b 10) 43.8 13) ((f r b 20) 47 25) ((f r b 30) 51.9 35) ((l r) 37.3 90))\00";
typedef vector<pair<string,string>> vp;
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


int main(){
    vector<string> flags{"((f l t)","((f r t)","((f l b)","((f r b)","((f c t)","((f c)","((f c b)","((f p l t)","((f p l c)","((f p l b)","((f p r t)","((f p r c)","((f p r b)","((f g r t)","((f g r c)","((f g r b)","((f g l t)","((f g l c)","((f g l b)"};
    for(auto flag: flags){
        cout<< flag << " " << buscarValores(palabra,flag)[0].first<< " " << buscarValores(palabra,flag)[0].second <<endl;
    }
}
