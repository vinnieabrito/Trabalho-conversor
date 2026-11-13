#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// aceita so as bases 2, 3, 8, 10 e 16
bool baseValida(int base) {
    return base == 2 || base == 3 || base == 8 ||
        base == 10 || base == 16;
}

// confere se todos os digitos pertencem a base
bool numeroValido(string numero, int base) {
    int inicio = (numero[0] == '-') ? 1 : 0;
    if (numero.size() == inicio) return false;

    for (int i = inicio; i < numero.size(); i++) {
        char c = toupper(numero[i]);
        int digito;

        if (c >= '0' && c <= '9')
            digito = c - '0';
        else if (c >= 'A' && c <= 'F')
            digito = c - 'A' + 10;
        else
            return false;

        if (digito >= base) return false;
    }
    return true;
}

// converte qualquer base para decimal
long long paradecimal(string numero, int base) {
    long long decimal = 0;
    bool negativo = numero[0] == '-';
    int inicio = negativo ? 1 : 0;

    for (int i = inicio; i < numero.size(); i++) {
        char c = toupper(numero[i]);
        int digito;

        if (c >= '0' && c <= '9')
            digito = c - '0';
        else
            digito = c - 'A' + 10;

        decimal = decimal * base + digito;
    }

    return negativo ? -decimal : decimal;
}

// converte decimal para qualquer base
string dedecimal(long long numero, int base) {
    if (numero == 0) return "0";

    string resultado = "";
    string caracteres = "0123456789ABCDEF";
    bool negativo = numero < 0;

    if (negativo) numero = -numero;

    while (numero > 0) {
        resultado += caracteres[numero % base];
        numero /= base;
    }

    if (negativo) resultado += '-';

    reverse(resultado.begin(), resultado.end());
    return resultado;
}

// converte de uma base para outra
string conversor(string numero, int origem, int destino) {
    return dedecimal(paradecimal(numero, origem), destino);
}

int main() {
    string numero;
    int base1, base2;

    // print e leitura
    cout << "Bases permitidas: 2, 3, 8, 10 e 16\n";

    cout << "Digite o numero: ";
    cin >> numero;

    cout << "Digite a base de origem: ";
    cin >> base1;

    // verificacao se as bases sao validas (e se condizem com o numero
    if (!baseValida(base1)) {
        cout << "Base de origem invalida!";
        return 1;
    }

    if (!numeroValido(numero, base1)) {
        cout << "Numero invalido para a base " << base1 << "!";
        return 1;
    }

    cout << "Digite a base do resultado: ";
    cin >> base2;
    if (!baseValida(base2)) {
        cout << "Base do resultado invalida!";
        return 1;
    }

    cout << conversor(numero, base1, base2);

    return 0;
}