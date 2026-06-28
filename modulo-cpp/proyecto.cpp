#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// 1. STRUCTS
struct Curso {
    string codigo;
    string nombre;
    string area;
    int creditos;
};

struct Prerrequisito {
    string curso;
    string prerrequisito;
};

struct Historial {
    string estudiante;
    string codigoCurso;
    int nota;
};

struct Interes {
    string estudiante;
    string area;
};

// 2. FUNCIONES DE GENERACION DE CSV
void generarCSVCursos(const vector<Curso>& lista) {
    ofstream archivo("../data/cursos.csv");
    if (archivo.is_open()) {
        archivo << "codigo,nombre,area,creditos\n";
        for (const auto& c : lista) archivo << c.codigo << "," << c.nombre << "," << c.area << "," << c.creditos << "\n";
        archivo.close();
    }
}

void generarCSVPrerrequisitos(const vector<Prerrequisito>& lista) {
    ofstream archivo("../data/prerrequisitos.csv");
    if (archivo.is_open()) {
        archivo << "curso,prerrequisito\n";
        for (const auto& p : lista) archivo << p.curso << "," << p.prerrequisito << "\n";
        archivo.close();
    }
}

void generarCSVHistorial(const vector<Historial>& lista) {
    ofstream archivo("../data/historial.csv");
    if (archivo.is_open()) {
        archivo << "estudiante,codigoCurso,nota\n";
        for (const auto& h : lista) archivo << h.estudiante << "," << h.codigoCurso << "," << h.nota << "\n";
        archivo.close();
    }
}

void generarCSVIntereses(const vector<Interes>& lista) {
    ofstream archivo("../data/intereses.csv");
    if (archivo.is_open()) {
        archivo << "estudiante,area\n";
        for (const auto& i : lista) archivo << i.estudiante << "," << i.area << "\n";
        archivo.close();
    }
}

void guardarTodosLosCSV(const vector<Curso>& c, const vector<Prerrequisito>& p, const vector<Historial>& h, const vector<Interes>& i) {
    generarCSVCursos(c);
    generarCSVPrerrequisitos(p);
    generarCSVHistorial(h);
    generarCSVIntereses(i);
    cout << "\n[EXITO] Todos los datos han sido guardados en los archivos CSV.\n";
}

// 3. REGISTRO
void registrarNota(vector<Historial>& lista) {
    Historial h;
    cout << "\n--- REGISTRAR NOTA ---\n";
    cout << "ID del Estudiante: "; cin >> h.estudiante;
    cout << "Codigo del Curso: "; cin >> h.codigoCurso;
    cout << "Nota obtenida: "; cin >> h.nota;
    lista.push_back(h);
    cout << "[OK] Nota registrada temporalmente en memoria.\n";
}

