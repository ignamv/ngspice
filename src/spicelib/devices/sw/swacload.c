/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Gordon Jacobs
**********/
/*
 */

#include "ngspice/ngspice.h"
#include "ngspice/cktdefs.h"
#include "swdefs.h"
#include "ngspice/sperror.h"
#include "ngspice/suffix.h"


int
SWacLoad(GENmodel *inModel, CKTcircuit *ckt)
        /* load the current values into the 
         * sparse matrix previously provided 
         * during AC analysis.
         */
{
    SWmodel *model = (SWmodel *)inModel;
    SWinstance *here;
    double g_now;
    int current_state;

    /*  loop through all the switch models */
    for( ; model != NULL; model = model->SWnextModel ) {

        /* loop through all the instances of the model */
        for (here = model->SWinstances; here != NULL ;
                here=here->SWnextInstance) {

            /* In AC analysis, just propogate the state... */

            current_state = (int)*(ckt->CKTstate0 + here->SWstate);

            g_now = current_state?(model->SWonConduct):(model->SWoffConduct);

            *(here->SWposPosPtr) += g_now;
            *(here->SWposNegPtr) -= g_now;
            *(here->SWnegPosPtr) -= g_now;
            *(here->SWnegNegPtr) += g_now;
        }
    }
    return(OK);
}
