
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

#include <TF1.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>


using namespace std;

//bisogna definre la funzione Req

int main(int argc, char** argv){

//controllo che sia stato inserito il parametro
    if (argc < 3){
        cout << "metti il nome" <<endl;
        return 1;
    }

    TGraphErrors* myGraph = new TGraphErrors(argv[1]);

    //DEFINISCO LA MIA FUNZIONE
    TF1 *Req = new TF1("Req", Requiv, 0, 45e-6, 2);
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
    OutFile << fit->GetParameter(1) << "\t" << fit->GetParError(1);
    OutFile.close();

    myAPP->Run();
    return 0;

}



