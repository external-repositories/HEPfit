/*
 * Copyright (C) 2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef MCHARGINO_H
#define	MCHARGINO_H

#include <ThObservable.h>
#include <ThObsType.h>
#include "SUSY.h"

class Mchargino : public ThObservable {
public:

    Mchargino(const ThObsType& ObsType, const int ind)
    : ThObservable(ObsType), index(ind)
    {
    };

    double getThValue()
    {
        return ((static_cast<const SUSY*> (&SM))->getMch()(index));
    };

private:
    const int index;

};

#endif	/* MCHARGINO_H */

