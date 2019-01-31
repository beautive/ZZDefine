//
//  ZZDefine.h
//  ZZDefine
//
//  Created by dengtacj on 2019/1/31.
//  Copyright © 2019年 zz. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZZDefine : NSObject

// App Frame
#define Application_Frame      [[UIScreen mainScreen] applicationFrame]

// App Frame Height&Width
#define App_Frame_Height        [[UIScreen mainScreen] applicationFrame].size.height
#define App_Frame_Width        [[UIScreen mainScreen] applicationFrame].size.width

// MainScreen Height&Width
#define Main_Screen_Height      [[UIScreen mainScreen] bounds].size.height
#define Main_Screen_Width      [[UIScreen mainScreen] bounds].size.width


// View 坐标(x,y)和宽高(width,height)
#define X(v)                   (v).frame.origin.x
#define Y(v)                   (v).frame.origin.y

#define WIDTH(v)               (v).frame.size.width
#define HEIGHT(v)              (v).frame.size.height

#define MinX(v)                CGRectGetMinX((v).frame)
#define MinY(v)                CGRectGetMinY((v).frame)

#define MidX(v)                CGRectGetMidX((v).frame)
#define MidY(v)                CGRectGetMidY((v).frame)

#define MaxX(v)                CGRectGetMaxX((v).frame)
#define MaxY(v)                CGRectGetMaxY((v).frame)

// 系统控件默认高度
#define StatusBarHeight        (20.f)
#define TopBarHeight           (44.f)
#define BottomBarHeight        (49.f)
#define CellDefaultHeight      (44.f)
#define EnglishKeyboardHeight  (216.f)
#define ChineseKeyboardHeight  (252.f)

// 沙盒路径
#define PATH_OF_APP_HOME    NSHomeDirectory()
#define PATH_OF_TEMP        NSTemporaryDirectory()
#define PATH_OF_DOCUMENT    [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]

// 加载图片
#define PNGIMAGE(NAME)          [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:(NAME) ofType:@"png"]]
#define JPGIMAGE(NAME)          [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:(NAME) ofType:@"jpg"]]
#define IMAGE(NAME, EXT)        [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:(NAME) ofType:(EXT)]]


// 颜色(RGB)
#define RGBCOLOR(r, g, b)      [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:1]
#define RGBACOLOR(r, g, b, a)  [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:(a)]
// 随机颜色
#define RANDOM_UICOLOR    [UIColor colorWithRed:arc4random_uniform(256) / 255.0 green:arc4random_uniform(256) / 255.0 blue:arc4random_uniform(256) / 255.0 alpha:1]



// View 圆角和加边框
#define ViewBorderRadius(View, Radius, Width, Color)\
\
[View.layer setCornerRadius:(Radius)];\
[View.layer setMasksToBounds:YES];\
[View.layer setBorderWidth:(Width)];\
[View.layer setBorderColor:[Color CGColor]]

// View 圆角
#define ViewRadius(View, Radius)\
\
[View.layer setCornerRadius:(Radius)];\
[View.layer setMasksToBounds:YES]


// 当前语言
#define CURRENTLANGUAGE        ([[NSLocale preferredLanguages] objectAtIndex:0])



// 本地化字符串
/** NSLocalizedString宏做的其实就是在当前bundle中查找资源文件名“Localizable.strings”(参数:键＋注释) */
#define LocalString(x, ...)    NSLocalizedString(x, nil)
/** NSLocalizedStringFromTable宏做的其实就是在当前bundle中查找资源文件名“xxx.strings”(参数:键＋文件名＋注释) */
#define AppLocalString(x, ...)  NSLocalizedStringFromTable(x, @"someName", nil)



// 时间间隔
#define kHUDDuration            (1.f)
// 一天的秒数
#define SecondsOfDay            (24.f * 60.f * 60.f)
// 秒数
#define Seconds(Days)          (24.f * 60.f * 60.f * (Days))
// 一天的毫秒数
#define MillisecondsOfDay      (24.f * 60.f * 60.f * 1000.f)
// 毫秒数
#define Milliseconds(Days)      (24.f * 60.f * 60.f * 1000.f * (Days))



