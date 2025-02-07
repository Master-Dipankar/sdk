/**
 * @file GfxProcCG.h
 * @brief Graphics layer using Cocoa Touch
 *
 * (c) 2013-2015 by Mega Limited, Auckland, New Zealand
 *
 * This file is part of the MEGA SDK - Client Access Engine.
 *
 * Applications using the MEGA API must present a valid application key
 * and comply with the the rules set forth in the Terms of Service.
 *
 * The MEGA SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * @copyright Simplified (2-clause) BSD License.
 *
 * You should have received a copy of the license along with this
 * program.
 */

#ifdef USE_IOS
#ifndef GFX_CLASS
#define GFX_CLASS GfxProcCG

#include "mega.h"
#include <ImageIO/CGImageSource.h>

// bitmap graphics processor
class MEGA_API GfxProcCG : public mega::GfxProc
{
    CGImageSourceRef imageSource;
    CFDictionaryRef imageParams;
    CFMutableDictionaryRef thumbnailParams;
    CGImageRef createThumbnailWithMaxSize(int size);
    int maxSizeForThumbnail(const int rw, const int rh);
private: // mega::GfxProc implementations
    const char* supportedformats();
    bool readbitmap(mega::FileAccess*, const mega::LocalPath&, int);
    bool resizebitmap(int, int, mega::string*);
    void freebitmap();
public:
    GfxProcCG();
    ~GfxProcCG();
};
#endif

void ios_statsid(std::string *statsid);
void ios_appbasepath(std::string *appbasepath);
#endif
