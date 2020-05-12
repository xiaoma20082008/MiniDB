# MiniDB

## Intro

A Simple Disk Based B+Tree Relational Database Management System Written By C++.

## Usage

```shell script
  cd ~
  git clone https://github.com/xiaoma20082008/MiniDB.git
  cd MiniDB
  mkdir build && cd build
  cmake .. && make
  ./MiniDB
```

Enjoy it !!!

## Internal

### SQL Syntax

All Of The SQL Syntax Is Similar To Antlr4's Syntax.

#### Common


```
expr
    : longValue                                             #LongExpr
    | strValue                                              #StringExpr
    | decValue                                              #DecimalExpr
    | NULL                                                  #NullExpr
    | TRUE                                                  #BoolExpr
    | FALSE                                                 #BoolExpr
    | ident                                                 #IdentExpr
    | functionCall                                          #FunCallExpr
    | ('+' | '-' | '~') expr                                #UnaryExpr
    | expr operator expr                                    #BinaryExpr
    | 'not' expr                                            #NotExpr
    | expr 'is' 'not'? 'null'                               #IsNullExpr
    | 'between' expr 'and' expr                             #BetweenExpr
    | 'like' expr                                           #LikeExpr
    ;
operator
    : '+' | '-' | '*' | '/' | '%' |'^'                      #ArithmeticExpr
    | '<' | '<=' | '>' | '>=' | '!=' | '<>'                 #CompareExpr
    | 'and' | 'or'                                          #LogicalExpr
    ;
strValue
    : '\'' ~('\'') '\''
    ;
decValue
    : [0-9]+'.'[0-9]+
    ;
longValue
    : [1-9][0-9]*
    ;
ident
    : [A-Za-z_$][A-Za-z_$0-9]*
    ;
```

#### DDL

```
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

columnDef
    :
    ;
```

#### DML

```
insert
    : INSERT INTO? tb=IDENT '(' ')' VALUES '(' ')'
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
```

### B+Tree Format

`todo`
