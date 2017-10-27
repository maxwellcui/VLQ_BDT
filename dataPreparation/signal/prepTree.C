//A ROOT macro that prepares Tree for TMVA training
//----------------------------------------------
//Author: Maxwell Cui
//Created date: Aug 19, 2017
//Latest modified: Sep 25, 2017
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
  oldTree->SetBranchStatus("ht",1);
  oldTree->SetBranchStatus("met_met",1);
  oldTree->SetBranchStatus("met_sumet",1);
  oldTree->SetBranchStatus("mu_pt",1);
  oldTree->SetBranchStatus("el_pt",1);
  oldTree->SetBranchStatus("mu",1);
  oldTree->SetBranchStatus("jet_pt",1);
  oldTree->SetBranchStatus("met_phi",1);
  oldTree->SetBranchStatus("SSee_2016",1);
  oldTree->SetBranchStatus("SSmm_2016",1);
  oldTree->SetBranchStatus("SSem_2016",1);
  oldTree->SetBranchStatus("eee_2016",1);
  oldTree->SetBranchStatus("eem_2016",1);
  oldTree->SetBranchStatus("emm_2016",1);
  oldTree->SetBranchStatus("mmm_2016",1);
  oldTree->SetBranchStatus("lep_pt",1);
  oldTree->SetBranchStatus("jet_mv2c10",1);   //Using MV2c10 for b-tagging

  oldTree->SetBranchStatus("weight_mc",1);
  oldTree->SetBranchStatus("weight_jvt",1);
  oldTree->SetBranchStatus("weight_leptonSF_tightLeps",1);
  oldTree->SetBranchStatus("weight_indiv_SF_MU_TTVA",1);
  oldTree->SetBranchStatus("weight_pileup",1);
  oldTree->SetBranchStatus("weight_bTagSF_77",1);

  //====================Output file==========================
  //
  TFile *outputFile=new TFile(outputName,"recreate");
  //  
  //=========================================================
 
 //Copy to new tree
  TTree *newTree=oldTree->CloneTree();

  //Working with b-jet
  //
  // Declaration of leaf types
  Float_t         mu;
  std::vector<float>   *el_pt;
  std::vector<float>   *mu_pt;
  std::vector<float>   *jet_pt;
  std::vector<float>   *jet_mv2c10;
  Float_t         met_met;
  Float_t         met_phi;
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
  TBranch        *b_mu;   //!
  TBranch        *b_el_pt;   //!
  TBranch        *b_mu_pt;   //!
  TBranch        *b_jet_pt;   //!
  TBranch        *b_jet_mv2c10;   //!
  TBranch        *b_met_met;   //!
  TBranch        *b_met_sumet;
  TBranch        *b_met_phi;   //!
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
  el_pt = 0;
  mu_pt = 0;
  jet_pt = 0;
  jet_mv2c10 = 0;
  lep_pt = 0;
  
  //Set branch addresses and brunch pointers
  oldTree->SetBranchAddress("mu", &mu, &b_mu);
  oldTree->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
  oldTree->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
  oldTree->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
  oldTree->SetBranchAddress("jet_mv2c10", &jet_mv2c10, &b_jet_mv2c10);
  oldTree->SetBranchAddress("met_met", &met_met, &b_met_met);
  oldTree->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
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


  //Declare bjet variable
  Int_t bjet;

  //Add new branch
  TBranch *bjetBranch=newTree->Branch("bjet",&bjet,"bjet/I");

  //Get the number of events
  Int_t nentries=(Int_t)oldTree->GetEntries();

  //Calculate bjet, algorithm is provided by Prof. Varnes
  for(Int_t i=0;i<nentries;i++)
    {
      oldTree->GetEntry(i);
      bjet=0;
      if(SSee_2016 || SSem_2016 || SSmm_2016 || eee_2016 || eem_2016 || emm_2016 || mmm_2016)
      	{
      	  for(unsigned int ibjet=0;ibjet<jet_mv2c10->size();ibjet++)
      	    {
      	      ///     if  (jet_mv2c10->at(ibjet) > 0.1758475) {  // 85% WP 
	      if  (jet_mv2c10->at(ibjet) > 0.645925) 
		{  // 77% WP
		  //if (jet_mv2c10->at(ibjet) > 0.8244273) {  // 70% WP
		bjet++;
		}      
      	    }
	  bjetBranch->Fill();
	}
    }
  
  //Working with normalization  
  //
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
  //Float_t globalWeight;
  TBranch *evtBranch=newTree->Branch("evtWeight",&evtWeight,"evtWeight/F");
  //TBranch *gblBranch=newTree->Branch("globalWeight",&globalWeight,"globalWeight/F");
  //globalWeight=0;

  std::cout<<"mcnorm is: "<<mcnorm<<std::endl;

  for(Int_t j=0;j<nentries;j++)
    {
      oldTree->GetEntry(j);

      //Calculate event weight
      evtWeight=weight_mc*weight_jvt*(weight_leptonSF_tightLeps/weight_indiv_SF_MU_TTVA)*weight_pileup*weight_bTagSF_77*lumi/mcnorm;
      
      //std::cout<<std::endl;
      // std::cout<<"The weight_jvt is: "<<weight_jvt<<std::endl;
      // std::cout<<"The weight_mc is: "<<weight_mc<<std::endl;
      // std::cout<<"The weight_pileup is: "<<weight_pileup<<std::endl;
      // std::cout<<"The weight_indiv_SF_MU_TTVA is: "<<weight_indiv_SF_MU_TTVA<<std::endl;
      // std::cout<<"The weight_bTagSF_77 is: "<<weight_bTagSF_77<<std::endl;
      // std::cout<<"The weight_leptonSF_tightLeps is: "<<weight_leptonSF_tightLeps<<std::endl;
      //std::cout<<"The event weight is: "<<evtWeight<<std::endl;
      //globalWeight+=evtWeight;
      evtBranch->Fill();
    }
  //gblBranch->Fill();
  newTree->Fill();
  newTree->Print();
  newTree->Write();

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
      TString fullInput;
      fullInput=dataPATH+"signals/"+fileName;
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
