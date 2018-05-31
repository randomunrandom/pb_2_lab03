

#ifndef __TXLIB_H
#define __TXLIB_H

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include <windows.h>


extern HWND             _txCanvas_Wnd         ;
extern HDC              _txCanvas_BackBuf[2]  ;
extern UINT             _txCanvas_Timer       ;
extern HANDLE           _txCanvas_Thread      ;
extern CRITICAL_SECTION _txCanvas_LockBackBuf ;
extern int              _txCanvas_LockRefresh ;

extern HWND             _txConsole_Wnd        ;
extern HANDLE           _txConsole_Thread     ;

extern bool             _txConsole_CursorMode ;

extern bool             _txRunning            ;
extern bool             _txExit               ;

extern int              _txMouseX             ;
extern int              _txMouseY             ;
extern int              _txMouseButtons       ;

//-----------------------------------------------------------------------------

HWND             _txCanvas_Wnd         = NULL;
HDC              _txCanvas_BackBuf[2]  = {NULL, NULL};
UINT             _txCanvas_Timer       = 0;
HANDLE           _txCanvas_Thread      = NULL;
CRITICAL_SECTION _txCanvas_LockBackBuf = {0};
int              _txCanvas_LockRefresh = 0;

HWND             _txConsole_Wnd        = NULL;
HANDLE           _txConsole_Thread     = NULL;

bool             _txConsole_CursorMode = false;

bool             _txRunning            = false;
bool             _txExit               = false;

int              _txMouseX             = 0;
int              _txMouseY             = 0;
int              _txMouseButtons       = 0;


//=============================================================================
//! \cond Namespaces



namespace {
namespace TX {

//! \endcond Namespaces
//=============================================================================

//=============================================================================
//  \name    �����
//=============================================================================

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   �������� ���������������� ������
//! \see     txSetColor(), txSetFillColor(), txGetColor(), txGetFillColor(), txGetPixel()
//  \note    The TX_* constants are the wrappers around my teacher's bug at 20050915 :)

enum txColors
    {
    txBLACK        = RGB (  0,   0,   0), TX_BLACK         = txBLACK,        //!< ������
    txBLUE         = RGB (  0,   0, 128), TX_BLUE          = txBLUE,         //!< �����
    txGREEN        = RGB (  0, 128,   0), TX_GREEN         = txGREEN,        //!< �������
    txCYAN         = RGB (  0, 128, 128), TX_CYAN          = txCYAN,         //!< ���������
    txRED          = RGB (128,   0,   0), TX_RED           = txRED,          //!< �������
    txMAGENTA      = RGB (128,   0, 128), TX_MAGENTA       = txMAGENTA,      //!< ���������
    txBROWN        = RGB (128, 128,   0), TX_BROWN         = txBROWN,        //!< ����������
    txORANGE       = RGB (255, 128,   0), TX_ORANGE        = txORANGE,       //!< ���������
    txGRAY         = RGB (160, 160, 160), TX_GRAY          = txGRAY,         //!< �����
    txDARKGRAY     = RGB (128, 128, 128), TX_DARKGRAY      = txDARKGRAY,     //!< �����-�����
    txLIGHTGRAY    = RGB (192, 192, 192), TX_LIGHTGRAY     = txLIGHTGRAY,    //!< ������-�����
    txLIGHTBLUE    = RGB (  0,   0, 255), TX_LIGHTBLUE     = txLIGHTBLUE,    //!< ������-�����
    txLIGHTGREEN   = RGB (  0, 255, 128), TX_LIGHTGREEN    = txLIGHTGREEN,   //!< ������-�������
    txLIGHTCYAN    = RGB (  0, 255, 255), TX_LIGHTCYAN     = txLIGHTCYAN,    //!< ������-���������
    txLIGHTRED     = RGB (255,   0, 128), TX_LIGHTRED      = txLIGHTRED,     //!< ������-�������
    txLIGHTMAGENTA = RGB (255,   0, 255), TX_LIGHTMAGENTA  = txLIGHTMAGENTA, //!< ������-���������
    txPINK         = RGB (255, 128, 255), TX_PINK          = txPINK,         //!< �������
    txYELLOW       = RGB (255, 255, 128), TX_YELLOW        = txYELLOW,       //!< ������
    txWHITE        = RGB (255, 255, 255), TX_WHITE         = txWHITE,        //!< �����
    txTRANSPARENT  = 0xFFFFFFFF,          TX_TRANSPARENT   = txTRANSPARENT,  //!< ����������
    txNULL         = txTRANSPARENT,       TX_NULL          = txNULL,         //!< ����������

//! �������� ������ (����������)

    txHUE          = 0x04000000,          TX_HUE           = txHUE,          //!< �������� ���
    txSATURATION   = 0x05000000,          TX_SATURATION    = txSATURATION,   //!< ������������
    txLIGHTNESS    = 0x06000000,          TX_LIGHTNESS     = txLIGHTNESS     //!< ��������
    };

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������� (���������) ���� �� ���� ������� ������ (���������).
//! \return  ��������� ���� � ������� COLORREF.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors
//! \see     RGB(), txExtractColor(), txRGB2HSL(), txHSL2RGB()

#ifdef FOR_DOXYGEN_ONLY
COLORREF RGB (red,       //!< ���������� �������� ����� � ��������� [0; 255]
              green,     //!< ���������� �������� ����� � ��������� [0; 255]
              blue       //!< ���������� ������ ����� � ��������� [0; 255]
              );
#endif

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ��������� �������� ���������� (�������� �����) �� ���������� �����.
//! \return  �������� ����������, ��. \ref txColors
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), txColors
//! \see     RGB(), txExtractColor(), txRGB2HSL(), txHSL2RGB(), \ref txColors

int txExtractColor (COLORREF color,     //!< ��������� ����
                    COLORREF component  //!< ����������� ����������, ��. \ref txColors
                    );

//---------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ����������� ���� �� ������� RGB � ������ HSL.
//!
//!          ������ RGB ������������ ���
//!
//!          - ������� ���������� ����� (Red), �� 0 �� 255.
//!          - ������� ���������� ����� (Green), �� 0 �� 255.
//!          - ����� ���������� ����� (Blue), �� 0 �� 255.
//!
//!          ������ HSL ������������ ���
//!
//!          - �������� ��� (Hue), �� 0 �� 360.
//!          - ������������ (Saturation), �� 0 �� 255.
//!          - �������� (Lightness), �� 0 �� 255.
//!
//! \return  ��������� ���� � ���� COLORREF.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors
//! \see     RGB(), txExtractColor(), txRGB2HSL(), txHSL2RGB(), \ref txColors

COLORREF txRGB2HSL (COLORREF rgbColor   //!< ������������� ���� � ������� RGB
                    );

//---------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ����������� ���� �� ������� HSL � ������ RGB.
//!
//!          ������ RGB ������������ ���
//!
//!          - ������� ���������� ����� (Red), �� 0 �� 255.
//!          - ������� ���������� ����� (Green), �� 0 �� 255.
//!          - ����� ���������� ����� (Blue), �� 0 �� 255.
//!
//!          ������ HSL ������������ ���
//!
//!          - �������� ��� (Hue), �� 0 �� 360.
//!          - ������������ (Saturation), �� 0 �� 255.
//!          - �������� (Lightness), �� 0 �� 255.
//!
//! \return  ��������� ���� � ���� COLORREF.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors
//! \see     RGB(), txExtractColor(), txRGB2HSL(), txHSL2RGB(), \ref txColors

COLORREF txHSL2RGB (COLORREF hslColor   //!< ������������� ���� � ������� HSL
                    );

//=============================================================================
//  \name    ������������� � ��������� ���������
//=============================================================================

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   �������� ���� ���������
//! \return  ����� ��������
//! \see     txOk()

bool  txCreateWindow (double sizeX,        //!< ������ ���� �� ����������� (����)
                      double sizeY,        //!< ������ ���� �� ����������� (����)
                      bool centered = true //!< ������������� ���� �� �������
                      );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   �������� ������������ ������ ����������
//! \return  ��������� ����������
//! \see     txCreateWindow()

bool  txOK();

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ���������� ������ ���� ��������� � ���� ��������� POINT.
//! \return  ������ ���� ��������� � ���� ��������� POINT.
//! \see     txGetExtentX(), txGetExtentY()

POINT txGetExtent();

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ���������� ������ ���� ���������.
//! \return  ������ ���� ���������.
//! \see     txGetExtent(), txGetExtentY()

int txGetExtentX();

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ���������� ������ ���� ���������.
//! \return  ������ ���� ���������.
//! \see     txGetExtent(), txGetExtentX()

int txGetExtentY();

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ��������� ���������� ��������� �� ���������.
//!
//!          ��������� �� ���������:\n
//!          - ����� - ���� ����� (TX_WHITE), ������� 1
//!          - ������� - ���� ����� (TX_WHITE)
//!          - ����� - ��������� �����, ���� ����� (TX_WHITE)
//!          - ���������� ��������� �������� - ����������� ����� (R2_COPYPEN)
//!
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txSelectFont(), txSelectRegion(), txSetROP2()

bool txSetDefaults();

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������������� ������� ���� � ������� �����, ���� ������.
//! \return  ����� ��������.
//! \see     txColor(), txGetColor(), txFillColor(), txGetFillColor(), \ref txColors, RGB()

bool txSetColor (COLORREF color,   //!< ���� ����� � ������, ��. \ref txColors, RGB()
                 int thickness = 1 //!< ������� �����
                 );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������������� ������� ���� ����� � ������.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor()

bool txColor (double red,     //!< ���������� �������� ����� � ��������� [0; 1]
              double green,   //!< ���������� �������� ����� � ��������� [0; 1]
              double blue     //!< ���������� ������ ����� � ��������� [0; 1]
              );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ���������� ������� ���� ����� � ������.
//! \return  ������� ���� ����� � ������, ��. \ref txColors, RGB()
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()

COLORREF txGetColor();

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������������� ������� ���� ���������� �����.
//! \return  ����� ��������.
//! \see     txFillColor(), txGetFillColor(), txColor(), txGetColor(), \ref txColors, RGB()

bool txSetFillColor (COLORREF color  //!< ���� ����������, ��. \ref txColors, RGB()
                     );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������������� ������� ���� ���������� �����.
//! \return  ����� ��������.
//! \see     txSetFillColor(), txGetFillColor(), txSetColor(), txGetColor()

bool txFillColor (double red,   //!< ���������� �������� ����� � ��������� [0; 1]
                  double green, //!< ���������� �������� ����� � ��������� [0; 1]
                  double blue   //!< ���������� ������ ����� � ��������� [0; 1]
                  );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ���������� ������� ���� ���������� �����.
//! \return  ������� ���� ���������� �����, ��. \ref txColors, RGB()
//! \see     txSetFillColor(), txGetFillColor(), txSetColor(), txGetColor(), \ref txColors, RGB()

COLORREF txGetFillColor();

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������������� ����� �������������� ������ ��� ���������.
//!
//!          ��� ��������� ����������� ���������� ����� �� ������ ������� �������
//!          �� ������, � ��������� ����� ������ � ������� ����� ����� � ����������.
//!
//!          ������ �������������� ������:
//!
//!          \table
//!          \tr R2_COPYPEN     \td ������� = ����� ����� (����� ���������� ����� :) \endtr
//!          \tr R2_NOTCOPYPEN  \td ������� = ~�����\n \endtr
//!
//!          \tr R2_BLACK       \td ������� = ������ ���� (���� ����� ������������)    \endtr
//!          \tr R2_WHITE       \td ������� = �����  ���� (���� ����� ������������)    \endtr
//!          \tr R2_NOT         \td ������� = ~�������    (���� ����� ������������)\n  \endtr
//!
//!          \tr R2_XORPEN      \td ������� =    ������� ^  �����    \endtr
//!          \tr R2_NOTXORPEN   \td ������� = ~ (������� ^  �����)\n \endtr
//!
//!          \tr R2_MASKPEN     \td ������� =    ������� &  �����    \endtr
//!          \tr R2_NOTMASKPEN  \td ������� = ~ (������� &  �����)   \endtr
//!          \tr R2_MASKNOTPEN  \td ������� =    ������� & ~�����    \endtr
//!          \tr R2_MASKPENNOT  \td ������� =   ~������� &  �����\n  \endtr
//!
//!          \tr R2_MERGEPEN    \td ������� =    ������� |  �����    \endtr
//!          \tr R2_NOTMERGEPEN \td ������� = ~ (������� |  �����)   \endtr
//!          \tr R2_MERGENOTPEN \td ������� =    ������� | ~�����    \endtr
//!          \tr R2_MERGEPENNOT \td ������� =   ~������� |  �����\n  \endtr
//!
//!          \tr R2_NOP         \td ������� ������ �� ����������.    \endtr
//!          \endtable
//!
//! \return  ���������� ����� �������������� ������, ��. \ref txColors, RGB()
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool txSetROP2 (int mode         //!< ����� ���������� ������
                );

//=============================================================================
//  \name    ������
//=============================================================================

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������� ����� ������� ������ ����������.
//! \return  ����� ��������.
//! \see     txSetFillColor(), txFillColor(), txGetFillColor(), \ref txColors, RGB()

bool  txClear();

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ ������� (����� �� ������).
//! \return  ����� ��������.
//! \see     txSetPixel (double, double, double, double, double), txGetPixel(), \ref txColors, RGB()

bool  txSetPixel (double x,      //!< �-���������� �����
                  double y,      //!< Y-���������� �����
                  COLORREF color //!< ���� �����, ��. \ref txColors, RGB()
                  );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ ������� (����� �� ������).
//! \return  ����� ��������.
//! \see     txSetPixel (double, double, COLORREF), txGetPixel()

bool  txSetPixel (double x,     //!< �-���������� �����
                  double y,     //!< Y-���������� �����
                  double red,   //!< ���������� �������� ����� � ��������� [0; 1]
                  double green, //!< ���������� �������� ����� � ��������� [0; 1]
                  double blue   //!< ���������� ������ ����� � ��������� [0; 1]
                  );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ���������� ������� ���� ����� (�������) �� ������.
//! \return  ������� ���� �������, ��. \ref txColors, RGB()
//! \see     \ref txColors, RGB()

COLORREF txGetPixel (double x,  //!< �-���������� �����
                     double y   //!< Y-���������� �����
                     );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ �����.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txLine (double x0,        //!< X-���������� ��������� �����
              double y0,        //!< Y-���������� ��������� �����
              double x1,        //!< X-���������� �������� �����
              double y1         //!< Y-���������� �������� �����
              );

//-----------------------------------------------------------------------------
// VV
//! \ingroup Drawing
//! \brief   ��������� X ������� ����� (�� ���������� ���������� �������� txLineTo � txMoveTo).
//! \return  �������� X.
//! \see     txGetCurrentY (), txMoveTo(), txLineTo(), txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor()  \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

double txGetCurrentX ();

//-----------------------------------------------------------------------------
// VV

//! \ingroup Drawing
//! \brief   ��������� Y ������� ����� (�� ���������� ���������� �������� txLineTo � txMoveTo).
//! \return  �������� Y.
//! \see     txGetCurrentX (), txMoveTo(), txLineTo(), txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor()  \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

double txGetCurrentY ();

//-----------------------------------------------------------------------------
// VV

//! \ingroup Drawing
//! \brief   ���������� ������� ����� (�� ���������� ���������� �������� txLineTo � txMoveTo).
//! \return  ����� ��������.
//! \see     txGetCurrentX (), txLineTo(), txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor()  \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txMoveTo (double x,        //!< X-���������� �������� �����
                double y         //!< Y-���������� �������� �����
               );

//-----------------------------------------------------------------------------
// VV

//! \ingroup Drawing
//! \brief   ������ ����� �� ������� ����� (�� ���������� ���������� �������� txLineTo � txMoveTo).
//! \return  ����� ��������.
//! \see     txGetCurrentX (), txGetCurrentY (), txMoveTo(), txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), txMoveTo() \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txLineTo (double x,        //!< X-���������� �������� �����
                double y         //!< Y-���������� �������� �����
               );

//-----------------------------------------------------------------------------

