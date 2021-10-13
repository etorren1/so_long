#import <AppKit/NSScreen.h>

void	my_get_screen_size(int *width, int *height)
{
    NSRect disp;

	disp = [[NSScreen mainScreen] frame];
    *height = (int)disp.size.height;
    *width = (int)disp.size.width;
}
