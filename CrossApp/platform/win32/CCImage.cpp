
#define __CC_PLATFORM_IMAGE_CPP__
#include "platform/CCImageCommon_cpp.h"

NS_CC_BEGIN

/**
@brief    A memory DC which uses to draw text on bitmap.
*/
class BitmapDC
{
public:
    BitmapDC(HWND hWnd = NULL)
    : m_hDC(NULL)
    , m_hBmp(NULL)
    , m_hFont((HFONT)GetStockObject(DEFAULT_GUI_FONT))
    , m_hWnd(NULL)
    {
        m_hWnd = hWnd;
        HDC hdc = GetDC(hWnd);
        m_hDC   = CreateCompatibleDC(hdc);
        ReleaseDC(hWnd, hdc);
    }

    ~BitmapDC()
    {
        prepareBitmap(0, 0);
        if (m_hDC)
        {
            DeleteDC(m_hDC);
        }
        HFONT hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        if (hDefFont != m_hFont)
        {
            DeleteObject(m_hFont);
            m_hFont = hDefFont;
        }
		// release temp font resource	
		if (m_curFontPath.size() > 0)
		{
			wchar_t * pwszBuffer = utf8ToUtf16(m_curFontPath);
			if (pwszBuffer)
			{
				RemoveFontResourceW(pwszBuffer);
				SendMessage( m_hWnd, WM_FONTCHANGE, 0, 0);
				delete [] pwszBuffer;
				pwszBuffer = NULL;
			}
		}
    }

	wchar_t * utf8ToUtf16(std::string nString)
	{
		wchar_t * pwszBuffer = NULL;
		do 
		{
			if (nString.size() < 0)
			{
				break;
			}
			// utf-8 to utf-16
			int nLen = nString.size();
			int nBufLen  = nLen + 1;			
			pwszBuffer = new wchar_t[nBufLen];
			CC_BREAK_IF(! pwszBuffer);
			memset(pwszBuffer,0,nBufLen);
			nLen = MultiByteToWideChar(CP_UTF8, 0, nString.c_str(), nLen, pwszBuffer, nBufLen);		
			pwszBuffer[nLen] = '\0';
		} while (0);	
		return pwszBuffer;

	}

    bool setFont(const char * pFontName = NULL, int nSize = 0)
    {
        bool bRet = false;
        do 
        {
            std::string fontName = pFontName;
            std::string fontPath;
            HFONT       hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            LOGFONTA    tNewFont = {0};
            LOGFONTA    tOldFont = {0};
            GetObjectA(hDefFont, sizeof(tNewFont), &tNewFont);
            if (fontName.c_str())
            {    
                // create font from ttf file
                int nFindttf = fontName.find(".ttf");
                int nFindTTF = fontName.find(".TTF");
                if (nFindttf >= 0 || nFindTTF >= 0)
                {
                    fontPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fontName.c_str());
                    int nFindPos = fontName.rfind("/");
                    fontName = &fontName[nFindPos+1];
                    nFindPos = fontName.rfind(".");
                    fontName = fontName.substr(0,nFindPos);                
                }
                tNewFont.lfCharSet = DEFAULT_CHARSET;
#ifndef __MINGW32__
                strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, fontName.c_str());
#else
                strcpy(tNewFont.lfFaceName, fontName.c_str());
#endif
            }
            if (nSize)
            {
                tNewFont.lfHeight = -nSize;
            }
            GetObjectA(m_hFont,  sizeof(tOldFont), &tOldFont);

            if (tOldFont.lfHeight == tNewFont.lfHeight
                && 0 == strcmp(tOldFont.lfFaceName, tNewFont.lfFaceName))
            {
                // already has the font 
                bRet = true;
                break;
            }

            // delete old font
            if (m_hFont != hDefFont)
            {
                DeleteObject(m_hFont);
				// release old font register
				if (m_curFontPath.size() > 0)
				{
					wchar_t * pwszBuffer = utf8ToUtf16(m_curFontPath);
					if (pwszBuffer)
					{
						if(RemoveFontResourceW(pwszBuffer))
						{
							SendMessage( m_hWnd, WM_FONTCHANGE, 0, 0);
						}						
						delete [] pwszBuffer;
						pwszBuffer = NULL;
					}
				}
				if (fontPath.size() > 0)
					m_curFontPath = fontPath;
				else
					m_curFontPath.clear();
				// register temp font
				if (m_curFontPath.size() > 0)
				{
					wchar_t * pwszBuffer = utf8ToUtf16(m_curFontPath);
					if (pwszBuffer)
					{
						if(AddFontResourceW(pwszBuffer))
						{
							SendMessage( m_hWnd, WM_FONTCHANGE, 0, 0);
						}						
						delete [] pwszBuffer;
						pwszBuffer = NULL;
					}
				}
            }
            m_hFont = NULL;

            // disable Cleartype
            tNewFont.lfQuality = ANTIALIASED_QUALITY;

            // create new font
            m_hFont = CreateFontIndirectA(&tNewFont);
            if (! m_hFont)
            {
                // create failed, use default font
                m_hFont = hDefFont;
                break;
            }
            
