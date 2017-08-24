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
  oldTree->SetBranchStatus("SSee",1);
  oldTree->SetBranchStatus("SSmm",1);
  oldTree->SetBranchStatus("SSem",1);
  oldTree->SetBranchStatus("eee",1);
  oldTree->SetBranchStatus("eem",1);
  oldTree->SetBranchStatus("emm",1);
  oldTree->SetBranchStatus("mmm",1);
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
  Int_t           SSee;
  Int_t           SSmm;
  Int_t           SSem;
  Int_t           eee;
  Int_t           eem;
  Int_t           emm;
  Int_t           mmm;
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
  TBranch        *b_SSee;   //!
  TBranch        *b_SSmm;   //!
  TBranch        *b_SSem;   //!
  TBranch        *b_eee;   //!
  TBranch        *b_eem;   //!
  TBranch        *b_emm;   //!
  TBranch        *b_mmm;   //!
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
  oldTree->SetBranchAddress("SSee", &SSee, &b_SSee);
  oldTree->SetBranchAddress("SSmm", &SSmm, &b_SSmm);
  oldTree->SetBranchAddress("SSem", &SSem, &b_SSem);
  oldTree->SetBranchAddress("eee", &eee, &b_eee);
  oldTree->SetBranchAddress("eem", &eem, &b_eem);
  oldTree->SetBranchAddress("emm", &emm, &b_emm);
  oldTree->SetBranchAddress("mmm", &mmm, &b_mmm);
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
      bj=0;
      if(SSee || SSem || SSmm || eee || eem || emm || mmm)
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
      std::string combine;
      comnine=dataPATH+fileName;
      TFile *bg=new TFile(combine);
      create(bg,fileName);
      delete bg;
    }
  inputFile.close();
}
