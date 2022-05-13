#include "base/base.h"
#include "base/move.h"
#include "base/pid.h"
#include "base/color.h"
#include "shifter/shifter.h"
#include "module/module.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    base b;
    pid ctl;
    shifter s;
    color cs_f, cs_s;

    b = baseNew('D', 'A', '1');
    ctl = pidNew(0.0, 25.0, 25.0, 0.0);
    s = shifterNew('B', 'C');
    cs_f = colorNew('4');
    cs_s = colorNew('3');

    colorProfileLoad(&cs_f, "../data/profile_k_F", "../data/profile_l_F");
    colorProfileLoad(&cs_s, "../data/profile_k_S", "../data/profile_l_S");

    getc(stdin);
/*
    moveTimed(b, 600, 1.5, &ctl, FWD, NS_STD);
    moveLine(b, 500, cs_f, cs_s, 100.0, 8.0, -41, FWD, LBRW, NS_STD);
    moveColor(b, 100, cs_s, 0, 10.0, &ctl, FWD, NS_STD);

    moduleDrive(s, -530, 3);
    moduleDrive(s,  180, 2);
    
    moduleDrive(s,  550, 1);
    sleep(0.5);
    moduleDrive(s, -550, 1);
    moduleDrive(s,  550, 1);

    moduleDrive(s,  530, 3);
    moveTimed(b, 600, 0.3, &ctl, FWD, NS_STD);
    moduleDrive(s, -180, 2);

    moveTimed(b, 900, 1.0, &ctl, BWD, NS_STD);

    shifterShift(s, 0);
*/


    moduleDrive(s, 450, 3);
    moveTimed(b, 300, 0.8, &ctl, FWD, NS_STD);
    rotate(b, -50, 400);

    moveColor(b, 500, cs_s, 0, 7, &ctl, FWD, NS_INI);
    moveColor(b, 200, cs_s, 100, 20, &ctl, FWD, NS_FIN);
    moveTimed(b, 200, 1.6, &ctl, FWD, NS_STD);
    rotate(b, -38, 400);

    moveColor(b, 500, cs_s, 0, 5, &ctl, FWD, NS_INI);

    //bridge
    moveColor(b, 500, cs_s, 100, 20, &ctl, FWD, NS_FIN);
    rotate(b, -2, 400);
    moveColor(b, 500, cs_s, 7, 5, &ctl, FWD, NS_INI);    
    moveColor(b, 500, cs_s, 0, 5, &ctl, FWD, NS_FIN);
    moveTimed(b, 500, 0.7, &ctl, FWD, NS_STD);
    moveTimed(b, 500, 1, &ctl, BWD, NS_STD);
    moveTimed(b, 500, 1.4, &ctl, FWD, NS_STD);
    
    //inno project
    moduleDrive(s, -120, 2);

/*
    moveColor(b, 500, cs_s, 0, 5, &ctl, BWD, NS_STD);
    moduleDrive(s, -270, 3);
    moduleDrive(s, 270, 3);
*/
    shifterShift(s, 0);

    return 0;
}