// The  Telephony  API  is jointly copyrighted by Intel and Microsoft.  You are
// granted  a royalty free worldwide, unlimited license to make copies, and use
// the   API/SPI  for  making  applications/drivers  that  interface  with  the
// specification provided that this paragraph and the Intel/Microsoft copyright
// statement is maintained as is in the text and source code files.
//
// Copyright 1992, 1993 Intel/Microsoft, all rights reserved.

// @CESYSGEN IF CE_MODULES_TAPI

#ifndef TAPI_H
#define TAPI_H

#include <windows.h>

#pragma pack(1)
// Type definitions of the data types used in tapi

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif   /* __cplusplus */


#define DECLARE_OPAQUE32(name)  struct name##__ { int unused; }; \
                                typedef const struct name##__ FAR* name

DECLARE_OPAQUE32(HCALL);
typedef HCALL * LPHCALL;

DECLARE_OPAQUE32(HLINE);
typedef HLINE * LPHLINE;

DECLARE_OPAQUE32(HPHONE);
typedef HPHONE * LPHPHONE;

DECLARE_OPAQUE32(HLINEAPP);
typedef HLINEAPP * LPHLINEAPP;

DECLARE_OPAQUE32(HPHONEAPP);
typedef HPHONEAPP * LPHPHONEAPP;

typedef HICON * LPHICON;
// typedef of the LINE callback procedure
typedef void (CALLBACK * LINECALLBACK)  (DWORD hDevice,
                                              DWORD dwMessage,
                                              DWORD dwInstance,
                                              DWORD dwParam1,
                                              DWORD dwParam2,
                                              DWORD dwParam3);

// typedef of the PHONE callback procedure
typedef void (CALLBACK * PHONECALLBACK)  (DWORD hDevice,
                                               DWORD dwMessage,
                                               DWORD dwInstance,
                                               DWORD dwParam1,
                                               DWORD dwParam2,
                                               DWORD dwParam3);


// Messages for Phones and Lines

/**
 * This message is sent when the status of an address changes on a line that is currently open by
 * the application. The application can invoke lineGetAddressStatus to determine the current status
 * of the address.
 *
 * @param dwDevice Specifies a handle to the line device.
 * @param dwCallbackInstance Specifies the callback instance supplied when opening the line.
 * @param dwParam1 Specifies the address identifier of the address that changed status.
 * @param dwParam2 Specifies the address state that changed. It can be a combination of the
 *   following values: Value Description LINEADDRESSSTATE_OTHER Address-status items other than those
 *   listed below have changed. The application should check the current address status to determine
 *   which items have changed. LINEADDRESSSTATE_DEVSPECIFIC The device-specific item of the address
 *   status has changed. LINEADDRESSSTATE_INUSEZERO The address has changed to idle (it is now in use
 *   by zero stations). LINEADDRESSSTATE_INUSEONE The address has changed from idle or from being used
 *   by many bridged stations to being used by just one station. LINEADDRESSSTATE_INUSEMANY The
 *   monitored or bridged address has changed from being used by one station to being used by more
 *   than one station. LINEADDRESSSTATE_NUMCALLS The number of calls on the address has changed. This
 *   is the result of events such as a new inbound call, an outbound call on the address, or a call
 *   changing its hold status. LINEADDRESSSTATE_FORWARD The forwarding status of the address has
 *   changed, including the number of rings for determining a no-answer condition. The application
 *   should check the address status to determine details about the address's current forwarding
 *   status. LINEADDRESSSTATE_TERMINALS The terminal settings for the address have changed.
 * @param dwParam3 Unused.
 *
 * @return None.
 *
 * The LINE_ADDRESSSTATE message is sent to any application that has opened the line device and that
 * has enabled this message. The sending of this message for the various status items can be
 * controlled and queried using lineGetStatusMessages and lineSetStatusMessages. By default, address
 * status reporting is disabled.
 */
#define LINE_ADDRESSSTATE        0L
/**
 * This message is sent when the call information about the specified call has changed. The
 * application can invoke lineGetCallInfo to determine the current call information.
 *
 * @param dwDevice Specifies a handle to the call.
 * @param dwCallbackInstance Specifies the callback instance supplied when opening the call's line.
 * @param dwParam1 Specifies the call information item that has changed. It can be a combination of
 *   the following values: Value Description LINECALLINFOSTATE_OTHER Information items other than
 *   those listed below have changed. The application should check the current call information to
 *   determine which items have changed. LINECALLINFOSTATE_DEVSPECIFIC The device-specific field of
 *   the call-information record has changed. LINECALLINFOSTATE_BEARERMODE The bearer mode field of
 *   the call-information record has changed. LINECALLINFOSTATE_RATE The rate field of the
 *   call-information record has changed. LINECALLINFOSTATE_MEDIAMODE The media mode field of the
 *   call-information record has changed. LINECALLINFOSTATE_APPSPECIFIC The application-specific field
 *   of the call-information record has changed. LINECALLINFOSTATE_CALLID The call identifier field of
 *   the call-information record has changed. LINECALLINFOSTATE_RELATEDCALLID The related call
 *   identifier field of the call-information record has changed. LINECALLINFOSTATE_ORIGIN The origin
 *   field of the call-information record has changed. LINECALLINFOSTATE_REASON The reason field of
 *   the call-information record has changed. LINECALLINFOSTATE_COMPLETIONID The completion identifier
 *   field of the call-information record has changed. LINECALLINFOSTATE_NUMOWNERINCR The number of
 *   owner fields in the call-information record was increased. LINECALLINFOSTATE_NUMOWNERDECR The
 *   number of owner fields in the call-information record was decreased.
 *   LINECALLINFOSTATE_NUMMONITORS The number of monitors fields in the call-information record has
 *   changed. LINECALLINFOSTATE_TRUNK The trunk field of the call information record has changed.
 *   LINECALLINFOSTATE_CALLERID One of the caller ID-related fields of the call information record has
 *   changed. LINECALLINFOSTATE_CALLEDID One of the caller ID-related fields of the call information
 *   record has changed. LINECALLINFOSTATE_CONNECTEDID One of the connected identifier-related fields
 *   of the call information record has changed. LINECALLINFOSTATE_REDIRECTIONID One of the
 *   redirection identifier-related fields of the call information record has changed.
 *   LINECALLINFOSTATE_REDIRECTINGID One of the redirecting identifier-related fields of the call
 *   information record has changed. LINECALLINFOSTATE_DISPLAY The display field of the call
 *   information record has changed. LINECALLINFOSTATE_USERUSERINFO The user-user information of the
 *   call information record has changed. LINECALLINFOSTATE_HIGHLEVELCOMP The high-level compatibility
 *   field of the call information record has changed. LINECALLINFOSTATE_LOWLEVELCOMP The low-level
 *   compatibility field of the call information record has changed. LINECALLINFOSTATE_CHARGINGINFO
 *   The charging information of the call information record has changed. LINECALLINFOSTATE_TERMINAL
 *   The terminal mode information of the call information record has changed.
 *   LINECALLINFOSTATE_DIALPARAMS The dial parameters of the call information record has changed.
 *   LINECALLINFOSTATE_MONITORMODES One or more of the digit, tone, or media monitoring fields in the
 *   call information record has changed.
 * @param dwParam2 Unused.
 * @param dwParam3 Unused.
 *
 * @return None.
 *
 * A LINE_CALLINFO message with a NumOwnersIncr, NumOwnersDecr, and/or NumMonitorsChanged indication
 * is sent to applications that already have a handle for the call. This can be the result of
 * another application changing ownership or monitorship to a call with lineOpen, lineClose, and
 * lineShutdown.
 *
 * These LINE_CALLINFO messages are not sent when a notification of a new call is provided in a
 * LINE_CALLSTATE message, because the call information already reflects the correct number of
 * owners and monitors at the time the LINE_CALLSTATE messages are sent. LINE_CALLINFO messages are
 * also suppressed in the case where a call is offered by TAPI to monitors through the
 * LINECALLSTATE_UNKNOWN mechanism.
 *
 * Note The application that causes a change in the number of owners or monitors (for example, by
 * invoking lineDeallocateCall or lineSetCallPrivilege) does not itself receive a message indicating
 * that the change has been done.
 *
 * No LINE_CALLINFO messages are sent for a call after the call has entered the idle state.
 * Specifically, changes in the number of owners and monitors are not reported as applications
 * deallocate their handles for the idle call.
 */
#define LINE_CALLINFO            1L
/**
 * This message is sent when the status of the specified call has changed. Several such messages
 * will typically be received during the lifetime of a call. Applications are notified of new
 * incoming calls with this message; the new call will be in the offering state. The application can
 * use lineGetCallStatus to retrieve more detailed information about the current status of the call.
 *
 * @param dwDevice Specifies a handle to the call.
 * @param dwCallbackInstance Specifies the callback instance supplied when opening the call's line.
 * @param dwParam1 Specifies the new call state. It is only one of the following LINECALLSTATE_
 *   values: Value Description LINECALLSTATE_IDLE The call is idle-no call actually exists.
 *   LINECALLSTATE_OFFERING The call is being offered to the station, signaling the arrival of a new
 *   call. In some environments, a call in the offering state does not automatically alert the user.
 *   Alerting is done by the switch instructing the line to ring; it does not affect any call states.
 *   LINECALLSTATE_ACCEPTED The call was offering and has been accepted. This indicates to other
 *   (monitoring) applications that the current owner application has claimed responsibility for
 *   answering the call. In ISDN, this also indicates that alerting to both parties has started.
 *   LINECALLSTATE_DIALTONE The call is receiving a dial tone from the switch, which means that the
 *   switch is ready to receive a dialed number. LINECALLSTATE_DIALING Destination address information
 *   (a phone number) is being sent to the switch over the call. Note that lineGenerateDigits does not
 *   place the line into the dialing state. LINECALLSTATE_RINGBACK The call is receiving ringback from
 *   the called address. Ringback indicates that the other station has been reached and is being
 *   alerted. LINECALLSTATE_BUSY The call is receiving a busy tone. Busy tone indicates that the call
 *   cannot be completed-either a circuit (trunk) or the remote party's station are in use.
 *   LINECALLSTATE_SPECIALINFO Special information is sent by the network. Special information is
 *   typically sent when the destination cannot be reached. LINECALLSTATE_CONNECTED The call has been
 *   established and the connection is made. Information is able to flow over the call between the
 *   originating address and the destination address. LINECALLSTATE_PROCEEDING Dialing has completed
 *   and the call is proceeding through the switch or telephone network. LINECALLSTATE_ONHOLD The call
 *   is on hold by the switch. LINECALLSTATE_CONFERENCED The call is currently a member of a
 *   multiparty conference call. LINECALLSTATE_ONHOLDPENDCONF The call is currently on hold while it
 *   is being added to a conference. LINECALLSTATE_ONHOLDPENTRANSFER The call is currently on hold
 *   awaiting transfer to another number. LINECALLSTATE_DISCONNECTED The remote party has disconnected
 *   from the call. LINECALLSTATE_UNKNOWN The state of the call is not known. This may be due to
 *   limitations of the call-progress detection implementation.
 * @param dwParam2 Specifies call-state-dependent information. If dwParam1 is LINECALLSTATE_BUSY,
 *   dwParam2 contains details about the busy mode. This parameter uses the following LINEBUSYMODE_
 *   constants: Value Description LINEBUSYMODE_STATION The busy signal indicates that the called
 *   party's station is busy. This is usually signaled by means of a "normal" busy tone.
 *   LINEBUSYMODE_TRUNK The busy signal indicates that a trunk or circuit is busy. This is usually
 *   signaled with a "long" busy tone. LINEBUSYMODE_UNKNOWN The busy signal's specific mode is
 *   currently unknown, but may become known later. LINEBUSYMODE_UNAVAIL The busy signal's specific
 *   mode is unavailable and cannot become known. If dwParam1 is LINECALLSTATE_CONNECTED, dwParam2
 *   contains details about the connected mode. This parameter uses the following LINECONNECTEDMODE_
 *   constants: Value Description LINECONNECTEDMODE_ACTIVE Indicates that the call is connected at the
 *   current station (the current station is a participant in the call). LINECONNECTEDMODE_INACTIVE
 *   Indicates that the call is active at one or more other stations, but the current station is not a
 *   participant in the call. If dwParam1 is LINECALLSTATE_DIALTONE, dwParam2 contains the details
 *   about the dial tone mode. This parameter uses the following LINEDIALTONEMODE_ constants: Value
 *   Description LINEDIALTONEMODE_NORMAL This is a "normal" dial tone, which typically is a continuous
 *   tone. LINEDIALTONEMODE_SPECIAL This is a special dial tone indicating that a certain condition is
 *   currently in effect. LINEDIALTONEMODE_INTERNAL This is an internal dial tone, as within a PBX.
 *   LINEDIALTONEMODE_EXTERNAL This is an external (public network) dial tone.
 *   LINEDIALTONEMODE_UNKNOWN The dial tone mode is currently unknown, but may become known later.
 *   LINEDIALTONEMODE_UNAVAIL The dial tone mode is unavailable and cannot become known. If dwParam1
 *   is LINECALLSTATE_OFFERING, dwParam2 contains details about the connected mode. This parameter
 *   uses the following LINEOFFERINGMODE_ constants: Value Description LINEOFFERINGMODE_ACTIVE
 *   Indicates that the call is alerting at the current station (is accompanied by
 *   LINEDEVSTATE_RINGING messages), and if any application is set up to automatically answer, it may
 *   do so. LINEOFFERINGMODE_INACTIVE Indicates that the call is being offered at more than one
 *   station, but the current station is not alerting (for example, it may be an attendant station
 *   where the offering status is advisory, such as blinking a light). If dwParam1 is
 *   LINECALLSTATE_SPECIALINFO, dwParam2 contains the details about the special information mode. This
 *   parameter uses the following LINESPECIALINFO_ constants: Value Description
 *   LINESPECIALINFO_NOCIRCUIT This special information tone precedes a "no circuit" or emergency
 *   announcement (trunk blockage category). LINESPECIALINFO_CUSTIRREG This special information tone
 *   precedes a vacant number, AIS, Centrex number change and nonworking station, access code not
 *   dialed or dialed in error, or manual intercept operator message (customer irregularity category).
 *   LINESPECIALINFO_REORDER This special information tone precedes a reorder announcement (equipment
 *   irregularity category). LINESPECIALINFO_UNKNOWN Specifics about the special information tone are
 *   currently unknown but may become known later. LINESPECIALINFO_UNAVAIL Specifics about the special
 *   information tone are unavailable and cannot become known. If dwParam1 is
 *   LINECALLSTATE_DISCONNECTED, dwParam2 contains details about the disconnect mode. This parameter
 *   uses the following LINEDISCONNECTMODE_ constants: Value Description LINEDISCONNECTMODE_NORMAL
 *   This is a "normal" disconnect request by the remote party, the call was terminated normally.
 *   LINEDISCONNECTMODE_UNKNOWN The reason for the disconnect request is unknown.
 *   LINEDISCONNECTMODE_REJECT The remote user has rejected the call. LINEDISCONNECTMODE_PICKUP The
 *   call was picked up from elsewhere. LINEDISCONNECTMODE_FORWARDED The call was forwarded by the
 *   switch. LINEDISCONNECTMODE_BUSY The remote user's station is busy. LINEDISCONNECTMODE_NOANSWER
 *   The remote user's station does not answer. LINEDISCONNECTMODE_NODIALTONE A dial tone was not
 *   detected within a service-provider defined timeout, at a point during dialing when one was
 *   expected (such as at a "W" in the dialable string). LINEDISCONNECTMODE_BADADDRESS The destination
 *   address in invalid. LINEDISCONNECTMODE_UNREACHABLE The remote user could not be reached.
 *   LINEDISCONNECTMODE_CONGESTION The network is congested. LINEDISCONNECTMODE_INCOMPATIBLE The
 *   remote user's station equipment is incompatible for the type of call requested.
 *   LINEDISCONNECTMODE_UNAVAIL The reason for the disconnect is unavailable and cannot become known
 *   later. Note In circumstances where a delayed response is appropriate, use
 *   LINEDISCONNECTMODE_TEMPFAILURE. Where a blacklisted response is appropriate, use
 *   LINEDISCONNECT_BLOCKED. If dwParam1 is LINECALLSTATE_CONFERENCED, dwParam2 contains the hConfCall
 *   parameter of the parent call of the conference of which the subject hCall is a member. If the
 *   call specified in dwParam2 was not previously considered by the application to be a parent
 *   conference call (hConfCall), the application must do so as a result of this message. If the
 *   application does not have a handle to the parent call of the conference (because it has
 *   previously called lineDeallocateCall on that handle) dwParam2 is set to NULL.
 * @param dwParam3 If zero, this parameter specifies that there has been no change in the
 *   application's privilege for the call. If nonzero, it specifies the application's privilege to the
 *   call. This occurs in the following situations: (1) The first time that the application is given a
 *   handle to this call; (2) When the application is the target of a call handoff (even if the
 *   application already was an owner of the call). This parameter uses the following
 *   LINECALLPRIVILEGE_ constants: Value Description LINECALLPRIVILEGE_MONITOR The application has
 *   monitor privilege. LINECALLPRIVILEGE_OWNER The application has owner privilege.
 *
 * @return None.
 *
 * This message is sent to any application that has a handle for the call. The LINE_CALLSTATE
 * message also notifies applications that monitor calls on a line about the existence and state of
 * outbound calls established by other applications or manually by the user (for example, on an
 * attached phone device). The call state of such calls reflects the actual state of the call, which
 * is not offering. By examining the call state, the application can determine whether the call is
 * an inbound call that needs to be answered or not.
 *
 * A LINE_CALLSTATE message with an unknown call state can be sent to a monitoring application as
 * the result of a successful lineMakeCall function that has been requested by another application.
 * At the same time that the requesting application is sent a LINE_REPLY (success) for the requested
 * operation, any monitoring applications on the line are sent the LINE_CALLSTATE (unknown) message.
 * A LINE_CALLSTATE message indicating the "real" call state of the newly generated call is sent
 * (using information provided by the service provider) to the requesting and monitoring
 * applications shortly thereafter.
 *
 * A LINE_CALLSTATE (unknown) message is sent to monitoring applications only if
 * lineCompleteTransfer causes calls to be resolved into a three-way conference.
 *
 * For backward compatibility, older applications are not expecting any particular value in dwParam2
 * of a LINECALLSTATE_CONFERENCED message. TAPI therefore passes the parent call hConfCall in
 * dwParam2 regardless of the API version of the application receiving the message. In the case of a
 * conference call initiated by the service provider, the older application is not aware that the
 * parent call has become a conference call unless it happens to spontaneously examine other
 * information (for example, call lineGetConfRelatedCalls)
 *
 * This message cannot be disabled.
 */
#define LINE_CALLSTATE           2L
/**
 * This message is sent when the specified line device has been forcibly closed. The line device
 * handle or any call handles for calls on the line are no longer valid once this message has been
 * sent.
 *
 * @param dwDevice Specifies a handle to the line device that was closed. This handle is no longer
 *   valid.
 * @param dwCallbackInstance Specifies the callback instance supplied when opening the line.
 * @param dwParam1 Unused.
 * @param dwParam2 Unused.
 * @param dwParam3 Unused.
 *
 * @return None.
 *
 * The LINE_CLOSE message is only sent to any application after an open line has been forcibly
 * closed. This can be done to prevent a single application from monopolizing a line device for too
 * long. Whether or not the line can be reopened immediately after a forced close is
 * device-specific.
 *
 * A line device can also be forcibly closed after the user has modified the configuration of that
 * line or its driver. If the user wants the configuration changes to be effective immediately (as
 * opposed to after the next system restart), and they affect the application's current view of the
 * device (such as a change in device capabilities), then a service provider can forcibly close the
 * line device.
 */
#define LINE_CLOSE               3L
/**
 * This message is sent to notify the application about device-specific events occurring a line,
 * address or call. The meaning of the message and the interpretation of the parameters is device
 * specific.
 *
 * @param dwDevice Specifies a handle to either a line device or call. This is device specific.
 * @param dwCallbackInstance Specifies the callback instance supplied when opening the line.
 * @param dwParam1 Device specific.
 * @param dwParam2 Device specific.
 * @param dwParam3 Device specific.
 *
 * @return None.
 *
 * The LINE_DEVSPECIFIC message is used by a service provider in conjunction with the
 * lineDevSpecific function. Its meaning is device specific.
 */
#define LINE_DEVSPECIFIC         4L
#define LINE_DEVSPECIFICFEATURE  5L
#define LINE_GATHERDIGITS        6L
#define LINE_GENERATE            7L
/**
 * This message is sent when the state of a line device has changed. The application can invoke
 * lineGetLineDevStatus to determine the new status of the line.
 *
 * @param dwDevice Specifies a handle to the line device. This parameter is NULL when dwParam1 is
 *   LINEDEVSTATE_REINIT.
 * @param dwCallbackInstance Specifies the callback instance supplied when opening the line. If the
 *   dwParam1 parameter is LINEDEVSTATE_REINIT, the dwCallbackInstance parameter is not valid and is
 *   set to zero.
 * @param dwParam1 Specifies the line device status item that has changed. It can be a combination
 *   of the following LINEDEVSTATE_ constants: Value Description LINEDEVSTATE_OTHER Device status
 *   items other than those listed below have changed. The application should check the current device
 *   status to determine which items have changed. LINEDEVSTATE_RINGING The switch tells the line to
 *   alert the user. Service providers notify applications on each ring cycle by sending messages
 *   containing this constant. For example, in the United States, service providers send a message
 *   with this constant every six seconds. LINEDEVSTATE_CONNECTED The line was previously disconnected
 *   and is now connected to TAPI. LINEDEVSTATE_DISCONNECTED This line was previously connected and is
 *   now disconnected from TAPI. LINEDEVSTATE_MSGWAITON The "message waiting" indicator is turned on.
 *   LINEDEVSTATE_MSGWAITOFF The "message waiting" indicator is turned off.
 *   LINEDEVSTATE_NUMCOMPLETIONS The number of outstanding call completions on the line device has
 *   changed. LINEDEVSTATE_INSERVICE The line is connected to TAPI. This happens when TAPI is first
 *   activated, or when the line wire is physically plugged in and in service at the switch while TAPI
 *   is active. LINEDEVSTATE_OUTOFSERVICE The line is out of service at the switch or physically
 *   disconnected. TAPI cannot be used to operate on the line device. LINEDEVSTATE_MAINTENANCE
 *   Maintenance is being performed on the line at the switch. TAPI cannot be used to operate on the
 *   line device. LINEDEVSTATE_OPEN The line has been opened by another application.
 *   LINEDEVSTATE_CLOSE The line has been closed by another application. LINEDEVSTATE_NUMCALLS The
 *   number of calls on the line device has changed. LINEDEVSTATE_TERMINALS The terminal settings have
 *   changed. LINEDEVSTATE_ROAMMODE The roaming state of the line device has changed.
 *   LINEDEVSTATE_BATTERY The battery level has changed significantly (cellular). LINEDEVSTATE_SIGNAL
 *   The signal level has changed significantly (cellular). LINEDEVSTATE_DEVSPECIFIC The line's
 *   device-specific information has changed. LINEDEVSTATE_REINIT Items have changed in the
 *   configuration of line devices. To become aware of these changes (as with the appearance of new
 *   line devices), the application should reinitialize its use of TAPI. The dwDevice parameter is
 *   left NULL for this state change as it applies to any of the lines in the system.
 *   LINEDEVSTATE_LOCK The locked status of the line device has changed. (For more information, refer
 *   to the description of the LINEDEVSTATUSFLAGS_LOCKED bit of the LINEDEVSTATUSFLAGS_ constants.)
 *   LINEDEVSTATE_CAPSCHANGE Indicates that, due to configuration changes made by the user or other
 *   circumstances, one or more of the members in the LINEDEVCAPS structure for the address have
 *   changed. The application should use lineGetDevCaps to read the updated structure.
 *   LINEDEVSTATE_CONFIGCHANGE Indicates that configuration changes have been made to one or more of
 *   the media devices associated with the line device. The application, if it desires, can use
 *   lineGetDevConfig to read the updated information. LINEDEVSTATE_TRANSLATECHANGE Indicates that,
 *   due to configuration changes made by the user or other circumstances, one or more of the members
 *   in the LINETRANSLATECAPS structure have changed. The application should use lineGetTranslateCaps
 *   to read the updated structure. LINEDEVSTATE_COMPLCANCEL Indicates that the call completion
 *   identified by the completion identifier contained in parameter dwParam2 of the LINE_LINEDEVSTATE
 *   message has been externally canceled and is no longer considered valid. LINEDEVSTATE_REMOVED
 *   Indicates that the device is being removed from the system by the service provider (most likely
 *   through user action, through a control panel or similar utility). Normally, a LINE_LINEDEVSTATE
 *   message with this value is immediately followed by a LINE_CLOSE message on the device. Subsequent
 *   attempts to access the device prior to TAPI being reinitialized result in LINEERR_NODEVICE being
 *   returned to the application. If a service provider sends a LINE_LINEDEVSTATE message containing
 *   this value to TAPI, TAPI passes it along to applications that have negotiated TAPI version 1.4 or
 *   later; applications negotiating a previous API version do not receive any notification.
 * @param dwParam2 Specifies the interpretation of this parameter depends on the value of dwParam1.
 *   If dwParam1 is LINEDEVSTATE_RINGING, dwParam2 contains the ring mode with which the switch
 *   instructs the line to ring. Valid ring modes are numbers in the range one to dwNumRingModes,
 *   where dwNumRingModes is a line device capability. If dwParam1 is LINEDEVSTATE_REINIT, and the
 *   message was issued by TAPI as a result of translation of a new API message into a REINIT message,
 *   then dwParam2 contains the dwMsg parameter of the original message (for example, LINE_CREATE or
 *   LINE_LINEDEVSTATE). If dwParam2 is zero, this indicates that the REINIT message is a "real"
 *   REINIT message that requires the application to call lineShutdown at its earliest convenience.
 * @param dwParam3 Specifies the interpretation of this parameter depends on the value of dwParam1.
 *   If dwParam1 is LINEDEVSTATE_RINGING, dwParam3 contains the ring count for this ring event. The
 *   ring count starts at zero. If dwParam1 is LINEDEVSTATE_REINIT, and the message was issued by TAPI
 *   as a result of translation of a new API message into a REINIT message, then dwParam3 contains the
 *   dwParam1 parameter of the original message (for example, LINEDEVSTATE_TRANSLATECHANGE or some
 *   other LINEDEVSTATE_ value, if dwParam2 is LINE_LINEDEVSTATE, or the new device identifier, if
 *   dwParam2 is LINE_CREATE).
 *
 * @return None.
 *
 * The sending of the LINE_LINEDEVSTATE message can be controlled with lineSetStatusMessages. An
 * application can indicate status item changes about which it wants to be notified. By default, all
 * status reporting is disabled except for LINEDEVSTATE_REINIT, which cannot be disabled. This
 * message is sent to all applications that have a handle to the line, including those that called
 * lineOpen with the dwPrivileges parameter set to LINECALLPRIVILEGE_NONE, LINECALLPRIVILEGE_OWNER,
 * LINECALLPRIVILEGE_MONITOR, or permitted combinations of these.
 *
 * The dwParam1 parameter does not support the following constants:
 *
 * LINEDEVSTATE_MESAGEWAITON
 *
 * LINEDEVSTATE_MESSAGEWAITOFF
 *
 * LINEDEVSTATE_INSERVICE
 *
 * LINEDEVSTATE_OUTOFSERVICE
 *
 * LINEDEVSTATE_MAINTENANCE
 *
 * LINEDEVSTATE_TERMINALS
 *
 * LINEDEVSTATE_ROAMMODE
 *
 * LINEDEVSTATE_BATTERY
 *
 * LINEDEVSTATE_SIGNAL
 *
 * LINEDEVSTATE_LOCK
 *
 * LINEDEVSTATE_COMPLCANCEL
 *
 * See Also
 */
