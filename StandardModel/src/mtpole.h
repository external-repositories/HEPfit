/* 
 * Copyright (C) 2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef MTPOLE_H
#define	MTPOLE_H

#include <ThObservable.h>
#include <ThObsType.h>
#include "QCD.h"

class mtpole : public ThObservable {
public:

    mtpole(const ThObsType& ObsType) 
    : ThObservable(ObsType) 
    {
    };
    
    double getThValue()
    {
        return SM.getMtpole();
    };

private:

};

#endif	/* MTPOLE_H */

