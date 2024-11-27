#include <iostream>
#include <chrono>
#include <format>
#include <stdio.h>
#include <fstream>
#include "GasSupplySystem.h"
#include "Addition.h"
#include "MainMenu.h"

using namespace std;
using namespace chrono;

int StartProgram(GasSupplySystem& GSS) {

    while (1)
    {
        vector<string> menu = { "Add Pipe", "Add CS",
            "Show", "Edit Pipe", "Edit Station", 
            "Delete", "Network", "Save", "Load" };
        switch (ChooseActionMenu(menu, true))
        {
        case 1:
        {

            GSS.AddPipe();
            break;
        }
        case 2:
        {
            GSS.AddCS();
            break;
        }
        case 3:
        {
            MenuShowObjects(GSS);
            break;
        }
        case 4:
        {
            MenuEditPipes(GSS);
            break;
        }
        case 5:
        {
            MenuEditCS(GSS);
            break;
        }
        case 6:
        {
            MenuDelete(GSS);
            break;
        }
        case 7:
        {   
            MenuNetwork(GSS);
            break;
        }
        case 8:
        {
            MenuSave(GSS);
            break;
        }
        case 9:
        {
            MenuLoad(GSS);
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Wrong action" << "\n";
        }
        }
    }
}

int main(int argc, char* argv[])
{
    GasSupplySystem GSS;
    redirect_output_wrapper cerr_out(cerr);
    string time = std::format("{:%d.%m.%Y_%H_%M_%OS}", system_clock::now() + std::chrono::hours(3));
    ofstream out_logfile("Logging/log_" + time);
    if (out_logfile)
        cerr_out.redirect(out_logfile);

    StartProgram(GSS);
}
   
    

    




