#include "functions.h"
#include "../constants/constants.h"

void handleCorners( Sprite head, int *x_move, int *y_move )
{
// jesli idzie w lewo i trafi na lewa krawedz
    if( ( x_move == -1 ) && ( head.x_pos == 0 ) ){
        // jesli jest na gornej krawedzi, nie moze isc w swoje prawo
        if( head.y_pos == 0){
            x_move = 0;
            y_move = 1;
        }
        else{
            x_move = 0;
            y_move = -1;
        }

    }
    // idzie w prawo i prawa kwawedz
    if( ( x_move == 1 ) && ( head.x_pos == X_BORDER - 1 ) ){
        if( head.y_pos == Y_BORDER - 1){
            x_move = 0;
            y_move = -1;
        }
        else{
            x_move = 0;
            y_move = 1;
        }
    }
    // idzie w gore i gorna krawedz
    if( ( y_move == -1 ) && ( head.y_pos == 0 ) ){
        if( head.x_pos == X_BORDER - 1){
            x_move = -1;
            y_move = 0;
            printf("DEBUG \n");
        }
        else{
            x_move = 1;
            y_move = 0;
        }
    }
    // idzie w dol i dolna krawedz
    if( ( y_move == 1 ) && ( head.y_pos == Y_BORDER - 1 ) ){
        if( head.x_pos == 0){
            x_move = 1;
            y_move = 0;
        }
        else{
            x_move = -1;
            y_move = 0;
        }
    }
}