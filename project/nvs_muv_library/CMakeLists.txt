set(COMPONENT_SRCS
    "src/nvs_storage.c")

set(COMPONENT_ADD_INCLUDEDIRS "include")

#set(COMPONENT_REQUIRES "nvs_driver")

set(COMPONENT_PRIV_REQUIRES main nvs_flash)

register_component(nvs_muv_library)

component_compile_options(PUBLIC -DMPU_COMPONENT_TRUE=1)
