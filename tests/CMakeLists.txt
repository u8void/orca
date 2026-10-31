enable_testing()

add_executable(orca_decoder_test
    test_decoder.c
)

target_link_libraries(orca_decoder_test PRIVATE orca_core)

add_test(
    NAME orca_decoder_test
    COMMAND orca_decoder_test
)
