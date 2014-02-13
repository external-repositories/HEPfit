/* 
 * Copyright (C) 2012-2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef RBOTTOM_H
#define	RBOTTOM_H

#include <stdexcept>
#include <ThObservable.h>
#include "EW.h"

/**
 * @class Rbottom
 * @ingroup EW 
 * @brief An observable class for
 * @f$R_b^0=\Gamma(Z\to b\bar{b})/\Gamma(Z\to {\rm hadrons})@f$ at the @f$Z@f$ pole.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the ratio of the @f$Z\to b\bar{b}@f$ 
 * width to the @f$Z@f$-boson hadronic width at the @f$Z@f$ pole:
 * @f[
 * R_b = \frac{\Gamma_b}{\Gamma_h}\,.
 * @f]
 */
class Rbottom : public ThObservable {
public:

    /**
     * @brief Constructor.
     * @param[in] EW_i a reference to an object of type EW
     */
    Rbottom(const EW& EW_i) 
    : ThObservable(EW_i), myEW(EW_i)
    {
    };

    /**
     * @brief The ratio @f$R_b^0=\Gamma(Z\to b\bar{b})/\Gamma(Z\to {\rm hadrons})@f$
     * at the @f$Z@f$ pole.
     * @return @f$R_b^0@f$
     */
    double computeThValue();

    
private:
    const EW& myEW;///< A reference to an object of type EW.

};

#endif	/* RBOTTOM_H */

