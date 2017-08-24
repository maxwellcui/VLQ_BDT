//A ROOT macro that prepares Tree for TMVA training
//----------------------------------------------
//Author: Maxwell Cui
//Date: Aug 19, 2017
//----------------------------------------------

#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

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
  //oldTree->SetBranchStatus("weight_mc",1);

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
  vector<float>   *el_pt;
  vector<float>   *mu_pt;
  vector<float>   *jet_pt;
  vector<float>   *jet_mv2c10;
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
  vector<float>   *lep_pt;
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
	      if  (jet_mv2c10->at(ibjet) > 0.645925) {  // 77% WP
		//if (jet_mv2c10->at(ibjet) > 0.8244273) {  // 70% WP
		bjet++;
	      }
	      
      	    }
      	}
      bjetBranch->Fill();
    }

  //Working with normalization  
  //
  Float_t lumi=36.1;   

  //Declare leaf and branch
  Float_t         weight_mc;
  TBranch        *b_weight_mc;

  //Set branch addresses and brunch pointers
  oldTree->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);

  //Get the data...algrithm is from Prof. Varnes
  TH1F *lumInt=new TH1F;
  inputFile->GetObject("hIntLum",lumInt);
  Float_t mcnorm=lumInt->GetBinContent(1);
  
  //Declare variable for event weight
  Float_t evtWeight;
  TBranch *ewBranch=newTree->Branch("evtWeight",&evtWeight,"evtWeight/F");

  for(Int_t i=0;i<nentries;i++)
    {
      oldTree->GetEntry(i);
      evtWeight=weight_mc*lumi/mcnorm;
      ewBranch->Fill();
    }
    
  newTree->Print();
  newTree->Write();

  outputFile->Close();
  
  delete oldTree;
}

void prepTree()
{

  //Variable 'envName' can be the environmental variable on the system that
  //includes the path to the directory of the data files.
  //Please make sure that the variable is exported.
  
  const char* envName="MCDATA";
  std::string dataPATH=std::getenv(envName);
  
  std::ifstream inputFile("datafiles.txt");
  TString fileName;

  while(std::getline(inputFile,fileName))
    {
      std::cout<<"Readig file: "<<dataPATH+fileName<<std::endl;
      TString combine;
      combine=dataPATH+fileName;
      if(!combine)
	{
	  std::cout<<"No file: "<<combine<<std::endl;
	}
      else
	{
	  TFile *bg=new TFile(combine);
	  create(bg,fileName);
	  delete bg;
	}
    }
  inputFile.close();
}
