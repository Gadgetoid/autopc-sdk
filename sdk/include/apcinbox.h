/****************************************************************************
* Copyright (c) 1998 Microsoft Corporation, All rights reserved.
****************************************************************************
* APCInbox.h    - Contains platform specific information for the AutoPC Inbox
*
* Notes:        Additional header fields used by AutoPC Wireless 
*               application are:
*
*               Type    -   Indicates the type of message. Currently optional
*                           for 'Email', 'Traffic', and 'News' messages.  
*                           However, this is used to determine messages of
*                           type 'Page'.  If this is not present, 'Email' is
*                           assummed.
*
*               Status  -   This can be either 'read', 'unread' or 'new'. If
*                           this field is not present, the message is assumed
*                           to be new.
*
****************************************************************************/
#ifndef __APCINBOX_H__
#define	__APCINBOX_H__

// msg type flags
#define MSG_EMAIL   0           // default
#define MSG_PAGE    1
#define MSG_TRAFFIC 2
#define MSG_NEWS    3

// folders - Email and pages will be using the inbox
#define MAIL_FOLDER_TRAFFIC 18  // szName will be "Traffic"
#define MAIL_FOLDER_NEWS    19  // szName will be "News"

// msg status flags
#define MSG_UNREAD  0
#define MSG_READ    1
#define MSG_NEW     2
#define MSG_SAVE    4

#define MSG_NOT_SAVE        (MAIL_STATUS_NOT|MAIL_STATUS_LOCKED)

#endif // __APCINBOX_H__
