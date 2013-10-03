//
//  Phone.h
//  PlivoOutgoingApp
//
//  Created by Iwan BK on 10/2/13.
//  Copyright (c) 2013 Plivo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PlivoEndpoint.h"

@interface Phone : NSObject

- (void)login;

- (PlivoOutgoing *)call:(NSString *)dest;

- (void)setDelegate:(id)delegate;

@end
