//
//  PlivoEndpoint.h
//  PlivoEndpoint
//
//  Copyright (c) 2013 Plivo Inc. All rights reserved.
//  Use of this software is subject to the
//  terms mentioned here, http://plivo.com/terms/

#include "PlivoIncoming.h"
#include "PlivoOutgoing.h"
#include "PlivoRest.h"

typedef enum
{
    UnRegistered = 0,
    Registered
} PlivoEndpointState;

@class PlivoEndpoint;

// defining a protocol
@protocol PlivoEndpointDelegate<NSObject>

@optional
/* This delegate gets called when registration to an endpoint is successful.
 */
- (void)onLogin;

/* This delegate gets called when registration to an endpoint fails.
 */
- (void)onLoginFailed;

/* On an incoming call to a registered endpoint, this delegate receives
 a PlivoIncoming object.
 */
- (void)onIncomingCall:(PlivoIncoming *)incoming;

/* On an incoming call, if the call is disconnected by the caller, this delegate
 would be triggered with the PlivoIncoming object.
 */
- (void)onIncomingCallRejected:(PlivoIncoming *)incoming;

/* On an incoming call, if the call is disconnected by the caller after being answered,
 this delegate would be triggered with the PlivoIncoming object.
 */
- (void)onIncomingCallHangup:(PlivoIncoming *)incoming;

/* On an active endpoint, this delegate would be called with the digit
 received on the call.
 */
- (void)onIncomingDigit:(NSString *)digit;

/* When an outgoing call is answered, this delegate would be called with
 the PlivoOutgoing object
 */
- (void)onOutgoingCallAnswered:(PlivoOutgoing *)call;

/* When an outgoing call is ringing, this delegate would be called with
 the PlivoOutgoing object
 */
- (void)onOutgoingCallRinging:(PlivoOutgoing *)call;

/* When an outgoing call is rejected by the called number, this
 delegate would be called with the PlivoOutgoing object
 */
- (void)onOutgoingCallRejected:(PlivoOutgoing *)call;

/* When an outgoing call is made to an invalid number, this
 delagate would be called with the PlivoOutgoing object
 */
- (void)onOutgoingCallInvalid:(PlivoOutgoing *)call;

/* When an outgoing call is disconnected by the called number after the call
 has been answered
 */
- (void)onOutgoingCallHangup:(PlivoOutgoing *)call;


@end


@interface PlivoEndpoint : NSObject {
    PlivoEndpointState state;
}

/* The delegate object on which events will be received.
 */
@property (nonatomic, assign) id delegate;
@property (nonatomic, readwrite) PlivoAccId accId;


/* Registers an endpoint
 
 Calling this method with the username and password of your SIP endpoint would
 register the endpoint.
 */
- (void)login:(NSString *)username AndPassword:(NSString *)password;

/* Register an endpoint with extra headers
 Alternatively you can register an endpoint with with your very own custom headers
 */

- (void)login:(NSString *)username AndPassword:(NSString *)password AndHeaders:(NSDictionary *)headers;

/* Unregisters an endpoint
 
 Calling this method with would unregister the SIP endpoint
 */
- (void)logout;

/* Create an Outgoing Call Object
 
 Calling this method would return an PlivoOutgoing object,
 linked to the registered endpoint. Calling this method on an unregistered PlivoEndpoint
 object would return an empty object.
 */
- (PlivoOutgoing *)createOutgoingCall;

/* Disconnect a call
 
 Calling this method would disconnect the call in progress. This can be
 used with the call id.
 */
- (void)hangup:(PlivoCallId)callId;

/* Notifications */
- (void)onLoginNotification;
- (void)onLoginFailedNotification;

- (void)onIncomingCallNotification:(PlivoIncoming *)incoming;
- (void)onIncomingCallRejectedNotification:(PlivoIncoming *)incoming;
- (void)onIncomingCallHangupNotification:(PlivoIncoming *)incoming;

- (void)onIncomingDigitNotification:(NSString *)digit;

- (void)onOutgoingCallRingingNotification:(PlivoOutgoing *)outgoing;
- (void)onOutgoingCallAnsweredNotification:(PlivoOutgoing *)outgoing;
- (void)onOutgoingCallRejectedNotification:(PlivoOutgoing *)outgoing;
- (void)onOutgoingCallInvalidNotification:(PlivoOutgoing *)outgoing;
- (void)onOutgoingCallHangupNotification:(PlivoOutgoing *)outgoing;


@end

