#include  "itcfunc.h"
int main(){
    
	lcd_ttyopen(1);
    
	game();
	
    lcd_nextline();
    lcd_ttyclose();
    while (1);
    return 0;
}
