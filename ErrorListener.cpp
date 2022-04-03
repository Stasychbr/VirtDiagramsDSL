#include "ErrorListener.h"

void ErrorListener::syntaxError(antlr4::Recognizer* recognizer,
								antlr4::Token* offendingSymbol,
								size_t line, size_t charPositionInLine,
								const std::string& msg,
								std::__exception_ptr::exception_ptr e)
{
	Q_EMIT errorOccured(msg);
}
