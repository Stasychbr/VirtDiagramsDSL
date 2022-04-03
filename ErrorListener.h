#pragma once

#include <QObject>

#include <BaseErrorListener.h>

class ErrorListener : public QObject, public antlr4::BaseErrorListener
{
	Q_OBJECT
public:
	void syntaxError(antlr4::Recognizer* recognizer,
					 antlr4::Token* offendingSymbol,
					 size_t line, size_t charPositionInLine,
					 const std::string &msg,
					 std::exception_ptr e) override;

Q_SIGNALS:
	//Add all required info to signature
	// and connect corresponding receiver
	void errorOccured(const std::string& msg);
};

