// Copyright 2020 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <pera_software/aidkit/aidkit.hpp>

class QAction;
class QWidget;
class QSpinBox;
class QLineEdit;
class QAbstractButton;

namespace pera_software::aidkit::qt {

class BooleanProperty;
class StringProperty;
class IntegerProperty;

// Bind a widget to an action:

void AIDKIT_API bindWidgetEnabledProperty(QWidget *widget, QAction *action);
void AIDKIT_API bindWidgetVisibleProperty(QWidget *widget, QAction *action);
void AIDKIT_API bindButtonTextProperty(QAbstractButton *button, QAction *action);
void AIDKIT_API bindWidgetToolTipProperty(QWidget *widget, QAction *action);
void AIDKIT_API bindWidgetClickedSignal(QAbstractButton *button, QAction *action);

// Bind a widget to a property:

void AIDKIT_API bindWidgetEnabledProperty(QWidget *widget, BooleanProperty *property);
void AIDKIT_API bindSpinBoxValueProperty(QSpinBox *spinBox, IntegerProperty *property);
void AIDKIT_API bindLineEditTextProperty(QLineEdit *lineEdit, StringProperty *property);

}
