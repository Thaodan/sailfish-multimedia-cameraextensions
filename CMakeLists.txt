project(SFMultimediaCameraExtensions)

cmake_minimum_required(VERSION 3.10)
set(QT_MIN_VERSION "5.6.0")


include(FeatureSummary)
include(GenerateExportHeader)

find_package(ECM 0.0.8 REQUIRED NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED
  DESCRIPTION "Extra CMake Modules."
  URL "https://commits.kde.org/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND
  FATAL_ON_MISSING_REQUIRED_PACKAGES)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${ECM_MODULE_PATH}
  ${ECM_KDE_MODULE_DIR})

include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMGenerateQmlTypes)

include(KDEInstallDirs)

set(SFMultimediaCameraExtensions_VERSION 0.1.0)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS
  Core
  Multimedia
  Quick)

ecm_setup_version(${SFMultimediaCameraExtensions_VERSION}
  VARIABLE_PREFIX
  SFMultimediaCameraExtensions
  VERSION_HEADER
  "${CMAKE_CURRENT_BINARY_DIR}/SFMultimediaCameraExtensions_version.h"
  PACKAGE_VERSION_FILE
  "${CMAKE_CURRENT_BINARY_DIR}/SFMultimediaCameraExtensionsConfigVersion.cmake"
  SOVERSION
  1
  )



set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR
  "${KDE_INSTALL_CMAKEPACKAGEDIR}/SFMultimediaCameraExtensions")

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/SFMultimediaCameraExtensionsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/SFMultimediaCameraExtensionsConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
  )

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/SFMultimediaCameraExtensionsConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/SFMultimediaCameraExtensionsConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
  )

install(EXPORT SFMultimediaCameraExtensionsTargets
  DESTINATION
  "${CMAKECONFIG_INSTALL_DIR}"
  FILE SFMultimediaCameraExtensionsTargets.cmake
  NAMESPACE Sailfish::Multimedia:: )

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/SFMultimediaCameraExtensions_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR}/sfmultimediacameraextensions COMPONENT Devel
  )


feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
