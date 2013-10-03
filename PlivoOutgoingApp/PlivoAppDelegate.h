//
//  PlivoAppDelegate.h
//  PlivoOutgoingApp
//
//  Created by Iwan BK on 10/2/13.
//  Copyright (c) 2013 Plivo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PlivoViewController.h"
#import "Phone.h"

@interface PlivoAppDelegate : UIResponder <UIApplicationDelegate>

@property (nonatomic, retain) IBOutlet PlivoViewController* viewController;

@property Phone *phone;

@property (strong, nonatomic) UIWindow *window;

@end
