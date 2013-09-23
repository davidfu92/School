// ext3grep -- An ext3 file system investigation and undelete tool
// src/timestamp-sys.h.  Generated from sys.h.in by configure.
// This file contains operating system header workarounds and application
// wide macro definitions related to third party libraries and/or compilation
// in general.
//
// Copyright (C) 2008, by
// 
// Carlo Wood, Run on IRC <carlo@alinoe.com>
// RSA-1024 0x624ACAD5 1997-01-26                    Sign & Encrypt
// Fingerprint16 = 32 EC A7 B6 AC DB 65 A6  F6 F6 55 DD 1C DC FF 61
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SYS_H
#define SYS_H

#if HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef CWDEBUG
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifdef USE_LIBCW
#include <libcw/sys.h>
#else
#include <libcwd/sys.h>
#endif
#endif

#define UNUSED(x)

// Compilers and preprocessor used.  Put here to cause a recompile when changed.
// CC    : gcc version 4.4.7 20120313 (Red Hat 4.4.7-3) (GCC) 
// CXX   : gcc version 4.4.7 20120313 (Red Hat 4.4.7-3) (GCC) 
// CXXCPP: gcc version 4.4.7 20120313 (Red Hat 4.4.7-3) (GCC) 
//
// Also cause a full recompile when the definition of CWDEBUG is changed.
// CWDEBUG: no
//
// Also cause a full recompile if CXXFLAGS is changed.
// CXXFLAGS: -g -DDEBUG -DUSE_MMAP=1 -I/usr/include/ext2fs -I/usr/include/et

#endif // SYS_H
