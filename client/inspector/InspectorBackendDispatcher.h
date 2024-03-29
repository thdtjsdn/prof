// File is generated by Source/WebCore/inspector/CodeGeneratorInspector.py

// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef InspectorBackendDispatcher_h
#define InspectorBackendDispatcher_h

#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class InspectorAgent;
class InspectorObject;
class InspectorArray;
class InspectorFrontendChannel;

class InspectorApplicationCacheAgent;
class InspectorCSSAgent;
class InspectorConsoleAgent;
class InspectorDOMAgent;
#if ENABLE(JAVASCRIPT_DEBUGGER)

class InspectorDOMDebuggerAgent;
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

class InspectorDOMStorageAgent;
#if ENABLE(SQL_DATABASE)

class InspectorDatabaseAgent;
#endif // ENABLE(SQL_DATABASE)

#if ENABLE(JAVASCRIPT_DEBUGGER)

class InspectorDebuggerAgent;
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(FILE_SYSTEM)

class InspectorFileSystemAgent;
#endif // ENABLE(FILE_SYSTEM)

class InspectorAgent;
class InspectorMemoryAgent;
class InspectorResourceAgent;
class InspectorPageAgent;
#if ENABLE(JAVASCRIPT_DEBUGGER)

class InspectorProfilerAgent;
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

class InspectorRuntimeAgent;
class InspectorTimelineAgent;
#if ENABLE(WORKERS)

class InspectorWorkerAgent;
#endif // ENABLE(WORKERS)


typedef String ErrorString;

class InspectorBackendDispatcher: public RefCounted<InspectorBackendDispatcher> {
public:
    InspectorBackendDispatcher(InspectorFrontendChannel* inspectorFrontendChannel)
        : m_inspectorFrontendChannel(inspectorFrontendChannel)
        , m_applicationCacheAgent(0)
        , m_cssAgent(0)
        , m_consoleAgent(0)
        , m_domAgent(0)
#if ENABLE(JAVASCRIPT_DEBUGGER)

        , m_domDebuggerAgent(0)
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

        , m_domStorageAgent(0)
#if ENABLE(SQL_DATABASE)

        , m_databaseAgent(0)
#endif // ENABLE(SQL_DATABASE)

#if ENABLE(JAVASCRIPT_DEBUGGER)

        , m_debuggerAgent(0)
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(FILE_SYSTEM)

        , m_fileSystemAgent(0)
#endif // ENABLE(FILE_SYSTEM)

        , m_inspectorAgent(0)
        , m_memoryAgent(0)
        , m_networkAgent(0)
        , m_pageAgent(0)
#if ENABLE(JAVASCRIPT_DEBUGGER)

        , m_profilerAgent(0)
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

        , m_runtimeAgent(0)
        , m_timelineAgent(0)
#if ENABLE(WORKERS)

        , m_workerAgent(0)
#endif // ENABLE(WORKERS)

    { }

    void registerAgent(InspectorApplicationCacheAgent* applicationCacheAgent) { ASSERT(!m_applicationCacheAgent); m_applicationCacheAgent = applicationCacheAgent; }
    void registerAgent(InspectorCSSAgent* cssAgent) { ASSERT(!m_cssAgent); m_cssAgent = cssAgent; }
    void registerAgent(InspectorConsoleAgent* consoleAgent) { ASSERT(!m_consoleAgent); m_consoleAgent = consoleAgent; }
    void registerAgent(InspectorDOMAgent* domAgent) { ASSERT(!m_domAgent); m_domAgent = domAgent; }
#if ENABLE(JAVASCRIPT_DEBUGGER)

    void registerAgent(InspectorDOMDebuggerAgent* domDebuggerAgent) { ASSERT(!m_domDebuggerAgent); m_domDebuggerAgent = domDebuggerAgent; }
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

    void registerAgent(InspectorDOMStorageAgent* domStorageAgent) { ASSERT(!m_domStorageAgent); m_domStorageAgent = domStorageAgent; }
#if ENABLE(SQL_DATABASE)

