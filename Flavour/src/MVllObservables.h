/* 
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef MVLLOBSERVABLES_H
#define	MVLLOBSERVABLES_H

#include "MVll.h"
#include <StandardModel.h>
#include <ThObservable.h>


/**
 * @class P_1
 * @ingroup flavour
 * @brief A class for the clean observable P_1. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class P_1 : public ThObservable{
public:
    
    /**
    * @brief \f$ P_{1} \f$ 
    */
    P_1(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    
    /**
    * @return return the clean observable P_1
    */
    double computeThValue ();
    
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;
    
};


/**
 * @class P_2
 * @ingroup flavour
 * @brief A class for the clean observable P_2. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class P_2 : public ThObservable {
public:
    
    /**
    * @brief \f$ P_{2} \f$ 
    */
    P_2(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return return the clean observable P_2
    */
    double computeThValue ();
   
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;
    
};


/**
 * @class P_3
 * @ingroup flavour
 * @brief A class for the clean observable P_3. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class P_3 : public ThObservable{
public:
    
    /**
    * @brief \f$ P_{3} \f$ 
    */
    P_3(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return return the clean observable P_3
    */
    double computeThValue ();
   
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


/**
 * @class P_4Prime
 * @ingroup flavour
 * @brief A class for the clean observable P'_4. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class P_4Prime : public ThObservable{
public:
    
    /**
    * @brief \f$ P'_{4} \f$ 
    */
    P_4Prime(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return return the clean observable P'_4
    */
    double computeThValue ();
    
protected:
    
    
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;
};


/**
 * @class P_5Prime
 * @ingroup flavour
 * @brief A class for the clean observable P'_5. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class P_5Prime : public ThObservable{
public:
    
    /**
    * @brief \f$ P'_{5} \f$ 
    */

    P_5Prime(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return return the clean observable P'_5
    */
    double computeThValue ();
    
protected:
    
    
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


/**
 * @class P_6Prime
 * @ingroup flavour
 * @brief A class for the clean observable P'_6. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class P_6Prime : public ThObservable{
public:
    
    /**
    * @brief \f$ P'_{6} \f$ 
    */
    P_6Prime(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);

    /**
    * @return return the clean observable P'_6
    */
    double computeThValue ();
   
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


/**
 * @class GammaPrime
 * @ingroup flavour
 * @brief A class for the clean observable Gamma'. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class GammaPrime : public ThObservable{
public:
    
    /**
    * @brief \f$ Gamma' \f$ 
    */
    GammaPrime(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    double computeGammaPrime(double qmin, double qmax);
    
    /**
    * @return return the clean observable Gamma'
    */
    double computeThValue ();
   
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


/**
 * @class A_FB
 * @ingroup flavour
 * @brief A class for the clean observable A_{FB}. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class A_FB : public GammaPrime{
public:
    
    /**
    * @brief \f$ Gamma' \f$ 
    */
    A_FB(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return return the clean observable Gamma'
    */
    double computeThValue ();
   
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


/**
 * @class BF
 * @ingroup flavour
 * @brief A class for the Branching Fraction. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class BR_MVll : public GammaPrime{
public:
    
    /**
    * @brief \f$B\to K^* l^+l^-\f$ 
    */
    BR_MVll(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return the branching fraction of \f$B\to K^* l^+l^-\f$
    */
    double computeThValue ();
    
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;
    
};


/**
 * @class ACP
 * @ingroup flavour
 * @brief A class for the clean observable ACP. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class ACP_MVll : public GammaPrime{
public:
    
    /**
    * @brief \f$ A_{CP} \f$ 
    */
    ACP_MVll(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return return the clean observable ACP
    */
    double computeThValue ();
   
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


/**
 * @class P3CP
 * @ingroup flavour
 * @brief A class for the clean observable P3CP. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class P3CP : public ThObservable{
public:
    
    /**
    * @brief \f$ P_3^{CP} \f$ 
    */
    P3CP(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return return the clean observable P3CP
    */
    double computeThValue ();

private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


/**
 * @class F_L
 * @ingroup flavour
 * @brief A class for the clean observable F_L. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class F_L : public ThObservable{
public:
    
    /**
    * @brief \f$ F_L \f$ 
    */
    F_L(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);

    
    /**
    * @return return the clean observable F_L
    */
    double computeThValue ();

private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


/**
 * @class M_1Prime
 * @ingroup flavour
 * @brief A class for the clean observable M'_1. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class M_1Prime : public ThObservable{
public:
    
    /**
    * @brief \f$ M'_1 \f$ 
    */
    M_1Prime(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return return the clean observable M'_1
    */
    double computeThValue ();
    
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


/**
 * @class M_2Prime
 * @ingroup flavour
 * @brief A class for the clean observable M'_2. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class M_2Prime : public ThObservable{
public:
    
    /**
    * @brief \f$ M'_2 \f$ 
    */
    M_2Prime(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i);
    
    /**
    * @return return the clean observable M'_2
    */
    double computeThValue ();
    
private:
    const StandardModel& mySM;
    StandardModel::lepton lep;
    StandardModel::meson meson;
    StandardModel::meson vectorM;

};


#endif	/* MVLLOBSERVABLES_H */

    