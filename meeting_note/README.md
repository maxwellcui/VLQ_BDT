# Meeting note
## BB_M1000 training result

![input](./BB_input_variables.png)

![signal_cor](./BB_signal_coorelation.png)

![bg_cor](./background_coorelation.png)

![classfier_output](./classfier_output_distribution.png)

![roc](./roc.png)

## TMVA training log
```shell
maxwellcui@Max-00:~/research/VLQ_BDT/training/BB$ root ../../dataPreparation/background/normalized_ttW_np1_410067_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root 
   ------------------------------------------------------------
  | Welcome to ROOT 6.06/00                http://root.cern.ch |
  |                               (c) 1995-2014, The ROOT Team |
  | Built for linuxx8664gcc                                    |
  | From tag v6-06-00, 9 December 2015                         |
  | Try '.help', '.demo', '.license', '.credits', '.quit'/'.q' |
   ------------------------------------------------------------

root [0] 
Attaching file ../../dataPreparation/background/normalized_ttW_np1_410067_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root as _file0...
(TFile *) 0x109e090
root [1] .ls
TFile**		../../dataPreparation/background/normalized_ttW_np1_410067_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root	
 TFile*		../../dataPreparation/background/normalized_ttW_np1_410067_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root	
  KEY: TTree	trainingTree;1	tree
root [2] q
input_line_45:2:3: error: use of undeclared identifier 'q'
 (q)
  ^
root [3] .q
maxwellcui@Max-00:~/research/VLQ_BDT/training/BB$ make
make: Nothing to be done for `default'.
maxwellcui@Max-00:~/research/VLQ_BDT/training/BB$ ./bdt_vlq 

==>Start BDT
--- Factory                  : Parsing option string: 
--- Factory                  : ... "V:!Silent:Color:DrawProgressBar:AnalysisType=Classification"
--- Factory                  : The following options are set:
--- Factory                  : - By User:
--- Factory                  :     V: "True" [Verbose flag]
--- Factory                  :     Color: "True" [Flag for coloured screen output (default: True, if in batch mode: False)]
--- Factory                  :     Silent: "False" [Batch mode: boolean silent flag inhibiting any output from TMVA after the creation of the factory class object (default: False)]
--- Factory                  :     DrawProgressBar: "True" [Draw progress bar to display training, testing and evaluation schedule (default: True)]
--- Factory                  :     AnalysisType: "Classification" [Set the analysis type (Classification, Regression, Multiclass, Auto) (default: Auto)]
--- Factory                  : - Default:
--- Factory                  :     Transformations: "I" [List of transformations to test; formatting example: "Transformations=I;D;P;U;G,D", for identity, decorrelation, PCA, Uniform and Gaussianisation followed by decorrelation transformations]
--- Factory                  : You are running ROOT Version: 6.06/00, Dec 9, 2015
--- Factory                  : 
--- Factory                  : _/_/_/_/_/ _|      _|  _|      _|    _|_|   
--- Factory                  :    _/      _|_|  _|_|  _|      _|  _|    _| 
--- Factory                  :   _/       _|  _|  _|  _|      _|  _|_|_|_| 
--- Factory                  :  _/        _|      _|    _|  _|    _|    _| 
--- Factory                  : _/         _|      _|      _|      _|    _| 
--- Factory                  : 
--- Factory                  : ___________TMVA Version 4.2.1, Feb 5, 2015
--- Factory                  : 
--- <FATAL> Factory                  : Tree does not exist (empty pointer).
***> abort program execution
maxwellcui@Max-00:~/research/VLQ_BDT/training/BB$ make
Building bdt_vlq ... g++ -O0 -ggdb -std=c++11  bdt_vlq.C  -I/home/maxwellcui/root/include  -L/home/maxwellcui/root/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic -lMLP -lMinuit -lTreePlayer -lTMVA -lTMVAGui -lXMLIO  -lMLP -lm  -g -o bdt_vlq
Done
maxwellcui@Max-00:~/research/VLQ_BDT/training/BB$ ./bdt_vlq 

