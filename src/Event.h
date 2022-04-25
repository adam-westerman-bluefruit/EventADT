#ifndef _Event_H_
#define _Event_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct Event* EventPtr;

void Events_system_init(void);
void Event_invoke(EventPtr event);
uint32_t Event_addListener(EventPtr event, void (*ptr)(void));
uint32_t Event_removeListener(EventPtr event, void (*ptr)(void));
void Event_wipeAllListener(EventPtr event);
uint32_t Event_internal_getElementIndex(EventPtr event, void (*ptr)(void));
EventPtr Event_createNew(void);
bool Event_destroy(EventPtr event);
uint8_t Event_getTotalEvents();

#endif