#define LINE_LINEDEVSTATE        8L
#define LINE_MONITORDIGITS       9L
#define LINE_MONITORMEDIA        10L
#define LINE_MONITORTONE         11L
/**
 * This message is sent to report the results of function calls that completed asynchronously.
 *
 * @param dwDevice Not used.
 * @param dwCallbackInstance Returns the application's callback instance.
 * @param dwParam1 Specifies the request identifier for which this is the reply.
 * @param dwParam2 Specifies the success or error indication. The application should cast this
 *   parameter into a LONG. Zero indicates success; a negative number indicates an error.
 * @param dwParam3 Unused.
 *
 * @return None.
 *
 * Functions that operate asynchronously return a positive request identifier value to the
 * application. This request identifier is returned with the reply message to identify the request
 * that was completed. The other parameter for the LINE_REPLY message carries the success or failure
 * indication. Possible errors are the same as those defined by the corresponding function. This
 * message cannot be disabled.
 *
 * In some cases, an application may fail to receive the LINE_REPLY message corresponding to a call
 * to an asynchronous function. This occurs if the corresponding call handle is deallocated before
 * the message has been received.
 *
 * Note When an application invokes any asynchronous operation that writes data back into
 * application memory, the application must keep that memory available for writing until a
 * LINE_REPLY or LINE_GATHERDIGITS message is received.
 *
 * The LINE_REQUEST message is sent to the highest priority application that has registered for the
 * corresponding request mode. This message indicates the arrival of an Assisted Telephony request
 * of the specified request mode. If dwParam1 is LINEREQUESTMODE_MAKECALL or
 * LINEREQUESTMODE_MEDIACALL, the application can invoke lineGetRequest using the corresponding
 * request mode to receive the request. If dwParam1 is LINEREQUESTMODE_DROP, the message contains
 * all of the information the request recipient needs to perform the request.
 */
#define LINE_REPLY               12L
#define LINE_REQUEST             13L
#define PHONE_BUTTON             14L
#define PHONE_CLOSE              15L
#define PHONE_DEVSPECIFIC        16L
#define PHONE_REPLY              17L
#define PHONE_STATE              18L

/**
 * This message is sent to inform the application of the creation of a new line device.
 *
 * @param dwDevice Unused.
 * @param dwCallbackInstance Unused.
 * @param dwParam1 Specifies the dwDeviceID of the newly created device.
 * @param dwParam2 Unused.
 * @param dwParam3 Unused.
 *
 * @return None.
 *
 * Older applications (that negotiated TAPI version 1.3) are sent a LINE_LINEDEVSTATE message
 * specifying LINEDEVSTATE_REINIT, which requires them to shut down their use of the API and call
 * lineInitialize again to obtain the new number of devices. Unlike previous versions of TAPI,
 * however, this version does not require all applications to shut down before allowing applications
 * to reinitialize; reinitialization can take place immediately when a new device is created
 * (complete shutdown is still required when a service provider is removed from the system).
 *
 * Applications supporting TAPI version 1.4 or later are sent a LINE_CREATE message. This informs
 * them of the existence of the new device and its new device identifier. The application can then
 * choose whether or not to attempt working with the new device at its leisure. This message is sent
 * to all applications supporting this or subsequent versions of the API that have called
 * lineInitialize or lineInitalizeEx, including those that do not have any line devices open at the
 * time.
 */
#define LINE_CREATE              19L
#define PHONE_CREATE             20L

/**
 * This message is sent to inform an application of the removal, or deletion from the system, of a
 * line device. Generally, this is not used for "temporary" removals, such as extraction of PCMCIA
 * devices, but only for permanent removals in which the device would no longer be reported by the
 * service provider if TAPI were reinitialized.
 *
 * @param dwDevice Reserved; set to zero.
 * @param dwCallbackInstance Reserved; set to zero.
 * @param dwParam1 Specifies the identifier of the line device that was removed.
 * @param dwParam2 Reserved; set to zero.
 * @param dwParam3 Reserved; set to zero.
 *
 * @return None.
 *
 * Applications supporting TAPI version 2.0 or later are sent a LINE_REMOVE message. This informs
 * them that the device has been removed from the system. The LINE_REMOVE message is preceded by a
 * LINE_CLOSE message on each line handle, if the application had the line open. This message is
 * sent to all applications supporting TAPI version 2.0 or later that have called lineInitializeEx,
 * including those that do not have any line devices open at the time.
 *
 * Older applications are sent a LINE_LINEDEVSTATE message specifying LINEDEVSTATE_REMOVED, followed
 * by a LINE_CLOSE message. Unlike the LINE_REMOVE message, however, these older applications can
 * receive these messages only if they have the line open when it is removed. If they do not have
 * the line open, their only indication that the device was removed would be receiving a
 * LINEERR_NODEVICE error when they attempt to access the device.
 *
 * After a device has been removed, any attempt to access the device by its device identifier
 * results in a LINEERR_NODEVICE error. After all TAPI applications have shutdown so that TAPI can
 * restart, and when TAPI is reinitialized, the removed device no longer occupies a device
 * identifier.
 *
 * Implementation Note It is TAPI that returns this LINEERR_NODEVICE; after a LINE_REMOVE message is
 * received from a service provider; no further calls are made to that service provider using that
 * line device identifier.
 */
#define LINE_REMOVE              21L

// Define Simple Telephony Constants.

#define TAPI_REPLY                    WM_USER + 99

#define TAPIERR_CONNECTED           0L
#define TAPIERR_DROPPED             -1L
#define TAPIERR_NOREQUESTRECIPIENT  -2L
#define TAPIERR_REQUESTQUEUEFULL    -3L
#define TAPIERR_INVALDESTADDRESS    -4L
#define TAPIERR_INVALWINDOWHANDLE   -5L
#define TAPIERR_INVALDEVICECLASS    -6L
#define TAPIERR_INVALDEVICEID       -7L
#define TAPIERR_DEVICECLASSUNAVAIL  -8L    
#define TAPIERR_DEVICEIDUNAVAIL     -9L    
#define TAPIERR_DEVICEINUSE         -10L    
#define TAPIERR_DESTBUSY            -11L    
#define TAPIERR_DESTNOANSWER        -12L    
#define TAPIERR_DESTUNAVAIL         -13L    
#define TAPIERR_UNKNOWNWINHANDLE    -14L    
#define TAPIERR_UNKNOWNREQUESTID    -15L    
#define TAPIERR_REQUESTFAILED       -16L
#define TAPIERR_REQUESTCANCELLED    -17L
#define TAPIERR_INVALPOINTER        -18L


#define TAPIMAXDESTADDRESSSIZE    80L 
#define TAPIMAXAPPNAMESIZE        40L
#define TAPIMAXCALLEDPARTYSIZE    40L
#define TAPIMAXCOMMENTSIZE        80L
#define TAPIMAXDEVICECLASSSIZE    40L
#define TAPIMAXDEVICEIDSIZE       40L


// Data types and values for Phones


#define PHONEBUTTONFUNCTION_UNKNOWN          0x00000000
#define PHONEBUTTONFUNCTION_CONFERENCE       0x00000001
#define PHONEBUTTONFUNCTION_TRANSFER         0x00000002
#define PHONEBUTTONFUNCTION_DROP             0x00000003
#define PHONEBUTTONFUNCTION_HOLD             0x00000004
#define PHONEBUTTONFUNCTION_RECALL           0x00000005
#define PHONEBUTTONFUNCTION_DISCONNECT       0x00000006
#define PHONEBUTTONFUNCTION_CONNECT          0x00000007
#define PHONEBUTTONFUNCTION_MSGWAITON        0x00000008
#define PHONEBUTTONFUNCTION_MSGWAITOFF       0x00000009
#define PHONEBUTTONFUNCTION_SELECTRING       0x0000000A
#define PHONEBUTTONFUNCTION_ABBREVDIAL       0x0000000B
#define PHONEBUTTONFUNCTION_FORWARD          0x0000000C
#define PHONEBUTTONFUNCTION_PICKUP           0x0000000D
#define PHONEBUTTONFUNCTION_RINGAGAIN        0x0000000E
#define PHONEBUTTONFUNCTION_PARK             0x0000000F
#define PHONEBUTTONFUNCTION_REJECT           0x00000010
#define PHONEBUTTONFUNCTION_REDIRECT         0x00000011
#define PHONEBUTTONFUNCTION_MUTE             0x00000012
#define PHONEBUTTONFUNCTION_VOLUMEUP         0x00000013
#define PHONEBUTTONFUNCTION_VOLUMEDOWN       0x00000014
#define PHONEBUTTONFUNCTION_SPEAKERON        0x00000015
#define PHONEBUTTONFUNCTION_SPEAKEROFF       0x00000016
#define PHONEBUTTONFUNCTION_FLASH            0x00000017
#define PHONEBUTTONFUNCTION_DATAON           0x00000018
#define PHONEBUTTONFUNCTION_DATAOFF          0x00000019
#define PHONEBUTTONFUNCTION_DONOTDISTURB     0x0000001A
#define PHONEBUTTONFUNCTION_INTERCOM         0x0000001B
#define PHONEBUTTONFUNCTION_BRIDGEDAPP       0x0000001C
#define PHONEBUTTONFUNCTION_BUSY             0x0000001D
#define PHONEBUTTONFUNCTION_CALLAPP          0x0000001E
#define PHONEBUTTONFUNCTION_DATETIME         0x0000001F
#define PHONEBUTTONFUNCTION_DIRECTORY        0x00000020
#define PHONEBUTTONFUNCTION_COVER            0x00000021
#define PHONEBUTTONFUNCTION_CALLID           0x00000022
#define PHONEBUTTONFUNCTION_LASTNUM          0x00000023
#define PHONEBUTTONFUNCTION_NIGHTSRV         0x00000024
#define PHONEBUTTONFUNCTION_SENDCALLS        0x00000025
#define PHONEBUTTONFUNCTION_MSGINDICATOR     0x00000026
#define PHONEBUTTONFUNCTION_REPDIAL          0x00000027
#define PHONEBUTTONFUNCTION_SETREPDIAL       0x00000028
#define PHONEBUTTONFUNCTION_SYSTEMSPEED      0x00000029
#define PHONEBUTTONFUNCTION_STATIONSPEED     0x0000002A
#define PHONEBUTTONFUNCTION_CAMPON           0x0000002B
#define PHONEBUTTONFUNCTION_SAVEREPEAT       0x0000002C
#define PHONEBUTTONFUNCTION_QUEUECALL        0x0000002D
#define PHONEBUTTONFUNCTION_NONE             0x0000002E

typedef struct phonebuttoninfo_tag {
    DWORD    dwTotalSize;
    DWORD    dwNeededSize;
    DWORD    dwUsedSize;

    DWORD    dwButtonMode;
    DWORD    dwButtonFunction;

    DWORD    dwButtonTextSize;
    DWORD    dwButtonTextOffset;

    DWORD    dwDevSpecificSize;
    DWORD    dwDevSpecificOffset;
} PHONEBUTTONINFO, *LPPHONEBUTTONINFO;

#define PHONEBUTTONMODE_DUMMY        0x00000001
#define PHONEBUTTONMODE_CALL         0x00000002
#define PHONEBUTTONMODE_FEATURE      0x00000004
#define PHONEBUTTONMODE_KEYPAD       0x00000008
#define PHONEBUTTONMODE_LOCAL        0x00000010
#define PHONEBUTTONMODE_DISPLAY      0x00000020

#define PHONEBUTTONSTATE_UP          0x00000001
#define PHONEBUTTONSTATE_DOWN        0x00000002

typedef struct phoneextensionid_tag {
    DWORD    dwExtensionID0;
    DWORD    dwExtensionID1;
    DWORD    dwExtensionID2;
    DWORD    dwExtensionID3;
} PHONEEXTENSIONID, *LPPHONEEXTENSIONID;


typedef struct phonecaps_tag {
    DWORD    dwTotalSize;
    DWORD    dwNeededSize;
    DWORD    dwUsedSize;

    DWORD    dwProviderInfoSize;
    DWORD    dwProviderInfoOffset;

    DWORD    dwPhoneInfoSize;
    DWORD    dwPhoneInfoOffset;

    DWORD    dwPermanentPhoneID;
    DWORD    dwPhoneNameSize;
    DWORD    dwPhoneNameOffset;
    DWORD    dwStringFormat;    

    DWORD    dwPhoneStates;
    DWORD    dwHookSwitchDevs;
    DWORD    dwHandsetHookSwitchModes;
    DWORD    dwSpeakerHookSwitchModes;
    DWORD    dwHeadsetHookSwitchModes;

    DWORD    dwVolumeFlags;
    DWORD    dwGainFlags;
    DWORD    dwDisplayNumRows;
    DWORD    dwDisplayNumColumns;
    DWORD    dwNumRingModes;
    DWORD    dwNumButtonLamps;

    DWORD    dwButtonModesSize;
    DWORD    dwButtonModesOffset;

    DWORD    dwButtonFunctionsSize;
    DWORD    dwButtonFunctionsOffset;

    DWORD    dwLampModesSize;
    DWORD    dwLampModesOffset;

    DWORD    dwNumSetData;
    DWORD    dwSetDataSize;
    DWORD    dwSetDataOffset;

    DWORD    dwNumGetData;
    DWORD    dwGetDataSize;
    DWORD    dwGetDataOffset;

    DWORD    dwDevSpecificSize;
    DWORD    dwDevSpecificOffset;

} PHONECAPS, *LPPHONECAPS;

#define PHONEERR_ALLOCATED              0x90000001
#define PHONEERR_BADDEVICEID            0x90000002
#define PHONEERR_INCOMPATIBLEAPIVERSION 0x90000003
#define PHONEERR_INCOMPATIBLEEXTVERSION 0x90000004
#define PHONEERR_INIFILECORRUPT         0x90000005
#define PHONEERR_INUSE                  0x90000006
#define PHONEERR_INVALAPPHANDLE         0x90000007
#define PHONEERR_INVALAPPNAME           0x90000008
#define PHONEERR_INVALBUTTONLAMPID      0x90000009
#define PHONEERR_INVALBUTTONMODE        0x9000000A
#define PHONEERR_INVALBUTTONSTATE       0x9000000B
#define PHONEERR_INVALDATAID            0x9000000C
#define PHONEERR_INVALDEVICECLASS       0x9000000D
#define PHONEERR_INVALEXTVERSION        0x9000000E
#define PHONEERR_INVALHOOKSWITCHDEV     0x9000000F
#define PHONEERR_INVALHOOKSWITCHMODE    0x90000010
#define PHONEERR_INVALLAMPMODE          0x90000011
#define PHONEERR_INVALPARAM             0x90000012
#define PHONEERR_INVALPHONEHANDLE       0x90000013
#define PHONEERR_INVALPHONESTATE        0x90000014
#define PHONEERR_INVALPOINTER           0x90000015
#define PHONEERR_INVALPRIVILEGE         0x90000016
#define PHONEERR_INVALRINGMODE          0x90000017
#define PHONEERR_NODEVICE               0x90000018
#define PHONEERR_NODRIVER               0x90000019
#define PHONEERR_NOMEM                  0x9000001A
#define PHONEERR_NOTOWNER               0x9000001B
#define PHONEERR_OPERATIONFAILED        0x9000001C
#define PHONEERR_OPERATIONUNAVAIL       0x9000001D
#define PHONEERR_RESOURCEUNAVAIL        0x9000001F
#define PHONEERR_REQUESTOVERRUN         0x90000020              
#define PHONEERR_STRUCTURETOOSMALL      0x90000021
#define PHONEERR_UNINITIALIZED          0x90000022
#define PHONEERR_REINIT                 0x90000023

#define PHONEHOOKSWITCHDEV_HANDSET      0x00000001
#define PHONEHOOKSWITCHDEV_SPEAKER      0x00000002
#define PHONEHOOKSWITCHDEV_HEADSET      0x00000004
              
#define PHONEHOOKSWITCHMODE_ONHOOK      0x00000001
#define PHONEHOOKSWITCHMODE_MIC         0x00000002
#define PHONEHOOKSWITCHMODE_SPEAKER     0x00000004
#define PHONEHOOKSWITCHMODE_MICSPEAKER  0x00000008
#define PHONEHOOKSWITCHMODE_UNKNOWN     0x00000010              

#define PHONELAMPMODE_DUMMY              0x00000001
#define PHONELAMPMODE_OFF                0x00000002
#define PHONELAMPMODE_STEADY             0x00000004
#define PHONELAMPMODE_WINK               0x00000008
#define PHONELAMPMODE_FLASH              0x00000010
#define PHONELAMPMODE_FLUTTER            0x00000020
#define PHONELAMPMODE_BROKENFLUTTER      0x00000040
#define PHONELAMPMODE_UNKNOWN            0x00000080


#define PHONEPRIVILEGE_MONITOR        0x00000001
#define PHONEPRIVILEGE_OWNER          0x00000002

#define PHONESTATE_OTHER               0x00000001
#define PHONESTATE_CONNECTED           0x00000002
#define PHONESTATE_DISCONNECTED        0x00000004
#define PHONESTATE_OWNER               0x00000008
#define PHONESTATE_MONITORS            0x00000010
#define PHONESTATE_DISPLAY             0x00000020
#define PHONESTATE_LAMP                0x00000040
#define PHONESTATE_RINGMODE            0x00000080
#define PHONESTATE_RINGVOLUME          0x00000100
#define PHONESTATE_HANDSETHOOKSWITCH   0x00000200
#define PHONESTATE_HANDSETVOLUME       0x00000400
#define PHONESTATE_HANDSETGAIN         0x00000800
#define PHONESTATE_SPEAKERHOOKSWITCH   0x00001000
#define PHONESTATE_SPEAKERVOLUME       0x00002000
#define PHONESTATE_SPEAKERGAIN         0x00004000
#define PHONESTATE_HEADSETHOOKSWITCH   0x00008000
#define PHONESTATE_HEADSETVOLUME       0x00010000
#define PHONESTATE_HEADSETGAIN         0x00020000
#define PHONESTATE_SUSPEND             0x00040000
#define PHONESTATE_RESUME              0x00080000
#define PHONESTATE_DEVSPECIFIC         0x00100000
#define PHONESTATE_REINIT              0x00200000

typedef struct phonestatus_tag {
    DWORD    dwTotalSize;
    DWORD    dwNeededSize;
    DWORD    dwUsedSize;

    DWORD    dwStatusFlags; 
    DWORD    dwNumOwners;
    DWORD    dwNumMonitors;
    DWORD    dwRingMode;
    DWORD    dwRingVolume;

    DWORD    dwHandsetHookSwitchMode;
    DWORD    dwHandsetVolume;
    DWORD    dwHandsetGain;

    DWORD    dwSpeakerHookSwitchMode;
    DWORD    dwSpeakerVolume;
    DWORD    dwSpeakerGain;

    DWORD    dwHeadsetHookSwitchMode;
    DWORD    dwHeadsetVolume;
    DWORD    dwHeadsetGain;

    DWORD    dwDisplaySize;
    DWORD    dwDisplayOffset;

    DWORD    dwLampModesSize;
    DWORD    dwLampModesOffset;

    DWORD    dwOwnerNameSize;
    DWORD    dwOwnerNameOffset;

    DWORD    dwDevSpecificSize;
    DWORD    dwDevSpecificOffset;
} PHONESTATUS, *LPPHONESTATUS;

#define PHONESTATUSFLAGS_CONNECTED    0x00000001
#define PHONESTATUSFLAGS_SUSPENDED    0x00000002

#define STRINGFORMAT_ASCII   0x00000001
#define STRINGFORMAT_DBCS    0x00000002
#define STRINGFORMAT_UNICODE 0x00000003
#define STRINGFORMAT_BINARY  0x00000004

/**
 * This structure is used for returning variably sized strings. It is used both by the line device
 * class and the phone device class.
 *
 * No extensibility.
 *
 * If a string cannot be returned in a variable structure, the dwStringSize and dwStringOffset
 * members are set in one of these ways:
 *
 * dwStringSize and dwStringOffset members are both set to zero.
 *
 * dwStringOffset is nonzero and dwStringSize is zero.
 *
 * dwStringOffset is nonzero, dwStringSize is 1, and the byte at the given offset is zero.
 */
typedef struct varstring_tag {
    /**
     * Specifies the total size, in bytes, allocated to this data structure.
     */
    DWORD    dwTotalSize;
    /**
     * Specifies the size, in bytes, for this data structure that is needed to hold all the returned
     * data.
     */
    DWORD    dwNeededSize;
    /**
     * Specifies the size, in bytes, of the portion of this data structure that contains useful data.
     */
    DWORD    dwUsedSize;

    /**
     * Specifies the format of the string. This member uses the following STRINGFORMAT_ constants: Value
     * Description STRINGFORMAT_ASCII ASCII string format using one byte per character. The actual
     * string is a NULL-terminated ASCII string with the terminating NULL accounted for in the string
     * size. STRINGFORMAT_DBCS DBCS string format using one or two bytes per character.
     * STRINGFORMAT_UNICODE Unicode string format using two bytes per character. STRINGFORMAT_BINARY An
     * array of unsigned characters that could be used for numeric values.
     */
    DWORD    dwStringFormat;
    DWORD    dwStringSize;
    /**
     * Specify the size, in bytes, of the variably sized device field that contains the string data, and
     * the offset, in bytes, from the beginning of this data structure.
     */
    DWORD    dwStringOffset;
} VARSTRING, *LPVARSTRING;

// Data types and values for Lines


#define LINEADDRCAPFLAGS_FWDNUMRINGS        0x00000001
#define LINEADDRCAPFLAGS_PICKUPGROUPID      0x00000002    
#define LINEADDRCAPFLAGS_SECURE             0x00000004
#define LINEADDRCAPFLAGS_BLOCKIDDEFAULT     0x00000008
#define LINEADDRCAPFLAGS_BLOCKIDOVERRIDE    0x00000010
#define LINEADDRCAPFLAGS_DIALED             0x00000020
#define LINEADDRCAPFLAGS_ORIGOFFHOOK        0x00000040
#define LINEADDRCAPFLAGS_DESTOFFHOOK        0x00000080
#define LINEADDRCAPFLAGS_FWDCONSULT         0x00000100
#define LINEADDRCAPFLAGS_SETUPCONFNULL      0x00000200
#define LINEADDRCAPFLAGS_AUTORECONNECT      0x00000400
#define LINEADDRCAPFLAGS_COMPLETIONID       0x00000800
#define LINEADDRCAPFLAGS_TRANSFERHELD       0x00001000
#define LINEADDRCAPFLAGS_TRANSFERMAKE       0x00002000
#define LINEADDRCAPFLAGS_CONFERENCEHELD     0x00004000
#define LINEADDRCAPFLAGS_CONFERENCEMAKE     0x00008000
#define LINEADDRCAPFLAGS_PARTIALDIAL        0x00010000
#define LINEADDRCAPFLAGS_FWDSTATUSVALID     0x00020000
#define LINEADDRCAPFLAGS_FWDINTEXTADDR      0x00040000
#define LINEADDRCAPFLAGS_FWDBUSYNAADDR      0x00080000
#define LINEADDRCAPFLAGS_ACCEPTTOALERT      0x00100000
#define LINEADDRCAPFLAGS_CONFDROP           0x00200000
#define LINEADDRCAPFLAGS_PICKUPCALLWAIT     0x00400000

typedef struct lineaddresscaps_tag {
    DWORD    dwTotalSize;
    DWORD    dwNeededSize;
    DWORD    dwUsedSize;

    DWORD    dwLineDeviceID;

    DWORD    dwAddressSize;
    DWORD    dwAddressOffset;

    DWORD    dwDevSpecificSize;
    DWORD    dwDevSpecificOffset;

    DWORD    dwAddressSharing;
    DWORD    dwAddressStates;
    DWORD    dwCallInfoStates;
    DWORD    dwCallerIDFlags;
    DWORD    dwCalledIDFlags;
    DWORD    dwConnectedIDFlags;
    DWORD    dwRedirectionIDFlags;
    DWORD    dwRedirectingIDFlags;
    DWORD    dwCallStates;
    DWORD    dwDialToneModes;
    DWORD    dwBusyModes;
    DWORD    dwSpecialInfo;
    DWORD    dwDisconnectModes;

    DWORD    dwMaxNumActiveCalls;
    DWORD    dwMaxNumOnHoldCalls;
    DWORD    dwMaxNumOnHoldPendingCalls;
    DWORD    dwMaxNumConference;
    DWORD    dwMaxNumTransConf;

    DWORD    dwAddrCapFlags;
    DWORD    dwCallFeatures;
    DWORD    dwRemoveFromConfCaps;
    DWORD    dwRemoveFromConfState;
    DWORD    dwTransferModes;
    DWORD    dwParkModes;

    DWORD    dwForwardModes;
    DWORD    dwMaxForwardEntries;
    DWORD    dwMaxSpecificEntries;
    DWORD    dwMinFwdNumRings;
    DWORD    dwMaxFwdNumRings;

    DWORD    dwMaxCallCompletions;
    DWORD    dwCallCompletionConds;
    DWORD    dwCallCompletionModes;
    DWORD    dwNumCompletionMessages;
    DWORD    dwCompletionMsgTextEntrySize;
    DWORD    dwCompletionMsgTextSize;
    DWORD    dwCompletionMsgTextOffset;
} LINEADDRESSCAPS, *LPLINEADDRESSCAPS;

#define LINEADDRESSMODE_ADDRESSID        0x00000001
#define LINEADDRESSMODE_DIALABLEADDR     0x00000002


#define LINEADDRESSSHARING_PRIVATE        0x00000001
#define LINEADDRESSSHARING_BRIDGEDEXCL    0x00000002
#define LINEADDRESSSHARING_BRIDGEDNEW     0x00000004
#define LINEADDRESSSHARING_BRIDGEDSHARED  0x00000008
#define LINEADDRESSSHARING_MONITORED      0x00000010

#define LINEADDRESSSTATE_OTHER            0x00000001
#define LINEADDRESSSTATE_DEVSPECIFIC      0x00000002
#define LINEADDRESSSTATE_INUSEZERO        0x00000004
#define LINEADDRESSSTATE_INUSEONE         0x00000008
#define LINEADDRESSSTATE_INUSEMANY        0x00000010
#define LINEADDRESSSTATE_NUMCALLS         0x00000020
#define LINEADDRESSSTATE_FORWARD          0x00000040
#define LINEADDRESSSTATE_TERMINALS        0x00000080

typedef struct lineaddressstatus_tag {
    DWORD    dwTotalSize;
    DWORD    dwNeededSize;
    DWORD    dwUsedSize;

    DWORD    dwNumInUse;
    DWORD    dwNumActiveCalls;
    DWORD    dwNumOnHoldCalls;
    DWORD    dwNumOnHoldPendCalls;
    DWORD    dwAddressFeatures;

    DWORD    dwNumRingsNoAnswer;
    DWORD    dwForwardNumEntries;
    DWORD    dwForwardSize;
    DWORD    dwForwardOffset;

    DWORD    dwTerminalModesSize;
    DWORD    dwTerminalModesOffset;

    DWORD    dwDevSpecificSize;
    DWORD    dwDevSpecificOffset;
} LINEADDRESSSTATUS, *LPLINEADDRESSSTATUS;

#define LINEADDRFEATURE_FORWARD           0x00000001
#define LINEADDRFEATURE_MAKECALL          0x00000002
#define LINEADDRFEATURE_PICKUP            0x00000004
#define LINEADDRFEATURE_SETMEDIACONTROL   0x00000008
#define LINEADDRFEATURE_SETTERMINAL       0x00000010
#define LINEADDRFEATURE_SETUPCONF         0x00000020
#define LINEADDRFEATURE_UNCOMPLETECALL    0x00000040
#define LINEADDRFEATURE_UNPARK            0x00000080


#define LINEANSWERMODE_NONE    0x00000001
#define LINEANSWERMODE_DROP    0x00000002
#define LINEANSWERMODE_HOLD    0x00000004

