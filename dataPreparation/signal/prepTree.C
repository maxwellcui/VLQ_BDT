//A ROOT macro that prepares Tree for TMVA training
//----------------------------------------------
//Author: Maxwell Cui
//Created date: Aug 19, 2017
//Latest modified: Oct 17, 2017
//----------------------------------------------

#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TH1F.h"


void create(TFile* inputTree, TString outputName)
{
  TTree *oldTree=new TTree;
  inputTree->GetObject("nominal_Loose",oldTree);
  
  //Deactive all branches
  oldTree->SetBranchStatus("*",0);

  //Active the interested branches
 
  //Variables for training
  oldTree->SetBranchStatus("ht",1);
  oldTree->SetBranchStatus("met_met",1);
  oldTree->SetBranchStatus("met_sumet",1);
  oldTree->SetBranchStatus("jet_pt",1);
  oldTree->SetBranchStatus("lep_pt",1);

  //====================Output file==========================
  TFile *outputFile=new TFile(outputName,"recreate");
  TTree *newTree=oldTree->CloneTree(0);
  newTree->SetName("trainingTree");

  //b-tagging
  oldTree->SetBranchStatus("SSee_2016",1);
  oldTree->SetBranchStatus("SSmm_2016",1);
  oldTree->SetBranchStatus("SSem_2016",1);
  oldTree->SetBranchStatus("eee_2016",1);
  oldTree->SetBranchStatus("eem_2016",1);
  oldTree->SetBranchStatus("emm_2016",1);
  oldTree->SetBranchStatus("mmm_2016",1);
  oldTree->SetBranchStatus("jet_mv2c10",1);   //Using MV2c10 for b-tagging

  //event weight calculation
  oldTree->SetBranchStatus("weight_mc",1);
  oldTree->SetBranchStatus("weight_jvt",1);
  oldTree->SetBranchStatus("weight_leptonSF_tightLeps",1);
  oldTree->SetBranchStatus("weight_indiv_SF_MU_TTVA",1);
  oldTree->SetBranchStatus("weight_pileup",1);
  oldTree->SetBranchStatus("weight_bTagSF_77",1);

 


  //Working with b-jet
  //
  // Declaration of leaf types
  std::vector<float>   *jet_pt;
  std::vector<float>   *jet_mv2c10;
  Float_t         met_met;
  Float_t         met_sumet;
  Int_t           SSee_2016;
  Int_t           SSmm_2016;
  Int_t           SSem_2016;
  Int_t           eee_2016;
  Int_t           eem_2016;
  Int_t           emm_2016;
  Int_t           mmm_2016;
  std::vector<float>   *lep_pt;
  Float_t         ht;
 
  // List of branches
  TBranch        *b_jet_pt;   //!
  TBranch        *b_jet_mv2c10;   //!
  TBranch        *b_met_met;   //!
  TBranch        *b_met_sumet;
  TBranch        *b_SSee_2016;   //!
  TBranch        *b_SSmm_2016;   //!
  TBranch        *b_SSem_2016;   //!
  TBranch        *b_eee_2016;   //!
  TBranch        *b_eem_2016;   //!
  TBranch        *b_emm_2016;   //!
  TBranch        *b_mmm_2016;   //!
  TBranch        *b_lep_pt;   //!
  TBranch        *b_ht;   //!

  //Set object pointer
  jet_pt = 0;
  jet_mv2c10 = 0;
  lep_pt = 0;
  
  //Set branch addresses and brunch pointers
  oldTree->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
  oldTree->SetBranchAddress("jet_mv2c10", &jet_mv2c10, &b_jet_mv2c10);
  oldTree->SetBranchAddress("met_met", &met_met, &b_met_met);
  oldTree->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
  oldTree->SetBranchAddress("SSee_2016", &SSee_2016, &b_SSee_2016);
  oldTree->SetBranchAddress("SSmm_2016", &SSmm_2016, &b_SSmm_2016);
  oldTree->SetBranchAddress("SSem_2016", &SSem_2016, &b_SSem_2016);
  oldTree->SetBranchAddress("eee_2016", &eee_2016, &b_eee_2016);
  oldTree->SetBranchAddress("eem_2016", &eem_2016, &b_eem_2016);
  oldTree->SetBranchAddress("emm_2016", &emm_2016, &b_emm_2016);
  oldTree->SetBranchAddress("mmm_2016", &mmm_2016, &b_mmm_2016);
  oldTree->SetBranchAddress("lep_pt", &lep_pt, &b_lep_pt);
  oldTree->SetBranchAddress("ht", &ht, &b_ht);

  //Working with normalization  
  Float_t lumi=36.1;   

  //Declare leaf and branch
  Float_t         weight_mc;
  Float_t         weight_jvt;
  Float_t         weight_leptonSF_tightLeps;
  Float_t         weight_indiv_SF_MU_TTVA;
  Float_t         weight_pileup;
  Float_t         weight_bTagSF_77;

  TBranch        *b_weight_mc;
  TBranch        *b_weight_jvt;
  TBranch        *b_weight_leptonSF_tightLeps;
  TBranch        *b_weight_indiv_SF_MU_TTVA;
  TBranch        *b_weight_pileup;
  TBranch        *b_weight_bTagSF_77;

  //Set branch addresses and brunch pointers
  oldTree->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);
  oldTree->SetBranchAddress("weight_jvt", &weight_jvt, &b_weight_jvt);
  oldTree->SetBranchAddress("weight_leptonSF_tightLeps", &weight_leptonSF_tightLeps, &b_weight_leptonSF_tightLeps);
  oldTree->SetBranchAddress("weight_indiv_SF_MU_TTVA", &weight_indiv_SF_MU_TTVA, &b_weight_indiv_SF_MU_TTVA);
  oldTree->SetBranchAddress("weight_pileup", &weight_pileup, &b_weight_pileup);
  oldTree->SetBranchAddress("weight_bTagSF_77", &weight_bTagSF_77, &b_weight_bTagSF_77);


  //Get the data...algrithm is from Prof. Varnes
  TH1F *lumInt=new TH1F;
  inputTree->GetObject("hIntLum",lumInt);
  Float_t mcnorm=lumInt->GetBinContent(1);
  
  //Declare variable for event weight
  Float_t evtWeight;

  //Branch for event weight
  TBranch *evtBranch=newTree->Branch("evtWeight",&evtWeight,"evtWeight/F");

  std::cout<<"mcnorm is: "<<mcnorm<<std::endl;

  //Declare bjet variable
  Int_t bjet;
  
  //Branch of b-jet
  TBranch *bjetBranch=newTree->Branch("bjet",&bjet,"bjet/I");
  
  //Get the number of events
  Long64_t nentries=(Int_t)oldTree->GetEntries();

  //Calculate eventWeight
  //Calculate bjet, algorithm is provided by Prof. Varnes
  for(Long64_t i=0;i<nentries;i++)
    {
      //Get entry
      oldTree->GetEntry(i);
      bjet=0;                    //Initilization

      //B-tagging
      if(SSee_2016 || SSem_2016 || SSmm_2016 || eee_2016 || eem_2016 || emm_2016 || mmm_2016)
      	{
      	  for(unsigned int ibjet=0;ibjet<jet_mv2c10->size();ibjet++)
      	    {
      	      //0.1758475 85% WP
	      //0.8244273 70% WP
	      if  (jet_mv2c10->at(ibjet) > 0.645925)  // 77% WP 		 
		{ 
		  bjet++;
		}      
      	    }
      	}
      
      //Event weight calculation
      //Calculate event weight
      if(bjet!=0)
	{
	  evtWeight=weight_mc*weight_jvt*(weight_leptonSF_tightLeps/weight_indiv_SF_MU_TTVA)*weight_pileup*weight_bTagSF_77*lumi/mcnorm;
	  newTree->Fill();
	}
    
    }

  newTree->Write(0,TObject::kOverwrite);
  newTree->Print();


  outputFile->Close();
  
  delete oldTree;
  delete lumInt;
}

void prepTree(char* argv)
{

  //Variable 'envName' can be the environmental variable on the system that
  //includes the path to the directory of the data files.
  //Please make sure that the variable is exported.
  
  const char* envName="MCDATA";
  std::string dataPATH=std::getenv(envName);
  if(dataPATH.empty())
    {
      std::cout<<"\tData path not found! Please make sure you export MCDATA which contains the path of data.\n";
    }
  else
    {
      std::cout<<"\tData path is: "<<dataPATH<<std::endl<<std::endl;
    }
  std::string dlist(argv);
  std::ifstream inputFile(dlist);
  std::string fileName;

  while(std::getline(inputFile,fileName))
    {
      //Create the full path to the data
      TString fullInput;
      fullInput=dataPATH+fileName;
      std::cout<<"Readig file: "<<fullInput<<std::endl;

      TString outputName;
      outputName="normalized_"+fileName;

      TFile *bg=new TFile(fullInput);
      create(bg,outputName);
      delete bg;
	  
	  
    }
  inputFile.close();
}

int main(int argc, char **argv)
{
  if(argc<=1)
    {
      std::cout<<"Please select the datalist.\n";
      exit(1);
    }
  else if(argc==2)
    {
      prepTree(argv[1]);
    }
}
