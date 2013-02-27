/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <cmath>
#include "EWSM.h"
#include <iostream>


const double EWSM::Mw_error = 0.00001; /* 0.01 MeV */ 


EWSM::EWSM(const StandardModel& SM_i) 
: SM(SM_i) 
{
    flag_order[EW1] = true;
    flag_order[EW1QCD1] = true;
    flag_order[EW1QCD2] = true;
    flag_order[EW2] = true;
    flag_order[EW2QCD1] = true;
    flag_order[EW3] = true;

    bUseCacheEWSM = true;// use caches in the current class
    //bUseCacheEWSM = false;// do not use caches in the current class (for test)
    
    //std::string Model = SM.ModelName();
    //std::cout << "Model in EWSM: " << Model << std::endl;
 
    myCache = new EWSMcache(SM);
    myOneLoopEW = new EWSMOneLoopEW(*myCache);
    myTwoLoopQCD = new EWSMTwoLoopQCD(*myCache);
    myThreeLoopQCD = new EWSMThreeLoopQCD(*myCache);
    myTwoLoopEW = new EWSMTwoLoopEW(*myCache);
    myThreeLoopEW2QCD = new EWSMThreeLoopEW2QCD(*myCache);
    myThreeLoopEW = new EWSMThreeLoopEW(*myCache);
    myApproximateFormulae = new EWSMApproximateFormulae(SM);   

    myTwoFermionsLEP2 = new EWSMTwoFermionsLEP2(SM);

    // Initializations of the caches
    DeltaAlphaLepton_cache = 0.0;
    DeltaAlpha_cache = 0.0;
    Mw_cache = 0.0;
    GammaW_cache = 0.0;
    R0b_cache = 0.0;
    int i, j;
    for (j=0; j<NumSMParams; ++j) {
        DeltaAlphaLepton_params_cache[j] = 0.0;
        DeltaAlpha_params_cache[j] = 0.0;
        Mw_params_cache[j] = 0.0;
        GammaW_params_cache[j] = 0.0;
        R0b_params_cache[j] = 0.0;
    }
    for (i=0; i<6; ++i) {
        rhoZ_l_cache[i] = complex(0.0, 0.0, false);
        rhoZ_q_cache[i] = complex(0.0, 0.0, false);
        kappaZ_l_cache[i] = complex(0.0, 0.0, false);
        kappaZ_q_cache[i] = complex(0.0, 0.0, false);
        for (j=0; j<NumSMParams; ++j) {
            rhoZ_l_params_cache[i][j] = 0.0;
            rhoZ_q_params_cache[i][j] = 0.0;
            kappaZ_l_params_cache[i][j] = 0.0;
            kappaZ_q_params_cache[i][j] = 0.0;
        }
    }
}


////////////////////////////////////////////////////////////////////////

bool EWSM::checkSMparams(double Params_cache[]) const 
{
    // 11 parameters in QCD:
    // "AlsMz","Mz","mup","mdown","mcharm","mstrange", "mtop","mbottom",
    // "mut","mub","muc"
    // 10 parameters in StandardModel
    // "GF", "ale", "dAle5Mz", "mHl", 
    // "mneutrino_1", "mneutrino_2", "mneutrino_3", "melectron", "mmu", "mtau",
    // "delMw", "delSin2th_l"
    double SMparams[NumSMParams] = { 
        SM.getAlsMz(), SM.getMz(), SM.getGF(), SM.getAle(), SM.getDAle5Mz(),
        SM.getMHl(), SM.getMtpole(), 
        SM.getLeptons(SM.NEUTRINO_1).getMass(), 
        SM.getLeptons(SM.NEUTRINO_2).getMass(),
        SM.getLeptons(SM.NEUTRINO_3).getMass(),
        SM.getLeptons(SM.ELECTRON).getMass(),
        SM.getLeptons(SM.MU).getMass(),
        SM.getLeptons(SM.TAU).getMass(),
        SM.getQuarks(SM.UP).getMass(),
        SM.getQuarks(SM.DOWN).getMass(),
        SM.getQuarks(SM.CHARM).getMass(),
        SM.getQuarks(SM.STRANGE).getMass(),
        SM.getQuarks(SM.BOTTOM).getMass(),
        SM.getMut(), SM.getMub(), SM.getMuc(),
        SM.getDelMw(), SM.getDelSin2th_l()
    };
        
    // check updated parameters
    bool bCache = true;
    for(int i=0; i<NumSMParams; ++i) {
        if (Params_cache[i] != SMparams[i]) { 
            Params_cache[i] = SMparams[i];                 
            bCache &= false;
        }
    }
    
    return bCache;
}


////////////////////////////////////////////////////////////////////////

double EWSM::DeltaAlphaLepton(const double s) const 
{
    if (s==SM.getMz()*SM.getMz())
        if (bUseCacheEWSM)
            if (checkSMparams(DeltaAlphaLepton_params_cache))
                return DeltaAlphaLepton_cache;
    
    double DeltaAlphaL = 0.0;
    if (flag_order[EW1]) 
        DeltaAlphaL += myOneLoopEW->DeltaAlpha_l(s);
    if (flag_order[EW1QCD1]) 
        DeltaAlphaL += myTwoLoopQCD->DeltaAlpha_l(s);
    if (flag_order[EW1QCD2]) 
        DeltaAlphaL += myThreeLoopQCD->DeltaAlpha_l(s);
    if (flag_order[EW2]) 
        DeltaAlphaL += myTwoLoopEW->DeltaAlpha_l(s);
    if (flag_order[EW2QCD1]) 
        DeltaAlphaL += myThreeLoopEW2QCD->DeltaAlpha_l(s);
    if (flag_order[EW3]) 
        DeltaAlphaL += myThreeLoopEW->DeltaAlpha_l(s);

    if (s==SM.getMz()*SM.getMz())
        DeltaAlphaLepton_cache = DeltaAlphaL;
    return DeltaAlphaL;
}


double EWSM::DeltaAlphaL5q() const 
{
    double Mz2 = SM.getMz()*SM.getMz();    
    return (DeltaAlphaLepton(Mz2) + SM.getDAle5Mz());
}


double EWSM::DeltaAlphaTop(const double s) const 
{
    double DeltaAlpha = 0.0;
    if (flag_order[EW1]) 
        DeltaAlpha += myOneLoopEW->DeltaAlpha_t(s);
    if (flag_order[EW1QCD1]) 
        DeltaAlpha += myTwoLoopQCD->DeltaAlpha_t(s);
    if (flag_order[EW1QCD2]) 
        DeltaAlpha += myThreeLoopQCD->DeltaAlpha_t(s);
    if (flag_order[EW2]) 
        DeltaAlpha += myTwoLoopEW->DeltaAlpha_t(s);
    if (flag_order[EW2QCD1]) 
        DeltaAlpha += myThreeLoopEW2QCD->DeltaAlpha_t(s);
    if (flag_order[EW3]) 
        DeltaAlpha += myThreeLoopEW->DeltaAlpha_t(s);

    return DeltaAlpha; 
}