//! \ingroup Drawing
//! \brief   ������ �������������.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txRectangle (double x0,   //!< X-���������� �������� ������ ����
                   double y0,   //!< Y-���������� �������� ������ ����
                   double x1,   //!< X-���������� ������� ������� ����
                   double y1    //!< Y-���������� ������� ������� ����
                   );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ ������� ����� ��� �������������.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txPolygon (POINT* points, //!< ������ �������� POINT � ������������ �����
                 int npoints    //!< ���������� ����� � �������
                 );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ ������.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txEllipse (double x0,     //!< X-���������� �������� ������ ���� ���������� ��������������
                 double y0,     //!< Y-���������� �������� ������ ���� ���������� ��������������
                 double x1,     //!< X-���������� ������� ������� ���� ���������� ��������������
                 double y1      //!< Y-���������� ������� ������� ���� ���������� ��������������
                 );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ ���������� ��� ����.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txCircle (double x,       //!< �-���������� ������
                double y,       //!< Y-���������� ������
                double r        //!< ������
                );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ ���� �������.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txArc (double x0,         //!< X-���������� �������� ������ ���� ��������������,
                                //!<   ���������� ������ �������, ����������� ����
             double y0,         //!< Y-���������� �������� ������ ���� ��������������
             double x1,         //!< X-���������� ������� ������� ���� ��������������
             double y1,         //!< Y-���������� ������� ������� ���� ��������������
             double startAngle, //!< ���� ����� ������������ ��� OX � ������� ���� (� ��������)
             double totalAngle  //!< �������� ���� (� ��������)
             );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ ������ �������.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txPie (double x0,         //!< X-���������� �������� ������ ���� ��������������,
                                //!<   ���������� ������ �������, ����������� ������
             double y0,         //!< Y-���������� �������� ������ ���� ��������������
             double x1,         //!< X-���������� ������� ������� ���� ��������������
             double y1,         //!< Y-���������� ������� ������� ���� ��������������
             double startAngle, //!< ���� ����� ������������ ��� OX � ������� ������� (� ��������)
             double totalAngle  //!< �������� ������� (� ��������)
             );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ ����� �������.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool  txChord (double x0,         //!< X-���������� �������� ������ ���� ��������������,
                                  //!<   ���������� ������ �������, ����������� �����
               double y0,         //!< Y-���������� �������� ������ ���� ��������������
               double x1,         //!< X-���������� ������� ������� ���� ��������������
               double y1,         //!< Y-���������� ������� ������� ���� ��������������
               double startAngle, //!< ���� ����� ������������ ��� OX � ������� ����� (� ��������)
               double totalAngle  //!< �������� ����� (� ��������)
               );

//=============================================================================
//  \name    ������ � �������
//=============================================================================

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������ �����.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()

bool  txTextOut (double x,         //!< �-���������� ��������� ����� ������
                 double y,         //!< Y-���������� ��������� ����� ������
                 const char text[] //!< ��������� ������
                 );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   �������� ������� �����.
//! \return  ����� ��������.
//! \see     txTextOut()

bool  txSelectFont (const char* name,       //!< �������� ������
                    double sizeY,           //!< ������ ���� (������ �� Y)
                    double sizeX = 0,       //!< ������ ����
                    int bold = FW_DONTCARE, //!< �������� ������ (�� 0 �� 1000)
                    bool italic = false,    //!< ������
                    bool underline = false, //!< �������������
                    bool strikeout = false  //!< ������������
                    );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ��������� ������� ��������� �������.
//! \return  ������� ������� � ��������� SIZE.
//! \see     txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()

SIZE  txGetTextExtent (const char* text     //!< ��������� ������
                      );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ��������� ������ ��������� �������.
//! \return  ������ �������.
//! \see     txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()

int txGetTextExtentX (const char* text      //!< ��������� ������
                     );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ��������� ������ ��������� �������.
//! \return  ������ �������.
//! \see     txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()

int txGetTextExtentY (const char* text      //!< ��������� ������
                     );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������������� ������� ������������ ������.
//!
//!          ����� ������������:
//!
//!          \table
//!          \tr TA_BASELINE \td ����� (X,Y) ���������� ������� ����� ������. \endtr
//!          \tr TA_BOTTOM   \td ����� (X,Y) ���������� ������ ������� ���������� ��������������\n
//!                              (����� ����� ���� ���� �����).   \endtr
//!          \tr TA_TOP      \td ����� (X,Y) ���������� ������� ������� ���������� ��������������\n
//!                              (����� ����� ���� ���� �����).\n \endtr
//!
//!          \tr TA_CENTER   \td ����� ����� �������� �� ����������� ������������ ����� (X,Y). \endtr
//!          \tr TA_LEFT     \td ����� (X,Y) ���������� ����� ������� ���������� ��������������\n
//!                              (����� ����� ������ ���� �����). \endtr
//!          \tr TA_RIGHT    \td ����� (X,Y) ���������� ������ ������� ���������� ��������������\n
//!                              (����� ����� ����� ���� �����).  \endtr
//!          \endtable
//!
//! \return  ����� ��������.
//! \see     txTextOut(), txSelectFont(), txGetTextExtent(), txGetTextExtentX(), txGetTextExtentY()

bool txSetTextAlign (unsigned align = TA_CENTER | TA_BASELINE //!< ����� ������������
                     );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ���� ����� �� ��� ��������.
//! \return  ���������� � ������ � ��������� LOGFONT.
//!          ���� ����� �� ������, ���������� NULL.
//! \see     txTextOut(), txSelectFont()

LOGFONT* txFontExist (const char* name      //!< �������� ������
                     );

//=============================================================================
//  \name    ������
//=============================================================================

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   �������� ������������ ������ ������� ������ ����������.
//!
//!          ������ �������:
//!
//!          FLOODFILLSURFACE - �������� �������, ��������� ������ color.\n
//!          FLOODFILLBORDER  - �������� �� �������, ��������� ������ color.
//!
//! \return  ����� ��������.
//! \see     txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txLine(), txRectangle(), txPolygon(), txEllipse(), txCircle(), txArc(), txPie(), txChord()

bool txFloodFill (double x,                        //!< �-���������� ����� ������ �������
                  double y,                        //!< Y-���������� ����� ������ �������
                  COLORREF color = TX_TRANSPARENT, //!< ���� ���������� ������� (TX_TRANSPARENT - ���������������)
                  DWORD mode = FLOODFILLSURFACE    //!< ����� ������� (FLOODFILLSURFACE - ������� ����������� ����)
                  );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������������� ������� ������������� ������ ���������.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()

bool txSelectRegion (double x0,   //!< X-���������� �������� ������ ����
                     double y0,   //!< Y-���������� �������� ������ ����
                     double x1,   //!< X-���������� ������� ������� ����
                     double y1    //!< Y-���������� ������� ������� ����
                     );

//-----------------------------------------------------------------------------
//! \ingroup Service
//! \brief   ������������� ������� ������ GDI.
//! \return  ����� ��������.
//! \see     txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()
//!          txSelectFont(), txSelectRegion()

bool txSelectObject (HGDIOBJ obj     //!< ���������� ������� GDI
                     );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ��������� ���������� ����������� ����, �� ��������� �������.
//!
//! \warning ��������� ������������ �� ������ �����. ��� ����� �������� �
//!          �������� ����������� � ����. ���� ��������� ��������, �� �����������
//!          txSleep() ������ ������� ������� Sleep().
//!
//! \return  �������� �������� ���������� (���� 0, �� ��������� ��������������).
//! \see     txBegin(), txEnd(), txSleep(), txUpdateWindow(), txTextCursor()

int txBegin();

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������������ ���������� ����, ��������������� �������� txBegin().
//!
//! \warning ���� txBegin() ���������� ��������� ���, �� ��� ������ ����������
//!          ��������� ������� �� ��� ������� txEnd().
//!
//! \return  �������� �������� ���������� (���� 0, �� ��������� ��������������).
//! \see     txBegin(), txEnd(), txSleep(), txUpdateWindow(), txTextCursor()

int txEnd();

//-----------------------------------------------------------------------------
//! \ingroup Service
//! \brief   ��������� ��� ������������ ���������� ����������� � ����.
//!
//!          � ������� �� txBegin() � txEnd(), ��������� ���� ���������� ���
//!          ����� ����������.
//!
//! \warning ��������� ������������ �� ������ �����. ��� ����� �������� �
//!          �������� ����������� � ����. ���� ��������� ��������, �� �����������
//!          txSleep() ������ ������� ������� Sleep().
//!
//! \return  ���������� ��������� ������ ����������.
//! \see     txBegin(), txEnd(), txSleep(), txUpdateWindow(), txTextCursor(), txLock(), txUnlock(), txGDI()

bool txUpdateWindow (bool update = true //!< ����� ���������� (false - ��������� ����������)
                     );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ��������� ��� ������������ ��������� ��������� ������� � ����.
//! \return  ���������� �������� ����������.
//! \see     txCreateWindow(), txUpdateWindow(), txLock(), txUnlock(), txGDI()

bool txTextCursor (bool blink = true    //!< false - ����������� �������� ������
                   );

//=============================================================================
//  \name    ��������� � ������ � �������� �����������
//=============================================================================

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ������� �������������� ����� (�������� ���������, DC) � ������.
//! \return  ���������� (�����������) ���������� ��������� ���������.
//! \see     txCreateWindow(), txCreateCompatibleDC(), txLoadImage(), txDeleteDC()
//!
//! \remarks ��������� �������� ����� ����� ����� ������� ��� ������ txDeleteDC().

HDC txCreateCompatibleDC (double sizeX,            //!< ������ ������
                          double sizeY,            //!< ������ ������
                          HBITMAP bitmap = NULL    //!< Bitmap associated with DC
                          );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ��������� �� ����� ����������� � ������� BMP.
//! \return  ���������� ���������� ��������� ��������� � ������, � ����������� ������������.
//! \see     txCreateWindow(), txCreateCompatibleDC(), txLoadImage(), txDeleteDC(), txBitBlt(), txAlphaBlend(), txTransparentBlt(),
//!
//! \remarks ����������� ����������� � ����������� �������� ��������� (�����),
//!          ������� ����� ����� ����� ������� ��� ������ txDeleteDC().

HDC txLoadImage (LPCTSTR name, double sizeX, double sizeY);     //!< ��� ����� � ������������

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   ���������� ����� (�������� ���������, DC) � ������.
//! \return  ����� ��������.
//! \see     txCreateWindow(), txCreateCompatibleDC(), txLoadImage(), txDeleteDC()

bool txDeleteDC (HDC dc            //!< �������� ��������� ��� �����������
                 );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   �������� ����������� � ������ ������ (��������� ���������, DC) �� ������.
//!
//!          ������ �����������:
//!
//!          \table
//!          \tr SRCCOPY     \td ������ �������� :) - ����� ���������������� �����\n \endtr
//!
//!          \tr BLACKNESS   \td ��������� �����-�������� ������ ������ (�����-�������� ������������). \endtr
//!          \tr WHITENESS   \td ��������� �����-�������� ����� ������ (�����-�������� ������������). \endtr
//!          \tr DSTINVERT   \td ����������� ����� �� ������-��������� (�����-�������� ������������). \endtr
//!          \tr PATCOPY     \td �������� ���� ������� ����� ������-���������.\n \endtr
//!
//!          \tr MERGECOPY   \td �������� =   �������� & ���� ������� ����� ���������. \endtr
//!          \tr MERGEPAINT  \td �������� = ~ �������� | �������� \endtr
//!          \tr NOTSRCCOPY  \td �������� = ~ �������� \endtr
//!          \tr NOTSRCERASE \td �������� = ~ (�������� | ��������) \endtr
//!          \tr PATINVERT   \td �������� =  ����� ��������� ^  �������� \endtr
//!          \tr PATPAINT    \td �������� = (����� ��������� | ~��������) | �������� \endtr
//!          \tr SRCAND      \td �������� =  �������� & �������� \endtr
//!          \tr SRCERASE    \td �������� = ~�������� & �������� \endtr
//!          \tr SRCINVERT   \td �������� =  �������� ^ �������� \endtr
//!          \tr SRCPAINT    \td �������� =  �������� | �������� \endtr
//!          \endtable
//!
//! \return  ����� ��������.
//! \see     txAlphaBlend(), txTransparentBlt(), txSetColor(), txGetColor(), txSetFillColor(), txGetFillColor(), \ref txColors, RGB()

bool txBitBlt (HDC dest,           //!< �������� ���������� (���� ����������)
               double xDest,       //!< �-���������� �������� ������ ���� �����������-���������
               double yDest,       //!< Y-���������� �������� ������ ���� �����������-���������
               double width,       //!< ������ ����������� �����������
               double height,      //!< ������ ����������� �����������
               HDC src,            //!< �������� ��������� (������ ����������)
               double xSrc,        //!< �-���������� �������� ������ ���� �����������-���������
               double ySrc,        //!< Y-���������� �������� ������ ���� �����������-���������
               DWORD rOp = SRCCOPY //!< ��������� �������� �����������
               );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   �������� ����������� � ������ ������ (��������� ���������, DC) �� ������
//! \brief   � ������ ������������.
//! \return  ����� ��������.
//! \see     txBitBlt(), txTransparentBlt(), txLoadImage(), txCreateCompatibleDC()

bool txTransparentBlt (HDC dest,                 //!< �������� ���������� (���� ����������)
                       double xDest,             //!< �-���������� �������� ������ ���� �����������-���������
                       double yDest,             //!< Y-���������� �������� ������ ���� �����������-���������
                       double width,             //!< ������ ����������� �����������
                       double height,            //!< ������ ����������� �����������
                       HDC src,                  //!< �������� ��������� (������ ����������)
                       double xSrc,              //!< �-���������� �������� ������ ���� �����������-���������
                       double ySrc,              //!< Y-���������� �������� ������ ���� �����������-���������
                       COLORREF transColor = TX_BLACK //!< ����, ������� ����� ��������� ����������
                       );

//-----------------------------------------------------------------------------
//! \ingroup Drawing
//! \brief   �������� ����������� � ������ ������ (��������� ���������, DC) �� ������
//! \brief   � ������ ������������.
//!
//!          ����������� ������ ���� ��������� � ������� txLoadImage() � �����
//!          32-������� RGBA-������. �������������� ����� (�����-�����) �����
//!          ������� �������� �� ������������ �������� �����������.
//!
//!          �����-����� ����� �������, ��������, � Adobe Photoshop, ��������
//!          "����� ����� (New Channel)" � ������� ������� (Channels). ������
//!          ���� � �����-������ ������������� ������ ������������, ����� -
//!          ������ ��������������.
//!
//! \return  ����� ��������.
//! \see     txBitBlt(), txTransparentBlt(), txLoadImage(), txCreateCompatibleDC()

bool txAlphaBlend (HDC dest,                     //!< �������� ���������� (���� ����������)
                   double xDest,                 //!< �-���������� �������� ������ ���� �����������-���������
                   double yDest,                 //!< Y-���������� �������� ������ ���� �����������-���������
                   double width,                 //!< ������ ����������� �����������
                   double height,                //!< ������ ����������� �����������
                   HDC src,                      //!< �������� ��������� (������ ����������)
                   double xSrc,                  //!< �-���������� �������� ������ ���� �����������-���������
                   double ySrc,                  //!< Y-���������� �������� ������ ���� �����������-���������
                   double alpha = 1.0            //!< ����� ������������ �����������, � ���������� � �����-������.\n
                                                 //!<   (0 - ��� ���������, 1 - ������������ ������ �����-�����)
                   );

//=============================================================================
//
//  \name    ������ � �����
//
//=============================================================================

//-----------------------------------------------------------------------------
//! \ingroup Mouse
//! \brief   ���������� �-���������� ����!
//! \return  �-���������� ����.
//! \see     txMouseX(), txMouseY(), txMouseButtons()

double txMouseX();

//-----------------------------------------------------------------------------
//! \ingroup Mouse
//! \brief   ���������� Y-���������� ����!
//! \return  Y-���������� ����.
//! \see     txMouseX(), txMouseY(), txMouseButtons()

double txMouseY();

//-----------------------------------------------------------------------------
//! \ingroup Mouse
//! \brief   ���������� ��������� ������ ����!
//! \return  ��������� ������ ����.
//! \see     txMouseX(), txMouseY(), txMouseButtons()

int txMouseButtons();

//=============================================================================
//
// \name     Back-hole (I hope, not an ass-hole:) of the library)
//
//=============================================================================

