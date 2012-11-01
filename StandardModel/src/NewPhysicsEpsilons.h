/* 
 * File:   NewPhysicsEpsilons.h
 * Author: mishima
 */

#ifndef NEWPHYSICSEPSILONS_H
#define	NEWPHYSICSEPSILONS_H

#include "StandardModel.h"


class NewPhysicsEpsilons : public StandardModel  {
public:
    static const int NEPSILONvars = 4;
    static const std::string EPSILONvars[NEPSILONvars];
    
    /**
     * @brief NewPhysicsEpsilons constructor
     */
    NewPhysicsEpsilons();

    virtual std::string ModelName() const {
        return "NewPhysicsEpsilons";
    }

    virtual bool Update(const std::map<std::string, double>& DPars);
    virtual bool Init(const std::map<std::string, double>& DPars);    
    virtual bool CheckParameters(const std::map<std::string, double>& DPars);


    ////////////////////////////////////////////////////////////////////////     

    double GetMyEpsilon_1() const {
        return myEpsilon_1;
    }

    double GetMyEpsilon_2() const {
        return myEpsilon_2;
    }

    double GetMyEpsilon_3() const {
        return myEpsilon_3;
    }

    double GetMyEpsilon_b() const {
        return myEpsilon_b;
    }

    double epsilon1() const {
        return myEpsilon_1;
    }

    double epsilon2() const {
        return myEpsilon_2;
    }

    double epsilon3() const {
        return myEpsilon_3;
    }

    double epsilonb() const {
        return myEpsilon_b;
    }    
    

    ////////////////////////////////////////////////////////////////////////     
    
    /**
     * @return the W boson mass
     */
    virtual double Mw() const;

    /**
     * @return Mw^2/Mz^2
     */
    virtual double cW2() const;
    
    /**
     * @return 1-Mw^2/Mz^2
     */
    virtual double sW2() const;
    
    /**
     * @brief effective coupling rho_Z^l
     * @param[in] l lepton
     * @return rho_Z^l
     */
    virtual complex rhoZ_l(const StandardModel::lepton l) const;
    
    /**
     * @brief effective coupling rho_Z^q
     * @param[in] q quark
     * @return rho_Z^q
     */
    virtual complex rhoZ_q(const StandardModel::quark q) const;

    /**
     * @brief effective coupling kappa_Z^l
     * @param[in] l name of lepton
     * @return kappa_Z^l in the SM
     */
    virtual complex kappaZ_l(const StandardModel::lepton l) const;

    /**
     * @brief effective coupling kappa_Z^q
     * @param[in] q name of quark
     * @return kappa_Z^q in the SM
     */
    virtual complex kappaZ_q(const StandardModel::quark q) const;       
    
    /**
     * @brief vector effective coupling for neutral-current interactions
     * @param[in] l lepton
     * @return g_V^l
     */
    virtual complex gVl(const StandardModel::lepton l) const;

    /**
     * @brief vector effective coupling for neutral-current interactions
     * @param[in] q quark
     * @return g_V^q
     */
    virtual complex gVq(const StandardModel::quark q) const;

    /**
     * @brief axial-vector effective coupling for neutral-current interactions
     * @param[in] l lepton
     * @return g_A^l
     */
    virtual complex gAl(const StandardModel::lepton l) const;

    /**
     * @brief axial-vector effective coupling for neutral-current interactions
     * @param[in] q quark
     * @return g_A^q
     */
    virtual complex gAq(const StandardModel::quark q) const; 
    
    /**
     * @return the total width of the W boson
     */
    virtual double GammaW() const;    

    
    ////////////////////////////////////////////////////////////////////////   

protected:    
    double myEpsilon_1, myEpsilon_2, myEpsilon_3, myEpsilon_b;
    virtual void SetParameter(const std::string name, const double& value);
    
    
    ////////////////////////////////////////////////////////////////////////     
    
private:
    double Delta_rW() const;
    double Delta_kappaPrime() const;
 
    complex rhoZ_e() const;
    complex kappaZ_e() const;
    complex gVe() const;
    complex gAe() const;
    
};

#endif	/* NEWPHYSICSEPSILONS_H */

