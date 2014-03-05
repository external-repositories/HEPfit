/* 
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef INPUTPARAMETERS_H
#define	INPUTPARAMETERS_H

class InputParameters {
public:
    
    InputParameters()
    {};
    
    virtual ~InputParameters()
    {};
    
    std::map<std::string, double> getInputParameters(std::string& ModelName)
    {
        if (ModelName.compare("StandardModel") == 0) return(StandardModel());
        if (ModelName.compare("NPEpsilons") == 0) return(NPEpsilons());
        if (ModelName.compare("NPEpsilons_pureNP") == 0) return(NPEpsilons_pureNP());
        if (ModelName.compare("NPSTU") == 0) return(NPSTU());
        if (ModelName.compare("NPHiggs") == 0) return(NPHiggs());
        if (ModelName.compare("NPZbbbar") == 0) return(NPZbbbar());
        if (ModelName.compare("NPEffective1") == 0) return(NPEffective1());
        if (ModelName.compare("NPEffective2") == 0) return(NPEffective2());
        else throw std::runtime_error("\nERROR: Incorrect model name passed to InputParameters():  " + ModelName + "\n");
    };
    
private:
    
    std::map<std::string, double> StandardModel()
    {
        DPars_IN["GF"] = 1.1663787e-5;
        DPars_IN["ale"] = 7.2973525698e-3;
        DPars_IN["AlsMz"] = 0.1184;
        DPars_IN["dAle5Mz"] = 0.02750;
        DPars_IN["Mz"] = 91.1875;
        DPars_IN["mtop"] = 173.2;
        DPars_IN["mHl"] = 125.6;
        DPars_IN["delMw"] = 0.;
        DPars_IN["delSin2th_l"] = 0.;
        DPars_IN["delGammaZ"] = 0.;
        DPars_IN["mup"] = 0.0023;
        DPars_IN["mdown"] = 0.0048;
        DPars_IN["mstrange"] = 0.095;
        DPars_IN["mcharm"] = 1.275;
        DPars_IN["mbottom"] = 4.18;
        DPars_IN["muc"] = 1.275;
        DPars_IN["mub"] = 4.18;
        DPars_IN["mut"] = 164.;
        DPars_IN["mneutrino_1"] = 0.;
        DPars_IN["mneutrino_2"] = 0.;
        DPars_IN["mneutrino_3"] = 0.;
        DPars_IN["melectron"] = 5.109989e-4;
        DPars_IN["mmu"] = 0.10565837;
        DPars_IN["mtau"] = 1.77682;
        DPars_IN["MBd"] = 0.;
        DPars_IN["tBd"] = 0.;
        DPars_IN["MBs"] = 0.;
        DPars_IN["tBs"] = 0.;
        DPars_IN["MBp"] = 0.;
        DPars_IN["MK0"] = 0.;
        DPars_IN["MKp"] = 0.;
        DPars_IN["FK"] = 0.;
        DPars_IN["FBs"] = 0.;
        DPars_IN["FBsoFBd"] = 0.;
        DPars_IN["BBsoBBd"] = 0.;
        DPars_IN["BBs1"] = 0.;
        DPars_IN["BBs2"] = 0.;
        DPars_IN["BBs3"] = 0.;
        DPars_IN["BBs4"] = 0.;
        DPars_IN["BBs5"] = 0.;
        DPars_IN["BBsscale"] = 0.;
        DPars_IN["BBsscheme"] = 0.;
        DPars_IN["lambda"] = 0.;
        DPars_IN["A"] = 0.;
        DPars_IN["rhob"] = 0.;
        DPars_IN["etab"] = 0.;
        DPars_IN["muw"] = 0.;
        DPars_IN["phiEpsK"] = 0.;
        DPars_IN["KbarEpsK"] = 0.;
        DPars_IN["DeltaMK"] = 0.;
        DPars_IN["Dmk"] = 0.;
        DPars_IN["SM_M12D"] = 0.;
        DPars_IN["MD"] = 0.;
        DPars_IN["FD"] = 0.;
        DPars_IN["BD1"] = 0.;
        DPars_IN["BD2"] = 0.;
        DPars_IN["BD3"] = 0.;
        DPars_IN["BD4"] = 0.;
        DPars_IN["BD5"] = 0.;
        DPars_IN["BDscale"] = 0.;
        DPars_IN["BDscheme"] = 0.;
        DPars_IN["BK1"] = 0.;
        DPars_IN["BK2"] = 0.;
        DPars_IN["BK3"] = 0.;
        DPars_IN["BK4"] = 0.;
        DPars_IN["BK5"] = 0.;
        DPars_IN["BKscale"] = 0.;
        DPars_IN["BKscheme"] = 0.;
        DPars_IN["EpsK"] = 0.;
        DPars_IN["BK(1/2)1"] = 0.;
        DPars_IN["BK(1/2)2"] = 0.;
        DPars_IN["BK(1/2)3"] = 0.;
        DPars_IN["BK(1/2)4"] = 0.;
        DPars_IN["BK(1/2)5"] = 0.;
        DPars_IN["BK(1/2)6"] = 0.;
        DPars_IN["BK(1/2)7"] = 0.;
        DPars_IN["BK(1/2)8"] = 0.;
        DPars_IN["BK(1/2)9"] = 0.;
        DPars_IN["BK(1/2)10"] = 0.;
        DPars_IN["BKd_scale"] = 0.;
        DPars_IN["BKd_scheme"] = 0.;
        DPars_IN["BK(3/2)1"] = 0.;
        DPars_IN["BK(3/2)2"] = 0.;
        DPars_IN["BK(3/2)3"] = 0.;
        DPars_IN["BK(3/2)4"] = 0.;
        DPars_IN["BK(3/2)5"] = 0.;
        DPars_IN["BK(3/2)6"] = 0.;
        DPars_IN["BK(3/2)7"] = 0.;
        DPars_IN["BK(3/2)8"] = 0.;
        DPars_IN["BK(3/2)9"] = 0.;
        DPars_IN["BK(3/2)10"] = 0.;
        DPars_IN["ReA2_Kd"] = 0.;
        DPars_IN["ReA0_Kd"] = 0.;
        DPars_IN["Omega_eta_etap"] = 0.;
        DPars_IN["Br_Kp_P0enu"] = 0.;
        DPars_IN["Br_Kp_munu"] = 0.;
        DPars_IN["Br_B_Xcenu"] = 0.;
        DPars_IN["DeltaP_cu"] = 0.;
        DPars_IN["IB_Kl"] = 0.;
        DPars_IN["IB_Kp"] = 0.;
        DPars_IN["tKl"] = 0.;
        DPars_IN["tKp"] = 0.;
        
        return (DPars_IN);
    };
    
    std::map<std::string, double> NPEpsilons()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["epsilon_1"] = 0.;
        DPars_IN["epsilon_2"] = 0.;
        DPars_IN["epsilon_3"] = 0.;
        DPars_IN["epsilon_b"] = 0.;
        
        return (DPars_IN);
    };
    
    std::map<std::string, double> NPEpsilons_pureNP()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["delEps_1"] = 0.;
        DPars_IN["delEps_2"] = 0.;
        DPars_IN["delEps_3"] = 0.;
        DPars_IN["delEps_b"] = 0.;
        
        return (DPars_IN);
    };
    
    std::map<std::string, double> NPSTU()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["obliqueS"] = 0.;
        DPars_IN["obliqueT"] = 0.;
        DPars_IN["obliqueU"] = 0.;
        
        return (DPars_IN);
    };
    
    std::map<std::string, double> NPHiggs()
    {
        DPars_IN = StandardModel();
                
        DPars_IN["a"] = 0.;
        DPars_IN["b"] = 0.;
        DPars_IN["c_u"] = 0.;
        DPars_IN["c_d"] = 0.;
        DPars_IN["c_e"] = 0.;
        DPars_IN["d_3"] = 0.;
        DPars_IN["d_4"] = 0.;
        DPars_IN["LambdaNP"] = 0.;
        
        return (DPars_IN);
    };
    
    std::map<std::string, double> NPZbbbar()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["deltaGVb"] = 0.;
        DPars_IN["deltaGAb"] = 0.;
        
        return (DPars_IN);
    };
    
    std::map<std::string, double> NPEffective1()
    {
        DPars_IN = StandardModel();
                        
        DPars_IN["cWB_NP"] = 0.;
        DPars_IN["cH_NP"] = 0.;
        DPars_IN["cLL_NP"] = 0.;
        DPars_IN["cHLp_NP"] = 0.;
        DPars_IN["cHQp_NP"] = 0.;
        DPars_IN["cHL_NP"] = 0.;
        DPars_IN["cHQ_NP"] = 0.;
        DPars_IN["cHE_NP"] = 0.;
        DPars_IN["cHU_NP"] = 0.;
        DPars_IN["cHD_NP"] = 0.;
        DPars_IN["Lambda_NP"] = 0.;
        
        return (DPars_IN);
    };
    
    std::map<std::string, double> NPEffective2()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["cWB_NP"] = 0.;
        DPars_IN["cH_NP"] = 0.;
        DPars_IN["cLL_NP"] = 0.;
        DPars_IN["cHLp_NP"] = 0.;
        DPars_IN["cHQ1p_NP"] = 0.;
        DPars_IN["cHQ2p_NP"] = 0.;
        DPars_IN["cHQ3p_NP"] = 0.;
        DPars_IN["cHL_NP"] = 0.;
        DPars_IN["cHQ1_NP"] = 0.;
        DPars_IN["cHQ2_NP"] = 0.;
        DPars_IN["cHQ3_NP"] = 0.;
        DPars_IN["cHE_NP"] = 0.;
        DPars_IN["cHU1_NP"] = 0.;
        DPars_IN["cHU2_NP"] = 0.;
        DPars_IN["cHU3_NP"] = 0.;
        DPars_IN["cHD1_NP"] = 0.;
        DPars_IN["cHD2_NP"] = 0.;
        DPars_IN["cHD3_NP"] = 0.;
        DPars_IN["Lambda_NP"] = 0.;
        
        return (DPars_IN);
    };
    
    std::map<std::string, double> DPars_IN;
};

#endif	/* INPUTPARAMETERS_H */
    