/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include "collectsymbolsastvisitor.h"

#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>

#include <stringcachefwd.h>

namespace ClangBackEnd {

class CollectSymbolsConsumer : public clang::ASTConsumer
{
public:
    CollectSymbolsConsumer(SymbolEntries &symbolEntries,
                           SourceLocationEntries &sourceLocationEntries,
                           FilePathCache<std::mutex> &filePathCache)
        : m_symbolEntries(symbolEntries),
          m_sourceLocationEntries(sourceLocationEntries),
          m_filePathCache(filePathCache)
    {}

    void HandleTranslationUnit(clang::ASTContext &astContext) override
    {
        CollectSymbolsASTVisitor visitor{m_symbolEntries,
                                         m_sourceLocationEntries,
                                         m_filePathCache,
                                         astContext.getSourceManager()};
        visitor.TraverseDecl(astContext.getTranslationUnitDecl());
    }

     bool shouldSkipFunctionBody(clang::Decl *declation) override
     {
         const clang::SourceManager &sourceManager =  declation->getASTContext().getSourceManager();
         const clang::SourceLocation location = declation->getLocation();

         if (sourceManager.isInSystemHeader(location))
             return true;

         return false;
     }

private:
    SymbolEntries &m_symbolEntries;
    SourceLocationEntries &m_sourceLocationEntries;
    FilePathCache<std::mutex> &m_filePathCache;
};
}
