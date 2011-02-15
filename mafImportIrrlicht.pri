# import Irrlicht foundation library references
# Foundation libraries dependencies
 INCLUDEPATH += $$(MAF3_FOUNDATION_LIB_DIR)/Irrlicht/include
 

unix:LIB_CHECK = $$(MAF3_FOUNDATION_LIB_DIR)/Irrlicht/lib/
win32:LIB_CHECK = $$(MAF3_FOUNDATION_LIB_DIR)\Irrlicht\lib\

# Foundation libraries dependencies
exists( $$LIB_CHECK ) {
    LIBS += -L$$(MAF3_FOUNDATION_LIB_DIR)/Irrlicht/lib/ \
            -lIrrlicht
}

win32:!exists( $$DESTDIR\*Irrlicht* ):QMAKE_PRE_LINK += copy \
        $$quote($$(MAF3_FOUNDATION_LIB_DIR)\Irrlicht\lib\*Irrlicht*) \
        $$DESTDIR

unix:!exists( $$DESTDIR/*Irrlicht* ):QMAKE_PRE_LINK += cd $$(MAF3_FOUNDATION_LIB_DIR)/Irrlicht/lib/ ;tar -cf zipped *;mv zipped $$DESTDIR/;cd $$DESTDIR/;tar -xvf zipped;rm zipped


