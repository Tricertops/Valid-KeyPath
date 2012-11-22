//
//  MTKValidKeyPath.m
//
//  Created by Martin Kiss on 19.11.12.
//  Copyright (c) 2012 Martin Kiss. All rights reserved.
//

#import "MTKValidKeyPath.h"



@implementation NSMutableString (MTKValidKeyPath)



- (NSMutableString * (^)(NSString *))mtk_blockAppendingString {
    return ^(NSString *keyToAppend){
        if (keyToAppend.length) {
            if (self.length) [self appendString:@"."];
            [self appendString:keyToAppend];
        }
        return self;
    };
}



@end
