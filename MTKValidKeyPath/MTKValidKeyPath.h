//
//  MTKValidKeyPath.h
//
//  Created by Martin Kiss on 19.11.12.
//  Copyright (c) 2012 Martin Kiss. All rights reserved.
//

#import <Foundation/Foundation.h>



/// Turn validation on/off.
#ifdef DEBUG
    #define MTK_VALIDATE_KEYS
#else
    #undef MTK_VALIDATE_KEYS
#endif



/// Conversion from symbol to string. Completes and warns on refactoring.
#define MTK_KEY(__KEY__)     (NSStringFromSelector(@selector(__KEY__)))

/// Conversion from symbol to string by validating against instance of given class. Completes, warns on refactoring and throws compilation error if the given method was not found.
#ifdef MTK_VALIDATE_KEYS
/// DEBUG
#define MTK_VALID_KEY(__CLASS__, __KEY__)                   \
({                                                          \
    while (1) {                                             \
        break;                                              \
        [__CLASS__ class];                                  \
        __CLASS__ * instance = nil;                         \
        [instance __KEY__];                                 \
    }                                                       \
    MTK_KEY(__KEY__);                                       \
})
#else
/// NOT DEBUG
#define MTK_VALID_KEY(__CLASS_, __KEY__)    MTK_KEY(__KEY__)
#endif

/// Alias for method `mtk_blockAppendingString` that does not validate the key.
#define MTK_APPEND_KEY(__KEY__)     mtk_blockAppendingString(MTK_KEY(__KEY__))

/// Alias for method `mtk_blockAppendingString` that validates the key.
#define MTK_APPEND_VALID_KEY(__CLASS__, __KEY__)     mtk_blockAppendingString(MTK_VALID_KEY(__CLASS__, __KEY__))

/// Constructor for key-path that can be used for dot syntax.
#define MTK_BEGIN_KEY   ((NSMutableString *)[NSMutableString string])



@interface NSMutableString (MTKValidKeyPath)

/// Method returning block, that can be used for easy dot syntax.
- (NSMutableString * (^)(NSString *))mtk_blockAppendingString;

@end


