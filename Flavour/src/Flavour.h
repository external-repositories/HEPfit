/* 
 * Copyright (C) 2012 SusyFit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef FLAVOUR_H
#define FLAVOUR_H

class StandardModel;
class HeffDF2;
class HeffDB1;
class MVll;
class MPll;
class MVgamma;
#include "QCD.h"
#include <boost/tuple/tuple.hpp>

/**
 * @class Flavour
 * @ingroup Flavour
 * @brief The parent class in Flavour for calculating all the Wilson coefficients for various Flavor Violating processes. 
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details The Flavour class aggregates the Wilson coefficients for each of the processes generated by the model by calling the Hamiltonians.
 */

class Flavour {
public:

    /**
     * @brief The constructor.
     * @param[in] SM_i a reference to an object of the class StandardModel
     */
    Flavour(const StandardModel& SM_i);

    /**
     * @brief The member that returns an object of the class HeffDF2.
     * @return returns the Hamiltonian for the \f$ \Delta F = 2 \f$ processes
     * 
     */
    const HeffDF2& getHDF2() const
    {
        return HDF2;
    }

    /**
     * @brief The member that returns an object of the class HeffDB1.
     * @return returns the Hamiltonian for the \f$ \Delta B = 1 \f$ processes.
     * 
     */
    const HeffDB1& getHDB1() const
    {
        return HDB1;
    }

    /**
     * @brief Computes the Wilson coefficient for the process \f$ B_d \to \mu \mu \f$.
     * @param[in] mu the lower matching scale for the process
     * @param[in] scheme the scheme in which the Wilson Coefficients need to be calculated
     * @return returns the Wilson coefficients for the process \f$ B_d \to \mu \mu \f$
     * 
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffBd(double mu, schemes scheme = NDR) const;

    gslpp::vector<gslpp::complex>** ComputeCoeffDS1pnunu() const;

    gslpp::vector<gslpp::complex>** ComputeCoeffDS1mumu() const;

    /**
     * @brief Computes the Wilson coefficient for the process \f$ B_s \to \mu \mu \f$.
     * @param[in] mu the lower matching scale for the process
     * @param[in] scheme the scheme in which the Wilson Coefficients need to be calculated
     * @return returns the Wilson coefficients for the process \f$ B_s \to \mu \mu \f$
     * 
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffBs(double mu, schemes scheme = NDR) const;

    gslpp::vector<gslpp::complex>** ComputeCoeffdd(double mu, schemes scheme = NDR) const;

    gslpp::vector<gslpp::complex>** ComputeCoeffK(double mu, schemes scheme = NDR) const;

    gslpp::vector<gslpp::complex>** ComputeCoeffmK(double mu, schemes scheme = NDR) const;

    gslpp::vector<gslpp::complex>** ComputeCoeffDS1PP(double mu, schemes scheme = NDR) const;

    /**
     * @brief Computes the Wilson coefficient for the process \f$ B_s \to \mu \mu \f$.
     * @param[in] mu the lower matching scale for the process
     * @param[in] scheme the scheme in which the Wilson Coefficients need to be calculated
     * @return returns the Wilson coefficients for the process \f$ B_s \to \mu \mu \f$
     * 
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffsmumu(double mu, schemes scheme = NDR) const;

    /**
     * @brief Computes the Wilson coefficient for the process \f$ B_d \to \mu \mu \f$.
     * @param[in] mu the lower matching scale for the process
     * @param[in] scheme the scheme in which the Wilson Coefficients need to be calculated
     * @return returns the Wilson coefficients for the process \f$ B_d \to \mu \mu \f$
     * 
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffdmumu(double mu, schemes scheme = NDR) const;

    /**
     * @brief Computes the Wilson coefficient for the process \f$ B_d \to \tau \nu \f$.
     * @param[in] mu the lower matching scale for the process
     * @param[in] scheme the scheme in which the Wilson Coefficients need to be calculated
     * @return returns the Wilson coefficients for the process \f$ B_d \to \tau \nu \f$
     * 
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffbtaunu() const;

    gslpp::vector<gslpp::complex>** ComputeCoeffsnunu() const;

    gslpp::vector<gslpp::complex>** ComputeCoeffdnunu() const;

    /**
     * @brief Computes the Wilson coefficient for the process \f$ b \to s \gamma \f$.
     * @param[in] mu the lower matching scale for the process
     * @param[in] scheme the scheme in which the Wilson Coefficients need to be calculated
     * @return returns the Wilson coefficients for the process \f$ b \to s \gamma \f$
     * 
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffsgamma(double mu, schemes scheme = NDR) const;

    /**
     * @brief Computes the chirality flipped Wilson coefficient for the process \f$ b \to s \gamma \f$.
     * @param[in] mu the lower matching scale for the process
     * @param[in] scheme the scheme in which the Wilson Coefficients need to be calculated
     * @return returns the chirality flipped Wilson coefficients for the process \f$ b \to s \gamma \f$
     * 
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffprimesgamma(double mu, schemes scheme = NDR) const;

    /**
     * @brief Computes the Wilson coefficient for the process \f$ B \to V/P \ell^+ \ell^- \f$.
     * @param[in] mu the lower matching scale for the process
     * @param[in] scheme the scheme in which the Wilson Coefficients need to be calculated
     * @return returns the Wilson coefficients for the process \f$ B \to V/P \ell^+ \ell^- \f$
     * 
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffBMll(double mu, QCD::lepton lepton, schemes scheme = NDR) const;

    /**
     * @brief Computes the chirality flipped Wilson coefficient for the process \f$ B \to V/P \ell^+ \ell^- \f$.
     * @param[in] mu the lower matching scale for the process
     * @param[in] scheme the scheme in which the Wilson Coefficients need to be calculated
     * @return returns the chirality flipped Wilson coefficients for the process \f$ B \to V/P \ell^+ \ell^- \f$
     * 
     */
    gslpp::vector<gslpp::complex>** ComputeCoeffprimeBMll(double mu, QCD::lepton lepton, schemes scheme = NDR) const;