double EWSM::DeltaAlpha() const 
{
    if (bUseCacheEWSM)
        if (checkSMparams(DeltaAlpha_params_cache))
            return DeltaAlpha_cache;
    
    double Mz2 = SM.getMz()*SM.getMz();
    DeltaAlpha_cache = DeltaAlphaL5q() + DeltaAlphaTop(Mz2);
    return DeltaAlpha_cache; 
}


double EWSM::alphaMz() const 
{
    return (SM.getAle()/(1.0 - DeltaAlpha()));
}


////////////////////////////////////////////////////////////////////////

double EWSM::Mw_SM() const 
{    
    if (bUseCacheEWSM)       
        if (checkSMparams(Mw_params_cache))
            return Mw_cache;

    double Mw;
    if (schemeMw==APPROXIMATEFORMULA)
        Mw = myApproximateFormulae->Mw(DeltaAlphaL5q());
    else {
        //std::cout << std::setprecision(12) 
        //          << "TEST: Mw_tree = " << SM.Mw_tree() << std::endl;
        
        double DeltaRho[orders_EW_size], DeltaR_rem[orders_EW_size];
        ComputeDeltaRho(SM.Mw_tree(), DeltaRho);
        ComputeDeltaR_rem(SM.Mw_tree(), DeltaR_rem);
        Mw = resumMw(SM.Mw_tree(), DeltaRho, DeltaR_rem);
        
        /* Mw from iterations */
        double Mw_org = SM.Mw_tree();
        while (fabs(Mw - Mw_org) > Mw_error) {
            Mw_org = Mw;
            ComputeDeltaRho(Mw, DeltaRho);
            ComputeDeltaR_rem(Mw, DeltaR_rem);
            Mw = resumMw(Mw, DeltaRho, DeltaR_rem);
            /* TEST */
            //int prec_def = std::cout.precision();
            //std::cout << std::setprecision(12) << "TEST: Mw_org = " << Mw_org 
            //        << "  Mw_new = " << Mw << std::endl;
            //std::cout.precision(prec_def);
        }
    } 
    
    Mw_cache = Mw;
    return Mw;
}


double EWSM::DeltaR_SM() const 
{
    double Mw = Mw_SM();
    double sW2 = 1.0 - Mw*Mw/SM.getMz()/SM.getMz();
    double tmp = sqrt(2.0)*SM.getGF()*sW2*Mw*Mw/M_PI/SM.getAle();
    if (schemeMw==NORESUM || schemeMw==APPROXIMATEFORMULA) {
        return (tmp - 1.0);
    } else {
        return (1.0 - 1.0/tmp);
    }
}


double EWSM::cW2_SM() const 
{
    double Mw = Mw_SM();
    return ( Mw*Mw/SM.getMz()/SM.getMz() );
}


double EWSM::sW2_SM() const 
{
    return ( 1.0 - cW2_SM() );
}


complex EWSM::rhoZ_l_SM(const StandardModel::lepton l) const 
{    
    if (schemeRhoZ==APPROXIMATEFORMULA)
        throw std::runtime_error("No approximate formula is available for rhoZ^f"); 
    else {

        if (bUseCacheEWSM)        
            if (checkSMparams(rhoZ_l_params_cache[(int)l]))
                return rhoZ_l_cache[(int)l];
        
        double Mw = Mw_SM();
        
        /* compute Delta rho */
        double DeltaRho[orders_EW_size];
        ComputeDeltaRho(Mw, DeltaRho);
        
        /* compute delta rho_rem^f */
        complex deltaRho_rem_f[orders_EW_size];
        deltaRho_rem_f[EW1] = complex(0.0, 0.0, false);        
        deltaRho_rem_f[EW1QCD1] = complex(0.0, 0.0, false);
        deltaRho_rem_f[EW1QCD2] = complex(0.0, 0.0, false);        
        deltaRho_rem_f[EW2] = complex(0.0, 0.0, false);       
        deltaRho_rem_f[EW2QCD1] = complex(0.0, 0.0, false);
        deltaRho_rem_f[EW3] = complex(0.0, 0.0, false);    
        if (flag_order[EW1]) 
            deltaRho_rem_f[EW1] = myOneLoopEW->deltaRho_rem_l(l,Mw);
        if (flag_order[EW1QCD1]) 
            deltaRho_rem_f[EW1QCD1] = complex(myTwoLoopQCD->deltaRho_rem_l(l,Mw).real(), 0.0, false);
        if (flag_order[EW1QCD2]) 
            deltaRho_rem_f[EW1QCD2] = complex(myThreeLoopQCD->deltaRho_rem_l(l,Mw).real(), 0.0, false);
        if (flag_order[EW2]) 
            deltaRho_rem_f[EW2] = complex(myTwoLoopEW->deltaRho_rem_l(l,Mw).real(), 0.0, false);
        if (flag_order[EW2QCD1]) 
            deltaRho_rem_f[EW2QCD1] = complex(myThreeLoopEW2QCD->deltaRho_rem_l(l,Mw).real(), 0.0, false);
        if (flag_order[EW3]) 
            deltaRho_rem_f[EW3] = complex(myThreeLoopEW->deltaRho_rem_l(l,Mw).real(), 0.0, false);  
        
        /* compute Delta rbar_rem */
        double DeltaRbar_rem = 0.0;
        if (flag_order[EW1])
            DeltaRbar_rem = myOneLoopEW->DeltaRbar_rem(Mw);    
        
        /* Re[rho_Z^f] with or without resummation */
        double deltaRho_rem_f_real[orders_EW_size];
        for (int j=0; j<orders_EW_size; ++j)
            deltaRho_rem_f_real[j] = deltaRho_rem_f[j].real();
        double ReRhoZf = resumRhoZ(DeltaRho, deltaRho_rem_f_real, 
                                   DeltaRbar_rem, false);
        
        /* Im[rho_Z^f] without resummation */
        double ImRhoZf = 0.0;
        for (int j=0; j<orders_EW_size; ++j)
            ImRhoZf += deltaRho_rem_f[j].imag();    
        
        rhoZ_l_cache[(int)l] = complex(ReRhoZf, ImRhoZf, false);
        return (complex(ReRhoZf, ImRhoZf, false));    
    }
}