    void registerAgent(InspectorDatabaseAgent* databaseAgent) { ASSERT(!m_databaseAgent); m_databaseAgent = databaseAgent; }
#endif // ENABLE(SQL_DATABASE)

#if ENABLE(JAVASCRIPT_DEBUGGER)

    void registerAgent(InspectorDebuggerAgent* debuggerAgent) { ASSERT(!m_debuggerAgent); m_debuggerAgent = debuggerAgent; }
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(FILE_SYSTEM)

    void registerAgent(InspectorFileSystemAgent* fileSystemAgent) { ASSERT(!m_fileSystemAgent); m_fileSystemAgent = fileSystemAgent; }
#endif // ENABLE(FILE_SYSTEM)

    void registerAgent(InspectorAgent* inspectorAgent) { ASSERT(!m_inspectorAgent); m_inspectorAgent = inspectorAgent; }
    void registerAgent(InspectorMemoryAgent* memoryAgent) { ASSERT(!m_memoryAgent); m_memoryAgent = memoryAgent; }
    void registerAgent(InspectorResourceAgent* networkAgent) { ASSERT(!m_networkAgent); m_networkAgent = networkAgent; }
    void registerAgent(InspectorPageAgent* pageAgent) { ASSERT(!m_pageAgent); m_pageAgent = pageAgent; }
#if ENABLE(JAVASCRIPT_DEBUGGER)

    void registerAgent(InspectorProfilerAgent* profilerAgent) { ASSERT(!m_profilerAgent); m_profilerAgent = profilerAgent; }
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

    void registerAgent(InspectorRuntimeAgent* runtimeAgent) { ASSERT(!m_runtimeAgent); m_runtimeAgent = runtimeAgent; }
    void registerAgent(InspectorTimelineAgent* timelineAgent) { ASSERT(!m_timelineAgent); m_timelineAgent = timelineAgent; }
#if ENABLE(WORKERS)

    void registerAgent(InspectorWorkerAgent* workerAgent) { ASSERT(!m_workerAgent); m_workerAgent = workerAgent; }
#endif // ENABLE(WORKERS)


    void clearFrontend() { m_inspectorFrontendChannel = 0; }

    enum CommonErrorCode {
        ParseError = 0,
        InvalidRequest,
        MethodNotFound,
        InvalidParams,
        InternalError,
        ServerError,
        LastEntry,
    };

    void reportProtocolError(const long* const callId, CommonErrorCode, const String& errorMessage) const;
    void reportProtocolError(const long* const callId, CommonErrorCode, const String& errorMessage, PassRefPtr<InspectorArray> data) const;
    void dispatch(const String& message);
    static bool getCommandName(const String& message, String* result);

    enum MethodNames {
        kInspector_enableCmd,
        kInspector_disableCmd,
        kMemory_getDOMNodeCountCmd,
        kPage_enableCmd,
        kPage_disableCmd,
        kPage_addScriptToEvaluateOnLoadCmd,
        kPage_removeScriptToEvaluateOnLoadCmd,
        kPage_reloadCmd,
        kPage_openCmd,
        kPage_getCookiesCmd,
        kPage_deleteCookieCmd,
        kPage_getResourceTreeCmd,
        kPage_getResourceContentCmd,
        kPage_searchInResourceCmd,
        kPage_searchInResourcesCmd,
        kRuntime_evaluateCmd,
        kRuntime_callFunctionOnCmd,
        kRuntime_getPropertiesCmd,
        kRuntime_releaseObjectCmd,
        kRuntime_releaseObjectGroupCmd,
        kRuntime_runCmd,
        kConsole_enableCmd,
        kConsole_disableCmd,
        kConsole_clearMessagesCmd,
        kConsole_setMonitoringXHREnabledCmd,
        kConsole_addInspectedNodeCmd,
        kNetwork_enableCmd,
        kNetwork_disableCmd,
        kNetwork_setUserAgentOverrideCmd,
        kNetwork_setExtraHTTPHeadersCmd,
        kNetwork_getResponseBodyCmd,
        kNetwork_canClearBrowserCacheCmd,
        kNetwork_clearBrowserCacheCmd,
        kNetwork_canClearBrowserCookiesCmd,
        kNetwork_clearBrowserCookiesCmd,
        kNetwork_setCacheDisabledCmd,
#if ENABLE(SQL_DATABASE)

