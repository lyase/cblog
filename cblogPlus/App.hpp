/*
 * =====================================================================================
 *
 *       Filename:  App.hpp
 *
 *    Description:  Main witty App
 *
 *        Version:  1.0
 *        Created:  18/07/11 21:18:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <vector>
#include <string>
#include <Wt/WApplication>
#include <Wt/Dbo/backend/Postgres>
#include "base/SessionHandle.hpp"
#include "base/MemorySessionStore.hpp"
#include "model/User.hpp"
#include "base/BaseApp.hpp"
#include "urls.hpp"
#include "IUsers.hpp"
#include "IURLs.hpp"
#include "INavigation.hpp"

namespace Wt {
    class WEvent;
}

using std::vector;
using std::string;
using Wt::WApplication;
using Wt::WEnvironment;
using Wt::Signal;
using Wt::WEvent;
namespace dbo = Wt::Dbo;

namespace wittyPlus {

class MainWindow;
class URL2Action;
class ExtensionManager;

const string appCookieName = "witty-plus-app-cookie";

typedef base::BaseApp<model::User> BaseApp;

class App : public BaseApp, public IUsers, public INavigation, public IURLs {
public:
    typedef Signal<> URLChangedSignal;
    typedef Signal<WString> MessageSignal;
    typedef vector<string> UrlHistory;
    typedef vector<string>::const_iterator HistoryIndex;
protected:
    URL2Action* _url2ActionMapper; /// Handles turning urls into actions
    dbo::backend::Postgres postgres;
    UrlHistory urlHistory;
    // Signals
    UserChangedSignal* _userChanged;
    MessageSignal* _statusTextChanged;
    // Windows
    MainWindow* _mainWindow;
    // Methods
    void adminUsers();
    void notify(const WEvent& event);
    void rememberHistory(const string& url) {
        if ((urlHistory.size() >= 1) and (urlHistory.back() == url)) {
            // They probably hit 'back' in the browser.
            // Don't record the url in this case, it's already at the top of the history
            // and we always want the current url in there
            return;
        } else {
            urlHistory.push_back(url);
        }
    }
public:
    App(const WEnvironment& environment);
    MessageSignal* statusTextChanged() { return _statusTextChanged; } /// An event triggered when the status text (shown on the front page) changes
    /// Shows a status message for a period of time
    MainWindow* mainWindow() { return _mainWindow; }
    void setStatusText(const WString& newStatusText) { statusTextChanged()->emit(newStatusText); } // TODO: remove .. so IGUI can handle it

    // IUsers Implementation
    virtual bool tryLogin(const string& username, const string& password);
    virtual UserChangedSignal* userChanged(); /// An event triggered when a user logs in or logs out
    virtual Wt::Dbo::ptr<model::User> user(); /// Returns a dbo::ptr to the currently logged in user
    virtual void logout(); /// Logs out the current user
    virtual bool isLoggedIn(); /// Returns true if a user is currently logged in
    
    // INavigation Implementation
    virtual void go(const string& newUrl); /// Use to send the user somewhere inside the app
    /** Go back one in the history but only if it keeps you inside the app.
     * @param dontLogout don't go if 'back' would take us to /logout
     * @return true if we navigated
     **/
    virtual bool goBack(bool dontLogout=true);
    virtual void goBackOrHome(); /// Go Back, if we don't have history .. go home

    // IURLs implementation
    /** Returns an existing signal handler, or create's a new one on the fly and returns it,
      * with 'override' it'll replace an old one instead of returning it
      * @param url the user navigates to to fire the signal
      * @param override if true, deletes any old signal handlers we find
     **/
    virtual base::URLSignal& urlSignal(const string& url, bool override = false); /// Returns/creates the signal that will be called when a certain URL is navigated to

    /// Returns true if client is running on an iphone TODO: Add more possibilities here
    bool isIPhone() { return environment().userAgent().find("iPhone") != string::npos; }
};

WApplication *createApplication(const WEnvironment& env);

App* app();

} // namespace wittyPlus

#endif // APP_HPP
