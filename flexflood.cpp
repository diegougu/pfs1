#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Punto {
    double x, y, z;
};

class FlexFlood {
public:
    int nx, ny, n;
    vector<double> bx, by;
    vector< vector<Punto> > celdas;

    FlexFlood() {
        nx = 4;
        ny = 4;
        n = 0;
    }

    int columnaX(double v) {
        int c = 0;
        for (int i = 0; i < bx.size(); i++) {
            if (v >= bx[i]) c++;
        }
        return c;
    }

    int columnaY(double v) {
        int c = 0;
        for (int i = 0; i < by.size(); i++) {
            if (v >= by[i]) c++;
        }
        return c;
    }

    void construir(vector<Punto> datos) {
        n = datos.size();
        vector<double> xs, ys;
        for (int i = 0; i < datos.size(); i++) {
            xs.push_back(datos[i].x);
            ys.push_back(datos[i].y);
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        bx.clear();
        by.clear();
        for (int c = 1; c < nx; c++) bx.push_back(xs[xs.size() * c / nx]);
        for (int c = 1; c < ny; c++) by.push_back(ys[ys.size() * c / ny]);
        celdas.clear();
        celdas.resize(nx * ny);
        for (int i = 0; i < datos.size(); i++) {
            ponerEnCelda(datos[i]);
        }
    }

    void ponerEnCelda(Punto p) {
        int i = columnaX(p.x);
        int j = columnaY(p.y);
        vector<Punto>& c = celdas[i * ny + j];
        int pos = 0;
        while (pos < c.size() && c[pos].z < p.z) pos++;
        c.insert(c.begin() + pos, p);
    }

    void insertar(Punto p) {
        ponerEnCelda(p);
        n++;
    }

    int contarColumnaX(int i) {
        int s = 0;
        for (int j = 0; j < ny; j++) s += celdas[i * ny + j].size();
        return s;
    }

    int contarColumnaY(int j) {
        int s = 0;
        for (int i = 0; i < nx; i++) s += celdas[i * ny + j].size();
        return s;
    }

    void imprimir() {
        cout << "n = " << n << endl;
        cout << "columnas en x (" << nx << "): ";
        for (int i = 0; i < nx; i++) cout << contarColumnaX(i) << " ";
        cout << endl;
        cout << "columnas en y (" << ny << "): ";
        for (int j = 0; j < ny; j++) cout << contarColumnaY(j) << " ";
        cout << endl;
    }
};

double azar() {
    return rand() % 10000 / 10000.0;
}

int main() {
    FlexFlood ff;

    vector<Punto> datos;
    for (int i = 0; i < 10000; i++) {
        Punto p;
        p.x = azar();
        p.y = azar();
        p.z = azar();
        datos.push_back(p);
    }
    ff.construir(datos);
    cout << "despues de construir" << endl;
    ff.imprimir();

    for (int i = 0; i < 20000; i++) {
        Punto p;
        p.x = azar() + 1 + i / 5000.0;
        p.y = azar() + 1 + i / 5000.0;
        p.z = azar();
        ff.insertar(p);
    }
    cout << "despues de insertar" << endl;
    ff.imprimir();

    return 0;
}
