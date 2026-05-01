/* stub libintl.h for systems without gettext */
#ifndef _LIBINTL_H
#define _LIBINTL_H

#define gettext(s)	((char *)(s))
#define textdomain(d)	((void) d)

#endif
