//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992-1996.
//
//  File:       OLE2.h
//  Contents:   Main OLE2 header; Defines Linking and Emmebbeding interfaces, and API's.
//              Also includes .h files for the compobj, and oleauto  subcomponents.
//
//----------------------------------------------------------------------------
#if !defined( _OLE2_H_ )
#define _OLE2_H_

// Set packing to 8
#include <pshpack8.h>

// Make 100% sure WIN32 is defined
#ifndef WIN32
#define WIN32    100  // 100 == NT version 1.0
#endif


// SET to remove _export from interface definitions


#include <winerror.h>

#include <objbase.h>
#include <oleauto.h>

// View OBJECT Error Codes

#define E_DRAW                  VIEW_E_DRAW

// IDataObject Error Codes
#define DATA_E_FORMATETC        DV_E_FORMATETC





// Common stuff gleamed from OLE.2,

/* verbs */
#define OLEIVERB_PRIMARY            (0L)
#define OLEIVERB_SHOW               (-1L)
#define OLEIVERB_OPEN               (-2L)
#define OLEIVERB_HIDE               (-3L)
#define OLEIVERB_UIACTIVATE         (-4L)
#define OLEIVERB_INPLACEACTIVATE    (-5L)
#define OLEIVERB_DISCARDUNDOSTATE   (-6L)

// for OleCreateEmbeddingHelper flags; roles in low word; options in high word
#define EMBDHLP_INPROC_HANDLER   0x0000L
#define EMBDHLP_INPROC_SERVER    0x0001L
#define EMBDHLP_CREATENOW    0x00000000L
#define EMBDHLP_DELAYCREATE  0x00010000L

/* extended create function flags */
#define OLECREATE_LEAVERUNNING	0x00000001

/* pull in the MIDL generated header */

#include <oleidl.h>






/****** DV APIs ***********************************************************/


WINOLEAPI CreateDataAdviseHolder(LPDATAADVISEHOLDER FAR* ppDAHolder);







/****** OLE API Prototypes ************************************************/

WINOLEAPI_(DWORD) OleBuildVersion( VOID );

/* helper functions */
/**
 * This function reads the CLSID previously written to a storage object with the WriteClassStg.
 *
 * @param pStg [in] Pointer to the IStorage interface on the storage object containing the CLSID to
 *   be retrieved.
 * @param pclsid [out] Pointer to where the CLSID is written. Can return CLSID_NULL.
 *
 * @return This function supports the standard return value E_OUTOFMEMORY, as well as the following:
 *   - S_OK: The CLSID was returned successfully. This function also returns any of the error values
 *   returned by the IStorage::Stat method.
 *
 * This function is simply a helper function that calls the IStorage::Stat method and retrieves the
 * CLSID previously written to the storage object with a call to WriteClassStg from the STATSTG
 * structure.
 */
WINOLEAPI ReadClassStg(LPSTORAGE pStg, CLSID FAR* pclsid);
/**
 * This function stores the specified CLSID in a storage object.
 *
 * @param pStg [in] IStorage pointer to the storage object that gets a new CLSID.
 * @param rclsid [in] CLSID to be stored with the object.
 *
 * @return - S_OK: Indicates the CLSID was successfully written to the file. - STG_E_MEDIUMFULL:
 *   Indicates the CLSID could not be written due to lack of memory. IStorage::SetClass method error
 *   return values.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * The WriteClassStg function writes a CLSID to the specified storage object so it can be read by
 * the ReadClassStg function. Container applications typically call this function before calling the
 * IPersistStorage::Save method.
 */
WINOLEAPI WriteClassStg(LPSTORAGE pStg, REFCLSID rclsid);
/**
 * This function reads the CLSID previously written to a stream object with the WriteClassStm
 * method.
 *
 * @param pStm [in] Pointer to the IStream interface on the stream object containing the CLSID to be
 *   read. This CLSID must have been previously written to the stream object using WriteClassStm.
 * @param pclsid [out] Pointer to where the CLSID is to be written.
 *
 * @return - S_OK: The CLSID was successfully retrieved. - STG_E_READFAULT: End of file was reached.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * Most applications do not call the ReadClassStm method directly.
 */
