/* Includes ------------------------------------------------------------------*/
#include "timer_handles.h"
#include "key_scaner.h"

void KeyDownHandler(void);
void Time2Handler(){
	keyScanner();
	KeyDownHandler();
}

void Time3Handler(){
}
