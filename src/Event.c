#include "Event.h"
#include <stdio.h>
#include <string.h>

#define MAX_LISTNERS 16 
#define MAX_NAME_LENGTH 30

struct Event 
{
    void (*fun_ptr_arr[MAX_LISTNERS])(void); 
    uint8_t currentRegisteredListeners;
};

#define MAX_EVENTS 32

static struct Event mEventStorage[MAX_EVENTS];
static EventPtr mEventPointers[MAX_EVENTS];
static uint8_t mNextUnusedEvent;

static bool getElementIndex(EventPtr event, void (*ptr)(void), int* index);
static void wipeAllListeners(EventPtr event);



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
        return 0; 

    EventPtr evPtr = mEventPointers[mNextUnusedEvent];
    wipeAllListeners(evPtr);
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

uint8_t Event_addListener(EventPtr event, void (*ptr)(void))
{
    if(event->currentRegisteredListeners >= MAX_LISTNERS) 
        return -1;

    event->fun_ptr_arr[event->currentRegisteredListeners++] = ptr;
    return 0;
}

uint8_t Event_removeListener(EventPtr event, void (*ptr)(void))
{
    int i;
    if(!getElementIndex(event,ptr,&i))
        return -1;
    
    event->fun_ptr_arr[i] = (NULL);
    
    for (size_t i = 0; i < event->currentRegisteredListeners; i++)
    {
        if(event->fun_ptr_arr[i] != NULL) continue;
        if(i+1 < event->currentRegisteredListeners) 
        {
            event->fun_ptr_arr[i] = event->fun_ptr_arr[i+1];
            event->fun_ptr_arr[i+1] = NULL;
        } 
    }
    event->currentRegisteredListeners--; 
    return 0;
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

void wipeAllListeners(EventPtr event)
{
    for (size_t i = 0; i < event->currentRegisteredListeners; i++)
    {
        event->fun_ptr_arr[i] = NULL;
    }
    event->currentRegisteredListeners = 0;
}

static bool getElementIndex(EventPtr event, void (*ptr)(void), int* index)
{
    for (size_t i = 0; i < event->currentRegisteredListeners; i++)
    {
        if(event->fun_ptr_arr[i] == ptr)
        {
            *index = i;
            return true;
        }
    }
    return false;
}
