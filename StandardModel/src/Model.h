/* 
 * File:   Model.h
 * Author: marco
 *
 * Created on February 23, 2011, 3:48 PM
 */

#ifndef MODEL_H
#define	MODEL_H

#include <map>

class Model {
public:
    virtual void Update(const std::map<std::string, double>&) = 0;
    virtual bool CheckParameters(const std::map<std::string, double>&) = 0;
    virtual void SetParameter(const std::string, const double&) = 0;
    virtual bool Init(const std::map<std::string, double>&) = 0;

    virtual std::string ModelName() const = 0;
private:

};

#endif	/* MODEL_H */