#define LINEBEARERMODE_VOICE            0x00000001
#define LINEBEARERMODE_SPEECH           0x00000002
#define LINEBEARERMODE_MULTIUSE         0x00000004
#define LINEBEARERMODE_DATA             0x00000008
#define LINEBEARERMODE_ALTSPEECHDATA    0x00000010
#define LINEBEARERMODE_NONCALLSIGNALING 0x00000020
#define LINEBEARERMODE_PASSTHROUGH      0x00000040

#define LINEBUSYMODE_STATION    0x00000001
#define LINEBUSYMODE_TRUNK      0x00000002
#define LINEBUSYMODE_UNKNOWN    0x00000004
#define LINEBUSYMODE_UNAVAIL    0x00000008

#define LINECALLCOMPLCOND_BUSY        0x00000001
#define LINECALLCOMPLCOND_NOANSWER    0x00000002

#define LINECALLCOMPLMODE_CAMPON      0x00000001
#define LINECALLCOMPLMODE_CALLBACK    0x00000002
#define LINECALLCOMPLMODE_INTRUDE     0x00000004
#define LINECALLCOMPLMODE_MESSAGE     0x00000008

#define LINECALLFEATURE_ACCEPT                   0x00000001
#define LINECALLFEATURE_ADDTOCONF                0x00000002
#define LINECALLFEATURE_ANSWER                   0x00000004
#define LINECALLFEATURE_BLINDTRANSFER            0x00000008
#define LINECALLFEATURE_COMPLETECALL             0x00000010
#define LINECALLFEATURE_COMPLETETRANSF           0x00000020
#define LINECALLFEATURE_DIAL                     0x00000040
#define LINECALLFEATURE_DROP                     0x00000080
#define LINECALLFEATURE_GATHERDIGITS             0x00000100
#define LINECALLFEATURE_GENERATEDIGITS           0x00000200
#define LINECALLFEATURE_GENERATETONE             0x00000400
#define LINECALLFEATURE_HOLD                     0x00000800
#define LINECALLFEATURE_MONITORDIGITS            0x00001000
#define LINECALLFEATURE_MONITORMEDIA             0x00002000
#define LINECALLFEATURE_MONITORTONES             0x00004000
#define LINECALLFEATURE_PARK                     0x00008000
#define LINECALLFEATURE_PREPAREADDCONF           0x00010000
#define LINECALLFEATURE_REDIRECT                 0x00020000
#define LINECALLFEATURE_REMOVEFROMCONF           0x00040000
#define LINECALLFEATURE_SECURECALL               0x00080000
#define LINECALLFEATURE_SENDUSERUSER             0x00100000
#define LINECALLFEATURE_SETCALLPARAMS            0x00200000
#define LINECALLFEATURE_SETMEDIACONTROL          0x00400000
#define LINECALLFEATURE_SETTERMINAL              0x00800000
#define LINECALLFEATURE_SETUPCONF                0x01000000
#define LINECALLFEATURE_SETUPTRANSFER            0x02000000
#define LINECALLFEATURE_SWAPHOLD                 0x04000000
#define LINECALLFEATURE_UNHOLD                   0x08000000

typedef struct linedialparams_tag {
    DWORD    dwDialPause;
    DWORD    dwDialSpeed;
    DWORD    dwDigitDuration;
    DWORD    dwWaitForDialtone;
} LINEDIALPARAMS, *LPLINEDIALPARAMS;

/**
 * This structure contains call data. This data remains fixed during the call and is obtained with
 * the lineGetCallInfo function. If a part of the structure does change, then a LINE_CALLINFO
 * message is sent to the application indicating which data item has changed. Dynamically changing
 * call data, such as call progress status, is available in the LINECALLSTATUS structure, returned
 * with the lineGetCallStatus function.
 *
 * Device-specific extensions should use the DevSpecific (dwDevSpecificSize and dwDevSpecificOffset)
 * variably sized area of this data structure.
 *
 * The LINECALLINFO data structure contains relatively fixed data about a call. This structure is
 * returned with lineGetCallInfo. When data items in this data structure have changed, a
 * LINE_CALLINFO message is sent to the application. A parameter to this message is the data item or
 * field that changed.
 *
 * The members dwCallTreatment through dwReceivingFlowspecOffset are available only to applications
 * that open the line device with an API version of 2.0 or later.
 *
 * Note The preferred format for specification of the contents of the dwCallID member and the other
 * five similar members (dwCallerIDFlag, dwCallerIDSize, dwCallerIDOffset, dwCallerIDNameSize, and
 * dwCallerIDNameOffset) is the TAPI canonical number format. For example, a ICLID of "4258828080"
 * received from the switch should be converted to "+1 (425) 8828080" before being placed in the
 * LINECALLINFO structure. This standardized format facilitates searching of databases and callback
 * functions implemented in applications.
 */
typedef struct linecallinfo_tag {
    /**
     * Specifies the total size, in bytes, allocated to this data structure.
     */
    DWORD    dwTotalSize;
    /**
     * Specifies the size, in bytes, for this data structure needed to contain all the returned data.
     */
    DWORD    dwNeededSize;
    /**
     * Specifies the size, in bytes, of the portion of this data structure that contains useful data.
     */
    DWORD    dwUsedSize;

    /**
     * Handle for the line device with which this call is associated.
     */
    HLINE    hLine;
    /**
     * Specifies the device identifier of the line device with which this call is associated.
     */
    DWORD    dwLineDeviceID;
    /**
     * Specifies the address identifier of the address on the line on which this call exists.
     */
    DWORD    dwAddressID;

    /**
     * Specifies the current bearer mode of the call. It uses the following LINEBEARERMODE_ constants:
     * Value Description LINEBEARERMODE_VOICE A regular 3.1 kHz analog voice grade bearer service. Bit
     * integrity is not assured. Voice can support fax and modem media modes. LINEBEARERMODE_SPEECH
     * Corresponds to the G.711 codec speech transmission on the call. The network can use processing
     * techniques such as analog transmission, echo cancellation, and compression/decompression. Bit
     * integrity is not assured. Speech is not intended to support fax and modem media modes.
     * LINEBEARERMODE_MULTIUSE The multiuse mode, defined by ISDN. LINEBEARERMODE_DATA The unrestricted
     * data transfer on the call. The data rate is specified separately. LINEBEARERMODE_ALTSPEECHDATA
     * The alternate transfer of speech or unrestricted data on the same call; ISDN.
     * LINEBEARERMODE_NONCALLSIGNALING A non-call-associated signaling connection from the application
     * to the service provider or switch; treated as a media stream by TAPI. LINEBEARERMODE_PASSTHROUGH
     * When a call is active in LINEBEARERMODE_PASSTHROUGH, the service provider gives direct access to
     * the attached hardware for control by the application. This mode is used primarily by applications
     * desiring temporary direct control over asynchronous modems, accessed through the Win32
     * communication functions, for the purpose of configuring or using special features not otherwise
     * supported by the service provider.
     */
    DWORD    dwBearerMode;
    /**
     * Specifies the rate of the call data stream, in bits per second (bps).
     */
    DWORD    dwRate;
    /**
     * Specifies the media mode of the data stream currently on the call. This is the media mode
     * determined by the owner of the call, which is not necessarily the same as that of the last
     * LINE_MONITORMEDIA message. This member is not directly affected by the LINE_MONITORMEDIA
     * messages. It uses the following LINEMEDIAMODE_ constants: Value Description LINEMEDIAMODE_UNKNOWN
     * A media stream exists, but its mode is not known. This corresponds to a call with an unclassified
     * media type. In typical analog telephony environments, an incoming call's media mode may be
     * unknown until after the call has been answered and the media stream has been filtered to make a
     * determination. LINEMEDIAMODE_INTERACTIVEVOICE Speech is detected on the call and the call is
     * treated as an interactive call with a humans at each end. LINEMEDIAMODE_AUTOMATEDVOICE Speech is
     * detected on the call and is handled locally by an application. LINEMEDIAMODE_DATAMODEM A data
     * modem session is detected on the call. LINEMEDIAMODE_G3FAX A group 3 fax is being sent or
     * received on the call. LINEMEDIAMODE_G4FAX A group 4 fax is being sent or received on the call.
     * LINEMEDIAMODE_TDD A TDD (Telecommunications device for the deaf) session on the call.
     * LINEMEDIAMODE_DIGITALDATA Digital data being sent or received on the call. LINEMEDIAMODE_TELETEX
     * A teletext session on the call. Teletext is one of the telematic services. LINEMEDIAMODE_VIDEOTEX
     * A videotext session on the call. Videotext is one of the telematic services. LINEMEDIAMODE_TELEX
     * A telex session on the call. Telex is one of the telematic services. LINEMEDIAMODE_MIXED A mixed
     * session on the call. Mixed is one of the ISDN telematic services. LINEMEDIAMODE_ADSI An ADSI
     * (Analog Display Services Interface) session on the call. LINEMEDIAMODE_VOICEVIEW The media mode
     * of the call is VoiceView.
     */
    DWORD    dwMediaMode;

    /**
     * Uninterpreted by the API implementation and service provider. It can be set by any owner
     * application of this call with the lineSetAppSpecific function.
     */
    DWORD    dwAppSpecific;
    /**
     * In some telephony environments, the switch, or service provider can assign a unique identifier to
     * each call. This enables the call to be tracked across transfers, forwards, or other events. The
     * domain of these call identifiers and their scope is service provider-defined. The dwCallID member
     * makes this unique identifier available to the applications.
     */
    DWORD    dwCallID;
    /**
     * Telephony environments that use the call identifier often may find it necessary to relate one
     * call to another. The dwRelatedCallID member can be used by the service provider for this purpose.
     */
    DWORD    dwRelatedCallID;
    /**
     * Specifies a collection of call-related parameters when the call is outgoing. These are the same
     * call parameters specified in lineMakeCall, of type LINECALLPARAMFLAGS_. It is one of the
     * following values: Value Description LINECALLPARAMFLAGS_SECURE The call is currently secure. This
     * flag is also updated if the call is later secured with the lineSecureCall function.
     * LINECALLPARAMFLAGS_IDLE The call started out using an idle call. LINECALLPARAMFLAGS_BLOCKID The
     * originator identity was concealed (block caller IDpresentation to the remote party).
     * LINECALLPARAMFLAGS_ORIGOFFHOOK The originator's phone was automatically disconnected.
     * LINECALLPARAMFLAGS_DESTOFFHOOK The called party's phone was automatically disconnected.
     */
    DWORD    dwCallParamFlags;
    /**
     * Specifies the call states of type LINECALLSTATE_ for which the application can be notified on
     * this call. The dwCallStates member is constant in LINECALLINFO and does not change depending on
     * the call state. It is one of the following values: Value Description LINECALLSTATE_IDLE The call
     * is idle-no call exists. LINECALLSTATE_OFFERING The call is offered to the station signaling the
     * arrival of a new call. In some environments, a call in the offering state does not automatically
     * alert the user; the alert is handled by the switch instructing the line to ring. It does not
     * affect any call states. LINECALLSTATE_ACCEPTED The call was offered and accepted. This indicates
     * to monitoring applications that the current owner application has claimed responsibility for
     * answering the call. In ISDN, this also initiates alerting to both parties. LINECALLSTATE_DIALTONE
     * The call is receiving a dial tone from the switch, which means that the switch is ready to
     * receive a dialed number. LINECALLSTATE_DIALING Destination address data, a phone number, is being
     * sent to the switch on the call. The lineGenerateDigits function does not place the line into the
     * dialing state. LINECALLSTATE_RINGBACK The call is receiving a ringback from the called address.
     * Ringback indicates that the other station has been reached and is being alerted.
     * LINECALLSTATE_BUSY The call is receiving a busy signal. A busy signal indicates that the call
     * cannot be completed-either a circuit (trunk) or the remote party station are in use.
     * LINECALLSTATE_SPECIALINFO Special data is sent by the network. Special data is typically sent
     * when the destination cannot be reached. LINECALLSTATE_CONNECTED The call has been established,
     * the connection is made. Data is able to flow on the call between the originating address and the
     * destination address. LINECALLSTATE_PROCEEDING Dialing has completed and the call is proceeding
     * through the switch or telephone network. LINECALLSTATE_ONHOLD The call is on hold by the switch.
     * LINECALLSTATE_CONFERENCED The call is currently a member of a multiparty conference call.
     * LINECALLSTATE_ONHOLDPENDCONF The call is currently on hold while being added to a conference.
     * LINECALLSTATE_ONHOLDPENDTRANSF The call is currently on hold waiting transfer to another number.
     * LINECALLSTATE_DISCONNECTED The remote party has disconnected from the call. LINECALLSTATE_UNKNOWN
     * The call state is not known. This may be due to limitations of the call progress detection
     * implementation.
     */
    DWORD    dwCallStates;

    /**
     * Specifies the various digit modes of type LINEDIGITMODE_ for which monitoring is currently
     * enabled. It is one of the following values: Value Description LINEDIGITMODE_PULSE Uses pulse or
     * rotary for digit signaling. LINEDIGITMODE_DTMF Uses DTMF tones for digit signaling.
     * LINEDIGITMODE_DTMFEND Uses DTMF tones for digit detection, and also detects the down edges.
     */
    DWORD    dwMonitorDigitModes;
    /**
     * Specifies the various media modes for which monitoring is currently enabled, of type
     * LINEMEDIAMODE_. It is one of the following values: Value Description
     * LINEMEDIAMODE_INTERACTIVEVOICE The presence of speech on the call and the call is treated as an
     * interactive call with a human on both ends. LINEMEDIAMODE_AUTOMATEDVOICE The presence of speech
     * on the call and the voice is locally handled by an automated application. LINEMEDIAMODE_DATAMODEM
     * A data modem session on the call. LINEMEDIAMODE_G3FAX A group 3 fax is being sent or received on
     * the call. LINEMEDIAMODE_G4FAX A group 4 fax is being sent or received on the call.
     * LINEMEDIAMODE_TDD A TDD (Telecommunications device for the deaf) session on the call.
     * LINEMEDIAMODE_DIGITALDATA Digital data is being sent or received on the call.
     * LINEMEDIAMODE_TELETEX A teletext session on the call. Teletext is one of the telematic services.
     * LINEMEDIAMODE_VIDEOTEX A videotext session on the call. Videotext is one of the telematic
     * services. LINEMEDIAMODE_TELEX A telex session on the call. Telex is one of the telematic
     * services. LINEMEDIAMODE_MIXED A mixed session on the call. Mixed is one of the ISDN telematic
     * services. LINEMEDIAMODE_ADSI An ADSI (Analog Display Services Interface) session on the call.
     * LINEMEDIAMODE_VOICEVIEW The media mode of the call is VoiceView.
     */
    DWORD    dwMonitorMediaModes;
    /**
     * The dialing parameters currently in effect on the call, of type LINEDIALPARAMS. Unless these
     * parameters are set by either lineMakeCall or lineSetCallParams, their values are the same as the
     * defaults used in the LINEDEVCAPS structure.
     */
    LINEDIALPARAMS    DialParams;

    /**
     * Identifies where the call originated from. It uses the following LINECALLORIGIN_ constants: Value
     * Description LINECALLORIGIN_OUTBOUND The call is outgoing. LINECALLORIGIN_INTERNAL The call is
     * incoming and originated internally. LINECALLORIGIN_EXTERNAL The call is incoming and originated
     * externally. LINECALLORIGIN_UNKNOWN The call is an incoming call and its origin is currently
     * unknown, but may be identified later. LINECALLORIGIN_UNAVAIL The call is an incoming call. Its
     * origin is not available and will never be identified. LINECALLORIGIN_CONFERENCE The call handle
     * is for a conference call, that is, the application's connection to the conference bridge in the
     * switch.
     */
    DWORD    dwOrigin;
    /**
     * Specifies the reason why the call occurred. It uses the following LINECALLREASON_ constants:
     * Value Description LINECALLREASON_DIRECT The call is a direct call. LINECALLREASON_FWDBUSY The
     * call was forwarded from another extension that was busy at the time of the call.
     * LINECALLREASON_FWDNOANSWER The call was forwarded from another extension that did not answer the
     * call after some number of rings. LINECALLREASON_FWDUNCOND The call was forwarded unconditionally
     * from another number. LINECALLREASON_PICKUP The call was picked up from another extension.
     * LINECALLREASON_UNPARK The call was retrieved as a parked call. LINECALLREASON_REDIRECT The call
     * was redirected to this station. LINECALLREASON_CALLCOMPLETION The call was the result of a call
     * completion request. LINECALLREASON_TRANSFER The call has been transferred from another number.
     * Party identifier data may identify the caller and where the call was transferred from.
     * LINECALLREASON_REMINDER The call is a reminder that the user has a call parked or on hold for a
     * potentially long time. LINECALLREASON_UNKNOWN The reason for the call is currently unknown, but
     * may be identified later. LINECALLREASON_UNAVAIL The reason for the call is unavailable and cannot
     * be identified later.
     */
    DWORD    dwReason;
    /**
     * Specifies the completion identifier for the incoming call if it is the result of a completion
     * request that terminates. This identifier is meaningful only if dwReason is
     * LINECALLREASON_CALLCOMPLETION.
     */
    DWORD    dwCompletionID;
    /**
     * Specifies the number of application modules with different call handles with owner privilege for
     * the call.
     */
    DWORD    dwNumOwners;
    /**
     * Specifies the number of application modules with different call handles with monitor privilege
     * for the call.
     */
    DWORD    dwNumMonitors;

    /**
     * Specifies the country code of the destination party. Zero if unknown.
     */
    DWORD    dwCountryCode;
    /**
     * Specifies the number of the trunk over which the call is routed. This member is used for both
     * incoming and outgoing calls. The dwTrunk member should be set to 0xFFFFFFFF if it is unknown.
     */
    DWORD    dwTrunk;

    /**
     * Determines the validity and content of the caller party identifier data. The caller is the
     * originator of the call. It uses the following LINECALLPARTYID_* constants: Value Description
     * LINECALLPARTYID_BLOCKED Caller identifier data for the call has been blocked by the caller, but
     * would otherwise have been available. LINECALLPARTYID_OUTOFAREA Caller identifier data for the
     * call is not available because it is not propagated completely by the network.
     * LINECALLPARTYID_NAME The caller identifier data for the call is the caller's name taken from a
     * table maintained inside the switch. It is provided in the caller identifier name field.
     * LINECALLPARTYID_ADDRESS The caller identifier data for the call is the caller's number and is
     * provided in the caller identifier field. LINECALLPARTYID_PARTIAL Caller identifier data for the
     * call is valid, but is limited to partial number data. LINECALLPARTYID_UNKNOWN Caller identifier
     * data is currently unknown, but it may be identified later. LINECALLPARTYID_UNAVAIL Caller
     * identifier data is unavailable and cannot be identified later.
     */
    DWORD    dwCallerIDFlags;
    DWORD    dwCallerIDSize;
    DWORD    dwCallerIDOffset;
    DWORD    dwCallerIDNameSize;
    DWORD    dwCallerIDNameOffset;

    /**
     * Determines the validity and content of the called-party identifier data. The called party
     * corresponds to the originally addressed party. It uses the following LINECALLPARTYID_ constants:
     * Value Description LINECALLPARTYID_BLOCKED Called identifier data for the call has been blocked by
     * the caller, but would otherwise have been available. LINECALLPARTYID_OUTOFAREA Caller identifier
     * data for the call is not available because it is not propagated all the way by the network.
     * LINECALLPARTYID_NAME The called identifier data for the call is the caller's name (from a table
     * maintained inside the switch). It is provided in the called identifier name field.
     * LINECALLPARTYID_ADDRESS The called identifier data for the call is the caller's number and is
     * provided in the called identifier field. LINECALLPARTYID_PARTIAL Called identifier data for the
     * call is valid, but is limited to partial number data. LINECALLPARTYID_UNKNOWN Called identifier
     * data is currently unknown, but it may be identified later. LINECALLPARTYID_UNAVAIL Called
     * identifier data is unavailable and cannot be identified later.
     */
    DWORD    dwCalledIDFlags;
    DWORD    dwCalledIDSize;
    /**
     * Specify the size, in bytes, of the field that contains the called-party identifier number data,
     * and the offset, in bytes, from the beginning of this data structure.
     */
    DWORD    dwCalledIDOffset;
    DWORD    dwCalledIDNameSize;
    /**
     * Specify the size, in bytes, of the field that contains the called-party identifier name data, and
     * the offset, in bytes, from the beginning of this data structure.
     */
    DWORD    dwCalledIDNameOffset;

    /**
     * Determines the validity and content of the connected party identifier data. The connected party
     * is the party that was actually connected to. This may be different from the called-party
     * identifier if the call was diverted. It uses the following LINECALLPARTYID_ constants: Value
     * Description LINECALLPARTYID_BLOCKED Connected party identifier data for the call has been blocked
     * by the caller, but would otherwise have been available. LINECALLPARTYID_OUTOFAREA Connected
     * identifier data for the call is not available as it is not propagated all the way by the network.
     * LINECALLPARTYID_NAME The connected party identifier data for the call is the caller's name (from
     * a table maintained inside the switch). It is provided in the connected identifier name field.
     * LINECALLPARTYID_ADDRESS The connected party identifier data for the call is the caller's number
     * and is provided in the connected identifier field. LINECALLPARTYID_PARTIAL Connected party
     * identifier data for the call is valid, but is limited to partial number data.
     * LINECALLPARTYID_UNKNOWN Connected party identifier data is currently unknown, but it may be
     * identified later. LINECALLPARTYID_UNAVAIL Connected party identifier data is unavailable and
     * cannot be identified later.
     */
    DWORD    dwConnectedIDFlags;
    DWORD    dwConnectedIDSize;
    DWORD    dwConnectedIDOffset;
    DWORD    dwConnectedIDNameSize;
    DWORD    dwConnectedIDNameOffset;

    /**
     * Determines the validity and content of the redirection party identifier data. The redirection
     * party identifies to the calling user the number toward which diversion was invoked. It uses the
     * following LINECALLPARTYID_ constants: Value Description LINECALLPARTYID_BLOCKED Redirection party
     * identifier data for the call has been blocked by the caller, but would otherwise have been
     * available. LINECALLPARTYID_OUTOFAREA Redirection identifier data for the call is not available
     * because it is not propagated all the along the network. LINECALLPARTYID_NAME The redirection
     * party identifier data for the call is the caller's name (from a table maintained inside the
     * switch). It is provided in the redirection identifier name field. LINECALLPARTYID_ADDRESS The
     * redirection party identifier data for the call is the caller's number and is provided in the
     * redirection identifier field. LINECALLPARTYID_PARTIAL Redirection party identifier data for the
     * call is valid, but is limited to partial number data. LINECALLPARTYID_UNKNOWN Redirection
     * identifier data is currently unknown, but it may be identified later. LINECALLPARTYID_UNAVAIL
     * Redirection identifier data is unavailable and cannot be identified later.
     */
    DWORD    dwRedirectionIDFlags;
    DWORD    dwRedirectionIDSize;
    DWORD    dwRedirectionIDOffset;
    DWORD    dwRedirectionIDNameSize;
    DWORD    dwRedirectionIDNameOffset;

    /**
     * Determines the validity and content of the redirecting party identifier data. The party that
     * received the call identifies the new destination number or whatever data is detected to the call
     * originator. It uses the following LINECALLPARTYID_* constants: Value Description
     * LINECALLPARTYID_BLOCKED Redirecting party identifier data for the call has been blocked by the
     * caller, but would otherwise have been available. LINECALLPARTYID_OUTOFAREA Redirecting identifier
     * data for the call is not available because it is not propagated all the way by the network.
     * LINECALLPARTYID_NAME The redirecting party identifier data for the call is the caller's name
     * (from a table maintained inside the switch). It is provided in the redirecting identifier name
     * field. LINECALLPARTYID_ADDRESS The redirecting party identifier data for the call is the caller's
     * number and is provided in the redirecting identifier field. LINECALLPARTYID_PARTIAL Redirecting
     * party identifier data for the call is valid, but is limited to partial number data.
     * LINECALLPARTYID_UNKNOWN Redirecting identifier data is currently unknown, but it may be
     * identified later. LINECALLPARTYID_UNAVAIL Redirecting identifier data is unavailable and cannot
     * be identified later.
     */
    DWORD    dwRedirectingIDFlags;
    DWORD    dwRedirectingIDSize;
    DWORD    dwRedirectingIDOffset;
    DWORD    dwRedirectingIDNameSize;
    DWORD    dwRedirectingIDNameOffset;

    DWORD    dwAppNameSize;
    DWORD    dwAppNameOffset;

    DWORD    dwDisplayableAddressSize;
    DWORD    dwDisplayableAddressOffset;

    DWORD    dwCalledPartySize;
    DWORD    dwCalledPartyOffset;

    DWORD    dwCommentSize;
    DWORD    dwCommentOffset;

    DWORD    dwDisplaySize;
    DWORD    dwDisplayOffset;

    DWORD    dwUserUserInfoSize;
    DWORD    dwUserUserInfoOffset;

    DWORD    dwHighLevelCompSize;
    DWORD    dwHighLevelCompOffset;

    DWORD    dwLowLevelCompSize;
    DWORD    dwLowLevelCompOffset;

    DWORD    dwChargingInfoSize;
    DWORD    dwChargingInfoOffset;

    DWORD    dwTerminalModesSize;
    DWORD    dwTerminalModesOffset;

    DWORD    dwDevSpecificSize;
    DWORD    dwDevSpecificOffset;
} LINECALLINFO, *LPLINECALLINFO;

#define LINECALLINFOSTATE_OTHER             0x00000001
#define LINECALLINFOSTATE_DEVSPECIFIC       0x00000002
#define LINECALLINFOSTATE_BEARERMODE        0x00000004
#define LINECALLINFOSTATE_RATE              0x00000008
#define LINECALLINFOSTATE_MEDIAMODE         0x00000010
#define LINECALLINFOSTATE_APPSPECIFIC       0x00000020
#define LINECALLINFOSTATE_CALLID            0x00000040
#define LINECALLINFOSTATE_RELATEDCALLID     0x00000080
#define LINECALLINFOSTATE_ORIGIN            0x00000100
#define LINECALLINFOSTATE_REASON            0x00000200
#define LINECALLINFOSTATE_COMPLETIONID      0x00000400
#define LINECALLINFOSTATE_NUMOWNERINCR      0x00000800
#define LINECALLINFOSTATE_NUMOWNERDECR      0x00001000
#define LINECALLINFOSTATE_NUMMONITORS       0x00002000
#define LINECALLINFOSTATE_TRUNK             0x00004000
#define LINECALLINFOSTATE_CALLERID          0x00008000
#define LINECALLINFOSTATE_CALLEDID          0x00010000
#define LINECALLINFOSTATE_CONNECTEDID       0x00020000
#define LINECALLINFOSTATE_REDIRECTIONID     0x00040000
#define LINECALLINFOSTATE_REDIRECTINGID     0x00080000
#define LINECALLINFOSTATE_DISPLAY           0x00100000
#define LINECALLINFOSTATE_USERUSERINFO      0x00200000
#define LINECALLINFOSTATE_HIGHLEVELCOMP     0x00400000
#define LINECALLINFOSTATE_LOWLEVELCOMP      0x00800000
#define LINECALLINFOSTATE_CHARGINGINFO      0x01000000
#define LINECALLINFOSTATE_TERMINAL          0x02000000
#define LINECALLINFOSTATE_DIALPARAMS        0x04000000
#define LINECALLINFOSTATE_MONITORMODES      0x08000000

typedef struct linecalllist_tag {
    DWORD    dwTotalSize;
    DWORD    dwNeededSize;
    DWORD    dwUsedSize;
    
    DWORD    dwCallsNumEntries;
    DWORD    dwCallsSize;
    DWORD    dwCallsOffset;
} LINECALLLIST, *LPLINECALLLIST;

