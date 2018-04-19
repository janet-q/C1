#include <iostream>
#include <fstream>
#include <TGraph.h>
#include <TF1.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <math.h>
#include <vector>

#define R 90.0 //Ohm
#define VO 1.5 //V


using namespace std;


/*double espon(double* x, double* par){
    return (double)R*(double)VO*par[1]*(exp(-(double)R*x[0]/(2*par[0])));
}

double sincos(double* x, double* par){
    return ((double)R/(2*par[0]))*cos((sqrt(1/(par[0]*par[1])))*x[0])+(sqrt(1/(par[0]*par[1])))*sin((sqrt(1/(par[0]*par[1])))*x[0]);
}
*/
double funz (double* x, double* par){
    double omega = sqrt(1/(par[0]*par[1]));
    double gamma = R/(2*par[0]);
    double beta = sqrt(gamma*gamma-omega*omega);
    //R*C*V0*(exp(-gamma*t)*(gamma*cos(omega*t)+omega*sin(omegat)
    return par[2]*((exp(-(gamma-beta)*x[0]))-exp(-(gamma+beta)*x[0]));
}

int main(int argc, char** argv){

//controllo che sia stato inserito il parametro
    if (argc < 2){
        cout << "metti il nome" <<endl;
        return 1;
    }

    double tMin = 0;
    double tMax = 0.001;

    int N = 17;

    TGraph* myGraph = new TGraph(argv[1]);

    //INIZIO ANALISI DEI DATI
    TF1* myFun = new TF1("myFun", funz, 0, 0.001, 3);

    //Inizializzazione dei parametri:
    myFun->SetParameter(0, 0.15);
    myFun->SetParameter(1, 5*1e-8);
    myFun->SetParameter(2, 5);

    //Nomino i parametri
    myFun->SetParName(0,"L");
    myFun->SetParName(1,"C");
    myFun->SetParName(2,"amp");

    //DISEGNO LO SCHIFO
    gStyle->SetOptFit(1112);
    TApplication* myAPP = new TApplication("myAPP", NULL, NULL);
    TCanvas* myCanvas = new TCanvas("myCanvas", "Titolo",0,0,1500,1000);

    myCanvas->cd();
    myGraph->GetXaxis();
    myGraph->SetTitle("t (micros)");
    myGraph->GetYaxis();
    myGraph->SetTitle("V (mV)");
    myGraph->SetMarkerStyle(20);
    myGraph->SetMarkerSize(1);

    myGraph->Draw("AP");
    myGraph->Fit("myFun");
    //myFun->Draw("same");
    myCanvas->Modified();
    myCanvas->Update();

    //myCanvas->Print();

    //risultati del fit
   /* double chi2 = myFun->GetChisquare();
    cout << chi2 << endl;
    cout << "Chi ridotto" << chi2/myFun->GetNDF() << endl;
    cout << "p_v" << myFun->GetProb() << endl;
    double amp = myFun->GetChisquare();
    */
    myAPP->Run();
    return 0;

}



