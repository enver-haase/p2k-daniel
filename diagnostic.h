
#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include "main.h"

void init_diagnostic(void);
void start_diagnostic(void);
SWITCH_FUNCTION* diagnostic_switch_matrix_function(void);
SWITCH_FUNCTION* diagnostic_direct_switch_function(void);

#endif //DIAGNOSTIC.H
