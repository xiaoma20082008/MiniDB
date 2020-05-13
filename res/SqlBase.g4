grammar SqlBase;

import Keywords;

command
    : createDatabase
    | createTable
    | createIndex
    | dropDatabase
    | dropTable
    | dropIndex
    | insert
    | delete
    | update
    | select
    | begin
    | commit
    | rollback
    ;

createDatabase
    : CREATE (DATABASE | SCHEMA) db=ident
    ;
createTable
    : CREATE TABLE db=ident '(' columnDef (',' columnDef)*  ')'
    ;
createIndex
    : CREATE INDEX idx=ident ON tb=ident USING '(' ident (',' ident)* ')'
    ;
dropDatabase
    : DROP (DATABASE | SCHEMA) db=ident
    ;
dropTable
    : DROP TABLE tb=ident
    ;
dropIndex
    : DROP INDEX idx=ident
    ;

insert
    : INSERT INTO? tb=ident '('col+=ident (',' col+=ident)* ')' VALUES exprList
    ;
update
    : UPDATE tb=IDENT SET lhs=expr '=' rhs=expr (',' lhs=expr '=' rhs=expr)* (WHERE expr)?
    ;
delete
    : DELETE FROM tb=IDENT (WHERE expr)?
    ;
select
    : SELECT (ALL | DISTINCT)? selectItem (',' selectItem)*
      (FROM tableExpr)?
      (WHERE expr)?
      (GROUP BY expr (',' expr)* (HAVING expr)?)?
      (ORDER BY expr (ASC|DESC)?)?
      (LIMIT limit=longValue ((',' | OFFSET) offset=longValue)?)?
    ;

begin
    : BEGIN
    | START TRANSACTION
    ;
commit
    : COMMIT
    ;
rollback
    : ROLLBACK
    ;

selectItem
    : expr (AS? alias=ident)?
    ;
tableExpr
    : tb=ident (AS? alias=ident)?                #simple
    | tableExpr joinType JOIN tableExpr
            ON expr                              #joinOn
    | tableExpr joinType JOIN tableExpr
            USING '(' ident (',' ident)* ')'     #joinUsing
    | tableExpr ',' tableExpr                    #joinCross
    ;
joinType
    : LEFT | RIGHT | CROSS | INNER
    ;
columnDef
    :
    ;

subQuery
    :
    ;
expr
    : longValue                                             #LongExpr
    | strValue                                              #StringExpr
    | decValue                                              #DecimalExpr
    | NULL                                                  #NullExpr
    | TRUE                                                  #BoolExpr
    | FALSE                                                 #BoolExpr
    | ident                                                 #IdentExpr
    | funcCall                                              #FunCallExpr
    | ('+' | '-' | '~') expr                                #UnaryExpr
    | expr operator expr                                    #BinaryExpr
    | NOT expr                                              #NotExpr
    | expr IS NOT? (TRUE|FALSE|UNKNOWN)                     #IsExpr
    | 'between' expr 'and' expr                             #BetweenExpr
    | 'like' expr                                           #LikeExpr
    ;

