set(sf_mulitmedia_cameraextensions_SRCS
  effectsmodel.cpp
  exposuremodel.cpp
  flashmodel.cpp
  focusmodel.cpp
  isomodel.cpp
  resolutionmodel.cpp
  whitebalancemodel.cpp
)

add_library(SFMultimediaCameraExtensions SHARED
  ${sf_mulitmedia_cameraextensions_SRCS})

target_include_directories(SFMultimediaCameraExtensions
  PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
  "$<BUILD_INTERFACE:${SFMultimediaCameraExtensions_BINARY_DIR}>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/sfmultimediacameraextensions>"
  INTERFACE
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfmultimediacameraextensions>"
  )

target_link_libraries(SFMultimediaCameraExtensions
  PUBLIC
  Qt5::Core
  Qt5::Multimedia
  )

set_target_properties(SFMultimediaCameraExtensions
  PROPERTIES
  VERSION ${SFMultimediaCameraExtensions_VERSION_STRING}
  SOVERSION ${SFMultimediaCameraExtensions_SOVERSION}
  EXPORT_NAME SFMultimediaCameraExtensions
  )

install(TARGETS SFMultimediaCameraExtensions
  EXPORT
  SFMultimediaCameraExtensionsTargets
  ${KF5_INSTALL_TARGETS_DEFAULT_ARGS}
  )

#add_library(Sailfish::Multimedia::CameraExtensions shared
#  ALIAS SFMultimediaCameraExtensions)

generate_export_header(SFMultimediaCameraExtensions
  EXPORT_FILE_NAME
  ${SFMultimediaCameraExtensions_BINARY_DIR}/sfmultimediacameraextensions/SFMultimediaCameraExtensions_export.h
  BASE_NAME
  SFMultimediaCameraExtensions
  )
ecm_generate_headers(SFMultimediaCameraExtensions_CamelCase_HEADERS
    HEADER_NAMES
        IsoModel
        FlashModel
        ResolutionModel
        WhiteBalanceModel
        FocusModel
        ExposureModel
        EffectsModel
    REQUIRED_HEADERS SFMultimediaCameraExtensions_HEADERS
    PREFIX SFMultimediaCameraExtensions
)

install(FILES ${SFMultimediaCameraExtensions_CamelCase_HEADERS}
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/sfmultimediacameraextensions/SFMultimediaCameraExtensions/
  COMPONENT Devel)
install(FILES
  ${SFMultimediaCameraExtensions_BINARY_DIR}/sfmultimediacameraextensions/SFMultimediaCameraExtensions_export.h
  ${SFMultimediaCameraExtensions_HEADERS}
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/sfmultimediacameraextensions/sfmultimediacameraextensions
  COMPONENT
  Devel
)


add_subdirectory(quick)