WINOLEAPI ReadClassStm(LPSTREAM pStm, CLSID FAR* pclsid);
/**
 * This function writes a CLSID to the specified stream object so it can be read by the ReadClassStm
 * function. Most applications do not call WriteClassStm directly.
 *
 * @param pStm [in] IStream pointer to the stream into which the CLSID is to be written.
 * @param rclsid [in] CLSID to write to the stream.
 *
 * @return - S_OK: Indicates the CLSID was successfully written. - STG_E_MEDIUMFULL: The CLSID could
 *   not be written because there is no space left on device. IStorage::SetClass method error return
 *   values.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 *
 * The WriteClassStm function writes a CLSID to the specified stream object so it can be read by the
 * ReadClassStm function. Most applications do not call WriteClassStm directly.
 */
WINOLEAPI WriteClassStm(LPSTREAM pStm, REFCLSID rclsid);
WINOLEAPI WriteFmtUserTypeStg (LPSTORAGE pstg, CLIPFORMAT cf, LPOLESTR lpszUserType);
WINOLEAPI ReadFmtUserTypeStg (LPSTORAGE pstg, CLIPFORMAT FAR* pcf, LPOLESTR FAR* lplpszUserType);


/* init/term */

WINOLEAPI OleInitialize(LPVOID pvReserved);
WINOLEAPI_(void) OleUninitialize(void);


/* APIs to query whether (Embedded/Linked) object can be created from
   the data object */

WINOLEAPI  OleQueryLinkFromData(LPDATAOBJECT pSrcDataObject);
WINOLEAPI  OleQueryCreateFromData(LPDATAOBJECT pSrcDataObject);


/* Object creation APIs */

/**
 * This function creates an embedded object identified by a CLSID. It is typically used to implement
 * a menu item that allows the end user to insert a new object.
 *
 * @param rclsid [in] CLSID of the embedded object that is to be created.
 * @param riid [in] Reference to the identifier of the interface, usually IID_IOleObject (defined in
 *   the OLE headers as the interface identifier for IOleObject), through which the caller will
 *   communicate with the new object.
 * @param renderopt [in] Value from the enumeration OLERENDER, indicating the locally cached drawing
 *   capabilities the newly created object is to have. The OLERENDER value chosen affects the possible
 *   values for the pFormatEtc parameter.
 * @param pFormatEtc [in] Depending on which of the OLERENDER flags is used as the value of
 *   renderopt, pointer to one of the FORMATETC enumeration values. Refer to the OLERENDER enumeration
 *   for restrictions. This parameter, along with the renderopt parameter, specifies what the new
 *   object can cache initially.
 * @param pClientSite [in] If you want OleCreate to call IOleObject::SetClientSite, pClientSite is
 *   the pointer to the IOleClientSite interface on the container. The value can be NULL, in which
 *   case you must specifically call IOleClientSite::SetClientSite before attempting operations.
 * @param pStg [in] Pointer to an instance of the IStorage interface on the storage object. This
 *   parameter cannot be NULL.
 * @param ppvObject [out] Pointer to the pointer variable that receives the interface pointer
 *   requested in riid. Upon successful return, *ppvObject contains the requested interface pointer.
 *
 * @return This function supports the standard return value E_OUTOFMEMORY, as well as the following:
 *   Value Description S_OK Embedded object created successfully.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application. For more information about handling exceptions, see
 * Programming Considerations.
 *
 * The OleCreate function creates a new embedded object, and is typically called to implement the
 * menu item Insert New Object. When OleCreate returns, the object it has created is blank (contains
 * no data), unless renderopt is OLERENDER_DRAW or OLERENDER_FORMAT, and is loaded. Containers
 * typically then call the OleRun function or IOleObject::DoVerb to show the object for initial
 * editing.
 *
 * The rclsid parameter specifies the CLSID of the requested object. CLSIDs of registered objects
 * are stored in the system registry. When an application user selects Insert Object, a selection
 * box allows the user to select the type of object desired from those in the registry. When
 * OleCreate is used to implement the Insert Object menu item, the CLSID associated with the
 * selected item is assigned to the rclsid parameter of OleCreate.
 *
 * The riid parameter specifies the interface the client will use to communicate with the new
 * object. Upon successful return, the ppvObject parameter holds a pointer to the requested
 * interface.
 *
 * The created object's cache contains information that allows a presentation of a contained object
 * when the container is opened. Information about what should be cached is passed in the renderopt
 * and pFormatetc values. When OleCreate returns, the created object's cache is not necessarily
 * filled. Instead, the cache is filled the first time the object enters the running state. The
 * caller can add additional cache control with a call to IOleCache::Cache after the return of
 * OleCreate and before the object is run. If renderopt is OLERENDER_DRAW or OLERENDER_FORMAT,
 * OleCreate requires that the object support the IOleCache interface. There is no such requirement
 * for any other value of renderopt.
 *
 * If pClientSite is non-NULL, OleCreate calls IOleObject::SetClientSite through the pClientSite
 * pointer. IOleClientSite is the primary interface by which an object requests services from its
 * container. If pClientSite is NULL, you must make a specific call to IOleObject::SetClientSite
 * before attempting any operations.
 */