//-----------------------------------------------------------------------------
//! \ingroup Service
//! \brief   ���������� ���������� ��������� ��������� ������
//! \return  ���������� ��������� ��������� ������
//! \see     txWindow(), txLock(), txUnlock(), txGDI()

HDC  txDC();

//-----------------------------------------------------------------------------
//! \ingroup Service
//! \brief   ���������� ���������� ���� ������
//! \return  ���������� ���� ������
//! \see     txDC(), txLock(), txUnlock(), txGDI()

HWND txWindow();

//-----------------------------------------------------------------------------
//! \ingroup Service
//! \brief   ���������� ������ (����������� ���������).
//!
//!          ����� ������� ����� ������� Win32 GDI ���������� �������������
//!          ����� �������� txLock() � ����� �������������� � ������� txUnlock().
//!          ��� ������� � ���, ��� ���������� ����������� ���� (��� ���, ���
//!          ����� - ��������� ��������� WM_PAINT :) ���������� � ���������
//!          ������. ������� ����������� ������ - ��� ��������������� ������
//!          ���� �� �����������.
//!
//!          txLock() ���������� EnterCriticalSection(), � ���������
//!          ���������������� �����, ����������� ����, ��� ��� �������
//!          ����������� ������.
//!
//!          txLock()/txUnlock() - �������������� ��������, �� ���������� ��
//!          ���������������� ��������� txBegin()/txEnd()/txUpdateWindow(),
//!          ������� �� ���������������� �����, � ������ ��������� ��������
//!          �� ���������� ����.
//!
//! \return  ��������� ����������
//! \see     txDC(), txLock(), txUnlock(), txGDI()

bool txLock();

//-----------------------------------------------------------------------------
//! \ingroup Service
//! \brief   ������������� ������
//! \return  ��������� ����������
//! \see     txDC(), txLock(), txUnlock(), txGDI()

bool txUnlock();

//! \cond    Internal
template <typename T> inline T txUnlock (T value);
//! \endcond Internal

//-----------------------------------------------------------------------------
//! \ingroup Service
//! \brief   ����� ������� Win32 GDI � �������������� ����������� � ��������������
//! \return  ��������, ������������ ���������� �������� GDI.
//! \param   cmd ������� GDI (��������, ������������ ��������)
//! \note    ���� � ������ ������� GDI ������������ �������, �� �����������
//!          ������� ������, ��� ��� ��� ���-���� ������:
//!          txGDI <b>((</b> Rectangle (txDC(), x1, y1, x2, y2) <b>))</b>;
//! \see     txDC(), txLock(), txUnlock(), txGDI()
//! \hideinitializer

#define txGDI( cmd ) txUnlock ((txLock(), (cmd)))

//-----------------------------------------------------------------------------
//! \ingroup Technical
//! \brief   ���������� ������ � ����������� � ������� ������ ����������.
//! \return  ������ � ����������� � ������� ������ ����������.

const char* txVersion();

//=============================================================================
//
// \name     Misc functions
//
//=============================================================================

//-----------------------------------------------------------------------------
//! \ingroup Misc
//! \brief   ��������, ��������� �� �������� � ������ ���������� ��������� [a; b]
//! \return  ���� a <= x && x <= b, �� ������, ���� ��� - ����
//! \hideinitializer

template <typename T>
inline bool In (T x, //!< ����������� ��������
                T a, //!< ����� ������� (������������)
                T b  //!< ������ ������� (������������)
                )
    {
    return a <= x && x <= b;
    }

//-----------------------------------------------------------------------------
//! \ingroup Misc
//! \brief   ��������, ��������� �� ����� pt ������ �������������� rect
//! \return  ��������� ��������

inline bool In (const COORD& pt,       //!< ����������� �����
                const SMALL_RECT& rect //!< �������������
                )
    {
    return In (pt.X, rect.Left, rect.Right) && In (pt.Y, rect.Top, rect.Bottom);
    }

//-----------------------------------------------------------------------------
//! \ingroup Misc
//! \brief   ���������� ������������ �� ���� �����
//! \param   a ���� �� ����� :)
//! \param   b ������ �� ����� :)
//! \return  ������������ �� ���� ����� a � b
//! \hideinitializer

#define MAX( a, b )      ( (a) > (b) ? (a) : (b) )

//-----------------------------------------------------------------------------
//! \ingroup Misc
//! \brief   ���������� ����������� �� ���� �����
//! \param   a ���� �� ����� :)
//! \param   b ������ �� ����� :)
//! \return  ����������� �� ���� ����� a � b
//! \hideinitializer

#define MIN( a, b )      ( (a) < (b) ? (a) : (b) )

//-----------------------------------------------------------------------------
//! \ingroup Misc
//! \brief   ��������� ��������� �����
//! \param   range ������ ������� ��������� (�� ������� ���� �������).
//! \return  ��������� ����� ����� � ��������� [0; range).\n
//!          �� ��� �������, ��� �������� ������ �������� � ����������� ����������? :)
//! \hideinitializer

#define random( range )  ( rand() % (range) )

//-----------------------------------------------------------------------------
//! \ingroup Misc
//! \brief   ����������� ���������� ��������� �� ������������ �����.
//!
//!          �� ����� �������� ���������� ����������� � ���� ������
//!          ������������� ��������������.
//!
//! \return  ��������� ���������� ���������� ����.
//! \see     txUpdateWindow()

bool txSleep (int time   //!< �������� � �������������
              );

//-----------------------------------------------------------------------------
//! \ingroup Misc
//! \brief   ������������� �������� ����.
//!
//!          ������ ���������������:
//!
//!          \table
//!          \tr SND_ASYNC       \td ���� ������������� ������������ � ������� ���������.\n
//!                                  ����� �������� ��������, �������� txPlaySound (NULL). \endtr
//!          \tr SND_SYNC        \td ���������� ��������� ������������������ �� ���������
//!                                  ��������������� �����. \endtr
//!          \tr SND_LOOP        \td ����������� ���� ��� ���������������.\n
//!                                  ����� �������� ��������, �������� txPlaySound (NULL).\n \endtr
//!
//!          \tr SND_NODEFAULT   \td �� ������������ ���� �� ���������, ���� ������ ���������
//!                                  ��������� �������� ����. \endtr
//!          \tr SND_NOSTOP      \td ���� �����-���� ���� ��� �������������, �� �������������
//!                                  ��� ��� ��������������� ���������� �����. \endtr
//!          \tr SND_APPLICATION \td ����������� ����, ��������� ���������, ������������������
//!                                  ��� ������� ���� �������� ������. \endtr
//!          \endtable
//!
//! \return  ����� ��������.

bool txPlaySound (const char* filename = NULL, //!< ��� ��������� �����.
                                               //!< ���� NULL - ������������� ����.
                  DWORD mode = SND_ASYNC       //!< ����� ���������������
                  );

//-----------------------------------------------------------------------------
//! \ingroup Misc
//! \brief   ����� ��
//! \return  ����� ��

const double txPI = asin (1.0) * 2;

//=============================================================================
// ����������� ���������
//=============================================================================

//! \ingroup Technical
//! \brief   �������� ������� ������� ������� (��)

const unsigned _TX_CURSOR_BLINK_INTERVAL  = 250;

//! \ingroup Technical
//! \brief   ����� �������

const char   _TX_CONSOLE_FONT[]           = "Lucida Console";

//! \ingroup Technical
//! \brief   ���� ������ �������

const COLORREF _TX_CONSOLE_COLOR          = txLIGHTGRAY;

//! \ingroup Technical
//! \brief   ������� �������� �������� (��)

const int    _TX_TIMEOUT                  = 1000;

//! \ingroup Technical
//! \brief   �������� ���������� ������ (��)

const int    _TX_WINDOW_UPDATE_INTERVAL   = 10;

//! \ingroup Technical
//! \brief   ������������ ���������� ����� ������ ������� ��� ���������� ������

#define      _TX_USE_CONSOLE_THREAD         0

//! \ingroup Technical
//! \brief   ������� ������ ����������.
//!          ��� ��������� ������������� ����������� ��� ���������� ������.
//! \see     txVersion()

#define      _TX_VERSION                    "[Version 0.01 alpha, build 01]"

//=============================================================================
//! \cond    Internal
//@{

namespace Internal
{

//-----------------------------------------------------------------------------

bool _txInitialize (int sizeX, int sizeY, bool centered);
bool _txCleanup();
void _txOnExit();

bool _txCanvas_SetDefaults();
bool _txConsole_SetDefaults();

HWND _txCanvas_CreateWindow (POINT size);
bool _txCanvas_OK();
bool _txCanvas_DestroyWindow();
int  _txCanvas_SetLockRefresh (int count);
bool _txCanvas_OnCreate (HWND wnd);
bool _txCanvas_OnDestroy (HWND wnd);
bool _txCanvas_OnClose (HWND);
bool _txCanvas_OnPaint (HWND wnd);
bool _txCanvas_OnChar (HWND wnd, WPARAM ch);
bool _txCanvas_OnTimer (HWND wnd, WPARAM id);
bool _txCanvas_OnMouse (HWND wnd, WPARAM buttons, LPARAM coords);
bool _txCanvas_OnCmdAbout (HWND wnd, WPARAM cmd);
bool _txCanvas_OnCmdConsole (HWND wnd, WPARAM cmd);
DWORD WINAPI _txCanvas_ThreadProc (LPVOID data);
LRESULT CALLBACK _txCanvas_WndProc (HWND wnd, UINT msg, WPARAM wpar, LPARAM lpar);

HDC  _txBuffer_Create (HWND wnd, const POINT* size = NULL, HBITMAP bmap = NULL);
bool _txBuffer_Delete (HDC dc);
bool _txSelect (HGDIOBJ obj, HDC dc = txDC());

bool _txConsole_Attach();
bool _txConsole_OK();
bool _txConsole_Detach();
bool _txConsole_Draw (HDC dc);
HWND _txConsole_GetWindow();
DWORD WINAPI _txConsole_ThreadProc (LPVOID);

//-----------------------------------------------------------------------------

bool _Throw (const char file[], int line, const char func[], DWORD error, const char msg[], ...);

#ifdef __FUNCTION__
#define THROW(msg)    _Throw (__FILE__, __LINE__, __FUNCTION__, GetLastError(), msg)
#else
#define THROW(msg)    _Throw (__FILE__, __LINE__, NULL,         GetLastError(), msg)
#endif

#define _             ,
#define NEEDED        ;
//|| THROW (NULL)

//-----------------------------------------------------------------------------

#define PRINT_HERE()  printf ("%s (%d) %s(): Here... :)\n", __FILE__, __LINE__, __FUNCTION__)

#ifndef NDEBUG
#undef  assert
#define assert(p)     ( !(p)? (THROW ("\aAssertion failed: \"%s\"" _ #p), 0) : _txDummy() )
#else
#undef  assert
#define assert(p)     ( 1 )
#endif

#define _txWaitFor(p)  { for (int __i##__LINE__ = 0; __i##__LINE__ < _TX_TIMEOUT/10; __i##__LINE__++) \
                             { if (p) break; Sleep (10); } }

inline int _txDummy()  { return 1; }

//-----------------------------------------------------------------------------

