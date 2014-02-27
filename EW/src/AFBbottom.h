/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef AFBBOTTOM_H
#define	AFBBOTTOM_H

#include <stdexcept>
#include <ThObservable.h>
#include "EW.h"

/**
 * @class AFBbottom 
 * @ingroup EW
 * @brief An observable class for the forward-backward asymmetry in
 * @f$e^+ e^-\to Z\to b\bar{b}@f$ at the @f$Z@f$ pole.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the forward-backward asymmetry for 
 * the @f$e^+ e^-\to Z\to b\bar{b}@f$ process at the @f$Z@f$ pole in terms of
 * the asymmetry parameters @f$\mathcal{A}_f@f$, computed in the EW class:
 * @f[
 * A_{\mathrm{FB}}^{0,b}=\frac 34 \mathcal{A}_e \mathcal{A}_b\,.
 * @f]
 *
 * @sa EW_NPZff::AFBbottom() and the detailed description of EW class
 * for the inclusion of new physics contribution
 *
 */
class AFBbottom : public ThObservable {
public:

    /**
     * @brief Constructor.
     * @param[in] EW_i a reference to an object of type EW
     */
    AFBbottom(const EW& EW_i) 
    : ThObservable(EW_i), myEW(EW_i) 
    {
    };

    /**
     * @brief The forward-backward asymmetry for @f$e^+ e^-\to Z \to b\bar{b}@f$
     * at the @f$Z@f$ pole, @f$A^{0,b}_{\mathrm{FB}}@f$
     * @return @f$A^{0,b}_{\mathrm{FB}}@f$
     */
    double computeThValue();

    
private:
    const EW& myEW;///< A reference to an object of type EW.

};

#endif	/* AFBBOTTOM_H */