        kDatabase_enableCmd,
        kDatabase_disableCmd,
        kDatabase_getDatabaseTableNamesCmd,
        kDatabase_executeSQLCmd,
#endif // ENABLE(SQL_DATABASE)

        kDOMStorage_enableCmd,
        kDOMStorage_disableCmd,
        kDOMStorage_getDOMStorageEntriesCmd,
        kDOMStorage_setDOMStorageItemCmd,
        kDOMStorage_removeDOMStorageItemCmd,
        kApplicationCache_getFramesWithManifestsCmd,
        kApplicationCache_enableCmd,
        kApplicationCache_getManifestForFrameCmd,
        kApplicationCache_getApplicationCacheForFrameCmd,
#if ENABLE(FILE_SYSTEM)

        kFileSystem_enableCmd,
        kFileSystem_disableCmd,
#endif // ENABLE(FILE_SYSTEM)

        kDOM_getDocumentCmd,
        kDOM_requestChildNodesCmd,
        kDOM_querySelectorCmd,
        kDOM_querySelectorAllCmd,
        kDOM_setNodeNameCmd,
        kDOM_setNodeValueCmd,
        kDOM_removeNodeCmd,
        kDOM_setAttributeValueCmd,
        kDOM_setAttributesAsTextCmd,
        kDOM_removeAttributeCmd,
        kDOM_getEventListenersForNodeCmd,
        kDOM_copyNodeCmd,
        kDOM_getOuterHTMLCmd,
        kDOM_setOuterHTMLCmd,
        kDOM_performSearchCmd,
        kDOM_getSearchResultsCmd,
        kDOM_discardSearchResultsCmd,
        kDOM_requestNodeCmd,
        kDOM_setInspectModeEnabledCmd,
        kDOM_highlightRectCmd,
        kDOM_highlightNodeCmd,
        kDOM_hideHighlightCmd,
        kDOM_highlightFrameCmd,
        kDOM_pushNodeByPathToFrontendCmd,
        kDOM_resolveNodeCmd,
        kDOM_getAttributesCmd,
        kDOM_moveToCmd,
        kCSS_enableCmd,
        kCSS_disableCmd,
        kCSS_getMatchedStylesForNodeCmd,
        kCSS_getInlineStylesForNodeCmd,
        kCSS_getComputedStyleForNodeCmd,
        kCSS_getAllStyleSheetsCmd,
        kCSS_getStyleSheetCmd,
        kCSS_getStyleSheetTextCmd,
        kCSS_setStyleSheetTextCmd,
        kCSS_setPropertyTextCmd,
        kCSS_togglePropertyCmd,
        kCSS_setRuleSelectorCmd,
        kCSS_addRuleCmd,
        kCSS_getSupportedCSSPropertiesCmd,
        kCSS_startSelectorProfilerCmd,
        kCSS_stopSelectorProfilerCmd,
        kTimeline_startCmd,
        kTimeline_stopCmd,
#if ENABLE(JAVASCRIPT_DEBUGGER)

        kDebugger_causesRecompilationCmd,
        kDebugger_supportsNativeBreakpointsCmd,
        kDebugger_enableCmd,
        kDebugger_disableCmd,
        kDebugger_setBreakpointsActiveCmd,
        kDebugger_setBreakpointByUrlCmd,
        kDebugger_setBreakpointCmd,
        kDebugger_removeBreakpointCmd,
        kDebugger_continueToLocationCmd,
        kDebugger_stepOverCmd,
        kDebugger_stepIntoCmd,
        kDebugger_stepOutCmd,
        kDebugger_pauseCmd,
        kDebugger_resumeCmd,
        kDebugger_searchInContentCmd,
        kDebugger_canSetScriptSourceCmd,
        kDebugger_setScriptSourceCmd,
        kDebugger_getScriptSourceCmd,
        kDebugger_getFunctionLocationCmd,
        kDebugger_setPauseOnExceptionsCmd,
        kDebugger_evaluateOnCallFrameCmd,
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(JAVASCRIPT_DEBUGGER)