WINOLEAPI  OleCreate(REFCLSID rclsid, REFIID riid, DWORD renderopt,
                LPFORMATETC pFormatEtc, LPOLECLIENTSITE pClientSite,
                LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateEx(REFCLSID rclsid, REFIID riid, DWORD dwFlags,
                DWORD renderopt, ULONG cFormats, DWORD* rgAdvf,
                LPFORMATETC rgFormatEtc, IAdviseSink FAR* lpAdviseSink,
                DWORD FAR* rgdwConnection, LPOLECLIENTSITE pClientSite,
                LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateFromData(LPDATAOBJECT pSrcDataObj, REFIID riid,
                DWORD renderopt, LPFORMATETC pFormatEtc,
                LPOLECLIENTSITE pClientSite, LPSTORAGE pStg,
                LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateFromDataEx(LPDATAOBJECT pSrcDataObj, REFIID riid,
                DWORD dwFlags, DWORD renderopt, ULONG cFormats, DWORD* rgAdvf,
                LPFORMATETC rgFormatEtc, IAdviseSink FAR* lpAdviseSink,
                DWORD FAR* rgdwConnection, LPOLECLIENTSITE pClientSite,
                LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkFromData(LPDATAOBJECT pSrcDataObj, REFIID riid,
                DWORD renderopt, LPFORMATETC pFormatEtc,
                LPOLECLIENTSITE pClientSite, LPSTORAGE pStg,
                LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkFromDataEx(LPDATAOBJECT pSrcDataObj, REFIID riid,
                DWORD dwFlags, DWORD renderopt, ULONG cFormats, DWORD* rgAdvf,
                LPFORMATETC rgFormatEtc, IAdviseSink FAR* lpAdviseSink,
                DWORD FAR* rgdwConnection, LPOLECLIENTSITE pClientSite,
                LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateStaticFromData(LPDATAOBJECT pSrcDataObj, REFIID iid,
                DWORD renderopt, LPFORMATETC pFormatEtc,
                LPOLECLIENTSITE pClientSite, LPSTORAGE pStg,
                LPVOID FAR* ppvObj);


WINOLEAPI  OleCreateLink(LPMONIKER pmkLinkSrc, REFIID riid,
            DWORD renderopt, LPFORMATETC lpFormatEtc,
            LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkEx(LPMONIKER pmkLinkSrc, REFIID riid,
            DWORD dwFlags, DWORD renderopt, ULONG cFormats, DWORD* rgAdvf,
            LPFORMATETC rgFormatEtc, IAdviseSink FAR* lpAdviseSink,
            DWORD FAR* rgdwConnection, LPOLECLIENTSITE pClientSite,
            LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkToFile(LPCOLESTR lpszFileName, REFIID riid,
            DWORD renderopt, LPFORMATETC lpFormatEtc,
            LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkToFileEx(LPCOLESTR lpszFileName, REFIID riid,
            DWORD dwFlags, DWORD renderopt, ULONG cFormats, DWORD* rgAdvf,
            LPFORMATETC rgFormatEtc, IAdviseSink FAR* lpAdviseSink,
            DWORD FAR* rgdwConnection, LPOLECLIENTSITE pClientSite,
            LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateFromFile(REFCLSID rclsid, LPCOLESTR lpszFileName, REFIID riid,
            DWORD renderopt, LPFORMATETC lpFormatEtc,
            LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateFromFileEx(REFCLSID rclsid, LPCOLESTR lpszFileName, REFIID riid,
            DWORD dwFlags, DWORD renderopt, ULONG cFormats, DWORD* rgAdvf,
            LPFORMATETC rgFormatEtc, IAdviseSink FAR* lpAdviseSink,
            DWORD FAR* rgdwConnection, LPOLECLIENTSITE pClientSite,
            LPSTORAGE pStg, LPVOID FAR* ppvObj);

WINOLEAPI  OleLoad(LPSTORAGE pStg, REFIID riid, LPOLECLIENTSITE pClientSite,
            LPVOID FAR* ppvObj);

/**
 * This function saves an object opened in transacted mode into the specified storage object.
 *
 * @param pPS [in] Pointer to the IPersistStorage interface on the object to be saved.
 * @param pStg [in] Pointer to the IStorage interface on the destination storage object to which the
 *   object indicated in pPS is to be saved.
 * @param fSameAsLoad [in] Boolean that is set to TRUE if pStg is the same storage object from which
 *   the object was loaded or created, or to FALSE if pstg was loaded or created from a different
 *   storage object.
 *
 * @return - S_OK: The object was successfully saved. - STG_E_MEDIUMFULL: The object could not be
 *   saved due to lack of disk space. This function can also return any of the error values returned
 *   by the IPersistStorage::Save method.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application. For more information about handling exceptions, see
 * Programming Considerations.
 *
 * The OleSave helper function handles the common situation in which an object is open in transacted
 * mode and is then to be saved into the specified storage object which uses the OLE-provided
 * compound file implementation. Transacted mode means that changes to the object are buffered until
 * either of the IStorage methods Commit or Revert is called. Callers can handle other situations by
 * calling the IPersistStorage and IStorage interfaces directly.
 *
 * OleSave does the following:
 *
 * Calls the IPersistStorage::GetClassID method to get the CLSID of the object.
 *
 * Writes the CLSID to the storage object using the WriteClassStg function.
 *
 * Calls the IPersistStorage::Save method to save the object.
 *
 * If there were no errors on the save; calls the IStorage::Commit method to commit the changes.
 *
 * Note Static objects are saved into a stream called CONTENTS. Static metafile objects get saved in
 * "placeable metafile format" and static DIB data gets saved in "DIB file format." These formats
 * are defined to be the OLE standards for metafile and DIB. All data transferred using an IStream
 * interface or a file transferred using IDataObject::GetDataHere must be in these formats. Also,
 * all objects whose default file format is a metafile or DIB must write their data into a CONTENTS
 * stream using these standard formats.
 */
WINOLEAPI  OleSave(LPPERSISTSTORAGE pPS, LPSTORAGE pStg, BOOL fSameAsLoad);

WINOLEAPI  OleLoadFromStream( LPSTREAM pStm, REFIID iidInterface, LPVOID FAR* ppvObj);
WINOLEAPI  OleSaveToStream( LPPERSISTSTREAM pPStm, LPSTREAM pStm );


/**
 * This function notifies an object embedded in an OLE container to ensure correct reference.
 *
 * @param pUnk [in] Pointer to the IUnknown interface of the object.
 * @param fContained [in] Boolean that is set to TRUE if the object is an embedded object, or to
 *   FALSE otherwise.
 *
 * @return This function supports the standard return values E_INVALIDARG, E_OUTOFMEMORY and
 *   E_UNEXPECTED, as well as the following: - S_OK: The object was notified successfully.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application. For more information about handling exceptions, see
 * Programming Considerations.
 *
 * The OleSetContainedObject function notifies an object that it is embedded in an OLE container.
 * The implementation of OleSetContainedObject was changed in OLE 2.01 to coincide with the
 * publication of the IRunnableObject interface. You can use OleSetContainedObject and the
 * IRunnableObject::SetContainedObject method interchangeably. The OleSetContainedObject function
 * queries the object for a pointer to the IRunnableObject interface. If successful, the function
 * returns the results of calling IRunnableObject::SetContainedObject.
 *
 * Note The implementation of OleSetContainedObject in earlier versions of OLE differs from that
 * described here.
 */
WINOLEAPI  OleSetContainedObject(LPUNKNOWN pUnknown, BOOL fContained);
WINOLEAPI  OleNoteObjectVisible(LPUNKNOWN pUnknown, BOOL fVisible);


/* Drag/Drop APIs */

WINOLEAPI  RegisterDragDrop(HWND hwnd, LPDROPTARGET pDropTarget);
WINOLEAPI  RevokeDragDrop(HWND hwnd);
WINOLEAPI  DoDragDrop(LPDATAOBJECT pDataObj, LPDROPSOURCE pDropSource,
            DWORD dwOKEffects, LPDWORD pdwEffect);

/* Clipboard APIs */

WINOLEAPI  OleSetClipboard(LPDATAOBJECT pDataObj);
WINOLEAPI  OleGetClipboard(LPDATAOBJECT FAR* ppDataObj);
WINOLEAPI  OleFlushClipboard(void);
WINOLEAPI  OleIsCurrentClipboard(LPDATAOBJECT pDataObj);


/* InPlace Editing APIs */

WINOLEAPI_(HOLEMENU)   OleCreateMenuDescriptor (HMENU hmenuCombined,
                                LPOLEMENUGROUPWIDTHS lpMenuWidths);
/**
 * This function installs or removes OLE dispatching code from the container's frame window.
 *
 * @param holemenu [in] Handle to the composite menu descriptor returned by the
 *   OleCreateMenuDescriptor function. If NULL, the dispatching code is unhooked.
 * @param hwndFrame [in] Handle to the container's frame window where the in-place composite menu is
 *   to be installed.
 * @param hwndActiveObject [in] Handle to the object's in-place activation window. OLE dispatches
 *   menu messages and commands to this window.
 * @param lpFrame [in] Long pointer to the IOleInPlaceFrame interface on the container's frame
 *   window.
 * @param lpActiveObj [in] Long pointer to the IOleInPlaceActiveObject interface on the active
 *   in-place object.
 *
 * @return This function supports the standard return values E_FAIL, E_INVALIDARG and E_UNEXPECTED,
 *   as well as the following: - S_OK: The menu was installed correctly.
 *
 * The hwndActiveObject and the lpActiveObj parameters are not supported. Set to NULL.
 *
 * The container should call OleSetMenuDescriptor to install the dispatching code on hwndFrame when
 * the object calls the IOleInPlaceFrame::SetMenu method, or to remove the dispatching code by
 * passing NULL as the value for holemenu to OleSetMenuDescriptor.
 *
 * If both the lpFrame and lpActiveObj parameters are non-NULL, OLE installs the context-sensitive
 * help F1 message filter for the application. Otherwise, the application must supply its own
 * message filter.
 */
WINOLEAPI              OleSetMenuDescriptor (HOLEMENU holemenu, HWND hwndFrame,
                                HWND hwndActiveObject,
                                LPOLEINPLACEFRAME lpFrame,
                                LPOLEINPLACEACTIVEOBJECT lpActiveObj);
WINOLEAPI              OleDestroyMenuDescriptor (HOLEMENU holemenu);

WINOLEAPI              OleTranslateAccelerator (LPOLEINPLACEFRAME lpFrame,
                            LPOLEINPLACEFRAMEINFO lpFrameInfo, LPMSG lpmsg);


/* Helper APIs */
WINOLEAPI_(HANDLE) OleDuplicateData (HANDLE hSrc, CLIPFORMAT cfFormat,
                        UINT uiFlags);

/**
 * This helper function provides a convenient way to draw objects by encapsulating the
 * IViewObject::Draw method and other related maintenance functions for the drawing rectangle.
 *
 * @param pUnk [in] Pointer to the IUnknown interface on the view object that is to be drawn.
 * @param dwAspect [in] Specifies how the object is to be represented. Representations include
 *   content, an icon, a thumbnail, or a printed document. Valid values are taken from the enumeration
 *   DVASPECT. See DVASPECT for more information.
 * @param hdcDraw [in] Handle to the device context (DC) on which to draw. Cannot be a metafile
 *   device context.
 * @param lprcBounds [in] Long pointer to a RECT structure specifying the rectangle in which the
 *   object should be drawn. This parameter is converted to a RECTL structure and passed to
 *   IViewObject::Draw.
 *
 * @return This function supports the standard return values E_INVALIDARG and E_OUTOFMEMORY, as well
 *   as the following: Value Description S_OK Object was successfully drawn. OLE_E_BLANK No data to
 *   draw from. E_ABORT The draw operation was aborted. VIEW_E_DRAW An error occurred in drawing.
 *   OLE_E_INVALIDRECT The rectangle is invalid. DV_E_NOIVIEWOBJECT The object does not support the
 *   IViewObject interface.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application. For more information about handling exceptions, see
 * Programming Considerations.
 *
 * The OleDraw helper function calls the QueryInterface method for the object specified (pUnk),
 * asking for an IViewObject interface on that object. Then, OleDraw converts the RECT structure to
 * a RECTL structure, and calls IViewObject::Draw as follows:
 *
 *     lpViewObj->Draw(dwAspect,-1,0,0,0,hdcDraw,&rectl,0,0,0);
 *
 * Do not use OleDraw to draw into a metafile because it does not specify the lprcWBounds parameter
 * required for drawing into metafiles.
 */
WINOLEAPI          OleDraw (LPUNKNOWN pUnknown, DWORD dwAspect, HDC hdcDraw,
                    LPCRECT lprcBounds);

/**
 * This function puts an OLE compound document object into the running state.
 *
 * @return This function supports the standard return values E_INVALIDARG and E_UNEXPECTED, as well
 *   as the following: - S_OK: The object was successfully placed in the running state. -
 *   OLE_E_CLASSDIFF: The source of an OLE link has been converted to a different class.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application. For more information about handling exceptions, see
 * Programming Considerations.
 *
 * The OleRun function puts an object in the running state. The implementation of OleRun was changed
 * in OLE 2.01 to coincide with the publication of the IRunnableObject interface. You can use OleRun
 * and IRunnableObject::Run interchangeably. OleRun queries the object for a pointer to
 * IRunnableObject. If successful, the function returns the results of calling the
 * IRunnableObject::Run method.
 *
 * Note The implementation of OleRun in earlier versions of OLE differs from that described here.
 */
WINOLEAPI          OleRun(LPUNKNOWN pUnknown);
/**
 * This function determines whether a compound document object is currently in the running state.
 *
 * @return The return value is TRUE if the object is running; otherwise, it is FALSE.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application. For more information about handling exceptions, see
 * Programming Considerations.
 *
 * You can use OleIsRunning and IRunnableObject::IsRunning interchangeably. OleIsRunning queries the
 * object for a pointer to the IRunnableObject interface and calls its IsRunning method. If
 * successful, the function returns the results of the call to IRunnableObject::IsRunning.
 *
 * Note The implementation of OleIsRunning in earlier versions of OLE differs from that described
 * here.
 */
WINOLEAPI_(BOOL)   OleIsRunning(LPOLEOBJECT pObject);
WINOLEAPI          OleLockRunning(LPUNKNOWN pUnknown, BOOL fLock, BOOL fLastUnlockCloses);
/**
 * This function frees the specified storage medium.
 *
 * @return None.
 *
 * The ReleaseStgMedium function calls the appropriate method or function to release the specified
 * storage medium. Use this function during data transfer operations where storage medium structures
 * are parameters. In addition to identifying the type of the storage medium, this structure
 * specifies the appropriate IUnknown::Release method for releasing the storage medium when it is no
 * longer needed.
 *
 * It is common to pass a STGMEDIUM from one body of code to another, in which the one called can
 * allocate a medium and return it to the caller. ReleaseStgMedium permits flexibility in whether
 * the receiving body of code owns the medium, or whether the original provider of the medium still
 * owns it, in which case the receiving code needs to inform the provider that it can free the
 * medium.
 *
 * When the original provider of the medium is responsible for freeing the medium, the provider
 * calls ReleaseStgMedium, specifying the medium and the appropriate IUnknown pointer as the
 * punkForRelease structure member. Depending on the type of storage medium being freed, one of the
 * following actions is taken, followed by a call to the Release method on the specified IUnknown
 * pointer:
 *
 * Medium ReleaseStgMedium Action TYMED_HGLOBAL None. TYMED_GDI None. TYMED_ENHMF None. TYMED_MFPICT
 * None. TYMED_FILE Frees the file name string using standard memory management mechanisms.
 * TYMED_ISTREAM Calls IStream::Release. TYMED_ISTORAGE Calls IStorage::Release.
 *
 * The provider indicates that the receiver of the medium is responsible for freeing the medium by
 * specifying NULL for the punkForRelease structure member. Then the receiver calls
 * ReleaseStgMedium, which makes a call as described in the following table depending on the type of
 * storage medium being freed:
 *
 * Medium ReleaseStgMedium Action TYMED_HGLOBAL Calls the LocalFree function on the handle.
 * TYMED_GDI Calls the Win32 DeleteObject function on the handle. TYMED_ENHMF Deletes the enhanced
 * metafile. TYMED_FILE Frees the disk file by deleting it. Frees the file name string by using the
 * standard memory management paradigm. TYMED_ISTREAM Calls IStream::Release. TYMED_ISTORAGE Calls
 * IStorage::Release.
 *
 * In either case, after the call to ReleaseStgMedium, the specified storage medium is invalid and
 * can no longer be used.
 */
WINOLEAPI_(void)   ReleaseStgMedium(LPSTGMEDIUM);
/**
 * This function instantiates an advise holder object for managing compound document notifications.
 * It passes out a pointer to the object's OLE implementation of the IOleAdviseHolder interface.
 *
 * @return This function supports the standard return value E_OUTOFMEMORY, as well as the following:
 *   - S_OK: The new OLE advise holder returned successfully.
 *
 * The function CreateOleAdviseHolder creates an instance of an advise holder, which supports the
 * OLE implementation of the IOleAdviseHolder interface. The methods of this interface are intended
 * to be used to implement the advisory methods of IOleObject, and, when advisory connections have
 * been set up with objects supporting an advisory sink, to send notifications of changes in the
 * object to the advisory sink. The advise holder returned by CreateOleAdviseHolder will suffice for
 * the great majority of applications. The OLE-provided implementation does not, however, support
 * IOleAdviseHolder::EnumAdvise, so if you need to use this method, you will need to implement your
 * own advise holder.
 *
 * Passing into this function any invalid and, under some circumstances, NULL pointers will result
 * in unexpected termination of the application.
 */
WINOLEAPI          CreateOleAdviseHolder(LPOLEADVISEHOLDER FAR* ppOAHolder);

WINOLEAPI          OleCreateDefaultHandler(REFCLSID clsid, LPUNKNOWN pUnkOuter,
                    REFIID riid, LPVOID FAR* lplpObj);

WINOLEAPI          OleCreateEmbeddingHelper(REFCLSID clsid, LPUNKNOWN pUnkOuter,
                    DWORD flags, LPCLASSFACTORY pCF,
                                        REFIID riid, LPVOID FAR* lplpObj);

WINOLEAPI_(BOOL)   IsAccelerator(HACCEL hAccel, int cAccelEntries, LPMSG lpMsg,
                                        WORD FAR* lpwCmd);
/* Icon extraction Helper APIs */

WINOLEAPI_(HGLOBAL) OleGetIconOfFile(LPOLESTR lpszPath, BOOL fUseFileAsLabel);

WINOLEAPI_(HGLOBAL) OleGetIconOfClass(REFCLSID rclsid,     LPOLESTR lpszLabel,
                                        BOOL fUseTypeAsLabel);

WINOLEAPI_(HGLOBAL) OleMetafilePictFromIconAndLabel(HICON hIcon, LPOLESTR lpszLabel,
                                        LPOLESTR lpszSourceFile, UINT iIconIndex);



/* Registration Database Helper APIs */

WINOLEAPI                  OleRegGetUserType (REFCLSID clsid, DWORD dwFormOfType,
                                        LPOLESTR FAR* pszUserType);

WINOLEAPI                  OleRegGetMiscStatus     (REFCLSID clsid, DWORD dwAspect,
                                        DWORD FAR* pdwStatus);

WINOLEAPI                  OleRegEnumFormatEtc     (REFCLSID clsid, DWORD dwDirection,
                                        LPENUMFORMATETC FAR* ppenum);

WINOLEAPI                  OleRegEnumVerbs (REFCLSID clsid, LPENUMOLEVERB FAR* ppenum);





/* OLE 1.0 conversion APIS */

/***** OLE 1.0 OLESTREAM declarations *************************************/

typedef struct _OLESTREAM FAR*  LPOLESTREAM;

typedef struct _OLESTREAMVTBL
{
    DWORD (CALLBACK* Get)(LPOLESTREAM, void FAR*, DWORD);
    DWORD (CALLBACK* Put)(LPOLESTREAM, const void FAR*, DWORD);
} OLESTREAMVTBL;
typedef  OLESTREAMVTBL FAR*  LPOLESTREAMVTBL;

typedef struct _OLESTREAM
{
    LPOLESTREAMVTBL lpstbl;
} OLESTREAM;


WINOLEAPI OleConvertOLESTREAMToIStorage
    (LPOLESTREAM                lpolestream,
    LPSTORAGE                   pstg,
    const DVTARGETDEVICE FAR*   ptd);

WINOLEAPI OleConvertIStorageToOLESTREAM
    (LPSTORAGE      pstg,
    LPOLESTREAM     lpolestream);


/* Storage Utility APIs */
WINOLEAPI GetHGlobalFromILockBytes (LPLOCKBYTES plkbyt, HGLOBAL FAR* phglobal);
WINOLEAPI CreateILockBytesOnHGlobal (HGLOBAL hGlobal, BOOL fDeleteOnRelease,
                                    LPLOCKBYTES FAR* pplkbyt);

WINOLEAPI GetHGlobalFromStream (LPSTREAM pstm, HGLOBAL FAR* phglobal);
WINOLEAPI CreateStreamOnHGlobal (HGLOBAL hGlobal, BOOL fDeleteOnRelease,
                                LPSTREAM FAR* ppstm);


/* ConvertTo APIS */

WINOLEAPI OleDoAutoConvert(LPSTORAGE pStg, LPCLSID pClsidNew);
WINOLEAPI OleGetAutoConvert(REFCLSID clsidOld, LPCLSID pClsidNew);
WINOLEAPI OleSetAutoConvert(REFCLSID clsidOld, REFCLSID clsidNew);
WINOLEAPI GetConvertStg(LPSTORAGE pStg);
WINOLEAPI SetConvertStg(LPSTORAGE pStg, BOOL fConvert);


WINOLEAPI OleConvertIStorageToOLESTREAMEx
    (LPSTORAGE          pstg,
                                    // Presentation data to OLESTREAM
     CLIPFORMAT         cfFormat,   //      format
     LONG               lWidth,     //      width
     LONG               lHeight,    //      height
     DWORD              dwSize,     //      size in bytes
     LPSTGMEDIUM        pmedium,    //      bits
     LPOLESTREAM        polestm);

WINOLEAPI OleConvertOLESTREAMToIStorageEx
    (LPOLESTREAM        polestm,
     LPSTORAGE          pstg,
                                    // Presentation data from OLESTREAM
     CLIPFORMAT FAR*    pcfFormat,  //      format
     LONG FAR*          plwWidth,   //      width
     LONG FAR*          plHeight,   //      height
     DWORD FAR*         pdwSize,    //      size in bytes
     LPSTGMEDIUM        pmedium);   //      bits

#ifndef RC_INVOKED
#include <poppack.h>
#endif // RC_INVOKED

#endif     // __OLE2_H__

