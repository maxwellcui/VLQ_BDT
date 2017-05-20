//This is the ROOT program that will take in the 
//root file, extract some specific entries, and 
//calculate the bjet, then recombing it to the new root file.
//User should modify the path and name of the file to meet his or her own concern.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Author: Maxwell Cui
//Date: 11.15.2016
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void gnr(TFile* inputFile,TString outputName)
{
  TTree *oldTree=new TTree;
  inputFile->GetObject("nominal_Loose",oldTree);
  
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
  oldTree->SetBranchStatus("jet_mv2c20",1);
  oldTree->SetBranchStatus("weight_mc",1);

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
  vector<float>   *jet_mv2c20;
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
  TBranch        *b_jet_mv2c20;   //!
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
  jet_mv2c20 = 0;
  lep_pt = 0;
  
  //Set branch addresses and brunch pointers
  oldTree->SetBranchAddress("mu", &mu, &b_mu);
  oldTree->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
  oldTree->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
  oldTree->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
  oldTree->SetBranchAddress("jet_mv2c20", &jet_mv2c20, &b_jet_mv2c20);
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
  Int_t bj;

  //Add new branch
  TBranch *bjBranch=newTree->Branch("bj",&bj,"bj/I");

  Int_t nentries=(Int_t)oldTree->GetEntries();

  //Calculate bjet, algorithm is from SelOpt.C
  for(Int_t i=0;i<nentries;i++)
    {
      oldTree->GetEntry(i);
      //cout<<SSee<<endl;
      bj=0;
      if(SSee || SSem || SSmm || eee || eem || emm || mmm)
      	{
      	  for(unsigned int ibjet=0;ibjet<jet_mv2c20->size();ibjet++)
      	    {
      	      if(jet_mv2c20->at(ibjet)>-0.4434) //don't know why is this. //It's actually from some other ML result
      		{
      		  bj++;
      		}
	      
      	    }
      	}
      bjBranch->Fill();
    }

  //Working with normalization  
  //
  float lumi=30;   //Number is from Prof. Varnes

  //Declare leaf and branch
  Float_t         weight_mc;
  TBranch        *b_weight_mc;   //!

  //Set branch addresses and brunch pointers
  oldTree->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);

  TH1F *lumInt=new TH1F;
  inputFile->GetObject("hIntLum",lumInt);
  
  float mcnorm=lumInt->GetBinContent(1);
  
  //Declare variable for event weight
  Float_t evtWeight;
  TBranch *ewBranch=newTree->Branch("evtWeight",&evtWeight,"evtWeight/F");

  for(Int_t i=0;i<nentries;i++)
    {
      oldTree->GetEntry(i);
      //evtWeight=0;
      evtWeight=weight_mc*lumi/mcnorm;
      ewBranch->Fill();
    }

  //------------------
  newTree->Print();
  outputFile->Write();

  delete oldTree;
  delete lumInt;
  delete outputFile;
}

void gnrTree()
{

  //=========================Input file===========================================
  //Signal
  TFile *s1=new TFile("../data/signal/BBS_M800_302490_sig_2016_25nsTOPQ1.root");
  //----------
  //Background
  TFile *b1=new TFile("../data/background/ttW_np0_410066_bkg_2016_25nsTOPQ1.root");
  TFile *b2=new TFile("../data/background/ttW_np1_410067_bkg_2016_25nsTOPQ1.root");
  TFile *b3=new TFile("../data/background/ttW_np2_410068_bkg_2016_25nsTOPQ1.root");
  TFile *b4=new TFile("../data/background/ttH.root"); 
  TFile *b5=new TFile("../data/background/VV.root"); 
  TFile *b6=new TFile("../data/background/VVV.root"); 
  //==============================================================================

  gnr(s1,"BBS_sig.root");
  delete s1;

  gnr(b1,"ttW_np0_bkg.root");
  delete b1;

  gnr(b2,"ttW_np1_bkg.root");
  delete b2;

  gnr(b3,"ttW_np2_bkg.root");
  delete b3; 

  gnr(b4,"ttH.root");
  delete b4;

  gnr(b5,"VV.root");
  delete b5;
 
  gnr(b6,"VVV.root");
  delete b6;


}
