//
//  Phone.m
//  PlivoOutgoingApp
//
//  Created by Iwan BK on 10/2/13.
//  Copyright (c) 2013 Plivo. All rights reserved.
//

#import "Phone.h"
#import "PlivoEndpoint.h"

@implementation Phone {
    PlivoEndpoint *endpoint;
}

- (id) init
{
    self = [super init];
    
    if (self) {
        endpoint = [[PlivoEndpoint alloc] init];
    }
    
    return self;
}

- (void)login
{
#warning Change to valid plivo endpoint username and password.
    NSString *username = @"plivousername";
    NSString *password = @"plivopassword";
    [endpoint login:username AndPassword:password];
}

- (PlivoOutgoing *)call:(NSString *)dest
{
    NSString *sipUri = [[NSString alloc]initWithFormat:@"sip:%@@phone.plivo.com", dest];
    PlivoOutgoing *outCall = [endpoint createOutgoingCall];
    [outCall call:sipUri];
    return outCall;
}

- (void)setDelegate:(id)delegate
{
    [endpoint setDelegate:delegate];
}

@end
