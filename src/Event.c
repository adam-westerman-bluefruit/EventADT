#include "Event.h"
#include <stdio.h>
#include <string.h>

#define MAX_LISTNERS 16 
#define MAX_NAME_LENGTH 30

struct Event 
{
    void (*fun_ptr_arr[MAX_LISTNERS])(void); // 8*16 = 128
    uint8_t currentRegisteredListeners; // 8
};

#define MAX_EVENTS 32

static struct Event mEventStorage[MAX_EVENTS]; // 136 * 32 = 4,352 ?
static EventPtr mEventPointers[MAX_EVENTS]; // 8*32
static uint8_t mNextUnusedEvent;

// allocate some space to store deleted
static size_t pointerStorage;

void Events_system_init()
{
    for (size_t i = 0; i < MAX_EVENTS; i++)
    {
        mEventPointers[i] = &mEventStorage[i];
    }
    mNextUnusedEvent = 0;
}

EventPtr Event_createNew()
{
    if (mNextUnusedEvent >= MAX_EVENTS)
    return 0; // no more free events

    EventPtr evPtr = mEventPointers[mNextUnusedEvent];
    Event_wipeAllListener(evPtr);
    mNextUnusedEvent++;
    return evPtr;
}

bool Event_destroy(EventPtr event)
{
    if (mNextUnusedEvent <= 0)
    return false;

    mNextUnusedEvent--;
    mEventPointers[mNextUnusedEvent] = event;
    return true;
}

uint32_t Event_addListener(EventPtr event, void (*ptr)(void))
{
    if(event->currentRegisteredListeners >= MAX_LISTNERS) return -1;

    event->fun_ptr_arr[event->currentRegisteredListeners++] = ptr;
    return 0;
}

uint32_t Event_removeListener(EventPtr event, void (*ptr)(void))
{
    int i = Event_internal_getElementIndex(event,ptr);
    if(i==-1)return -1; // hop out if element doesnt exist
    event->fun_ptr_arr[i] = (NULL);
    
    for (size_t i = 0; i < event->currentRegisteredListeners; i++)
    {
        if(event->fun_ptr_arr[i] != NULL) continue;
        if(i+1 < event->currentRegisteredListeners) // end of array
        {
            event->fun_ptr_arr[i] = event->fun_ptr_arr[i+1];
            event->fun_ptr_arr[i+1] = NULL;
        } 
    }
    event->currentRegisteredListeners--; 
    return 0;
}

void Event_wipeAllListener(EventPtr event)
{
    if(event->currentRegisteredListeners == 0)return;
    //
    for (size_t i = 0; i < event->currentRegisteredListeners; i++)
    {
        event->fun_ptr_arr[i] = NULL;
    }
    event->currentRegisteredListeners = 0;
}

uint32_t Event_internal_getElementIndex(EventPtr event, void (*ptr)(void))
{
    for (size_t i = 0; i < event->currentRegisteredListeners; i++)
    {
        if(event->fun_ptr_arr[i] == ptr)
        {
            return i;
        }
    }
    return -1;
}

void Event_invoke(EventPtr event)
{
    for (size_t i = 0; i < event->currentRegisteredListeners; i++)
    {
        event->fun_ptr_arr[i](); // invoke listeners
    }
}


uint8_t Event_getTotalEvents()
{
    return mNextUnusedEvent;
}