    /**
     * @brief Returns the initial and final state dependent object for \f$ B \to V \ell^+ \ell^- \f$.
     * @param[in] meson_i specifies the meson in the initial state
     * @param[in] vector_i specifies the vector in the final state
     * @param[in] lepton_i specifies the lepton in the final state
     * @return returns a pointer to the initial and final state dependent object for the process \f$ B \to V \ell^+ \ell^- \f$
     * 
     */
    MVll& getMVll(unsigned int meson_i, unsigned int vector_i, unsigned int lep_i) const;

    /**
     * @brief Returns the initial and final state dependent object for \f$ B \to P \ell^+ \ell^- \f$.
     * @param[in] meson_i specifies the meson in the initial state
     * @param[in] pseudoscalar_i specifies the vector in the final state
     * @param[in] lepton_i specifies the lepton in the final state
     * @return returns a pointer to the initial and final state dependent object for the process \f$ B \to P \ell^+ \ell^- \f$
     * 
     */
    MPll& getMPll(unsigned int meson_i, unsigned int pseudoscalar_i, unsigned int lep_i) const;

    /**
     * @brief Returns the initial and final state dependent object for \f$ B \to V \gamma \f$.
     * @param[in] meson_i specifies the meson in the initial state
     * @param[in] vector_i specifies the vector in the final state
     * @return returns a pointer to the initial and final state dependent object for the process \f$ B \to V \gamma \f$
     * 
     */
    MVgamma& getMVgamma(unsigned int meson_i, unsigned int vector_i) const;

