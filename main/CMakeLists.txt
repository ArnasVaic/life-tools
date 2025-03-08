add_executable(main
    main.c
)

target_link_libraries(main
    module_a
)

if(TARGET_GROUP STREQUAL release)
    target_compile_options(main PRIVATE -O2 -DNDEBUG)

elseif(TARGET_GROUP STREQUAL debug)
    target_compile_options(main PRIVATE
        -g                             # Debug symbols
        -O0                            # No optimization (easier debugging)
        -Wall -Wextra -Wpedantic       # Strict warnings
        -Werror                        # Treat warnings as errors
        -Wshadow                       # Warn when a variable shadows another
        -Wconversion                   # Warn on implicit type conversions
        -Wsign-conversion              # Warn on signed/unsigned mismatches
        -Wnull-dereference             # Warn on dereferencing NULL
        -Wdouble-promotion             # Warn when float is promoted to double
        -Wformat=2                     # Stricter format warnings
        -Wimplicit-fallthrough         # Warn when fallthrough in switch cases isn't annotated
        -Wstrict-aliasing              # Warn about unsafe type punning
        -Wunreachable-code             # Warn on code that will never be executed
        -Wthread-safety                # Warn on potential thread safety issues
        # -fsanitize=address,undefined   # AddressSanitizer + UndefinedBehaviorSanitizer
        -fsanitize=leak                # Detect memory leaks
        # -fsanitize=memory              # Detect uninitialized memory usage
        -fstack-protector-strong       # Enable stack smashing protection
        -fno-omit-frame-pointer        # Keep frame pointer for better debugging
    )

endif()