#define LINECALLORIGIN_OUTBOUND    0x00000001
#define LINECALLORIGIN_INTERNAL    0x00000002
#define LINECALLORIGIN_EXTERNAL    0x00000004
#define LINECALLORIGIN_UNKNOWN     0x00000010
#define LINECALLORIGIN_UNAVAIL     0x00000020
#define LINECALLORIGIN_CONFERENCE  0x00000040

#define LINECALLPARAMFLAGS_SECURE           0x00000001
#define LINECALLPARAMFLAGS_IDLE             0x00000002
#define LINECALLPARAMFLAGS_BLOCKID          0x00000004
#define LINECALLPARAMFLAGS_ORIGOFFHOOK      0x00000008
#define LINECALLPARAMFLAGS_DESTOFFHOOK      0x00000010

/**
 * This structure describes parameters supplied when making calls using the lineMakeCall function.
 * The LINECALLPARAMS structure is also used as a parameter in other operations.
 *
 * Device-specific extensions should use the dwDevSpecificSize and dwDevSpecificOffset members of
 * this structure.
 *
 * This structure is used as a parameter to lineMakeCall when setting up a call. Its fields enable
 * the application to specify the quality of service requested from the network as well as a variety
 * of ISDN call-setup parameters. If no LINECALLPARAMS structure is supplied to lineMakeCall, a
 * default POTS voice-grade call is requested with the default values listed above.
 *
 * Note The members dwOrigAddressSize through dwDevSpecificOffset are ignored when an lpCallParams
 * parameter is specified with the lineOpen function.
 *
 * For Windows CE versions 1.0 through 2.12, the following members are not supported:
 *
 * dwUUISendUserUserInfoSize dwDeviceClassSize dwMinRate dwDeviceClassOffset dwMaxRate
 * dwDeviceConfigSize dwPredictiveAutoTransferStates dwDeviceConfigOffset dwTargetAddressSize
 * dwCallDataSize dwTargetAddressOffset dwCallDataOffset dwSendingFlowspecSize dwNoAnswerTimeout
 * dwSendingFlowspecOffset dwCallingPartyIDSize dwReceivingFlowspecSize dwCallingPartyIDOffset
 * dwReceivingFlowspecOffset
 */
typedef struct linecallparams_tag {     // Defaults:
    /**
     * Specifies the total size, in bytes, allocated to this data structure. This size should be big
     * enough to hold all the fixed and variably sized portions of this data structure.
     */
    DWORD    dwTotalSize;               // ---------
    
    /**
     * Specifies the bearer mode for the call. If dwBearerMode is set to any value except
     * LINEBEARERMODE_PASSTHROUGH, the call will attempt to complete if or not that bearer mode is
     * supported on the line being accessed. This member uses the following LINEBEARERMODE_ constants:
     * Value Description LINEBEARERMODE_VOICE This is a regular 3.1 kHz analog voice grade bearer
     * service. Bit integrity is not assured. Voice can support fax and modem media modes.
     * LINEBEARERMODE_SPEECH Corresponds to G.711 speech transmission on the call. The network can use
     * processing techniques such as analog transmission, echo cancellation, and
     * compression/decompression. Bit integrity is not assured. Speech is not intended to support fax
     * and modem media modes. LINEBEARERMODE_MULTIUSE The multiuse mode defined by ISDN.
     * LINEBEARERMODE_DATA The unrestricted data transfer on the call. The data rate is specified
     * separately. LINEBEARERMODE_ALTSPEECHDATA The alternate transfer of speech or unrestricted data on
     * the same call (ISDN). LINEBEARERMODE_NONCALLSIGNALING Corresponds to a non-call-associated
     * signaling connection from the application to the service provider or switch (treated as a "media
     * stream" by the Telephony API). LINEBEARERMODE_PASSTHROUGH When a call is active in
     * LINEBEARERMODE_PASSTHROUGH, the service provider gives direct access to the attached hardware for
     * control by the application. This mode is used primarily by applications desiring temporary direct
     * control over asynchronous modems, accessed through the Win32 comm functions, for the purpose of
     * configuring or using special features not otherwise supported by the service provider.
     *
     * If dwBearerMode is zero, the default value is LINEBEARERMODE_VOICE.
     */
    DWORD    dwBearerMode;              // voice
    DWORD    dwMinRate;                 // (3.1kHz)
    DWORD    dwMaxRate;                 // (3.1kHz)
    /**
     * Specifies the expected media mode of the call. This member uses the following LINEMEDIAMODE_
     * constants: Value Description LINEMEDIAMODE_UNKNOWN A media stream exists, but its mode is not
     * known. This would correspond to a call with an unclassified media type. In typical analog
     * telephony environments, an incoming call's media mode may be unknown until after the call has
     * been answered and the media stream has been filtered to make a determination.
     * LINEMEDIAMODE_INTERACTIVEVOICE The presence of speech on the call and the call is treated as an
     * interactive call with humans on both ends. LINEMEDIAMODE_AUTOMATEDVOICE The presence of speech on
     * the call and the voice is locally handled by an automated application. LINEMEDIAMODE_DATAMODEM A
     * datamodem session on the call. LINEMEDIAMODE_G3FAX A group 3 fax is being sent or received on the
     * call. LINEMEDIAMODE_G4FAX A group 4 fax is being sent or received on the call. LINEMEDIAMODE_TDD
     * A TDD (Telephony Devices for the Deaf) session on the call. LINEMEDIAMODE_DIGITALDATA Digital
     * data is being sent or received on the call. LINEMEDIAMODE_TELETEX A teletex session on the call.
     * Teletex is one of the telematic services. LINEMEDIAMODE_VIDEOTEX A videotex session on the call.
     * Videotex is one of the telematic services. LINEMEDIAMODE_TELEX A telex session on the call. Telex
     * is one of the telematic services. LINEMEDIAMODE_MIXED A mixed session on the call. Mixed is one
     * of the ISDN telematic services. LINEMEDIAMODE_ADSI An ADSI (Analog Display Services Interface)
     * session on the call. LINEMEDIAMODE_VOICEVIEW The media mode of the call is VoiceView.
     *
     * If dwMediaMode is zero, the default value is LINEMEDIAMODE_INTERACTIVEVOICE.
     */
    DWORD    dwMediaMode;               // interactiveVoice

    /**
     * Specifies a collection of Boolean call-setup parameters. This member uses the following
     * LINECALLPARAMFLAGS_ constants: Value Description LINECALLPARAMFLAGS_SECURE The call should be set
     * up as secure. LINECALLPARAMFLAGS_IDLE The call should get an idle call appearance.
     * LINECALLPARAMFLAGS_BLOCKID The originator identity should be concealed (block caller identifier).
     * LINECALLPARAMFLAGS_ORIGOFFHOOK The originator's phone should be automatically taken offhook.
     * LINECALLPARAMFLAGS_DESTOFFHOOK The called party's phone should be automatically taken offhook.
     */
    DWORD    dwCallParamFlags;          // 0
    /**
     * Specifies the mode by which the originating address is specified. The dwAddressMode member cannot
     * be LINEADDRESSMODE_ADDRESSID for the lineOpen function call. This member uses the following
     * LINEADDRESSMODE_ constants: Value Description LINEADDRESSMODE_ADDRESSID The address is specified
     * with a small integer in the range zero to dwNumAddresses minus one, where dwNumAddresses is the
     * value in the line's LINEDEVCAPS structure. The selected address is specified in the dwAddressID
     * member. LINEADDRESSMODE_DIALABLEADDR The address is specified with its dialable address. The
     * address is contained in the dwOrigAddressSize and dwOrigAddressOffset field. If dwAddressMode is
     * zero, the default value is LINEADDRESSMODE_ADDRESSID.
     */
    DWORD    dwAddressMode;             // addressID
    /**
     * Specifies the address identifier of the originating address if dwAddressMode is set to
     * LINEADDRESSMODE_ADDRESSID.
     */
    DWORD    dwAddressID;               // (any available)

    /**
     * Unsupported; set to zero.
     */
    LINEDIALPARAMS  DialParams;         // (0, 0, 0, 0)
    
    DWORD    dwOrigAddressSize;         // 0
    DWORD    dwOrigAddressOffset;
    DWORD    dwDisplayableAddressSize;
    DWORD    dwDisplayableAddressOffset;

    DWORD    dwCalledPartySize;         // 0
    DWORD    dwCalledPartyOffset;

    DWORD    dwCommentSize;             // 0
    DWORD    dwCommentOffset;

    DWORD    dwUserUserInfoSize;        // 0
    DWORD    dwUserUserInfoOffset;

    DWORD    dwHighLevelCompSize;       // 0
    DWORD    dwHighLevelCompOffset;

    DWORD    dwLowLevelCompSize;        // 0
    DWORD    dwLowLevelCompOffset;

    DWORD    dwDevSpecificSize;         // 0
    DWORD    dwDevSpecificOffset;
} LINECALLPARAMS, *LPLINECALLPARAMS;


#define LINECALLPARTYID_BLOCKED         0x00000001
#define LINECALLPARTYID_OUTOFAREA       0x00000002
#define LINECALLPARTYID_NAME            0x00000004
#define LINECALLPARTYID_ADDRESS         0x00000008
#define LINECALLPARTYID_PARTIAL         0x00000010
#define LINECALLPARTYID_UNKNOWN         0x00000020
#define LINECALLPARTYID_UNAVAIL         0x00000040

#define LINECALLPRIVILEGE_NONE          0x00000001
#define LINECALLPRIVILEGE_MONITOR       0x00000002
#define LINECALLPRIVILEGE_OWNER         0x00000004

#define LINECALLREASON_DIRECT           0x00000001
#define LINECALLREASON_FWDBUSY          0x00000002
#define LINECALLREASON_FWDNOANSWER      0x00000004
#define LINECALLREASON_FWDUNCOND        0x00000008
#define LINECALLREASON_PICKUP           0x00000010
#define LINECALLREASON_UNPARK           0x00000020
#define LINECALLREASON_REDIRECT         0x00000040
#define LINECALLREASON_CALLCOMPLETION   0x00000080
#define LINECALLREASON_TRANSFER         0x00000100
#define LINECALLREASON_REMINDER         0x00000200
#define LINECALLREASON_UNKNOWN          0x00000400
#define LINECALLREASON_UNAVAIL          0x00000800
#define LINECALLREASON_INTRUDE          0x00001000
#define LINECALLREASON_PARKED           0x00002000

#define LINECALLSELECT_LINE     0x00000001
#define LINECALLSELECT_ADDRESS  0x00000002
#define LINECALLSELECT_CALL     0x00000004

#define LINECALLSTATE_IDLE                  0x00000001
#define LINECALLSTATE_OFFERING              0x00000002
#define LINECALLSTATE_ACCEPTED              0x00000004
#define LINECALLSTATE_DIALTONE              0x00000008
#define LINECALLSTATE_DIALING               0x00000010
#define LINECALLSTATE_RINGBACK              0x00000020
#define LINECALLSTATE_BUSY                  0x00000040
#define LINECALLSTATE_SPECIALINFO           0x00000080
#define LINECALLSTATE_CONNECTED             0x00000100
#define LINECALLSTATE_PROCEEDING            0x00000200
#define LINECALLSTATE_ONHOLD                0x00000400
#define LINECALLSTATE_CONFERENCED           0x00000800
#define LINECALLSTATE_ONHOLDPENDCONF        0x00001000
#define LINECALLSTATE_ONHOLDPENDTRANSFER    0x00002000
#define LINECALLSTATE_DISCONNECTED          0x00004000
#define LINECALLSTATE_UNKNOWN               0x00008000


#define LINECONNECTEDMODE_ACTIVE            0x00000001
#define LINECONNECTEDMODE_INACTIVE          0x00000002

#define LINEOFFERINGMODE_ACTIVE             0x00000001
#define LINEOFFERINGMODE_INACTIVE           0x00000002


typedef struct linecallstatus_tag {
    DWORD    dwTotalSize;
    DWORD    dwNeededSize;
    DWORD    dwUsedSize;

    DWORD    dwCallState;
    DWORD    dwCallStateMode;
    DWORD    dwCallPrivilege;
    DWORD    dwCallFeatures;

    DWORD    dwDevSpecificSize;
    DWORD    dwDevSpecificOffset;
} LINECALLSTATUS, *LPLINECALLSTATUS;

#define LINEDEVCAPFLAGS_CROSSADDRCONF   0x00000001
#define LINEDEVCAPFLAGS_HIGHLEVCOMP     0x00000002
#define LINEDEVCAPFLAGS_LOWLEVCOMP      0x00000004
#define LINEDEVCAPFLAGS_MEDIACONTROL    0x00000008
#define LINEDEVCAPFLAGS_MULTIPLEADDR    0x00000010
#define LINEDEVCAPFLAGS_CLOSEDROP       0x00000020
#define LINEDEVCAPFLAGS_DIALBILLING     0x00000040
#define LINEDEVCAPFLAGS_DIALQUIET       0x00000080
#define LINEDEVCAPFLAGS_DIALDIALTONE    0x00000100

typedef struct lineextensionid_tag {
    DWORD    dwExtensionID0;
    DWORD    dwExtensionID1;
    DWORD    dwExtensionID2;
    DWORD    dwExtensionID3;
} LINEEXTENSIONID, *LPLINEEXTENSIONID;


/**
 * This structure describes the capabilities of a line device.
 *
 * Device-specific extensions should use the dwDevSpecificSize and dwDevSpecificOffset members of
 * this structure.
 *
 * Older applications are compiled without new members in the LINEDEVCAPS structure, and using a
 * SIZEOF LINEDEVCAPS smaller than the new size. The application passes in a dwAPIVersion parameter
 * with the lineGetDevCaps function, which can be used for guidance by TAPI in handling this
 * situation. If the application passes in a dwTotalSize member less than the size of the fixed
 * portion of the structure as defined in the specified dwAPIVersion, LINEERR_STRUCTURETOOSMALL is
 * returned. If sufficient memory has been allocated by the application, before calling
 * TSPI_lineGetDevCaps, TAPI sets the dwNeededSize and dwUsedSize members to the fixed size of the
 * structure as it existed in the specified API version.
 *
 * New applications must be cognizant of the API version negotiated, and not examine the contents of
 * members in the fixed portion beyond the original end of the fixed portion of the structure for
 * the negotiated API version.
 *
 * If the LINEBEARERMODE_DATA bit is set in the dwBearerModes member, the dwMaxRate member indicates
 * the maximum rate of digital transmission on the bearer channel. The dwMaxRate member of the
 * LINEDEVCAPS structure can contain valid values even if the dwBearerModes member of the
 * LINEDEVCAPS structure is not set to LINEBEARERMODE_DATA.
 *
 * If LINEBEARERMODE_DATA is not set in dwBearerModes, but the LINEBEARERMODE_VOICE value is set and
 * the LINEMEDIAMODE_DATAMODEM value is set in the dwMediaModes member, the dwMaxRate member
 * indicates the maximum SYNCHRONOUS (DCE) bit rate on the phone line for the attached modem or
 * functional equivalent. For example, if the modem's fastest modulation speed is V.32bis at
 * 14,400bps, dwMaxRate equals 14400. This is not the fastest DTE port rate (which would most likely
 * be 38400, 57600, or 115200), but the fastest bit rate the modem supports on the phone line.
 *
 * The application must be careful to check to see that LINEBEARERMODE_DATA is not set, to avoid
 * misinterpreting the dwMaxRate member. It is likely to be 64000 or higher if LINEBEARERMODE_DATA
 * is set.
 *
 * It should also be noted that if the modem has not been specifically identified (for example, it
 * is a "generic" modem), the figure indicated is a "best guess" based on examination of the modem.
 */
typedef struct linedevcaps_tag {
    /**
     * Specifies the total size, in bytes, allocated to this data structure.
     */
    DWORD    dwTotalSize;
    /**
     * Specifies the size, in bytes, for this data structure that is needed to hold all the returned
     * data.
     */
    DWORD    dwNeededSize;
    /**
     * Specifies the size, in bytes, of the portion of this data structure that contains useful data.
     */
    DWORD    dwUsedSize;

    DWORD    dwProviderInfoSize;
    DWORD    dwProviderInfoOffset;

    DWORD    dwSwitchInfoSize;
    DWORD    dwSwitchInfoOffset;

    /**
     * Unsupported; set to zero.
     */
    DWORD    dwPermanentLineID;
    DWORD    dwLineNameSize;
    DWORD    dwLineNameOffset;
    /**
     * Specifies the string format used with this line device. This member uses the following
     * STRINGFORMAT_ constants: Value Description STRINGFORMAT_ASCII The ASCII string format using one
     * byte per character. STRINGFORMAT_DBCS The DBCS string format using one or two bytes per
     * character. STRINGFORMAT_UNICODE The Unicode string format using two bytes per character.
     */
    DWORD    dwStringFormat;
    
    /**
     * Specifies the mode by which the originating address is specified. This member uses the
     * LINEADDRESSMODE_ constants.
     */
    DWORD    dwAddressModes;
    /**
     * Specifies the number of addresses associated with this line device. Individual addresses are
     * referred to by address identifiers. Address identifiers range from zero to one less than the
     * value indicated by dwNumAddresses.
     */
    DWORD    dwNumAddresses;
    /**
     * Flag array that indicates the different bearer modes that the address is able to support. This
     * member uses the following LINEBEARERMODE_ constants: Value Description LINEBEARERMODE_VOICE A
     * regular 3.1 kHz analog voice-grade bearer service. Bit integrity is not assured. Voice can
     * support fax and modem media modes. LINEBEARERMODE_SPEECH Corresponds to G.711 speech transmission
     * on the call. The network may use processing techniques such as analog transmission, echo
     * cancellation and compression/decompression. Bit integrity is not assured. Speech is not intended
     * to support fax and modem media modes. LINEBEARERMODE_MULTIUSE The multiuse mode defined by ISDN.
     * LINEBEARERMODE_DATA The unrestricted data transfer on the call. The data rate is specified
     * separately. LINEBEARERMODE_ALTSPEECHDATA The alternate transfer of speech or unrestricted data on
     * the same call (ISDN). LINEBEARERMODE_NONCALLSIGNALING Corresponds to a non-call-associated
     * signaling connection from the application to the service provider or switch (treated as a "media
     * stream" by the Telephony API). LINEBEARERMODE_PASSTHROUGH When a call is active in
     * LINEBEARERMODE_PASSTHROUGH, the service provider gives direct access to the attached hardware for
     * control by the application. This mode is used primarily by applications desiring temporary direct
     * control over asynchronous modems, accessed through the Win32 communications functions, for the
     * purpose of configuring or using special features not otherwise supported by the service provider.
     */
    DWORD    dwBearerModes;
    /**
     * Contains the maximum data rate in bits per second for data exchange over the call.
     */
    DWORD    dwMaxRate;
    /**
     * Flag array that indicates the different media modes the address is able to support. This member
     * uses the following LINEMEDIAMODE_ constants: Value Description LINEMEDIAMODE_UNKNOWN A media
     * stream exists, but its mode is not known. This corresponds to a call with an unclassified media
     * type. In typical analog telephony environments, an incoming call's media mode may be unknown
     * until after the call has been answered and the media stream filtered to make a determination.
     * LINEMEDIAMODE_INTERACTIVEVOICE The presence of speech on the call and the call is treated as an
     * interactive call with humans on both ends. LINEMEDIAMODE_AUTOMATEDVOICE The presence of speech on
     * the call and the voice is locally handled by an automated application. LINEMEDIAMODE_DATAMODEM A
     * data modem session on the call. LINEMEDIAMODE_G3FAX A group 3 fax is being sent or received over
     * the call. LINEMEDIAMODE_G4FAX A group 4 fax is being sent or received over the call.
     * LINEMEDIAMODE_TDD A TDD (Telephony Devices for the Deaf) session on the call.
     * LINEMEDIAMODE_DIGITALDATA Digital data being transmitted over the call. LINEMEDIAMODE_TELETEX A
     * teletex session on the call. Teletex is one of the telematic services. LINEMEDIAMODE_VIDEOTEX A
     * videotex session on the call. Videotex is one of the telematic services. LINEMEDIAMODE_TELEX A
     * telex session on the call. Telex is one of the telematic services. LINEMEDIAMODE_MIXED A mixed
     * session on the call. Mixed is one of the ISDN telematic services. LINEMEDIAMODE_ADSI An ADSI
     * (Analog Display Services Interface) session on the call. LINEMEDIAMODE_VOICEVIEW The media mode
     * of the call is VoiceView.
     */
    DWORD    dwMediaModes;

    DWORD    dwGenerateToneModes;
    DWORD    dwGenerateToneMaxNumFreq;
    DWORD    dwGenerateDigitModes;
    DWORD    dwMonitorToneMaxNumFreq;
    DWORD    dwMonitorToneMaxNumEntries;
    DWORD    dwMonitorDigitModes;
    DWORD    dwGatherDigitsMinTimeout;
    DWORD    dwGatherDigitsMaxTimeout;

    /**
     * Unsupported; set to zero.
     */
    DWORD    dwMedCtlDigitMaxListSize;
    /**
     * Contains the maximum number of entries that can be specified in the media list.
     */
    DWORD    dwMedCtlMediaMaxListSize;
    /**
     * Unsupported; set to zero.
     */
    DWORD    dwMedCtlToneMaxListSize;
    /**
     * Contains the maximum number of entries that can be specified in the call state list.
     */
    DWORD    dwMedCtlCallStateMaxListSize;

    /**
     * Specifies various Boolean device capabilities. This member uses the following LINEDEVCAPFLAGS_
     * constants: Value Description LINEDEVCAPFLAGS_CROSSADDRCONF Specifies if calls on different
     * addresses on this line can be conferenced. LINEDEVCAPFLAGS_HIGHLEVCOMP Specifies if high-level
     * compatibility data elements are supported on this line. LINEDEVCAPFLAGS_LOWLEVCOMP Specifies if
     * low-level compatibility data elements are supported on this line. LINEDEVCAPFLAGS_MEDIACONTROL
     * Specifies if media control operations are available for calls at this line.
     * LINEDEVCAPFLAGS_MULTIPLEADDR Specifies if lineMakeCall is able to deal with multiple addresses at
     * once (such as for inverse multiplexing). LINEDEVCAPFLAGS_CLOSEDROP Specifies what happens when an
     * open line is closed while the application has calls active on the line. If TRUE, the service
     * provider drops (clears) all active calls on the line when the last application that has opened
     * the line closes it with lineClose. If FALSE, the service provider does not drop active calls in
     * such cases. Instead, the calls remain active and under control of external device(s). A service
     * provider typically sets this bit to FALSE if there is some other device that can keep the call
     * alive. For example, if an analog line has the computer and phone set both connect directly to
     * them in a party-line configuration, the offhook phone automatically keeps the call active even
     * after the computer powers down. Applications should check this flag to determine if to warn the
     * user (with an OK/Cancel dialog box) that active calls will be lost. LINEDEVCAPFLAGS_DIALBILLING
     * LINEDEVCAPFLAGS_DIALQUIET LINEDEVCAPFLAGS_DIALDIALTONE These flags indicate if the "$", "@", or
     * "W" dialable string modifier is supported for a given line device. It is TRUE if the modifier is
     * supported; otherwise, FALSE. The "?" (prompt user to continue dialing) is never supported by a
     * line device. These flags enable an application to determine "up front" which modifiers would
     * result in the generation of a LINEERR. The application has the choice of pre-scanning dialable
     * strings for unsupported characters, or passing the "raw" string from lineTranslateAddress
     * directly to the provider as part of lineMakeCall and letting the function generate an error to
     * tell it which unsupported modifier occurs first in the string.
     */
    DWORD    dwDevCapFlags;
    /**
     * Provides the maximum number of (minimum bandwidth) calls that can be active (connected) on the
     * line at any one time. The actual number of active calls may be lower if higher bandwidth calls
     * have been established on the line.
     */
    DWORD    dwMaxNumActiveCalls;
    /**
     * Specifies the effect on the active call when answering another offering call on a line device.
     * This member uses the following LINEANSWERMODE_ constants: Value Description LINEANSWERMODE_NONE
     * Answering another call on the same line has no effect on the existing active call(s) on the line.
     * LINEANSWERMODE_DROP The currently active call is automatically dropped. LINEANSWERMODE_HOLD The
     * currently active call is automatically placed on hold.
     */
    DWORD    dwAnswerMode;
    /**
     * Contains the number of different ring modes that can be reported in the LINE_LINEDEVSTATE message
     * with the ringing indication. Different ring modes range from one to dwRingModes. Zero indicates
     * no ring.
     */
    DWORD    dwRingModes;
    /**
     * Specifies the different line status components for which the application may be notified in a
     * LINE_LINEDEVSTATE message on this line. This member uses the following LINEDEVSTATE_ constants:
     * Value Description LINEDEVSTATE_OTHER Device-status items other than those listed below have
     * changed. The application should check the current device status to determine which items have
     * changed. LINEDEVSTATE_RINGING The switch tells the line to alert the user. Service providers
     * notify applications on each ring cycle by sending LINE_LINEDEVSTATE messages containing this
     * constant. For example, in the United States, service providers send a message with this constant
     * every six seconds. LINEDEVSTATE_CONNECTED The line was previously disconnected and is now
     * connected to TAPI. LINEDEVSTATE_DISCONNECTED This line was previously connected and is now
     * disconnected from TAPI. LINEDEVSTATE_MSGWAITON The "message waiting" indicator is turned on.
     * LINEDEVSTATE_MSGWAITOFF The "message waiting" indicator is turned off.
     * LINEDEVSTATE_NUMCOMPLETIONS The number of outstanding call completions on the line device has
     * changed. LINEDEVSTATE_INSERVICE The line is connected to TAPI. This happens when TAPI is first
     * activated or when the line wire is physically plugged in and in service at the switch while TAPI
     * is active. LINEDEVSTATE_OUTOFSERVICE The line is out of service at the switch or physically
     * disconnected. TAPI cannot be used to operate on the line device. LINEDEVSTATE_MAINTENANCE
     * Maintenance is being performed on the line at the switch. TAPI cannot be used to operate on the
     * line device. LINEDEVSTATE_OPEN The line has been opened. LINEDEVSTATE_CLOSE The line has been
     * closed. LINEDEVSTATE_NUMCALLS The number of calls on the line device has changed.
     * LINEDEVSTATE_TERMINALS The terminal settings have changed. LINEDEVSTATE_ROAMMODE The roam mode of
     * the line device has changed. LINEDEVSTATE_BATTERY The battery level has changed significantly
     * (cellular). LINEDEVSTATE_SIGNAL The signal level has changed significantly (cellular).
     * LINEDEVSTATE_DEVSPECIFIC The line's device-specific data has changed. LINEDEVSTATE_REINIT Items
     * have changed in the configuration of line devices. To become aware of these changes (such as for
     * the appearance of new line devices), the application should reinitialize its use of TAPI. The
     * hDevice parameter is left NULL for this state change as it applies to any of the lines in the
     * system. LINEDEVSTATE_LOCK The locked status of the line device has changed.
     * LINEDEVSTATE_CAPSCHANGE Indicates that due to configuration changes made by the user or other
     * circumstances one or more of the members in the LINEDEVCAPS structure for the address have
     * changed. The application should use lineGetDevCaps to read the updated structure. If a service
     * provider sends a LINE_LINEDEVSTATE message containing this value to TAPI, TAPI passes it along to
     * applications that have negotiated TAPI version 1.4 or later; applications negotiating a previous
     * API version receive LINE_LINEDEVSTATE messages specifying LINEDEVSTATE_REINIT, requiring them to
     * shutdown and reinitialize their connection to TAPI in order to obtain the updated data.
     * LINEDEVSTATE_CONFIGCHANGE Indicates that configuration changes have been made to one or more of
     * the media devices associated with the line device. The application, if it desires, may use
     * lineGetDevConfig to read the updated data. If a service provider sends a LINE_LINEDEVSTATE
     * message containing this value to TAPI, TAPI passes it along to applications that have negotiated
     * TAPI version 1.4 or later; applications negotiating a previous API version do not receive any
     * notification. LINEDEVSTATE_TRANSLATECHANGE Indicates that due to configuration changes made by
     * the user or other circumstances one or more of the members in the LINETRANSLATECAPS structure
     * have changed. The application should use lineGetTranslateCaps to read the updated structure. If a
     * service provider sends a LINE_LINEDEVSTATE message containing this value to TAPI, TAPI passes it
     * along to applications that have negotiated TAPI version 1.4 or later; applications negotiating a
     * previous API version receive LINE_LINEDEVSTATE messages specifying LINEDEVSTATE_REINIT, requiring
     * them to shutdown and reinitialize their connection to TAPI in order to obtain the updated data.
     * LINEDEVSTATE_COMPLCANCEL Indicates that the call completion identified by the completion
     * identifier contained in the dwParam2 parameter of the LINE_LINEDEVSTATE message has been
     * externally canceled and is no longer considered valid. If a service provider sends a
     * LINE_LINEDEVSTATE message containing this value to TAPI, TAPI passes it along to applications
     * that have negotiated TAPI version 1.4 or later; applications negotiating a previous API version
     * do not receive any notification. LINEDEVSTATE_REMOVED Indicates that the device is being removed
     * from the system by the service provider (most likely through user action, through a control panel
     * or similar utility). Normally, a LINE_LINEDEVSTATE message with this value is immediately
     * followed by a LINE_CLOSE message on the device. Subsequent attempts to access the device prior to
     * TAPI being reinitialized result in LINEERR_NODEVICE being returned to the application. If a
     * service provider sends a LINE_LINEDEVSTATE message containing this value to TAPI, TAPI passes it
     * along to applications that have negotiated TAPI version 1.4 or later; applications negotiating a
     * previous API version do not receive any notification.
     */
    DWORD    dwLineStates;

    /**
     * Specifies the maximum size of user-user data that can be sent during a call accept.
     */
    DWORD    dwUUIAcceptSize;
    /**
     * Specifies the maximum size of user-user data that can be sent during a call answer.
     */
    DWORD    dwUUIAnswerSize;
    /**
     * Specifies the maximum size of user-user data that can be sent during a make call.
     */
    DWORD    dwUUIMakeCallSize;
    /**
     * Specifies the maximum size of user-user data that can be sent during a call drop.
     */
    DWORD    dwUUIDropSize;
    /**
     * Unsupported; set to zero.
     */
    DWORD    dwUUISendUserUserInfoSize;
    /**
     * Specifies the maximum size of user-user data that can be received in the LINECALLINFO structure.
     */
    DWORD    dwUUICallInfoSize;
    
    LINEDIALPARAMS    MinDialParams;
    /**
     * Unsupported; set to zero
     */
    LINEDIALPARAMS    MaxDialParams;
    /**
     * Unsupported; set to zero.
     */
    LINEDIALPARAMS    DefaultDialParams;

    DWORD    dwNumTerminals;
    DWORD    dwTerminalCapsSize;
    DWORD    dwTerminalCapsOffset;
    DWORD    dwTerminalTextEntrySize;
    DWORD    dwTerminalTextSize;
    /**
     * Unsupported; set to zero.
     */
    DWORD    dwTerminalTextOffset;

    DWORD    dwDevSpecificSize;
    /**
     * Specify the size, in bytes, of the variably sized device-specific field, and the offset, in
     * bytes, from the beginning of this data structure.
     */
    DWORD    dwDevSpecificOffset;
} LINEDEVCAPS, *LPLINEDEVCAPS;
    
