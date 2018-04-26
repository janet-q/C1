
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>


using namespace std;

//bisogna definre la funzione Req

double Requivalente (double * x,double *par){
    return (par[1]*par[0]/(par[0]-par[1]))*x[0];
}

int main(int argc, char** argv){

//controllo che sia stato inserito il parametro
    if (argc < 3){
        cout << "metti il nome" <<endl;
        return 1;
    }

    TGraphErrors* myGraph = new TGraphErrors(argv[1]);
    myGraph->GetXaxis()->SetTitle("A (A)");
    myGraph->GetYaxis()->SetTitle("V (V)");
    myGraph->SetMarkerStyle(20);
    myGraph->SetMarkerSize(1);

    //DEFINISCO LA MIA FUNZIONE
    TF1* Req = new TF1("Req", Requivalente, 0, 50e-5, 2);
    Req->SetParameter(0, 1.06679e+07);
    Req->SetParameter(1, 67957.87);

    Req->SetParName(0,"Rv");
    Req->SetParName(1,"R");


    //INIZIO ANALISI DEI DATI

    //DISEGNO LO SCHIFO
    gStyle->SetOptFit(1112);
    TApplication* myAPP = new TApplication("myAPP", NULL, NULL);
    TCanvas* myCanvas = new TCanvas("Misura della resistenza equivalente", "Titolo",0,0,1500,1000);

    myCanvas->cd();


    myGraph->Draw("AP");
    myGraph->Fit("Req");
    myCanvas->Modified();
    myCanvas->Update();

    myAPP->Run();
    //myCanvas->Print();



    //risultati del fit

    //TF1 *fit = myGraph->GetFunction("pol1");

    std::string fileOutput = argv[2];
    std::ofstream OutFile (fileOutput.c_str());
    OutFile << Req->GetParameter(0) << "\t" << Req->GetParError(0);
    OutFile.close();

   // myAPP->Run();
    return 0;

}



