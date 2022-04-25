#include <gtest/gtest.h>
extern "C"
{
    #include "../src/Event.h"
    #include "../src/Methods.h"
}

TEST(EventSystem, create_event_through_struct)
{
    // Given
    Events_system_init();

    // When
    EventPtr customEvent_a = Event_createNew();
    
    // Then
    ASSERT_EQ(1, Event_getTotalEvents());
}

TEST(EventSystem, add_listener_to_event)
{
    // Given
    Events_system_init();
    Method_reset();
    EventPtr customEvent_b = Event_createNew();
    Event_addListener(customEvent_b,&Method_step_a);

    // When
    Event_invoke(customEvent_b);
    
    // Then
    ASSERT_EQ(1, get_val_a());
}

TEST(EventSystem, remove_listener_from_event)
{
    // Given
    Events_system_init();
    Method_reset();
    EventPtr customEvent_c = Event_createNew();
    Event_addListener(customEvent_c,&Method_step_a);
    Event_addListener(customEvent_c,&Method_step_b);

    // When
    Event_invoke(customEvent_c);
    Event_removeListener(customEvent_c,&Method_step_a);
    Event_invoke(customEvent_c);

    // Then
    ASSERT_EQ(1, get_val_a());
    ASSERT_EQ(2, get_val_b());
}