#define IMPORT( lib, retval, name, params ) \
     retval (WINAPI* name) params = (retval (WINAPI*) params) _txImport (lib ".dll", #name, true)

#define IMPORT_OPT( lib, retval, name, params ) \
     retval (WINAPI* name) params = (retval (WINAPI*) params) _txImport (lib ".dll", #name, false)

FARPROC _txImport (const char lib[], const char name[], int required = true);

//-----------------------------------------------------------------------------
// Dev-CPP doesn't link with GDI32 by default, so do sunrise by hand. :(
// <tears>

//! \cond Namespaces
namespace Win32 {
//! \endcond Namespaces

IMPORT ("GDI32", int,      GetDeviceCaps,          (HDC dc, int index));
IMPORT ("GDI32", HDC,      CreateCompatibleDC,     (HDC dc));
IMPORT ("GDI32", HBITMAP,  CreateCompatibleBitmap, (HDC dc, int width, int height));
IMPORT ("GDI32", HGDIOBJ,  GetStockObject,         (int object));
IMPORT ("GDI32", HGDIOBJ,  SelectObject,           (HDC dc, HGDIOBJ object));
IMPORT ("GDI32", HGDIOBJ,  GetCurrentObject,       (HDC dc, UINT objectType));
IMPORT ("GDI32", int,      GetObjectA,             (HGDIOBJ obj, int bufsize, LPVOID buffer));
IMPORT ("GDI32", BOOL,     DeleteDC,               (HDC dc));
IMPORT ("GDI32", BOOL,     DeleteObject,           (HGDIOBJ object));
IMPORT ("GDI32", COLORREF, SetTextColor,           (HDC dc, COLORREF color));
IMPORT ("GDI32", int,      SetBkMode,              (HDC dc, int bkMode));
IMPORT ("GDI32", HFONT,    CreateFontA,            (int height, int width, int escapement, int orientation,
                                                    int weight, DWORD italic, DWORD underline, DWORD strikeout,
                                                    DWORD charSet, DWORD outputPrec, DWORD clipPrec,
                                                    DWORD quality, DWORD pitchAndFamily, LPCTSTR face));
IMPORT ("GDI32", int,      EnumFontFamiliesExA,    (HDC dc, LPLOGFONT logFont, FONTENUMPROC enumProc,
                                                    LPARAM lParam, DWORD reserved));
IMPORT ("GDI32", COLORREF, SetPixel,               (HDC dc, int x, int y, COLORREF color));
IMPORT ("GDI32", COLORREF, GetPixel,               (HDC dc, int x, int y));
IMPORT ("GDI32", HPEN,     CreatePen,              (int penStyle, int width, COLORREF color));
IMPORT ("GDI32", HBRUSH,   CreateSolidBrush,       (COLORREF color));
IMPORT ("GDI32", BOOL,     MoveToEx,               (HDC dc, int x, int y, LPPOINT point));
IMPORT ("GDI32", BOOL,     LineTo,                 (HDC dc, int x, int y));
IMPORT ("GDI32", BOOL,     Polygon,                (HDC dc, CONST POINT* points, int n));
IMPORT ("GDI32", BOOL,     Rectangle,              (HDC dc, int x0, int y0, int x1, int y1));
IMPORT ("GDI32", BOOL,     Ellipse,                (HDC dc, int x0, int y0, int x1, int y1));
IMPORT ("GDI32", BOOL,     Arc,                    (HDC dc, int x0, int y0, int x1, int y1,
                                                    int xStart, int yStart, int xEnd, int yEnd));
IMPORT ("GDI32", BOOL,     Pie,                    (HDC dc, int x0, int y0, int x1, int y1,
                                                    int xStart, int yStart, int xEnd, int yEnd));
IMPORT ("GDI32", BOOL,     Chord,                  (HDC dc, int x0, int y0, int x1, int y1,
                                                    int xStart, int yStart, int xEnd, int yEnd));
IMPORT ("GDI32", BOOL,     TextOutA,               (HDC dc, int x, int y, LPCTSTR string, int length));
IMPORT ("GDI32", UINT,     SetTextAlign,           (HDC dc, UINT mode));
IMPORT ("GDI32", BOOL,     GetTextExtentPoint32A,  (HDC dc, LPCTSTR string, int length, LPSIZE size));
IMPORT ("GDI32", BOOL,     ExtFloodFill,           (HDC dc, int x, int y, COLORREF color, UINT type));
IMPORT ("GDI32", BOOL,     BitBlt,                 (HDC dest, int xDest, int yDest, int width, int height,
                                                    HDC src,  int xSrc,  int ySrc,  DWORD rOp));
IMPORT ("GDI32", BOOL,     PatBlt,                 (HDC dc, int x0, int y0, int width, int height, DWORD rOp));
IMPORT ("GDI32", int,      SetROP2,                (HDC dc, int mode));
IMPORT ("GDI32", HRGN,     CreateRectRgn,          (int x0, int y0, int x1, int y1));
IMPORT ("GDI32", BOOL,     GetBitmapDimensionEx,   (HBITMAP bitmap, LPSIZE dimensions));

IMPORT ("USER32",HANDLE,   LoadImageA,             (HINSTANCE inst, LPCTSTR name, UINT type,
                                                    int sizex, int sizey, UINT mode));

IMPORT ("WinMM", BOOL,     PlaySound,              (LPCSTR sound, HMODULE mod, DWORD mode));

IMPORT_OPT ("MSImg32",BOOL,TransparentBlt,         (HDC dest, int destX, int destY, int destWidth, int destHeight,
                                                    HDC src,  int srcX,  int srcY,  int srcWidth,  int srcHeight,
                                                    UINT transparentColor));
IMPORT_OPT ("MSImg32",BOOL,AlphaBlend,             (HDC dest, int destX, int destY, int destWidth, int destHeight,
                                                    HDC src,  int srcX,  int srcY,  int srcWidth,  int srcHeight,
                                                    BLENDFUNCTION blending));
//VV
IMPORT     ("GDI32", int,  GetCurrentPositionEx,   (HDC dc, POINT *point));
IMPORT     ("GDI32", int,  GetDIBits,              (HDC dc, HBITMAP hbmp, UINT uStartScan, UINT cScanLines,
                                                    LPVOID lpvBits, LPBITMAPINFO lpbi, UINT uUsage));





//! \cond Namespaces
}; // namespace Win32
using namespace Win32;
//! \endcond Namespaces

// </tears>
//=============================================================================
//...
#define _txIDM_ABOUT        40000
#define _txIDM_CONSOLE      40001

//-----------------------------------------------------------------------------

//! \cond Namespaces
}; // namespace Internal
using namespace Internal;
//! \endcond Namespaces

//=============================================================================

bool txCreateWindow (double sizeX, double sizeY, bool centered)
{
if (txOK()) return false;
return _txInitialize ((int)sizeX, (int)sizeY, centered);
}

//-----------------------------------------------------------------------------

bool txOK()
{
return _txConsole_OK() &&
       _txCanvas_OK();
}

//-----------------------------------------------------------------------------

const char* txVersion()
{
return _TX_VERSION;
}

//-----------------------------------------------------------------------------

inline HDC  txDC()           { return _txCanvas_BackBuf[0]; }
inline HWND txWindow()       { return _txCanvas_Wnd;        }

//-----------------------------------------------------------------------------

POINT txGetExtent()
{
assert (txOK());

RECT r = {0};
GetClientRect (txWindow(), &r);
POINT size = { r.right - r.left, r.bottom - r.top };
return size;
}

int txGetExtentX() { return txGetExtent().x; }
int txGetExtentY() { return txGetExtent().y; }

//-----------------------------------------------------------------------------

bool txClear()
{
assert (txOK());
POINT size = txGetExtent();

return txGDI ((Win32::PatBlt (txDC(), 0, 0, size.x, size.y, PATCOPY) != 0));
}

//-----------------------------------------------------------------------------

//VV
int linethickness = 1;

bool txSetColor (COLORREF color, int thickness)
{
assert (txOK());
//VV
linethickness = thickness;

return _txSelect (Win32::CreatePen ((color == TX_TRANSPARENT? PS_NULL : PS_SOLID), thickness, color)) &&
        txGDI   ((Win32::SetTextColor (txDC(), color) != 0));
}

//-----------------------------------------------------------------------------

bool txColor (double r, double g, double b)
{
if (r > 1) r = 1; if (r < 0) r = 0;
if (g > 1) g = 1; if (g < 0) g = 0;
if (b > 1) b = 1; if (b < 0) b = 0;
return txSetColor (RGB (r*255, g*255, b*255));
}

//-----------------------------------------------------------------------------

COLORREF txGetColor()
{
assert (txOK());

HGDIOBJ obj = txGDI ((Win32::GetCurrentObject (txDC(), OBJ_PEN))); obj NEEDED;

char buf [MAX (sizeof (LOGPEN), sizeof (EXTLOGPEN))] = {0};

int size = GetObject (obj, 0, NULL);
GetObject (obj, sizeof (buf), buf) NEEDED;

return (size == sizeof (LOGPEN))? ((LOGPEN*)buf)->lopnColor : ((EXTLOGPEN*)buf)->elpColor;
}

//-----------------------------------------------------------------------------

bool txSetFillColor (COLORREF color)
{
assert (txOK());

return _txSelect ((color == TX_TRANSPARENT)? Win32::GetStockObject   (HOLLOW_BRUSH) :
                                             Win32::CreateSolidBrush (color));
}

//-----------------------------------------------------------------------------

bool txFillColor (double r, double g, double b)
{
if (r > 1) r = 1; if (r < 0) r = 0;
if (g > 1) g = 1; if (g < 0) g = 0;
if (b > 1) b = 1; if (b < 0) b = 0;
return txSetFillColor (RGB (r*255, g*255, b*255));
}

//-----------------------------------------------------------------------------

COLORREF txGetFillColor()
{
assert (txOK());

HGDIOBJ obj = txGDI ((Win32::GetCurrentObject (txDC(), OBJ_BRUSH))); obj NEEDED;

LOGBRUSH buf = {0};
txGDI ((Win32::GetObject (obj, sizeof (buf), &buf))) NEEDED;

return buf.lbColor;
}

//-----------------------------------------------------------------------------

int txExtractColor (COLORREF color, COLORREF component)
{
switch (component)
    {
    case TX_RED:
    case TX_HUE:        return (BYTE)(color >>  0);

    case TX_GREEN:
    case TX_SATURATION: return (BYTE)(color >>  8);

    case TX_BLUE:
    case TX_LIGHTNESS:  return (BYTE)(color >> 16);

    default:            return -1;
    }
}

//---------------------------------------------------------------------------

COLORREF txRGB2HSL (COLORREF color)
{
int r = txExtractColor (color, TX_RED),
    g = txExtractColor (color, TX_GREEN),
    b = txExtractColor (color, TX_BLUE);

double m1 = MAX (MAX (r, g), b) / 255.0,
	   m2 = MIN (MIN (r, g), b) / 255.0,
	   dm = m1 - m2,
	   sm = m1 + m2,

	   ir = r / 255.0,
	   ig = g / 255.0,
	   ib = b / 255.0,

	   ih = 0,
	   is = 0,
	   il = sm / 2;

if (dm != 0)
	{
	is = dm / ((sm <= 1)? sm : (2-sm));

	double cr = (m1 - ir) / dm,
		   cg = (m1 - ig) / dm,
		   cb = (m1 - ib) / dm;

	if (ir == m1) ih =     cb - cg;
	if (ig == m1) ih = 2 + cr - cb;
	if (ib == m1) ih = 4 + cg - cr;
	}

return RGB ((int)(ih >= 0? ih*60 : ih*60 + 360), (int)(is*255), (int)(il*255));
}

//---------------------------------------------------------------------------

COLORREF txHSL2RGB (COLORREF color)
{
struct xRGB
    {
    static double calc (double h, double m1, double m2)
        {
	    if (h < 0)   h += 360;
	    if (h > 360) h -= 360;

	    return (h <  60)? m1 + (m2-m1) *      h  / 60 :
               (h < 180)? m2 :
	           (h < 240)? m1 + (m2-m1) * (240-h) / 60 :
                          m1;
        }
    };

int h = txExtractColor (color, TX_HUE),
    s = txExtractColor (color, TX_SATURATION),
    l = txExtractColor (color, TX_LIGHTNESS);

double ih = h,
       il = l / 100.0,
       is = s / 100.0,

       m2 = (il <= 0.5)? il * (1 + is) : il + is - il * is,
       m1 = 2 * il - m2,

	   ir = s? xRGB::calc (ih + 120, m1, m2) : il,
	   ig = s? xRGB::calc (ih,       m1, m2) : il,
	   ib = s? xRGB::calc (ih - 120, m1, m2) : il;

return RGB (ir * 255, ig * 255, ib * 255);
}

//-----------------------------------------------------------------------------

bool txSetPixel (double x, double y, COLORREF color)
{
assert (txOK());

txGDI ((Win32::SetPixel (txDC(), (int)x, (int)y, color))); //?? on MingW NEEDED;

RECT r = { (int)x, (int)y, (int)x, (int)y };
InvalidateRect (txWindow(), &r, false) NEEDED;
return true;
}

//-----------------------------------------------------------------------------

bool txSetPixel (double x, double y, double r, double g, double b)
{
if (r > 1) r = 1; if (r < 0) r = 0;
if (g > 1) g = 1; if (g < 0) g = 0;
if (b > 1) b = 1; if (b < 0) b = 0;
return txSetPixel (x, y, RGB (r*255, g*255, b*255));
}

//-----------------------------------------------------------------------------

COLORREF txGetPixel (double x, double y)
{
assert (txOK());

return txGDI ((Win32::GetPixel (txDC(), (int)x, (int)y)));
}

//-----------------------------------------------------------------------------

bool txLine (double x0, double y0, double x1, double y1)
{
assert (txOK());

txGDI ((Win32::MoveToEx (txDC(), (int)x0, (int)y0, NULL))) NEEDED;
txGDI ((Win32::LineTo   (txDC(), (int)x1, (int)y1)))       NEEDED;

RECT r = { (int)x0, (int)y0, (int)x1, (int)y1 };
InvalidateRect (txWindow(), &r, false) NEEDED;
return true;
}


//-----------------------------------------------------------------------------
// VV

double txGetCurrentX ()
{
assert (txOK());

POINT point;
Win32::GetCurrentPositionEx(txDC(), &point);

return point.x;
}

//-----------------------------------------------------------------------------
// VV

double txGetCurrentY ()
{
assert (txOK());

POINT point;

Win32::GetCurrentPositionEx(txDC(), &point);

return point.y;
}


//-----------------------------------------------------------------------------
// VV

bool txLineTo (double x, double y)
{
assert (txOK());

POINT oldPoint;

Win32::GetCurrentPositionEx(txDC(), &oldPoint);


txGDI ((Win32::LineTo   (txDC(), (int)x, (int)y)))                       NEEDED;

RECT r = { (int)oldPoint.x, (int)oldPoint.y, (int)x, (int)y };
InvalidateRect (txWindow(), &r, false)                                   NEEDED;
return true;
}

//-----------------------------------------------------------------------------
// VV

bool txMoveTo (double x, double y)
{
assert (txOK());

POINT point;

Win32::MoveToEx   (txDC(), (int)x, (int)y, &point)                       NEEDED;

return true;
}

//-----------------------------------------------------------------------------


bool txRectangle (double x0, double y0, double x1, double y1)
{
assert (txOK());

txGDI ((Win32::Rectangle (txDC(), (int)x0, (int)y0, (int)x1, (int)y1))) NEEDED;

RECT r = { (int)x0, (int)y0, (int)x1, (int)y1 };
InvalidateRect (txWindow(), &r, false) NEEDED;
return true;
}

//-----------------------------------------------------------------------------

bool txPolygon (POINT* points, int npoints)
{
assert (txOK());

return txGDI ((Win32::Polygon (txDC(), points, npoints) != 0));
}

//-----------------------------------------------------------------------------

bool txEllipse (double x0, double y0, double x1, double y1)
{
assert (txOK());

txGDI ((Win32::Ellipse (txDC(), (int)x0, (int)y0, (int)x1, (int)y1))) NEEDED;

RECT r = { (int)x0, (int)y0, (int)x1, (int)y1 };
InvalidateRect (txWindow(), &r, false) NEEDED;
return true;
}

bool txCircle (double x, double y, double r)
{
return txEllipse (x-r, y-r, x+r, y+r);
}

//-----------------------------------------------------------------------------

bool txArc (double x0, double y0, double x1, double y1, double startAngle, double totalAngle)
{
assert (txOK());

double start = startAngle * txPI / 180, end = (startAngle + totalAngle) * txPI / 180;
POINT center = { (int)((x0+x1)/2), (int)((y0+y1)/2) };

return txGDI ((Win32::Arc (txDC(),    (int)x0, (int)y0, (int)x1, (int)y1,
                           center.x + (int)(100*cos (start)), center.y - (int)(100*sin (start)),
                           center.x + (int)(100*cos (end)),   center.y - (int)(100*sin (end))) != 0));
}

//-----------------------------------------------------------------------------

bool txPie (double x0, double y0, double x1, double y1, double startAngle, double totalAngle)
{
assert (txOK());

double start = startAngle * txPI / 180, end = (startAngle + totalAngle) * txPI / 180;
POINT center = { (int)((x0+x1)/2), (int)((y0+y1)/2) };

return txGDI ((Win32::Pie (txDC(),    (int)x0, (int)y0, (int)x1, (int)y1,
                           center.x + (int)(100*cos (start)), center.y - (int)(100*sin (start)),
                           center.x + (int)(100*cos (end)),   center.y - (int)(100*sin (end))) != 0));
}

//-----------------------------------------------------------------------------

bool txChord (double x0, double y0, double x1, double y1, double startAngle, double totalAngle)
{
assert (txOK());

double start = startAngle * txPI / 180, end = (startAngle + totalAngle) * txPI / 180;
POINT center = { (int)((x0+x1)/2), (int)((y0+y1)/2) };

return txGDI ((Win32::Chord (txDC(),    (int)x0, (int)y0, (int)x1, (int)y1,
                             center.x + (int)(100*cos (start)), center.y - (int)(100*sin (start)),
                             center.x + (int)(100*cos (end)),   center.y - (int)(100*sin (end))) != 0));
}

//-----------------------------------------------------------------------------

bool txTextOut (double x, double y, const char text[])
{
assert (txOK());

int len = (int) strlen (text);
txGDI ((Win32::TextOut (txDC(), (int)x, (int)y, text, len))) NEEDED;

SIZE size = {0};
txGDI ((Win32::GetTextExtentPoint32 (txDC(), text, len, &size))) NEEDED;

RECT r = { (int)x, (int)y, (int)x + size.cx, (int)y + size.cy };
InvalidateRect (txWindow(), &r, false) NEEDED;
return true;
}

//-----------------------------------------------------------------------------

SIZE txGetTextExtent (const char* text)
{
assert (txOK());

SIZE size = {0};
txGDI ((Win32::GetTextExtentPoint32 (txDC(), text, (int) strlen (text), &size))) NEEDED;

return size;
}

int txGetTextExtentX (const char* text) { return txGetTextExtent (text) . cx; }
int txGetTextExtentY (const char* text) { return txGetTextExtent (text) . cy; }

//-----------------------------------------------------------------------------

bool txSelectFont (const char* name, double sizeY, double sizeX,
                   int bold, bool italic, bool underline, bool strikeout)
{
assert (txOK());

_txSelect (txFontExist (name)? CreateFont ((int)sizeY, (int)(sizeX? sizeX : sizeY*10/25), 0, 0,
                                           bold, italic, underline, strikeout,
                                           DEFAULT_CHARSET,
                                           OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                           DEFAULT_QUALITY, FIXED_PITCH, name)
                               :
                               GetStockObject (SYSTEM_FIXED_FONT));
return true;
}

//-----------------------------------------------------------------------------

bool txSetTextAlign (unsigned align)
{
assert (txOK());

txGDI ((Win32::SetTextAlign (txDC(), align)));
return true;
}

//-----------------------------------------------------------------------------

LOGFONT* txFontExist (const char* name)
{
assert (txOK());

LOGFONT font   = {0};
font.lfCharSet = DEFAULT_CHARSET;
strncpy (font.lfFaceName, name, sizeof font.lfFaceName);

struct enumFonts
    {
    static int CALLBACK Proc (const LOGFONT* font, const TEXTMETRIC*, DWORD, LPARAM data)
        {
        assert (font); assert (data);
        return strnicmp (font->lfFaceName, ((LOGFONT*)data)->lfFaceName, LF_FACESIZE) != 0;
        }
    };

return txGDI ((Win32::EnumFontFamiliesEx (txDC(), &font, enumFonts::Proc, (LPARAM)&font, 0) == 0? &font : NULL));
}

//-----------------------------------------------------------------------------

bool txFloodFill (double x, double y, COLORREF color, DWORD mode)
{
assert (txOK());
if (color == TX_TRANSPARENT) color = txGetPixel (x, y);

return txGDI ((Win32::ExtFloodFill (txDC(), (int)x, (int)y, color, mode) != 0));
}

//-----------------------------------------------------------------------------

bool txSetROP2 (int mode)
{
assert (txOK());

return txGDI ((Win32::SetROP2 (txDC(), mode) != 0));
}

//-----------------------------------------------------------------------------

HDC txCreateCompatibleDC (double sizeX, double sizeY, HBITMAP bitmap)
{
assert (txOK());
POINT size = { (int)sizeX, (int)sizeY };
HDC dc = _txBuffer_Create (txWindow(), &size, bitmap); dc NEEDED;
return dc;
}

//-----------------------------------------------------------------------------

HDC txLoadImage (LPCTSTR name, double sizeX = 0, double sizeY = 0 )
{


HBITMAP image = (HBITMAP) LoadImage (NULL, name, IMAGE_BITMAP, (int)sizeX, (int)sizeY, LR_LOADFROMFILE);
if (!image) return NULL;

HDC dc = txCreateCompatibleDC (sizeX, sizeY, image);

_txSelect (image, dc);
return dc;
}

//-----------------------------------------------------------------------------

bool txDeleteCanvas (HDC dc)
{
assert (txOK());
return _txBuffer_Delete (dc);
}

//-----------------------------------------------------------------------------

bool txBitBlt (HDC dest, double xDest, double yDest, double width, double height,
               HDC src,  double xSrc,  double ySrc,  DWORD rOp)
{
assert (txOK());

return txGDI ((Win32::BitBlt (dest, (int)xDest, (int)yDest, (int)width, (int)height,
                              src,  (int)xSrc,  (int)ySrc, rOp) != 0));
}

//-----------------------------------------------------------------------------

bool txTransparentBlt (HDC dest, double destX, double destY, double sizeX, double sizeY,
                       HDC src,  double srcX,  double srcY,  COLORREF transColor)
{
assert (txOK());
if (!TransparentBlt) return false;

return Win32::TransparentBlt (dest, (int)destX, (int)destY, (int)sizeX, (int)sizeY,
                              src,  (int)srcX,  (int)srcY,  (int)sizeX, (int)sizeY, transColor);
}

//-----------------------------------------------------------------------------

bool txAlphaBlend (HDC dest, double destX, double destY, double sizeX, double sizeY,
                   HDC src,  double srcX,  double srcY,  double alpha)
{
assert (txOK());
if (!AlphaBlend) return false;

if (alpha < 0) alpha = 0;
if (alpha > 0) alpha = 1;

#ifndef AC_SRC_ALPHA
#define AC_SRC_ALPHA 0x01   // On some old MinGW versions, this is not defined.
#endif

BLENDFUNCTION blend = {AC_SRC_OVER, 0, (BYTE) (alpha * 255), AC_SRC_ALPHA};

return Win32::AlphaBlend (dest, (int)destX, (int)destY, (int)sizeX, (int)sizeY,
                          src,  (int)srcX,  (int)srcY,  (int)sizeX, (int)sizeY, blend);
}

//-----------------------------------------------------------------------------

bool txSelectRegion (double x0, double y0, double x1, double y1)
{
assert (txOK());

HRGN rgn = CreateRectRgn ((int)x0, (int)y0, (int)x1, (int)y1);
return txSelectObject (rgn);
}

//-----------------------------------------------------------------------------

bool txSelectObject (HGDIOBJ obj)
{
assert (txOK());
return _txSelect (obj);
}

//-----------------------------------------------------------------------------

int txBegin()
{
_txCanvas_SetLockRefresh (_txCanvas_LockRefresh + 1);
return _txCanvas_LockRefresh;
}

//-----------------------------------------------------------------------------

int txEnd()
{
_txCanvas_SetLockRefresh (_txCanvas_LockRefresh - 1);
return _txCanvas_LockRefresh;
}

//-----------------------------------------------------------------------------

bool txUpdateWindow (bool update)
{
return _txCanvas_SetLockRefresh (update? 0 : 1);
}

//-----------------------------------------------------------------------------

bool txSleep (int time)
{
int old = _txCanvas_SetLockRefresh (0);

Sleep (time);

_txCanvas_SetLockRefresh (old);
return old;
}

//-----------------------------------------------------------------------------

bool txTextCursor (bool mode)
{
bool old = _txConsole_CursorMode;

_txConsole_CursorMode = mode;

return old;
}

//-----------------------------------------------------------------------------

inline bool txLock()
{
EnterCriticalSection (&_txCanvas_LockBackBuf);
return true;
}

//-----------------------------------------------------------------------------

inline bool txUnlock()
{
LeaveCriticalSection (&_txCanvas_LockBackBuf);
return true;

}

//-----------------------------------------------------------------------------

template <typename T> inline
T txUnlock (T value)
{
txUnlock();
return value;
}

//-----------------------------------------------------------------------------

inline double  txMouseX()       { return _txMouseX; }
inline double  txMouseY()       { return _txMouseY; }
inline int     txMouseButtons() { return _txMouseButtons; }

//-----------------------------------------------------------------------------

bool txPlaySound (const char* filename, DWORD mode)
{
mode |= SND_FILENAME | SND_NODEFAULT | SND_NOWAIT;
if (mode & SND_LOOP) mode = mode & ~SND_SYNC | SND_ASYNC;
if (!filename) mode = SND_PURGE;

return PlaySound (filename, NULL, mode);
}

//-----------------------------------------------------------------------------

bool txSetDefaults()
{
assert (txOK());

return _txCanvas_SetDefaults() &&
       _txConsole_SetDefaults();
}

//=============================================================================

//! \cond Namespaces
namespace Internal {
//! \endcond Namespaces

//=============================================================================

bool _txCanvas_SetDefaults()
{
assert (txOK());

txLock();

RECT r = {0};
GetClientRect (_txConsole_Wnd, &r) NEEDED;
POINT size = { r.right - r.left, r.bottom - r.top };

_txSelect (GetStockObject (WHITE_PEN))   NEEDED;
_txSelect (GetStockObject (WHITE_BRUSH)) NEEDED;
_txSelect (CreateFont (size.y/25, size.y/50, 0, 0,
                       FW_REGULAR, FALSE, FALSE, FALSE,
                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                       DEFAULT_QUALITY, DEFAULT_PITCH, NULL)) NEEDED;

Win32::SetTextColor (txDC(), RGB (255, 255, 255));
Win32::SetBkMode    (txDC(), TRANSPARENT) NEEDED;

Win32::SetROP2      (txDC(), R2_COPYPEN) NEEDED;

txUnlock();
return true;
}

//-----------------------------------------------------------------------------

bool _txConsole_SetDefaults()
{
assert (txOK());

txLock();

HDC dc = _txCanvas_BackBuf[1];

CONSOLE_SCREEN_BUFFER_INFO con = {0};
GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &con) NEEDED;

RECT r = {0};
GetClientRect (_txConsole_Wnd, &r) NEEDED;

POINT phy = { r.right - r.left, r.bottom - r.top };
COORD log = { (short) (con.srWindow.Right  - con.srWindow.Left + 1),
              (short) (con.srWindow.Bottom - con.srWindow.Top  + 1) };

GetClientRect (_txCanvas_Wnd, &r) NEEDED;
POINT size = { r.right - r.left, r.bottom - r.top };

POINT fontSize = { (SHORT) ((1.0 * phy.x / log.X) / (1.0 * phy.x / size.x)),
                   (SHORT) ((1.0 * phy.y / log.Y) / (1.0 * phy.y / size.y)) };

_txSelect (txFontExist (_TX_CONSOLE_FONT)? CreateFont (fontSize.y, fontSize.x, 0, 0,
                                                       FW_REGULAR, FALSE, FALSE, FALSE,
                                                       DEFAULT_CHARSET,
                                                       OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                                       DEFAULT_QUALITY, FIXED_PITCH, _TX_CONSOLE_FONT)
                                           :
                                           GetStockObject (SYSTEM_FIXED_FONT),
                                           dc) NEEDED;

Win32::SetTextColor (dc, _TX_CONSOLE_COLOR);
Win32::SetBkMode    (dc, TRANSPARENT) NEEDED;

txUnlock();

return true;
}

//=============================================================================

bool _txInitialize (int sizeX, int sizeY, bool centered)
{
atexit (_txOnExit);

txUpdateWindow (false);

InitializeCriticalSection (&_txCanvas_LockBackBuf);

_txConsole_Attach();

POINT size = { sizeX, sizeY };
if (centered) { size.x *= -1; size.y *= -1; }

DWORD id = 0;
_txCanvas_Thread = CreateThread (NULL, 0, _txCanvas_ThreadProc, &size, 0, &id);
_txCanvas_Thread || THROW ("Cannot create _txCanvas_Thread: CreateThread() failed");
_txWaitFor (_txCanvas_OK());

#if _TX_USE_CONSOLE_THREAD
_txConsole_Thread = CreateThread (NULL, 0, _txConsole_ThreadProc, NULL, 0, &id);
_txConsole_Thread || THROW ("Cannot create _txConsole_Thread: CreateThread() failed");
_txWaitFor (_txConsole_OK());
#endif

txSetDefaults();

txUpdateWindow (true);

return true;
}

//-----------------------------------------------------------------------------

void _txOnExit()
{
_txRunning = false;
long style = GetWindowLong(_txCanvas_Wnd, GWL_STYLE);

if (style & WS_CAPTION)
   {
   if (!_txExit) WaitForSingleObject (_txCanvas_Thread, INFINITE);
   }

_txCleanup();
}

//-----------------------------------------------------------------------------

bool _txCleanup()
{
if (_txCanvas_Thread)  CloseHandle (_txCanvas_Thread)  NEEDED; _txCanvas_Thread  = NULL;
if (_txConsole_Thread) CloseHandle (_txConsole_Thread) NEEDED; _txConsole_Thread = NULL;

_txConsole_Detach();

DeleteCriticalSection (&_txCanvas_LockBackBuf);

return true;
}

//=============================================================================

DWORD WINAPI _txCanvas_ThreadProc (LPVOID data)
{
assert (data);

_txCanvas_CreateWindow (*(POINT*) data);
_txCanvas_Wnd || THROW ("Cannot create canvas: _txCanvas_CreateWindow() failed");

MSG msg = {0};
while (GetMessage (&msg, NULL, 0, 0))
   {
   TranslateMessage (&msg);
   DispatchMessage  (&msg);
   }

return (DWORD) msg.wParam;
}
//-----------------------------------------------------------------------------
HWND _txCanvas_CreateWindow (POINT clientSize)
 {
 const char className[] = __FILE__ "\\_txCanvas\\Class";

 //VV
 bool windowed    = true;

 WNDCLASSEX wc    = {0};
 wc.cbSize        = sizeof (wc);
 wc.style         = CS_HREDRAW | CS_VREDRAW;
 wc.lpfnWndProc   = _txCanvas_WndProc;
 wc.hInstance     = GetModuleHandle (NULL);
 wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
 wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
 wc.lpszClassName = className;
 RegisterClassEx (&wc) || THROW ("RegisterClass (\"%s\") failed"_ className);

 char name[256] = ""; GetModuleFileName (NULL, name, sizeof name) NEEDED;
 int centered = false;
 if (clientSize.x < 0 && clientSize.y < 0) { clientSize.x *= -1; clientSize.y *= -1; centered = true; }

 POINT scr     = { GetSystemMetrics (SM_CXSCREEN),
 GetSystemMetrics (SM_CYSCREEN) };
 POINT frame   = { GetSystemMetrics (SM_CXFIXEDFRAME),
 GetSystemMetrics (SM_CYFIXEDFRAME) };
 POINT caption = { 0, GetSystemMetrics (SM_CYCAPTION) };
 POINT size    = { clientSize.x + 2*frame.x, clientSize.y + 2*frame.y + caption.y };
 POINT center  = { scr.x / 2, scr.y / 2};

 //VV
 if (clientSize.x == 0 || clientSize.y == 0)
    {
    windowed      = false;
    clientSize    = scr;
    size          = scr;
    centered      = true;
    }

 if (!centered)
    {
    RECT r = {0}; GetWindowRect (_txConsole_Wnd, &r) NEEDED;
    center.x = (r.right + r.left) / 2;
    center.y = (r.bottom + r.top) / 2;
    }
//VV
DWORD wStyle = WS_POPUP;

if (windowed)
   {
   wStyle |= WS_BORDER | WS_CAPTION | WS_SYSMENU;
   }

_txCanvas_Wnd = CreateWindowEx (0, className, name, wStyle,
                                center.x - size.x/2, center.y - size.y/2, size.x, size.y,
                                NULL, NULL, GetModuleHandle (NULL), NULL);

_txCanvas_Wnd || THROW ("Cannot create canvas: CreateWindowEx (\"%s\") failed"_ className);


 ShowWindow   (_txCanvas_Wnd, SW_SHOW);
 UpdateWindow (_txCanvas_Wnd) NEEDED;

 if (_txConsole_Wnd)
     {
     SetWindowPos (_txConsole_Wnd, HWND_NOTOPMOST, center.x -
                   size.x*2/5, center.y - size.y*2/5, 0, 0,
                   SWP_NOSIZE | SWP_NOACTIVATE | SWP_HIDEWINDOW) NEEDED;
     }
 //VV
 if (windowed)
    {
    HMENU menu = GetSystemMenu (_txCanvas_Wnd, false); menu NEEDED;
    AppendMenu (menu, MF_SEPARATOR, 0, NULL) NEEDED;
    AppendMenu (menu, MF_STRING | MF_UNCHECKED,_txIDM_CONSOLE, "Show Console")     NEEDED;
    AppendMenu (menu, MF_STRING | MF_UNCHECKED,_txIDM_ABOUT,   "About Library...") NEEDED;
    CheckMenuItem (menu,  _txIDM_CONSOLE, (IsWindowVisible (_txConsole_Wnd))? MF_CHECKED : MF_UNCHECKED);
    }

 return _txCanvas_Wnd;
 }


bool _txCanvas_OK()
{
return _txCanvas_Thread &&
       _txCanvas_Wnd &&
       _txCanvas_BackBuf[0] &&
       _txCanvas_BackBuf[1];
}

//-----------------------------------------------------------------------------

bool _txCanvas_DestroyWindow()
{
if (!_txCanvas_Wnd) return false;

char className[128] = "";
GetClassName (_txCanvas_Wnd, className, sizeof className) NEEDED;

DestroyWindow (_txCanvas_Wnd) NEEDED;
UnregisterClass (className, GetModuleHandle (NULL)) NEEDED;

_txCanvas_Wnd = NULL;
return true;
}

//-----------------------------------------------------------------------------

int _txCanvas_SetLockRefresh (int count)
{
int old = _txCanvas_LockRefresh;

_txCanvas_LockRefresh = count;

if (!_txCanvas_LockRefresh) InvalidateRect (txWindow(), NULL, false);

return old;
}

//=============================================================================

bool _txCanvas_OnCreate (HWND wnd)
{
_txRunning = true;

(_txCanvas_BackBuf[0] = _txBuffer_Create (wnd)) NEEDED;
(_txCanvas_BackBuf[1] = _txBuffer_Create (wnd)) NEEDED;

#if !_TX_USE_CONSOLE_THREAD
SetTimer (wnd, _txCanvas_Timer, _TX_WINDOW_UPDATE_INTERVAL, NULL) NEEDED;
#endif

return true;
}

//-----------------------------------------------------------------------------

bool _txCanvas_OnDestroy (HWND wnd)
{
if (_txCanvas_Timer) KillTimer (wnd, _txCanvas_Timer) NEEDED;

if (_txCanvas_BackBuf[0]) _txBuffer_Delete (_txCanvas_BackBuf[0]); _txCanvas_BackBuf[0] = NULL;
if (_txCanvas_BackBuf[1]) _txBuffer_Delete (_txCanvas_BackBuf[1]); _txCanvas_BackBuf[1] = NULL;

PostQuitMessage (0);

// Should terminate user process (main() etc.) even if they are not finished.
// So, use exit().

if (_txRunning) { _txExit = true; exit (0); }

return true;
}

//-----------------------------------------------------------------------------

bool _txCanvas_OnClose (HWND)
{
assert (_txCanvas_OK());

char name[256] = __FILE__;
GetModuleFileName (NULL, name, sizeof name) NEEDED;

if (_txRunning &&
    MessageBox (_txCanvas_Wnd, "The program is still running. Terminate anyway?    ", name,
                MB_OKCANCEL | MB_ICONSTOP) != IDOK) return false;
return true;
}

//-----------------------------------------------------------------------------

bool _txCanvas_OnPaint (HWND wnd)
{
assert (wnd);                      // assert (_txCanvas_OK()); ??W95 - Failed at window close
if (!_txCanvas_OK()) return false; //                          ??W95 - Changed-to

PAINTSTRUCT ps = {0};
HDC dc = BeginPaint (wnd, &ps); dc NEEDED;

RECT r = {0};
GetClientRect (wnd, &r) NEEDED;
POINT size = { r.right - r.left, r.bottom - r.top };

if (!_txCanvas_LockRefresh)
    {
    txGDI ((Win32::BitBlt (_txCanvas_BackBuf[1], 0, 0, size.x, size.y, txDC(), 0, 0, SRCCOPY))) NEEDED;

    if (_txConsole_OK()) _txConsole_Draw (_txCanvas_BackBuf[1]);
    }

txGDI ((Win32::BitBlt (dc, 0, 0, size.x, size.y, _txCanvas_BackBuf[1], 0, 0, SRCCOPY))) NEEDED;

EndPaint (wnd, &ps) NEEDED;
return true;
}

//-----------------------------------------------------------------------------

bool _txCanvas_OnChar (HWND, WPARAM ch)
{
// assert (_txCanvas_OK()); !!!W95 - Faied at window close

INPUT_RECORD evt = {0};

evt.EventType                        = KEY_EVENT;
evt.Event.KeyEvent.bKeyDown          = true;
evt.Event.KeyEvent.wRepeatCount      = 1;
evt.Event.KeyEvent.wVirtualKeyCode   = 0;
evt.Event.KeyEvent.wVirtualScanCode  = 0;
evt.Event.KeyEvent.uChar.AsciiChar   = (char) ch;
evt.Event.KeyEvent.dwControlKeyState = 0;

DWORD written = 0;
WriteConsoleInput (GetStdHandle (STD_INPUT_HANDLE), &evt, 1, &written) NEEDED;

return true;
}

//-----------------------------------------------------------------------------

bool _txCanvas_OnMouse (HWND, WPARAM buttons, LPARAM coords)
{
// assert (_txCanvas_OK()); !!!W95 - Faied at window close

_txMouseX       = LOWORD (coords);
_txMouseY       = HIWORD (coords);
_txMouseButtons = (int) buttons;

return true;
}

//-----------------------------------------------------------------------------

bool _txCanvas_OnTimer (HWND, WPARAM)
{
// assert (_txCanvas_OK()); ??Win95 On exit App - Check failed

InvalidateRect (_txCanvas_Wnd, NULL, false) NEEDED;
UpdateWindow   (_txCanvas_Wnd)              NEEDED;

return true;
}

//-----------------------------------------------------------------------------

bool _txCanvas_OnCmdConsole (HWND wnd, WPARAM cmd)
{
assert (wnd); assert (_txCanvas_OK()); assert (_txConsole_OK());

bool visible = IsWindowVisible (_txConsole_Wnd) != 0;

ShowWindow (_txConsole_Wnd, visible? SW_HIDE : SW_SHOW);

visible = IsWindowVisible (_txConsole_Wnd) != 0;
CheckMenuItem (GetSystemMenu (wnd, false), (int)cmd, visible? MF_CHECKED : MF_UNCHECKED);

return true;
}

//-----------------------------------------------------------------------------

bool _txCanvas_OnCmdAbout (HWND wnd, WPARAM cmd)
{
assert (wnd);

MessageBox (NULL, "\nSimple Graphics Library with BGI Emulation\n\n"
                  _TX_VERSION "  (c) Ded (TX), VV (BGI) 2005-06\n\n"
                  "Compiled with: " __FILE__ ", at "__DATE__ " " __TIME__"      \n",
                  "About TX Library",
                  MB_ICONINFORMATION);

return true;
}

//-----------------------------------------------------------------------------

LRESULT CALLBACK _txCanvas_WndProc (HWND wnd, UINT msg, WPARAM wpar, LPARAM lpar)
{
switch (msg)
    {
    case WM_CREATE:       _txCanvas_OnCreate     (wnd);         break;

    case WM_CLOSE:        if (!_txCanvas_OnClose (wnd))         return 0;
    case WM_DESTROY:      _txCanvas_OnDestroy    (wnd);         break;

    case WM_PAINT:        _txCanvas_OnPaint      (wnd);         break;
    case WM_CHAR:         _txCanvas_OnChar       (wnd, wpar);   break;
    case WM_TIMER:        _txCanvas_OnTimer      (wnd, wpar);   break;

    case WM_LBUTTONUP:
    case WM_LBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MOUSEMOVE:    _txCanvas_OnMouse  (wnd, wpar, lpar); break;
    }

if (msg == WM_SYSCOMMAND) switch (wpar)
    {
    case _txIDM_ABOUT:    _txCanvas_OnCmdAbout   (wnd, wpar);   break;
    case _txIDM_CONSOLE:  _txCanvas_OnCmdConsole (wnd, wpar);   break;
    }

return DefWindowProc (wnd, msg, wpar, lpar);
}

//=============================================================================

bool _txConsole_Attach()
{
FreeConsole();
AllocConsole();

HANDLE con = GetStdHandle (STD_OUTPUT_HANDLE); con NEEDED;
COORD size = { 80, 25 };
SetConsoleScreenBufferSize (con, size) NEEDED;

_txConsole_Wnd = _txConsole_GetWindow();

return true;
}

//-----------------------------------------------------------------------------

bool _txConsole_OK()
{
return
#if _TX_USE_CONSOLE_THREAD
      _txConsole_Thread &&
#endif
      _txConsole_Wnd != NULL;
}

//-----------------------------------------------------------------------------

bool _txConsole_Detach()
{
FreeConsole();
return true;
}

//-----------------------------------------------------------------------------

DWORD WINAPI _txConsole_ThreadProc (LPVOID)
{
assert (_txConsole_OK()); assert (_txCanvas_OK());

SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_IDLE) NEEDED;

while (_txDummy())
    {
    InvalidateRect (_txCanvas_Wnd, NULL, false) NEEDED;
    UpdateWindow   (_txCanvas_Wnd)              NEEDED;

    Sleep (_TX_WINDOW_UPDATE_INTERVAL);
    }

return 0;
}

