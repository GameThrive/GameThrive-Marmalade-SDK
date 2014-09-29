/*
C++ Shim implementation of the s3eGameThrive extension's.

Not intended for modifications

These functions are called by C# to access native interface and from C++ to
access managed interface.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eGameThrive_shim.h"

using namespace s3eGameThriveExtension;


IManagedS3Es3eGameThriveAPI^ s3eGameThriveShim::s_ManagedInterface = nullptr;

s3eGameThriveShim::s3eGameThriveShim()
{
}

s3eGameThriveShim::~s3eGameThriveShim()
{
    Terminate();
}

bool s3eGameThriveShim::Init(IManagedS3Es3eGameThriveAPI^ managedAPI)
{
    // It's an error to do this twice.
    if (s_ManagedInterface)
        return false;

    s_ManagedInterface = managedAPI;
    return true;
}

bool s3eGameThriveShim::Terminate()
{
    // It's an error to do this twice.
    if (!s_ManagedInterface)
        return false;

    s_ManagedInterface = nullptr;
    return true;
}

IManagedS3Es3eGameThriveAPI^ s3eGameThriveShim::GetInterface()
{
    return s_ManagedInterface;
}
