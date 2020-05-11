set(SOURCES
        AstOptimizer.h AstOptimizer.cpp
        CatalogManager.h CatalogManager.cpp
        CommandManager.h CommandManager.cpp
        DBEngine.h DBEngine.cpp
        Exception.h
        Interpreter.h Interpreter.cpp
        RelNode.h RelNode.cpp
        SqlCall.h SqlCall.cpp
        SqlStmtParser.h SqlStmtParser.cpp
        SqlExpr.h SqlExpr.cpp
        SqlExprParser.h SqlExprParser.cpp
        SqlLexer.h SqlLexer.cpp
        SqlNode.h
        SqlParser.h SqlParser.cpp
        StringUtils.h StringUtils.cpp
        Types.h
        )

add_library(mini_db STATIC ${SOURCES})