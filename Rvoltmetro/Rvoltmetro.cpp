#include <iostream>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

int main(int argc, char** argv){
    if (argc < 2){
        cout << "metti il nome" <<endl;
        return 1;
    }

    double R, Req, dR, dReq;

    std::string fileInput = argv[1];
    std::ifstream InFile (fileInput.c_str());
    InFile >> R >> dR >> Req >> dReq;

    cout << R << endl;
    cout << dR << endl;
    cout << Req << endl;
    cout << dReq << endl;

    double Rv = R*Req/(R-Req);
    //double dRv = sqrt()

    cout << Rv << endl;

    InFile.close();

    std::string fileOutput = argv[2];
    std::ofstream OutFile (fileOutput.c_str());
    OutFile << "La resistenza del Voltmetro è Rv = " << Rv;
    OutFile.close();
}
