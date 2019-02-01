#ifndef NODEIMPL_H
#define NODEIMPL_H
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

#include <set>

#include "Common.h"

namespace e57 {

class CheckedFile;

class NodeImpl : public std::enable_shared_from_this<NodeImpl>
{
public:
    virtual NodeType        type() const = 0;
    void                    checkImageFileOpen(const char* srcFileName, int srcLineNumber, const char* srcFunctionName) const;
    virtual bool            isTypeEquivalent(NodeImplSharedPtr ni) = 0;
    bool                    isRoot() const;
    NodeImplSharedPtr       parent();
    ustring                 pathName() const;
    ustring                 relativePathName(const NodeImplSharedPtr &origin, ustring childPathName = ustring()) const;
    ustring                 elementName() const;
    ImageFileImplSharedPtr  destImageFile();

    ustring                 imageFileName() const;
    virtual bool            isDefined(const ustring& pathName) = 0;
    bool                    isAttached() const;
    virtual void            setAttachedRecursive();

    void                    setParent(NodeImplSharedPtr parent, const ustring& elementName);
    bool                    isTypeConstrained();

    virtual NodeImplSharedPtr get(const ustring& pathName);
    virtual void            set(const ustring& pathName, NodeImplSharedPtr ni, bool autoPathCreate = false);
    virtual void            set(const std::vector<ustring>& fields, unsigned level, NodeImplSharedPtr ni, bool autoPathCreate = false);

    virtual void            checkLeavesInSet(const std::set<ustring>& pathNames, NodeImplSharedPtr origin) = 0;
    void                    checkBuffers(const std::vector<SourceDestBuffer>& sdbufs, bool allowMissing);
    bool                    findTerminalPosition(const NodeImplSharedPtr &target, uint64_t& countFromLeft);

    virtual void            writeXml(ImageFileImplSharedPtr imf, CheckedFile& cf, int indent, const char* forcedFieldName=nullptr) = 0;

    virtual                 ~NodeImpl() = default;

#ifdef E57_DEBUG
    virtual void            dump(int indent = 0, std::ostream& os = std::cout) const;
#endif

private:
    bool _verifyPathNameAbsolute( const ustring &inPathName );

    NodeImplSharedPtr   _verifyAndGetRoot();

protected:
    friend class StructureNodeImpl;
    friend class CompressedVectorWriterImpl;
    friend class Decoder;
    friend class Encoder;

                               NodeImpl(std::weak_ptr<ImageFileImpl> destImageFile);
    NodeImpl&                  operator=(NodeImpl& n);
    virtual NodeImplSharedPtr  lookup(const ustring& /*pathName*/) {return NodeImplSharedPtr();}
    NodeImplSharedPtr          getRoot();

    std::weak_ptr<ImageFileImpl>       destImageFile_;
    std::weak_ptr<NodeImpl>            parent_;
    ustring                            elementName_;
    bool                               isAttached_;
};

}

#endif