//-----------------------------------------------------------------------------

bool _txConsole_Draw (HDC dc)
{
assert (_txConsole_OK()); assert (_txCanvas_OK());

txLock();

CONSOLE_SCREEN_BUFFER_INFO con = {0};
GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &con) NEEDED;

TCHAR* buf = new TCHAR [con.dwSize.X * con.dwSize.Y + 1]; buf NEEDED;

COORD zero = {0};
DWORD read = 0;
ReadConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE), buf,
                            con.dwSize.X * con.dwSize.Y * sizeof (TCHAR),
                            zero, &read) NEEDED;
//OemToCharBuff (buf, buf, read) NEEDED;

SIZE fontSz = {0};
Win32::GetTextExtentPoint32 (dc, "W", 1, &fontSz) NEEDED;

int sizeX = con.srWindow.Right - con.srWindow.Left + 1;
for (int y = con.srWindow.Top; y <= con.srWindow.Bottom; y++)
    Win32::TextOut (dc, 0, y*fontSz.cy, buf + y*con.dwSize.X + con.srWindow.Left, sizeX) NEEDED;

delete[] buf;

if (_txConsole_CursorMode &&
    GetTickCount() % _TX_CURSOR_BLINK_INTERVAL*2 > _TX_CURSOR_BLINK_INTERVAL &&
    In (con.dwCursorPosition, con.srWindow))
    {
    Win32::TextOut (dc,
                   (con.dwCursorPosition.X - con.srWindow.Left)*fontSz.cx,
                   (con.dwCursorPosition.Y - con.srWindow.Top) *fontSz.cy + 1,
                    "_", 1) NEEDED;
    }

