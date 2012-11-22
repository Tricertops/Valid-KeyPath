Valid Key-Path
==============


The Problem
------------
_Keys_ and _key-paths_ are quite common thing when it comes to OS X or iOS development. Many core frameworks uses or even relies on features like _Key-Value Coding_ or _Key-Value Observing_ (you know, Core Data or Bindings).

Example of key `@"view"` and key-path `@"view.superview.backgroundColor"`.

We know, that _KVC_ and _KVO_ are good and realiable features, but why a lot of programmers is trying to avoid using them massively? We know this too. Because of keys / key-paths. They are simple strings, that can handle anything and are source of troubles when it comes to refactoring. Also, since there is only runtime validiation of these keys, one typo can crash whole application:

```objc
This class is not key value coding-compliant for the key 'backgroudColor'.
```

I wanted to start heavily using _KVO_ with Core Data, so I decided to find a way to bring symbol-like features to key-paths. Impossible?



The Solution
------------
**I created a set of macros, that allows you to specify key-paths using symbols – classes and selectors.**

![image](Valid-KeyPath/README/example.png)

---



### Major Advantages: ###
1. **Just a string** – This is not a new way to use _Key-Value Coding_, but rather a new way to create strings containing key-paths. You can mix it with raw string notation (`@"key.path"`).
2. **Code completion** – When typing a selector name Xcode suggests you only selectors (keys) from class you specified.  
![image](Valid-KeyPath/README/completion.png)  
(Well, it offers you all methods from that class, but this works only with methods taking no arguments = _getters_.)
3. **Compie time validation** – If you use validating macros, Xcode will throw a compilation error once the given class does not declare given selector.  
![image](Valid-KeyPath/README/validation.png)  
(You may also use non-validating macros to aviod this, but you may lose other advantages. Use them only if you don't know the class.)
4. **Refactorable** – Last, but not least major advantage. These keys are fully refactorable using Xcode built-in tool.  
![image](Valid-KeyPath/README/refactoring.png)  
(This works only with validating macros. Non-validating macros will just show a warning during refactoring preview. Validating macros will also display refactoring warning, but you may absolutely ignore them – it will work.)
5. **This is not enough?** Check out implementation details below for what is happening under the hood.

---



#### Minor Disadvantages: ####

1. **Little more typing** – Yes, in general you hit keyboard more times than with raw key-paths. But you will hit less while refactoring or fixing stupid typos.
2. **Longer compilation** – Since macros contains some code. Project will take longer to compile – additional 0.5 second or so.
3. **Slower runtine** – Additional code will in theory add some time. Content of macros are altered on RELEASE, so there is less of it.
4. **Does these really matters?** Check out implementation details below for what is happening under the hood.

---



### How To Use & Requirements ###
1. You need to be able to use **blocks** and use of ARC is encouraged.
2. Inport the two source files located in `MTKValidKeyPath` directory in precompiled header.
3. Create aliases for these macros in some global file. See `example.m`:

```objc
#define KEY     MTK_BEGIN_KEY
#define __      MTK_APPEND_VALID_KEY
```

---



### How Does It Work ###

##### Symbol-To-String Conversion #####
Macro for converting symbol (method name) to `NSString` uses `NSStringFromSelector` function and `@selector` directive.

```objc
#define MTK_KEY(__KEY__)     (NSStringFromSelector(@selector(__KEY__)))
MTK_KEY(title)   >>>>>   NSStringFromSelector(@selector(title))
```


##### Key Validation #####
Macro for validating given key against class contains a chunk of code. Main part is `while` loop, that is breaked immediately, **so the code is not actually executed in runtime**. Inside it calls `class` method on given class and then given selector on instance of this class. This provides refactoring and compile-time validation. Returns string created by macro above.

```objc
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
```


##### Key-Path Creation #####
Simple contructor of `NSMutableString` that also cast the resulting object.

```objc
#define MTK_BEGIN_KEY   ((NSMutableString *)[NSMutableString string])
```


##### Key-Path Chaining #####
Key-path chaining uses dot syntax and blocks. You call method returning block and immediately executing the block with argument in parenthesis. This instance method is added to `NSMutableString` class in category. This block appends given argument to the receiver and returns it, so you can continue chaining.

```objc
- (NSMutableString * (^)(NSString *))mtk_blockAppendingString;

mutableString.mtk_blockAppendingString(@"part1").mtk_blockAppendingString(@"part2");
```

---

_That awkward moment, when README is longer than the source code._
