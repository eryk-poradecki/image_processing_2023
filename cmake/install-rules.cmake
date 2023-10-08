install(
    TARGETS img_exe
    RUNTIME COMPONENT img_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
