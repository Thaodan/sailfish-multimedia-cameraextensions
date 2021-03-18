add_library(sf_multimedia_cameraextensions_quickplugin
  sf_mulitmedia_cameraextensions_quickplugin.cpp)

target_link_libraries(sf_multimedia_cameraextensions_quickplugin Qt5::Qml SFMultimediaCameraExtensions)
set(bindest "${CMAKE_BINARY_DIR}/bin/qml/org/sailfishos/multimedia/cameraextensions")
set_target_properties(sf_multimedia_cameraextensions_quickplugin
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${bindest}")

add_custom_target(moveqmldir ALL
  COMMAND
  cmake -E make_directory -p ${bindest}
  COMMAND
  cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${bindest})

install(TARGETS sf_multimedia_cameraextensions_quickplugin
  DESTINATION
  ${KDE_INSTALL_QMLDIR}/org/sailfishos/multimedia/cameraextensions)
install(FILES qmldir
  DESTINATION
  ${KDE_INSTALL_QMLDIR}/org/sailfishos/multimedia/cameraextensions)



ecm_generate_qmltypes(org.sailfishos.multimedia.cameraextensions 1.0
  DESTINATION
  ${KDE_INSTALL_QMLDIR}/org/sailfishos/multimedia/cameraextensions)
