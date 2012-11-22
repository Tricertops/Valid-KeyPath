//
//  main.m
//  MTKValidKeyPath
//
//  Created by Martin Kiss on 21.11.12.
//  Copyright (c) 2012 iMartin Kiss. All rights reserved.
//

#import "MTKValidKeyPath.h"
#define KEY         MTK_BEGIN_KEY
#define __          MTK_APPEND_VALID_KEY
#define __unsafe    MTK_APPEND_KEY



int main(int argc, char *argv[]) {
    @autoreleasepool {
        
        
        
        NSString *keyPath = KEY.__(UIViewController, view).__(UIView, backgroundColor);
        
        
        
        NSLog(@"Key-Path: %@", keyPath);
        
        return UIApplicationMain(argc, argv, nil, nil);
    }
}
