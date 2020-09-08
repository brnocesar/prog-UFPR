#include <stdio.h>
#include <math.h>

void main() {

    double dt, t,
        x, vx, ax,
        y, vy, ay, ymax,
        v, teta, g, b, rad;
    
    b  =    1;
    g  =   10;
    dt = 0.01;
    v  =  100;

    for (teta=0 ; teta<=90 ; teta=teta+1) {

        x   =               0;
        y   =               0;
        vx  =               0;
        vy  =               0; 
        rad =      M_PI/180.0; // radianos para graus
        vx  = v*cos(teta*rad);
        vy  = v*sin(teta*rad);
        
        for (t=0; t<=5000; t=t+dt) {

            // printf("%g\t %f\t %f\t %f\t %f\n", t, x, y, vx, vy);
            
            if (y<0) break; // projetil chega ao nivel 0, para de calcular
            
            ax =  0 -  b * vx ;
            ay = -g -  b * vy ;
            x  =  x + vx * dt ;
            y  =  y + vy * dt ;
            vx = vx + ax * dt ;
            vy = vy + ay * dt ;

            if (ymax<y) ymax=y ; //salva a maior altura
        }

        //printf("angulo=%g\t tempo=%g\t alcance=%g\t altura_maxima=%g\n",teta, t, x, ymax); //grandezas e valores
        printf("%f %f %f %f\n",teta, t, x, ymax); //somente valores
    }
}
