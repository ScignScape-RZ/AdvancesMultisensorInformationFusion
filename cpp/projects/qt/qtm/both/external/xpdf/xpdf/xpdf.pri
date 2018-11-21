

#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += widgets
QT += network


RESOURCES += \
    $$SRC_DIR/xpdf-qt/icons.qrc


LIBS +=  -lqtfreetyped  -lqtlibpngd -lz


INCLUDEPATH += $$SRC_DIR/
INCLUDEPATH += $$SRC_DIR/aconf
INCLUDEPATH += $$SRC_DIR/goo

INCLUDEPATH += $$SRC_DIR/fofi
INCLUDEPATH += $$SRC_DIR/splash
INCLUDEPATH += $$SRC_DIR/xpdf
INCLUDEPATH += $$SRC_DIR/freetype/ft2build


INCLUDEPATH += $$SRC_DIR/freetype
INCLUDEPATH += $$SRC_DIR/ft2build


DISTFILES += \
    $$SRC_DIR/xpdf-qt/back.svg \
    $$SRC_DIR/xpdf-qt/findNext.svg \
    $$SRC_DIR/xpdf-qt/findPrevious.svg \
    $$SRC_DIR/xpdf-qt/findSettings.svg \
    $$SRC_DIR/xpdf-qt/fitPage.svg \
    $$SRC_DIR/xpdf-qt/fitPageOn.svg \
    $$SRC_DIR/xpdf-qt/fitWidth.svg \
    $$SRC_DIR/xpdf-qt/fitWidthOn.svg \
    $$SRC_DIR/xpdf-qt/forward.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon-err0.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon-err1.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon-err2.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon-err3.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon-err4.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon-err5.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon-err6.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon-err7.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon0.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon1.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon2.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon3.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon4.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon5.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon6.svg \
    $$SRC_DIR/xpdf-qt/indicator-icon7.svg \
    $$SRC_DIR/xpdf-qt/selectModeBlock.svg \
    $$SRC_DIR/xpdf-qt/selectModeLinear.svg \
    $$SRC_DIR/xpdf-qt/xpdf-icon.svg \
    $$SRC_DIR/xpdf-qt/zoomIn.svg \
    $$SRC_DIR/xpdf-qt/zoomOut.svg \
    $$SRC_DIR/xpdf-qt/xpdf-icon.ico \
    $$SRC_DIR/xpdf-qt/xpdf.rc \
    $$SRC_DIR/xpdf-qt/CMakeLists.txt

