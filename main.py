import sys
from antlr4 import *
from antlr_build.MetaGrammarLexer import MetaGrammarLexer
from antlr_build.MetaGrammarParser import MetaGrammarParser
from antlr_build.MetaGrammarVisitor import MetaGrammarVisitor


def get_username():
    return 'User'


class MyVisitor(MetaGrammarVisitor):
    i = 0
    def visitRule_(self, ctx):
        print(ctx.getText(), self.i)
        self.i += 1


if __name__ == "__main__":
    str = open('rules.txt').read()
    data = InputStream(str)
    # lexer
    lexer = MetaGrammarLexer(data)
    stream = CommonTokenStream(lexer)
    # parser
    parser = MetaGrammarParser(stream)
    tree = parser.rulelist()
    # evaluator
    visitor = MyVisitor()
    visitor.visit(tree)
