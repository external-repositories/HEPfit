/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "Mw.h"


double Mw::getThValue() {
    double myMw;
    if (myEWTYPE==EW::EWCHMN)  
        myMw = myEW.getMyEW_CHMN().Mw();
    else if (myEWTYPE==EW::EWABC)
        myMw = myEW.getMyEW_ABC().Mw(SM.epsilon1(),SM.epsilon2(),SM.epsilon3());
    else if (myEWTYPE==EW::EWABC2) {
        double delta_alpha = (SM.alphaMz() - 1.0/128.90)/SM.getAle();
        double cW2_Born = 0.768905*(1.0 - 0.40*delta_alpha);
        double cW2 = cW2_Born*(1.0 + 1.43*SM.epsilon1() - 1.00*SM.epsilon2() - 0.86*SM.epsilon3());
        myMw = sqrt(cW2)*SM.getMz();
    } else {
        myMw = SM.Mw();    

        if ( myEW.checkModelForSTU() ) {
            if(myEWTYPE==EW::EWBURGESS) {
                // TEST: the fit result by Gfitter in arXiv:1209.2716, 
                //       corresponding to MH=125.7 and Mt=173.52 
                //myMw = 80.367; 
                
                myMw *= 1.0 - 0.00723/2.0*myEW.S() + 0.0111/2.0*myEW.T() + 0.00849/2.0*myEW.U();
            } else {
                double alpha = myEW.alpha0();  
                double c = sqrt(myEW.c02());
                double c2 = myEW.c02();
                double s2 = myEW.s02();
                
                myMw -= alpha*c*SM.getMz()/4.0/(c2-s2)
                        *( myEW.S() - 2.0*c2*myEW.T() - (c2-s2)*myEW.U()/2.0/s2 );
            }
        }
    }
    
    return myMw;
}