        kDOMDebugger_setDOMBreakpointCmd,
        kDOMDebugger_removeDOMBreakpointCmd,
        kDOMDebugger_setEventListenerBreakpointCmd,
        kDOMDebugger_removeEventListenerBreakpointCmd,
        kDOMDebugger_setXHRBreakpointCmd,
        kDOMDebugger_removeXHRBreakpointCmd,
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(JAVASCRIPT_DEBUGGER)

        kProfiler_causesRecompilationCmd,
        kProfiler_isSamplingCmd,
        kProfiler_hasHeapProfilerCmd,
        kProfiler_enableCmd,
        kProfiler_disableCmd,
        kProfiler_startCmd,
        kProfiler_stopCmd,
        kProfiler_getProfileHeadersCmd,
        kProfiler_getProfileCmd,
        kProfiler_removeProfileCmd,
        kProfiler_clearProfilesCmd,
        kProfiler_takeHeapSnapshotCmd,
        kProfiler_collectGarbageCmd,
        kProfiler_getObjectByHeapObjectIdCmd,
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(WORKERS)

        kWorker_setWorkerInspectionEnabledCmd,
        kWorker_sendMessageToWorkerCmd,
        kWorker_connectToWorkerCmd,
        kWorker_disconnectFromWorkerCmd,
        kWorker_setAutoconnectToWorkersCmd,
#endif // ENABLE(WORKERS)

};

    static const char* commandNames[];

private:
    static int getInt(InspectorObject* object, const String& name, bool* valueFound, InspectorArray* protocolErrors);
    static String getString(InspectorObject* object, const String& name, bool* valueFound, InspectorArray* protocolErrors);
    static bool getBoolean(InspectorObject* object, const String& name, bool* valueFound, InspectorArray* protocolErrors);
    static PassRefPtr<InspectorObject> getObject(InspectorObject* object, const String& name, bool* valueFound, InspectorArray* protocolErrors);
    static PassRefPtr<InspectorArray> getArray(InspectorObject* object, const String& name, bool* valueFound, InspectorArray* protocolErrors);
    void sendResponse(long callId, PassRefPtr<InspectorObject> result, const String& errorMessage, PassRefPtr<InspectorArray> protocolErrors, ErrorString invocationError);

    void Inspector_enable(long callId, InspectorObject* requestMessageObject);
    void Inspector_disable(long callId, InspectorObject* requestMessageObject);
    void Memory_getDOMNodeCount(long callId, InspectorObject* requestMessageObject);
    void Page_enable(long callId, InspectorObject* requestMessageObject);
    void Page_disable(long callId, InspectorObject* requestMessageObject);
    void Page_addScriptToEvaluateOnLoad(long callId, InspectorObject* requestMessageObject);
    void Page_removeScriptToEvaluateOnLoad(long callId, InspectorObject* requestMessageObject);
    void Page_reload(long callId, InspectorObject* requestMessageObject);
    void Page_open(long callId, InspectorObject* requestMessageObject);
    void Page_getCookies(long callId, InspectorObject* requestMessageObject);
    void Page_deleteCookie(long callId, InspectorObject* requestMessageObject);
    void Page_getResourceTree(long callId, InspectorObject* requestMessageObject);
    void Page_getResourceContent(long callId, InspectorObject* requestMessageObject);
    void Page_searchInResource(long callId, InspectorObject* requestMessageObject);
    void Page_searchInResources(long callId, InspectorObject* requestMessageObject);
    void Runtime_evaluate(long callId, InspectorObject* requestMessageObject);
    void Runtime_callFunctionOn(long callId, InspectorObject* requestMessageObject);
    void Runtime_getProperties(long callId, InspectorObject* requestMessageObject);
    void Runtime_releaseObject(long callId, InspectorObject* requestMessageObject);
    void Runtime_releaseObjectGroup(long callId, InspectorObject* requestMessageObject);
    void Runtime_run(long callId, InspectorObject* requestMessageObject);
    void Console_enable(long callId, InspectorObject* requestMessageObject);
    void Console_disable(long callId, InspectorObject* requestMessageObject);
    void Console_clearMessages(long callId, InspectorObject* requestMessageObject);
    void Console_setMonitoringXHREnabled(long callId, InspectorObject* requestMessageObject);
    void Console_addInspectedNode(long callId, InspectorObject* requestMessageObject);
    void Network_enable(long callId, InspectorObject* requestMessageObject);
    void Network_disable(long callId, InspectorObject* requestMessageObject);
    void Network_setUserAgentOverride(long callId, InspectorObject* requestMessageObject);
    void Network_setExtraHTTPHeaders(long callId, InspectorObject* requestMessageObject);
    void Network_getResponseBody(long callId, InspectorObject* requestMessageObject);
    void Network_canClearBrowserCache(long callId, InspectorObject* requestMessageObject);
    void Network_clearBrowserCache(long callId, InspectorObject* requestMessageObject);
    void Network_canClearBrowserCookies(long callId, InspectorObject* requestMessageObject);
    void Network_clearBrowserCookies(long callId, InspectorObject* requestMessageObject);
    void Network_setCacheDisabled(long callId, InspectorObject* requestMessageObject);
#if ENABLE(SQL_DATABASE)