txUnlock();
return true;
}

//-----------------------------------------------------------------------------

HWND _txConsole_GetWindow()
{
static HWND (WINAPI* GetConsoleWindow) () =
      (HWND (WINAPI*)()) _txImport ("Kernel32", "GetConsoleWindow", false);

if (GetConsoleWindow) return GetConsoleWindow();

SetLastError (0);

char title[1024] = "";
GetConsoleTitle (title, sizeof (title));

char unique [128] = "";
LARGE_INTEGER time = {0};
QueryPerformanceCounter (&time) NEEDED;
sprintf (unique, __FILE__ "(%d)\\Temp Title %08lx%08lx", __LINE__, time.HighPart, time.LowPart);

SetConsoleTitle (unique) NEEDED;

HWND con = NULL;
_txWaitFor (con = FindWindow (NULL, unique));

SetConsoleTitle (title) NEEDED;

con || THROW ("Cannot find console window");
return con;
}

//=============================================================================

HDC _txBuffer_Create (HWND wnd, const POINT* size, HBITMAP bmap)
{
assert (wnd);

txLock();

HDC wndDC = GetDC (wnd); wndDC NEEDED;
(Win32::GetDeviceCaps (wndDC, RASTERCAPS) & RC_BITBLT) || THROW ("GetDeviceCaps(): RASTERCAPS: RC_BITBLT not supported");

RECT r = {0};
GetClientRect (wnd, &r) NEEDED;
POINT sz = { r.right - r.left, r.bottom - r.top };
if (!size) size = &sz;

HDC dc = Win32::CreateCompatibleDC (wndDC);
dc || THROW ("Cannot create buffer: CreateCompatibleDC() failed");

if (!bmap) bmap = Win32::CreateCompatibleBitmap (wndDC, size->x, size->y);
bmap || THROW ("Cannot create buffer: CreateCompatibleBitmap() failed");

Win32::SelectObject (dc, bmap) NEEDED;

Win32::PatBlt (dc, 0, 0, size->x, size->y, BLACKNESS) NEEDED;

ReleaseDC (wnd, wndDC) NEEDED;

txUnlock();
return dc;
}

//-----------------------------------------------------------------------------

bool _txBuffer_Delete (HDC dc)
{
if (!dc) return false;

txLock();

HBITMAP zeroBitmap = Win32::CreateCompatibleBitmap (dc, 0, 0); zeroBitmap NEEDED;
HRGN    zeroRgn    = Win32::CreateRectRgn (0, 0, 0, 0);        zeroRgn    NEEDED;

_txSelect (Win32::GetStockObject (NULL_PEN),    dc) NEEDED;
_txSelect (Win32::GetStockObject (NULL_BRUSH),  dc) NEEDED;
_txSelect (Win32::GetStockObject (SYSTEM_FONT), dc) NEEDED;
_txSelect (zeroBitmap,                          dc) NEEDED;
_txSelect (zeroRgn,                             dc); // ??W95 NEEDED;
Win32::DeleteDC (dc)                            NEEDED;

Win32::DeleteObject (zeroBitmap)                NEEDED;
Win32::DeleteObject (zeroRgn)                   NEEDED;

txUnlock();
return true;
}

//=============================================================================

bool _txSelect (HGDIOBJ obj, HDC dc)
{
txLock();

obj = Win32::SelectObject (dc, obj); obj NEEDED;
if (obj) Win32::DeleteObject (obj); // NEEDED; ??Win95 - On exit App - Check Failed

txUnlock();

return obj != NULL;
}

//=============================================================================

bool _Throw (const char file[], int line, const char func[], DWORD error,
             const char msg[], ...)
{
 const size_t MAXSTR = 1024;

bool fatal = (msg && *msg == '\a')? (msg++, true) : false;
va_list arg; va_start (arg, msg);
char str[MAXSTR] = "", *s = str;

if (file)
    s += sprintf (s, "THROW(): %s", file);

if (line)
    s += sprintf (s, " (%d)", line);

if (func)
    s += sprintf (s, " %s()", func);

if (error)
    s += sprintf (s, ": Error %lu: ", error),
    s += FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, error, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
                        s, (DWORD) (sizeof (str) - (s - str)), NULL) - 3;
if (msg && *msg)
    s +=  sprintf (s, ": "),
    s += vsprintf (s, msg, arg);

s += sprintf (s, "    \n");

printf (str);
OutputDebugString (str);
MessageBox (NULL, str, fatal? "System: Fatal Error" : "System",
            MB_ICONSTOP | MB_TOPMOST | MB_SYSTEMMODAL);

if (fatal) abort();

va_end (arg);
return false;
}

//=============================================================================

FARPROC _txImport (const char lib[], const char name[], int required)
{
FARPROC addr = GetProcAddress (LoadLibrary (lib), name);

if (!addr && required) THROW ("\aCannot import %s\\%s" _ lib _ name);

return addr;
}

//@}
//! \endcond Internal
//=============================================================================
//! \cond Namespaces

} // namespace Internal
} // namespace TX
} // anonymous namespace

using namespace TX;
using namespace TX::Internal::Win32;

//! \endcond Namespaces
//=============================================================================

#endif // __TXLIB_H

//=============================================================================
//  \name    ������� �������������
//=============================================================================