HEADERS += \
    $$SRC_DIR/fofi/FoFiBase.h \
    $$SRC_DIR/fofi/FoFiEncodings.h \
    $$SRC_DIR/fofi/FoFiIdentifier.h \
    $$SRC_DIR/fofi/FoFiTrueType.h \
    $$SRC_DIR/fofi/FoFiType1.h \
    $$SRC_DIR/fofi/FoFiType1C.h \
    $$SRC_DIR/goo/FixedPoint.h \
    $$SRC_DIR/goo/gfile.h \
    $$SRC_DIR/goo/GHash.h \
    $$SRC_DIR/goo/GList.h \
    $$SRC_DIR/goo/gmem.h \
    $$SRC_DIR/goo/gmempp.h \
    $$SRC_DIR/goo/GMutex.h \
    $$SRC_DIR/goo/GString.h \
    $$SRC_DIR/goo/gtypes.h \
    $$SRC_DIR/goo/parseargs.h \
    $$SRC_DIR/splash/Splash.h \
    $$SRC_DIR/splash/SplashBitmap.h \
    $$SRC_DIR/splash/SplashClip.h \
    $$SRC_DIR/splash/SplashErrorCodes.h \
    $$SRC_DIR/splash/SplashFont.h \
    $$SRC_DIR/splash/SplashFontEngine.h \
    $$SRC_DIR/splash/SplashFontFile.h \
    $$SRC_DIR/splash/SplashFontFileID.h \
    $$SRC_DIR/splash/SplashFTFont.h \
    $$SRC_DIR/splash/SplashFTFontEngine.h \
    $$SRC_DIR/splash/SplashFTFontFile.h \
    $$SRC_DIR/splash/SplashGlyphBitmap.h \
    $$SRC_DIR/splash/SplashMath.h \
    $$SRC_DIR/splash/SplashPath.h \
    $$SRC_DIR/splash/SplashPattern.h \
    $$SRC_DIR/splash/SplashScreen.h \
    $$SRC_DIR/splash/SplashState.h \
    $$SRC_DIR/splash/SplashTypes.h \
    $$SRC_DIR/splash/SplashXPath.h \
    $$SRC_DIR/splash/SplashXPathScanner.h \
    $$SRC_DIR/xpdf/AcroForm.h \
    $$SRC_DIR/xpdf/Annot.h \
    $$SRC_DIR/xpdf/Array.h \
    $$SRC_DIR/xpdf/BuiltinFont.h \
    $$SRC_DIR/xpdf/BuiltinFontTables.h \
    $$SRC_DIR/xpdf/Catalog.h \
    $$SRC_DIR/xpdf/CharCodeToUnicode.h \
    $$SRC_DIR/xpdf/CharTypes.h \
    $$SRC_DIR/xpdf/CMap.h \
    $$SRC_DIR/xpdf/CompactFontTables.h \
    $$SRC_DIR/xpdf/config.h \
    $$SRC_DIR/xpdf/Decrypt.h \
    $$SRC_DIR/xpdf/Dict.h \
    $$SRC_DIR/xpdf/DisplayState.h \
    $$SRC_DIR/xpdf/Error.h \
    $$SRC_DIR/xpdf/ErrorCodes.h \
    $$SRC_DIR/xpdf/FontEncodingTables.h \
    $$SRC_DIR/xpdf/Form.h \
    $$SRC_DIR/xpdf/Function.h \
    $$SRC_DIR/xpdf/Gfx.h \
    $$SRC_DIR/xpdf/GfxFont.h \
    $$SRC_DIR/xpdf/GfxState.h \
    $$SRC_DIR/xpdf/GlobalParams.h \
    $$SRC_DIR/xpdf/HTMLGen.h \
    $$SRC_DIR/xpdf/ImageOutputDev.h \
    $$SRC_DIR/xpdf/JArithmeticDecoder.h \
    $$SRC_DIR/xpdf/JBIG2Stream.h \
    $$SRC_DIR/xpdf/JPXStream.h \
    $$SRC_DIR/xpdf/Lexer.h \
    $$SRC_DIR/xpdf/Link.h \
    $$SRC_DIR/xpdf/NameToCharCode.h \
    $$SRC_DIR/xpdf/NameToUnicodeTable.h \
    $$SRC_DIR/xpdf/Object.h \
    $$SRC_DIR/xpdf/OptionalContent.h \
    $$SRC_DIR/xpdf/Outline.h \
    $$SRC_DIR/xpdf/OutputDev.h \
    $$SRC_DIR/xpdf/Page.h \
    $$SRC_DIR/xpdf/Parser.h \
    $$SRC_DIR/xpdf/PDFCore.h \
    $$SRC_DIR/xpdf/PDFDoc.h \
    $$SRC_DIR/xpdf/PDFDocEncoding.h \
    $$SRC_DIR/xpdf/PreScanOutputDev.h \
    $$SRC_DIR/xpdf/PSOutputDev.h \
    $$SRC_DIR/xpdf/PSTokenizer.h \
    $$SRC_DIR/xpdf/SecurityHandler.h \
    $$SRC_DIR/xpdf/SplashOutputDev.h \
    $$SRC_DIR/xpdf/Stream-CCITT.h \
    $$SRC_DIR/xpdf/Stream.h \
    $$SRC_DIR/xpdf/TextOutputDev.h \
    $$SRC_DIR/xpdf/TextString.h \
    $$SRC_DIR/xpdf/TileCache.h \
    $$SRC_DIR/xpdf/TileCompositor.h \
    $$SRC_DIR/xpdf/TileMap.h \
    $$SRC_DIR/xpdf/UnicodeMap.h \
    $$SRC_DIR/xpdf/UnicodeMapTables.h \
    $$SRC_DIR/xpdf/UnicodeTypeTable.h \
    $$SRC_DIR/xpdf/UTF8.h \
    $$SRC_DIR/xpdf/XFAForm.h \
    $$SRC_DIR/xpdf/XRef.h \
    $$SRC_DIR/xpdf/Zoox.h \
    $$SRC_DIR/xpdf-qt/QtPDFCore.h \
    $$SRC_DIR/xpdf-qt/XpdfApp.h \
    $$SRC_DIR/xpdf-qt/XpdfViewer.h \
    $$SRC_DIR/xpdf-qt/XpdfWidget.h \
    $$SRC_DIR/xpdf-qt/XpdfWidgetPrint.h \
    $$SRC_DIR/xpdf-qt/xpdf-component.h \


