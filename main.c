#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <math.h>
using namespace std;
int eckenanzahl = 0;

double getPolygonArea(double x[], double y[], int n) {
    if ((x == NULL) || (y == NULL)) return 0.0;  // auf leere Argumente testen
    // Anzahl der Ecken des Polygons
    if (n < 3) {
        printf("Fehler aufgetreten");
        return 0.0;
    }
    double a = 0.0;
    // Variable fuer Flaeche des Polygons
    for (int i = 0; i < n; i++) {                // Schleife zwecks Summenbildung
        a += (y[i] + y[(i + 1) % n]) * (x[i] - x[(i + 1) % n]);
    }
    return abs(a / 2.0);                    // Flaecheninhalt zurueckliefern
}

void getSchwerpunkt(double x[], double y[], int n, double b) {
    if ((x == NULL) || (y == NULL))
    {
        cout << "Fehler: keine Eckpunkte eingegeben" << endl;
    }
    if (n < 3) {
        cout << "Fehler: weniger als 3 Eckpunkte angegeben" << endl;
    }
    double x_s = 0.0;
    double y_s = 0.0;
    for (int i = 0; i < n; i++) {
        x_s += (x[i] + x[(i + 1) % n]) * ((x[i] * y[(i + 1) % n]) - (x[(i + 1) % n] * y[i]));
        y_s += (y[i] + y[(i + 1) % n]) * ((x[i] * y[(i + 1) % n]) - (x[(i + 1) % n] * y[i]));
    }
    double f = abs(x_s / (6 * b));
    double e = abs(y_s / (6 * b));
    cout << " Der Geometrische Schwerpunkt S des Polygons befindet sich bei S=(" << fixed << setprecision(2) << f << "/" << fixed << setprecision(2) << e << ")" << endl;
}

void evenodd(double x[], double y[], int n)
{
    float testx;
    float testy;
    printf("\n Platzierung des gewuenschten Loches: \n--------------------------------------");
    printf("\n Bitte gewuenschte x Koordinate eingeben:");
    scanf("%a", &testx);
    printf("\n Bitte gewuenschte y Koordinate eingeben:");
    scanf("%a", &testy);

    int i, j, c = 0;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((y[i] > testy) != (y[j] > testy)) &&
            (testx < (x[j] - x[i]) * (testy - y[i]) / (y[j] - y[i]) + x[i]))
            c = !c;
    }
    if (c != 1) {
        printf("\n Das gewuenschte Loch liegt ausserhalb des Polygons\n \n");
    }
    else {
        printf("\n Das gewuenschte Loch liegt innerhalb des Polygons\n\n");
    }

}




int main()
{
    /*ofstream out;
    out.open("test.txt");
    out << "Hello File";
    out.close();
 
    ifstream in("hallo.txt");
    string zeile;
    while (!in.eof()) {
        getline(in, zeile);
        cout << zeile << endl;
    }*/
    FILE* fp;
    size_t len = 0;
    char resp;

    double x, y;

    // open the input file "messwerte.txt" for reading
    fp = fopen("hallo.txt", "r");
    if (fp == NULL)
    {
        // if file could not be opened (wrong path, not readable, ...)
        // output a short message and immediately exit
        printf("Eingabedatei kann nicht geoeffnet werden.\n");
        scanf("%c", &resp);
        exit(EXIT_FAILURE);
    }


    // print program header
    printf("\n\n Programm zur Berechnung eines Polygons\n");
    printf("----------------------------------------\n");



    // the following loop reads a new value in every iteration
    // until the end of the file or some invalid token is found
    int i = 0;
    double c[50];
    double d[50];
    while (1)
    {

        len = fscanf(fp, "%lf %lf", &x, &y);

        c[i] = { x };
        d[i] = { y };
        i++;


        /*for (int i = 0; i <= y; i++) {
            c[i] = { y };
        }*/
        if (len == EOF)
            break;
        else if (len == 0) {
            printf("Unerwartetes Zeichen in der Eingabedatei.");
            scanf("%c", &resp);
            exit(EXIT_FAILURE);
        }

        printf(" Lese Eckpunkt: %6.2f/%6.2f\n", x, y);
    }

    // output results
    printf("\n Ergebnisse:\n");
    printf("-------------\n\n");
    double ergebnis = getPolygonArea(c, d, i);
    cout << " Der Flaecheninhalt A des Polygons ist A=" << ergebnis << endl;
    getSchwerpunkt(c, d, i, ergebnis);
    evenodd(c, d, ergebnis);
    // finally close the input file and clean up memory
    fclose(fp);

    // wait for user input before closing terminal
    scanf("%c", &resp);


    /*if (in.is_open()) {
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    }
    else {
        cout << "File didnt exist" << endl;
    }*/
}