//-----------------------------------------------------------------------------
/*! \page    Tutorial_1st ������: ����������

	\section Tutorial_1st_01 ��������� ���������� ���������

	���������� ��������� �� � (��� �++) ������� �� ���� ������: �������
	����������� ��������� � ������� ������� ���������. ���������� ������,
	� ������� �������� �� ������ ������� �������.

	\section Tutorial_1st_02 ������ ����������� ���������

	��������� (�������) ����������� ��������� ��������� ������ � ������
	����� ��������� � �������� ������ ���:

	\code
    #include <stdio.h>
    #include "Graphics.h"
	\endcode

	\c Stdio.h � \c Graphics.h - ����� ���������, ������� ������������ � �����
	���������. ����� ����� �� ������ ������������ �������, ������� � ����������,
	����������� � ���� ������. ������, ��� �����, ��������� ���������� �� �����,
	���� ��� � �� ������. ����� ������������ ����� ���������, ������ ����� ����
	����� �������.

	\section Tutorial_1st_03 ������� ������� ���������

	��������� �� � (�++) ������� �� �������. ������� - ��� �������� �����-����
	�������� � �������� ������ (���������).

	��������,

	\code
    void main()
    {
    txCreateWindow (800, 600);
    txLine (320, 290, 320, 220);
    }
	\endcode

	������� ������� - ��� �������, � ������� ���������� ���������� ���������.
	�� ��� - \c main(). ������ ����������, ��� ���� ���� ������ � �������, �.�.,
	�� �������� �����-�� ��������. ��� ����, ����� ������� ������ ������, ��
	����� \a �������. ������� \c main() �������� ���� ������������ �������
	����������. ����� \c void ��������, ��� \c main() �� ����� ����������
	����, ��� �� �������, �����-���� ����������� ����� ����������. ���
	�������������, �.�. �� ������ � �� ���������, � ������ ������ �� ������.

	��������, ���������� � �������, ����������� � �������� ������ \c { � \c }.
	��� ���������� ������ � ����� �������.

	������ ������� �������� ������ ������, ������� ���-�� ������ �� ������.
	����� ���������, ���, ��� ��� ��������� ����������, ����� ������ ������,
	���������� ���� ����� ��������� �� ������. ��� ������������ �������
	���������� ���������. ������ ������ � ���������������� �������������
	������ ������ ������ � ������� �����.

	��� ��������� ��������� � ����, ����� � ��� �� ���������� ������, �����
	�����, ����� � ������ ������ � ��� ������ �������. ������ �� ������ ��
	����������� ������� ������, ����� �������, �� � ����� ������ ��������.
	������� �������� ������ ��������� �������� �� ���, � �������������
	���������� ���� ��� ������ � �����������. ������ � ����� �����������
	������� ��������� ����� ������� ���� ������, ������� ������.

	������ ����� ���������� ���������:

	\code
    #include "Graphics.h"
    void   main(){
    txCreateWindow(800,600);  // ��-�����, ��� ������ ��� ����. :)
    txLine(320,290,320,220);
     txLine (320, 290,280,350);
      txLine(320, 290,360,350);
     txLine(320,230,270,275);
    txLine(320,230, 400,220);
    txCircle(320,190,30);
      txSelectFont( "Times",60);
    txTextOut(240,400,"Hello, world!");
    }
    \endcode

	��� ������� ��������� �������� ����� ������������ ������������ �������,
	� ������� ������� ����� ���� ���������� �����-������, � ��� OY �������
	����. ��� ��������� ����������, �� �������� ������. :) ��������, �������

	\code
    txLine (320, 290, 320, 220);
    \endcode

    �������� ����� �� ����� x=320 � �=290 � ����� � x=320 � y=220.

	������ ������� ������������� ������ � �������. ��� - ������ ����� � �������
	�����. ����� � ������� �������� � ����� ������� \a ������������ ��������
	��� ����������. ��������, � ������ � \c txCreateWindow (800, 600) ����� �
	������� ��������, �.�. � ���� ������ "��������� �����" � ���, ��� ����
	������� ���� ��� ���������. � ������ � <tt>void main()</tt> - �� ��������,
	�.�. �������� ������� \c main() �� ��������� (�� ����� ����, ��� ��� ������
	������).

	���� � ��������� ������������ ������, ��� ����������� � ������� �������,
	��������:

	\code
    txTextOut (240, 400, "Hello, world!");
    \endcode

	���� � ��������� ����������� ����� � ������� ������, �� ��� �����
	���������� �� ����� ����� ������, � �� �������, ��� � ������� �����.

	\section Tutorial_1st_04 ���������������� ������

	� ������� ���������� ������ ������ ���� �����:

	- ������ ������ (����������, ����������) - �� �������� ���������������
	  �������� <i>(syntax error).</i> ��� ���������� �� ������� ���������,
	  �� ������ �������� ��������� � �������� ��� (������ ����������). �������
	  �� �������� �������� ������� ����������. ����������� ���� ��� ���� ��
	  ��������� � ��������� �� �����������.

	- ���������� ������ - ��� ���������� ����� ������� ���������, ��� ����
	  ��� ���������� ������ ��� (������ ������� ��������������, \a warnings).
	  �� �������� �������� ������� ����������.

	����������� ��� �������������� ������ �� ���� ������ ���������� ��-��
	����������������. ���������������� �������������� ������:

	- ������ �������� �����, �������� ��������� � ������:
	  \code
	  #iclude "grafics.h"
	  vod maim()
	  tx Line (10, 10, 20, 20)
	  \endcode

	- ������ ������� � ��������� �����:
	  \code
	  txcircle (100, 100, 10)
	  \endcode

	- �� ������ ������:
	  \code
	  void main
	  \endcode

	- �������� �������:
	  \code
	  tx�ircle (100 100 10)
	  \endcode

	- �������� ����� � �������:
	  \code
	  txSelectFont ("Times", 60)
	  \endcode

	- �������� ��� ������ �������:
	  \code
	  txSelectFont (Times, 60)
	  txSelectFont ('Times', 60)
	  \endcode

	- ������ ������ ����� � �������:
	  \code
	  void main();
	  \endcode

	- �������� ������� ����� ����� ����� �������:
	  \code
	  3,1415
	  \endcode

	- �������� �������� ������:
  	  \code
      void main()
      txCreateWindow (800, 600);
      txLine (320, 290, 320, 220);
	  \endcode

	- �������� ������ ����������� ��� ����������� ������, ��� ����� ������,
	  ������ ���������� �������� ������, ��� ������ ���� ������:
  	  \code
      void main()
      {
      txCreateWindow (800, 600);

      txLine (320, 290, 320, 220;  // �� ������� ������� ������
      }
	  \endcode
  	  \code
      void main()
      {
      txCreateWindow {800, 600};   // �������� ������ ������ �������
      }

      txLine (320, 290, 320, 220;  // ������� �� ��������� ������� main()
      }                            // ������ ������
	  \endcode

	- �������� ������� �� ������� �������� ������
  	  \code
      void main()
      {
      txCreateWindow (800, 600);
      }

      txLine (320, 290, 320, 220); // ������� �� ��������� ������� main()
	  \endcode

	������ � ���������� ������. ��������, �� �� ������� ������ ���� ���������
	(�� ��������� �� �����), ��� ���������� ���� ������ ������ ������, � ���
	������� ����������, ��� ������ �������� ����������. ��� ������ ����������
	����� ������� ���������. �� ����� ������, ���� ��������� �� ����� ������
	��� ������� ���� �� ������, � ��� �������, � ������� ��� ������ � ���������.

	\section Tutorial_1st_Code ����������� ������
    \include TXEx01.cpp
*/
//-----------------------------------------------------------------------------
/*! \page Tutorial_1stEx ������: ���������� :)

	\section Tutorial_1stEx_Code ����������� ������
    \include TXEx02.cpp
*/
//-----------------------------------------------------------------------------
/*! \page Tutorial_Functions ������: �������

	\section Tutorial_Functions_Code ����������� ������
    \include TXEx03.cpp
*/
//-----------------------------------------------------------------------------
/*! \page Tutorial_Parameters ������: ������� � �����������

	\section Tutorial_Parameters_Code ����������� ������
    \include TXEx04.cpp
*/
//-----------------------------------------------------------------------------
/*! \page Tutorial_While ������: �����

	\section Tutorial_While_Code ����������� ������
    \include TXEx05.cpp
*/
//-----------------------------------------------------------------------------
/*! \page Tutorial_For ������: ����� (2)

	\section Tutorial_For_Code ����������� ������
    \include TXEx06.cpp
*/





///////////////////////////////////////////////////////////////////////////////
// BGI Support
///////////////////////////////////////////////////////////////////////////////

#ifndef __TX_GRAPHICS_H
#define __TX_GRAPHICS_H


#ifdef BGISUPPORTCHECK
#define BGINOSUPPORT printf ("Unsupported BGI function: %s", __FUNCTION__);
#else
#define BGINOSUPPORT
#endif

// BGI Colors------------------------------------------------------------------

//! \cond Namespaces
namespace {
namespace TX_BGI {
//! \endcond Namespaces


//! \cond Internal
enum COLORS {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE,
};


COLORREF ColorBGI2TX(int color){
   COLORREF txcol = TX_WHITE;
   switch (color){
       case BLACK:           txcol = TX_BLACK;       break;
       case BLUE:            txcol = TX_BLUE;        break;
       case GREEN:           txcol = TX_GREEN;       break;
       case CYAN:            txcol = TX_CYAN;        break;
       case RED:             txcol = TX_RED;         break;
       case MAGENTA:         txcol = TX_BLACK;       break;
       case BROWN:           txcol = TX_BROWN;       break;
       case LIGHTGRAY:       txcol = TX_LIGHTGRAY;   break;
       case DARKGRAY:        txcol = TX_DARKGRAY;    break;
       case LIGHTBLUE:       txcol = TX_LIGHTBLUE;   break;
       case LIGHTGREEN:      txcol = TX_LIGHTGREEN;  break;
       case LIGHTCYAN:       txcol = TX_LIGHTCYAN;   break;
       case LIGHTRED:        txcol = TX_LIGHTRED;    break;
       case LIGHTMAGENTA:    txcol = TX_LIGHTMAGENTA;break;
       case YELLOW:          txcol = TX_YELLOW;      break;
       case WHITE:           txcol = TX_WHITE;       break;
       default:              txcol = color;
  }
  return txcol;
}

int  ColorTX2BGI(int color){
   int  txcol = WHITE;
   switch (color){
       case TX_BLACK:           txcol = BLACK;       break;
       case TX_BLUE:            txcol = BLUE;        break;
       case TX_GREEN:           txcol = GREEN;       break;
       case TX_CYAN:            txcol = CYAN;        break;
       case TX_RED:             txcol = RED;         break;
       case TX_MAGENTA:         txcol = BLACK;       break;
       case TX_BROWN:           txcol = BROWN;       break;
       case TX_LIGHTGRAY:       txcol = LIGHTGRAY;   break;
       case TX_DARKGRAY:        txcol = DARKGRAY;    break;
       case TX_LIGHTBLUE:       txcol = LIGHTBLUE;   break;
       case TX_LIGHTGREEN:      txcol = LIGHTGREEN;  break;
       case TX_LIGHTCYAN:       txcol = LIGHTCYAN;   break;
       case TX_LIGHTRED:        txcol = LIGHTRED;    break;
       case TX_LIGHTMAGENTA:    txcol = LIGHTMAGENTA;break;
       case TX_YELLOW:          txcol = YELLOW;      break;
       case TX_WHITE:           txcol = WHITE;       break;
       default:              txcol = color;
  }
  return txcol;
}

// Fonts ----------------------------------------------------------------------

const char *BGIFontNames[]={
  "System",
  "Tahoma",
  "Times New Roman",
  "Verdana",
  "Arial",
  "System",
  "Tahoma",
  "Times New Roman",
  "Verdana",
  "Arial"
};

// Other constants ------------------------------------------------------------

enum graphics_errors {      /* graphresult error return codes */
    grOk               =   0,
    grNoInitGraph      =  -1,
    grNotDetected      =  -2,
    grFileNotFound     =  -3,
    grInvalidDriver    =  -4,
    grNoLoadMem        =  -5,
    grNoScanMem        =  -6,
    grNoFloodMem       =  -7,
    grFontNotFound     =  -8,
    grNoFontMem        =  -9,
    grInvalidMode      = -10,
    grError            = -11,   /* generic error */
    grIOerror          = -12,
    grInvalidFont      = -13,
    grInvalidFontNum   = -14,
    grInvalidVersion   = -18
};

enum graphics_drivers {     /* define graphics drivers */
    DETECT,         /* requests autodetection */
    CGA, MCGA, EGA, EGA64, EGAMONO, IBM8514,    /* 1 - 6 */
    HERCMONO, ATT400, VGA, PC3270,          /* 7 - 10 */
    CURRENT_DRIVER = -1
};

enum graphics_modes {       /* graphics modes for each driver */
    CGAC0      = 0,  /* 320x200 palette 0; 1 page   */
    CGAC1      = 1,  /* 320x200 palette 1; 1 page   */
    CGAC2      = 2,  /* 320x200 palette 2: 1 page   */
    CGAC3      = 3,  /* 320x200 palette 3; 1 page   */
    CGAHI      = 4,  /* 640x200 1 page          */
    MCGAC0     = 0,  /* 320x200 palette 0; 1 page   */
    MCGAC1     = 1,  /* 320x200 palette 1; 1 page   */
    MCGAC2     = 2,  /* 320x200 palette 2; 1 page   */
    MCGAC3     = 3,  /* 320x200 palette 3; 1 page   */
    MCGAMED    = 4,  /* 640x200 1 page          */
    MCGAHI     = 5,  /* 640x480 1 page          */
    EGALO      = 0,  /* 640x200 16 color 4 pages    */
    EGAHI      = 1,  /* 640x350 16 color 2 pages    */
    EGA64LO    = 0,  /* 640x200 16 color 1 page     */
    EGA64HI    = 1,  /* 640x350 4 color  1 page     */
    EGAMONOHI  = 0,  /* 640x350 64K on card, 1 page - 256K on card, 4 pages */
    HERCMONOHI = 0,  /* 720x348 2 pages         */
    ATT400C0   = 0,  /* 320x200 palette 0; 1 page   */
    ATT400C1   = 1,  /* 320x200 palette 1; 1 page   */
    ATT400C2   = 2,  /* 320x200 palette 2; 1 page   */
    ATT400C3   = 3,  /* 320x200 palette 3; 1 page   */
    ATT400MED  = 4,  /* 640x200 1 page          */
    ATT400HI   = 5,  /* 640x400 1 page          */
    VGALO      = 0,  /* 640x200 16 color 4 pages    */
    VGAMED     = 1,  /* 640x350 16 color 2 pages    */
    VGAHI      = 2,  /* 640x480 16 color 1 page     */
    PC3270HI   = 0,  /* 720x350 1 page          */
    IBM8514LO  = 0,  /* 640x480 256 colors      */
    IBM8514HI  = 1   /*1024x768 256 colors      */
};

enum line_styles {      /* Line styles for get/setlinestyle */
    SOLID_LINE   = 0,
    DOTTED_LINE  = 1,
    CENTER_LINE  = 2,
    DASHED_LINE  = 3,
    USERBIT_LINE = 4,   /* User defined line style */
};

enum line_widths {      /* Line widths for get/setlinestyle */
    NORM_WIDTH  = 1,
    THICK_WIDTH = 3,
};

enum font_names {
    DEFAULT_FONT    = 0,    /* 8x8 bit mapped font */
    TRIPLEX_FONT    = 1,    /* "Stroked" fonts */
    SMALL_FONT  = 2,
    SANS_SERIF_FONT = 3,
    GOTHIC_FONT = 4,
    SCRIPT_FONT = 5,
    SIMPLEX_FONT = 6,
    TRIPLEX_SCR_FONT = 7,
    COMPLEX_FONT = 8,
    EUROPEAN_FONT = 9,
    BOLD_FONT = 10
};

#define HORIZ_DIR   0   /* left to right */
#define VERT_DIR    1   /* bottom to top */

enum fill_patterns {        /* Fill patterns for get/setfillstyle */
    EMPTY_FILL,     /* fills area in background color */
    SOLID_FILL,     /* fills area in solid fill color */
    LINE_FILL,      /* --- fill */
    LTSLASH_FILL,       /* /// fill */
    SLASH_FILL,     /* /// fill with thick lines */
    BKSLASH_FILL,       /* \\\ fill with thick lines */
    LTBKSLASH_FILL,     /* \\\ fill */
    HATCH_FILL,     /* light hatch fill */
    XHATCH_FILL,        /* heavy cross hatch fill */
    INTERLEAVE_FILL,    /* interleaving line fill */
    WIDE_DOT_FILL,      /* Widely spaced dot fill */
    CLOSE_DOT_FILL,     /* Closely spaced dot fill */
    USER_FILL       /* user defined fill */
};

enum putimage_ops {     /* BitBlt operators for putimage */
    COPY_PUT,        /* MOV */
    XOR_PUT,        /* XOR */
    OR_PUT,         /* OR  */
    AND_PUT,        /* AND */
    NOT_PUT         /* NOT */
};

enum text_just {        /* Horizontal and vertical justification
                           for settextjustify */
    LEFT_TEXT,
    CENTER_TEXT,
    RIGHT_TEXT,