// app 信息
#define VERSION            [[[NSBundle mainBundle] infoDictionary] valueForKey:@"CFBundleShortVersionString"]



// block self (deprecated  不推荐使用 仿苹果提示关键字，😆)
#define BlockWeakObject(o) __typeof(o) __weak
#define BlockWeakSelf BlockWeakObject(self)



// 推荐使用（摘自YYKit）
/**
 Synthsize a weak or strong reference.
 
 Example:
 @weakify(self)
 [self doSomething^{
 @strongify(self)
 if (!self) return;
 ...
 }];
 
 */
#ifndef weakify
#if DEBUG
#if __has_feature(objc_arc)
#define weakify(object) autoreleasepool{} __weak __typeof__(object) weak##_##object = object;
#else
#define weakify(object) autoreleasepool{} __block __typeof__(object) block##_##object = object;
#endif
#else
#if __has_feature(objc_arc)
#define weakify(object) try{} @finally{} {} __weak __typeof__(object) weak##_##object = object;
#else
#define weakify(object) try{} @finally{} {} __block __typeof__(object) block##_##object = object;
#endif
#endif
#endif

#ifndef strongify
#if DEBUG
#if __has_feature(objc_arc)
#define strongify(object) autoreleasepool{} __typeof__(object) object = weak##_##object;
#else
#define strongify(object) autoreleasepool{} __typeof__(object) object = block##_##object;
#endif
#else
#if __has_feature(objc_arc)
#define strongify(object) try{} @finally{} __typeof__(object) object = weak##_##object;
#else
#define strongify(object) try{} @finally{} __typeof__(object) object = block##_##object;
#endif
#endif
#endif





// 自定义NSLog,在debug模式下打印，在release模式下取消一切NSLog
#ifdef DEBUG
#define NSLog(FORMAT, ...) fprintf(stderr,"%s:%d\t%s\n",[[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String], __LINE__, [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);
#else
#define NSLog(FORMAT, ...) nil
#endif


// 判断机型
#define kDevice_Is_iPhone5 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) : NO)
#define kDevice_Is_iPhone6 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(750, 1334), [[UIScreen mainScreen] currentMode].size) : NO)
#define kDevice_Is_iPhone6Plus ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1242, 2208), [[UIScreen mainScreen] currentMode].size) : NO)



// alert
#define Alert(_S_, ...)    [[[UIAlertView alloc] initWithTitle:@"提示" message:[NSString stringWithFormat:(_S_), ##__VA_ARGS__] delegate:nil cancelButtonTitle:@"知道了" otherButtonTitles:nil] show]


#define SINGLETON_FOR_HEADER(className) \
\
+ (className *)shared##className;

#define SINGLETON_FOR_IMPLEMENTATION(className) \
\
+ (className *)shared##className { \
static className *shared##className = nil; \
static dispatch_once_t onceToken; \
dispatch_once(&onceToken, ^{ \
shared##className = [[self alloc] init]; \
}); \
return shared##className; \
}

// 通知相关
#define ADD_OBSERVER(_selector,_name) \
ADD_OBSERVER_WITH_OBJECT(_selector, _name, nil)
//post
#define POST_NOTIFICATION_WITH_OBJECT_AND_INFO(_name, _object, _info) \
([[NSNotificationCenter defaultCenter] postNotificationName:_name object:_object userInfo:(_info)])
#define POST_NOTIFICATION(_name) \
POST_NOTIFICATION_WITH_OBJECT_AND_INFO(_name, nil, nil)
#define POST_NOTIFICATION_WITH_OBJECT(_name, _object) \
POST_NOTIFICATION_WITH_OBJECT_AND_INFO(_name, _object, nil)
#define POST_NOTIFICATION_WITH_INFO(_name, _info) \
POST_NOTIFICATION_WITH_OBJECT_AND_INFO(_name, nil, _info)
//remove
#define REMOVE_OBSERVER(_name) \
([[NSNotificationCenter defaultCenter] removeObserver:self name:_name object:nil])
#define REMOVE_ALL_OBSERVERS(_self) \
([[NSNotificationCenter defaultCenter] removeObserver:_self])


