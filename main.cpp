#include <iostream>
#include <string>
#include <cstdlib>
#include "mes.h"
// Ponizej biblioteki do rysowania wykresow
#include "pbPlots.hpp"
#include "supportLib.hpp"
using namespace std;

void drawPlot(const MES& solvedProblem, int pointsNumber)
{
    vector<double> xPoints;
    vector<double> yPoints;
    double start = solvedProblem.getLeftMargin();
    double diff = (solvedProblem.getRightMargin() - start) / pointsNumber;
    for (int i = 0; i < pointsNumber; i++)
    {
        xPoints.push_back(start + i * diff);
        yPoints.push_back(solvedProblem.getValueInPoint(start + i * diff));
    }
    RGBABitmapImageReference* imageRef = CreateRGBABitmapImageReference();
    StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
    bool success = DrawScatterPlot(imageRef, 800, 800, &xPoints, &yPoints, errorMessage);
    if (success)
    {
        vector<double>* pngData = ConvertToPNG(imageRef->image);
        WriteToFile(pngData, "Wykres.png");
        DeleteImage(imageRef->image);
        cout<<"Wykres zosta\210 pomyslnie wygenerowany do folderu g\210\242wnego jako plik \"Wykres.png\""<<endl;
        system("pause");
    }
    else
    {
        cout<<"Wyst\245pi\210 b\210\245d podczas generowania wykresu. Koniec programu."<<endl;
        exit(-2);
    }
}

int main()
{
    cout<<"Podaj liczb\251 element\242w sko\344czonych: ";
    int elements;
    cin>>elements;
    if (elements < 1)
    {
        cout<<"Podano niepoprawn\245 warto\230\206. Koniec programu."<<endl;
        exit(-1);
    }
    cout<<"Czy uwzgl\251dnia\206 sta\210\245 grawitacji (tak / nie)? ";
    string answer;
    cin>>answer;
    bool state;
    if (answer == "tak" || answer == "Tak")
        state = true;
    else if (answer == "nie" || answer == "Nie")
        state = false;
    else
    {
        cout<<"Podano niepoprawn\245 odpowied\253. Koniec programu."<<endl;
        exit(-1);
    }
    MES mesSolver = MES(elements, state); // Jezeli chcemy pominac G, ustawiamy false
    mesSolver.solve();
    drawPlot(mesSolver, 5*elements);
    return 0;
}
