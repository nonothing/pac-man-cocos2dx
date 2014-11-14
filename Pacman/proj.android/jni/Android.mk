LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/Controller/SoundController.cpp\
				   ../../Classes/View/LevelMenuScene.cpp\
				   ../../Classes/View/MainMenuScene.cpp\
				   ../../Classes/View/WorldScene.cpp\
				   ../../Classes/View/AbstractScene.cpp\
				   ../../Classes/Model/Brick.cpp\
				   ../../Classes/Model/Player.cpp\
				   ../../Classes/Model/Point.cpp\
				   ../../Classes/Model/PButton.cpp\
				   ../../Classes/Model/Rectangle.cpp\
				   ../../Classes/Model/ReadLevel.cpp\
				   ../../Classes/Model/World.cpp\
				   ../../Classes/Model/LevelMenu.cpp\
				   ../../Classes/Model/Level.cpp\
				   ../../Classes/Model/WorldObject.cpp\
				   ../../Classes/Model/WorldObjectMove.cpp\
				   ../../Classes/Model/Spirit/Spirit.cpp\
				   ../../Classes/Model/Spirit/Blinky.cpp\
				   ../../Classes/Model/Spirit/Pinky.cpp\
				   ../../Classes/Model/Spirit/Inky.cpp\
				   ../../Classes/Model/Spirit/Clyde.cpp\
				   ../../Classes/Controller/WorldController.cpp\
				   ../../Classes/Controller/MenuController.cpp\
				  
				   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
