#pragma once

#include <QObject>

#include <BaseErrorListener.h>

class ErrorListener : public QObject, public antlr4::BaseErrorListener
{
	Q_OBJECT
public:
<<<<<<< HEAD
    ErrorListener(QObject* parent);
=======
>>>>>>> 2793513d8fd17ea6c1bff93ea134aaaa37f31aff
	void syntaxError(antlr4::Recognizer* recognizer,
					 antlr4::Token* offendingSymbol,
					 size_t line, size_t charPositionInLine,
					 const std::string &msg,
					 std::exception_ptr e) override;
<<<<<<< HEAD
    ~ErrorListener() = default;

Q_SIGNALS:
    // Add all required info to signature
	// and connect corresponding receiver
    void errorOccured(size_t line, size_t charPositionInLine, const std::string& msg);
=======

Q_SIGNALS:
	//Add all required info to signature
	// and connect corresponding receiver
	void errorOccured(const std::string& msg);
>>>>>>> 2793513d8fd17ea6c1bff93ea134aaaa37f31aff
};

