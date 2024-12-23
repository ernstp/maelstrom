
/*  A simple menu button class -- only handles mouse input */

#include "SDL_types.h"


class ButtonList {

public:
	typedef struct _button {
		/* Sensitive area */
		Uint16 x1, y1;
		Uint16 x2, y2;
		void (*callback)(void);
		struct _button *next;
	} button;
	ButtonList() {
		button_list.next = NULL;
	}
	~ButtonList() {
		Delete_Buttons();
	}

	void Add_Button(Uint16 x, Uint16 y, Uint16 width, Uint16 height, 
						void (*callback)(void)) {
		button *belem;
		
		for ( belem=&button_list; belem->next; belem=belem->next );
		belem->next = new button;
		belem = belem->next;
		belem->x1 = x;
		belem->y1 = y;
		belem->x2 = x+width;
		belem->y2 = y+height;
		belem->callback = callback;
		belem->next = NULL;
	}

	void Activate_Button(Uint16 x, Uint16 y) {
		button *belem;

		for ( belem=button_list.next; belem; belem=belem->next ) {
			if ( (x >= belem->x1) && (x <= belem->x2) &&
			     (y >= belem->y1) && (y <= belem->y2) ) {
				if ( belem->callback )
					(*belem->callback)();
			}
		}
	}

	void Delete_Buttons(void) {
		button *belem, *btemp;

		for ( belem=button_list.next; belem; ) {
			btemp = belem;
			belem = belem->next;
			delete btemp;
		};
		button_list.next = NULL;
	}
	
private:
	button button_list;
};
