#include <iostream>
#include <string>
#include  <iomanip>
#include <locale>

using namespace std;

int main()
{

    // 1. Constantes y Arreglos
    const double CAPITAL_INICIAL = 850000.0;

    // Arreglo con los nombres de los bancos de la consigna.
    string nombresBancos[3] = { "Banco Provincia", "Banco Nacion", "Banco Hipotecario" };

    // Arreglos para almacenar los promedios de las TNAs y montos finales.
    double tnaPromedio[3] = { 0.0, 0.0, 0.0 };
    double tnaAnual[3];
    double tnaTrimestral[3];
    double tnaMensual[3];

    // Variables para registrar al ganador absoluto.
    double maxMontoFinal = 0.0;
    int indiceMejorBanco = 0;
    string mejorModalidad = "";

    //Ingreso de datos.
    cout << "=================================================" << endl;
    cout << "          INGRESO DE TASAS HISTORICAS            " << endl;
    cout << "=================================================" << endl;

    for (int i = 0; i < 3; i++) {
        cout << "\n> " << nombresBancos[i] << ":" << endl;
        double sumaTasas = 0.0;
        double tasaIngresada = 0.0;

        for (int ano = 1; ano <= 3; ano++) {
            // Si ano es 1 -> 2026 - 1 = 2025
            // Si ano es 2 -> 2026 - 2 = 2024
            // Si ano es 3 -> 2026 - 3 = 2023
            cout << "  Ingrese la TNA del ano " << 2026 - ano << " (en %): ";
            cin >> tasaIngresada;
            sumaTasas += tasaIngresada;
        }
        // Calculamos el promedio de los 3 años para este banco
        tnaPromedio[i] = sumaTasas / 3.0;
    }

    cout.imbue(locale("es_AR.UTF-8"));
    cout << fixed << setprecision(2);

    //Procesamiento de datos.
    for (int i = 0; i < 3; i++) {
        double tasaTantoPorUno = tnaPromedio[i] / 100.0;

        // A. Modalidad Anual
        tnaAnual[i] = CAPITAL_INICIAL * (1.0 + tasaTantoPorUno);

        // B. Modalidad Trimestral (4 períodos de reinversión)
        double capTrim = CAPITAL_INICIAL;
        double tasaTrim = tasaTantoPorUno / 4.0;
        for (int t = 1; t <= 4; t++) {
            capTrim = capTrim * (1.0 + tasaTrim);
        }
        tnaTrimestral[i] = capTrim;

        // C. Modalidad Mensual (12 períodos de reinversión)
        double capMensual = CAPITAL_INICIAL;
        double tasaMensual = tasaTantoPorUno / 12.0;
        for (int m = 1; m <= 12; m++) {
            capMensual = capMensual * (1.0 + tasaMensual);
        }
        tnaMensual[i] = capMensual;

        //Evaluamos la mejro opcion.
        if (tnaAnual[i] > maxMontoFinal) {
            maxMontoFinal = tnaAnual[i];
            indiceMejorBanco = i;
            mejorModalidad = "Inversion por un ano completo";
        }
        if (tnaTrimestral[i] > maxMontoFinal) {
            maxMontoFinal = tnaTrimestral[i];
            indiceMejorBanco = i;
            mejorModalidad = "Inversion por trimestres (reinvirtiendo)";
        }
        if (tnaMensual[i] > maxMontoFinal) {
            maxMontoFinal = tnaMensual[i];
            indiceMejorBanco = i;
            mejorModalidad = "Inversion por meses (reinvirtiendo)";
        }
    }

    //Mostramos rendimientos.
    cout << "\n=================================================" << endl;
    cout << "         RENDIMIENTOS NETOS OBTENIDOS            " << endl;
    cout << "=================================================" << endl;

    for (int i = 0; i < 3; i++) {
        cout << "\n> " << nombresBancos[i] << " (Tasa Promedio: " << tnaPromedio[i] << "%)" << endl;
        // Restamos el CAPITAL_INICIAL para mostrar estrictamente el RENDIMIENTO (la ganancia)
        cout << "  - Modalidad Anual:      $" << tnaAnual[i] - CAPITAL_INICIAL << "  (Total: $" << tnaAnual[i] << ")" << endl;
        cout << "  - Modalidad Trimestral: $" << tnaTrimestral[i] - CAPITAL_INICIAL << "  (Total: $" << tnaTrimestral[i] << ")" << endl;
        cout << "  - Modalidad Mensual:    $" << tnaMensual[i] - CAPITAL_INICIAL << "  (Total: $" << tnaMensual[i] << ")" << endl;
    }

    //Opcion recomendada
    cout << "\n=================================================" << endl;
    cout << "               OPCION RECOMENDADA                " << endl;
    cout << "=================================================" << endl;
    cout << "Banco recomendado:       " << nombresBancos[indiceMejorBanco] << endl;
    cout << "Modalidad mas rentable:  " << mejorModalidad << endl;
    cout << "Rendimiento neto:        $" << maxMontoFinal - CAPITAL_INICIAL << endl;
    cout << "Monto final acumulado:   $" << maxMontoFinal << endl;
    cout << "=================================================" << endl;

    cin.ignore();
    cin.get();
    return 0;
}