complex EWSM::rhoZ_q_SM(const StandardModel::quark q) const 
{    
    if (q==StandardModel::TOP) return (complex(0.0, 0.0, false));
    if (schemeRhoZ==APPROXIMATEFORMULA)
        throw std::runtime_error("No approximate formula is available for rhoZ^f"); 
    else {

        if (bUseCacheEWSM)        
            if (checkSMparams(rhoZ_q_params_cache[(int)q]))
                return rhoZ_q_cache[(int)q];
        
        double Mw = Mw_SM();
        
        /* compute Delta rho */
        double DeltaRho[orders_EW_size];
        ComputeDeltaRho(Mw, DeltaRho);
        
        /* compute delta rho_rem^f */
        complex deltaRho_rem_f[orders_EW_size];
        deltaRho_rem_f[EW1] = complex(0.0, 0.0, false); 
        deltaRho_rem_f[EW1QCD1] = complex(0.0, 0.0, false); 
        deltaRho_rem_f[EW1QCD2] = complex(0.0, 0.0, false); 
        deltaRho_rem_f[EW2] = complex(0.0, 0.0, false); 
        deltaRho_rem_f[EW2QCD1] = complex(0.0, 0.0, false); 
        deltaRho_rem_f[EW3] = complex(0.0, 0.0, false); 
        if (flag_order[EW1]) 
            deltaRho_rem_f[EW1] = myOneLoopEW->deltaRho_rem_q(q,Mw);
        if (flag_order[EW1QCD1]) 
            deltaRho_rem_f[EW1QCD1] = complex(myTwoLoopQCD->deltaRho_rem_q(q,Mw).real(), 0.0, false);
        if (flag_order[EW1QCD2]) 
            deltaRho_rem_f[EW1QCD2] = complex(myThreeLoopQCD->deltaRho_rem_q(q,Mw).real(), 0.0, false);
        if (flag_order[EW2]) 
            deltaRho_rem_f[EW2] = complex(myTwoLoopEW->deltaRho_rem_q(q,Mw).real(), 0.0, false);
        if (flag_order[EW2QCD1]) 
            deltaRho_rem_f[EW2QCD1] = complex(myThreeLoopEW2QCD->deltaRho_rem_q(q,Mw).real(), 0.0, false);
        if (flag_order[EW3]) 
            deltaRho_rem_f[EW3] = complex(myThreeLoopEW->deltaRho_rem_q(q,Mw).real(), 0.0, false);  
        
        /* compute Delta rbar_rem */
        double DeltaRbar_rem = 0.0;
        if (flag_order[EW1])
            DeltaRbar_rem = myOneLoopEW->DeltaRbar_rem(Mw);    
        
        /* Re[rho_Z^f] with or without resummation */
        double deltaRho_rem_f_real[orders_EW_size];
        for (int j=0; j<orders_EW_size; ++j)
            deltaRho_rem_f_real[j] = deltaRho_rem_f[j].real();
        bool bool_Zbb = false;
        if (q==StandardModel::BOTTOM) bool_Zbb = true;
        double ReRhoZf = resumRhoZ(DeltaRho, deltaRho_rem_f_real, 
                                   DeltaRbar_rem, bool_Zbb);
        
        /* Im[rho_Z^f] without resummation */
        double ImRhoZf = 0.0;
        for (int j=0; j<orders_EW_size; ++j)
            ImRhoZf += deltaRho_rem_f[j].imag();    
        if (q==StandardModel::BOTTOM)
            ImRhoZf *= pow(1.0 + taub(), 2.0);/* Corrections to the Z-b-bbar vertex */ 
        
        rhoZ_q_cache[(int)q] = complex(ReRhoZf, ImRhoZf, false);
        return (complex(ReRhoZf, ImRhoZf, false));    
    }
}


complex EWSM::kappaZ_l_SM(const StandardModel::lepton l) const 
{

    if (bUseCacheEWSM)    
        if (checkSMparams(kappaZ_l_params_cache[(int)l]))
            return kappaZ_l_cache[(int)l];

    double Mw = Mw_SM();
    
    double ReKappaZf = 0.0, ImKappaZf = 0.0;
    if (schemeKappaZ==APPROXIMATEFORMULA) {
        ReKappaZf = myApproximateFormulae->sin2thetaEff_l(l, DeltaAlphaL5q())/sW2_SM(); 
        ImKappaZf = myOneLoopEW->deltaKappa_rem_l(l,Mw).imag();
        
        /* TEST */
        //ImKappaZf -= SM.getAle()*SM.getAlsMz()/24.0/M_PI*(cW2_SM() - sW2_SM())/sW2_SM()/sW2_SM();        
    } else {
        /* compute Delta rho */
        double DeltaRho[orders_EW_size];
        ComputeDeltaRho(Mw, DeltaRho);
        
        /* compute delta kappa_rem^f */
        complex deltaKappa_rem_f[orders_EW_size];
        deltaKappa_rem_f[EW1] = complex(0.0, 0.0, false); 
        deltaKappa_rem_f[EW1QCD1] = complex(0.0, 0.0, false); 
        deltaKappa_rem_f[EW1QCD2] = complex(0.0, 0.0, false); 
        deltaKappa_rem_f[EW2] = complex(0.0, 0.0, false); 
        deltaKappa_rem_f[EW2QCD1] = complex(0.0, 0.0, false);         
        deltaKappa_rem_f[EW3] = complex(0.0, 0.0, false); 
        if (flag_order[EW1]) 
            deltaKappa_rem_f[EW1] = myOneLoopEW->deltaKappa_rem_l(l,Mw);
        if (flag_order[EW1QCD1]) 
            deltaKappa_rem_f[EW1QCD1] = complex(myTwoLoopQCD->deltaKappa_rem_l(l,Mw).real(), 0.0, false);
        if (flag_order[EW1QCD2]) 
            deltaKappa_rem_f[EW1QCD2] = complex(myThreeLoopQCD->deltaKappa_rem_l(l,Mw).real(), 0.0, false);
        if (flag_order[EW2]) 
            deltaKappa_rem_f[EW2] = complex(myTwoLoopEW->deltaKappa_rem_l(l,Mw).real(), 0.0, false);
        if (flag_order[EW2QCD1]) 
            deltaKappa_rem_f[EW2QCD1] = complex(myThreeLoopEW2QCD->deltaKappa_rem_l(l,Mw).real(), 0.0, false);
        if (flag_order[EW3]) 
            deltaKappa_rem_f[EW3] = complex(myThreeLoopEW->deltaKappa_rem_l(l,Mw).real(), 0.0, false);   
    
        /* compute Delta rbar_rem */
        double DeltaRbar_rem = 0.0;
        if (flag_order[EW1])
            DeltaRbar_rem = myOneLoopEW->DeltaRbar_rem(Mw);    
        
        /* Re[kappa_Z^f] with or without resummation */
        double deltaKappa_rem_f_real[orders_EW_size];
        for (int j=0; j<orders_EW_size; ++j)
            deltaKappa_rem_f_real[j] = deltaKappa_rem_f[j].real();
        ReKappaZf = resumKappaZ(DeltaRho, deltaKappa_rem_f_real, 
                                DeltaRbar_rem, false);
        
        /* O(alpha^2) correction to Re[kappa_Z^f] from the Z-gamma mixing */
        ReKappaZf += 35.0*alphaMz()*alphaMz()/18.0/sW2_SM()
                *(1.0 - 8.0/3.0*ReKappaZf*sW2_SM());
    
        /* Im[kappa_Z^f] without resummation */
        for (int j=0; j<orders_EW_size; ++j)
            ImKappaZf += deltaKappa_rem_f[j].imag();   
    }
        
    kappaZ_l_cache[(int)l] = complex(ReKappaZf, ImKappaZf, false);
    return (complex(ReKappaZf, ImKappaZf, false));       
}


