//This is a testing version of the BDT training code
//Author: Zhaoyuan "Maxwell" Cui
//Physics department, Unversity of Arizona

#include "iostream"

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

  //Read training data
  //
  TString fSig="../normalization/BBS_sig.root";
  TString fBkg_VV="../normalization/VV.root";
  TString fBkg_VVV="../normalization/VVV.root";
  TString fBkg_ttW_np2="../normalization/ttW_np2_bkg.root";
  TString fBkg_ttW_np1="../normalization/ttW_np1_bkg.root";
  TString fBkg_ttW_np0="../normalization/ttW_np0_bkg.root";
  TString fBkg_ttH="../normalization/ttH.root";

  TFile *inputSig=TFile::Open(fSig);
  TFile *inputVV=TFile::Open(fBkg_VV);
  TFile *inputVVV=TFile::Open(fBkg_VVV);
  TFile *inputNP2=TFile::Open(fBkg_ttW_np2);
  TFile *inputNP1=TFile::Open(fBkg_ttW_np1);
  TFile *inputNP0=TFile::Open(fBkg_ttW_np0);
  TFile *inputttH=TFile::Open(fBkg_ttH);

  TTree *signal=(TTree*)inputSig->Get("nominal_Loose");
  TTree *vv=(TTree*)inputVV->Get("nominal_Loose");
  TTree *vvv=(TTree*)inputVVV->Get("nominal_Loose");
  TTree *ttW_np2=(TTree*)inputNP2->Get("nominal_Loose");
  TTree *ttW_np1=(TTree*)inputNP1->Get("nominal_Loose");
  TTree *ttW_np0=(TTree*)inputNP0->Get("nominal_Loose");
  TTree *ttH=(TTree*)inputttH->Get("nominal_Loose");

  std::cout<<"File operation done"<<std::endl;

  //Add variables that will be used for MVA training
  factory->AddVariable("mu",'F');
  factory->AddVariable("el_pt.[0]",'F');
  factory->AddVariable("mu_pt.[0]",'F');
  factory->AddVariable("jet_pt.[0]",'F');
  factory->AddVariable("met_met",'F');
  factory->AddVariable("met_phi",'F');
  factory->AddVariable("SSee",'I');
  factory->AddVariable("SSem",'I');
  factory->AddVariable("SSmm",'I');
  factory->AddVariable("eee",'I');
  factory->AddVariable("eem",'I');
  factory->AddVariable("emm",'I');
  factory->AddVariable("mmm",'I');
  factory->AddVariable("lep_pt.[0]",'I');
  factory->AddVariable("ht",'F');
  factory->AddVariable("met_sumet",'F');
  factory->AddVariable("bj",'I');

  std::cout<<" --- BDT_VLQ\tUsing input file: "
	   <<"\n\t"
	   <<inputSig->GetName()<<"\n\t"
	   <<inputVV->GetName()<<"\n\t"
	   <<inputVVV->GetName()<<"\n\t"
	   <<inputNP2->GetName()<<"\n\t"
	   <<inputNP1->GetName()<<"\n\t"
	   <<inputNP0->GetName()<<"\n\t"
	   <<inputttH->GetName()<<std::endl;

  //Global event weights per tree
  Double_t signalWeight=1.0;
  Double_t vvWeight=1.0;
  Double_t vvvWeight=1.0;
  Double_t ttW_np2Weight=1.0;
  Double_t ttW_np1Weight=1.0;
  Double_t ttW_np0Weight=1.0;
  Double_t ttHWeight=1.0;

  factory->AddSignalTree(signal,signalWeight);
  factory->AddBackgroundTree(vv,vvWeight);
  factory->AddBackgroundTree(vvv,vvvWeight);
  factory->AddBackgroundTree(ttW_np2,ttW_np2Weight);
  factory->AddBackgroundTree(ttW_np1,ttW_np2Weight);
  factory->AddBackgroundTree(ttW_np0,ttW_np2Weight);
  factory->AddBackgroundTree(ttH,ttHWeight);

  factory->SetWeightExpression("evtWeight");

  //Apply additional cuts on the signal and background samples
  TCut mycut="";
  factory->PrepareTrainingAndTestTree(mycut,"SplitMode=random:!V:NormMode=None");

  // --- Book MVA method
  //
  //Boosted Decision Tree

  TString Option="!H:!V:NTrees=1000:MaxDepth=10:MinNodeSize=2.5%:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining:SeparationType=MisClassificationError";

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
