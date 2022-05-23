#include "base/base.h"
#include "base/move.h"
#include "base/pid.h"
#include "base/color.h"
#include "shifter/shifter.h"
#include "shifter/module.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    base b;
    pid ctl;
    shifter s;
    color cs_m, cs_l;

    b = baseNew('D', 'A', '1');
    ctl = pidNew(0.0, 25.0, 25.0, 0.0);
    s = shifterNew('B', 'C');
    cs_m = colorNew('4');
    cs_l = colorNew('3');

    colorProfileLoad(&cs_m, "../data/profile_k_F", "../data/profile_l_F");
    colorProfileLoad(&cs_l, "../data/profile_k_S", "../data/profile_l_S");

    getc(stdin);

    // get to line
    moduleAsyncDrive(s, -500, 2);
    moveTimed(b, 300, 0.4, &ctl, FWD, NS_STD);
    rotate(b, -50, 400);
    moveColor(b, 700, cs_l, 0.0, 7.0, &ctl, FWD, NS_INI);
    moveColor(b, 200, cs_l, 100.0, 20.0, &ctl, FWD, NS_FIN);
    moveTimed(b, 200, 2.0, &ctl, FWD, NS_STD);
    rotate(b, -38, 400);
    moduleAwaitDrive(s);
    shifterShift(s, 0);

    // move on line
    moveColor(b, 700, cs_m, 0.0, 8.0, &ctl, FWD, NS_INI);
    moveColor(b, 700, cs_m, 100.0, 20.0, &ctl, FWD, NS_MID);
    moveColor(b, 700, cs_m, 0.0, 8.0, &ctl, FWD, NS_FIN);
    moveTimed(b, 500, 2.4, &ctl, FWD, NS_STD);
    moveColor(b, 500, cs_l, 0.0, 8.0, &ctl, FWD, NS_STD);

    // put down boxes
    moduleDrive(s, -3960, 0);

    // go back
    moveTimed(b, 500, 0.3, &ctl, BWD, NS_STD); 

    // turn left and do the heli
    moduleDrive(s, -800, 3);
    moduleAsyncDrive(s, 3960, 0);
    rotate(b, 88, 400);
    moveTimed(b, 500, 0.7, &ctl, FWD, NS_STD);
    rotate(b, -60, 400);
    moveColor(b, 500, cs_l, 0.0, 7.0, &ctl, FWD, NS_INI);
    moveColor(b, 500, cs_l, 100.0, 20.0, &ctl, FWD, NS_FIN);
    moveTimed(b, 500, 0.15, &ctl, FWD, NS_STD);
    moduleAwaitDrive(s);
    moveTimed(b, 500, 0.3, &ctl, BWD, NS_STD);
    rotate(b, 60, 400);

    // put down forks
    moduleDrive(s, -900, 1);

    // reverse
    moveTimed(b, 200, 3.0, &ctl, BWD, NS_STD);

    // rail repair
    moduleDrive(s, 800, 3);
    moduleDrive(s, -800, 3);

    // raise forks
    moveTimed(b, 300, 0.05, &ctl, FWD, NS_STD);
    moduleDrive(s, 900, 1);

    // go fwd
    moveTimed(b, 500, 2.0, &ctl, FWD, NS_STD);
    
    // lower pusher stick
    moduleDrive(s, 500, 2);
    sleep(0.5);

    // reverse
    moveTimed(b, 800, 1.8, &ctl, BWD, NS_STD);

    // return
    moveTimed(b, 500, 1.2, &ctl, FWD, NS_STD);
    moduleDrive(s, -500, 2);
    rotate(b, -90, 400);
    moveTimed(b, 700, 3, &ctl, BWD, NS_STD);
    rotate(b, 30, 400);
    moveTimed(b, 700, 4, &ctl, FWD, NS_STD);

    shifterShift(s, 0);

    return 0;
}
