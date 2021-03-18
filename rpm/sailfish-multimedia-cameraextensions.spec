Name:       sailfish-multimedia-cameraextensions
Summary:    Sailfish Multimedia Camera Helper Library
Version:    0.1
Release:    0
License:    LGPLv2+
URL:        https://bitbucket.org/jolla/ui-jolla-camera
Source0:    %{name}-%{version}.tar.bz2

BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Multimedia)
BuildRequires:  cmake
BuildRequires:  extra-cmake-modules
BuildRequires:  qt5-qtdeclarative-devel-tools
%description
This is a small QML plugin to make working with the Qt Multimedia Camera easier
on Sailfish OS.


%package devel
Summary:    Development files for SFMultimediaCameraExtensions
Requires:   %{name} = %{version}-%{release}

%description devel
This package contains the files necessary to develop
applications using %{name}


%prep
mkdir -p build
%setup -q -n %{name}-%{version}

%build
%cmake -B build
%make_build -C build

%install
cd build
%make_install

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/libSFMultimediaCameraExtensions.so.*
%{_libdir}/qt5/qml/org/sailfishos/multimedia/*

%files devel
%defattr(-,root,root,-)
%{_includedir}/sfmultimediacameraextensions/*
#%{_datadir}/qt5/mkspecs/modules/qt_KCalendarCore.pri
%{_libdir}/cmake/SFMultimediaCameraExtensions/*
%{_libdir}/libSFMultimediaCameraExtensions.so
#%{_libdir}/pkgconfig/KF5CalendarCore.pc