==>Start BDT
--- Factory                  : Parsing option string: 
--- Factory                  : ... "V:!Silent:Color:DrawProgressBar:AnalysisType=Classification"
--- Factory                  : The following options are set:
--- Factory                  : - By User:
--- Factory                  :     V: "True" [Verbose flag]
--- Factory                  :     Color: "True" [Flag for coloured screen output (default: True, if in batch mode: False)]
--- Factory                  :     Silent: "False" [Batch mode: boolean silent flag inhibiting any output from TMVA after the creation of the factory class object (default: False)]
--- Factory                  :     DrawProgressBar: "True" [Draw progress bar to display training, testing and evaluation schedule (default: True)]
--- Factory                  :     AnalysisType: "Classification" [Set the analysis type (Classification, Regression, Multiclass, Auto) (default: Auto)]
--- Factory                  : - Default:
--- Factory                  :     Transformations: "I" [List of transformations to test; formatting example: "Transformations=I;D;P;U;G,D", for identity, decorrelation, PCA, Uniform and Gaussianisation followed by decorrelation transformations]
--- Factory                  : You are running ROOT Version: 6.06/00, Dec 9, 2015
--- Factory                  : 
--- Factory                  : _/_/_/_/_/ _|      _|  _|      _|    _|_|   
--- Factory                  :    _/      _|_|  _|_|  _|      _|  _|    _| 
--- Factory                  :   _/       _|  _|  _|  _|      _|  _|_|_|_| 
--- Factory                  :  _/        _|      _|    _|  _|    _|    _| 
--- Factory                  : _/         _|      _|      _|      _|    _| 
--- Factory                  : 
--- Factory                  : ___________TMVA Version 4.2.1, Feb 5, 2015
--- Factory                  : 
--- DataSetInfo              : Added class "Signal"	 with internal class number 0
--- Factory                  : Add Tree trainingTree of type Signal with 5795 events
diboson_ggllll_361073_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
diboson_ggllvv_361077_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
diboson_llll_361063_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
diboson_lllljj_EW6_361072_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
diboson_lllvjj_EW6_361071_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
diboson_lllvOFMinus_361065_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
diboson_lllvOFPlus_361067_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
diboson_lllvSFMinus_361064_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
diboson_lllvSFPlus_361066_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
diboson_llvvjj_ss_EW6_361070_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
ttbar_410000_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
ttW_np0_410066_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
ttW_np1_410067_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
ttW_np2_410068_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
ttH125_allhad_343367_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
ttH125_dil_343365_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
ttH125_inc_semil_343366_SSbkg_deterre_Apr2017_36p1ifb_25nsTOPQ1_eLHM.root
There are total 17 backgroud files.
--- DataSetInfo              : Added class "Background"	 with internal class number 1
--- Factory                  : Add Tree trainingTree of type Background with 1674 events
--- Factory                  : Add Tree trainingTree of type Background with 52 events
--- Factory                  : Add Tree trainingTree of type Background with 334 events
--- Factory                  : Add Tree trainingTree of type Background with 277 events
--- Factory                  : Add Tree trainingTree of type Background with 58 events
--- Factory                  : Add Tree trainingTree of type Background with 368 events
--- Factory                  : Add Tree trainingTree of type Background with 467 events
--- Factory                  : Add Tree trainingTree of type Background with 321 events
--- Factory                  : Add Tree trainingTree of type Background with 366 events
--- Factory                  : Add Tree trainingTree of type Background with 95 events
--- Factory                  : Add Tree trainingTree of type Background with 6740 events
--- Factory                  : Add Tree trainingTree of type Background with 23275 events
--- Factory                  : Add Tree trainingTree of type Background with 23266 events
--- Factory                  : Add Tree trainingTree of type Background with 11850 events
--- Factory                  : Add Tree trainingTree of type Background with 151 events
--- Factory                  : Add Tree trainingTree of type Background with 76887 events
--- Factory                  : Add Tree trainingTree of type Background with 36284 events
File operation done
--- DataSetInfo              : Class index : 0  name : Signal
--- DataSetInfo              : Class index : 1  name : Background
--- Factory                  : Booking method: BDT
--- DataSetFactory           : Splitmode is: "RANDOM" the mixmode is: "SAMEASSPLITMODE"
--- DataSetFactory           : Create training and testing trees -- looping over class "Signal" ...
--- DataSetFactory           : Weight expression for class 'Signal': "evtWeight"
--- DataSetFactory           : Create training and testing trees -- looping over class "Background" ...
--- DataSetFactory           : Weight expression for class 'Background': "evtWeight"
--- DataSetFactory           : Number of events in input trees (after possible flattening of arrays):
--- DataSetFactory           :     Signal          -- number of events       : 5795   / sum of weights: 17.3517
--- DataSetFactory           :     Background      -- number of events       : 182465  / sum of weights: 2697.18
--- DataSetFactory           :     Signal     tree -- total number of entries: 5795 
--- DataSetFactory           :     Background tree -- total number of entries: 182465
--- DataSetFactory           : Preselection: (will NOT affect number of requested training and testing events)
--- DataSetFactory           :     No preselection cuts applied on event classes
--- DataSetFactory           : No weight renormalisation applied: use original global and event weights
--- DataSetFactory           : Create internal training tree
--- DataSetFactory           : Create internal testing tree
--- DataSetInfo              : Correlation matrix (Signal):
--- DataSetInfo              : -------------------------------------------------------------------
--- DataSetInfo              :             jet_pt.[0] met_met lep_pt.[0]      ht met_sumet    bjet
--- DataSetInfo              : jet_pt.[0]:     +1.000  +0.219     -0.019  +0.704    +0.686  -0.048
--- DataSetInfo              :    met_met:     +0.219  +1.000     -0.087  +0.026    +0.027  +0.026
--- DataSetInfo              : lep_pt.[0]:     -0.019  -0.087     +1.000  +0.389    +0.391  -0.028
--- DataSetInfo              :         ht:     +0.704  +0.026     +0.389  +1.000    +0.979  -0.007
--- DataSetInfo              :  met_sumet:     +0.686  +0.027     +0.391  +0.979    +1.000  -0.011
--- DataSetInfo              :       bjet:     -0.048  +0.026     -0.028  -0.007    -0.011  +1.000
--- DataSetInfo              : -------------------------------------------------------------------
--- DataSetInfo              : Correlation matrix (Background):
--- DataSetInfo              : -------------------------------------------------------------------
--- DataSetInfo              :             jet_pt.[0] met_met lep_pt.[0]      ht met_sumet    bjet
--- DataSetInfo              : jet_pt.[0]:     +1.000  +0.438     +0.378  +0.853    +0.822  +0.106
--- DataSetInfo              :    met_met:     +0.438  +1.000     +0.220  +0.384    +0.384  +0.069
--- DataSetInfo              : lep_pt.[0]:     +0.378  +0.220     +1.000  +0.630    +0.614  +0.006
--- DataSetInfo              :         ht:     +0.853  +0.384     +0.630  +1.000    +0.968  +0.162
--- DataSetInfo              :  met_sumet:     +0.822  +0.384     +0.614  +0.968    +1.000  +0.133
--- DataSetInfo              :       bjet:     +0.106  +0.069     +0.006  +0.162    +0.133  +1.000
--- DataSetInfo              : -------------------------------------------------------------------
--- DataSetFactory           :  
--- Factory                  : 
--- Factory                  : current transformation string: 'I'
--- Factory                  : Create Transformation "I" with events from all classes.
--- Id                       : Transformation, Variable selection : 
--- Id                       : Input : variable 'jet_pt.[0]' (index=0).   <---> Output : variable 'jet_pt.[0]' (index=0).
--- Id                       : Input : variable 'met_met' (index=1).   <---> Output : variable 'met_met' (index=1).
--- Id                       : Input : variable 'lep_pt.[0]' (index=2).   <---> Output : variable 'lep_pt.[0]' (index=2).
--- Id                       : Input : variable 'ht' (index=3).   <---> Output : variable 'ht' (index=3).
--- Id                       : Input : variable 'met_sumet' (index=4).   <---> Output : variable 'met_sumet' (index=4).
--- Id                       : Input : variable 'bjet' (index=5).   <---> Output : variable 'bjet' (index=5).
--- Id                       : Preparing the Identity transformation...
--- TFHandler_Factory        : ---------------------------------------------------------------------
--- TFHandler_Factory        :   Variable          Mean          RMS   [        Min          Max ]
--- TFHandler_Factory        : ---------------------------------------------------------------------
--- TFHandler_Factory        : jet_pt.[0]:  1.2084e+05      98663.   [      25007.  2.0349e+06 ]
--- TFHandler_Factory        :    met_met:      74967.      57932.   [      139.36  1.6837e+06 ]
--- TFHandler_Factory        : lep_pt.[0]:  1.0458e+05      64710.   [      28117.  1.9337e+06 ]
--- TFHandler_Factory        :         ht:  4.0052e+05  2.5046e+05   [      90636.  4.5517e+06 ]
--- TFHandler_Factory        :  met_sumet:  4.9920e+05  2.6313e+05   [  1.1878e+05  4.6111e+06 ]
--- TFHandler_Factory        :       bjet:      1.3423     0.51148   [      1.0000      6.0000 ]
--- TFHandler_Factory        : ---------------------------------------------------------------------
--- TFHandler_Factory        : Plot event variables for Id
--- TFHandler_Factory        : Create scatter and profile plots in target-file directory: 
--- TFHandler_Factory        : BDT_VLQ_BB.root:/InputVariables_Id/CorrelationPlots
--- TFHandler_Factory        :  
--- TFHandler_Factory        : Ranking input variables (method unspecific)...
--- IdTransformation         : Ranking result (top variable is best ranked)
--- IdTransformation         : -----------------------------------
--- IdTransformation         : Rank : Variable   : Separation
--- IdTransformation         : -----------------------------------
--- IdTransformation         :    1 : lep_pt.[0] : 1.002e+00
--- IdTransformation         :    2 : ht         : 8.772e-01
--- IdTransformation         :    3 : met_sumet  : 8.746e-01
--- IdTransformation         :    4 : jet_pt.[0] : 7.403e-01
--- IdTransformation         :    5 : met_met    : 4.586e-01
--- IdTransformation         :    6 : bjet       : 5.036e-02
--- IdTransformation         : -----------------------------------
--- Factory                  :  
--- Factory                  : Train all methods for Classification ...
--- Factory                  : Train method: BDT for Classification
--- BDT                      : Begin training
--- BDT                      :  found and suggest the following possible pre-selection cuts 
--- BDT                      : as option DoPreselection was not used, these cuts however will not be performed, but the training will see the full sample
--- BDT                      :  found cut: Bkg if var 3 < 413438
--- BDT                      :  found cut: Bkg if var 4 < 525190
--- BDT                      :  found cut: Bkg if var 5 < 0.95
--- <WARNING> BDT                      : Events with negative event weights are USED during the BDT training. This might cause problems with small node sizes or with the boosting. Please remove negative events from training using the option *IgnoreEventsWithNegWeightsInTraining* in case you observe problems with the boosting
--- BDT                      : <InitEventSample> For classification trees, 
--- BDT                      :  the effective number of backgrounds is scaled to match 
--- BDT                      :  the signal. Othersise the first boosting step would do 'just that'!
--- BDT                      : re-normlise events such that Sig and Bkg have respective sum of weights = 1
--- BDT                      :   sig->sig*5409.42ev. bkg->bkg*34.9458ev.
--- BDT                      : #events: (reweighted) sig: 47064.5 bkg: 47064.5
--- BDT                      : #events: (unweighted) sig: 2897 bkg: 91232
--- BDT                      : Training 850 Decision Trees ... patience please
--- BinaryTree               : The minimal node size MinNodeSize=2.5 fMinNodeSize=2.5% is translated to an actual number of events = 1173.35 for the training sample size of 46934
--- BinaryTree               : Note: This number will be taken as absolute minimum in the node, 
--- BinaryTree               :       in terms of 'weighted events' and unweighted ones !! 
--- BDT                      : <Train> elapsed time: 110 sec                              
--- BDT                      : <Train> average number of nodes (w/o pruning) : 8
--- BDT                      : End of training                                              
--- BDT                      : Elapsed time for training with 94129 events: 110 sec         
--- BDT                      : Create MVA output for classification on training sample
--- BDT                      : Evaluation of BDT on training sample (94129 events)
--- BDT                      : Elapsed time for evaluation of 94129 events: 7.23 sec       
--- BDT                      : Creating weight file in xml format: weights/BDT_VLQ_BDT.weights.xml
--- BDT                      : Creating standalone response class: weights/BDT_VLQ_BDT.class.C
--- BDT                      : Write monitoring histograms to file: BDT_VLQ_BB.root:/Method_BDT/BDT
--- Factory                  : Training finished
--- Factory                  : 
--- Factory                  : Ranking input variables (method specific)...
--- BDT                      : Ranking result (top variable is best ranked)
--- BDT                      : --------------------------------------------
--- BDT                      : Rank : Variable   : Variable Importance
--- BDT                      : --------------------------------------------
--- BDT                      :    1 : lep_pt.[0] : 2.689e-01
--- BDT                      :    2 : ht         : 1.700e-01
--- BDT                      :    3 : met_sumet  : 1.676e-01
--- BDT                      :    4 : met_met    : 1.559e-01
--- BDT                      :    5 : jet_pt.[0] : 1.418e-01
--- BDT                      :    6 : bjet       : 9.579e-02
--- BDT                      : --------------------------------------------
--- Factory                  : 
--- Factory                  : === Destroy and recreate all methods via weight files for testing ===
--- Factory                  : 
--- MethodBase               : Reading weight file: weights/BDT_VLQ_BDT.weights.xml
--- BDT                      : Read method "BDT" of type "BDT"
--- BDT                      : MVA method was trained with TMVA Version: 4.2.1
--- BDT                      : MVA method was trained with ROOT Version: 6.06/00
--- Factory                  : Test all methods...
--- Factory                  : Test method: BDT for Classification performance
--- BDT                      : Evaluation of BDT on testing sample (94129 events)
--- BDT                      : Elapsed time for evaluation of 94129 events: 4.88 sec       
--- Factory                  : Evaluate all methods...
--- Factory                  : Evaluate classifier: BDT
--- BDT                      : Loop over test events and fill histograms with classifier response...
--- Factory                  : Write evaluation histograms to file
--- TFHandler_BDT            : Plot event variables for BDT
--- TFHandler_BDT            : ---------------------------------------------------------------------
--- TFHandler_BDT            :   Variable          Mean          RMS   [        Min          Max ]
--- TFHandler_BDT            : ---------------------------------------------------------------------
--- TFHandler_BDT            : jet_pt.[0]:  1.2170e+05      98500.   [      25009.  2.2160e+06 ]
--- TFHandler_BDT            :    met_met:      75877.      56282.   [      277.58  1.2994e+06 ]
--- TFHandler_BDT            : lep_pt.[0]:  1.0353e+05      61501.   [      28186.  1.3736e+06 ]
--- TFHandler_BDT            :         ht:  4.0033e+05  2.4735e+05   [      92644.  5.1556e+06 ]
--- TFHandler_BDT            :  met_sumet:  4.9630e+05  2.5967e+05   [  1.2628e+05  5.2003e+06 ]
--- TFHandler_BDT            :       bjet:      1.3556     0.51954   [      1.0000      6.0000 ]
--- TFHandler_BDT            : ---------------------------------------------------------------------
--- TFHandler_BDT            : Create scatter and profile plots in target-file directory: 
--- TFHandler_BDT            : BDT_VLQ_BB.root:/Method_BDT/BDT/CorrelationPlots
--- <WARNING> Tools                    : <GetCorrelationMatrix> zero variances for variables (0, 6)
--- <WARNING> Tools                    : <GetCorrelationMatrix> zero variances for variables (6, 0)
--- <WARNING> Tools                    : <GetCorrelationMatrix> zero variances for variables (0, 6)
--- <WARNING> Tools                    : <GetCorrelationMatrix> zero variances for variables (6, 0)
--- Factory                  : Correlations between input variables and MVA response (signal):
--- Factory                  : ----------------
--- Factory                  :                 BDT
--- Factory                  : jet_pt.[0]:  +0.363
--- Factory                  :    met_met:  +0.278
--- Factory                  : lep_pt.[0]:  +0.461
--- Factory                  :         ht:  +0.613
--- Factory                  :  met_sumet:  +0.609
--- Factory                  :       bjet:  +0.000
--- Factory                  : ----------------
--- Factory                  : 
--- Factory                  : Correlations between input variables and MVA response (background):
--- Factory                  : ----------------
--- Factory                  :                 BDT
--- Factory                  : jet_pt.[0]:  +0.764
--- Factory                  :    met_met:  +0.576
--- Factory                  : lep_pt.[0]:  +0.605
--- Factory                  :         ht:  +0.890
--- Factory                  :  met_sumet:  +0.888
--- Factory                  :       bjet:  +0.000
--- Factory                  : ----------------
--- Factory                  : 
--- Factory                  : The following "overlap" matrices contain the fraction of events for which 
--- Factory                  : the MVAs 'i' and 'j' have returned conform answers about "signal-likeness"
--- Factory                  : An event is signal-like, if its MVA output exceeds the following value:
--- Factory                  : --------------------
--- Factory                  :  Method:  Cut value:
--- Factory                  : --------------------
--- Factory                  :     BDT:     -0.081
--- Factory                  : --------------------
--- Factory                  : which correspond to the working point: eff(signal) = 1 - eff(background)
--- Factory                  : 
--- Factory                  : Evaluation results ranked by best signal efficiency and purity (area)
--- Factory                  : --------------------------------------------------------------------------------
--- Factory                  : MVA              Signal efficiency at bkg eff.(error):       | Sepa-    Signifi- 
--- Factory                  : Method:          @B=0.01    @B=0.10    @B=0.30    ROC-integ. | ration:  cance:   
--- Factory                  : --------------------------------------------------------------------------------
--- Factory                  : BDT            : 0.818(131)  0.995(23)  1.000(07)    0.993    | 0.900    3.518
--- Factory                  : --------------------------------------------------------------------------------
--- Factory                  : 
--- Factory                  : Testing efficiency compared to training efficiency (overtraining check)
--- Factory                  : --------------------------------------------------------------------------------
--- Factory                  : MVA              Signal efficiency: from test sample (from training sample) 
--- Factory                  : Method:          @B=0.01             @B=0.10            @B=0.30   
--- Factory                  : --------------------------------------------------------------------------------
--- Factory                  : BDT            : 0.818 (0.813)       0.995 (0.996)      1.000 (1.000)
--- Factory                  : --------------------------------------------------------------------------------
--- Factory                  : 
--- Dataset:Default          : Created tree 'TestTree' with 94129 events
--- Dataset:Default          : Created tree 'TrainTree' with 94129 events
--- Factory                  :   
--- Factory                  : Thank you for using TMVA!
--- Factory                  : For citation information, please visit: http://tmva.sf.net/citeTMVA.html
==> Wrote root file: BDT_VLQ_BB.root
==> TMVAClassification is done!
--- Launch TMVA GUI to view input file: BDT_VLQ_BB.root
=== Note: inactive buttons indicate classifiers that were not trained, ===
===       or functionalities that were not invoked during the training ===
```