// 4. CONSULTA Y REPORTE
void mostrarHistorial(const vector<Historial>& lista) {
    string id;
    cout << "\n--- CONSULTAR HISTORIAL ---\n";
    cout << "Ingrese ID del Estudiante: "; cin >> id;
    
    cout << "\nCursos de " << id << ":\n";
    bool encontrado = false;
    for (const auto& h : lista) {
        if (h.estudiante == id) {
            cout << "- Curso: " << h.codigoCurso << " | Nota: " << h.nota;
            if (h.nota >= 11) cout << " (Aprobado)\n";
            else cout << " (Desaprobado)\n";
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontraron registros para este estudiante.\n";
}

void reporteGeneral(const vector<Historial>& historial, const vector<Curso>& cursos) {
    string id;
    cout << "\n--- REPORTE GENERAL ---\n";
    cout << "Ingrese ID del Estudiante: "; cin >> id;

    int aprobados = 0, desaprobados = 0;
    int sumaNotas = 0, cantidadCursos = 0;
    int notaMax = -1, notaMin = 21;
    string cursoMax, cursoMin;
    bool encontrado = false;

    for (const auto& h : historial) {
        if (h.estudiante == id) {
            encontrado = true;
            sumaNotas += h.nota;
            cantidadCursos++;
            
            if (h.nota >= 11) aprobados++;
            else desaprobados++;

            if (h.nota > notaMax) { notaMax = h.nota; cursoMax = h.codigoCurso; }
            if (h.nota < notaMin) { notaMin = h.nota; cursoMin = h.codigoCurso; }
        }
    }

    if (!encontrado) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    // Buscar nombres de los cursos para el reporte
    string nombreMax = cursoMax, nombreMin = cursoMin;
    for (const auto& c : cursos) {
        if (c.codigo == cursoMax) nombreMax = c.nombre;
        if (c.codigo == cursoMin) nombreMin = c.nombre;
    }

    float promedio = (float)sumaNotas / cantidadCursos;

    cout << "\n-----------------------------------\n";
    cout << "Estudiante: " << id << "\n";
    cout << fixed << setprecision(1); // Formato para un decimal
    cout << "Promedio general: " << promedio << "\n";
    cout << "Cursos aprobados: " << aprobados << "\n";
    cout << "Cursos desaprobados: " << desaprobados << "\n";
    cout << "Curso con mayor nota: " << nombreMax << " (" << notaMax << ")\n";
    cout << "Curso con menor nota: " << nombreMin << " (" << notaMin << ")\n";
    cout << "-----------------------------------\n";
}

// 5. FUNCION PRINCIPAL Y MENU
int main() {
    vector<Curso> cursos = {
        {"CS101", "Programacion I", "Programacion", 4}, {"CS102", "Programacion II", "Programacion", 4},
        {"BD101", "Base de Datos I", "Datos", 4}, {"IA101", "Inteligencia Artificial", "IA", 4},
        {"SO101", "Sistemas Operativos", "Sistemas", 4}, {"RE101", "Redes de Computadoras", "Redes", 3},
        {"SI101", "Seguridad Informatica", "Seguridad", 3}, {"IS101", "Ingenieria de Software", "Sistemas", 4}
    };
    vector<Prerrequisito> prerrequisitos = {
        {"CS102", "CS101"}, {"BD101", "CS102"}, {"IA101", "CS102"}, 
        {"SO101", "CS101"}, {"RE101", "SO101"}, {"SI101", "RE101"}
    };
    vector<Historial> historial = {
        {"estudiantel", "CS101", 15}, {"estudiantel", "CS102", 12}, {"estudiantel", "BD101", 9}, {"estudiantel", "IA101", 14},
        {"estudiante2", "CS101", 18}, {"estudiante2", "CS102", 16}, {"estudiante2", "SO101", 10}, {"estudiante2", "IS101", 14}
    };
    vector<Interes> intereses = {
        {"estudiantel", "Programacion"}, {"estudiantel", "IA"}, {"estudiantel", "Datos"},
        {"estudiante2", "Sistemas"}, {"estudiante2", "Seguridad"}
    };

    // Generar CSV iniciales al abrir el programa
    guardarTodosLosCSV(cursos, prerrequisitos, historial, intereses);

    int opcion;
    do {
        cout << "\n=======================================\n";
        cout << " SISTEMA DE RECOMENDACION ACADEMICA\n";
        cout << "=======================================\n";
        cout << "1. Registrar nueva nota en historial\n";
        cout << "2. Consultar historial de un estudiante\n";
        cout << "3. Ver Reporte General del estudiante\n";
        cout << "4. Guardar cambios en archivos CSV\n";
        cout << "5. Salir\n";
        cout << "=======================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarNota(historial); break;
            case 2: mostrarHistorial(historial); break;
            case 3: reporteGeneral(historial, cursos); break;
            case 4: guardarTodosLosCSV(cursos, prerrequisitos, historial, intereses); break;
            case 5: cout << "\nSaliendo del sistema imperativo...\n"; break;
            default: cout << "\nOpcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}