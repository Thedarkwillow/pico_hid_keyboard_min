include(FetchContent)
set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk" CACHE PATH "Pico SDK path")
if (NOT EXISTS "${PICO_SDK_PATH}/pico_sdk_init.cmake")
  FetchContent_Declare(pico_sdk
    GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk.git
    GIT_TAG 1.5.1)
  FetchContent_MakeAvailable(pico_sdk)
  set(PICO_SDK_PATH ${pico_sdk_SOURCE_DIR} CACHE PATH "" FORCE)
endif()
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
