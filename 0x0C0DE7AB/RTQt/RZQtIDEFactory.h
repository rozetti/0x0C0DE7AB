#pragma once

#include "RZQtIDELeftGutterWidgetLine.h"

class IRZQtIDEFactory
{
public:
    virtual IRZQtIDELeftGutterWidgetLine *createLeftGutterLine() const = 0;
};

class RZQtIDELeftGutterWidgetLine;

class RZQtIDEFactory : public IRZQtIDEFactory
{
public:
    virtual IRZQtIDELeftGutterWidgetLine *createLeftGutterLine() const override
    {
        return new RZQtIDELeftGutterWidgetLine();
    }

    static RZQtIDEFactory _instance;
};