#define LINEDEVSTATE_OTHER              0x00000001
#define LINEDEVSTATE_RINGING            0x00000002
#define LINEDEVSTATE_CONNECTED          0x00000004
#define LINEDEVSTATE_DISCONNECTED       0x00000008
#define LINEDEVSTATE_MSGWAITON          0x00000010
#define LINEDEVSTATE_MSGWAITOFF         0x00000020
#define LINEDEVSTATE_INSERVICE          0x00000040
#define LINEDEVSTATE_OUTOFSERVICE       0x00000080
#define LINEDEVSTATE_MAINTENANCE        0x00000100
#define LINEDEVSTATE_OPEN               0x00000200
#define LINEDEVSTATE_CLOSE              0x00000400
#define LINEDEVSTATE_NUMCALLS           0x00000800
#define LINEDEVSTATE_NUMCOMPLETIONS     0x00001000
#define LINEDEVSTATE_TERMINALS          0x00002000
#define LINEDEVSTATE_ROAMMODE           0x00004000
#define LINEDEVSTATE_BATTERY            0x00008000
#define LINEDEVSTATE_SIGNAL             0x00010000
#define LINEDEVSTATE_DEVSPECIFIC        0x00020000
#define LINEDEVSTATE_REINIT             0x00040000
#define LINEDEVSTATE_LOCK               0x00080000
#define LINEDEVSTATE_CAPSCHANGE         0x00100000
#define LINEDEVSTATE_CONFIGCHANGE       0x00200000
#define LINEDEVSTATE_TRANSLATECHANGE    0x00400000
#define LINEDEVSTATE_COMPLCANCEL        0x00800000
#define LINEDEVSTATE_REMOVED            0x01000000


/**
 * This structure describes the current status of a line device.
 *
 * Device-specific extensions should use the DevSpecific (dwDevSpecificSize and dwDevSpecificOffset)
 * variably sized area of this data structure.
 *
 * The members dwAvailableMediaModes through dwAppInfoOffset are available only to applications that
 * open the line device with an API version of 2.0 or later.
 */
typedef struct linedevstatus_tag {
    /**
     * Specifies the total size in bytes allocated to this data structure.
     */
    DWORD    dwTotalSize;
    /**
     * Specifies the size, in bytes, for this data structure that is needed to hold all the returned
     * data.
     */
    DWORD    dwNeededSize;
    /**
     * Specifies the size, in bytes, of the portion of this data structure that contains useful data.
     */
    DWORD    dwUsedSize;

    /**
     * Specifies the number of active opens on the line device.
     */
    DWORD    dwNumOpens;
    /**
     * Specifies a bit array that indicates for which media modes the line device is currently open.
     */
    DWORD    dwOpenMediaModes;
    /**
     * Specifies the number of calls on the line in call states other idle, onhold,
     * onholdpendingtransfer, and onholdpendingconference.
     */
    DWORD    dwNumActiveCalls;
    /**
     * Specifies the number of calls on the line in the onhold state.
     */
    DWORD    dwNumOnHoldCalls;
    /**
     * Specifies the number of calls on the line in the onholdpendingtransfer or onholdpendingconference
     * state.
     */
    DWORD    dwNumOnHoldPendCalls;
    /**
     * Specifies the line-related API functions that are currently available on this line. It uses the
     * following LINEFEATURE_* constants: Value Description LINEFEATURE_DEVSPECIFIC Device-specific
     * operations can be used on the line. LINEFEATURE_DEVSPECIFICFEAT Device-specific features can be
     * used on the line. LINEFEATURE_FORWARD Forwarding of all addresses can be used on the line.
     * LINEFEATURE_MAKECALL An outgoing call can be placed on this line using an unspecified address.
     * LINEFEATURE_SETMEDIACONTROL Media control can be set on this line. LINEFEATURE_SETTERMINAL
     * Terminal modes for this line can be set.
     */
    DWORD    dwLineFeatures;
    /**
     * Specifies the number of outstanding call completion requests on the line.
     */
    DWORD    dwNumCallCompletions;
    /**
     * Specifies the current ring mode on the line device.
     */
    DWORD    dwRingMode;
    /**
     * Specifies the current signal level of the connection on the line. This is a value in the range
     * 0x00000000 (weakest signal) to 0x0000FFFF (strongest signal).
     */
    DWORD    dwSignalLevel;
    /**
     * Specifies the current battery level of the line device hardware. This is a value in the range
     * 0x00000000 (battery empty) to 0x0000FFFF (battery full).
     */
    DWORD    dwBatteryLevel;
    /**
     * Specifies the current roam mode of the line device. It uses the following LINEROAMMODE_
     * constants: Value Description LINEROAMMODE_UNKNOWN The roam mode is currently unknown, but may be
     * identified later. LINEROAMMODE_UNAVAIL The roam mode is unavailable and cannot be known.
     * LINEROAMMODE_HOME The line is connected to the home network node. LINEROAMMODE_ROAMA The line is
     * connected to the Roam-A carrier and calls are charged accordingly. LINEROAMMODE_ROAMB The line is
     * connected to the Roam-B carrier and calls are charged accordingly.
     */
    DWORD    dwRoamMode;
    
    /**
     * Specifies the size, in bytes, of this data structure that contains useful data, of type
     * LINEDEVSTATUSFLAGS_. Value Description LINEDEVSTATUSFLAGS_CONNECTED Specifies if the line is
     * connected to TAPI. If TRUE, the line is connected and API is able to operate on the line device.
     * If FALSE, the line is disconnected and the application is unable to control the line device using
     * TAPI. LINEDEVSTATUSFLAGS_LOCKED This bit is most often used with line devices associated with
     * cellular phones. Many cellular phones have a security mechanism that requires the entry of a
     * password to enable the phone to place calls. This bit may be used to indicate to applications
     * that the phone is locked and cannot place calls until the password is entered on the user
     * interface of the phone, so that the application can present an appropriate alert to the user.
     * LINEDEVSTATUSFLAGS_MSGWAIT This member indicates if the line has a message waiting. If TRUE, a
     * message is waiting; if FALSE, no message is waiting. LINEDEVSTATUSFLAGS_INSERVICE This member
     * indicates if the line is in service. If TRUE, the line is in service; if FALSE, the line is out
     * of service.
     */
    DWORD    dwDevStatusFlags;
    
    DWORD    dwTerminalModesSize;
    /**
     * Specify the size, in bytes, of the variably sized device field that contains an array with
     * DWORD-sized entries, and the offset, in bytes, from the beginning of this data structure. This
     * array is indexed by terminal identifiers, in the range from zero to dwNumTerminals minus one.
     * Each entry in the array specifies the current terminal modes for the corresponding terminal set
     * using the lineSetTerminal function for this line. It uses the following LINETERMMODE_ constants:
     * Value Description LINETERMMODE_LAMPS Lamp events sent from the line to the terminal.
     * LINETERMMODE_BUTTONS Button-press events sent from the terminal to the line. LINETERMMODE_DISPLAY
     * Display data sent from the line to the terminal. LINETERMMODE_RINGER Ringer-control data sent
     * from the switch to the terminal. LINETERMMODE_HOOKSWITCH Hookswitch events sent between the
     * terminal and the line. LINETERMMODE_MEDIATOLINE The unidirectional media stream from the terminal
     * to the line associated with a call on the line. Use this value when the routing of both
     * unidirectional channels of a call's media stream can be controlled independently.
     * LINETERMMODE_MEDIAFROMTERM The unidirectional media stream from the line to the terminal
     * associated with a call on the line. Use this value when the routing of both unidirectional
     * channels of a call's media stream can be controlled independently. LINETERMMODE_MEDIABIDIRECT The
     * bidirectional media stream associated with a call on the line and the terminal. Use this value
     * when the routing of both unidirectional channels of a call's media stream cannot be controlled
     * independently.
     */
    DWORD    dwTerminalModesOffset;
    
    DWORD    dwDevSpecificSize;
    /**
     * Specify the size, in bytes, of the variably sized device-specific field, and the offset, in
     * bytes, from the beginning of this data structure.
     */
    DWORD    dwDevSpecificOffset;
} LINEDEVSTATUS, *LPLINEDEVSTATUS;

#define LINEDEVSTATUSFLAGS_CONNECTED  0x00000001
#define LINEDEVSTATUSFLAGS_MSGWAIT    0x00000002
#define LINEDEVSTATUSFLAGS_INSERVICE  0x00000004
#define LINEDEVSTATUSFLAGS_LOCKED     0x00000008


#define LINEDIALTONEMODE_NORMAL    0x00000001
#define LINEDIALTONEMODE_SPECIAL   0x00000002
#define LINEDIALTONEMODE_INTERNAL  0x00000004
#define LINEDIALTONEMODE_EXTERNAL  0x00000008
#define LINEDIALTONEMODE_UNKNOWN   0x00000010
#define LINEDIALTONEMODE_UNAVAIL   0x00000020
    
#define LINEDIGITMODE_PULSE    0x00000001
#define LINEDIGITMODE_DTMF     0x00000002
#define LINEDIGITMODE_DTMFEND  0x00000004
    
#define LINEDISCONNECTMODE_NORMAL       0x00000001
#define LINEDISCONNECTMODE_UNKNOWN      0x00000002
#define LINEDISCONNECTMODE_REJECT       0x00000004
#define LINEDISCONNECTMODE_PICKUP       0x00000008
#define LINEDISCONNECTMODE_FORWARDED    0x00000010
#define LINEDISCONNECTMODE_BUSY         0x00000020
#define LINEDISCONNECTMODE_NOANSWER     0x00000040
#define LINEDISCONNECTMODE_BADADDRESS   0x00000080
#define LINEDISCONNECTMODE_UNREACHABLE  0x00000100
#define LINEDISCONNECTMODE_CONGESTION   0x00000200
#define LINEDISCONNECTMODE_INCOMPATIBLE 0x00000400
#define LINEDISCONNECTMODE_UNAVAIL      0x00000800
#define LINEDISCONNECTMODE_NODIALTONE   0x00001000

#define LINEERR_ALLOCATED                   0x80000001
#define LINEERR_BADDEVICEID                 0x80000002
#define LINEERR_BEARERMODEUNAVAIL           0x80000003
#define LINEERR_CALLUNAVAIL                 0x80000005
#define LINEERR_COMPLETIONOVERRUN           0x80000006
#define LINEERR_CONFERENCEFULL              0x80000007
#define LINEERR_DIALBILLING                 0x80000008
#define LINEERR_DIALDIALTONE                0x80000009
#define LINEERR_DIALPROMPT                  0x8000000A
#define LINEERR_DIALQUIET                   0x8000000B
#define LINEERR_INCOMPATIBLEAPIVERSION      0x8000000C
#define LINEERR_INCOMPATIBLEEXTVERSION      0x8000000D
#define LINEERR_INIFILECORRUPT              0x8000000E
#define LINEERR_INUSE                       0x8000000F
#define LINEERR_INVALADDRESS                0x80000010
#define LINEERR_INVALADDRESSID              0x80000011
#define LINEERR_INVALADDRESSMODE            0x80000012
#define LINEERR_INVALADDRESSSTATE           0x80000013
#define LINEERR_INVALAPPHANDLE              0x80000014
#define LINEERR_INVALAPPNAME                0x80000015
#define LINEERR_INVALBEARERMODE             0x80000016
#define LINEERR_INVALCALLCOMPLMODE          0x80000017
#define LINEERR_INVALCALLHANDLE             0x80000018
#define LINEERR_INVALCALLPARAMS             0x80000019
#define LINEERR_INVALCALLPRIVILEGE          0x8000001A
#define LINEERR_INVALCALLSELECT             0x8000001B
#define LINEERR_INVALCALLSTATE              0x8000001C
#define LINEERR_INVALCALLSTATELIST          0x8000001D
#define LINEERR_INVALCARD                   0x8000001E
#define LINEERR_INVALCOMPLETIONID           0x8000001F
#define LINEERR_INVALCONFCALLHANDLE         0x80000020
#define LINEERR_INVALCONSULTCALLHANDLE      0x80000021
#define LINEERR_INVALCOUNTRYCODE            0x80000022
#define LINEERR_INVALDEVICECLASS            0x80000023
#define LINEERR_INVALDEVICEHANDLE           0x80000024
#define LINEERR_INVALDIALPARAMS             0x80000025
#define LINEERR_INVALDIGITLIST              0x80000026
#define LINEERR_INVALDIGITMODE              0x80000027
#define LINEERR_INVALDIGITS                 0x80000028
#define LINEERR_INVALEXTVERSION             0x80000029
#define LINEERR_INVALGROUPID                0x8000002A
#define LINEERR_INVALLINEHANDLE             0x8000002B
#define LINEERR_INVALLINESTATE              0x8000002C
#define LINEERR_INVALLOCATION               0x8000002D
#define LINEERR_INVALMEDIALIST              0x8000002E
#define LINEERR_INVALMEDIAMODE              0x8000002F
#define LINEERR_INVALMESSAGEID              0x80000030
#define LINEERR_INVALPARAM                  0x80000032
#define LINEERR_INVALPARKID                 0x80000033
#define LINEERR_INVALPARKMODE               0x80000034
#define LINEERR_INVALPOINTER                0x80000035
#define LINEERR_INVALPRIVSELECT             0x80000036
#define LINEERR_INVALRATE                   0x80000037
#define LINEERR_INVALREQUESTMODE            0x80000038
#define LINEERR_INVALTERMINALID             0x80000039
#define LINEERR_INVALTERMINALMODE           0x8000003A
#define LINEERR_INVALTIMEOUT                0x8000003B 
#define LINEERR_INVALTONE                   0x8000003C
#define LINEERR_INVALTONELIST               0x8000003D
#define LINEERR_INVALTONEMODE               0x8000003E
#define LINEERR_INVALTRANSFERMODE           0x8000003F
#define LINEERR_LINEMAPPERFAILED            0x80000040
#define LINEERR_NOCONFERENCE                0x80000041
#define LINEERR_NODEVICE                    0x80000042
#define LINEERR_NODRIVER                    0x80000043
#define LINEERR_NOMEM                       0x80000044
#define LINEERR_NOREQUEST                   0x80000045
#define LINEERR_NOTOWNER                    0x80000046
#define LINEERR_NOTREGISTERED               0x80000047
#define LINEERR_OPERATIONFAILED             0x80000048
#define LINEERR_OPERATIONUNAVAIL            0x80000049
#define LINEERR_RATEUNAVAIL                 0x8000004A
#define LINEERR_RESOURCEUNAVAIL             0x8000004B
#define LINEERR_REQUESTOVERRUN              0x8000004C
#define LINEERR_STRUCTURETOOSMALL           0x8000004D
#define LINEERR_TARGETNOTFOUND              0x8000004E
#define LINEERR_TARGETSELF                  0x8000004F
#define LINEERR_UNINITIALIZED               0x80000050
#define LINEERR_USERUSERINFOTOOBIG          0x80000051
#define LINEERR_REINIT                      0x80000052
#define LINEERR_ADDRESSBLOCKED              0x80000053
#define LINEERR_BILLINGREJECTED             0x80000054
#define LINEERR_INVALFEATURE                0x80000055
#define LINEERR_NOMULTIPLEINSTANCE          0x80000056


#define LINEFEATURE_DEVSPECIFIC     0x00000001
#define LINEFEATURE_DEVSPECIFICFEAT 0x00000002
#define LINEFEATURE_FORWARD         0x00000004
#define LINEFEATURE_MAKECALL        0x00000008
#define LINEFEATURE_SETMEDIACONTROL 0x00000010
#define LINEFEATURE_SETTERMINAL     0x00000020

typedef struct lineforward_tag {
    DWORD    dwForwardMode;

    DWORD    dwCallerAddressSize;
    DWORD    dwCallerAddressOffset;
    
    DWORD    dwDestCountryCode;
    DWORD    dwDestAddressSize;
    DWORD    dwDestAddressOffset;    
} LINEFORWARD, *LPLINEFORWARD;

typedef struct lineforwardlist_tag {
    DWORD    dwTotalSize;

    DWORD    dwNumEntries;
    LINEFORWARD    ForwardList[1];
} LINEFORWARDLIST, *LPLINEFORWARDLIST;

#define LINEFORWARDMODE_UNCOND          0x00000001
#define LINEFORWARDMODE_UNCONDINTERNAL  0x00000002
#define LINEFORWARDMODE_UNCONDEXTERNAL  0x00000004
#define LINEFORWARDMODE_UNCONDSPECIFIC  0x00000008
#define LINEFORWARDMODE_BUSY            0x00000010
#define LINEFORWARDMODE_BUSYINTERNAL    0x00000020
#define LINEFORWARDMODE_BUSYEXTERNAL    0x00000040
#define LINEFORWARDMODE_BUSYSPECIFIC    0x00000080
#define LINEFORWARDMODE_NOANSW          0x00000100
#define LINEFORWARDMODE_NOANSWINTERNAL  0x00000200
#define LINEFORWARDMODE_NOANSWEXTERNAL  0x00000400
#define LINEFORWARDMODE_NOANSWSPECIFIC  0x00000800
#define LINEFORWARDMODE_BUSYNA          0x00001000
#define LINEFORWARDMODE_BUSYNAINTERNAL  0x00002000
#define LINEFORWARDMODE_BUSYNAEXTERNAL  0x00004000
#define LINEFORWARDMODE_BUSYNASPECIFIC  0x00008000
#define LINEFORWARDMODE_UNKNOWN         0x00010000
#define LINEFORWARDMODE_UNAVAIL         0x00020000

#define LINEGATHERTERM_BUFFERFULL    0x00000001
#define LINEGATHERTERM_TERMDIGIT     0x00000002
#define LINEGATHERTERM_FIRSTTIMEOUT  0x00000004
#define LINEGATHERTERM_INTERTIMEOUT  0x00000008
#define LINEGATHERTERM_CANCEL        0x00000010

#define LINEGENERATETERM_DONE    0x00000001
#define LINEGENERATETERM_CANCEL  0x00000002

typedef struct linegeneratetone_tag {
    DWORD    dwFrequency;
    DWORD    dwCadenceOn;
    DWORD    dwCadenceOff;
    DWORD    dwVolume;
} LINEGENERATETONE, *LPLINEGENERATETONE;

#define LINEMAPPER         0xFFFFFFFF
typedef struct linemediacontrolcallstate_tag {
    DWORD    dwCallStates;
    DWORD    dwMediaControl;
} LINEMEDIACONTROLCALLSTATE, 
*LPLINEMEDIACONTROLCALLSTATE;

typedef struct linemediacontroldigit_tag {
    DWORD            dwDigit;
    DWORD            dwDigitModes;
    DWORD            dwMediaControl;
} LINEMEDIACONTROLDIGIT, *LPLINEMEDIACONTROLDIGIT;

typedef struct linemediacontrolmedia_tag {
    DWORD            dwMediaModes;
    DWORD            dwDuration;
    DWORD            dwMediaControl;
} LINEMEDIACONTROLMEDIA, *LPLINEMEDIACONTROLMEDIA;

typedef struct linemediacontroltone_tag {
    DWORD    dwAppSpecific;
    DWORD    dwDuration;
    DWORD    dwFrequency1;
    DWORD    dwFrequency2;
    DWORD    dwFrequency3;
    DWORD    dwMediaControl;
} LINEMEDIACONTROLTONE, *LPLINEMEDIACONTROLTONE;

#define LINEMEDIACONTROL_NONE           0x00000001
#define LINEMEDIACONTROL_START          0x00000002
#define LINEMEDIACONTROL_RESET          0x00000004
#define LINEMEDIACONTROL_PAUSE          0x00000008
#define LINEMEDIACONTROL_RESUME         0x00000010
#define LINEMEDIACONTROL_RATEUP         0x00000020
#define LINEMEDIACONTROL_RATEDOWN       0x00000040
#define LINEMEDIACONTROL_RATENORMAL     0x00000080
#define LINEMEDIACONTROL_VOLUMEUP       0x00000100
#define LINEMEDIACONTROL_VOLUMEDOWN     0x00000200
#define LINEMEDIACONTROL_VOLUMENORMAL   0x00000400

#define LINEMEDIAMODE_UNKNOWN           0x00000002
#define LINEMEDIAMODE_INTERACTIVEVOICE  0x00000004
#define LINEMEDIAMODE_AUTOMATEDVOICE    0x00000008
#define LINEMEDIAMODE_DATAMODEM         0x00000010
#define LINEMEDIAMODE_G3FAX             0x00000020
#define LINEMEDIAMODE_TDD               0x00000040
#define LINEMEDIAMODE_G4FAX             0x00000080
#define LINEMEDIAMODE_DIGITALDATA       0x00000100
#define LINEMEDIAMODE_TELETEX           0x00000200
#define LINEMEDIAMODE_VIDEOTEX          0x00000400
#define LINEMEDIAMODE_TELEX             0x00000800
#define LINEMEDIAMODE_MIXED             0x00001000
#define LINEMEDIAMODE_ADSI              0x00002000
#define LINEMEDIAMODE_VOICEVIEW         0x00004000

#define LAST_LINEMEDIAMODE              0x00004000


typedef struct linemonitortone_tag {
    DWORD    dwAppSpecific;
    DWORD    dwDuration;
    DWORD    dwFrequency1;
    DWORD    dwFrequency2;
    DWORD    dwFrequency3;
} LINEMONITORTONE, *LPLINEMONITORTONE;

#define LINEPARKMODE_DIRECTED       0x00000001
#define LINEPARKMODE_NONDIRECTED    0x00000002

#define LINEREMOVEFROMCONF_NONE    0x00000001
#define LINEREMOVEFROMCONF_LAST    0x00000002
#define LINEREMOVEFROMCONF_ANY     0x00000003

typedef struct linereqmakecall_tag {
    char    szDestAddress[TAPIMAXDESTADDRESSSIZE];
    char    szAppName[TAPIMAXAPPNAMESIZE];
    char    szCalledParty[TAPIMAXCALLEDPARTYSIZE];
    char    szComment[TAPIMAXCOMMENTSIZE];
} LINEREQMAKECALL, *LPLINEREQMAKECALL;

typedef struct linereqmediacall_tag {
    HWND    hWnd;
    WPARAM  wRequestID;
    char    szDeviceClass[TAPIMAXDEVICECLASSSIZE];
    unsigned char    ucDeviceID[TAPIMAXDEVICEIDSIZE];
    DWORD    dwSize;
    DWORD    dwSecure;
    char    szDestAddress[TAPIMAXDESTADDRESSSIZE];
    char    szAppName[TAPIMAXAPPNAMESIZE];
    char    szCalledParty[TAPIMAXCALLEDPARTYSIZE];
    char    szComment[TAPIMAXCOMMENTSIZE];
} LINEREQMEDIACALL, *LPLINEREQMEDIACALL;

#define LINEREQUESTMODE_MAKECALL     0x00000001
#define LINEREQUESTMODE_MEDIACALL    0x00000002
#define LINEREQUESTMODE_DROP         0x00000004

#define LAST_LINEREQUESTMODE         LINEREQUESTMODE_MEDIACALL


#define LINEROAMMODE_UNKNOWN    0x00000001
#define LINEROAMMODE_UNAVAIL    0x00000002
#define LINEROAMMODE_HOME       0x00000004
#define LINEROAMMODE_ROAMA      0x00000008
#define LINEROAMMODE_ROAMB      0x00000010

#define LINESPECIALINFO_NOCIRCUIT    0x00000001
#define LINESPECIALINFO_CUSTIRREG    0x00000002
#define LINESPECIALINFO_REORDER      0x00000004
#define LINESPECIALINFO_UNKNOWN      0x00000008
#define LINESPECIALINFO_UNAVAIL      0x00000010

typedef struct linetermcaps_tag {
    DWORD    dwTermDev;
    DWORD    dwTermModes;
    DWORD    dwTermSharing;
} LINETERMCAPS, *LPLINETERMCAPS;

#define LINETERMDEV_PHONE      0x00000001
#define LINETERMDEV_HEADSET    0x00000002
#define LINETERMDEV_SPEAKER    0x00000004

#define LINETERMMODE_BUTTONS       0x00000001
#define LINETERMMODE_LAMPS         0x00000002
#define LINETERMMODE_DISPLAY       0x00000004
#define LINETERMMODE_RINGER        0x00000008
#define LINETERMMODE_HOOKSWITCH    0x00000010
#define LINETERMMODE_MEDIATOLINE   0x00000020
#define LINETERMMODE_MEDIAFROMLINE 0x00000040
#define LINETERMMODE_MEDIABIDIRECT 0x00000080

