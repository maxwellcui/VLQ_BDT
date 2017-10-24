//This is a testing version of the BDT training code
//Author: Zhaoyuan "Maxwell" Cui
//Physics department, Unversity of Arizona


/*------------------------------------------------------*\
|This code is designed for Vector-like B pair production |
\*----------------------------------------------------- */

#include "iostream"
#include "fstream"
#include "string"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

int bdt_vlq()
{
  //Load the library
  TMVA::Tools::Instance();
  
  std::cout<<std::endl;
  std::cout<<"==>Start BDT"<<std::endl;

  TString outputFileName("BDT_VLQ_BB.root");
  TFile *outputFile=TFile::Open(outputFileName, "RECREATE");
  
  //Register TMVA Factory
  TMVA::Factory *factory=new TMVA::Factory("BDT_VLQ", outputFile,
					   "V:!Silent:Color:DrawProgressBar:AnalysisType=Classification");


  //Add variables that will be used for MVA training
  factory->AddVariable("mu",'F');
  factory->AddVariable("el_pt.[0]",'F');
  factory->AddVariable("mu_pt.[0]",'F');
  factory->AddVariable("jet_pt.[0]",'F');
  factory->AddVariable("met_met",'F');
  //  factory->AddVariable("met_phi",'F');
  factory->AddVariable("SSee_2016",'I');
  factory->AddVariable("SSem_2016",'I');
  factory->AddVariable("SSmm_2016",'I');
  factory->AddVariable("eee_2016",'I');
  factory->AddVariable("eem_2016",'I');
  factory->AddVariable("emm_2016",'I');
  factory->AddVariable("mmm_2016",'I');
  factory->AddVariable("lep_pt.[0]",'I');
  factory->AddVariable("ht",'F');
  factory->AddVariable("met_sumet",'F');
  factory->AddVariable("bjet",'I');

  //Global event weights per tree
  Double_t signalWeight=1.0;
  Double_t backgroundWeight=1.0;


  //Read training data
  //
  // --- Signal
  TString fSig="../../dataPreparation/signal/normalized_BBS_M1000_302494_SSsig_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root"; 
  TFile *inputBB=TFile::Open(fSig);
  TTree *signal=(TTree*)inputBB->Get("nominal_Loose");
  factory->AddSignalTree(signal,signalWeight);
  factory->SetSignalWeightExpression("evtWeight");

  // --- Background
  std::ifstream list;
  list.open("../../dataPreparation/background/backgroundList.txt");
  if(!list)
    {
      std::cout<<"No such a file!\n";
      exit(1);
    }
  std::string fileName;
  std::vector <std::string> fileList;
  Int_t counter=0;
  while(list>>fileName)
    {
      fileList.push_back(fileName);
      counter++;
    }
  list.close();
  for(int i=0;i<counter;i++)
    {
      std::cout<<fileList[i]<<std::endl;
    }
  std::cout<<"There are total "<<counter<<" backgroud files.\n";

  TString prefix="../../dataPreparation/background/normalized_";
  TString fullName;
  for(int i=0; i<counter;i++)
    {
      fullName=prefix+fileList[i];
      TFile *inputBkg=TFile::Open(fullName);
      TTree *bkgTree=(TTree*)inputBkg->Get("nominal_Loose");
      factory->AddBackgroundTree(bkgTree,backgroundWeight);
      factory->SetBackgroundWeightExpression("evtWeight");
    }

  std::cout<<"File operation done"<<std::endl;





  //Apply additional cuts on the signal and background samples
  TCut mycut="";
  factory->PrepareTrainingAndTestTree(mycut,"SplitMode=random:!V:NormMode=None");

  // --- Book MVA method
  //
  //Boosted Decision Tree
  TString Option="!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20"; 

  //Book training method
  factory->BookMethod( TMVA::Types::kBDT, "BDT",
		       Option);

  //Train and evaluate
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  outputFile->Close();

  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;

  delete factory;

  //Launch the GUI for the root macros
  if (!gROOT->IsBatch())
    TMVA::TMVAGui(outputFileName);

  return 0;
}

int main()
{
  return bdt_vlq();
}
