TEMPLATE = lib

contains(CONFIG, dll) {
    DEFINES += CPLUSPLUS_BUILD_LIB
} else {
    DEFINES += CPLUSPLUS_BUILD_STATIC_LIB
}

unix:QMAKE_CXXFLAGS_DEBUG += -O2
win32:QMAKE_CXXFLAGS_DEBUG += -O2

CONFIG(debug , debug|release) {
   DESTDIR=../../../debug

} else {
    DESTDIR=../../../release
}

CONFIG += c++11

HEADERS += \
    AST.h \
    ASTfwd.h \
    ASTMatcher.h \
    ASTPatternBuilder.h \
    ASTVisitor.h \
    Bind.h \
    Control.h \
    CoreTypes.h \
    CPlusPlus.h \
    CPlusPlusForwardDeclarations.h \
    cppassert.h \
    DiagnosticClient.h \
    FullySpecifiedType.h \
    Lexer.h \
    Literals.h \
    LiteralTable.h \
    Matcher.h \
    MemoryPool.h \
    Name.h \
    Names.h \
    NameVisitor.h \
    ObjectiveCTypeQualifiers.h \
    Parser.h \
    QtContextKeywords.h \
    SafeMatcher.h \
    Scope.h \
    Symbol.h \
    Symbols.h \
    SymbolVisitor.h \
    Templates.h \
    Token.h \
    TranslationUnit.h \
    Type.h \
    TypeVisitor.h

SOURCES += \
    AST.cpp \
    ASTClone.cpp \
    ASTMatch0.cpp \
    ASTMatcher.cpp \
    ASTPatternBuilder.cpp \
    ASTVisit.cpp \
    ASTVisitor.cpp \
    Bind.cpp \
    Control.cpp \
    CoreTypes.cpp \
    DiagnosticClient.cpp \
    FullySpecifiedType.cpp \
    Keywords.cpp \
    Lexer.cpp \
    Literals.cpp \
    Matcher.cpp \
    MemoryPool.cpp \
    Name.cpp \
    Names.cpp \
    NameVisitor.cpp \
    ObjectiveCAtKeywords.cpp \
    ObjectiveCTypeQualifiers.cpp \
    Parser.cpp \
    QtContextKeywords.cpp \
    Scope.cpp \
    Symbol.cpp \
    Symbols.cpp \
    SymbolVisitor.cpp \
    Templates.cpp \
    Token.cpp \
    TranslationUnit.cpp \
    Type.cpp \
    TypeVisitor.cpp