complex EWSM::kappaZ_q_SM(const StandardModel::quark q) const 
{
    if (q==StandardModel::TOP) return (complex(0.0, 0.0, false));
    
    if (bUseCacheEWSM)     
        if (checkSMparams(kappaZ_q_params_cache[(int)q]))
            return kappaZ_q_cache[(int)q];

    double Mw = Mw_SM();
    
    double ReKappaZf = 0.0,  ImKappaZf = 0.0;    
    if (schemeKappaZ==APPROXIMATEFORMULA) {
        ReKappaZf = myApproximateFormulae->sin2thetaEff_q(q, DeltaAlphaL5q())/sW2_SM(); 
        ImKappaZf = myOneLoopEW->deltaKappa_rem_q(q,Mw).imag();

        /* TEST */
        //ImKappaZf -= SM.getAle()*SM.getAlsMz()/24.0/M_PI*(cW2_SM() - sW2_SM())/sW2_SM()/sW2_SM();        
    } else { 
        /* compute Delta rho */
        double DeltaRho[orders_EW_size];
        ComputeDeltaRho(Mw, DeltaRho); 

        /* compute delta kappa_rem^f */        
        complex deltaKappa_rem_f[orders_EW_size];
        deltaKappa_rem_f[EW1] = complex(0.0, 0.0, false);
        deltaKappa_rem_f[EW1QCD1] = complex(0.0, 0.0, false);
        deltaKappa_rem_f[EW1QCD2] = complex(0.0, 0.0, false);
        deltaKappa_rem_f[EW2] = complex(0.0, 0.0, false);
        deltaKappa_rem_f[EW2QCD1] = complex(0.0, 0.0, false);
        deltaKappa_rem_f[EW3] = complex(0.0, 0.0, false);
        if (flag_order[EW1]) 
            deltaKappa_rem_f[EW1] = myOneLoopEW->deltaKappa_rem_q(q,Mw);
        if (flag_order[EW1QCD1]) 
            deltaKappa_rem_f[EW1QCD1] = complex(myTwoLoopQCD->deltaKappa_rem_q(q,Mw).real(), 0.0, false);
        if (flag_order[EW1QCD2]) 
            deltaKappa_rem_f[EW1QCD2] = complex(myThreeLoopQCD->deltaKappa_rem_q(q,Mw).real(), 0.0, false);
        if (flag_order[EW2]) 
            deltaKappa_rem_f[EW2] = complex(myTwoLoopEW->deltaKappa_rem_q(q,Mw).real(), 0.0, false);
        if (flag_order[EW2QCD1]) 
            deltaKappa_rem_f[EW2QCD1] = complex(myThreeLoopEW2QCD->deltaKappa_rem_q(q,Mw).real(), 0.0, false);
        if (flag_order[EW3]) 
            deltaKappa_rem_f[EW3] = complex(myThreeLoopEW->deltaKappa_rem_q(q,Mw).real(), 0.0, false);   
    
        /* compute Delta rbar_rem */
        double DeltaRbar_rem = 0.0;
        if (flag_order[EW1])
            DeltaRbar_rem = myOneLoopEW->DeltaRbar_rem(Mw);    
    
        /* Re[kappa_Z^f] with or without resummation */
        double deltaKappa_rem_f_real[orders_EW_size];
        for (int j=0; j<orders_EW_size; ++j)
            deltaKappa_rem_f_real[j] = deltaKappa_rem_f[j].real();
        bool bool_Zbb = false;
        if (q==StandardModel::BOTTOM) bool_Zbb = true;
        ReKappaZf = resumKappaZ(DeltaRho, deltaKappa_rem_f_real, 
                                DeltaRbar_rem, bool_Zbb);
        
        /* O(alpha^2) correction to Re[kappa_Z^f] from the Z-gamma mixing */
        ReKappaZf += 35.0*alphaMz()*alphaMz()/18.0/sW2_SM()
                *(1.0 - 8.0/3.0*ReKappaZf*sW2_SM());
    
        /* Im[kappa_Z^f] without resummation */
        for (int j=0; j<orders_EW_size; ++j)
            ImKappaZf += deltaKappa_rem_f[j].imag();    
    }
        
    if (q==StandardModel::BOTTOM)
        ImKappaZf /= (1.0 + taub());/* Corrections to the Z-b-bbar vertex */ 
    
    kappaZ_q_cache[(int)q] = complex(ReKappaZf, ImKappaZf, false);
    return (complex(ReKappaZf, ImKappaZf, false));       
}


complex EWSM::gVl_SM(const StandardModel::lepton l) const 
{
    return ( gAl_SM(l)
             *(1.0 - 4.0*fabs(myCache->Ql(l))*kappaZ_l_SM(l)*sW2_SM()) );
}


complex EWSM::gVq_SM(const StandardModel::quark q) const 
{
    if (q==StandardModel::TOP) return (complex(0.0, 0.0, false));
    return ( gAq_SM(q)
             *(1.0 - 4.0*fabs(myCache->Qq(q))*kappaZ_q_SM(q)*sW2_SM()) );
}


complex EWSM::gAl_SM(const StandardModel::lepton l) const 
{
    return ( sqrt(rhoZ_l_SM(l))*SM.getLeptons(l).getIsospin() );
}


