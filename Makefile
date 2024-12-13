CC = gcc
CPP := g++
AR := ar cru
RANLIB := ranlib 
RM := rm -rf

CPPFLAGS := 
CPPFLAGS += -I.   
CPPFLAGS += -g -O2
CPPFLAGS += -DWIN32
CPPFLAGS += -D_DEBUG
CPPFLAGS += -D_WINDOWS
CPPFLAGS += -D_USRDLL
CPPFLAGS += -DCOCOS2DXWIN32_EXPORTS
CPPFLAGS += -DGL_GLEXT_PROTOTYPES
CPPFLAGS += -DCOCOS2D_DEBUG=1
CPPFLAGS += -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS += -D_SCL_SECURE_NO_WARNINGS
CPPFLAGS += -DPTW32_STATIC_LIB

CPPFLAGS += -D_WIN32_WINNT=0x0500
CPPFLAGS += -DGLEW_STATIC

CPPFLAGS += -I/local/include
CPPFLAGS += -ICrossApp
CPPFLAGS += -ICrossApp/include
CPPFLAGS += -ICrossApp/kazmath/include
CPPFLAGS += -ICrossApp/platform/win32
CPPFLAGS += -ICrossApp/platform/third_party/win32/iconv
CPPFLAGS += -ICrossApp/platform/third_party/win32/zlib
CPPFLAGS += -ICrossApp/platform/third_party/win32/libpng
CPPFLAGS += -ICrossApp/platform/third_party/win32/libjpeg
CPPFLAGS += -ICrossApp/platform/third_party/win32/libtiff
CPPFLAGS += -ICrossApp/platform/third_party/win32/libwebp
CPPFLAGS += -ICrossApp/platform/third_party/win32/pthread
CPPFLAGS += -ICrossApp/platform/third_party/win32/OGLES
CPPFLAGS += -ICrossApp/platform/third_party/win32/freetype

LDFLAGS := -LCrossApp/platform/third_party/win32/libraries -lfreetype -lglew32 -lwebp -ljpeg -lpng -lbz2 -lz 
#-lpthreadGC2
LDFLAGS	+= -lglaux -lglu32 -lopengl32 -lwinmm -lgdi32 -lcomdlg32
LDFLAGS += -lavicap32 -lws2_32 -lmingw32 -lpsapi -ladvapi32 
LDFLAGS += -lshell32 -lwinmm -lgdi32 
LDFLAGS += -lm -lws2_32 -lstdc++
#-lpthreadGC2 

OBJS := 

#cocoa
OBJS += CrossApp/cocoa/CCArray.o
OBJS += CrossApp/cocoa/CCDictionary.o
OBJS += CrossApp/cocoa/CCNS.o
OBJS += CrossApp/cocoa/CCSet.o
OBJS += CrossApp/cocoa/CCString.o
OBJS += CrossApp/cocoa/CACalendar.o

#actions
OBJS += CrossApp/actions/CCAction.o
OBJS += CrossApp/actions/CCActionCamera.o
OBJS += CrossApp/actions/CCActionEase.o
OBJS += CrossApp/actions/CCActionInstant.o
OBJS += CrossApp/actions/CCActionInterval.o
OBJS += CrossApp/actions/CCActionManager.o
OBJS += CrossApp/actions/CCActionTween.o

#platform
OBJS += CrossApp/platform/CCEGLViewProtocol.o
OBJS += CrossApp/platform/CCSAXParser.o
OBJS += CrossApp/platform/platform.o
OBJS += CrossApp/platform/CCFileUtils.o
OBJS += CrossApp/platform/CCImageCommonWebp.o
OBJS += CrossApp/platform/CAFreeTypeFont.o
OBJS += CrossApp/platform/CAFTFontCache.o
OBJS += CrossApp/platform/win32/CCAccelerometer.o
OBJS += CrossApp/platform/win32/CCApplication.o
OBJS += CrossApp/platform/win32/CCCommon.o
OBJS += CrossApp/platform/win32/CCEGLView.o
OBJS += CrossApp/platform/win32/CCImage.o
OBJS += CrossApp/platform/win32/CCStdC.o
OBJS += CrossApp/platform/win32/CCFileUtilsWin32.o
OBJS += CrossApp/platform/win32/CCDevice.o
OBJS += CrossApp/platform/win32/CADensityDpi.o
OBJS += CrossApp/platform/win32/CAWebViewImpl.o