#define LINETERMSHARING_PRIVATE       0x00000001
#define LINETERMSHARING_SHAREDEXCL    0x00000002
#define LINETERMSHARING_SHAREDCONF    0x00000004

#define LINETONEMODE_CUSTOM    0x00000001
#define LINETONEMODE_RINGBACK  0x00000002
#define LINETONEMODE_BUSY      0x00000004
#define LINETONEMODE_BEEP      0x00000008
#define LINETONEMODE_BILLING   0x00000010

#define LINETRANSFERMODE_TRANSFER    0x00000001
#define LINETRANSFERMODE_CONFERENCE  0x00000002

/**
 * This structure describes the result of an address translation.
 *
 * No extensions.
 */
typedef struct linetranslateoutput_tag {
    /**
     * Specifies the total size, in bytes, allocated to this data structure.
     */
    DWORD dwTotalSize;
    /**
     * Specifies the size, in bytes, for this data structure that is needed to hold all the returned
     * data.
     */
    DWORD dwNeededSize;
    /**
     * Specifies the size, in bytes, of the portion of this data structure that contains useful data.
     */
    DWORD dwUsedSize;

    DWORD dwDialableStringSize;
    /**
     * Contain the translated output that can be passed to the lineMakeCall or other function requiring
     * a dialable string. The output is always a NULL-terminated ASCII string (NULL is accounted for in
     * Size). Ancillary fields such as name and subaddress are included in this output string if they
     * were in the input string. This string may contain private data such as calling card numbers. It
     * should not be displayed to the user, to prevent inadvertent visibility to unauthorized persons.
     */
    DWORD dwDialableStringOffset;
    DWORD dwDisplayableStringSize;
    /**
     * Contain the translated output that can be displayed to the user for confirmation. It is identical
     * to DialableString, except that calling card digits are replaced with the "friendly name" of the
     * card enclosed within bracket characters (for example, "[AT&T Card]"), and ancillary fields such
     * as name and subaddress are removed. It should normally be safe to display this string in
     * call-status dialog boxes without exposing private data to unauthorized persons. This data is also
     * appropriate to include in call logs.
     */
    DWORD dwDisplayableStringOffset;

    /**
     * Contains the country code configured in CurrentLocation. This value may be used to control the
     * display by the application of certain user interface elements, for local call progress tone
     * detection, and for other purposes.
     */
    DWORD dwCurrentCountry;
    /**
     * Contains the destination country code of the translated address. This value may be passed to the
     * dwCountryCode parameter of lineMakeCall and other dialing functions (so that the call progress
     * tones of the destination country such as a busy signal are properly detected). This field is set
     * to zero if the destination address passed to lineTranslateAddress is not in canonical format.
     */
    DWORD dwDestCountry;
    /**
     * Indicates the data derived from the translation process, which may assist the application in
     * presenting user-interface elements. This field uses the following LINETRANSLATERESULT_ constants:
     */
    DWORD dwTranslateResults;
} LINETRANSLATEOUTPUT, *LPLINETRANSLATEOUTPUT;

/**
 * This structure describes the address translation capabilities.
 *
 * No extensions.
 */
typedef struct linetranslatecaps_tag {
    /**
     * Specifies the total size, in bytes, allocated to this data structure.
     */
    DWORD dwTotalSize;
    /**
     * Specifies the size, in bytes, for this data structure that is needed to hold all the returned
     * data.
     */
    DWORD dwNeededSize;
    /**
     * Specifies the size, in bytes, of the portion of this data structure that contains useful data.
     */
    DWORD dwUsedSize;

    /**
     * Specifies the number of entries in the LocationList. It includes all locations defined, including
     * zero (default).
     */
    DWORD dwNumLocations;
    DWORD dwLocationListSize;
    /**
     * List of locations known to the address translation. The list consists of a sequence of
     * LINELOCATIONENTRY structures. The dwLocationListOffset member points to the first byte of the
     * first LINELOCATIONENTRY structure, and the dwLocationListSize member indicates the total number
     * of bytes in the entire list.
     */
    DWORD dwLocationListOffset;
    
    /**
     * Specifies the dwPermanentLocationID member from the LINELOCATIONENTRY structure for the
     * CurrentLocation.
     */
    DWORD dwCurrentLocationID;
    
    DWORD dwNumCards;
    DWORD dwCardListSize;
    /**
     * Unsupported; set to zero.
     */
    DWORD dwCardListOffset;

    /**
     * Specifies the dwPreferredCardID member from the LINELOCATIONENTRY structure for the
     * CurrentLocation.
     */
    DWORD dwCurrentPreferredCardID;
} LINETRANSLATECAPS, *LPLINETRANSLATECAPS;

/**
 * The LINELOCATIONENTRY structure describes a location used to provide an address translation
 * context.
 *
 * No extensions.
 *
 * Older applications are compiled without knowledge of these new fields, and using a SIZEOF
 * LINELOCATIONENTRY smaller than the new size. Because this is an array in the variable portion of
 * a LINETRANSLATECAPS structure, it is imperative that older applications receive LINELOCATIONENTRY
 * structures in the format they previously expected, or they are not able to index through the
 * array properly. The application passes in a dwAPIVersion parameter with the lineGetTranslateCaps
 * function, which can be used for guidance by TAPI in handling this situation. The
 * lineGetTranslateCaps function should use the LINELOCATIONENTRY members and size that match the
 * indicated API version, when building the LINETRANSLATECAPS structure to be returned to the
 * application.
 */
typedef struct linelocationentry_tag {
    /**
     * The permanent identifier that identifies the location.
     */
    DWORD dwPermanentLocationID;
    DWORD dwLocationNameSize;
    /**
     * Contains a null-terminated ASCII string (size includes the NULL) that describes the location in a
     * user-friendly manner.
     */
    DWORD dwLocationNameOffset;
    /**
     * The country code of the location.
     */
    DWORD dwCountryCode;
    DWORD dwCityCodeSize;
    /**
     * Contains a null-terminated ASCII string specifying the city/area code associated with the
     * location (the size includes the NULL). This data, along with the country code, can be used by
     * applications to "default" entry fields for the user when entering phone numbers, to encourage the
     * entry of proper canonical numbers.
     */
    DWORD dwCityCodeOffset;
    /**
     * The preferred calling card when dialing from this location.
     */
    DWORD dwPreferredCardID;
    // From here down are new fields in TAPI32
    DWORD  dwLocalAccessCodeSize;
    /**
     * The size in bytes and the offset in bytes from the beginning of the LINETRANSLATECAPS structure
     * of a null-terminated ASCII string containing the access code to be dialed before calls to
     * addresses in the local calling area.
     */
    DWORD  dwLocalAccessCodeOffset;
    DWORD  dwLongDistanceAccessCodeSize;
    /**
     * The size in bytes and the offset in bytes from the beginning of the LINETRANSLATECAPS structure
     * of a null-terminated ASCII string containing the access code to be dialed before calls to
     * addresses outside the local calling area.
     */
    DWORD  dwLongDistanceAccessCodeOffset;
    DWORD  dwTollPrefixListSize;
    /**
     * The size in bytes and the offset in bytes from the beginning of the LINETRANSLATECAPS structure
     * of a null-terminated ASCII string containing the toll prefix list for the location. The string
     * contains only prefixes consisting of the digits "0" through "9", separated from each other by a
     * single "," (comma) character.
     */
    DWORD  dwTollPrefixListOffset;
    /**
     * The country identifier of the country selected for the location.
     */
    DWORD  dwCountryID;
    /**
     * Indicates options in effect for this location, with values taken from the LINELOCATIONOPTION_ set
     * of constants.
     */
    DWORD  dwOptions;
    DWORD  dwCancelCallWaitingSize;
    /**
     * The size in bytes and the offset in bytes from the beginning of the LINETRANSLATECAPS structure
     * of a null-terminated ASCII string containing the dial digits and modifier characters that should
     * be prefixed to the dialable string (after the pulse/tone character) when an application sets the
     * LINETRANSLATEOPTION_CANCELCALLWAITING bit in the dwTranslateOptions parameter of
     * lineTranslateAddress. If no prefix is defined, this may be indicated by dwCancelCallWaitingSize
     * being set to zero, or by it being set to 1 and dwCancelCallWaitingOffset pointing to an empty
     * string (single NULL byte).
     */
    DWORD  dwCancelCallWaitingOffset;
} LINELOCATIONENTRY, *LPLINELOCATIONENTRY;

typedef struct linecardentry_tag {
    DWORD dwPermanentCardID;
    DWORD dwCardNameSize;
    DWORD dwCardNameOffset;
} LINECARDENTRY, *LPLINECARDENTRY;

typedef struct lineproviderlist_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumProviders;
    DWORD dwProviderListSize;
    DWORD dwProviderListOffset;
} LINEPROVIDERLIST, FAR *LPLINEPROVIDERLIST;

typedef struct lineproviderentry_tag {
    DWORD dwPermanentProviderID;
    DWORD dwProviderFilenameSize;
    DWORD dwProviderFilenameOffset;
} LINEPROVIDERENTRY, FAR *LPLINEPROVIDERENTRY;


#define LINETOLLLISTOPTION_ADD         0x00000001
#define LINETOLLLISTOPTION_REMOVE      0x00000002

#define LINETRANSLATEOPTION_CARDOVERRIDE  0x00000001
#define LINETRANSLATEOPTION_CANCELCALLWAITING      0x00000002
#define LINETRANSLATEOPTION_FORCELOCAL             0x00000004
#define LINETRANSLATEOPTION_FORCELD                0x00000008

#define LINETRANSLATERESULT_CANONICAL              0x00000001
#define LINETRANSLATERESULT_INTERNATIONAL          0x00000002
#define LINETRANSLATERESULT_LONGDISTANCE           0x00000004
#define LINETRANSLATERESULT_LOCAL                  0x00000008
#define LINETRANSLATERESULT_INTOLLLIST             0x00000010
#define LINETRANSLATERESULT_NOTINTOLLLIST          0x00000020
#define LINETRANSLATERESULT_DIALBILLING            0x00000040
#define LINETRANSLATERESULT_DIALQUIET              0x00000080
#define LINETRANSLATERESULT_DIALDIALTONE           0x00000100
#define LINETRANSLATERESULT_DIALPROMPT             0x00000200


#define LINELOCATIONOPTION_PULSEDIAL               0x00000001

#define LINECARDOPTION_PREDEFINED              0x00000001
#define LINECARDOPTION_HIDDEN                  0x00000002


#define INITIALIZE_NEGOTIATION                     0xffffffff

// Simple Telephony prototypes

LONG WINAPI tapiRequestMakeCall(
        LPCTSTR lpszDestAddress,
        LPCTSTR lpszAppName,
        LPCTSTR lpszCalledParty,
        LPCTSTR lpszComment);

LONG WINAPI tapiRequestMediaCall(
        HWND hWnd,
        WPARAM wRequestID,
        LPCTSTR lpszDeviceClass,
        LPCTSTR lpDeviceID,
        DWORD dwSize,
        DWORD dwSecure,
        LPCTSTR lpszDestAddress,
        LPCTSTR lpszAppName,
        LPCTSTR lpszCalledParty,
        LPCTSTR lpszComment);

LONG WINAPI tapiRequestDrop(
        HWND hWnd,
        WPARAM wRequestID);

LONG WINAPI lineRegisterRequestRecipient(
        HLINEAPP hLineApp,
        DWORD dwRegistrationInstance,
        DWORD dwRequestMode,
        DWORD bEnable);

LONG WINAPI tapiGetLocationInfo(
      LPTSTR lpszCountryCode,
      LPTSTR lpszCityCode);
      
// Tapi Address Translation procedures
/**
 * This function sets the location used as the context for address translation.
 *
 * @param hLineApp [in] Application handle returned by lineInitialize. If an application has not yet
 *   called the lineInitialize function, it can set the hLineApp parameter to NULL.
 * @param dwLocation [in] Specifies a new value for the CurrentLocation entry in the [Locations]
 *   section in the registry. It must contain a valid permanent identifier of a Location entry in the
 *   [Locations] section, as obtained from lineGetTranslateCaps. If it is valid, the CurrentLocation
 *   entry is updated.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_INIFILECORRUPT LINEERR_NOMEM LINEERR_INVALAPPHANDLE
 *   LINEERR_OPERATIONFAILED LINEERR_INVALLOCATION LINEERR_RESOURCEUNAVAIL LINEERR_NODRIVER
 *   LINEERR_UNINITIALIZED
 */
LONG WINAPI lineSetCurrentLocation(
    HLINEAPP hLineApp,
    DWORD dwLocation);

LONG WINAPI lineSetTollList(
    HLINEAPP hLineApp,
    DWORD dwDeviceID,
    LPCTSTR lpszAddressIn,
    DWORD dwTollListOption);

/**
 * This function translates the specified address into a dialable string format.
 *
 * @param hLineApp [in] Application handle returned by lineInitialize. If an application has not yet
 *   called the lineInitialize function, it can set the hLineApp parameter to NULL.
 * @param dwDeviceID [in] Specifies the device identifier for the line device upon which the call is
 *   intended to be dialed, so that variations in dialing procedures on different lines can be applied
 *   to the translation process.
 * @param dwAPIVersion [in] Specifies the highest version of TAPI supported by the application (not
 *   necessarily the value negotiated by lineNegotiateAPIVersion on some particular line device).
 * @param lpszAddressIn [in] Pointer to a null-terminated string that contains the address from
 *   which the data is to be extracted for translation. Must be in either the canonical address
 *   format, or an arbitrary string of dialable digits (non-canonical). This parameter must not be
 *   NULL. If the AddressIn contains a subaddress or name field, or additional addresses separated
 *   from the first address by ASCII CR and LF characters, only the first address is translated, and
 *   the remainder of the string is returned to the application without modification.
 * @param dwCard [in] Unsupported; set to zero.
 * @param dwTranslateOptions [in] Specifies the associated operations to be performed prior to the
 *   translation of the address into a dialable string. This parameter uses the following
 *   LINETRANSLATEOPTION_ constants: Value Description LINETRANSLATEOPTION_CARDOVERRIDE If this bit is
 *   set, dwCard specifies the permanent identifier of a Card entry in the [Cards] section in the
 *   registry (as obtained from lineTranslateCaps) that should be used instead of the PreferredCardID
 *   specified in the definition of the CurrentLocation. It does not cause the PreferredCardID
 *   parameter of the current Location entry in the registry to be modified; the override applies only
 *   to the current translation operation. The dwCard parameter is ignored if the CARDOVERRIDE bit is
 *   not set. LINETRANSLATEOPTION_CANCELCALLWAITING Ignored. A user runs a Control Panel application
 *   to specify whether a Cancel Call Waiting string is appropriate for the location. A Cancel Call
 *   Waiting string is commonly used by data modem and fax applications to prevent interruption of
 *   calls by call waiting beeps. LINETRANSLATEOPTION_FORCELOCAL If the number is local but would have
 *   been translated as a long distance call (LINETRANSLATERESULT_INTOLLLIST bit set in the
 *   LINETRANSLATEOUTPUT structure), this option forces it to be translated as local. This is a
 *   temporary override of the toll list setting. LINETRANSLATEOPTION_FORCELD If the address could
 *   potentially have been a toll call, but would have been translated as a local call
 *   (LINETRANSLATERESULT_NOTINTOLLLIST bit set in the LINETRANSLATEOUTPUT structure), this option
 *   forces it to be translated as long distance. This is a temporary override of the toll list
 *   setting. Note If you have set the LINETRANSLATEOPTION_CANCELCALLWAITING bit, it is also advisable
 *   to set the LINECALLPARAMFLAGS_SECURE bit in the dwCallParamFlags member of the LINECALLPARAMS
 *   structure (passed in to lineMakeCall through the lpCallParams parameter). This prevents the line
 *   device from using dialable digits to suppress call interrupts.
 * @param lpTranslateOutput [out] Pointer to an application-allocated memory area to contain the
 *   output of the translation operation, of type LINETRANSLATEOUTPUT. Prior to calling
 *   lineTranslateAddress, the application should set the dwTotalSize member of this structure to
 *   indicate the amount of memory available to TAPI for returning data.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_BADDEVICEID LINEERR_INVALPOINTER
 *   LINEERR_INCOMPATIBLEAPIVERSION LINEERR_NODRIVER LINEERR_INIFILECORRUPT LINEERR_NOMEM
 *   LINEERR_INVALADDRESS LINEERR_OPERATIONFAILED LINEERR_INVALAPPHANDLE LINEERR_RESOURCEUNAVAIL
 *   LINEERR_INVALCARD LINEERR_STRUCTURETOOSMALL LINEERR_INVALPARAM
 *
 * This function does not translate multiplexed canonical addresses-that is, two canonical addresses
 * separated by <CRLF>. Only the first address is translated. The other address(es) are ignored.
 *
 * When an address is specified with a country code but without the local area code, the translation
 * is not as expected. Instead of translating the address as a local call, the system translates the
 * address as a long distance call with no area code. To avoid this behavior, set the
 * LINETRANSLATEOPTION_FORCELOCAL bit or provide the area code for all addresses, including local
 * ones.
 */
LONG WINAPI lineTranslateAddress(
    HLINEAPP hLineApp,
    DWORD dwDeviceID,
    DWORD dwAPIVersion,
    LPCTSTR lpszAddressIn,
    DWORD dwCard,
    DWORD dwTranslateOptions,
    LPLINETRANSLATEOUTPUT lpTranslateOutput);

/**
 * This function returns address translation capabilities.
 *
 * @param hLineApp [in] Application handle returned by lineInitialize. If an application has not yet
 *   called the lineInitialize function, it can set the hLineApp parameter to NULL.
 * @param dwAPIVersion [in] Specifies the highest version of TAPI supported by the application (not
 *   necessarily the value negotiated by lineNegotiateAPIVersion on some particular line device).
 * @param lpTranslateCaps [out] Pointer to a location to which a LINETRANSLATECAPS structure is
 *   loaded. Prior to calling lineGetTranslateCaps, the application should set the dwTotalSize member
 *   of this structure to indicate the amount of memory available to TAPI for returning data.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_INVALAPPHANDLE LINEERR_NOMEM
 *   LINEERR_INCOMPATIBLEAPIVERSION LINEERR_OPERATIONFAILED LINEERR_INIFILECORRUPT
 *   LINEERR_RESOURCEUNAVAIL LINEERR_INVALPOINTER LINEERR_STRUCTURETOOSMALL LINEERR_NODRIVER
 */
LONG WINAPI lineGetTranslateCaps(
    HLINEAPP hLineApp,
    DWORD dwAPIVersion,
    LPLINETRANSLATECAPS lpTranslateCaps);


// Tapi function prototypes

LONG WINAPI lineAccept(
        HCALL hCall, 
        LPCTSTR lpsUserUserInfo,
        DWORD dwSize);

LONG WINAPI lineAddToConference(
        HCALL hConfCall, 
        HCALL hConsultCall);

LONG WINAPI lineAnswer(
        HCALL hCall,
        LPCTSTR lpsUserUserInfo,
        DWORD dwSize);

LONG WINAPI lineBlindTransfer(
        HCALL hCall, 
        LPCTSTR lpszDestAddress,
        DWORD dwCountryCode);

/**
 * This function closes the specified open line device.
 *
 * @param hLine [in] Handle to the open line device to be closed. After the line has been
 *   successfully closed, this handle is no longer valid.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_INVALLINEHANDLE LINEERR_NOMEM
 *   LINEERR_OPERATIONFAILED LINEERR_OPERATIONUNAVAIL LINEERR_RESOURCEUNAVAIL LINEERR_UNINITIALIZED
 *
 * If an application calls lineClose while it still has active calls on the opened line, the
 * application's ownership of these calls is revoked. If the application owns these calls, the calls
 * are dropped as well. It is good programming practice for an application to dispose of the calls
 * it owns on an open line by explicitly relinquishing ownership and/or by dropping these calls
 * prior to closing the line.
 *
 * If the line was closed successfully, a LINE_LINEDEVSTATE message is sent to all applications
 * monitoring the line status for open/close changes. Outstanding asynchronous replies are
 * suppressed.
 *
 * Service providers may find it useful or necessary to forcibly reclaim line devices from an
 * application that has the line open. This can be useful to prevent an application from
 * monopolizing the line device. If this happens, a LINE_CLOSE message is sent to the application,
 * specifying the line handle of the line device that was closed.
 *
 * The lineOpen function allocates resources to the invoking application, and applications can be
 * prevented from opening a line if resources are unavailable. Therefore, an application that only
 * occasionally uses a line device, such as for making outgoing calls, should close the line to free
 * resources and enable other applications to open the line.
 */
LONG WINAPI lineClose(
        HLINE hLine);

LONG WINAPI  lineCompleteCall(
        HCALL hCall, 
        LPDWORD lpdwCompletionID, 
        DWORD dwCompletionMode, 
        DWORD dwMessageID);

LONG WINAPI lineCompleteTransfer(
        HCALL hCall, 
        HCALL hConsultCall,
        LPHCALL lphConfCall,
        DWORD dwTransferMode);

LONG WINAPI lineConfigDialog(
        DWORD dwDeviceID,
        HWND  hwndOwner,
        LPCTSTR lpszDeviceClass);

/**
 * This function deallocates the specified call handle.
 *
 * @param hCall [in] Call handle to be deallocated. An application with monitoring privileges for a
 *   call can always deallocate its handle for that call. An application with owner privilege for a
 *   call can deallocate its handle unless it is the sole owner of the call and the call is not in the
 *   idle state. The call handle is no longer valid after it has been deallocated.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_INVALCALLHANDLE LINEERR_INVALCALLSTATE
 *   LINEERR_NOMEM LINEERR_OPERATIONFAILED LINEERR_RESOURCEUNAVAIL LINEERR_UNINITIALIZED
 *
 * The deallocation does not affect the call state of the physical call. It does, however, release
 * internal resources related to the call.
 *
 * In TAPI versions earlier than 2.0, if the application is the sole owner of a call and the call is
 * not in the idle state, LINEERR_INVALCALLSTATE is returned. In this case, the application can
 * first drop the call using lineDrop and deallocate its call handle afterwards. An application that
 * has monitor privilege for a call can always deallocate its handle for the call.
 *
 * Note Be aware that leaving the call without an owner can result in the user being unable to
 * terminate the call if there are monitoring applications open preventing TAPI from calling
 * TSPI_lineCloseCall. Use this feature only if the application can determine that the call can be
 * controlled externally by the user. For more information, see LINEADDRCAPFLAGS_CLOSEDROP.
 *
 * When the lineDeallocateCall function deallocates a call handle, it also suspends further
 * processing of any outstanding LINE_REPLY messages for the call. An application must be designed
 * not to wait indefinitely for LINE_REPLY messages for each corresponding call to an asynchronous
 * function if it also uses the lineDeallocateCall function to deallocate handles.
 */
LONG WINAPI lineDeallocateCall(
        HCALL hCall);

LONG WINAPI lineDevSpecific(
        HLINE hLine, 
        DWORD dwAddressID,
        HCALL hCall,
        LPVOID lpParams, 
        DWORD dwSize);

LONG WINAPI lineDevSpecificFeature(
        HLINE hLine, 
        DWORD dwFeature, 
        LPVOID lpParams, 
        DWORD dwSize);

LONG WINAPI lineDial(
        HCALL hCall, 
        LPCTSTR lpszDestAddress, 
        DWORD dwCountryCode);

/**
 * This function drops or disconnects the specified call. The application has the option to specify
 * user-to-user data to be transmitted as part of the call disconnect.
 *
 * @param hCall [in] Handle to the call to be dropped. The application must be an owner of the call.
 *   The call state of hCall can be any state except idle.
 * @param lpsUserUserInfo [in] Pointer to a string that contains user data to be sent to the remote
 *   party as part of the call disconnect. This pointer can be left NULL if no user-to-user data is to
 *   be sent. User-to-user data is only sent if supported by the underlying network . For more
 *   information, see LINEDEVCAPS. The protocol field for the user-to-user data, if required, should
 *   appear as the first byte of the buffer pointed to by lpsUserUserInfo, and must be accounted for
 *   in dwSize.
 * @param dwSize [in] Specifies the size, in bytes, of the user-to-user data in lpsUserUserInfo. If
 *   lpsUserUserInfo is NULL, no user-to-user data is sent to the calling party and dwSize is ignored.
 *
 * @return Zero indicates success. A negative error number indicates that an error has occurred.
 *   Possible error values are as follows: LINEERR_INVALCALLHANDLE LINEERR_RESOURCEUNAVAIL
 *   LINEERR_OPERATIONUNAVAIL LINEERR_INVALPOINTER LINEERR_NOMEM LINEERR_USERUSERINFOTOOBIG
 *   LINEERR_OPERATIONFAILED LINEERR_INVALCALLSTATE LINEERR_NOTOWNER LINEERR_UNINITIALIZED
 *
 * When invoking lineDrop, related calls can sometimes be affected as well. For example, dropping a
 * conference call can drop all individual participating calls. LINE_CALLSTATE messages are sent to
 * the application for all calls whose call state is affected. A dropped call typically transitions
 * to the idle state. Invoking lineDrop on a call in the offering state rejects the call. Not all
 * telephone networks provide this capability.
 *
 * A call in the onholdpending state typically reverts to the connected state. When dropping the
 * consultation call to the third party for a conference call or when removing the third party in a
 * previously established conference call, the provider, and switch, can release the conference
 * bridge and revert the call back to a normal two-party call. If this is the case, hConfCall shifts
 * to the idle state, and the only remaining participating call transitions to the connected state.
 * Some switches automatically release the hold on the other call.
 *
 * The application has the option to send user-to-user data at the time of the drop. Even if
 * user-to-user data can be sent, there is no guarantee that the network will deliver this data to
 * the remote party.
 *
 * In various bridged or party-line configurations, when multiple parties are on the call, lineDrop
 * may not actually clear the call. For example, in a bridged situation, a lineDrop operation may
 * not actually drop the call because the status of other stations on the call may govern; instead,
 * the call may simply be changed to the LINECONNECTEDMODE_INACTIVE mode if it remains connected at
 * other stations.
 */
LONG WINAPI lineDrop(
        HCALL hCall, 
        LPCTSTR lpsUserUserInfo, 
        DWORD dwSize);

LONG WINAPI lineForward(
        HLINE hLine, 
        DWORD bAllAddresses, 
        DWORD dwAddressID, 
        LPLINEFORWARDLIST const lpForwardList, 
        DWORD dwNumRingsNoAnswer,
        LPHCALL lphConsultCall,
        LPLINECALLPARAMS const lpCallParams);

LONG WINAPI lineGatherDigits(
        HCALL hCall, 
        DWORD dwDigitModes, 
        LPTSTR lpsDigits, 
        DWORD dwNumDigits, 
        LPCTSTR lpszTerminationDigits, 
        DWORD dwFirstDigitTimeout, 
        DWORD dwInterDigitTimeout);

LONG WINAPI lineGenerateDigits(
        HCALL hCall, 
        DWORD dwDigitMode, 
        LPCTSTR lpszDigits, 
        DWORD dwDuration);

LONG WINAPI lineGenerateTone(
        HCALL hCall, 
        DWORD dwToneMode,
        DWORD dwDuration,
        DWORD dwNumTones,
        LPLINEGENERATETONE const lpTones);

LONG WINAPI lineGetAddressCaps(
        HLINEAPP hLineApp, 
        DWORD dwDeviceID, 
        DWORD dwAddressID, 
        DWORD dwAPIVersion,
        DWORD dwExtVersion, 
        LPLINEADDRESSCAPS lpAddressCaps);

LONG WINAPI lineGetAddressID(
        HLINE hLine, 
        LPDWORD lpdwAddressID, 
        DWORD dwAddressMode, 
        LPCTSTR lpsAddress, 
        DWORD dwSize);

LONG WINAPI lineGetAddressStatus(
        HLINE hLine,
        DWORD dwAddressID,
        LPLINEADDRESSSTATUS lpAddressStatus);