    BOTTOM_TEXT,
     /* CENTER_TEXT = 1,  already defined above */
    TOP_TEXT,
};

#define MAXCOLORS 15

struct palettetype {
    unsigned char size;
    signed char colors[MAXCOLORS+1];
};

struct linesettingstype {
    int linestyle;
    unsigned upattern;
    int thickness;
};

struct textsettingstype {
    int font;
    int direction;
    int charsize;
    int horiz;
    int vert;
};

struct fillsettingstype {
    int pattern;
    int color;
};

struct pointtype {
    int x, y;
};

struct viewporttype {
    int left, top, right, bottom;
    int clip;
};

struct arccoordstype {
    int x, y;
    int xstart, ystart, xend, yend;
};
//! \endcond Internal

// BGI functions --------------------------------------------------------------
//! \ingroup BGI
void arc(int _x, int _y, int _stangle, int _endangle, int _radius);

//! \ingroup BGI
void bar(int _left, int _top, int _right, int _bottom);

//! \ingroup BGI
void circle(int _x, int _y, int _radius);

//! \ingroup BGI
void cleardevice(void);

//! \ingroup BGI
void clearviewport(void);

//! \ingroup BGI
void closegraph(void);

//! \ingroup BGI
void fillpoly(int _numpoints, const int *_polypoints);

//! \ingroup BGI
void drawpoly(int _numpoints, const int *_polypoints);

//! \ingroup BGI
void ellipse(int _x, int _y, int _stangle, int _endangle,
             int _xradius, int _yradius);

//! \ingroup BGI
void fillellipse( int _x, int _y, int _xradius, int _yradius );


//! \ingroup BGI
void floodfill(int _x, int _y, int _border);

//void getarccoords(struct arccoordstype *_arccoords);

void getaspectratio(int *_xasp, int *_yasp);

//! \ingroup BGI
int getbkcolor(void);

//! \ingroup BGI
int getcolor(void);

//struct palettetype *  getdefaultpalette( void );

//char* getdrivername(void);


void getfillpattern(char *_pattern);

//void  getfillsettings(struct fillsettingstype *_fillinfo);

int getgraphmode(void);


void getimage(int _left, int _top, int _right, int _bottom,
                   void *_bitmap);

//void getlinesettings(struct linesettingstype *_lineinfo);

//! \ingroup BGI
int getmaxcolor(void);

int getmaxmode(void);

//! \ingroup BGI
int getmaxx(void);

//! \ingroup BGI
int getmaxy(void);

char *getmodename( int _mode_number );

void getmoderange(int _graphdriver, int *_lomode,
                   int *_himode);

//! \ingroup BGI
unsigned  getpixel(int _x, int _y);

// void getpalette(struct palettetype *_palette);

//! \ingroup BGI
int getpalettesize( void );

// void gettextsettings(struct textsettingstype *_texttypeinfo);

// void getviewsettings(struct viewporttype *_viewport);

//! \ingroup BGI
int getx(void);

//! \ingroup BGI
int gety(void);

//! \ingroup BGI
void graphdefaults(void);

char* grapherrormsg(int _errorcode);

void   _graphfreemem(void *_ptr, unsigned _size);

void * _graphgetmem(unsigned _size);

int    graphresult(void);

unsigned  imagesize(int _left, int _top, int _right, int _bottom);

//! \ingroup BGI
void initgraph(int  *_graphdriver = NULL,
               int  *_graphmode = NULL,
               const char *_pathtodriver = NULL);


//int     installuserdriver( const char *_name,
//                int huge (*detect)(void) );

int installuserfont( const char *_name );

//! \ingroup BGI
void line(int _x1, int _y1, int _x2, int _y2);

//! \ingroup BGI
void linerel(int _dx, int _dy);

//! \ingroup BGI
void lineto(int _x, int _y);

//! \ingroup BGI
void moverel(int _dx, int _dy);

//! \ingroup BGI
void moveto(int _x, int _y);

//! \ingroup BGI
void outtext(const char *_textstring);

//! \ingroup BGI
void outtextxy(int _x, int _y, const char *_textstring);

//! \ingroup BGI
void pieslice(int _x, int _y, int _stangle, int _endangle,
                   int _radius);


void putimage(int _left, int _top, const void *_bitmap, int _op);

//! \ingroup BGI
void putpixel(int _x, int _y, int _color);

//! \ingroup BGI
void rectangle(int _left, int _top, int _right, int _bottom);

//! \ingroup BGI
void restorecrtmode(void);

void sector( int _X, int _Y, int _StAngle, int _EndAngle,
                  int _XRadius, int _YRadius );

void setactivepage(int _page);

//void setallpalette(const struct palettetype *_palette);

//void        setaspectratio( int _xasp, int _yasp );

//! \ingroup BGI

void setbkcolor(int _color);

//! \ingroup BGI
void setcolor(int _color);

void  setfillpattern(const char *_upattern, int _color);

//! \ingroup BGI
//! \brief   ������������ ������ ���� �������, ����� ������������.
void  setfillstyle(int _pattern, int _color);

unsigned setgraphbufsize(unsigned _bufsize);

void setgraphmode(int _mode);

//! \ingroup BGI
//! \brief   ������������ ������ ������� �����, ����� ������������.
void setlinestyle(int _linestyle, unsigned _upattern,
                   int _thickness);

void setpalette(int _colornum, int _color);


void setrgbpalette(int _colornum,
                   int _red, int _green, int _blue);

//! \ingroup BGI
void settextjustify(int _horiz, int _vert);

//! \ingroup BGI
//! \brief ������������ ������ Windows, ������ ������������ �������� �� �����������.
void settextstyle(int _font, int _direction, int _charsize);


void setusercharsize(int _multx, int _divx,
                      int _multy, int _divy);
//! \ingroup BGI
void setviewport(int _left, int _top, int _right, int _bottom,
                  int _clip);

void setvisualpage(int _page);

//! \ingroup BGI
void setwritemode(int _mode);

//! \ingroup BGI
int textheight(const char *_textstring);

//! \ingroup BGI
int  textwidth(const char *_textstring);


//== Other functions ===========================================================
//! \ingroup BGI
//! \brief   ������ ���������� ������� ��� BGI-�������� :-)
void delay(int msecs);


//-----------------------------------------------------------------------------


//! \cond Internal

void arc(int _x, int _y, int _stangle, int _endangle, int _radius){
  txArc((double)_x, (double)_y, (double)_x + 2 * _radius, (double)_y + 2 * _radius, (double)_stangle,
        (double)_endangle - _stangle);
}

void bar(int _left, int _top, int _right, int _bottom){
  txRectangle((double)_left, (double)_top, (double)_right, (double)_bottom);
}

void bar3d(int _left, int _top, int _right, int _bottom,
                int _depth, int _topflag){                          BGINOSUPPORT
}

void circle(int _x, int _y, int _radius){
  COLORREF currentColor = txGetFillColor();
  txSetFillColor(TX_TRANSPARENT);
  txCircle((double)_x, (double)_y, (double)_radius);
  txSetFillColor(currentColor);
}

void cleardevice(void){
  txClear();
}

void clearviewport(void){
  txClear();
}

void closegraph(void){
  txSetFillColor(TX_BLACK);
  txClear();
}


void  fillpoly(int _numpoints, const int *_polypoints){

  POINT *points = new POINT[_numpoints];

  for (int i = 0; i < _numpoints; i++){
    points[i].x = _polypoints[i * 2];
    points[i].y = _polypoints[i * 2 + 1];
  }

  txPolygon(points, _numpoints);

  delete[] points;
}

void drawpoly(int _numpoints, const int *_polypoints){
  COLORREF currentColor = txGetFillColor();
  txSetFillColor(TX_TRANSPARENT);
  fillpoly(_numpoints,_polypoints);
  txSetFillColor(currentColor);
}

void ellipse(int _x, int _y, int _stangle, int _endangle,
              int _xradius, int _yradius){
  COLORREF currentColor = txGetFillColor();
  txSetFillColor(TX_TRANSPARENT);
  txEllipse((double)_x, (double)_y, (double)_x + 2 * (double)_xradius,
            (double)_y + 2 * (double)_yradius);
  txSetFillColor(currentColor);
}

void  fillellipse( int _x, int _y, int _xradius, int _yradius ){
  txEllipse((double)_x, (double)_y, (double)_x + 2 * _xradius, (double)_y + 2 * _yradius);
}



void  floodfill(int _x, int _y, int _border){
  txFloodFill((double)_x, (double)_y, ColorBGI2TX(_border), FLOODFILLBORDER);
}

//void getarccoords(struct arccoordstype *_arccoords);


int getbkcolor(void){
  return ColorTX2BGI(txGetColor());
}

int getcolor(void){
 return ColorTX2BGI(txGetColor());
}

//struct palettetype *  getdefaultpalette( void );

//char* getdrivername(void){
//     return (char*)NULL;
//}



//void  getfillsettings(struct fillsettingstype *_fillinfo);

int getgraphmode(void){
  return 0;
}


void getimage(int _left, int _top, int _right, int _bottom,
                   void *_bitmap);

//void getlinesettings(struct linesettingstype *_lineinfo);


int getmaxcolor(void){
  return 16;
}

int getmaxmode(void){
  return 0;
}

int getmaxx(void){
  return txGetExtentX();
}


int getmaxy(void){
  return txGetExtentY();
}

char *getmodename( int _mode_number ){
  return NULL;
}

void getmoderange(int _graphdriver, int *_lomode,
                   int *_himode){
}

int getpalettesize( void ){
  return 16;
}
// void gettextsettings(struct textsettingstype *_texttypeinfo);

// void getviewsettings(struct viewporttype *_viewport);


int getx(void){
    return (int)txGetCurrentX();
}


int gety(void){
    return (int)txGetCurrentY();
}


void graphdefaults(void){
  txSetDefaults();
}

char* grapherrormsg(int _errorcode){
	return 0;
}


int    graphresult(void){
  return txOK();
}



void initgraph(int  *_graphdriver,
               int  *_graphmode,
               const char *_pathtodrive){
  txCreateWindow(0, 0, true);
  txTextCursor(false);
}

//int     installuserdriver( const char *_name,
//                int huge (*detect)(void) );

int installuserfont( const char *_name ){
	return 0;
}


void line(int _x1, int _y1, int _x2, int _y2){
  txLine((double)_x1, (double)_y1, (double)_x2, (double)_y2);
}


void linerel(int _dx, int _dy){
  txLineTo(txGetCurrentX() + _dx, txGetCurrentY() + _dx);
}


void lineto(int _x, int _y){
  txLineTo((double)_x, (double)_y);
}


void moverel(int _dx, int _dy){
  txMoveTo(txGetCurrentX() + _dx, txGetCurrentY() + _dx);
}


void moveto(int _x, int _y){
     txMoveTo(_x, _y);
}


void outtext(const char *_textstring){
  txTextOut(txGetCurrentX(), txGetCurrentY(), _textstring);
}


void outtextxy(int _x, int _y, const char *_textstring){
  txTextOut(_x, _y, _textstring);
}


void pieslice(int _x, int _y, int _stangle, int _endangle,
                   int _radius){
  txPie(_x, _y, _x + 2 * _radius, _y + 2 * _radius, _stangle, _endangle);
}

void putimage(int _left, int _top, const void *_bitmap, int _op);


void putpixel(int _x, int _y, int _color){
  txSetPixel(_x, _y, ColorBGI2TX(_color));
}


void rectangle(int _left, int _top, int _right, int _bottom){
  COLORREF currentColor = txGetFillColor();
  txSetFillColor(TX_TRANSPARENT);
  txRectangle((double)_left, (double)_top, (double)_right, (double)_bottom);
  txSetFillColor(currentColor);
}


void restorecrtmode(void){
  txSetFillColor(TX_BLACK);
  txClear();
  txSetDefaults();
}

void sector( int _X, int _Y, int _StAngle, int _EndAngle,
                  int _XRadius, int _YRadius ){                     BGINOSUPPORT
}



//void        setallpalette(const struct palettetype *_palette);

//void        setaspectratio( int _xasp, int _yasp );


void setbkcolor(int _color){
  txSetFillColor(ColorBGI2TX(_color));
}


void setcolor(int _color){
  txSetColor(ColorBGI2TX(_color), linethickness);
}

void  setfillpattern(const char *_upattern, int _color){            BGINOSUPPORT
}

void  setfillstyle(int _pattern, int _color){
  txSetFillColor(ColorBGI2TX(_color));
}

unsigned setgraphbufsize(unsigned _bufsize){                        BGINOSUPPORT
  return 0;
}
void setgraphmode(int _mode){
}

void setlinestyle(int _linestyle, unsigned _upattern,
                   int _thickness){
  txSetColor(txGetColor(), _thickness);
}

void setpalette(int _colornum, int _color){
}


void setrgbpalette(int _colornum,
                   int _red, int _green, int _blue){
}


void settextjustify(int _horiz, int _vert){

  switch (_horiz){
    case LEFT_TEXT :  _horiz = TA_LEFT;         break;
    case RIGHT_TEXT:  _horiz = TA_RIGHT;        break;
    case CENTER_TEXT: _horiz = TA_CENTER;       break;
  }

  switch (_vert){
    case TOP_TEXT :   _vert = TA_TOP;          break;
    case BOTTOM_TEXT: _vert = TA_BOTTOM;       break;
  }

  txSetTextAlign  (_horiz | _vert);
}

void settextstyle(int _font, int _direction, int _charsize){
  txSelectFont(BGIFontNames[_font], _charsize * 10, 10);
}
void setusercharsize(int _multx, int _divx,
                      int _multy, int _divy){
}

void setviewport(int _left, int _top, int _right, int _bottom,
                  int _clip){
  txSelectRegion((double)_left, (double)_top, (double)_right, (double)_bottom);
}

void setwritemode(int _mode){
  switch (_mode){
    case COPY_PUT:   _mode = R2_COPYPEN;       break;
    case XOR_PUT:    _mode = R2_XORPEN;        break;
  }
  txSetROP2(_mode);
}


int textheight(const char *_textstring){
   return txGetTextExtentY(_textstring);
}


int  textwidth(const char *_textstring){
   return txGetTextExtentX(_textstring);
}


//== Other functions ===========================================================

void delay(int msecs){
  txSleep(msecs);
}

//! \endcond Internal


//! \cond Namespaces

} //namespace TX_BGI
} //namespace anonymous


using namespace TX_BGI;
//! \endcond Namespaces

// Prior build 50 compatibility
#define txSetBkColor txSetFillColor
#define txBkColor    txFillColor
#define txGetBkColor txGetFillColor


//=============================================================================

#endif // _TX_GRAPHICS_H

//=============================================================================


///////////////////////////////////////////////////////////////////////////////
// ADDON
///////////////////////////////////////////////////////////////////////////////


#ifndef __TX_ADDON
#define __TX_ADDON


//! \cond Namespaces
namespace {
namespace TX_ADDON {
//! \endcond Namespaces

//-----------------------------------------------------------------------------
//! \ingroup ADDON
//! \brief   ��������� � ���� ����������� � ������� BMP.
//! \return  ����� ��������
//! \see     txCreateWindow(), txCreateCompatibleDC(), txLoadImage(), txDeleteDC(),  txBitBlt(), txAlphaBlend(), txTransparentBlt()
//! \remark  ������� ����������� �������� �. (FiveStars)

bool txeSaveImage(LPCSTR filename, //!< ��� ������������ �����
                  HDC fromDC,      //!< ����� � �������� ����������� �����������
                  int x,           //!< �-���������� ������ �������� ���� ������������ ��������� ������
                  int y,           //!< y-���������� ������ �������� ���� ������������ ��������� ������
                  int sizeX,       //!< ������ ������������ ���������
                  int sizeY        //!< ������ ������������ ���������
                  );

//------------------------------------------------------------------------------

//! \cond Internal
bool txeSaveImage(LPCSTR filename, HDC fromDC, int x, int y, int sizeX, int sizeY)
{
  assert (txOK());

        HBITMAP HBM;
        BITMAP BM;
        BITMAPFILEHEADER BFH;
        BITMAPINFO BI = {0};
        LPBITMAPINFO BIH;
        DWORD dwTemp;
        DWORD ColorSize,DataSize;
        WORD BitCount;
        HANDLE FP;
        HDC DC;
        char * Buf;
        char s[10];

        DC = txCreateCompatibleDC(sizeX, sizeY);
        txBitBlt(DC, 0, 0, sizeX, sizeY, fromDC, x, y);

        HBM = (HBITMAP) Win32::GetCurrentObject(DC, OBJ_BITMAP);
        Win32::GetObject(HBM, sizeof(BITMAP), (LPSTR) &BM);

        BitCount = (WORD) BM.bmPlanes * BM.bmBitsPixel;

        switch(BitCount)
        {
            case 1:
            case 4:
            case 8:
            case 32:
               ColorSize = sizeof(RGBQUAD) * (1 << BitCount);
               break;
            case 24:
               ColorSize = 0;
                break;
        }

        DWORD t = BM.bmWidth * BitCount;
        DataSize = (t % 32 + t) / 8 * BM.bmHeight;

        BIH = &BI;
        BIH -> bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
        BIH -> bmiHeader.biWidth         = BM.bmWidth;
        BIH -> bmiHeader.biHeight        = BM.bmHeight;
        BIH -> bmiHeader.biPlanes        = 1;
        BIH -> bmiHeader.biBitCount      = BitCount;
        BIH -> bmiHeader.biCompression   = 0;
        BIH -> bmiHeader.biSizeImage     = DataSize;
        BIH -> bmiHeader.biXPelsPerMeter = 0;
        BIH -> bmiHeader.biYPelsPerMeter = 0;
        if (BitCount < 24)
        {
           BIH -> bmiHeader.biClrUsed       = (1 << BitCount);
        }
        BIH -> bmiHeader.biClrImportant  = 0;

        BFH.bfType                     = 0x4d42;
        BFH.bfOffBits                  = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ BIH->bmiHeader.biClrUsed * sizeof(RGBQUAD);
        BFH.bfReserved1                = 'V';
        BFH.bfReserved2                = 'V';
        BFH.bfSize                     = BFH.bfOffBits + DataSize;
        Buf = new char[DataSize];

        Win32::GetDIBits(DC, HBM, 0, (WORD) BM.bmHeight, Buf, BIH, DIB_RGB_COLORS);
        FILE * F = fopen(filename, "wb");

        fwrite(&BFH, sizeof(BFH),  1, F);
        fwrite(BIH,  sizeof(*BIH), 1, F);
        fwrite(Buf,  DataSize,     1, F);

        fclose(F);

        delete[] BIH;
        delete[] Buf;

        return true;
}

//! \endcond Internal

//! \cond Namespaces

} //namespace TX_ADDON
} //namespace anonymous

using namespace TX_ADDON;

//! \endcond Namespaces




#endif // __TX_ADDON


//=============================================================================
// EOF
//=============================================================================
