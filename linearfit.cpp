
#include <iostream>
#include <fstream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <sstream>
#include <cstring>
#include <string>
#include <TF1.h>


using namespace std;


int main(int argc, char** argv){

//controllo che sia stato inserito il parametro
    if (argc < 2){
        cout << "metti il nome" <<endl;
        return 1;
    }

    TGraphErrors* myGraph = new TGraphErrors(argv[1]);

    //INIZIO ANALISI DEI DATI

    //DISEGNO LO SCHIFO
    gStyle->SetOptFit(1112);
    TApplication* myAPP = new TApplication("myAPP", NULL, NULL);
    TCanvas* myCanvas = new TCanvas("Misura della resistenza 2", "Titolo",0,0,1500,1000);

    myCanvas->cd();
    myGraph->GetXaxis()->SetTitle("A (A)");
    myGraph->GetYaxis()->SetTitle("V (V)");
    myGraph->SetMarkerStyle(20);
    myGraph->SetMarkerSize(1);

    myGraph->Draw("AP");
    myGraph->Fit("pol1");
    myCanvas->Modified();
    myCanvas->Update();

    myCanvas->Print();



    //risultati del fit

    TF1 *fit = myGraph->GetFunction("pol1");

    std::string fileOutput = argv[2];
    std::ofstream OutFile (fileOutput.c_str());
    OutFile << "La Resistenza misurata è: " << fit->GetParameter(0)<<endl;
    OutFile << "Il Chi quadro è: " << fit->GetChisquare();
    OutFile.close();

    myAPP->Run();
    return 0;

}