    /**
     * @brief sets the update flag for the initial and final state dependent object for \f$ B \to V \ell^+ \ell^- \f$.
     * @param[in] meson_i specifies the meson in the initial state
     * @param[in] vector_i specifies the vector in the final state
     * @param[in] lepton_i specifies the lepton in the final state
     * 
     */
    void setUpdateFlag(unsigned int meson_i, unsigned int meson_j, unsigned int lep_i, bool updated_i) const;

    /**
     * @brief gets the update flag for the initial and final state dependent object for \f$ B \to V \ell^+ \ell^- \f$.
     * @param[in] meson_i specifies the meson in the initial state
     * @param[in] vector_i specifies the vector in the final state
     * @param[in] lepton_i specifies the lepton in the final state
     * 
     */
    bool getUpdateFlag(unsigned int meson_i, unsigned int meson_j, unsigned int lep_i) const;

    /**
     * @brief a member used for the caching for \f$ B \to V \ell^+ \ell^- \f$.
     * 
     */
    void setSMupdated() const;
    
    bool setFlagFullKD(bool fullKD)
    {
        return (this->fullKD = fullKD);
    }
    
    bool getFlagFullKD() const
    {
        return fullKD;
    }

private:

    HeffDF2& HDF2; ///< An Object for the Hamiltonian of the \f$ \Delta F = 2 \f$ processes.
    HeffDB1& HDB1; ///< An Object for the Hamiltonian of the \f$ \Delta B = 1 \f$ processes.
    MVll& MVll_BdKstarmu; ///< An object for the process \f$ B_d \to K^* \mu^+ \mu^- \f$.
    MVll& MVll_BdKstarel; ///< An object for the process \f$ B_d \to K^* \e^+ \e^- \f$.
    MVll& MVll_BpKstarmu; ///< An object for the process \f$ B^\pm \to K^{*\pm} \mu^+ \mu^- \f$.
    MVll& MVll_BpKstarel; ///< An object for the process \f$ B^\pm \to K^{*\pm} \e^+ \e^- \f$.
    MVll& MVll_Bsphimu; ///< An object for the process \f$ B_s \to \phi \mu^+ \mu^- \f$.
    MVll& MVll_Bsphiel; ///< An object for the process \f$ B_s \to \phi \e^+ \e^- \f$.
    MPll& MPll_BpKmu; ///< An object for the process \f$ B^+ \to K^+ \mu^+ \mu^- \f$.
    MPll& MPll_BpKel; ///< An object for the process \f$ B^+ \to K^+ \e^+ \e^- \f$.
    MVgamma& MVgamma_BdKstgamma;
    MVgamma& MVgamma_BpKstgamma;
    MVgamma& MVgamma_Bsphigamma;
    mutable bool update_BdKstarmu; ///< A flag used for caching of \f$ B_d \to K^* \mu^+ \mu^- \f$.
    mutable bool update_BdKstarel; ///< A flag used for caching of \f$ B_d \to K^* \e^+ \e^- \f$.
    mutable bool update_BpKstarmu; ///< A flag used for caching of \f$ B_d \to K^{*\pm} \mu^+ \mu^- \f$.
    mutable bool update_BpKstarel; ///< A flag used for caching of \f$ B_d \to K^{*\pm} \e^+ \e^- \f$.
    mutable bool update_Bsphimu; ///< A flag used for caching of \f$ B_s \to \phi \mu^+ \mu^- \f$.
    mutable bool update_Bsphiel; ///< A flag used for caching of \f$ B_s \to \phi \e^+ \e^- \f$.
    mutable bool update_BpKmu; ///< A flag used for caching of \f$ B^+ \to K^+ \mu^+ \mu^- \f$.
    mutable bool update_BpKel; ///< A flag used for caching of \f$ B^+ \to K^+ \e^+ \e^- \f$.
    mutable bool update_BdKstgamma;
    mutable bool update_BpKstgamma;
    mutable bool update_Bsphigamma;
    mutable bool fullKD;
};

/**
 * @}
 */

#endif /* FLAVOUR_H */