    void Database_enable(long callId, InspectorObject* requestMessageObject);
    void Database_disable(long callId, InspectorObject* requestMessageObject);
    void Database_getDatabaseTableNames(long callId, InspectorObject* requestMessageObject);
    void Database_executeSQL(long callId, InspectorObject* requestMessageObject);
#endif // ENABLE(SQL_DATABASE)

    void DOMStorage_enable(long callId, InspectorObject* requestMessageObject);
    void DOMStorage_disable(long callId, InspectorObject* requestMessageObject);
    void DOMStorage_getDOMStorageEntries(long callId, InspectorObject* requestMessageObject);
    void DOMStorage_setDOMStorageItem(long callId, InspectorObject* requestMessageObject);
    void DOMStorage_removeDOMStorageItem(long callId, InspectorObject* requestMessageObject);
    void ApplicationCache_getFramesWithManifests(long callId, InspectorObject* requestMessageObject);
    void ApplicationCache_enable(long callId, InspectorObject* requestMessageObject);
    void ApplicationCache_getManifestForFrame(long callId, InspectorObject* requestMessageObject);
    void ApplicationCache_getApplicationCacheForFrame(long callId, InspectorObject* requestMessageObject);
#if ENABLE(FILE_SYSTEM)

    void FileSystem_enable(long callId, InspectorObject* requestMessageObject);
    void FileSystem_disable(long callId, InspectorObject* requestMessageObject);
#endif // ENABLE(FILE_SYSTEM)