            bRet = true;
        } while (0);
        return bRet;
    }

    SIZE sizeWithText(const wchar_t * pszText, int nLen, DWORD dwFmt, LONG nWidthLimit)
    {
        SIZE tRet = {0};
        do 
        {
            CC_BREAK_IF(! pszText || nLen <= 0);

            RECT rc = {0, 0, 0, 0};
            DWORD dwCalcFmt = DT_CALCRECT;

            if (nWidthLimit > 0)
            {
                rc.right = nWidthLimit;
                dwCalcFmt |= DT_WORDBREAK
                    | (dwFmt & DT_CENTER)
                    | (dwFmt & DT_RIGHT);
            }
            // use current font to measure text extent
            HGDIOBJ hOld = SelectObject(m_hDC, m_hFont);

            // measure text size
            DrawTextW(m_hDC, pszText, nLen, &rc, dwCalcFmt);
            SelectObject(m_hDC, hOld);

            tRet.cx = rc.right;
            tRet.cy = rc.bottom;
        } while (0);

        return tRet;
    }

    bool prepareBitmap(int nWidth, int nHeight)
    {
        // release bitmap
        if (m_hBmp)
        {
            DeleteObject(m_hBmp);
            m_hBmp = NULL;
        }
        if (nWidth > 0 && nHeight > 0)
        {
            m_hBmp = CreateBitmap(nWidth, nHeight, 1, 32, NULL);
            if (! m_hBmp)
            {
                return false;
            }
        }
        return true;
    }

    int drawText(const char * pszText, SIZE& tSize, CCImage::ETextAlign eAlign)
    {
        int nRet = 0;
        wchar_t * pwszBuffer = 0;
        do 
        {
            CC_BREAK_IF(! pszText);

            DWORD dwFmt = DT_WORDBREAK;
            DWORD dwHoriFlag = eAlign & 0x0f;
            DWORD dwVertFlag = (eAlign & 0xf0) >> 4;

            switch (dwHoriFlag)
            {
            case 1: // left
                dwFmt |= DT_LEFT;
                break;
            case 2: // right
                dwFmt |= DT_RIGHT;
                break;
            case 3: // center
                dwFmt |= DT_CENTER;
                break;
            }

            int nLen = strlen(pszText);
            // utf-8 to utf-16
            int nBufLen  = nLen + 1;
            pwszBuffer = new wchar_t[nBufLen];
            CC_BREAK_IF(! pwszBuffer);

            memset(pwszBuffer, 0, sizeof(wchar_t)*nBufLen);
            nLen = MultiByteToWideChar(CP_UTF8, 0, pszText, nLen, pwszBuffer, nBufLen);

            SIZE newSize = sizeWithText(pwszBuffer, nLen, dwFmt, tSize.cx);

            RECT rcText = {0};
            // if content width is 0, use text size as content size
            if (tSize.cx <= 0)
            {
                tSize = newSize;
                rcText.right  = newSize.cx;
                rcText.bottom = newSize.cy;
            }
            else
            {

                LONG offsetX = 0;
                LONG offsetY = 0;
                rcText.right = newSize.cx; // store the text width to rectangle

                // calculate text horizontal offset
                if (1 != dwHoriFlag          // and text isn't align to left
                    && newSize.cx < tSize.cx)   // and text's width less then content width,
                {                               // then need adjust offset of X.
                    offsetX = (2 == dwHoriFlag) ? tSize.cx - newSize.cx     // align to right
                        : (tSize.cx - newSize.cx) / 2;                      // align to center
                }

                // if content height is 0, use text height as content height
                // else if content height less than text height, use content height to draw text
                if (tSize.cy <= 0)
                {
                    tSize.cy = newSize.cy;
                    dwFmt   |= DT_NOCLIP;
                    rcText.bottom = newSize.cy; // store the text height to rectangle
                }
                else if (tSize.cy < newSize.cy)
                {
                    // content height larger than text height need, clip text to rect
                    rcText.bottom = tSize.cy;
                }
                else
                {
                    rcText.bottom = newSize.cy; // store the text height to rectangle

                    // content larger than text, need adjust vertical position
                    dwFmt |= DT_NOCLIP;

                    // calculate text vertical offset
                    offsetY = (2 == dwVertFlag) ? tSize.cy - newSize.cy     // align to bottom
                        : (3 == dwVertFlag) ? (tSize.cy - newSize.cy) / 2   // align to middle
                        : 0;                                                // align to top
                }

                if (offsetX || offsetY)
                {
                    OffsetRect(&rcText, offsetX, offsetY);
                }
            }

            CC_BREAK_IF(! prepareBitmap(tSize.cx, tSize.cy));

            // draw text
            HGDIOBJ hOldFont = SelectObject(m_hDC, m_hFont);
            HGDIOBJ hOldBmp  = SelectObject(m_hDC, m_hBmp);
            
            SetBkMode(m_hDC, TRANSPARENT);
            SetTextColor(m_hDC, RGB(255, 255, 255)); // white color

            // draw text
            nRet = DrawTextW(m_hDC, pwszBuffer, nLen, &rcText, dwFmt);
            //DrawTextA(m_hDC, pszText, nLen, &rcText, dwFmt);

            SelectObject(m_hDC, hOldBmp);
            SelectObject(m_hDC, hOldFont);
        } while (0);
        CC_SAFE_DELETE_ARRAY(pwszBuffer);
        return nRet;
    }

    CC_SYNTHESIZE_READONLY(HDC, m_hDC, DC);
    CC_SYNTHESIZE_READONLY(HBITMAP, m_hBmp, Bitmap);
private:
    friend class CCImage;
    HFONT   m_hFont;
    HWND    m_hWnd;
    std::string m_curFontPath;
};

static BitmapDC& sharedBitmapDC()
{
    static BitmapDC s_BmpDC;
    return s_BmpDC;
}

NS_CC_END
