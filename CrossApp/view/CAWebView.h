//
//  CAWebView.h
//  CrossApp
//
//  Created by Zhujian on 14-12-1.
//  Copyright (c) 2014 http://www.9miao.com All rights reserved.
//

#ifndef __CA_UI_WEBVIEW_H
#define __CA_UI_WEBVIEW_H

#include "platform/CCPlatformConfig.h"
#include "platform/CCFileUtils.h"
#include "CAView.h"
#include "CAImageView.h"


NS_CC_BEGIN

class CAWebView;
class CAWebViewImpl;

class CAWebViewDelegate
{
public:
	virtual ~CAWebViewDelegate(){};

	virtual bool onShouldStartLoading(CAWebView* pWebView, const std::string &url) { return true; }
	
	virtual void onDidFinishLoading(CAWebView* pWebView, const std::string &url) {}
	
	virtual void onDidFailLoading(CAWebView* pWebView, const std::string &url) {}
	
	virtual void onJSCallback(CAWebView* pWebView, const std::string &message) {}
};

class CC_DLL CAWebView : public CAView
{
public:
    
    CAWebView();
    
    virtual ~CAWebView();
    
    virtual bool init();
    
	static CAWebView *createWithFrame(const CCRect& rect);

	static CAWebView *createWithCenter(const CCRect& rect);

    /**
    * Set javascript interface scheme.
    * @see #onJsCallback
    */
    void setJavascriptInterfaceScheme(const std::string &scheme);

    /**
    * Sets the main page content and base URL.
    * @param string The content for the main page.
    * @param baseURL The base URL for the content.
    */
    void loadHTMLString(const std::string &string, const std::string &baseURL);

    /**
    * Loads the given URL.
    * @param url content URL
    */
    void loadURL(const std::string &url);

    /**
    * Loads the given fileName.
    * @param fileName content fileName
    */
    void loadFile(const std::string &fileName);

    /**
    * Stops the current load.
    */
    void stopLoading();

    /**
    * Reloads the current URL.
    */
    void reload();

    /**
    * Gets whether this WebView has a back history item.
    * @return web view has a back history item.
    */
    bool canGoBack();

    /**
    * Gets whether this WebView has a forward history item.
    * @return web view has a forward history item.
    */
    bool canGoForward();

    /**
    * Goes back in the history.
    */
    void goBack();

    /**
    * Goes forward in the history.
    */
    void goForward();

    /**
    * evaluates JavaScript in the context of the currently displayed page
    */
    void evaluateJS(const std::string &js);

    /**
    * Set WebView should support zooming. The default value is false.
    */
    void setScalesPageToFit(const bool scalesPageToFit);

	void hideNativeWebAndShowImage();

	void showNativeWeb();
    
	virtual void draw();

	virtual void setVisible(bool visible);
    
	CC_SYNTHESIZE(CAWebViewDelegate*, m_pWebViewDelegate, WebViewDelegate);

private:
    
    CAWebViewImpl *_impl;
    
	bool m_bHideNativeWeCmd;
    
    CAImageView* m_pImageView;
    
	friend class CAWebViewImpl;
    
};


NS_CC_END


#endif //__CA_UI_WEBVIEW_H