#support
OBJS += CrossApp/support/base64.o
OBJS += CrossApp/support/CCPointExtension.o
OBJS += CrossApp/support/CCProfiling.o
OBJS += CrossApp/support/ccUtils.o
OBJS += CrossApp/support/CCVertex.o
OBJS += CrossApp/support/TransformUtils.o
OBJS += CrossApp/support/ccUTF8.o
OBJS += CrossApp/support/CANotificationCenter.o
OBJS += CrossApp/support/ConvertUTF.o
OBJS += CrossApp/support/ConvertUTFWrapper.o
OBJS += CrossApp/support/md5.o
OBJS += CrossApp/support/data_support/ccCArray.o
OBJS += CrossApp/support/image_support/TGAlib.o
OBJS += CrossApp/support/zip_support/ioapi.o
OBJS += CrossApp/support/zip_support/unzip.o
OBJS += CrossApp/support/zip_support/ZipUtils.o
OBJS += CrossApp/support/tinyxml2/tinyxml2.o
OBJS += CrossApp/support/user_default/CAUserDefault.o


#kazmath
OBJS += CrossApp/kazmath/src/aabb.o
OBJS += CrossApp/kazmath/src/mat3.o
OBJS += CrossApp/kazmath/src/mat4.o
OBJS += CrossApp/kazmath/src/neon_matrix_impl.o
OBJS += CrossApp/kazmath/src/plane.o
OBJS += CrossApp/kazmath/src/quaternion.o
OBJS += CrossApp/kazmath/src/ray2.o
OBJS += CrossApp/kazmath/src/utility.o
OBJS += CrossApp/kazmath/src/vec2.o
OBJS += CrossApp/kazmath/src/vec3.o
OBJS += CrossApp/kazmath/src/vec4.o
OBJS += CrossApp/kazmath/src/GL/mat4stack.o
OBJS += CrossApp/kazmath/src/GL/matrix.o

#draw_nodes
OBJS += CrossApp/draw_nodes/CCDrawingPrimitives.o
OBJS += CrossApp/draw_nodes/CCDrawNode.o

#shaders
OBJS += CrossApp/shaders/ccGLStateCache.o
OBJS += CrossApp/shaders/ccShaders.o
OBJS += CrossApp/shaders/CAGLProgram.o
OBJS += CrossApp/shaders/CAShaderCache.o
OBJS += CrossApp/shaders/CATransformation.o

#images
OBJS += CrossApp/images/CAImage.o
OBJS += CrossApp/images/CAImageCache.o


#basics
OBJS += CrossApp/basics/CAApplication.o
OBJS += CrossApp/basics/CAAutoreleasePool.o
OBJS += CrossApp/basics/CACamera.o
OBJS += CrossApp/basics/CAFPSImages.o
OBJS += CrossApp/basics/CAGeometry.o
OBJS += CrossApp/basics/CAObject.o
OBJS += CrossApp/basics/CAResponder.o
OBJS += CrossApp/basics/CAScheduler.o
OBJS += CrossApp/basics/CAIndexPath.o
OBJS += CrossApp/basics/CAThread.o

#dispatcher
OBJS += CrossApp/dispatcher/CAIMEDispatcher.o
OBJS += CrossApp/dispatcher/CAKeypadDelegate.o
OBJS += CrossApp/dispatcher/CAKeypadDispatcher.o
OBJS += CrossApp/dispatcher/CATouch.o
OBJS += CrossApp/dispatcher/CATouchDispatcher.o

#view
OBJS += CrossApp/view/CABatchView.o
OBJS += CrossApp/view/CAClippingView.o
OBJS += CrossApp/view/CAImageView.o
OBJS += CrossApp/view/CALabel.o
OBJS += CrossApp/view/CARenderImage.o
OBJS += CrossApp/view/CAScale9ImageView.o
OBJS += CrossApp/view/CAScrollView.o
OBJS += CrossApp/view/CATableView.o
OBJS += CrossApp/view/CAView.o
OBJS += CrossApp/view/CAWindow.o
OBJS += CrossApp/view/CAAlertView.o
OBJS += CrossApp/view/CACollectionView.o
OBJS += CrossApp/view/CAPageView.o
OBJS += CrossApp/view/CAPickerView.o
OBJS += CrossApp/view/CAActivityIndicatorView.o
OBJS += CrossApp/view/CADatePickerView.o
OBJS += CrossApp/view/CAListView.o
OBJS += CrossApp/view/CAPullToRefreshView.o
OBJS += CrossApp/view/CATextView.o
OBJS += CrossApp/view/CALabelStyle.o
OBJS += CrossApp/view/CAWebView.o


#control
OBJS += CrossApp/control/CABar.o
OBJS += CrossApp/control/CAButton.o
OBJS += CrossApp/control/CAControl.o
OBJS += CrossApp/control/CAProgress.o
OBJS += CrossApp/control/CASegmentedControl.o
OBJS += CrossApp/control/CASlider.o
OBJS += CrossApp/control/CASwitch.o
OBJS += CrossApp/control/CATextField.o
OBJS += CrossApp/control/CAPageControl.o
OBJS += CrossApp/control/CAStepper.o