// 检查字符串是否为空(PS：这里认为nil," ", "\n"均是空)
#define strIsEmpty(str)      (str==nil || [str length]==0 || [[str stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] length] == 0)

// trim string
#define TRIM_STRING(_string) (\
(OBJECT_IS_EMPTY(_string) || NO == [_string isKindOfClass:[NSString class]]) ? \
@"" : [_string stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] \
)

//  检查空对象
#define OBJECT_IS_EMPTY(_object) (_object == nil \
|| [_object isKindOfClass:[NSNull class]] \
|| ([_object respondsToSelector:@selector(length)] && [(NSData *)_object length] == 0) \
|| ([_object respondsToSelector:@selector(count)]  && [(NSArray *)_object count] == 0))
#define OBJECT_ISNOT_EMPTY(_object) (NO == OBJECT_IS_EMPTY(_object))
#define RETURN_WHEN_OBJECT_IS_EMPTY(_object)        if (OBJECT_IS_EMPTY(_object)) { return ;    }
#define RETURN_NIL_WHEN_OBJECT_IS_EMPTY(_object)    if (OBJECT_IS_EMPTY(_object)) { return nil; }
#define RETURN_EMPTY_WHEN_OBJECT_IS_EMPTY(_object)  if (OBJECT_IS_EMPTY(_object)) { return @""; }
#define RETURN_YES_WHEN_OBJECT_IS_EMPTY(_object)    if (OBJECT_IS_EMPTY(_object)) { return YES; }
#define RETURN_NO_WHEN_OBJECT_IS_EMPTY(_object)    if (OBJECT_IS_EMPTY(_object)) { return NO; }
#define RETURN_ZERO_WHEN_OBJECT_IS_EMPTY(_object)  if (OBJECT_IS_EMPTY(_object)) { return 0; }


/** 快速查询一段代码的执行时间 */
/** 用法
 TICK
 do your work here
 TOCK
 */

#define TICK NSDate *startTime = [NSDate date];
#define TOCK NSLog(@"Time:%f", -[startTime timeIntervalSinceNow]);



//由角度转换弧度 由弧度转换角度
#define DegreesToRadian(x) (M_PI * (x) / 180.0)
#define RadianToDegrees(radian) (radian*180.0)/(M_PI)



/*
 *  根据当前view 找所在tableview 里的 indexpath
 */
#define INDEXPATH_SUBVIEW_TABLEVIEW(subview,tableview)\
({\
CGRect subviewFrame = [subview convertRect:subview.bounds toView:tableview];\
NSIndexPath *tabIndexPath = [tableview indexPathForRowAtPoint:subviewFrame.origin];\
tabIndexPath;\
})\

/*
 *  根据当前view 找所在collectionview 里的 indexpath
 */
#define INDEXPATH_SUBVIEW_COLLECTION(subview,collectionview)\
({\
CGRect subviewFrame = [subview convertRect:subview.bounds toView:collectionview];\
NSIndexPath *tabIndexPath = [collectionview indexPathForItemAtPoint:subviewFrame.origin];\
tabIndexPath;\
})\


/*
 *  根据当前view 找所在tableview 里的 tableviewcell
 */
#define CELL_SUBVIEW_TABLEVIEW(subview,tableview)\
({\
CGRect subviewFrame = [subview convertRect:subview.bounds toView:tableview];\
NSIndexPath *indexPath = [tableview indexPathForRowAtPoint:subviewFrame.origin];\
UITableViewCell *tabCell  = [tableview cellForRowAtIndexPath:indexPath];\
tabCell;\
})\



@end

NS_ASSUME_NONNULL_END