    void DOM_getDocument(long callId, InspectorObject* requestMessageObject);
    void DOM_requestChildNodes(long callId, InspectorObject* requestMessageObject);
    void DOM_querySelector(long callId, InspectorObject* requestMessageObject);
    void DOM_querySelectorAll(long callId, InspectorObject* requestMessageObject);
    void DOM_setNodeName(long callId, InspectorObject* requestMessageObject);
    void DOM_setNodeValue(long callId, InspectorObject* requestMessageObject);
    void DOM_removeNode(long callId, InspectorObject* requestMessageObject);
    void DOM_setAttributeValue(long callId, InspectorObject* requestMessageObject);
    void DOM_setAttributesAsText(long callId, InspectorObject* requestMessageObject);
    void DOM_removeAttribute(long callId, InspectorObject* requestMessageObject);
    void DOM_getEventListenersForNode(long callId, InspectorObject* requestMessageObject);
    void DOM_copyNode(long callId, InspectorObject* requestMessageObject);
    void DOM_getOuterHTML(long callId, InspectorObject* requestMessageObject);
    void DOM_setOuterHTML(long callId, InspectorObject* requestMessageObject);
    void DOM_performSearch(long callId, InspectorObject* requestMessageObject);
    void DOM_getSearchResults(long callId, InspectorObject* requestMessageObject);
    void DOM_discardSearchResults(long callId, InspectorObject* requestMessageObject);
    void DOM_requestNode(long callId, InspectorObject* requestMessageObject);
    void DOM_setInspectModeEnabled(long callId, InspectorObject* requestMessageObject);
    void DOM_highlightRect(long callId, InspectorObject* requestMessageObject);
    void DOM_highlightNode(long callId, InspectorObject* requestMessageObject);
    void DOM_hideHighlight(long callId, InspectorObject* requestMessageObject);
    void DOM_highlightFrame(long callId, InspectorObject* requestMessageObject);
    void DOM_pushNodeByPathToFrontend(long callId, InspectorObject* requestMessageObject);
    void DOM_resolveNode(long callId, InspectorObject* requestMessageObject);
    void DOM_getAttributes(long callId, InspectorObject* requestMessageObject);
    void DOM_moveTo(long callId, InspectorObject* requestMessageObject);
    void CSS_enable(long callId, InspectorObject* requestMessageObject);
    void CSS_disable(long callId, InspectorObject* requestMessageObject);
    void CSS_getMatchedStylesForNode(long callId, InspectorObject* requestMessageObject);
    void CSS_getInlineStylesForNode(long callId, InspectorObject* requestMessageObject);
    void CSS_getComputedStyleForNode(long callId, InspectorObject* requestMessageObject);
    void CSS_getAllStyleSheets(long callId, InspectorObject* requestMessageObject);
    void CSS_getStyleSheet(long callId, InspectorObject* requestMessageObject);
    void CSS_getStyleSheetText(long callId, InspectorObject* requestMessageObject);
    void CSS_setStyleSheetText(long callId, InspectorObject* requestMessageObject);
    void CSS_setPropertyText(long callId, InspectorObject* requestMessageObject);
    void CSS_toggleProperty(long callId, InspectorObject* requestMessageObject);
    void CSS_setRuleSelector(long callId, InspectorObject* requestMessageObject);
    void CSS_addRule(long callId, InspectorObject* requestMessageObject);
    void CSS_getSupportedCSSProperties(long callId, InspectorObject* requestMessageObject);
    void CSS_startSelectorProfiler(long callId, InspectorObject* requestMessageObject);
    void CSS_stopSelectorProfiler(long callId, InspectorObject* requestMessageObject);
    void Timeline_start(long callId, InspectorObject* requestMessageObject);
    void Timeline_stop(long callId, InspectorObject* requestMessageObject);
#if ENABLE(JAVASCRIPT_DEBUGGER)

    void Debugger_causesRecompilation(long callId, InspectorObject* requestMessageObject);
    void Debugger_supportsNativeBreakpoints(long callId, InspectorObject* requestMessageObject);
    void Debugger_enable(long callId, InspectorObject* requestMessageObject);
    void Debugger_disable(long callId, InspectorObject* requestMessageObject);
    void Debugger_setBreakpointsActive(long callId, InspectorObject* requestMessageObject);
    void Debugger_setBreakpointByUrl(long callId, InspectorObject* requestMessageObject);
    void Debugger_setBreakpoint(long callId, InspectorObject* requestMessageObject);
    void Debugger_removeBreakpoint(long callId, InspectorObject* requestMessageObject);
    void Debugger_continueToLocation(long callId, InspectorObject* requestMessageObject);
    void Debugger_stepOver(long callId, InspectorObject* requestMessageObject);
    void Debugger_stepInto(long callId, InspectorObject* requestMessageObject);
    void Debugger_stepOut(long callId, InspectorObject* requestMessageObject);
    void Debugger_pause(long callId, InspectorObject* requestMessageObject);
    void Debugger_resume(long callId, InspectorObject* requestMessageObject);
    void Debugger_searchInContent(long callId, InspectorObject* requestMessageObject);
    void Debugger_canSetScriptSource(long callId, InspectorObject* requestMessageObject);
    void Debugger_setScriptSource(long callId, InspectorObject* requestMessageObject);
    void Debugger_getScriptSource(long callId, InspectorObject* requestMessageObject);
    void Debugger_getFunctionLocation(long callId, InspectorObject* requestMessageObject);
    void Debugger_setPauseOnExceptions(long callId, InspectorObject* requestMessageObject);
    void Debugger_evaluateOnCallFrame(long callId, InspectorObject* requestMessageObject);
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(JAVASCRIPT_DEBUGGER)

