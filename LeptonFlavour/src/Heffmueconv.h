/*
 * Copyright (C) 2015 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef HEFFMUECONV_H
#define	HEFFMUECONV_H

#include "StandardModel.h"
#include "StandardModelMatching.h"
#include "WilsonCoefficient.h"

/**
 * @class Heffmueconv
 * @ingroup LeptonFlavour
 * @brief A class for calculating all the Wilson coefficients for the process \f$ \mu \to e \f$ conversion in Nuclei. 
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details The Heffmueconv class aggregates the Wilson coefficients for the process \f$ \mu \to e \f$ conversion in Nuclei generated by the model and sum them order by order.
 */
class Heffmueconv {
public:
    /**
     * @brief The constructor of the class Heffmueconv.
     * @param[in] Wilson coefficient responsible for the process \f$ \mu \to e \f$ conversion in Nuclei in the SM 
     * @param[in] Wilson coefficient responsible for the process \f$ \mu \to e \f$ conversion in Nuclei in the model analyzed
     */
    Heffmueconv(const StandardModel & SM_i);
    
    /**
     * @brief destructor of the class Heffmueconv.
     */
    virtual ~Heffmueconv();
    
    /**
     * @brief Computes the Wilson coefficients for the process \f$ \mu \to e \f$ conversion in Nuclei.
     * @return returns the Wilson coefficients for the process
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffmueconv();

    /**
     * @brief Calls the model analyzed to calculate Wilson coefficients for the process \f$ \mu \to e \f$ conversion in Nuclei.
     */   
    const StandardModel& GetModel() const {
        return model;
    }
    
private :
    /**
     * @brief Variable which stores the model information.
     */
    const StandardModel& model;

    /**
     * @brief Variable which stores the Wilson coefficient for \f$ \mu \to e \f$ conversion in Nuclei.
     */
    WilsonCoefficient coeffmueconv;

};

#endif	/* HEFFMUECONV_H */
