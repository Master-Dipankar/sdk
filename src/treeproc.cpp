/**
 * @file treeproc.cpp
 * @brief Node tree processor
 *
 * (c) 2013-2014 by Mega Limited, Auckland, New Zealand
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

#include "mega/treeproc.h"
#include "mega/megaclient.h"

namespace mega {
// create share keys
TreeProcShareKeys::TreeProcShareKeys(Node* n)
{
    sn = n;
}

void TreeProcShareKeys::proc(MegaClient*, Node* n)
{
    snk.add(n, sn, sn != NULL);
}

void TreeProcShareKeys::get(Command* c)
{
    snk.get(c);
}

void TreeProcForeignKeys::proc(MegaClient* client, Node* n)
{
    if (n->foreignkey)
    {
        client->nodekeyrewrite.push_back(n->nodehandle);

        n->foreignkey = false;
    }
}

// total disk space / node count
TreeProcDU::TreeProcDU()
{
    numbytes = 0;
    numfiles = 0;
    numfolders = 0;
}

void TreeProcDU::proc(MegaClient*, Node* n)
{
    if (n->type == FILENODE)
    {
        numbytes += n->size;
        numfiles++;
    }
    else
    {
        numfolders++;
    }
}

// mark node as removed and notify
void TreeProcDel::proc(MegaClient* client, Node* n)
{
    n->changed.removed = true;
    client->notifynode(n);
}

#ifdef ENABLE_SYNC
// stop sync get
void TreeProcDelSyncGet::proc(MegaClient*, Node* n)
{
    if (n->syncget)
    {
        delete n->syncget;
        n->syncget = NULL;
    }
}

LocalTreeProcChangeSync::LocalTreeProcChangeSync(Sync *sync)
{
    this->newsync = sync;
}

void LocalTreeProcChangeSync::proc(MegaClient *, LocalNode *localnode)
{
    localnode->sync->statecachedel(localnode);
    localnode->sync = newsync;
    newsync->statecacheadd(localnode);
}

#endif
} // namespace
