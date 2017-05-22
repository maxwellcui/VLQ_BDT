# Multivariate selection of VLQ events
- Author: Zhaoyuan "Maxwell" Cui
- Advisor: Prof. [Erich Varnes](http://w3.physics.arizona.edu/people/erich-varnes)
- Physics department, University of Arizona

## Introduction
This study leverages the TMVA tool kit of ROOT data analysis framework to enhance the search of vector-like quark (VLQ). More about VLQ can be found in the following papers:
> C. Lee and R. N. Mohapatra, J. High Energy Phys. **2017**, 80, [arXiv:1611.05478 [hep-ph]](https://arxiv.org/abs/1611.05478v1)
>
> J. A. Aguilar-Saavedra, R. Benbrik, S. Heinemeyer, and M. Perez-Victoria, Phys. Rev. D **88**, 094010 (2013), [arXiv:1306.0572 [hep-ph]](https://arxiv.org/abs/1306.0572v3)

The goal of the study is to use the multivariate analysis method (Machine Learning) to develop a new way of searhcing VLQ.
Boosted Decision Tree (BDT) is used in this study. Background and signal raw data are generated by MC simulation. 
Raw data are provided by [Sarah Jones](http://w3.physics.arizona.edu/people/sarah-jones).

## Procedure
The procedure of the study contains two parts:
1. Data preparation
1. BDT training

### Data preparation
The raw data from the simulation contain lots of infromation that is not needed in the training. At the same time, some information that one is interested, for example, b-jet, is not explicitly included. Therefore, it's necessary to extract and recombine the infromation from the raw data. Training data are generated by the code in the file `gnrTree.C`. There are two specific modifications included (tick indicates done):
- [x] b-jet calculation
- [x] normalization of event weight


Variables that are included in training data (tick indicates in-use variables in training):
- [x] `mu`
- [x] `el_pt`
- [x] `mu_pt`
- [x] `jet_pt`
- [x] `met_met`
- [x] `met_phi`
- [x] `met_sumet`
- [x] `SSee`
- [x] `SSmm`
- [x] `Sem`
- [x] `eee`
- [x] `eem`
- [x] `emm`
- [x] `mmm`
- [x] `lep_pt`
- [x] `ht`
- [x] `bj`
- [x] `evWeight`
- [ ] `jet_mv2c20` used for b-jet calculation
- [ ] `weight_mc`  used for event weight normalization

