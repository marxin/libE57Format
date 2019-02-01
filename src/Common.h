#ifndef COMMON_P_H
#define COMMON_P_H

/*
 * Copyright 2009 - 2010 Kevin Ackley (kackley@gwi.net)
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Define the following symbol adds some functions to the API for implementation purposes.
// These functions are not available to a normal API user.
#define E57_INTERNAL_IMPLEMENTATION_ENABLE 1
#include "E57Format.h"

// Uncomment the lines below to enable various levels of cross checking and verification in the code.
// The extra code does not change the file contents.
// Recommend that E57_DEBUG remain defined even for production versions.
#define E57_DEBUG       1
//#define E57_MAX_DEBUG   1

// Uncomment the lines below to enable various levels of printing to the console of what is going on in the code.
//#define E57_VERBOSE     1
//#define E57_MAX_VERBOSE 1

// Uncomment the line below to enable writing packets that are correct but will stress the reader.
//#define E57_WRITE_CRAZY_PACKET_MODE 1

#ifdef _MSC_VER
// Disable MSVC warning: warning C4224: nonstandard extension used : formal parameter 'locale' was previously defined as a type
#pragma warning( disable : 4224)
#endif

namespace e57 {

//!!! inline these rather than macros?
#define E57_EXCEPTION1(ecode) (E57Exception((ecode), ustring(), __FILE__, __LINE__, static_cast<const char *>(__FUNCTION__)))
#define E57_EXCEPTION2(ecode, context) (E57Exception((ecode), (context), __FILE__, __LINE__, static_cast<const char *>(__FUNCTION__)))

// The URI of the LAS extension.
// Used to identify the extended field names for encoding data from LAS files (LAS versions 1.0 to 1.3).
// By convention, will typically be used with prefix "las".  ???"las13"?
#define LAS_V1_0_URI "http://www.astm.org/COMMIT/E57/2010-las-v1.0" //??? change to v1.0 before final release

/// Create whitespace of given length, for indenting printouts in dump() functions
inline std::string space(int n) {return(std::string(static_cast<size_t>(n),' '));}

/// Convert number to decimal, hexadecimal, and binary strings  (Note hex strings don't have leading zeros).
template <class T>
std::string toString(T x) {std::ostringstream ss; ss << x; return(ss.str());}

inline std::string hexString(uint64_t x) {std::ostringstream ss; ss << "0x" << std::hex << std::setw(16)<< std::setfill('0') << x; return(ss.str());}
inline std::string hexString(uint32_t x) {std::ostringstream ss; ss << "0x" << std::hex << std::setw(8) << std::setfill('0') << x; return(ss.str());}
inline std::string hexString(uint16_t x) {std::ostringstream ss; ss << "0x" << std::hex << std::setw(4) << std::setfill('0') << x; return(ss.str());}
inline std::string hexString(uint8_t x)  {std::ostringstream ss; ss << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned>(x); return(ss.str());}
inline std::string binaryString(uint64_t x) {std::ostringstream ss;for(int i=63;i>=0;i--){ss<<((x&(1LL<<i))?1:0);if(i>0&&i%8==0)ss<<" ";} return(ss.str());}
inline std::string binaryString(uint32_t x) {std::ostringstream ss;for(int i=31;i>=0;i--){ss<<((x&(1LL<<i))?1:0);if(i>0&&i%8==0)ss<<" ";} return(ss.str());}
inline std::string binaryString(uint16_t x) {std::ostringstream ss;for(int i=15;i>=0;i--){ss<<((x&(1LL<<i))?1:0);if(i>0&&i%8==0)ss<<" ";} return(ss.str());}
inline std::string binaryString(uint8_t x) {std::ostringstream ss;for(int i=7;i>=0;i--){ss<<((x&(1LL<<i))?1:0);if(i>0&&i%8==0)ss<<" ";} return(ss.str());}
inline std::string hexString(int64_t x) {return(hexString(static_cast<uint64_t>(x)));}
inline std::string hexString(int32_t x) {return(hexString(static_cast<uint32_t>(x)));}
inline std::string hexString(int16_t x) {return(hexString(static_cast<uint16_t>(x)));}
inline std::string hexString(int8_t x)  {return(hexString(static_cast<uint8_t>(x)));}
inline std::string binaryString(int64_t x) {return(binaryString(static_cast<uint64_t>(x)));}
inline std::string binaryString(int32_t x) {return(binaryString(static_cast<uint32_t>(x)));}
inline std::string binaryString(int16_t x) {return(binaryString(static_cast<uint16_t>(x)));}
inline std::string binaryString(int8_t x)  {return(binaryString(static_cast<uint8_t>(x)));}

using ImageFileImplSharedPtr = std::shared_ptr<class ImageFileImpl>;
using NodeImplSharedPtr = std::shared_ptr<class NodeImpl>;

}

#endif
