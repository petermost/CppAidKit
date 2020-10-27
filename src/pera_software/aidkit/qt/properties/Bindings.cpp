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

#include "Bindings.hpp"
#include "BooleanProperty.hpp"
#include "IntegerProperty.hpp"
#include "StringProperty.hpp"
#include <QSpinBox>
#include <QLineEdit>
#include <QAction>
#include <QPushButton>

namespace pera_software::aidkit::qt {

//
// Bind a widget to an action:
//

void bindWidgetEnabledProperty(QWidget *widget, QAction *action)
{
	auto updateEnabledProperty = [=] {
		widget->setEnabled(action->isEnabled());
	};

	updateEnabledProperty();
	QAction::connect(action, &QAction::changed, updateEnabledProperty);
}

void bindWidgetVisibleProperty(QWidget *widget, QAction *action)
{
	auto updateVisibleProperty = [=] {
		widget->setVisible(action->isVisible());
	};

	updateVisibleProperty();
	QAction::connect(action, &QAction::changed, updateVisibleProperty);
}

void bindButtonTextProperty(QAbstractButton *button, QAction *action)
{
	auto updateTextProperty = [=] {
		button->setText(action->text());
	};

	updateTextProperty();
	QAction::connect(action, &QAction::changed, updateTextProperty);
}

void bindWidgetToolTipProperty(QWidget *widget, QAction *action)
{
	auto updateToolTipProperty = [=] {
		widget->setToolTip(action->toolTip());
	};

	updateToolTipProperty();
	QAction::connect(action, &QAction::changed, updateToolTipProperty);
}

void bindWidgetClickedSignal(QAbstractButton *button, QAction *action)
{
	QAbstractButton::connect(button, &QPushButton::clicked, action, &QAction::trigger);
}

//
// Bind a widget to a property:
//

void bindWidgetEnabledProperty(QWidget *widget, BooleanProperty *property)
{
	widget->setEnabled(property->value());

	BooleanProperty::connect(property, &BooleanProperty::valueChanged, widget, &QWidget::setEnabled);
}


void bindSpinBoxValueProperty(QSpinBox *spinBox, IntegerProperty *property)
{
	spinBox->setValue(property->value());

	QSpinBox::connect(spinBox, qOverload<int>(&QSpinBox::valueChanged), property, &IntegerProperty::setValue);
	IntegerProperty::connect(property, &IntegerProperty::valueChanged, spinBox, &QSpinBox::setValue);
}


void bindLineEditTextProperty(QLineEdit *lineEdit, StringProperty *property)
{
	lineEdit->setText(property->value());

	QLineEdit::connect(lineEdit, &QLineEdit::textChanged, property, &StringProperty::setValue);
	StringProperty::connect(property, &StringProperty::valueChanged, lineEdit, &QLineEdit::setText);
}

}