LONG WINAPI lineGetCallInfo(
        HCALL hCall, 
        LPLINECALLINFO lpCallInfo);

LONG WINAPI lineGetCallStatus(
        HCALL hCall, 
        LPLINECALLSTATUS lpCallStatus);

LONG WINAPI lineGetConfRelatedCalls(
        HCALL hCall,
        LPLINECALLLIST lpCallList);
        
/**
 * This function queries a specified line device to determine its telephony capabilities. The
 * returned data is valid for all addresses on the line device.
 *
 * @param hLineApp [in] Handle to the application's registration with TAPI.
 * @param dwDeviceID [in] Specifies the line device to be queried.
 * @param dwAPIVersion [in] Specifies the version number of TAPI to be used. The high-order word
 *   contains the major version number; the low-order word contains the minor version number. This
 *   number is obtained by lineNegotiateAPIVersion.
 * @param dwExtVersion [in] Not supported; set to zero.
 * @param lpLineDevCaps [out] Pointer to a variable sized structure of type LINEDEVCAPS. Upon
 *   successful completion of the request, this structure is filled with line device capabilities
 *   data. Prior to calling lineGetDevCaps, the application should set the dwTotalSize member of this
 *   structure to indicate the amount of memory available to TAPI for returning data.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_BADDEVICEID LINEERR_NOMEM
 *   LINEERR_INCOMPATIBLEAPIVERSION LINEERR_OPERATIONFAILED LINEERR_INCOMPATIBLEEXTVERSION
 *   LINEERR_OPERATIONUNAVAIL LINEERR_INVALAPPHANDLE LINEERR_RESOURCEUNAVAIL LINEERR_INVALPOINTER
 *   LINEERR_STRUCTURETOOSMALL LINEERR_NODEVICE LINEERR_UNINITIALIZED LINEERR_NODRIVER
 *
 * Before using lineGetDevCaps, the application must negotiate the TAPI version to use, and, if
 * desired, the extension version to use.
 *
 * The TAPI and extension version numbers are those under which TAPI and the service provider must
 * operate. If version ranges do not overlap, the application, TAPI, or service-provider versions
 * are incompatible and an error is returned.
 *
 * One of the members in the LINEDEVCAPS structure returned by this function contains the number of
 * addresses assigned to the specified line device. The actual address identifiers used to reference
 * individual addresses vary from zero through one less than the returned number. The capabilities
 * of each address can be different. Use lineGetAddressCaps for each available <dwDeviceID,
 * dwAddressID> combination to determine the exact capabilities of each address.
 */
LONG WINAPI lineGetDevCaps(
        HLINEAPP hLineApp, 
        DWORD dwDeviceID, 
        DWORD dwAPIVersion,
        DWORD dwExtVersion, 
        LPLINEDEVCAPS lpLineDevCaps);

/**
 * This function returns an opaque data structure object, the contents of which are specific to the
 * line, service provider, and device class. The data structure object stores the current
 * configuration of a media-stream device associated with the line device.
 *
 * @param dwDeviceID [in] Specifies the line device to be configured.
 * @param lpDeviceConfig [out] Pointer to the memory location of type VARSTRING where the device
 *   configuration structure is returned. Upon successful completion of the request, this location is
 *   filled with the device configuration. The dwStringFormat member in the VARSTRING structure is set
 *   to STRINGFORMAT_BINARY. Prior to calling lineGetDevConfig, the application should set the
 *   dwTotalSize member of this structure to indicate the amount of memory available to TAPI for
 *   returning data.
 * @param lpszDeviceClass [out] Pointer to a null-terminated string that specifies the device class
 *   of the device whose configuration is requested. Valid device class lineGetID strings are the same
 *   as those specified for the function.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_BADDEVICEID LINEERR_OPERATIONFAILED
 *   LINEERR_INVALDEVICECLASS LINEERR_OPERATIONUNAVAIL LINEERR_INVALPOINTER LINEERR_RESOURCEUNAVAIL
 *   LINEERR_NODEVICE LINEERR_STRUCTURETOOSMALL LINEERR_NODRIVER LINEERR_UNINITIALIZED LINEERR_NOMEM
 *
 * For Windows CE, lineGetDevConfig always returns a default configuration for a device. There are
 * two advantages to this behavior. First, if a user chooses the default settings, then an
 * application does not need to store the associated configuration (for example in a connectoid).
 * Second, the lineConfigDialogEdit dialog can be easily made to always come up in the same state.
 *
 * Call states are device specific.
 *
 * The lineGetDevConfig function can be used to retrieve a data structure from TAPI that specifies
 * the configuration of a media stream device associated with a particular line device. For example,
 * the contents of this structure could specify data rate, character format, modulation schemes, and
 * error control protocol settings for a "datamodem" media device associated with the line.
 *
 * The exact format of the data contained within the structure is specific to the line and media
 * stream API (device class), is undocumented, and is undefined. The structure returned by this
 * function cannot be directly accessed or manipulated by the application, but can only be stored
 * intact and later used in lineSetDevConfig to restore the settings. The structure also cannot
 * necessarily be passed to other devices, even of the same device class (although this can work in
 * some instances, it is not guaranteed). An application can use lineConfigDialogEdit to manipulate
 * the configuration.
 */
LONG WINAPI lineGetDevConfig(
        DWORD dwDeviceID,
        LPVARSTRING lpDeviceConfig,
        LPCTSTR lpszDeviceClass);

LONG WINAPI lineGetNewCalls(
        HLINE hLine,
        DWORD dwAddressID,
        DWORD dwSelect,
        LPLINECALLLIST lpCallList);

LONG WINAPI lineGetIcon(
        DWORD dwDeviceID,
        LPCTSTR lpszDeviceClass,
        LPHICON lphIcon);
        
/**
 * This function returns a device identifier for the specified device class associated with the
 * selected line, address, or call.
 *
 * @param hLine [in] Handle to an open line device.
 * @param dwAddressID [in] Specifies an address on the given open line device.
 * @param hCall [in] Handle to a call.
 * @param dwSelect [in] Specifies whether the requested device identifier is associated with the
 *   line, address or a single call. The dwSelect parameter can only have a single flag set. This
 *   parameter uses the following LINECALLSELECT_* constants: Value Description LINECALLSELECT_LINE
 *   Selects the specified line device. The hLine parameter must be a valid line handle; hCall and
 *   dwAddressID are ignored. LINECALLSELECT_ADDRESS Selects the specified address on the line. Both
 *   hLine and dwAddressID must be valid; hCall is ignored. LINECALLSELECT_CALL Selects the specified
 *   call. hCall must be valid; hLine and dwAddressID are both ignored.
 * @param lpDeviceID [out] Pointer to a memory location of type VARSTRING, where the device
 *   identifier is returned. Upon successful completion of the request, this location is filled with
 *   the device identifier. The format of the returned data depends on the method used by the device
 *   class API for naming devices. Prior to calling lineGetID, the application should set the
 *   dwTotalSize member of this structure to indicate the amount of memory available to TAPI for
 *   returning data.
 * @param lpszDeviceClass [out] Pointer to a null-terminated string that specifies the device class
 *   of the device whose identifier is requested. Valid device class strings are those used in the
 *   System.ini section to identify device classes.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_INVALLINEHANDLE LINEERR_INVALCALLSELECT
 *   LINEERR_NOMEM LINEERR_RESOURCEUNAVAIL LINEERR_INVALADDRESSID LINEERR_INVALPOINTER
 *   LINEERR_OPERATIONUNAVAIL LINEERR_STRUCTURETOOSMALL LINEERR_INVALCALLHANDLE LINEERR_NODEVICE
 *   LINEERR_OPERATIONFAILED LINEERR_UNINITIALIZED
 *
 * The lineGetID function can be used to retrieve a line-device identifier when given a line handle.
 * This function can also be used to obtain the device identifier of a phone device or media device
 * (for device classes such as COM, wave, MIDI, phone, line, or NDIS) associated with a call,
 * address or line. This identifier can then be used with the appropriate API (such as phone, MIDI,
 * wave) to select the corresponding media device associated with the specified call.
 *
 * The following table shows device class names.
 *
 * Device class name Description comm * Communication port comm/datamodem * Modem through a
 * communication port comm/datamodem/portname Name of the device to which a modem is connected
 * wave/in Wave audio device (input only) wave/out Wave audio device (output only) midi/in Midi
 * sequencer (input only) midi/out Midi sequencer (output only) tapi/line * Line device tapi/phone
 * Phone device ndis * Network device tapi/terminal Terminal device
 *
 * A vendor that defines a device-specific media mode also needs to define the corresponding
 * device-specific (proprietary) API to manage devices of the media mode. To avoid collisions on
 * device class names assigned independently by different vendors, a vendor should select a name
 * that uniquely identifies both the vendor and, following it, the media type. For example:
 * "intel/video".
 */
LONG WINAPI lineGetID(
        HLINE hLine,
        DWORD dwAddressID, 
        HCALL hCall,
        DWORD dwSelect,        
        LPVARSTRING lpDeviceID, 
        LPCTSTR lpszDeviceClass);

LONG WINAPI lineGetLineDevStatus(
        HLINE hLine, 
        LPLINEDEVSTATUS lpLineDevStatus);

LONG WINAPI lineGetNumRings(
        HLINE hLine, 
        DWORD dwAddressID, 
        LPDWORD lpdwNumRings);

LONG WINAPI lineGetRequest(
        HLINEAPP hLineApp,
        DWORD dwRequestMode,
        LPVOID lpRequestBuffer);

LONG WINAPI lineGetStatusMessages(
        HLINE hLine, 
        LPDWORD lpdwLineStates, 
        LPDWORD lpdwAddressStates);

LONG WINAPI lineHandoff(
        HCALL hCall, 
        LPCTSTR lpszFileName,
        DWORD dwMediaMode);

LONG WINAPI lineHold(
        HCALL hCall);

/**
 * This function initializes the application's use of Tapi.dll for subsequent use of the line
 * abstraction. It registers the application's specified notification mechanism and returns the
 * number of line devices available to the application. A line device is any device that provides an
 * implementation for the line-prefixed functions in TAPI.
 *
 * @param lphLineApp [out] Pointer to a location that is filled with the application's usage handle
 *   for TAPI.
 * @param hInstance [in] Instance handle of the client application or DLL.
 * @param lpfnCallback [in] Pointer to a callback function that is invoked to determine status and
 *   events on the line device, addresses, or calls. For more information, see lineCallbackFunc.
 * @param lpszAppName [in] Pointer to a null-terminated string that contains only displayable ASCII
 *   characters. If this parameter is not NULL, it contains an application-supplied name for the
 *   application. This name is provided in the LINECALLINFO structure to indicate, in a user-friendly
 *   way, which application originated, or originally accepted or answered the call. This data can be
 *   useful for call logging purposes. If lpszAppName is NULL, the application's filename is used
 *   instead.
 * @param lpdwNumDevs [out] Pointer to a DWORD-sized location. Upon successful completion of this
 *   request, this location is filled with the number of line devices available to the application.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_INVALAPPNAME LINEERR_REINIT LINEERR_OPERATIONFAILED
 *   LINEERR_NODRIVER LINEERR_INIFILECORRUPT LINEERR_NODEVICE LINEERR_RESOURCEUNAVAIL LINEERR_NOMEM
 *   LINEERR_INVALPOINTER LINEERR_NOMULTIPLEINSTANCE
 *
 * If LINEERR_REINIT is returned and TAPI reinitialization has been requested (for example as a
 * result of adding or removing a telephony service provider), then lineInitialize requests are
 * rejected with this error until the last application shuts down its usage of the API (using
 * lineShutdown). At that time, the new configuration becomes effective and applications are once
 * again permitted to call lineInitialize. If the LINEERR_INVALPARAM error value is returned, the
 * specified hInstance parameter is invalid.
 *
 * The application can refer to individual line devices by using line device identifiers that range
 * from zero to dwNumDevs minus one. An application should not assume that these line devices are
 * capable of anything beyond what is specified by the Basic Telephony subset without first querying
 * their device capabilities using lineGetDevCaps.
 *
 * Applications should not invoke lineInitialize without subsequently opening a line (at least for
 * monitoring). If the application is not monitoring and not using any devices, it should call
 * lineShutdown so that memory resources allocated by Tapi.dll can be released if unneeded, and
 * Tapi.dll itself can be unloaded from memory while not needed.
 *
 * Another reason for performing a lineShutdown is that if a user changes the device configuration
 * (adds or removes a line or phone), there is no way for TAPI to notify an application that has a
 * line or phone handle open at the time. After a reconfiguration has taken place, causing a
 * LINEDEVSTATE_REINIT message to be sent, no applications can open a device until all applications
 * have performed a lineShutdown. If any service provider fails to initialize properly, this
 * function fails and returns the error indicated by the service provider.
 */
LONG WINAPI lineInitialize(
        LPHLINEAPP lphLineApp,
        HINSTANCE hInstance,
        LINECALLBACK lpfnCallback,
        LPCTSTR lpszAppName,
        LPDWORD lpdwNumDevs);

/**
 * This function places a call on the specified line to the specified destination address.
 * Optionally, call parameters can be specified if anything but default call setup parameters are
 * requested.
 *
 * @param hLine [in] Handle to the open line device on which a call is to be originated.
 * @param lphCall [in] Pointer to an HCALL handle. The handle is only valid after the LINE_REPLY
 *   message is received by the application indicating that the lineMakeCall function successfully
 *   completed. Use this handle to identify the call when invoking other telephony operations on the
 *   call. The application is initially the sole owner of this call. This handle is void if the
 *   function returns an error (synchronously or asynchronously by the reply message).
 * @param lpszDestAddress [in] Pointer to the null-terminated string that contains the destination
 *   address. This follows the standard dialable number format. This pointer can be NULL for
 *   non-dialed addresses (as with a hot phone). Service providers that have inverse multiplexing
 *   capabilities can enable an application to specify multiple addresses at once.
 * @param dwCountryCode [in] Specifies the country code of the called party. If a value of 0 is
 *   specified, a default is used by the implementation.
 * @param lpCallParams [in] Pointer to a LINECALLPARAMS structure. This structure enables the
 *   application to specify how it wants the call to be set up. If NULL is specified, a default 3.1
 *   kHz voice call is established and an arbitrary origination address on the line is selected. This
 *   structure enables the application to select elements such as the call's bearer mode, data rate,
 *   expected media mode, origination address, blocking of caller identification data, and dialing
 *   parameters.
 *
 * @return A positive request identifier indicates that the function is completed asynchronously. A
 *   negative error number indicates that an error has occurred. The dwParam2 parameter of the
 *   corresponding LINE_REPLY message is zero if the function succeeds, or it is a negative error
 *   number if an error occurs. Possible error values are as follows: LINEERR_ADDRESSBLOCKED
 *   LINEERR_INVALLINEHANDLE LINEERR_BEARERMODEUNAVAIL LINEERR_INVALLINESTATE LINEERR_CALLUNAVAIL
 *   LINEERR_INVALMEDIAMODE LINEERR_DIALBILLING LINEERR_INVALPARAM LINEERR_DIALDIALTONE
 *   LINEERR_INVALPOINTER LINEERR_DIALPROMPT LINEERR_INVALRATE LINEERR_DIALQUIET LINEERR_NOMEM
 *   LINEERR_INUSE LINEERR_OPERATIONFAILED LINEERR_INVALADDRESS LINEERR_OPERATIONUNAVAIL
 *   LINEERR_INVALADDRESSID LINEERR_RATEUNAVAIL LINEERR_INVALADDRESSMODE LINEERR_RESOURCEUNAVAIL
 *   LINEERR_INVALBEARERMODE LINEERR_STRUCTURETOOSMALL LINEERR_INVALCALLPARAMS LINEERR_UNINITIALIZED
 *   LINEERR_INVALCOUNTRYCODE LINEERR_USERUSERINFOTOOBIG
 *
 * If LINEERR_INVALLINESTATE is returned, the line is currently not in a state in which this
 * operation can be performed. A list of currently valid operations can be found in the
 * dwLineFeatures member (of the type LINEFEATURE_) in the LINEDEVSTATUS structure. If
 * LINEERR_DIALBILLING, LINEERR_DIALQUIET, LINEERR_DIALDIALTONE, or LINEERR_DIALPROMPT is returned,
 * none of the actions otherwise performed by lineMakeCall have occurred; for example, none of the
 * dialable address prior to the offending character has been dialed, no hook switch state has
 * changed, and so on.
 *
 * After dialing has completed, several LINE_CALLSTATE messages are usually sent to the application
 * to notify it about the progress of the call. No generally valid sequence of call-state
 * transitions is specified, as no single fixed sequence of transitions can be guaranteed in
 * practice. A typical sequence can cause a call to transition from dialtone, dialing, proceeding,
 * ringback, to connected. With non-dialed lines, the call can typically transition directly to
 * connected state.
 *
 * An application has the option to specify an originating address on the specified line device. A
 * service provider that models all stations on a switch as addresses on a single line device
 * enables the application to originate calls from any of these stations using lineMakeCall.
 *
 * The call parameters enable the application to make non-voice calls or request special call setup
 * options that are not available by default.
 *
 * An application can partially dial using lineMakeCall and continue dialing using lineDial. To
 * abandon a call attempt, use lineDrop.
 *
 * After lineMakeCall returns a success reply message to the application, a LINE_CALLSTATE message
 * is sent to the application to indicate the current state of the call. This state is not
 * necessarily LINECALLSTATE_DIALTONE.
 *
 * For Windows CE versions 1.0 through 2.11, lineMakeCall does not handle timeouts correctly. If a
 * connection fails after lineMakeCall returns but before the associated LINE_REPLY message is
 * received, a LINE_REPLY message is not generated. Because a LINE_REPLY message is never received,
 * an application does not have the handle for the call. Without a handle, an application cannot
 * call lineDrop nor lineDeallocateCall free call resources. Because call resources are never
 * deallocated, a call fails that is placed on the line before it is closed.
 *
 * For Windows CE versions 2.12 and later, the timeout problem is addressed by UNIMODEM sending a
 * LINEMAKECALL_TIMEOUT message after eight seconds without a response.
 */
LONG WINAPI lineMakeCall(
        HLINE hLine, 
        LPHCALL lphCall, 
        LPCTSTR lpszDestAddress, 
        DWORD dwCountryCode, 
        LPLINECALLPARAMS const lpCallParams);

LONG WINAPI lineMonitorDigits(
        HCALL hCall, 
        DWORD dwDigitModes);

LONG WINAPI lineMonitorMedia(
        HCALL hCall, 
        DWORD dwMediaModes);

LONG WINAPI lineMonitorTones(
        HCALL hCall, 
        LPLINEMONITORTONE const lpToneList, 
        DWORD dwNumEntries);

/**
 * This function enables an application to negotiate an TAPI version to use.
 *
 * @param hLineApp [in] Handle to the application's registration with TAPI.
 * @param dwDeviceID [in] Specifies the identifier of the line device to be queried.
 * @param dwAPILowVersion [in] Specifies the least recent TAPI version the application is compliant
 *   with. The high-order word is the major version number; the low-order word is the minor version
 *   number.
 * @param dwAPIHighVersion [in] Specifies the most recent TAPI version the application is compliant
 *   with. The high-order word is the major version number; the low-order word is the minor version
 *   number.
 * @param lpdwAPIVersion [out] Pointer to a DWORD-sized location that contains the TAPI version
 *   number that was negotiated. If negotiation succeeds, this number is in the range between
 *   dwAPILowVersion and dwAPIHighVersion.
 * @param lpExtensionID [out] Ignored; set to NULL.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_BADDEVICEID LINEERR_ LINEERR_NODRIVER
 *   LINEERR_UNINITIALIZED LINEERR_INCOMPATIBLEAPIVERSION LINEERR_NOMEM LINEERR_OPERATIONFAILED
 *   LINEERR_OPERATIONUNAVAIL LINEERR_INVALAPPHANDLE LINEERR_NODEVICE LINEERR_RESOURCEUNAVAIL
 *
 * Use lineInitialize to determine the number of line devices present in the system. The device
 * identifier specified by dwDeviceID varies from zero to one less than the number of line devices
 * present.
 *
 * The lineNegotiateAPIVersion function is used to negotiate the TAPI version number to use. It also
 * retrieves the extension identifier supported by the line device, and returns zeros if no
 * extensions are supported. If the application wants to use the extensions defined by the returned
 * extension identifier, it must call lineNegotiateExtVersion to negotiate the extension version to
 * use.
 *
 * The TAPI version number negotiated is that under which TAPI can operate. If version ranges do not
 * overlap, the application and API or service provider versions are incompatible and an error is
 * returned.
 */
LONG WINAPI lineNegotiateAPIVersion(
        HLINEAPP hLineApp,
        DWORD dwDeviceID,
        DWORD dwAPILowVersion,
        DWORD dwAPIHighVersion,
        LPDWORD lpdwAPIVersion,
        LPLINEEXTENSIONID lpExtensionID);

LONG WINAPI lineNegotiateExtVersion(
        HLINEAPP hLineApp,
        DWORD dwDeviceID,
        DWORD dwAPIVersion,
        DWORD dwExtLowVersion,
        DWORD dwExtHighVersion,
        LPDWORD lpdwExtVersion);

/**
 * This function opens the line device specified by its device identifier and returns a line handle
 * for the corresponding opened line device. This line handle is used in subsequent operations on
 * the line device.
 *
 * @param hLineApp [in] Handle to the application's registration with TAPI.
 * @param dwDeviceID [in] Species the identifier of the line device to be opened. It must be a valid
 *   device identifier.
 * @param lphLine [out] Pointer to an HLINE handle that is then loaded with the handle representing
 *   the opened line device. Use this handle to identify the device when invoking other functions on
 *   the open line device.
 * @param dwAPIVersion [in] Specifies the TAPI version number under which the application and TAPI
 *   have agreed to operate. This number is obtained with lineNegotiateAPIVersion.
 * @param dwExtVersion [in] Unsupported; set to zero.
 * @param dwCallbackInstance [in] Specifies user-instance data passed back to the application with
 *   each message associated with this line or with addresses or calls on this line. This parameter is
 *   not interpreted by TAPI.
 * @param dwPrivileges [in] Specifies the privilege the application wants for the calls it is
 *   notified for. This parameter can be a combination of the LINECALLPRIVILEGE_* constants. Value
 *   Description LINECALLPRIVILEGE_NONE The application can make only outgoing calls.
 *   LINECALLPRIVILEGE_MONITOR The application can monitor only incoming and outgoing calls.
 *   LINECALLPRIVILEGE_OWNER The application can own only incoming calls of the types specified in
 *   dwMediaModes. LINECALLPRIVILEGE_MONITOR + LINECALLPRIVILEGE_OWNER The application can own only
 *   incoming calls of the types specified in dwMediaModes, but if it is not an owner of a call, it is
 *   a monitor. Other flag combinations are invalid.
 * @param dwMediaModes [in] Specifies the media mode or modes of interest to the application. This
 *   parameter is used to register the application as a potential target for incoming call and call
 *   handoff for the specified media mode. This parameter is meaningful only if the bit
 *   LINECALLPRIVILEGE_OWNER in dwPrivileges is set (and ignored if it is not). This parameter uses
 *   the following LINEMEDIAMODE_* constants: Value Description LINEMEDIAMODE_UNKNOWN The application
 *   can handle calls of unknown media type (unclassified calls). LINEMEDIAMODE_INTERACTIVEVOICE The
 *   application can handle calls of the interactive voice media type. That is, it manages voice calls
 *   with the human user on this end of the call. LINEMEDIAMODE_AUTOMATEDVOICE Voice energy is present
 *   on the call. The voice is locally handled by an automated application. LINEMEDIAMODE_DATAMODEM
 *   The application can handle calls with the data-modem media mode. LINEMEDIAMODE_G3FAX The
 *   application can handle calls of the group 3 fax media type. LINEMEDIAMODE_TDD The application can
 *   handle calls with the TDD (Telephony Devices for the Deaf) media mode. LINEMEDIAMODE_G4FAX The
 *   application can handle calls of the group 4 fax media type. LINEMEDIAMODE_DIGITALDATA The
 *   application can handle calls of the digital-data media type. LINEMEDIAMODE_TELETEX The
 *   application can handle calls with the teletex media mode. LINEMEDIAMODE_VIDEOTEX The application
 *   can handle calls with the videotex media mode. LINEMEDIAMODE_TELEX The application can handle
 *   calls with the telex media mode. LINEMEDIAMODE_MIXED The application can handle calls with the
 *   ISDN mixed media mode. LINEMEDIAMODE_ADSI The application can handle calls with the ADSI (Analog
 *   Display Services Interface) media mode. LINEMEDIAMODE_VOICEVIEW The media mode of the call is
 *   VoiceView.
 * @param lpCallParams [in] Pointer to a structure of type LINECALLPARAMS. This pointer should be
 *   set to NULL for Windows CE 2.x.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_ALLOCATED LINEERR_NODEVICE LINEERR_BADDEVICEID
 *   LINEERR_NODRIVER LINEERR_INCOMPATIBLEAPIVERSION LINEERR_NOMEM LINEERR_INCOMPATIBLEEXTVERSION
 *   LINEERR_OPERATIONFAILED LINEERR_INVALAPPHANDLE LINEERR_OPERATIONUNAVAIL LINEERR_INVALMEDIAMODE
 *   LINEERR_REINIT LINEERR_INVALPOINTER LINEERR_RESOURCEUNAVAIL LINEERR_INVALPRIVSELECT
 *   LINEERR_STRUCTURETOOSMALL LINEERR_LINEMAPPERFAILED LINEERR_UNINITIALIZED
 *
 * If LINEERR_ALLOCATED is returned, the line cannot be opened due to a "persistent" condition, such
 * as that of a serial port being exclusively opened by another process. If LINEERR_RESOURCEUNAVAIL
 * is returned, the line cannot be opened due to a dynamic resource overcommitment such as in DSP
 * processor cycles or memory. This overcommitment can be transitory, caused by monitoring of media
 * mode or tones, and changes in these activities by other applications can make it possible to
 * reopen the line within a short time period. If LINEERR_REINIT is returned and TAPI
 * reinitialization has been requested (for example, as a result of adding or removing a telephony
 * service provider), then lineOpen requests are rejected with this error until the last application
 * shuts down its usage of the API (using lineShutdown); at that time the new configuration becomes
 * effective and applications are once again permitted to call lineInitialize.
 *
 * Opening a line always entitles the application to make calls on any address available on the
 * line. The ability of the application to deal with incoming calls or to be the target of call
 * handoffs on the line is determined by the dwMediaModes parameter. The lineOpen function registers
 * the application as having an interest in monitoring calls or receiving ownership of calls that
 * are of the specified media modes. If the application just wants to monitor calls, then it can
 * specify LINECALLPRIVILEGE_MONITOR. If the application just wants to make outgoing calls, it can
 * specify LINECALLPRIVILEGE_NONE. If the application is willing to control unclassified calls
 * (calls of unknown media mode), it can specify LINECALLPRIVILEGE_OWNER and LINEMEDIAMODE_UNKNOWN.
 * Otherwise, the application should specify the media mode it is interested in handling.
 *
 * The media modes specified with lineOpen add to the default value for the provider's media mode
 * monitoring for initial incoming call type determination. If a line device is opened with owner
 * privilege and an extension media mode is not registered, then the error LINEERR_INVALMEDIAMODE is
 * returned.
 *
 * An application that has successfully opened a line device can initiate calls using lineMakeCall.
 *
 * A single application can specify multiple flags simultaneously to handle multiple media modes.
 * Conflicts can arise if multiple applications open the same line device for the same media mode.
 * These conflicts are resolved by a priority scheme in which the user assigns relative priorities
 * to the applications. Only the highest priority application for a given media mode will ever
 * receive ownership (unsolicited) of a call of that media mode. Ownership can be received when an
 * incoming call first arrives or when a call is handed off.
 *
 * An application that handles automated voice should also select the interactive voice open mode
 * and be assigned the lowest priority for interactive voice. The reason for this is that service
 * providers report all voice media modes as interactive voice. If media mode determination is not
 * performed by the application for the UNKNOWN media type, and no interactive voice application has
 * opened the line device, voice calls would be unable to reach the automated voice application, and
 * would be dropped.
 *
 * The same application, or different installations of the same application, can open the same line
 * multiple times with the same or different parameters.
 *
 * When an application opens a line device it must specify the negotiated TAPI version, which is
 * obtained with a call to lineNegotiateAPIVersion. Version numbering enables the mixing and
 * matching of different application versions with different TAPI versions.
 */
