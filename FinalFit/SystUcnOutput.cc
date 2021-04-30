#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int N_Process = 8;
int N_Flavor = 4;
int N_Unc = 33;

string target[8] = {"Signal :",
                    "Fit_WZ : ", 
                    "Fit_ZZ : ",
                    "Fit_DY : ",
                    "Fit_ttbar : ",
                    "Fit_TTZ : ",
                    "Fit_tZq : ",
                    "Fit_Other : "
};
string UncList[33] = {"Central",
                     "JER_up", "JER_down", "JEC_up", "JEC_down", 
                     "ElecID_up", "ElecID_down", "ElecReco_up", "ElecReco_down",
                     "MuonID_up", "MuonID_down", "MuonIso_up", "MuonIso_down",
                     "cferr1_up", "cferr1_down", "cferr2_up", "cferr2_down",
                     "hf_up", "hf_down", "lf_up", "lf_down",
                     "hfstats1_up", "hfstats1_down", "hfstats2_up", "hfstats2_down",
                     "lfstats1_up", "lfstats1_down", "lfstats2_up", "lfstats2_down",
                     "jes_up", "jes_down", "pileup_up", "pileup_down"
};    
string FlavorList[4] = {"mmm", "mme", "mee", "eee"};

class channel{
    private:
        vector<string> getval;
        string line;
        string ChannelName;
    public:
        void Setchannels(string flavorName){
            ChannelName = flavorName;
        }
        bool isWanted(const std::string & line, std::string target){
            return (line.find(target) != string::npos);
        }
        void RetrieveInfo(string UncType){
            ifstream input (("../Record/2017_Zut/"+UncType+"/"+ChannelName+".log").c_str() ,ifstream::in);
            if(input.is_open()){
                while(getline(input, line)){
                    for(int i=0 ; i<8 ; i++){
                        if(isWanted(line, target[i])) getval.push_back(line.substr(line.find(" : ")+3, 10));
                    }
                }
            }
        } 
        void StoreInfo(ostream & output, string UncType){

            output << UncType.c_str() << ",";
            for(int i=0 ; i<getval.size() ; i++) output << getval[i] << ",";
            output << endl;
            getval.clear();
        }

};



int main(){
    
    ofstream output;
    output.open("example.csv");

    channel flavor[4];
 
    for(int FlavorId=0 ; FlavorId<N_Flavor ; FlavorId++){
        flavor[FlavorId].Setchannels(FlavorList[FlavorId]);
        output << endl;
        output << FlavorList[FlavorId] << endl;
        output << ",Signal_no,fit_WZ,fit_ZZ,fit_DY,fit_ttbar,TTZ,tZq,Others" << endl;

        for(int UncId=0 ; UncId<N_Unc ; UncId++){
            flavor[FlavorId].RetrieveInfo(UncList[UncId]);
            flavor[FlavorId].StoreInfo(output, UncList[UncId]);
        }    
    }

    output.close();
}