SOURCES += \
    $$SRC_DIR/fofi/FoFiBase.cc \
    $$SRC_DIR/fofi/FoFiEncodings.cc \
    $$SRC_DIR/fofi/FoFiIdentifier.cc \
    $$SRC_DIR/fofi/FoFiTrueType.cc \
    $$SRC_DIR/fofi/FoFiType1.cc \
    $$SRC_DIR/fofi/FoFiType1C.cc \
    $$SRC_DIR/goo/FixedPoint.cc \
    $$SRC_DIR/goo/gfile.cc \
    $$SRC_DIR/goo/GHash.cc \
    $$SRC_DIR/goo/GList.cc \
    $$SRC_DIR/goo/gmem.cc \
    $$SRC_DIR/goo/gmempp.cc \
    $$SRC_DIR/goo/GString.cc \
    $$SRC_DIR/splash/Splash.cc \
    $$SRC_DIR/splash/SplashBitmap.cc \
    $$SRC_DIR/splash/SplashClip.cc \
    $$SRC_DIR/splash/SplashFont.cc \
    $$SRC_DIR/splash/SplashFontEngine.cc \
    $$SRC_DIR/splash/SplashFontFile.cc \
    $$SRC_DIR/splash/SplashFontFileID.cc \
    $$SRC_DIR/splash/SplashFTFont.cc \
    $$SRC_DIR/splash/SplashFTFontEngine.cc \
    $$SRC_DIR/splash/SplashFTFontFile.cc \
    $$SRC_DIR/splash/SplashPath.cc \
    $$SRC_DIR/splash/SplashPattern.cc \
    $$SRC_DIR/splash/SplashScreen.cc \
    $$SRC_DIR/splash/SplashState.cc \
    $$SRC_DIR/splash/SplashXPath.cc \
    $$SRC_DIR/splash/SplashXPathScanner.cc \
    $$SRC_DIR/xpdf/AcroForm.cc \
    $$SRC_DIR/xpdf/Annot.cc \
    $$SRC_DIR/xpdf/Array.cc \
    $$SRC_DIR/xpdf/BuiltinFont.cc \
    $$SRC_DIR/xpdf/BuiltinFontTables.cc \
    $$SRC_DIR/xpdf/Catalog.cc \
    $$SRC_DIR/xpdf/CharCodeToUnicode.cc \
    $$SRC_DIR/xpdf/CMap.cc \
    $$SRC_DIR/xpdf/Decrypt.cc \
    $$SRC_DIR/xpdf/Dict.cc \
    $$SRC_DIR/xpdf/DisplayState.cc \
    $$SRC_DIR/xpdf/Error.cc \
    $$SRC_DIR/xpdf/FontEncodingTables.cc \
    $$SRC_DIR/xpdf/Form.cc \
    $$SRC_DIR/xpdf/Function.cc \
    $$SRC_DIR/xpdf/Gfx.cc \
    $$SRC_DIR/xpdf/GfxFont.cc \
    $$SRC_DIR/xpdf/GfxState.cc \
    $$SRC_DIR/xpdf/GlobalParams.cc \
    \ # $$SRC_DIR/xpdf/HTMLGen.cc \
    $$SRC_DIR/xpdf/ImageOutputDev.cc \
    $$SRC_DIR/xpdf/JArithmeticDecoder.cc \
    $$SRC_DIR/xpdf/JBIG2Stream.cc \
    $$SRC_DIR/xpdf/JPXStream.cc \
    $$SRC_DIR/xpdf/Lexer.cc \
    $$SRC_DIR/xpdf/Link.cc \
    $$SRC_DIR/xpdf/NameToCharCode.cc \
    $$SRC_DIR/xpdf/Object.cc \
    $$SRC_DIR/xpdf/OptionalContent.cc \
    $$SRC_DIR/xpdf/Outline.cc \
    $$SRC_DIR/xpdf/OutputDev.cc \
    $$SRC_DIR/xpdf/Page.cc \
    $$SRC_DIR/xpdf/Parser.cc \
    $$SRC_DIR/xpdf/PDFCore.cc \
    \ # $$SRC_DIR/xpdf/pdfdetach.cc \
    $$SRC_DIR/xpdf/PDFDoc.cc \
    $$SRC_DIR/xpdf/PDFDocEncoding.cc \
    \ # $$SRC_DIR/xpdf/pdffonts.cc \
    \ # $$SRC_DIR/xpdf/pdfimages.cc \
    \ # $$SRC_DIR/xpdf/pdfinfo.cc \
    \ # $$SRC_DIR/xpdf/pdftohtml.cc \
    \ # $$SRC_DIR/xpdf/pdftopng.cc \
    \ # $$SRC_DIR/xpdf/pdftoppm.cc \
    \ # $$SRC_DIR/xpdf/pdftops.cc \
    \ # $$SRC_DIR/xpdf/pdftotext.cc \
    $$SRC_DIR/xpdf/PreScanOutputDev.cc \
    $$SRC_DIR/xpdf/PSOutputDev.cc \
    $$SRC_DIR/xpdf/PSTokenizer.cc \
    $$SRC_DIR/xpdf/SecurityHandler.cc \
    $$SRC_DIR/xpdf/SplashOutputDev.cc \
    $$SRC_DIR/xpdf/Stream.cc \
    $$SRC_DIR/xpdf/TextOutputDev.cc \
    $$SRC_DIR/xpdf/TextString.cc \
    $$SRC_DIR/xpdf/TileCache.cc \
    $$SRC_DIR/xpdf/TileCompositor.cc \
    $$SRC_DIR/xpdf/TileMap.cc \
    $$SRC_DIR/xpdf/UnicodeMap.cc \
    $$SRC_DIR/xpdf/UnicodeTypeTable.cc \
    $$SRC_DIR/xpdf/UTF8.cc \
    $$SRC_DIR/xpdf/XFAForm.cc \
    $$SRC_DIR/xpdf/XRef.cc \
    $$SRC_DIR/xpdf/Zoox.cc \
    $$SRC_DIR/xpdf-qt/QtPDFCore.cc \
    $$SRC_DIR/xpdf-qt/xpdf.cc \
    $$SRC_DIR/xpdf-qt/XpdfApp.cc \
    $$SRC_DIR/xpdf-qt/XpdfViewer.cc \
    $$SRC_DIR/xpdf-qt/XpdfWidget.cc \
    $$SRC_DIR/xpdf-qt/XpdfWidgetPrint.cc \
    $$SRC_DIR/goo/parseargs.c \
    $$SRC_DIR/xpdf-qt/xpdf-component.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
