target_sources(
  firmware
  PRIVATE fatfs.cpp
          filesystem.cpp
          filesystem_fatfs.cpp
          filesystem_littlefs.cpp
          filesystem_littlefs_bbf.cpp
          filesystem_littlefs_internal.cpp
          filesystem_root.cpp
          filesystem_semihosting.cpp
          libsysbase_syscalls.cpp
          littlefs_bbf.cpp
          littlefs_internal.cpp
          logging.cpp
          lwip.cpp
          main.cpp
          timing_sys.cpp
          usb_device.cpp
          usb_device_cdc.cpp
          usb_device_msc.cpp
          usb_host.cpp
          usbh_conf.cpp
          usbh_diskio.cpp
  )

set_property(
  SOURCE src/main.cpp
  APPEND
  PROPERTY COMPILE_DEFINITIONS HAS_MMU2=$<BOOL:${HAS_MMU2}>
  )