complex EWSM::gAq_SM(const StandardModel::quark q) const 
{
    if (q==StandardModel::TOP) return (complex(0.0, 0.0, false));
    return ( sqrt(rhoZ_q_SM(q))*SM.getQuarks(q).getIsospin() );
}


double EWSM::rho_GammaW_l_SM(const StandardModel::lepton li, 
                             const StandardModel::lepton lj) const 
{
    double Mw = Mw_SM();
    double rhoW = 0.0;
    if (flag_order[EW1])
        rhoW = myOneLoopEW->rho_GammaW_l(li,lj,Mw);    
    return rhoW;
}


double EWSM::rho_GammaW_q_SM(const StandardModel::quark qi, 
                             const StandardModel::quark qj) const 
{
    double Mw = Mw_SM();
    double rhoW = 0.0;
    if (flag_order[EW1])
        rhoW = myOneLoopEW->rho_GammaW_q(qi,qj,Mw);    
    return rhoW;
}


double EWSM::GammaW_l_SM(const StandardModel::lepton li, 
                         const StandardModel::lepton lj) const 
{
    if ( ((int)li+2)%2 || ((int)lj+3)%2 ) 
        throw std::runtime_error("Error in EWSM::GammaW_l_SM()"); 
    
    double G0 = SM.getGF()*pow(Mw_SM(),3.0)/6.0/sqrt(2.0)/M_PI;    
    complex V(0.0, 0.0, false);
    if ( (li==StandardModel::NEUTRINO_1 && lj==StandardModel::ELECTRON) ||
         (li==StandardModel::NEUTRINO_2 && lj==StandardModel::MU) ||
         (li==StandardModel::NEUTRINO_3 && lj==StandardModel::TAU) )        
        V.real() = 1.0;
    return ( V.abs2()*G0*rho_GammaW_l_SM(li,lj) ); 
}
    
    
double EWSM::GammaW_q_SM(const StandardModel::quark qi, 
                         const StandardModel::quark qj) const 
{
    if ( ((int)qi+2)%2 || ((int)qj+3)%2 ) 
        throw std::runtime_error("Error in EWSM::GammaW_q_SM()"); 
    
    double G0 = SM.getGF()*pow(Mw_SM(),3.0)/6.0/sqrt(2.0)/M_PI;    
    complex V(0.0, 0.0, false);
    
    if ( qi==StandardModel::UP && qj==StandardModel::DOWN )
        V = SM.getCKM().V_ud();
    else if ( qi==StandardModel::UP && qj==StandardModel::STRANGE )
        V = SM.getCKM().V_us();
    else if ( qi==StandardModel::UP && qj==StandardModel::BOTTOM )
        V = SM.getCKM().V_ub();
    else if ( qi==StandardModel::CHARM && qj==StandardModel::DOWN )
        V = SM.getCKM().V_cd();
    else if ( qi==StandardModel::CHARM && qj==StandardModel::STRANGE )
        V = SM.getCKM().V_cs();
    else if ( qi==StandardModel::CHARM && qj==StandardModel::BOTTOM )
        V = SM.getCKM().V_cb();
    else if ( qi==StandardModel::TOP || qj==StandardModel::TOP) 
        return (0.0);
    double AlsMw = SM.Als(Mw_SM(), 5.0, SM.getAlsMz(), SM.getMz(), FULLNLO); 
    return ( 3.0*V.abs2()*G0*rho_GammaW_q_SM(qi,qj)*(1.0 + AlsMw/M_PI) );    
}


double EWSM::GammaW_SM() const 
{
    if (bUseCacheEWSM)      
        if (checkSMparams(GammaW_params_cache))
            return GammaW_cache;
    
    double GammaW = GammaW_l_SM(SM.NEUTRINO_1, SM.ELECTRON) 
                    + GammaW_l_SM(SM.NEUTRINO_2, SM.MU) 
                    + GammaW_l_SM(SM.NEUTRINO_3, SM.TAU)             
                    + GammaW_q_SM(SM.UP, SM.DOWN) 
                    + GammaW_q_SM(SM.UP, SM.STRANGE) 
                    + GammaW_q_SM(SM.UP, SM.BOTTOM) 
                    + GammaW_q_SM(SM.CHARM, SM.DOWN)
                    + GammaW_q_SM(SM.CHARM, SM.STRANGE) 
                    + GammaW_q_SM(SM.CHARM, SM.BOTTOM);
    GammaW_cache = GammaW;
    return GammaW;
}


double EWSM::R0_bottom_SM() const 
{
    if (!SM.IsFlagR0bApproximate())
        throw std::runtime_error("Error in EWSM::R0_bottom_SM()"); 

    if (bUseCacheEWSM)      
        if (checkSMparams(R0b_params_cache))
            return R0b_cache;

    double Rb = myApproximateFormulae->R0_bottom(DeltaAlphaL5q());
    R0b_cache = Rb;
    return Rb;
}


double EWSM::taub() const 
{
    double taub_tmp = 0.0;
    double Xt = myCache->Xt_GF();
    if (flag_order[EW1]) 
        taub_tmp += -2.0*Xt; 
    if (flag_order[EW1QCD1]) 
        taub_tmp += 2.0/3.0*M_PI*Xt*myCache->alsMt(); 
    if (flag_order[EW1QCD2]) 
        taub_tmp += 0.0;
    if (flag_order[EW2]) 
        taub_tmp += -2.0*Xt*Xt*myTwoLoopEW->tau_2();
    if (flag_order[EW2QCD1]) 
        taub_tmp += 0.0;
    if (flag_order[EW3]) 
        taub_tmp += 0.0;
    
    return taub_tmp;
}


////////////////////////////////////////////////////////////////////////  

complex EWSM::rhoZ_l_SM_FlavorDep(const StandardModel::lepton l) const 
{
    double Mz = SM.getMz(); 
    double Mw = Mw_SM();
    double cW2 = Mw*Mw/Mz/Mz, sW2 = 1.0 - cW2;
    StandardModel::lepton ELE = SM.ELECTRON;
    complex ul = ( 3.0*myCache->vl(ELE,Mw)*myCache->vl(ELE,Mw) 
                   + myCache->al(ELE)*myCache->al(ELE) )/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                 + myOneLoopEW->FW_l(Mz*Mz,ELE,Mw);
    complex uf = ( 3.0*myCache->vl(l,Mw)*myCache->vl(l,Mw) 
                   + myCache->al(l)*myCache->al(l) )/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                 + myOneLoopEW->FW_l(Mz*Mz,l,Mw);
    
    complex dRho = 2.0*(uf - ul);
    dRho *= SM.getAle()/4.0/M_PI/sW2;
    return dRho; 
}