/*

expr:
      isExpr                             #IsExpr
    | NOT expr                           #NotExpr
    | expr op = logicalOperator expr     #BinaryExpr
;

boolExpr:
    predicate                               #primaryExprPredicate
    | isExpr                                #primaryExprIsNull
    | boolExpr compareOperator predicate    #primaryExprCompare
;

isExpr
    : boolExpr (IS NOT? type=(TRUE|FALSE|UNKNOWN|NULL))?
    ;

predicate:
    bitExpr (
        NOT predicateOperations
        |  LIKE bitExpr
    )?
;

predicateOperations:
    IN (subQuery | '(' exprList ')')    # predicateExprIn
    | BETWEEN bitExpr AND predicate     # predicateExprBetween
    | LIKE simpleExpr                   # predicateExprLike
;

bitExpr:
    simpleExpr
    | bitExpr op = arithmeticOperator bitExpr
    | bitExpr op = ('<<' | '>>') bitExpr
    | bitExpr op = ('&&' | '&') bitExpr
    | bitExpr op = ('||' | '|') bitExpr
;

simpleExpr:
    variable                                                                                             # simpleExprVariable
    | columnRef jsonOperator?                                                                            # simpleExprColumnRef
    | runtimeFunctionCall                                                                                # simpleExprRuntimeFunction
    | functionCall                                                                                       # simpleExprFunction
    | simpleExpr COLLATE_SYMBOL textOrIdentifier                                                         # simpleExprCollate
    | literal                                                                                            # simpleExprLiteral
    | PARAM_MARKER                                                                                       # simpleExprParamMarker
    | sumExpr                                                                                            # simpleExprSum
    | {serverVersion >= 80000}? groupingOperation                                                        # simpleExprGroupingOperation
    | {serverVersion >= 80000}? windowFunctionCall                                                       # simpleExprWindowingFunction
    | simpleExpr CONCAT_PIPES_SYMBOL simpleExpr                                                          # simpleExprConcat
    | op = (PLUS_OPERATOR | MINUS_OPERATOR | BITWISE_NOT_OPERATOR) simpleExpr                            # simpleExprUnary
    | not2Rule simpleExpr                                                                                # simpleExprNot
    | ROW_SYMBOL? OPEN_PAR_SYMBOL exprList CLOSE_PAR_SYMBOL                                              # simpleExprList
    | EXISTS_SYMBOL? subquery                                                                            # simpleExprSubQuery
    | OPEN_CURLY_SYMBOL identifier expr CLOSE_CURLY_SYMBOL                                               # simpleExprOdbc
    | MATCH_SYMBOL identListArg AGAINST_SYMBOL OPEN_PAR_SYMBOL bitExpr fulltextOptions? CLOSE_PAR_SYMBOL # simpleExprMatch
    | BINARY_SYMBOL simpleExpr                                                                           # simpleExprBinary
    | CAST_SYMBOL OPEN_PAR_SYMBOL expr AS_SYMBOL castType arrayCast? CLOSE_PAR_SYMBOL                    # simpleExprCast
    | CASE_SYMBOL expr? (whenExpression thenExpression)+ elseExpression? END_SYMBOL                      # simpleExprCase
    | CONVERT_SYMBOL OPEN_PAR_SYMBOL expr COMMA_SYMBOL castType CLOSE_PAR_SYMBOL                         # simpleExprConvert
    | CONVERT_SYMBOL OPEN_PAR_SYMBOL expr USING_SYMBOL charsetName CLOSE_PAR_SYMBOL                      # simpleExprConvertUsing
    | DEFAULT_SYMBOL OPEN_PAR_SYMBOL simpleIdentifier CLOSE_PAR_SYMBOL                                   # simpleExprDefault
    | VALUES_SYMBOL OPEN_PAR_SYMBOL simpleIdentifier CLOSE_PAR_SYMBOL                                    # simpleExprValues
;

*/

exprList
    : '(' expr (',' expr)* ')'
    ;
funcCall
    : name=ident '(' (DISTINCT)? (expr (',' expr)*)? ')'
    ;
operator
    :
    ;
arithmeticOperator
    : '*' | '/' | '%' | '^' | '+' | '-'
    ;
compareOperator
    : '<' | '<=' | '>' | '>=' | '!=' | '<>'
    ;
logicalOperator
    : AND | OR
    ;

strValue
    : '\'' ~('\'')? '\''
    ;
decValue
    : DECIMAL_VAL
    ;
longValue
    : LONG_VAL
    ;
ident
    : IDENT
    ;

fragment DECIMAL_VAL
    : [0-9]+'.'[0-9]+
    ;
fragment LONG_VAL
    : [1-9][0-9]*
    ;
fragment IDENT
    : [A-Za-z_$][A-Za-z_$0-9]*
    ;