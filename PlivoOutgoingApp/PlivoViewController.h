//
//  PlivoViewController.h
//  PlivoOutgoingApp
//
//  Created by Iwan BK on 10/2/13.
//  Copyright (c) 2013 Plivo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PlivoEndpoint.h"
#import "Phone.h"

@interface PlivoViewController : UIViewController<PlivoEndpointDelegate, UITextViewDelegate, UITextFieldDelegate>

@property Phone *phone;

@end
