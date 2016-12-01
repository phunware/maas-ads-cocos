#import <UIKit/UIKit.h>

@class RootViewController;

#ifndef app_controller_h
#define app_controller_h
@interface AppController : NSObject <UIApplicationDelegate> {

}

@property(nonatomic, readwrite) RootViewController* viewController;

@end
#endif

