#define PRINT_MEMORY_LAYOUT 0

#if PRINT_MEMORY_LAYOUT
#include "print_memory_layout.h"
#endif
#include "polymorphic_array.h"

int main() {
#if PRINT_MEMORY_LAYOUT
    print_memory_layout();
#endif
    print_polymorphic_array_examples();
}
