/*  =========================================================================
    zsys - system-level methods

    -------------------------------------------------------------------------
    Copyright (c) 1991-2014 iMatix Corporation <www.imatix.com>
    Copyright other contributors as noted in the AUTHORS file.

    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the 
    Free Software Foundation; either version 3 of the License, or (at your 
    option) any later version.

    This software is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABIL-
    ITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General 
    Public License for more details.

    You should have received a copy of the GNU Lesser General Public License 
    along with this program. If not, see <http://www.gnu.org/licenses/>.
    =========================================================================
*/

#ifndef __ZSYS_H_INCLUDED__
#define __ZSYS_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  @interface
#define UDP_FRAME_MAX   255         //  Max size of UDP frame

//  Callback for interrupt signal handler
typedef void (zsys_handler_fn) (int signal_value);

//  Set interrupt handler (NULL means external handler)
CZMQ_EXPORT void
    zsys_handler_set (zsys_handler_fn *handler_fn);

//  Reset interrupt handler, call this at exit if needed
CZMQ_EXPORT void
    zsys_handler_reset (void);

//  Set network interface name to use for broadcasts
//  Use this to force the interface for beacons
//  This is experimental; may be merged into zbeacon class.
CZMQ_EXPORT void
    zsys_set_interface (const char *interface_name);

//  Return network interface name to use for broadcasts.
//  Returns "" if no interface was set.
//  This is experimental; may be merged into zbeacon class.
CZMQ_EXPORT char *
    zsys_interface (void);

//  Return 1 if file exists, else zero
CZMQ_EXPORT bool
    zsys_file_exists (const char *filename);

//  Return size of file, or -1 if not found
CZMQ_EXPORT ssize_t
    zsys_file_size (const char *filename);

//  Return file modification time. Returns 0 if the file does not exist.
CZMQ_EXPORT time_t
    zsys_file_modified (const char *filename);

//  Return file mode
CZMQ_EXPORT mode_t
    zsys_file_mode (const char *filename);

//  Delete file. Does not complain if the file is absent
CZMQ_EXPORT int
    zsys_file_delete (const char *filename);

//  Check if file is 'stable'
CZMQ_EXPORT bool
    zsys_file_stable (const char *filename);

//  Create a file path if it doesn't exist. The file path is treated as a 
//  printf format.
CZMQ_EXPORT int
    zsys_dir_create (const char *pathname, ...);

//  Remove a file path if empty; the pathname is treated as printf format.
CZMQ_EXPORT int
    zsys_dir_delete (const char *pathname, ...);

//  Set private file creation mode; all files created from here will be
//  readable/writable by the owner only.
CZMQ_EXPORT void
    zsys_file_mode_private (void);

//  Reset default file creation mode; all files created from here will use
//  process file mode defaults.
CZMQ_EXPORT void
    zsys_file_mode_default (void);

//  Return the czmq version for run-time API detection
CZMQ_EXPORT void
    zsys_version (int *major, int *minor, int *patch);

//  Format a string with variable arguments, returning a freshly allocated
//  buffer. If there was insufficient memory, returns NULL. Free the returned
//  string using zstr_free().
CZMQ_EXPORT char *
    zsys_vprintf (const char *format, va_list argptr);

//  Create UDP beacon socket; if the routable option is true, uses
//  multicast (not yet implemented), else uses broadcast. This method
//  and related ones might _eventually_ be moved to a zudp class.
CZMQ_EXPORT SOCKET
    zsys_udp_new (bool routable);

//  Send zframe to UDP socket
CZMQ_EXPORT void
    zsys_udp_send (SOCKET udpsock, zframe_t *frame, inaddr_t *address);

//  Receive zframe from UDP socket, and set address of peer that sent it
//  The peername must be a char [INET_ADDRSTRLEN] array.
CZMQ_EXPORT zframe_t *
    zsys_udp_recv (SOCKET udpsock, char *peername);

//  Handle an I/O error on some socket operation; will report and die on
//  fatal errors, and continue silently on "try again" errors.
CZMQ_EXPORT void
    zsys_socket_error (const char *reason);
    
//  Self test of this class
CZMQ_EXPORT int
    zsys_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