#controller
OBJS += CrossApp/controller/CABarItem.o
OBJS += CrossApp/controller/CAViewController.o
OBJS += CrossApp/controller/CADrawerController.o

#global
OBJS += CrossApp/CrossApp.o

#script_support
OBJS += CrossApp/script_support/CCScriptSupport.o
OBJS += CrossApp/script_support/JSViewController.o


TEMPLATE_OBJS :=
TEMPLATE_OBJS += template/multi-platform-cpp/Classes/AppDelegate.o
TEMPLATE_OBJS += template/multi-platform-cpp/Classes/FirstViewController.o
TEMPLATE_OBJS += template/multi-platform-cpp/Classes/RootWindow.o

HELLOCPP_OBJS += samples/demo/Classes/AppDelegate.o
HELLOCPP_OBJS += samples/demo/Classes/AlertViewTest/AlertViewTest.o
HELLOCPP_OBJS += samples/demo/Classes/ButtonTest/ButtonTest.o
HELLOCPP_OBJS += samples/demo/Classes/CollectionViewTest/CollectionViewTest.o
HELLOCPP_OBJS += samples/demo/Classes/ImageViewTest/ImageViewTest.o
HELLOCPP_OBJS += samples/demo/Classes/LabelTest/LabelTest.o
HELLOCPP_OBJS += samples/demo/Classes/ProgressTest/ProgressTest.o
HELLOCPP_OBJS += samples/demo/Classes/SegmentedControlTest/SegmentedControlTest.o
HELLOCPP_OBJS += samples/demo/Classes/SliderTest/SliderTest.o
HELLOCPP_OBJS += samples/demo/Classes/SwitchTest/SwitchTest.o
HELLOCPP_OBJS += samples/demo/Classes/TabBarTest/TabBarTest.o
HELLOCPP_OBJS += samples/demo/Classes/TextFieldTest/TextFieldTest.o
HELLOCPP_OBJS += samples/demo/Classes/TableViewTest/TableViewTest.o
# HELLOCPP_OBJS += samples/demo/Classes/ExtensionsTest/ExtensionsTest.o
HELLOCPP_OBJS += samples/demo/Classes/ViewController/FirstViewController.o
HELLOCPP_OBJS += samples/demo/Classes/ViewController/SecondViewController.o
HELLOCPP_OBJS += samples/demo/Classes/ViewController/ThirdViewController.o
HELLOCPP_OBJS += samples/demo/Classes/ViewController/FifthViewController.o
HELLOCPP_OBJS += samples/demo/Classes/ViewController/FourthViewController.o
# HELLOCPP_OBJS += samples/demo/Classes/ExtensionsTest/AddressBookTest.o
# HELLOCPP_OBJS += samples/demo/Classes/ExtensionsTest/HttpRequestTest.o
HELLOCPP_OBJS += samples/demo/Classes/MainMenu.o
HELLOCPP_OBJS += samples/demo/Classes/PageViewTest/PageViewTest.o
HELLOCPP_OBJS += samples/demo/Classes/ActivityIndicatorViewTest/ActivityIndicatorViewTest.o
HELLOCPP_OBJS += samples/demo/Classes/TableViewTest/MyTableViewCell.o
HELLOCPP_OBJS += samples/demo/Classes/ScrollViewTest/ScrollViewTest.o
HELLOCPP_OBJS += samples/demo/Classes/ListViewTest/ListViewTest.o
HELLOCPP_OBJS += samples/demo/Classes/ListViewTest/MyListViewCell.o
HELLOCPP_OBJS += samples/demo/Classes/TextViewTest/TextViewTest.o

all : crossapp.a template/multi-platform-cpp/HelloCpp.exe samples/demo/HelloCpp.exe

crossapp.a : $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

samples/demo/HelloCpp.exe: crossapp.a $(HELLOCPP_OBJS)
	$(CPP) samples/demo/proj.win32/main.cpp $(HELLOCPP_OBJS) crossapp.a -o $@ -Isamples/demo/Classes $(CPPFLAGS) $(LDFLAGS)

template/multi-platform-cpp/HelloCpp.exe: crossapp.a $(TEMPLATE_OBJS)
	$(CPP) template/multi-platform-cpp/proj.win32/main.cpp $(TEMPLATE_OBJS) crossapp.a -o $@ -Itemplate/multi-platform-cpp/Classes $(CPPFLAGS) $(LDFLAGS)

%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

%.o : %.c
	$(CC) $(CPPFLAGS) -o $@ -c $<
	
clean :
	$(RM) $(OBJS) crossapp.a 
	$(RM) $(TEMPLATE_OBJS) template/multi-platform-cpp/HelloCpp.exe $(BIMS)
	$(RM) $(HELLOCPP_OBJS) samples/demo/HelloCpp.exe $(BIMS)