complex EWSM::rhoZ_q_SM_FlavorDep(StandardModel::quark q) const 
{
    if (q==StandardModel::TOP) return (complex(0.0, 0.0, false));

    /* In the case of BOTTOM, the top contribution has to be subtracted.
     * The remaining contribution is the same as that for DOWN and STRANGE. */
    if (q==StandardModel::BOTTOM) q=StandardModel::DOWN;

    double Mz = SM.getMz(); 
    double Mw = Mw_SM();
    double cW2 = Mw*Mw/Mz/Mz, sW2 = 1.0 - cW2;
    StandardModel::lepton ELE = SM.ELECTRON;
    complex ul = ( 3.0*myCache->vl(ELE,Mw)*myCache->vl(ELE,Mw) 
                   + myCache->al(ELE)*myCache->al(ELE) )/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                 + myOneLoopEW->FW_l(Mz*Mz,ELE,Mw);
    complex uf = ( 3.0*myCache->vq(q,Mw)*myCache->vq(q,Mw) 
                   + myCache->aq(q)*myCache->aq(q) )/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                 + myOneLoopEW->FW_q(Mz*Mz,q,Mw);
    
    complex dRho = 2.0*(uf - ul);
    dRho *= SM.getAle()/4.0/M_PI/sW2;
    return dRho; 
}


complex EWSM::kappaZ_l_SM_FlavorDep(const StandardModel::lepton l) const 
{
    double Mz = SM.getMz(); 
    double Mw = Mw_SM();
    double cW2 = Mw*Mw/Mz/Mz, sW2 = 1.0 - cW2;
    StandardModel::lepton ELE = SM.ELECTRON;
    complex ul = ( 3.0*myCache->vl(ELE,Mw)*myCache->vl(ELE,Mw) 
                   + myCache->al(ELE)*myCache->al(ELE) )/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                 + myOneLoopEW->FW_l(Mz*Mz,ELE,Mw);
    double deltal = myCache->deltal(ELE, Mw);
    complex uf = ( 3.0*myCache->vl(l,Mw)*myCache->vl(l,Mw) 
                   + myCache->al(l)*myCache->al(l) )/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                 + myOneLoopEW->FW_l(Mz*Mz,l,Mw);
    double deltaf = myCache->deltal(l, Mw);
    
    complex dKappa = (deltaf*deltaf - deltal*deltal)/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                     - uf + ul;
    dKappa *= SM.getAle()/4.0/M_PI/sW2;
    return dKappa;
}


complex EWSM::kappaZ_q_SM_FlavorDep(StandardModel::quark q) const 
{
    if (q==StandardModel::TOP) return (complex(0.0, 0.0, false));

    /* In the case of BOTTOM, the top contribution has to be subtracted.
     * The remaining contribution is the same as that for DOWN and STRANGE. */
    if (q==StandardModel::BOTTOM) q=StandardModel::DOWN;
    
    double Mz = SM.getMz(); 
    double Mw = Mw_SM();
    double cW2 = Mw*Mw/Mz/Mz, sW2 = 1.0 - cW2;
    StandardModel::lepton ELE = SM.ELECTRON;
    complex ul = ( 3.0*myCache->vl(ELE,Mw)*myCache->vl(ELE,Mw) 
                   + myCache->al(ELE)*myCache->al(ELE) )/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                 + myOneLoopEW->FW_l(Mz*Mz,ELE,Mw);
    double deltal = myCache->deltal(ELE, Mw);
    complex uf = ( 3.0*myCache->vq(q,Mw)*myCache->vq(q,Mw) 
                   + myCache->aq(q)*myCache->aq(q) )/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                 + myOneLoopEW->FW_q(Mz*Mz,q,Mw);
    double deltaf = myCache->deltaq(q, Mw);
    
    complex dKappa = (deltaf*deltaf - deltal*deltal)/4.0/cW2*myOneLoopEW->FZ(Mz*Mz,Mw) 
                     - uf + ul;
    dKappa *= SM.getAle()/4.0/M_PI/sW2;
    return dKappa; 
}
    
    
////////////////////////////////////////////////////////////////////////     

void EWSM::ComputeDeltaRho(const double Mw_i,
                           double DeltaRho[orders_EW_size]) const 
{
    if (flag_order[EW1]) 
        DeltaRho[EW1] = myOneLoopEW->DeltaRho(Mw_i);
    else
        DeltaRho[EW1] = 0.0;
    if (flag_order[EW1QCD1]) 
        DeltaRho[EW1QCD1] = myTwoLoopQCD->DeltaRho(Mw_i);
    else
        DeltaRho[EW1QCD1] = 0.0;
    if (flag_order[EW1QCD2]) 
        DeltaRho[EW1QCD2] = myThreeLoopQCD->DeltaRho(Mw_i);
    else
        DeltaRho[EW1QCD2] = 0.0;
    if (flag_order[EW2]) 
        DeltaRho[EW2] = myTwoLoopEW->DeltaRho(Mw_i);
    else
        DeltaRho[EW2] = 0.0;
    if (flag_order[EW2QCD1]) 
        DeltaRho[EW2QCD1] = myThreeLoopEW2QCD->DeltaRho(Mw_i);
    else
        DeltaRho[EW2QCD1] = 0.0;
    if (flag_order[EW3]) 
        DeltaRho[EW3] = myThreeLoopEW->DeltaRho(Mw_i);  
    else
        DeltaRho[EW3] = 0.0;
}    


void EWSM::ComputeDeltaR_rem(const double Mw_i,
                             double DeltaR_rem[orders_EW_size]) const 
{    
    if (flag_order[EW1]) 
        DeltaR_rem[EW1] = myOneLoopEW->DeltaR_rem(Mw_i);
    else 
        DeltaR_rem[EW1] = 0.0;
    if (flag_order[EW1QCD1]) 
        DeltaR_rem[EW1QCD1] = myTwoLoopQCD->DeltaR_rem(Mw_i);
    else 
        DeltaR_rem[EW1QCD1] = 0.0;
    if (flag_order[EW1QCD2]) 
        DeltaR_rem[EW1QCD2] = myThreeLoopQCD->DeltaR_rem(Mw_i);
    else 
        DeltaR_rem[EW1QCD2] = 0.0;
    if (flag_order[EW2]) 
        DeltaR_rem[EW2] = myTwoLoopEW->DeltaR_rem(Mw_i);
    else 
        DeltaR_rem[EW2] = 0.0;
    if (flag_order[EW2QCD1]) 
        DeltaR_rem[EW2QCD1] = myThreeLoopEW2QCD->DeltaR_rem(Mw_i);
    else 
        DeltaR_rem[EW2QCD1] = 0.0;
    if (flag_order[EW3]) 
        DeltaR_rem[EW3] = myThreeLoopEW->DeltaR_rem(Mw_i);    
    else 
        DeltaR_rem[EW3] = 0.0;
}   


