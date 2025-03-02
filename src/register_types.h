/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#ifndef EXAMPLE_REGISTER_TYPES_H
#define EXAMPLE_REGISTER_TYPES_H

#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_util_lib(ModuleInitializationLevel p_level);
void uninitialize_util_lib(ModuleInitializationLevel p_level);

#endif // EXAMPLE_REGISTER_TYPES_H
