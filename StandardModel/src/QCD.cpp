/* 
 * File:   QCD.cpp
 * Author: marco
 * 
 * Created on February 17, 2011, 2:13 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <map>



#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <TF1.h>
#include <Math/WrappedTF1.h>
#include <Math/BrentRootFinder.h>
#include "QCD.h"

const std::string QCD::QCDvars[NQCDvars] = {
    "AlsMz","Mz","mup","mdown","mcharm","mstrange",
    "mtop","mbottom","mut","mub","muc","MBd",
    "MBs","MBp","MK0","MKp","MD","FBs","FBsoFBd", "FD",
    "BBsoBBd","BBs1","BBs2","BBs3","BBs4","BBs5", "BBsscale", "BBsscheme",
    "BD1","BD2","BD3","BD4","BD5", "BDscale", "BDscheme",
    "BK1","BK2","BK3","BK4","BK5", "BKscale", "BKscheme"
};

void QCD::Update(const std::map<std::string, double>& DPars) {
    computeYu = false;
    computeYd = false;
    computeBd = false; 
    computeFBd = false;
    computemt = false;
    for (std::map<std::string, double>::const_iterator it = DPars.begin(); it != DPars.end(); it++) 
        SetParameter(it->first,it->second);
    if(computeFBd)
        mesons[B_D].setDecayconst(mesons[B_S].getDecayconst()/FBsoFBd);
    if(computeBd)
        BBd.setBpars(0, BBs.getBpars()(0)/BBsoBBd);
    if(computemt)
 //       quarks[TOP].setMass(Mp2Mbar(mtpole));
        quarks[TOP].setMass(175.0);
}

void QCD::SetParameter(const std::string name, const double& value) {
    if(name.compare("AlsMz")==0){
        AlsMz = value;
        computemt = true;
    }
    else if(name.compare("Mz")==0)
        Mz = value;
    else if(name.compare("mup")==0){
        quarks[UP].setMass(value);
        computeYu = true;
    }
    else if(name.compare("mdown")==0){
        quarks[DOWN].setMass(value);
        computeYd = true;
    }
    else if(name.compare("mcharm")==0){
        quarks[CHARM].setMass(value);
        computeYu = true;
    }
    else if(name.compare("mstrange")==0){
        quarks[STRANGE].setMass(value);
        computeYd = true;
    }
    else if(name.compare("mtop")==0){
        mtpole = value;
        computeYu = true;
        computemt = true;
    }
    else if(name.compare("mbottom")==0){
        quarks[BOTTOM].setMass(value);
        computeYd = true;
    }
    else if(name.compare("mut")==0)
        mut = value;
    else if(name.compare("mub")==0)
        mub = value;
    else if(name.compare("muc")==0)
        muc = value;
    else if(name.compare("MBd")==0)
        mesons[B_D].setMass(value);
    else if(name.compare("MBs")==0)
        mesons[B_S].setMass(value);
    else if(name.compare("MBp")==0)
        mesons[B_P].setMass(value);
    else if(name.compare("MK0")==0)
        mesons[K_0].setMass(value);
    else if(name.compare("MKp")==0)
        mesons[K_P].setMass(value);
    else if(name.compare("MD")==0)
        mesons[D_0].setMass(value);
    else if(name.compare("FBs")==0) {
        mesons[B_S].setDecayconst(value);
        computeFBd = true;
    }
    else if(name.compare("FBsoFBd")==0) {
        FBsoFBd = value;
        computeFBd = true;
    }
    else if(name.compare("FD")==0) {
        mesons[D_0].setDecayconst(value);
    }
    else if(name.compare("BBsoBBd")==0) {
        BBsoBBd = value;
        computeBd = true;
    }
    else if(name.compare("BBs1")==0) {
        BBs.setBpars(0,value);
        computeBd = true;
    }
   else if(name.compare("BBs2")==0) {
        BBd.setBpars(1,value);
        BBs.setBpars(1,value);
    }
    else if(name.compare("BBs3")==0) {
        BBd.setBpars(2,value);
        BBs.setBpars(2,value);
    }
    else if(name.compare("BBs4")==0){
        BBd.setBpars(3,value);
        BBs.setBpars(3,value);
    }
    else if(name.compare("BBs5")==0){
        BBd.setBpars(4,value);
        BBs.setBpars(4,value);
    }    
    else if(name.compare("BBsscale")==0){
        BBd.setMu(value);
        BBs.setMu(value);
    }    
    else if(name.compare("BBsscheme")==0){
        BBd.setScheme((schemes) value);
        BBs.setScheme((schemes) value);
    }
    else if(name.compare("BD1")==0) {
        BD.setBpars(0,value);
    }
    else if(name.compare("BD2")==0) {
        BD.setBpars(1,value);
    }
    else if(name.compare("BD3")==0) {
        BD.setBpars(2,value);
    }
    else if(name.compare("BD4")==0){
        BD.setBpars(3,value);}
    else if(name.compare("BD5")==0){
        BD.setBpars(4,value);
    }    
    else if(name.compare("BDscale")==0){
        BD.setMu(value);
    }    
    else if(name.compare("BDscheme")==0){
        BD.setScheme((schemes) value);
    }
    else if(name.compare("BK1")==0) {
        BK.setBpars(0,value);
    }
   else if(name.compare("BK2")==0) {
        BK.setBpars(1,value);
   }
    else if(name.compare("BK3")==0) {
        BK.setBpars(2,value);
    }
    else if(name.compare("BK4")==0){
        BK.setBpars(3,value);}
    else if(name.compare("BK5")==0){
        BK.setBpars(4,value);
    }    
    else if(name.compare("BKscale")==0){
        BK.setMu(value);
    }    
    else if(name.compare("BKscheme")==0){
        BK.setScheme((schemes) value);
    }
//    else {
//        std::cout << "cannot set parameter " << name << " in SetQCDParameter" << std::endl;
//        exit(EXIT_FAILURE);
//    }

}

bool QCD::CheckParameters(const std::map<std::string, double>& DPars) {
    for(int i=0;i<NQCDvars;i++)
        if(DPars.find(QCDvars[i])==DPars.end()) {
            std::cout << "missing mandatory QCD parameter " << QCDvars[i] << std::endl;
            return false;
        }
    return true;
}

bool QCD::Init(const std::map<std::string, double>& DPars) {
    Update(DPars);
    return(CheckParameters(DPars));
}

double QCD::Beta0(double nf) const {
    return((11.*Nc-2.*nf)/3.);
}

double QCD::Beta1(double nf) const {
    return(34./3.*Nc*Nc-10./3.*Nc*nf-(Nc-1./Nc)*nf);
}

double QCD::Beta2(double nf) const{
    return (2857./2.-5033./18.*nf+325./54.*nf*nf);
}

double QCD::Thresholds(int i) const
{
    if(!(mut > mub && mub > muc)) {
        std::cout << "inverted thresholds!" << std::endl;
        exit(EXIT_FAILURE);
    }
    switch(i) {
        case 0: return(1.0E10);
        case 1: return(mut);
        case 2: return(mub);
        case 3: return(muc);
        case 4: return(1.);
        default: return(0.);
    }
}

double QCD::Nf(double mu) const {
    int i;

    for(i=1; i<5; i++)
        if(mu >= Thresholds(i))
            return(7.-i);
    std::cout << "error in QCD::Nf" << std::endl;
    exit(EXIT_FAILURE);
}

double QCD::AboveTh(double mu) const {
    int i;

    for(i=4; i>=0; i--)
        if(mu < Thresholds(i)) return(Thresholds(i));

    exit(EXIT_FAILURE);
}

double QCD::BelowTh(double mu) const {
  int i;

  for(i=0; i<5; i++)
    if(mu >= Thresholds(i)) return(Thresholds(i));

  exit(EXIT_FAILURE);
}

double QCD::Als(double mu, double lam, double nf, orders order) const {
  double ll = 2.*log(mu/lam);
  double x = log(ll);
  switch(order) {
      case LO:
          return(4.*M_PI/Beta0(nf)/ll);
      case FULLNLO:
          return(4.*M_PI/Beta0(nf)/ll*(1.-Beta1(nf)*log(ll)/pow(Beta0(nf),2.)/ll));
      case NLO:
          return(4.*M_PI/Beta0(nf)/ll*(-Beta1(nf)*log(ll)/pow(Beta0(nf),2.)/ll));
      case FULLNNLO:
          return(4.*M_PI*(1./Beta0(nf)/ll-Beta1(nf)*x/(Beta0(nf)*Beta0(nf)*Beta0(nf)*ll*ll)
                  +1./(Beta0(nf)*Beta0(nf)*Beta0(nf)*ll*ll*ll)*(Beta1(nf)*Beta1(nf)
                  /Beta0(nf)/Beta0(nf)*(x*x-x-1.)+Beta2(nf)/Beta0(nf))));
      case NNLO:
          return(1./(Beta0(nf)*Beta0(nf)*Beta0(nf)*ll*ll*ll)*(Beta1(nf)*Beta1(nf)
                  /Beta0(nf)/Beta0(nf)*(x*x-x-1.)+Beta2(nf)/Beta0(nf)));
      default:
          std::cerr << "als: order " << order <<" not defined\n" << std::endl;
          exit(EXIT_FAILURE);
  }
}

double QCD::Als(double mu, double nf, double alsi, double mi, orders order) const {
    double v = 1.-Beta0(nf)*alsi/2./M_PI*log(mi/mu);
    switch(order) {
        case LO:
            return(alsi/v);
        case FULLNLO:
            return(alsi/v*(1.-Beta1(nf)/Beta0(nf)*alsi/4./M_PI*log(v)/v));
        case NLO:
            return(alsi/v*(-Beta1(nf)/Beta0(nf)*alsi/4./M_PI*log(v)/v));
        default:
           std::cerr << "als: order " << order <<" not defined\n" << std::endl;
           exit(EXIT_FAILURE);
    }
}

double QCD::Als(double mu, double nfmu, orders order) const {
    double nfz = Nf(Mz), m, nfs;
    double x,y,z;
    double Lambda6 = 0.;
    double Lambda4_TMP = 0.;
    double Lambda3 = 0.;

    if(nfmu == nfz) return(Als(mu, Lambda5(order), nfmu, order));
    if(nfmu > nfz) {
//        m = BelowTh(mu);
//        nfs = nfmu-1;
        
        double mt = quarks[5].getMass();
        double lh = log(mt*mt/Lambda5(order)/Lambda5(order));
        y = Beta1(6)/Beta0(6);
        z = Beta1(5)/Beta0(5);
        
        x = 1./2./Beta0(6)*((Beta0(6) - Beta0(5))*lh + (y - z)*log(lh) 
           - y*log(Beta0(6)/Beta0(5)) + 1./Beta0(5)/lh*(z*(y - z)*log(lh) 
           + y*y - z*z - Beta2(6)/Beta0(6) + Beta2(5)/Beta0(5) - 11./72.)) 
           + log(Lambda5(order));

        Lambda6 = exp(x);
//         std::cout << std::left 
//             << std::setw(15) << "Lambda6new = " 
//             << std::setw(15) << Lambda6 << std::endl;
        
        return Als(mu, Lambda6, nfmu, order);
    } else if(nfmu < nfz){
        
        y = Beta1(4)/Beta0(4);
        z = Beta1(5)/Beta0(5);
        double mb = quarks[BOTTOM].getMass();
        double lh4 = log(mb*mb/Lambda5(order)/Lambda5(order));
        std::cout << std::left 
             << std::setw(15) << "lh4 = " 
             << std::setw(15) << lh4 << "\t" << order << std::endl;
        
        x = 1./2./Beta0(4)*((Beta0(4) - Beta0(5))*lh4 + (y - z)*log(lh4) 
           - y*log(Beta0(4)/Beta0(5)) + 1./Beta0(5)/lh4*(z*(y - z)*log(lh4) 
           + y*y - z*z - Beta2(4)/Beta0(4) + Beta2(5)/Beta0(5) + 11.*16./72.)) 
           + log(Lambda5(order));
        
        
        Lambda4_TMP = exp(x);
        std::cout << std::left 
             << std::setw(15) << "Lambda4new = " 
             << std::setw(15) << Lambda4_TMP << "\t" << order << std::endl;
        
        double mc = quarks[CHARM].getMass();
        double x3;
        double y3 = Beta1(3)/Beta0(3);
        double z3 = Beta1(4)/Beta0(4);
        double lh3 = log(mc*mc/Lambda4_TMP/Lambda4_TMP);
    
        x3 = 1./2./Beta0(3)*((Beta0(3) - Beta0(4))*lh3 + (y3 - z3)*log(lh3) 
          - y3*log(Beta0(3)/Beta0(4)) + 1./Beta0(4)/lh3*(z3*(y3 - z3)*log(lh3) 
          + y3*y3 - z3*z3 - Beta2(3)/Beta0(3) + Beta2(4)/Beta0(4) + 11.*16./72.)) 
          + log(Lambda4_TMP);

        Lambda3 = exp(x3);
       std::cout << std::left 
            << std::setw(15) << "Lambda3new = " 
            << std::setw(15) << Lambda3 << std::endl;
        
        
        if(nfmu == 4){
            return Als(mu, Lambda4_TMP, nfmu, order);
        } else if (nfmu == 3){
            return Als(mu, Lambda3, nfmu, order);
        }
//        m = AboveTh(mu);
//        nfs = nfmu+1;
    }
    //return(Als(mu, nfmu, Als(m, nfs, order), m, order));
}
            
void QCD::CacheShift(double cache[][5], int n) const {
    int i,j;
    for(i=4;i>0;i--)
        for(j=0;j<n;j++)
            cache[j][i] = cache[j][i-1];
}

double QCD::Als(double mu, orders order) const {
    //int i;
    return Als(mu, Nf(mu), order);
//    for(i=0;i<5;i++)
//        if((mu ==  als_cache[0][i]) && (order == als_cache[1][i]) &&
//                (AlsMz == als_cache[2][i]) && (Mz == als_cache[3][i]))
//            return als_cache[4][i];
//
//    CacheShift(als_cache,5);
//    als_cache[0][0] = mu;
//    als_cache[1][0] = order;
//    als_cache[2][0] = AlsMz;
//    als_cache[3][0] = Mz;
//    als_cache[4][0] = Als(mu, Nf(mu), order);
//
//    return(als_cache[4][0]);
}

double QCD::Zero(double *x, double *y) const {
    return(Als(mub, *x, 4., (orders) *y) - Als(mub, (orders) *y));
}

double QCD::ZeroNf5(double *x, double *y)const{
    return(Als(Mz,*x,5.,(orders) *y)-AlsMz);
}


double QCD::Lambda4(orders order) const {

    if(order!=LO && order!=FULLNLO){
        std::cerr<< "error in order selection in lambda4" << std::endl;
        exit(EXIT_FAILURE);
    }

    int i;
    double alsmub = Als(mub,order);
    for(i=0;i<5;i++)
        if(alsmub ==  lambda4_cache[0][i])
            return lambda4_cache[1][i];

    CacheShift(lambda4_cache,2);
    lambda4_cache[0][0] = alsmub;

    double xmin = 0.01, xmax = 0.8;
    TF1 f = TF1("f",this,&QCD::Zero,xmin,xmax,1,"QCD","zero");

    ROOT::Math::WrappedTF1 wf1(f);
    double ledouble = order;
    wf1.SetParameters(&ledouble);

    ROOT::Math::BrentRootFinder brf;
    brf.SetFunction( wf1, xmin, xmax );

    if(brf.Solve()) lambda4_cache[1][0]=brf.Root();
    else {
        std::cerr << "error in QCD::findroot" << std::endl;
        exit(EXIT_FAILURE);
    }
    return(lambda4_cache[1][0]);
}


double QCD::Lambda5(orders order) const {

    if(order!=LO && order!=FULLNLO && order!=FULLNNLO){
        std::cerr<< "error in order selection in lambda5" << std::endl;
        exit(EXIT_FAILURE);
    }

    int i;
    //double alsmub = Als(mub,order);
    for(i=0;i<5;i++)
        if(AlsMz ==  lambda5_cache[0][i])
            return lambda5_cache[1][i];

    CacheShift(lambda5_cache,2);
    lambda5_cache[0][0] = AlsMz;

    double xmin = 0.01, xmax = 0.8;
    TF1 f = TF1("f",this,&QCD::ZeroNf5,xmin,xmax,1,"QCD","zeroNf5");

    ROOT::Math::WrappedTF1 wf1(f);
    double ledouble = order;
    wf1.SetParameters(&ledouble);

    ROOT::Math::BrentRootFinder brf;
    brf.SetFunction( wf1, xmin, xmax );

    if(brf.Solve()) lambda5_cache[1][0]=brf.Root();
    else {
        std::cerr << "error in QCD::findroot" << std::endl;
        exit(EXIT_FAILURE);
    }
    return(lambda5_cache[1][0]);
}


// running da m(m) a m(mu)
double QCD::Mrun(double mu, double m, orders order) const
{
    return(Mrun(mu,m,m,order));
}

// running da m(mu_i) a m(mu_f)
double QCD::Mrun(double mu_f, double mu_i, double m, orders order) const
{
    int i;
    for(i=0;i<5;i++)
        if((mu_f ==  mrun_cache[0][i]) && (mu_i == mrun_cache[1][i]) &&
                (m == mrun_cache[2][i]) && (order == mrun_cache[3][i])&&
                (AlsMz == mrun_cache[4][i]))
            return mrun_cache[5][i];

    double mx, nfx;
    double nfi = Nf(mu_i), nff = Nf(mu_f);

    if(nff == nfi || (nff == nfi - 1 && mu_i == AboveTh(mu_f))) 
            return(Mrun(mu_f, mu_i, m, nff, order));
    if(nff > nfi) {
        mx = AboveTh(mu_i);
        nfx = nfi;
    }
    else {
        mx = BelowTh(mu_i);
        nfx = nfi-1;
    }

    double mrun = Mrun(mu_f, mx, Mrun(mx, mu_i, m, nfx, order), order);

    CacheShift(mrun_cache,6);
    mrun_cache[0][0] = mu_f;
    mrun_cache[1][0] = mu_i;
    mrun_cache[2][0] = m;
    mrun_cache[3][0] = order;
    mrun_cache[4][0] = AlsMz;
    mrun_cache[5][0] = mrun;
    
    return(mrun);
}

// running da m(mu_i) a m(mu_f) a nf fissato
double QCD::Mrun(double mu_f, double mu_i, double m, double nf, orders order) const
{
  double j;

    j = -(4./3.*(4.+97.-10./3.*nf))/2./Beta0(nf)+4.*Beta1(nf)/(Beta0(nf)*Beta0(nf));

    switch(order) {
        case LO:
            return(m*pow(Als(mu_f,order)/Als(mu_i,order),4./Beta0(nf)));
        case FULLNLO:
            return(m*pow(Als(mu_f,order)/Als(mu_i,order),4./Beta0(nf))*(1.+(Als(mu_i,order)-
                    Als(mu_f,order))/4./M_PI*j));
        case NLO:
            return(m*pow(Als(mu_f,order)/Als(mu_i,order),4./Beta0(nf))*(Als(mu_i,order)-
                    Als(mu_f,order))/4./M_PI*j);
        default:
            std::cerr << "mrun: order not defined\n" << std::endl;
            exit(EXIT_FAILURE);
    }
}

double QCD::Mp2Mbara(double * mu, double * mp) const
{
  return(*mp-Mbar2Mp(*mu));
}

double QCD::Mp2Mbar(double mp) const {

    int i;
    double ms = quarks[STRANGE].getMass(), mc = quarks[CHARM].getMass();
    double alsmp = Als(mp);
    for(i=0;i<5;i++)
        if(alsmp == mp2mbar_cache[0][i] && ms == mp2mbar_cache[1][i] &&
               mc == mp2mbar_cache[2][i] )
            return mp2mbar_cache[3][i];

    CacheShift(mp2mbar_cache,4);
    mp2mbar_cache[0][0] = alsmp;
    mp2mbar_cache[1][0] = ms;
    mp2mbar_cache[2][0] = mc;

    TF1 f("f",this,&QCD::Mp2Mbara,mp/2.,2.*mp,1,"QCD","mp2mbara");

    ROOT::Math::WrappedTF1 wf1(f);
    wf1.SetParameters(&mp);

    ROOT::Math::BrentRootFinder brf;

    brf.SetFunction( wf1, .7*mp, 1.3*mp );
    if(brf.Solve()) mp2mbar_cache[3][0] = brf.Root();
    else
    {
        std::cerr << "error in QCD::mp2mbar" << std::endl;
        exit(EXIT_FAILURE);
    }
    return(mp2mbar_cache[3][0]);
}

double QCD::Mbar2Mp(double mbar) const {
    if(mbar > 3.)
    {
        double a,D=5.;
        a=Als(mbar)/M_PI;
        if(mbar < 50.)
            D=4.-4./3.*(quarks[STRANGE].getMass()+quarks[CHARM].getMass())/mbar; //only for the b quark

        return(mbar*(1.+4./3.*a+a*a*(13.44434-1.0414*D)));
    }
    else
    {
        std::cerr << "can convert only top and bottom masses" << std::endl;
        exit(EXIT_FAILURE);
    }
}

double QCD::MS2DRqmass(const double& MSbar) const {
    return(MSbar/(1.+Als(MSbar)/4./M_PI*CF));
}