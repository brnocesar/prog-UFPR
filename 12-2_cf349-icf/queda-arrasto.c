#include <stdio.h>
#include <math.h>

void main() {
    double dt, t,
        x, vx, ax,
        y, vy, ay, ymax,
        v, teta, rad;

    dt = 0.00001;
    for (teta=0; teta<=90; teta=teta+5) {

        x=0, vx=0, ax=0,
        y=0, vy=0, ay=-10.0, ymax=0,
        v=100, rad=M_PI/180.0;
        vx = v*cos(teta*rad);
        vy = v*sin(teta*rad);

        for (t=0; t<=100; t=t+dt) {

            //printf("%g\t %g\t %g\t %g\t %g\n", t, x, y, vx, vy);

            if(y<0) break; // projetil chega ao nivel 0, para de calcular

            x  =  x + vx * dt;
            y  =  y + vy * dt;
            vx = vx + ax * dt;
            vy = vy + ay * dt;

            if (ymax<y) ymax=y;
        }

        //printf("angulo=%g\t tempo=%g\t alcance=%g\t altura_maxima=%g\n",teta, t, x, ymax); //grandezas e valores
        printf("%g\t %f\t %f\t %f\n",teta, t, x, ymax);
    }
}
