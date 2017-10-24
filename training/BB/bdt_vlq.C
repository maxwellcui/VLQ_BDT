//This is a testing version of the BDT training code
//Author: Zhaoyuan "Maxwell" Cui
//Physics department, Unversity of Arizona


/*------------------------------------------------------*\
|This code is designed for Vector-like B pair production |
\*----------------------------------------------------- */

#include "iostream"
#include "fstream"

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
  factory->AddVariable("mu_pt.[1]",'F');
  factory->AddVariable("jet_pt.[0]",'F');
  factory->AddVariable("met_met",'F');
  factory->AddVariable("met_phi",'F');
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


  //Read training data
  //
  // --- Signal
  TString fSig="../../dataPreparation/signal/normalized_BBS_M1000_302494_SSsig_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root"; 
  TFile *inputBB=TFile::Open(fSig);
  TTree *signal=(TTree*)inputBB->Get("nominal_Loose");

  // --- Background
  TString fBkg="../../dataPreparation/background/normalized_ttW_np0_410066_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root";
  TFile *inputBkg=TFile::Open(fBkg);
  TTree *ttW_np0=(TTree*)inputBkg->Get("nominal_Loose");


  std::cout<<"File operation done"<<std::endl;



  //Global event weights per tree
  Double_t signalWeight=1.0;
  Double_t ttW_np0Weight=1.0;

  factory->AddSignalTree(signal,signalWeight);
  factory->SetSignalWeightExpression("evtWeight");

  factory->AddBackgroundTree(ttW_np0,ttW_np0Weight);
  factory->SetBackgroundWeightExpression("evtWeight");

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
