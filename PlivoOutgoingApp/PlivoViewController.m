//
//  PlivoViewController.m
//  PlivoOutgoingApp
//
//  Created by Iwan BK on 10/2/13.
//  Copyright (c) 2013 Plivo. All rights reserved.
//

#import "PlivoViewController.h"

@interface PlivoViewController ()

@property (weak, nonatomic) IBOutlet UIButton *callBtn;
@property (weak, nonatomic) IBOutlet UIButton *hangupBtn;
@property (weak, nonatomic) IBOutlet UITextView *logTextView;
@property (weak, nonatomic) IBOutlet UITextField *textField;

- (IBAction)makeCall:(id)sender;
- (IBAction)hangupCall:(id)sender;

@end

@implementation PlivoViewController {
    PlivoOutgoing *outCall;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    /* disable call & hangup button */
    [self.hangupBtn setEnabled:NO];
    [self.callBtn setEnabled:NO];
    
    /* set delegate for debug log text view */
    self.logTextView.delegate = self;
    
    /* Login */
    [self.logTextView setText:@"- Logging in\n"];
    [self.phone login];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)textFieldShouldReturn:(UITextField *)theTextField {
    if (theTextField == self.textField) {
        [theTextField resignFirstResponder];
    }
    return YES;
}

/**
 * To hide keyboard when text view being clicked
 */
- (BOOL)textViewShouldBeginEditing:(UITextView *)textView
{
    return NO;
}

- (void)logDebug:(NSString *)message
{
    if ( ![NSThread isMainThread] )
	{
        [self performSelectorOnMainThread:@selector(logDebug:) withObject:message waitUntilDone:NO];
		return;
	}
    NSString *toLog = [[NSString alloc] initWithFormat:@"%@\n",message];
    [self.logTextView insertText:toLog];
    
	//Scroll textview
	[self.logTextView scrollRangeToVisible:NSMakeRange([self.logTextView.text length], 0)];
}


- (void)onLogin
{
    [self logDebug:@"- Login OK"];
    [self logDebug:@"- Ready to make a call"];
    [self enableCallDisableHangupBtn];
}

- (void)onLoginFailed
{
    [self logDebug:@"- Login failed. Please check your username and password"];
}

- (IBAction)makeCall:(id)sender {
    NSString *dest = [self.textField text];
    if (dest.length == 0) {
        [self logDebug:@"- Please enter SIP URI or Phone Number"];
        return;
    }
    
    NSString *debugStr = [[NSString alloc]initWithFormat:@"- Make a call to '%@'", dest];
    [self logDebug:debugStr];
    
    //make the call
    outCall = [self.phone call:dest];
    
    //enable hangup button and disable call button
    [self enableHangupDisableCallBtn];
}

- (IBAction)hangupCall:(id)sender {
    [self logDebug:@"- Hangup the call"];
    
    [outCall disconnect];
    
    //disable hangup button and enable call button
    [self enableCallDisableHangupBtn];
}

- (void)enableCallDisableHangupBtn
{
    [self.hangupBtn setEnabled:NO];
    [self.callBtn setEnabled:YES];
}

- (void)enableHangupDisableCallBtn
{
    [self.hangupBtn setEnabled:YES];
    [self.callBtn setEnabled:NO];
}

- (void)onOutgoingCallAnswered:(PlivoOutgoing *)call
{
    NSLog(@"call answered");
    [self logDebug:@"- On outgoing call answered"];
}

- (void)onOutgoingCallHangup:(PlivoOutgoing *)call
{
    [self logDebug:@"- On outgoing call hangup"];
    
    [self enableCallDisableHangupBtn];
}

- (void)onOutgoingCallRinging:(PlivoOutgoing *)call
{
    [self logDebug:@"- On outgoing call ringing"];
}

- (void)onOutgoingCallRejected:(PlivoOutgoing *)call
{
    [self logDebug:@"- On outgoing call rejected"];
    NSLog(@"On outgoing call rejected");
    [self enableCallDisableHangupBtn];
}

- (void)onOutgoingCallInvalid:(PlivoOutgoing *)call
{
    [self logDebug:@"- On outgoing call invalid"];
    
    [self enableCallDisableHangupBtn];
}
@end
