//This is a testing version of the BDT training code
//Author: Zhaoyuan "Maxwell" Cui
//Physics department, Unversity of Arizona

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

  TString outputFileName("BDT_VLQ_data.root");
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
  TString fSig;
  TString fBkg;
  TString prefix="normalized_";
  
  std::ifstream inputFile("datafiles.txt");
  std::string fileName;

  TFile *inputBg=new TFile[10];
  TTree *bgTree=new TTree[10];
  
  Int_t counter=0;

  while(std::getline(inputFile,fileName))
    {
      fileName=prefix+fileName;
      inputBg[counter]=new TFile::Open(fileName);
      bgTree[counter]=(TTree*)inputBg[counter]->Get("nominal_Loose");
      counter++;
    }

  //---
  // TFile *inputSig=TFile::Open(fSig);
  // TFile *inputVV=TFile::Open(fBkg_VV);
  // TFile *inputVVV=TFile::Open(fBkg_VVV);
  // TFile *inputNP2=TFile::Open(fBkg_ttW_np2);
  // TFile *inputNP1=TFile::Open(fBkg_ttW_np1);
  // TFile *inputNP0=TFile::Open(fBkg_ttW_np0);
  // TFile *inputttH=TFile::Open(fBkg_ttH);

  // TTree *signal=(TTree*)inputSig->Get("nominal_Loose");
  // TTree *vv=(TTree*)inputVV->Get("nominal_Loose");
  // TTree *vvv=(TTree*)inputVVV->Get("nominal_Loose");
  // TTree *ttW_np2=(TTree*)inputNP2->Get("nominal_Loose");
  // TTree *ttW_np1=(TTree*)inputNP1->Get("nominal_Loose");
  // TTree *ttW_np0=(TTree*)inputNP0->Get("nominal_Loose");
  // TTree *ttH=(TTree*)inputttH->Get("nominal_Loose");

  std::cout<<"File operation done"<<std::endl;


  for(Int_t n=0;n<10;n++)
    {
      std::cout<<" --- BDT_VLQ\tUsing input file: "
	       <<"\n\t"
	       <<inputBg[n]->GetName()<<"\n\t"
	       <<std::endl;
    }


  //Global event weights per tree
  // Double_t signalWeight=1.0;
  // Double_t vvWeight=1.0;
  // Double_t vvvWeight=1.0;
  // Double_t ttW_np2Weight=1.0;
  // Double_t ttW_np1Weight=1.0;
  // Double_t ttW_np0Weight=1.0;
  // Double_t ttHWeight=1.0;

  // factory->AddSignalTree(signal,signalWeight);
  // factory->AddBackgroundTree(vv,vvWeight);
  // factory->AddBackgroundTree(vvv,vvvWeight);
  // factory->AddBackgroundTree(ttW_np2,ttW_np2Weight);
  // factory->AddBackgroundTree(ttW_np1,ttW_np2Weight);
  // factory->AddBackgroundTree(ttW_np0,ttW_np2Weight);
  // factory->AddBackgroundTree(ttH,ttHWeight);

  factory->SetWeightExpression("evtWeight");

  //Apply additional cuts on the signal and background samples
  TCut mycut="";
  factory->PrepareTrainingAndTestTree(mycut,"SplitMode=random:!V:NormMode=None");

  // --- Book MVA method
  //
  //Boosted Decision Tree

  //TString Option="!H:!V:NTrees=400:MaxDepth=10:MinNodeSize=5%:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining:SeparationType=GiniIndex:BoostType=AdaBoost:VarTransform=Decorrelate";
  
  //TString Option="!H:!V:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex";

  TString Option="!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate"; 

  factory->BookMethod( TMVA::Types::kBDT, "BDT",
		       Option);

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