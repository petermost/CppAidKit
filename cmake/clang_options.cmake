function(set_default_clang_target_options targetName)
    message("Setting default Clang options for target '${targetName}")

    target_compile_options(${targetName}
        PRIVATE
            -Wall -Wextra -Wpedantic
            -Weverything

            -Wno-c++98-compat -Wno-c++98-compat-pedantic
            -Wno-format-nonliteral
            -Wno-exit-time-destructors -Wno-global-constructors
            -Wno-padded
            -Wno-redundant-parens
            -Wno-covered-switch-default
            -Wno-switch-enum
            -Wno-used-but-marked-unused
            -Wno-missing-prototypes
    )
endfunction()