    void DOMDebugger_setDOMBreakpoint(long callId, InspectorObject* requestMessageObject);
    void DOMDebugger_removeDOMBreakpoint(long callId, InspectorObject* requestMessageObject);
    void DOMDebugger_setEventListenerBreakpoint(long callId, InspectorObject* requestMessageObject);
    void DOMDebugger_removeEventListenerBreakpoint(long callId, InspectorObject* requestMessageObject);
    void DOMDebugger_setXHRBreakpoint(long callId, InspectorObject* requestMessageObject);
    void DOMDebugger_removeXHRBreakpoint(long callId, InspectorObject* requestMessageObject);
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(JAVASCRIPT_DEBUGGER)

    void Profiler_causesRecompilation(long callId, InspectorObject* requestMessageObject);
    void Profiler_isSampling(long callId, InspectorObject* requestMessageObject);
    void Profiler_hasHeapProfiler(long callId, InspectorObject* requestMessageObject);
    void Profiler_enable(long callId, InspectorObject* requestMessageObject);
    void Profiler_disable(long callId, InspectorObject* requestMessageObject);
    void Profiler_start(long callId, InspectorObject* requestMessageObject);
    void Profiler_stop(long callId, InspectorObject* requestMessageObject);
    void Profiler_getProfileHeaders(long callId, InspectorObject* requestMessageObject);
    void Profiler_getProfile(long callId, InspectorObject* requestMessageObject);
    void Profiler_removeProfile(long callId, InspectorObject* requestMessageObject);
    void Profiler_clearProfiles(long callId, InspectorObject* requestMessageObject);
    void Profiler_takeHeapSnapshot(long callId, InspectorObject* requestMessageObject);
    void Profiler_collectGarbage(long callId, InspectorObject* requestMessageObject);
    void Profiler_getObjectByHeapObjectId(long callId, InspectorObject* requestMessageObject);
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(WORKERS)

    void Worker_setWorkerInspectionEnabled(long callId, InspectorObject* requestMessageObject);
    void Worker_sendMessageToWorker(long callId, InspectorObject* requestMessageObject);
    void Worker_connectToWorker(long callId, InspectorObject* requestMessageObject);
    void Worker_disconnectFromWorker(long callId, InspectorObject* requestMessageObject);
    void Worker_setAutoconnectToWorkers(long callId, InspectorObject* requestMessageObject);
#endif // ENABLE(WORKERS)


    InspectorFrontendChannel* m_inspectorFrontendChannel;
    InspectorApplicationCacheAgent* m_applicationCacheAgent;
    InspectorCSSAgent* m_cssAgent;
    InspectorConsoleAgent* m_consoleAgent;
    InspectorDOMAgent* m_domAgent;
#if ENABLE(JAVASCRIPT_DEBUGGER)

    InspectorDOMDebuggerAgent* m_domDebuggerAgent;
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

    InspectorDOMStorageAgent* m_domStorageAgent;
#if ENABLE(SQL_DATABASE)

    InspectorDatabaseAgent* m_databaseAgent;
#endif // ENABLE(SQL_DATABASE)

#if ENABLE(JAVASCRIPT_DEBUGGER)

    InspectorDebuggerAgent* m_debuggerAgent;
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

#if ENABLE(FILE_SYSTEM)

    InspectorFileSystemAgent* m_fileSystemAgent;
#endif // ENABLE(FILE_SYSTEM)

    InspectorAgent* m_inspectorAgent;
    InspectorMemoryAgent* m_memoryAgent;
    InspectorResourceAgent* m_networkAgent;
    InspectorPageAgent* m_pageAgent;
#if ENABLE(JAVASCRIPT_DEBUGGER)

    InspectorProfilerAgent* m_profilerAgent;
#endif // ENABLE(JAVASCRIPT_DEBUGGER)

    InspectorRuntimeAgent* m_runtimeAgent;
    InspectorTimelineAgent* m_timelineAgent;
#if ENABLE(WORKERS)

    InspectorWorkerAgent* m_workerAgent;
#endif // ENABLE(WORKERS)

};

} // namespace WebCore
#endif // !defined(InspectorBackendDispatcher_h)


