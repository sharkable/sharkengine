LOCAL_PATH := /

include $(CLEAR_VARS)

LOCAL_MODULE := sharkengine

LOCAL_CFLAGS := -DANDROID_NDK \
                -DDISABLE_IMPORTGL \
                -include ../src/jni/AirHockey_Prefix.pch

LOCAL_CPPFLAGS += -std=gnu++0x -frtti

LOCAL_C_INCLUDES += \
    $(SHARKENGINE_APP_HOME)/src \
    $(SHARKENGINE_HOME)/core/src \
    $(SHARKENGINE_HOME)/core/include \
    $(SHARKENGINE_HOME)/platforms/android/src

LOCAL_CPP_EXTENSION := .cc .cpp

LOCAL_SRC_FILES := \
    $(SHARKENGINE_APP_SOURCE) \
    $(SHARKENGINE_HOME)/platforms/android/src/jni/app-android.c \
    $(SHARKENGINE_HOME)/platforms/android/src/jni/airhockey.cc \
    $(SHARKENGINE_HOME)/platforms/android/src/gameengine/android/modules/android_ad_engine.cc \
    $(SHARKENGINE_HOME)/platforms/android/src/gameengine/android/modules/android_analytics_engine.cc \
    $(SHARKENGINE_HOME)/platforms/android/src/gameengine/android/modules/android_app_store_engine.cc \
    $(SHARKENGINE_HOME)/platforms/android/src/gameengine/android/modules/android_asset_reader.cc \
    $(SHARKENGINE_HOME)/platforms/android/src/gameengine/android/modules/android_game_engine_factory.cc \
    $(SHARKENGINE_HOME)/platforms/android/src/gameengine/android/modules/android_local_store.cc \
    $(SHARKENGINE_HOME)/platforms/android/src/soundengine/sound_instance.cc \
    $(SHARKENGINE_HOME)/platforms/android/src/soundengine/sound_player.cc \
    $(SHARKENGINE_HOME)/platforms/android/src/soundengine/sound_type.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/animation.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/engine_view.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/entities/animatable.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/entities/button.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/entities/composite_entity.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/entities/multi_select.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/entities/simple_item.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/game_engine.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/opengl/texture2d.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/positions.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/resource_loader.cc \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_add.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_add_dir.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_close.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_delete.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_dirent.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_entry_free.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_entry_new.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_err_str.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_error.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_error_clear.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_error_get.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_error_get_sys_type.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_error_strerror.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_error_to_str.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_fclose.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_file_error_clear.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_file_error_get.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_file_get_offset.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_file_strerror.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_filerange_crc.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_fopen.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_fopen_index.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_fread.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_free.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_get_archive_comment.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_get_archive_flag.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_get_file_comment.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_get_num_files.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_get_name.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_memdup.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_name_locate.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_new.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_open.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_rename.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_replace.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_set_archive_comment.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_set_archive_flag.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_set_file_comment.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_source_buffer.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_source_file.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_source_filep.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_source_free.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_source_function.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_source_zip.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_set_name.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_stat.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_stat_index.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_stat_init.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_strerror.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_unchange.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_unchange_all.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_unchange_archive.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/libzip/zip_unchange_data.c \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Back.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Bounce.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Circ.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Cubic.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Elastic.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Expo.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Linear.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Quad.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Quart.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Quint.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/PennerEasing/Sine.cpp \
    $(SHARKENGINE_HOME)/core/src/gameengine/thirdparty/tinyxml2/tinyxml2.cpp

LOCAL_LDLIBS := -lGLESv1_CM -lOpenSLES -landroid -ldl -llog -lz

include $(BUILD_SHARED_LIBRARY)
