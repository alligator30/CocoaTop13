#import <mach/mach_types.h>
#import <sys/sysctl.h>
#import <UIKit/UIKit.h>

// Thread states are sorted by priority, top priority becomes a "task state"
typedef enum {
	ProcStateDebugging,
	ProcStateZombie,
	ProcStateRunning,
	ProcStateUninterruptible,
	ProcStateSleeping,
	ProcStateIndefiniteSleep,
	ProcStateTerminated,
	ProcStateHalted,
	ProcStateMax
} proc_state_t;

#define PROC_STATE_CHARS "DZRUSITH?"

// Display states determine grid row colors
typedef enum {
	ProcDisplaySystem,
	ProcDisplayUser,
	ProcDisplayNormal,
	ProcDisplayStarted,
	ProcDisplayTerminated,
	ProcDisplayRemove
} display_t;

@interface PSProc : NSObject
{
@public struct task_basic_info basic;
@public struct task_events_info events;
@public struct task_events_info events_prev;
}
@property (assign) display_t display;
@property (assign) pid_t pid;
@property (assign) pid_t ppid;
@property (assign) unsigned int prio;
@property (assign) unsigned int priobase;
@property (assign) task_role_t role;
@property (assign) int nice;
@property (assign) unsigned int flags;
@property (assign) unsigned int ptime;	// 100's of a second
@property (assign) dev_t tdev;
@property (assign) uid_t uid;
@property (assign) gid_t gid;
@property (assign) proc_state_t state;
@property (assign) unsigned int pcpu;
@property (assign) unsigned int threads;
@property (assign) unsigned int ports;
@property (retain) NSString *name;
@property (retain) NSArray *args;
@property (retain) UIImage *icon;
@property (retain) NSDictionary *app;
+ (instancetype)psProcWithKinfo:(struct kinfo_proc *)ki iconSize:(CGFloat)size;

@end

@interface PSProcArray : NSObject
@property (retain) NSMutableArray *procs;
@property (assign) CGFloat iconSize;
@property (assign) unsigned int totalCpu;
@property (assign) unsigned int threadCount;
@property (assign) uint64_t memUsed;
@property (assign) uint64_t memFree;
@property (assign) uint64_t memTotal;
+ (instancetype)psProcArrayWithIconSize:(CGFloat)size;
- (int)refresh;
- (void)sortUsingComparator:(NSComparator)comp desc:(BOOL)desc;
- (void)setAllDisplayed:(display_t)display;
- (NSUInteger)indexOfDisplayed:(display_t)display;
- (NSUInteger)count;
- (PSProc *)objectAtIndexedSubscript:(NSUInteger)idx;
- (PSProc *)procForPid:(pid_t)pid;

@end