double EWSM::resumMw(const double Mw_i, const double DeltaRho[orders_EW_size],
                     const double DeltaR_rem[orders_EW_size]) const
{
    if ( (schemeMw==APPROXIMATEFORMULA) 
            || (DeltaR_rem[EW2QCD1]!=0.0) 
            || (DeltaR_rem[EW3]!=0.0) )
        throw std::runtime_error("Error in EWSM::resumMw()"); 

    double cW2_TMP = Mw_i*Mw_i/SM.getMz()/SM.getMz();
    double sW2_TMP = 1.0 - cW2_TMP;
    
    double f_AlphaToGF, DeltaRho_sum = 0.0, DeltaRho_G;
    if (schemeMw==NORESUM) {
        for (int j=0; j<orders_EW_size; ++j)
            DeltaRho_sum += DeltaRho[(orders_EW)j];
    } else {
        // conversion: alpha(0) --> G_F
        f_AlphaToGF = sqrt(2.0)*SM.getGF()*pow(SM.getMz(),2.0)*sW2_TMP*cW2_TMP/M_PI/SM.getAle();
        DeltaRho_sum = f_AlphaToGF*DeltaRho[EW1]
                       + f_AlphaToGF*DeltaRho[EW1QCD1]
                       + f_AlphaToGF*DeltaRho[EW1QCD2]                
                       + pow(f_AlphaToGF,2.0)*DeltaRho[EW2]
                       + pow(f_AlphaToGF,2.0)*DeltaRho[EW2QCD1]
                       + pow(f_AlphaToGF,3.0)*DeltaRho[EW3];
        DeltaRho_G = f_AlphaToGF*DeltaRho[EW1];
    }
        
    double R;
    double DeltaR_rem_sum = 0.0;
    switch (schemeMw) {
        case NORESUM:
            for (int j=0; j<orders_EW_size; ++j)
                DeltaR_rem_sum += DeltaR_rem[(orders_EW)j];
            
            // R = 1 + Delta r
            R = 1.0 + DeltaAlphaL5q() - cW2_TMP/sW2_TMP*DeltaRho_sum
                + DeltaR_rem_sum;
            break;
        case OMSI:
            // R = 1/(1 - Delta r)
            R = 1.0/(1.0 + cW2_TMP/sW2_TMP*DeltaRho_sum)
                /(1.0 - DeltaAlphaL5q()
                  - DeltaR_rem[EW1] - DeltaR_rem[EW1QCD1] - DeltaR_rem[EW2]);
            break;
        case INTERMEDIATE:
            // R = 1/(1 - Delta r)
            R = 1.0/( (1.0 + cW2_TMP/sW2_TMP*DeltaRho_sum)
                      *(1.0 - DeltaAlphaL5q() - DeltaR_rem[EW1]) 
                        - DeltaR_rem[EW1QCD1] - DeltaR_rem[EW2] );
            break;        
        case OMSII:
            // R = 1/(1 - Delta r)
            R = 1.0/( (1.0 + cW2_TMP/sW2_TMP*DeltaRho_sum)*(1.0 - DeltaAlphaL5q())
                      - (1.0 + cW2_TMP/sW2_TMP*DeltaRho_G)*DeltaR_rem[EW1]
                      - DeltaR_rem[EW1QCD1] - DeltaR_rem[EW2] );
            break;
        default:
            throw std::runtime_error("Error in EWSM::resumMw()");             
    }   

    double tmp = 4.0*M_PI*SM.getAle()/sqrt(2.0)/SM.getGF()/SM.getMz()/SM.getMz();
    if (tmp*R > 1.0) throw std::runtime_error("Negative (1-tmp*R) in EWSM::resumMw()"); 
    
    return (SM.getMz()/sqrt(2.0) * sqrt(1.0 + sqrt(1.0 - tmp*R)));
}


double EWSM::resumRhoZ(const double DeltaRho[orders_EW_size],
                       const double deltaRho_rem[orders_EW_size],
                       const double DeltaRbar_rem, const bool bool_Zbb) const 
{
    if ( (schemeRhoZ==APPROXIMATEFORMULA) 
            || (deltaRho_rem[EW1QCD2]!=0.0) 
            || (deltaRho_rem[EW2QCD1]!=0.0) 
            || (deltaRho_rem[EW3]!=0.0) )
        throw std::runtime_error("Error in EWSM::resumRhoZ()");   

    double Mw_TMP = Mw_SM();
    double cW2_TMP = cW2_SM();
    double sW2_TMP = sW2_SM();
    
    double f_AlphaToGF, DeltaRho_sum = 0.0, DeltaRho_G, deltaRho_rem_sum=0.0;
    double DeltaRbar_rem_G, deltaRho_rem_G, deltaRho_rem_G2;
    if (schemeRhoZ==NORESUM && !bool_Zbb) {
        for (int j=0; j<EWSM::orders_EW_size; ++j) { 
            DeltaRho_sum += DeltaRho[j];
            deltaRho_rem_sum += deltaRho_rem[j];
        }
    } else {
        // conversion: alpha(0) --> G_F
        f_AlphaToGF = sqrt(2.0)*SM.getGF()*pow(SM.getMz(),2.0)
                      *sW2_TMP*cW2_TMP/M_PI/SM.getAle();
        DeltaRho_sum = f_AlphaToGF*DeltaRho[EW1]
                       + f_AlphaToGF*DeltaRho[EW1QCD1]
                       + f_AlphaToGF*DeltaRho[EW1QCD2]
                       + pow(f_AlphaToGF,2.0)*DeltaRho[EW2]
                       + pow(f_AlphaToGF,2.0)*DeltaRho[EW2QCD1]
                       + pow(f_AlphaToGF,3.0)*DeltaRho[EW3];
        DeltaRho_G = f_AlphaToGF*DeltaRho[EW1];
        DeltaRbar_rem_G = f_AlphaToGF*DeltaRbar_rem;
        deltaRho_rem_G = f_AlphaToGF*(deltaRho_rem[EW1] 
                                      + deltaRho_rem[EW1QCD1]);
        deltaRho_rem_G2 = pow(f_AlphaToGF,2.0)*deltaRho_rem[EW2];
    }
    
    /* Real parts */
    double rhoZ;
    if (!bool_Zbb) {
        switch (schemeRhoZ) {
            case NORESUM: 
                rhoZ = 1.0 + DeltaRho_sum + deltaRho_rem_sum;
                break;
            case OMSI:
                rhoZ = (1.0 + deltaRho_rem_G + deltaRho_rem_G2)
                        /(1.0 - DeltaRho_sum*(1.0 - DeltaRbar_rem_G));
                break;
            case INTERMEDIATE:
                rhoZ = (1.0 + deltaRho_rem_G)
                        /(1.0 - DeltaRho_sum*(1.0 - DeltaRbar_rem_G))
                        + deltaRho_rem_G2;            
                break;        
            case OMSII:
                rhoZ = 1.0 + DeltaRho_sum + pow(DeltaRho_G, 2.0) 
                        - DeltaRho_G*DeltaRbar_rem_G
                        + deltaRho_rem_G*(1.0 + DeltaRho_G) + deltaRho_rem_G2;  
                break;
            default:
                throw std::runtime_error("Error in EWSM::resumRhoZ()"); 
        }
    } else { 
        double rhoZbL = pow(1.0+taub(),2.0)/(1.0 - DeltaRho_sum);
        deltaRho_rem_G += myCache->ale()/4.0/M_PI/sW2_TMP*pow(myCache->Mt()/Mw_TMP, 2.0);        
        switch (schemeRhoZ) {
            case NORESUM: 
                rhoZ = (1.0 + DeltaRho_sum + deltaRho_rem_G)*pow(1.0+taub(),2.0);
                break;
            case OMSI:
                rhoZ = rhoZbL/(1.0 - rhoZbL*deltaRho_rem_G);
                break;
            case INTERMEDIATE:
                rhoZ = rhoZbL*(1.0 + rhoZbL*deltaRho_rem_G);
                break;
            case OMSII:
                rhoZ = rhoZbL*(1.0 + deltaRho_rem_G);
                break;
            default:
                throw std::runtime_error("Error in EWSM::resumRhoZ()");         
        }
    }
    
    return rhoZ;
}


