#ifndef heatControl
#define heatControl

#include <stdbool.h>

typedef enum {
    STATE_IDLE,
    STATE_STARTUP,
    STATE_RUN,
    STATE_ERROR
} SystemState;

void gpio_init(void);
void system_idle(void);
bool system_startup(void);
bool system_run(void);
void handle_error(void);
void gpio_init(void);


#endif