LONG WINAPI lineOpen(
        HLINEAPP hLineApp, 
        DWORD dwDeviceID,
        LPHLINE lphLine,
        DWORD dwAPIVersion,
        DWORD dwExtVersion,
        DWORD dwCallbackInstance,
        DWORD dwPrivileges,
        DWORD dwMediaModes,
        LPLINECALLPARAMS const lpCallParams);

LONG WINAPI linePark(
        HCALL hCall, 
        DWORD dwParkMode, 
        LPCTSTR lpszDirAddress,
        LPVARSTRING lpNonDirAddress);

LONG WINAPI linePickup(
        HLINE hLine,
        DWORD dwAddressID,
        LPHCALL lphCall, 
        LPCTSTR lpszDestAddress, 
        LPCTSTR lpszGroupID);

LONG WINAPI linePrepareAddToConference(
        HCALL            hConfCall,
        LPHCALL          lphConsultCall,
        LPLINECALLPARAMS const lpCallParams);
        
LONG WINAPI lineRedirect(
        HCALL hCall, 
        LPCTSTR lpszDestAddress, 
        DWORD dwCountryCode);

LONG WINAPI lineRemoveFromConference(
        HCALL hCall);

LONG WINAPI lineSecureCall(
        HCALL hCall);

LONG WINAPI lineSendUserUserInfo(
        HCALL hCall, 
        LPCTSTR lpsUserUserInfo, 
        DWORD dwSize);

LONG WINAPI lineSetAppSpecific(
        HCALL hCall, 
        DWORD dwAppSpecific);

LONG WINAPI lineSetCallParams(
        HCALL hCall, 
        DWORD dwBearerMode,
        DWORD dwMinRate,
        DWORD dwMaxRate,
        LPLINEDIALPARAMS const lpDialParams);

LONG WINAPI lineSetCallPrivilege(
        HCALL hCall,
        DWORD dwCallPrivilege);

/**
 * This function enables the application to restore the configuration of a media-stream device on a
 * line device to a setup previously obtained using the lineGetDevConfig function. For example, the
 * contents of this structure could specify data rate, character format, modulation schemes, and
 * error control protocol settings for a "datamodem" media device associated with the line.
 *
 * @param dwDeviceID [in] Specifies the line device to be configured.
 * @param lpDeviceConfig [in] Pointer to the opaque configuration data structure that was returned
 *   by lineGetDevConfig in the variable portion of the VARSTRING structure.
 * @param dwSize [in] Specifies the number of bytes in the structure pointed to by lpDeviceConfig.
 *   This value is returned in the dwStringSize member in the VARSTRING structure returned by
 *   lineGetDevConfig.
 * @param lpszDeviceClass [in] Pointer to a null-terminated string that specifies the device class
 *   of the device whose configuration is to be set. Valid device class strings are the same as those
 *   specified for the lineGetID function.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_BADDEVICEID LINEERR_NODEVICE LINEERR_NODRIVER
 *   LINEERR_NOMEM LINEERR_INVALDEVICECLASS LINEERR_OPERATIONFAILED LINEERR_INVALLINESTATE
 *   LINEERR_OPERATIONUNAVAIL LINEERR_INVALPARAM LINEERR_RESOURCEUNAVAIL LINEERR_INVALPOINTER
 *   LINEERR_UNINITIALIZED
 *
 * Call states are device specific.
 *
 * Typically, an application calls lineGetID to identify the media stream device associated with a
 * line, and then calls lineConfigDialogEdit to enable the user to change the device configuration
 * and affect the current call or next call with those changes by passing the output of
 * lineConfigDialogEdit to lineSetDevConfig. When the user wants to call the same destination again,
 * this lineSetDevConfig function can be used to restore the configuration settings selected by the
 * user.
 *
 * The exact format of the data contained within the structure is specific to the line and media
 * stream API (device class), is undocumented, and is undefined. The application must treat it as
 * "opaque" and not manipulate the contents directly. Generally, the structure can be sent using
 * this function only to the same device from which it was obtained. Certain telephony service
 * providers may, however, permit structures to be interchanged between identical devices (that is,
 * multiple ports on the same multiport modem card). Such interchangeability is not guaranteed in
 * any way, even for devices of the same device class.
 *
 * Some service providers may permit the configuration to be set while a call is active, and others
 * may not.
 */
LONG WINAPI lineSetDevConfig(
        DWORD dwDeviceID,
        LPVOID const lpDeviceConfig,
        DWORD dwSize,
        LPCTSTR lpszDeviceClass);

LONG WINAPI lineSetMediaControl(
        HLINE hLine,
        DWORD dwAddressID,
        HCALL hCall, 
        DWORD dwSelect,
        LPLINEMEDIACONTROLDIGIT const lpDigitList, 
        DWORD dwDigitNumEntries, 
        LPLINEMEDIACONTROLMEDIA const lpMediaList, 
        DWORD dwMediaNumEntries, 
        LPLINEMEDIACONTROLTONE const lpToneList, 
        DWORD dwToneNumEntries, 
        LPLINEMEDIACONTROLCALLSTATE const lpCallStateList, 
        DWORD dwCallStateNumEntries);

LONG WINAPI lineSetMediaMode(
        HCALL hCall,
        DWORD dwMediaModes);

LONG WINAPI lineSetNumRings(
        HLINE hLine, 
        DWORD dwAddressID, 
        DWORD dwNumRings);

/**
 * This function enables an application to specify which notification messages the application wants
 * to receive for events related to status changes for the specified line or any of its addresses.
 *
 * @param hLine [in] Handle to the line device.
 * @param dwLineStates [in] Specifies for which line-device status changes a message is to be sent
 *   to the application. This parameter uses the following LINEDEVSTATE_ constants: Value Description
 *   LINEDEVSTATE_OTHER Device-status items other than those listed below have changed. The
 *   application should check the current device status to determine which items have changed.
 *   LINEDEVSTATE_RINGING The switch tells the line to alert the user. Service providers notify
 *   applications on each ring cycle by sending LINE_LINEDEVSTATE messages that contains this
 *   constant. For example, in the United States, service providers send a message with this constant
 *   every six seconds. LINEDEVSTATE_CONNECTED The line was previously disconnected and is now
 *   connected to TAPI. LINEDEVSTATE_DISCONNECTED This line was previously connected and is now
 *   disconnected from TAPI. LINEDEVSTATE_MSGWAITON The "message waiting" indicator is turned on.
 *   LINEDEVSTATE_MSGWAITOFF The "message waiting" indicator is turned off. LINEDEVSTATE_INSERVICE The
 *   line is connected to TAPI. This happens when TAPI is first activated, or when the line wire is
 *   physically plugged in and in service at the switch while TAPI is active.
 *   LINEDEVSTATE_OUTOFSERVICE The line is out of service at the switch or physically disconnected.
 *   TAPI cannot be used to operate on the line device. LINEDEVSTATE_MAINTENANCE Maintenance is being
 *   performed on the line at the switch. TAPI cannot be used to operate on the line device.
 *   LINEDEVSTATE_OPEN The line has been opened by some application. LINEDEVSTATE_CLOSE The line has
 *   been closed by some application. LINEDEVSTATE_NUMCALLS The number of calls on the line device has
 *   changed. LINEDEVSTATE_NUMCOMPLETIONS The number of outstanding call completions on the line
 *   device has changed. LINEDEVSTATE_TERMINALS The terminal settings have changed.
 *   LINEDEVSTATE_ROAMMODE The roam mode of the line device has changed. LINEDEVSTATE_BATTERY The
 *   battery level has changed significantly (cellular). LINEDEVSTATE_SIGNAL The signal level has
 *   changed significantly (cellular). LINEDEVSTATE_DEVSPECIFIC The line's device-specific data has
 *   changed. LINEDEVSTATE_REINIT Items have changed in the configuration of line devices. To become
 *   aware of these changes (as with the appearance of new line devices) the application should
 *   reinitialize its use of TAPI. New lineInitialize and lineOpen requests are denied until
 *   applications have shut down their usage of TAPI. The hDevice parameter of the LINE_LINEDEVSTATE
 *   message is left NULL for this state change as it applies to any of the lines in the system.
 *   Because of the critical nature of LINEDEVSTATE_REINIT, such messages cannot be masked, so the
 *   setting of this bit is ignored and the messages are always delivered to the application.
 *   LINEDEVSTATE_LOCK The locked status of the line device has changed. LINEDEVSTATE_REMOVED
 *   Indicates that the device is being removed from the system by the service provider (most likely
 *   through user action, through a control panel or similar utility). Normally, a LINE_LINEDEVSTATE
 *   message with this value is immediately followed by a LINE_CLOSE message on the device. Subsequent
 *   attempts to access the device prior to TAPI being reinitialized result in LINEERR_NODEVICE being
 *   returned to the application. If a service provider sends a LINE_LINEDEVSTATE message that
 *   contains this value to TAPI, TAPI passes it along to applications that have negotiated TAPI
 *   version 1.4 or later; applications negotiating a previous TAPI version do not receive any
 *   notification.
 * @param dwAddressStates [in] Specifies for which address status changes a message is to be sent to
 *   the application. This parameter uses the following LINEADDRESSSTATE_ constants: Value Description
 *   LINEADDRESSSTATE_OTHER Address-status items other than those listed below have changed. The
 *   application should check the current address status to determine which items have changed.
 *   LINEADDRESSSTATE_DEVSPECIFIC The device-specific item of the address status has changed.
 *   LINEADDRESSSTATE_INUSEZERO The address has changed to idle (it is now in use by zero stations).
 *   LINEADDRESSSTATE_INUSEONE The address has changed from idle or from being in use by many bridged
 *   stations to being in use by just one station. LINEADDRESSSTATE_INUSEMANY The monitored or bridged
 *   address has changed from being in use by one station to being used by more than one station.
 *   LINEADDRESSSTATE_NUMCALLS The number of calls on the address has changed. This is the result of
 *   events such as a new incoming call, an outgoing call on the address, or a call changing its hold
 *   status. LINEADDRESSSTATE_FORWARD The forwarding status of the address has changed (including the
 *   number of rings for determining a no-answer condition). The application should check the address
 *   status to determine details about the address's current forwarding status.
 *   LINEADDRESSSTATE_TERMINALS The terminal settings for the address have changed.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_INVALADDRESSSTATE LINEERR_OPERATIONFAILED
 *   LINEERR_INVALLINEHANDLE LINEERR_OPERATIONUNAVAIL LINEERR_INVALLINESTATE LINEERR_RESOURCEUNAVAIL
 *   LINEERR_NOMEM LINEERR_UNINITIALIZED
 *
 * TAPI defines a number of messages that notify applications about events occurring on lines and
 * addresses. An application may not be interested in receiving all address and line status change
 * messages. The lineSetStatusMessages function can be used to select which messages the application
 * receives. By default, address and line status reporting is disabled.
 *
 * Prior to Windows CE version 2.12, LINEDEVSTATE_ messages are not supported.
 */
LONG WINAPI lineSetStatusMessages(
        HLINE hLine, 
        DWORD dwLineStates, 
        DWORD dwAddressStates);

LONG WINAPI lineSetTerminal(
        HLINE hLine, 
        DWORD dwAddressID,
        HCALL hCall,
        DWORD dwSelect,
        DWORD dwTerminalModes, 
        DWORD dwTerminalID, 
        DWORD  bEnable);

LONG WINAPI lineSetupConference(
        HCALL hCall,
        HLINE hLine,
        LPHCALL lphConfCall, 
        LPHCALL lphConsultCall, 
        DWORD dwNumParties,
        LPLINECALLPARAMS const lpCallParams);

LONG WINAPI lineSetupTransfer(
        HCALL hCall, 
        LPHCALL lphConsultCall,
        LPLINECALLPARAMS const lpCallParams);

/**
 * This function shuts down the application's usage of the abstraction of TAPI line API.
 *
 * @param hLineApp [in] Application's usage handle for the line API.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_INVALAPPHANDLE LINEERR_NOMEM
 *   LINEERR_RESOURCEUNAVAIL LINEERR_UNINITIALIZED
 *
 * If this function is called when the application has lines open or calls active, the call handles
 * are deleted and TAPI automatically performs the equivalent of a lineClose on each open line.
 * However, it is recommended that applications explicitly close all open lines before invoking
 * lineShutdown. If shutdown is performed while asynchronous requests are outstanding, those
 * requests are canceled.
 */
LONG WINAPI lineShutdown(
        HLINEAPP hLineApp);

LONG WINAPI lineSwapHold(
        HCALL hActiveCall, 
        HCALL hHeldCall);

LONG WINAPI lineUncompleteCall(
        HLINE hLine, 
        DWORD dwCompletionID);

LONG WINAPI lineUnhold(
        HCALL hCall);

LONG WINAPI lineUnpark(
        HLINE hLine,
        DWORD dwAddressID,
        LPHCALL lphCall, 
        LPCTSTR lpszDestAddress);

LONG WINAPI phoneClose(
        HPHONE hPhone);

LONG WINAPI phoneConfigDialog(
        DWORD dwDeviceID,
        HWND  hwndOwner,
        LPCTSTR lpszDeviceClass);


LONG WINAPI phoneDevSpecific(
        HPHONE hPhone, 
        LPVOID lpParams, 
        DWORD dwSize);

LONG WINAPI phoneGetButtonInfo(
        HPHONE hPhone, 
        DWORD dwButtonLampID, 
        LPPHONEBUTTONINFO lpButtonInfo);

LONG WINAPI phoneGetData(
        HPHONE hPhone, 
        DWORD dwDataID, 
        LPVOID lpData, 
        DWORD dwSize);

LONG WINAPI phoneGetDevCaps(
        HPHONEAPP hPhoneApp, 
        DWORD dwDeviceID,
        DWORD dwAPIVersion, 
        DWORD dwExtVersion, 
        LPPHONECAPS lpPhoneCaps);

LONG WINAPI phoneGetDisplay(
        HPHONE hPhone, 
        LPVARSTRING lpDisplay);

LONG WINAPI phoneGetGain(
        HPHONE hPhone, 
        DWORD dwHookSwitchDev, 
        LPDWORD lpdwGain);

LONG WINAPI phoneGetHookSwitch(
        HPHONE hPhone, 
        LPDWORD lpdwHookSwitchDevs);

LONG WINAPI phoneGetIcon(
        DWORD dwDeviceID,
        LPCTSTR lpszDeviceClass,
        LPHICON lphIcon);

LONG WINAPI phoneGetID(
        HPHONE hPhone, 
        LPVARSTRING lpDeviceID, 
        LPCTSTR lpszDeviceClass);

LONG WINAPI phoneGetLamp(
        HPHONE hPhone, 
        DWORD dwButtonLampID, 
        LPDWORD lpdwLampMode);

LONG WINAPI phoneGetRing(
        HPHONE hPhone, 
        LPDWORD lpdwRingMode, 
        LPDWORD lpdwVolume);

LONG WINAPI phoneGetStatus(
        HPHONE hPhone, 
        LPPHONESTATUS lpPhoneStatus);

LONG WINAPI phoneGetStatusMessages(
        HPHONE hPhone, 
        LPDWORD lpdwPhoneStates,
        LPDWORD lpdwButtonModes,
        LPDWORD lpdwButtonStates);

LONG WINAPI phoneGetVolume(
        HPHONE hPhone, 
        DWORD dwHookSwitchDev, 
        LPDWORD lpdwVolume);

LONG WINAPI phoneInitialize(
        LPHPHONEAPP   lphPhoneApp,
        HINSTANCE     hInstance,
        PHONECALLBACK lpfnCallback,
        LPCTSTR lpszAppName,
        LPDWORD       lpdwNumDevs);

LONG WINAPI phoneNegotiateAPIVersion(
        HPHONEAPP hPhoneApp,
        DWORD dwDeviceID,
        DWORD dwAPILowVersion,
        DWORD dwAPIHighVersion,
        LPDWORD lpdwAPIVersion,
        LPPHONEEXTENSIONID lpExtensionID);

LONG WINAPI phoneNegotiateExtVersion(
        HPHONEAPP hPhoneApp,
        DWORD dwDeviceID,
        DWORD dwAPIVersion,
        DWORD dwExtLowVersion,
        DWORD dwExtHighVersion,
        LPDWORD lpdwExtVersion);

LONG WINAPI phoneOpen(
        HPHONEAPP hPhoneApp, 
        DWORD dwDeviceID,
        LPHPHONE lphPhone,
        DWORD dwAPIVersion,
        DWORD dwExtVersion,
        DWORD dwCallbackInstance,
        DWORD dwPrivilege);

LONG WINAPI phoneSetButtonInfo(
        HPHONE hPhone, 
        DWORD dwButtonLampID, 
        LPPHONEBUTTONINFO const lpButtonInfo);

LONG WINAPI phoneSetData(
        HPHONE hPhone, 
        DWORD dwDataID, 
        LPVOID const lpData, 
        DWORD dwSize);

LONG WINAPI phoneSetDisplay(
        HPHONE hPhone, 
        DWORD dwRow, 
        DWORD dwColumn, 
        LPCTSTR lpsDisplay,
        DWORD dwSize);

LONG WINAPI phoneSetGain(
        HPHONE hPhone, 
        DWORD  dwHookSwitchDev, 
        DWORD  dwGain);

LONG WINAPI phoneSetHookSwitch(
        HPHONE hPhone, 
        DWORD  dwHookSwitchDevs, 
        DWORD  dwHookSwitchMode);

LONG WINAPI phoneSetLamp(
        HPHONE hPhone, 
        DWORD  dwButtonLampID, 
        DWORD  dwLampMode);

LONG WINAPI phoneSetRing(
        HPHONE hPhone, 
        DWORD  dwRingMode, 
        DWORD  dwVolume);

LONG WINAPI phoneSetStatusMessages(
        HPHONE hPhone, 
        DWORD  dwPhoneStates,
        DWORD  dwButtonModes,
        DWORD  dwButtonStates);

LONG WINAPI phoneSetVolume(
        HPHONE hPhone, 
        DWORD  dwHookSwitchDev, 
        DWORD  dwVolume);

LONG WINAPI phoneShutdown(
        HPHONEAPP hPhoneApp);

/**
 * This function displays an application-modal dialog box that enables the user to change the
 * current location, adjust location and calling card parameters, and see the effect on a phone
 * number about to be dialed.
 *
 * @param hLineApp [in] Application handle returned by lineInitialize. If you set hLineApp to NULL,
 *   this function fails and returns LINERR_INVALAPPHANDLE.
 * @param dwDeviceID [in] Specifies the device identifier for the line device upon which the call is
 *   intended to be dialed, so that variations in dialing procedures on different lines can be applied
 *   to the translation process.
 * @param dwAPIVersion [in] Specifies the highest version of TAPI supported by the application (not
 *   necessarily the value negotiated by lineNegotiateAPIVersion on the line device indicated by
 *   dwDeviceID).
 * @param hwndOwner [in] Handle to a window to which the dialog box is to be attached. Can be a NULL
 *   value to indicate that any window created during the function should have no owner window.
 * @param lpszAddressIn [in] Pointer to a null-terminated string that contains a phone number that
 *   is used, in the lower portion of the dialog box, to show the effect of the user's changes on the
 *   location parameters. The number must be in canonical format; if noncanonical, the phone number
 *   portion of the dialog box is not displayed. This pointer can be left NULL, in which case the
 *   phone number portion of the dialog box is not displayed. If the lpszAddressIn parameter contains
 *   a subaddress or name field, or additional addresses separated from the first address by ASCII CR
 *   and LF characters, only the first address is used in the dialog box.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_BADDEVICEID LINEERR_INVALPARAM
 *   LINEERR_INCOMPATIBLEAPIVERSION LINEERR_INVALPOINTER LINEERR_INIFILECORRUPT LINEERR_NODRIVER
 *   LINEERR_INUSE LINEERR_NOMEM LINEERR_INVALADDRESS LINEERR_OPERATIONFAILED LINEERR_INVALAPPHANDLE
 *   LINEERR_INUSE is returned if the dialog box is already displayed by another application (cannot
 *   be open more than once). In these versions, TAPI brings the existing dialog box to the front, and
 *   the error indicates that any particulars related to the address passed in by the current
 *   application have not been handled, because that address was not processed by the function. The
 *   application must call lineGetTranslateCaps after this function to obtain any changes the user
 *   made to the telephony address translation parameters, and call lineTranslateAddress to obtain a
 *   dialable string based on the user's new selections. If any function related to address
 *   translation (for example, lineGetTranslateCaps or lineTranslateAddress) returns
 *   LINEERR_INIFILECORRUPT, the application should call lineTranslateDialog. The lineTranslateDialog
 *   function detects the errors and corrects them, and reports the action taken to the user.
 *   LINEERR_INIFILECORRUPT is returned the first time any of these functions are used after
 *   installation of Windows CE, because the parameters are uninitialized (lineTranslateDialog takes
 *   care of initializing them, using the user-specified default country to select the default country
 *   code).
 */
LONG WINAPI lineTranslateDialog(
	HLINEAPP hLineApp,
	DWORD dwDeviceID,
	DWORD dwAPIVersion,
	HWND hwndOwner,
	LPCTSTR lpszAddressIn);

/**
 * This function causes the provider of the specified line device to display a dialog box-attached
 * to hwndOwner of the application-to enable the user to configure parameters related to the line
 * device.
 *
 * @param dwDeviceID [in] Specifies the line device to be configured.
 * @param hwndOwner [in] Handle to a window to which the dialog box is attached. Can be NULL to
 *   indicate that any window created during the function should have no owner window.
 * @param lpszDeviceClass [in] Pointer to a null-terminated string that identifies a device class
 *   name. This device class enables the application to select a specific configuration data
 *   applicable to that device class. This parameter is optional and can be left NULL, in which case
 *   the highest level configuration is selected. If an empty string is specified, the function fails
 *   and returns LINEERR_INVALDEVICECLASS.
 * @param lpDeviceConfigIn [in] Pointer to the opaque configuration data structure returned by
 *   lineGetDevConfig, or a previous invocation of lineConfigDialogEdit, in the variable portion of
 *   the VARSTRING structure.
 * @param dwSize [in] Specifies the number of bytes in the structure pointed to by lpDeviceConfigIn.
 *   This value is returned in the dwStringSize member in the VARSTRING structure returned by
 *   lineGetDevConfig or a previous invocation of lineConfigDialogEdit.
 * @param lpDeviceConfigOut [out] Pointer to the memory location of type VARSTRING, where the device
 *   configuration structure is returned. Upon successful completion of the request, this location is
 *   filled with the device configuration. The dwStringFormat member in the VARSTRING structure is set
 *   to STRINGFORMAT_BINARY. Prior to calling lineGetDevConfig, or a future call to
 *   lineConfigDialogEdit, the application should set the dwTotalSize member of this structure to
 *   indicate the amount of memory available to TAPI for returning data.
 *
 * @return Zero indicates success. A negative error number indicates that an error occurred.
 *   Possible error values are as follows: LINEERR_BADDEVICEID LINEERR_NOMEM LINEERR_INVALDEVICECLASS
 *   LINEERR_OPERATIONFAILED LINEERR_INVALPARAM LINEERR_OPERATIONUNAVAIL LINEERR_INVALPOINTER
 *   LINEERR_RESOURCEUNAVAIL LINEERR_NODEVICE LINEERR_STRUCTURETOOSMALL LINEERR_NODRIVER
 *   LINEERR_UNINITIALIZED
 *
 * If LINEERR_STRUCTURETOOSMALL is returned, the dwTotalSize member of the VARSTRING structure
 * pointed to by lpDeviceConfigOut does not specify enough memory to contain the entire
 * configuration structure. The dwNeededSize member has been set to the amount required. To the
 * extent that user entries were reflected in data that could not be returned due to insufficient
 * space, those edits are lost; an application should therefore allocate the maximum amount of
 * memory needed by the device class to return its configuration structure.
 *
 * The lineConfigDialogEdit function causes the service provider to display a modal dialog box,
 * attached to hwndOwner of the application, to enable the user to configure parameters related to
 * the line specified by dwDeviceID.
 *
 * The lpszDeviceClass parameter enables the application to select a specific subscreen of
 * configuration data applicable to the device class in which the user is interested; the permitted
 * strings are the same as for lineGetID. For example, if the line supports the Communications API,
 * passing "COMM" as lpszDeviceClass causes the provider to display the parameters related
 * specifically to Communications, or at least, start at the corresponding point in a multilevel
 * configuration dialog box chain, so the user does not have to search to find the parameters of
 * interest.
 *
 * The lpszDeviceClass parameter would be tapi/line or NULL to cause the provider to display the
 * highest level configuration for the line.
 *
 * With lineConfigDialogEdit, the parameters to edit are passed from the application, and the
 * results are returned to the application, with no impact on active connections. The results of the
 * editing are returned with this function, and the application does not need to call
 * lineGetDevConfig. Thus, lineConfigDialogEdit permits an application to provide the ability for
 * the user to set up parameters for future calls without having an impact on any active call.
 * However, the output of this function can be passed to lineSetDevConfig to affect the current call
 * or next call.
 */
LONG WINAPI lineConfigDialogEdit(
	DWORD dwDeviceID,
	HWND hwndOwner,
	LPCTSTR lpszDeviceClass,
	LPVOID const lpDeviceConfigIn,
	DWORD dwSize,
	LPVARSTRING lpDeviceConfigOut);

/**
 * This function installs a telephony service provider.
 *
 * @param lpszProviderFilename A pointer to a NULL-terminated string that contains the path of the
 *   service provider to be added.
 * @param hwndOwner A handle to a window in which any dialog boxes that need to be displayed as part
 *   of the installation process would be attached. Can be NULL to indicate that any window created
 *   during the function should have no owner window.
 * @param lpdwPermanentProviderID A pointer to a DWORD-sized memory location into which TAPI writes
 *   the permanent provider identifier of the newly installed service provider.
 *
 * @return Returns zero if the request succeeds, or a negative error number if an error occurs.
 *   Possible return values are: LINEERR_INIFILECORRUPT LINEERR_NOMEM LINEERR_INVALPARAM
 *   LINEERR_NOMULTIPLEINSTANCE LINEERR_INVALPOINTER LINEERR_OPERATIONFAILED
 *
 * In Windows CE, TAPI uses a function pointer table to call the service provider instead of using
 * exported ordinal entry points. In lineAddProvider, TAPI calls the service provider's exported
 * TSPI_lineGetProcTable function. This is the only function that a service provider need export.
 * Then TAPI calls the service provider's TSPI_providerInstall, TSPI_lineNegotiateTSPIVersion,
 * TSPI_providerInit, and TSPI_providerEnumDevices.
 */
LONG WINAPI lineAddProvider(
    LPCTSTR lpszProviderFilename,
    HWND hwndOwner,
    LPDWORD lpdwPermanentProviderID);

LONG WINAPI lineConfigProvider(
    HWND hwndOwner,
    DWORD dwPermanentProviderID);

LONG WINAPI lineRemoveProvider(
    DWORD dwPermanentProviderID,
    HWND hwndOwner);

LONG WINAPI lineGetProviderList(
    DWORD dwAPIVersion,
    LPLINEPROVIDERLIST lpProviderList);


#if defined(WINCEOEM) && defined(UNDER_CE)
#include <ptapi.h>
#ifdef WINCEMACRO
#include <mtapi.h>
#endif
#endif

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif   /* __cplusplus */

#pragma pack()

#endif // TAPI_H

// @CESYSGEN ENDIF