double EWSM::resumKappaZ(const double DeltaRho[orders_EW_size],
                         const double deltaKappa_rem[orders_EW_size],
                         const double DeltaRbar_rem, const bool bool_Zbb) const 
{
    if ( (schemeKappaZ==APPROXIMATEFORMULA)
            || (deltaKappa_rem[EW2QCD1]!=0.0)
            || (deltaKappa_rem[EW3]!=0.0) )
        throw std::runtime_error("Error in EWSM::resumKappaZ()");      

    double Mw_TMP = Mw_SM();
    double cW2_TMP = cW2_SM();
    double sW2_TMP = sW2_SM();
    
    double f_AlphaToGF, DeltaRho_sum = 0.0, DeltaRho_G, deltaKappa_rem_sum=0.0;
    double DeltaRbar_rem_G, deltaKappa_rem_G, deltaKappa_rem_G2;
    if (schemeKappaZ==NORESUM && !bool_Zbb) {
        for (int j=0; j<EWSM::orders_EW_size; ++j) { 
            DeltaRho_sum += DeltaRho[j];
            deltaKappa_rem_sum += deltaKappa_rem[j];
        }
    } else {
        // conversion: alpha(0) --> G_F
        f_AlphaToGF = sqrt(2.0)*SM.getGF()*pow(SM.getMz(),2.0)
                      *sW2_TMP*cW2_TMP/M_PI/SM.getAle();
        DeltaRho_sum = f_AlphaToGF*DeltaRho[EW1]
                       + f_AlphaToGF*DeltaRho[EW1QCD1]
                       + f_AlphaToGF*DeltaRho[EW1QCD2]
                       + pow(f_AlphaToGF,2.0)*DeltaRho[EW2]
                       + pow(f_AlphaToGF,2.0)*DeltaRho[EW2QCD1]
                       + pow(f_AlphaToGF,3.0)*DeltaRho[EW3];
        DeltaRho_G = f_AlphaToGF*DeltaRho[EW1];
        DeltaRbar_rem_G = f_AlphaToGF*DeltaRbar_rem;
        deltaKappa_rem_G = f_AlphaToGF*(deltaKappa_rem[EW1] 
                                        + deltaKappa_rem[EW1QCD1]
                                        + deltaKappa_rem[EW1QCD2]);
        deltaKappa_rem_G2 = pow(f_AlphaToGF,2.0)*deltaKappa_rem[EW2];
    }    
    
    /* Real parts */
    double kappaZ;
    if (!bool_Zbb) {
        switch (schemeKappaZ) {
            case NORESUM: 
                kappaZ = 1.0 + cW2_TMP/sW2_TMP*DeltaRho_sum + deltaKappa_rem_sum;
                break;
            case OMSI:
                kappaZ = (1.0 + deltaKappa_rem_G + deltaKappa_rem_G2)
                        *(1.0 + cW2_TMP/sW2_TMP*DeltaRho_sum*(1.0 - DeltaRbar_rem_G));
                break;
            case INTERMEDIATE:
                kappaZ = (1.0 + deltaKappa_rem_G)
                        *(1.0 + cW2_TMP/sW2_TMP*DeltaRho_sum*(1.0 - DeltaRbar_rem_G))
                        + deltaKappa_rem_G2;
                break;        
            case OMSII:
                kappaZ = 1.0 + cW2_TMP/sW2_TMP*DeltaRho_sum
                        - cW2_TMP/sW2_TMP*DeltaRho_G*DeltaRbar_rem_G
                        + deltaKappa_rem_G*(1.0 + cW2_TMP/sW2_TMP*DeltaRho_G)
                        + deltaKappa_rem_G2;
                break;
            default:
                throw std::runtime_error("Error in EWSM::resumKappaZ()"); 
        }
    } else {
        double kappaZbL = (1.0 + cW2_TMP/sW2_TMP*DeltaRho_sum)/(1.0+taub());
        deltaKappa_rem_G -= myCache->ale()/8.0/M_PI/sW2_TMP*pow(myCache->Mt()/Mw_TMP, 2.0);
        switch (schemeKappaZ) {
            case NORESUM: 
                kappaZ = (1.0 + cW2_TMP/sW2_TMP*DeltaRho_sum + deltaKappa_rem_G)/(1.0+taub());
                break;
            case OMSI:
                kappaZ = kappaZbL*(1.0 + deltaKappa_rem_G);
                break;
            case INTERMEDIATE:
                kappaZ = kappaZbL + deltaKappa_rem_G;
                break;
            case OMSII:
                kappaZ = kappaZbL + deltaKappa_rem_G;
                break;
            default:
                throw std::runtime_error("Error in EWSM::resumKappaZ()"); 
        }
    }

    return kappaZ;
}




