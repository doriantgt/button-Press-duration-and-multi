//
//  premadeCompares.hpp
//  buttonpresslib
//
//  Created by Dorian Tolman on 12/23/20.
//  Copyright © 2020 Dorian Tolman. All rights reserved.
//

#ifndef defualtComparesCodes_hpp
#define defualtComparesCodes_hpp
#include <stdio.h>
#include <iostream>
//#include "multiPressGroup.h"
#include "multiPressGroupCleaned.h"

#include "buttonduration.h"

//the press coder is the "sender" this is THE button value

//PressCoder(int code value, int press time);
PressCoder defualtPressCodes[3] = {PressCoder(1, 20), //debounce/click down
                                   PressCoder(2, 500), //Lpress long press
                                   PressCoder(3, 1500) //Hpress //hold press
};


//the button comps are the recievers
ButComp notPressed(0,0,Always);
ButComp clickDown(2, 1,Once);
ButComp LpressDown(2,2,Once);
ButComp HpressDown(2,3,Once);

ButComp clickUp(3, 1,Once);
ButComp LpressUp(3,2,Once);
ButComp HpressUp(3,3,Once);

ButComp clickUpAlways(3, 1,Always);
ButComp LpressUpAlways(3,2,Always);
ButComp HpressUpAlways(3,3,Always);

ButComp clickDownUse(2, 1,Use);
ButComp clickUpUse(3, 1,Use);

ButComp LpressDownUse(2,2,Use);
ButComp HpressDownUse(2,3,Use);

//arrays of pointers to butComps should use less data then arrays of butComps
ButComp  *clickClick [3] = {&clickUp, &clickUp, &notPressed};
ButComp  *LpressLpress [3] = {&LpressUp, &LpressUp, &notPressed};
ButComp  *clickClickClick [3] = {&clickUp, &clickUp, &clickUp};

MultiCompareGroup clickClickComp(clickClick,3);
MultiCompareGroup clickClickClickComp(clickClickClick,3);
MultiCompareGroup LpressLpressComp(LpressLpress,3);



#endif /* premadeCompares_hpp */
